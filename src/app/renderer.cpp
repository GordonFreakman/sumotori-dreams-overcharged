#include "boundary.h"

#include <glad/gl.h>

#include <stdio.h>

static SDL_GLContext s_context;

extern SumoS32 g_gameRenderQualityEnabled;

static GLuint UndefinedMaterialTexture(SumoS32 slot);

void SumoRenderRequestGLAttributes() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

bool SumoRenderCreateContext() {
  s_context = SDL_GL_CreateContext(SumoPlatformWindow());
  if (s_context == NULL) {
    fprintf(stderr, "sumotori: GL context creation failed: %s\n",
            SDL_GetError());
    return false;
  }
  SDL_GL_MakeCurrent(SumoPlatformWindow(), s_context);
  if (gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0) {
    fprintf(stderr, "sumotori: GL 3.3 core loader failed\n");
    return false;
  }
  SDL_GL_SetSwapInterval(1);

  int stencilBits = 0;
  SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &stencilBits);
  if (stencilBits < 8) {
    fprintf(stderr,
            "sumotori: got %d stencil bits, need 8; shadows disabled\n",
            stencilBits);
    g_gameRenderQualityEnabled = 0;
  }
  return true;
}

void SumoRenderPresent() { SDL_GL_SwapWindow(SumoPlatformWindow()); }

bool SumoRenderContextReady() { return s_context != NULL; }

extern SumoS32 g_gameConfiguredWidth;
extern SumoS32 g_gameConfiguredHeight;
extern SumoS32 g_gameRenderWidth;
extern SumoS32 g_gameRenderHeight;
extern SumoF32 g_gameAspectRatio;

SumoS32 RefreshGameProjection();

static bool s_projectionLive;

void SumoRenderMarkProjectionLive() { s_projectionLive = true; }

void SumoRenderAdoptTargetSize(SumoS32 width, SumoS32 height) {
  if (width <= 0 || height <= 0)
    return;
  bool changed = width != g_gameRenderWidth || height != g_gameRenderHeight ||
                 width != g_gameConfiguredWidth ||
                 height != g_gameConfiguredHeight;

  g_gameRenderWidth = width;
  g_gameRenderHeight = height;
  g_gameConfiguredWidth = width;
  g_gameConfiguredHeight = height;
  g_gameAspectRatio = (SumoF32)width / height;

  if (changed && s_projectionLive)
    RefreshGameProjection();
}

void SumoRenderUpdateTargetSize() {
  SDL_Window *window = SumoPlatformWindow();
  if (window == NULL)
    return;
  int width = 0;
  int height = 0;
#if SUMO_SDL_VERSION == 3
  SDL_GetWindowSizeInPixels(window, &width, &height);
#else
  SDL_GL_GetDrawableSize(window, &width, &height);
#endif
  SumoRenderAdoptTargetSize((SumoS32)width, (SumoS32)height);
}

SumoU8 *AcquireGameBackBufferPixels(SumoS32 *p_pitch) {
  if (s_context == NULL || g_gameConfiguredWidth <= 0 ||
      g_gameConfiguredHeight <= 0) {
    return NULL;
  }
  SumoS32 width = g_gameConfiguredWidth;
  SumoS32 height = g_gameConfiguredHeight;
  SumoU8 *pixels = new SumoU8[(size_t)width * height * 4];
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  for (SumoS32 row = 0; row < height / 2; ++row) {
    SumoU8 *top = pixels + (size_t)row * width * 4;
    SumoU8 *bottom = pixels + (size_t)(height - 1 - row) * width * 4;
    for (SumoS32 column = 0; column < width * 4; ++column) {
      SumoU8 swap = top[column];
      top[column] = bottom[column];
      bottom[column] = swap;
    }
  }
  for (SumoS32 index = 0; index < width * height; ++index) {
    SumoU8 *pixel = pixels + (size_t)index * 4;
    SumoU8 swap = pixel[0];
    pixel[0] = pixel[2];
    pixel[2] = swap;
  }
  *p_pitch = width * 4;
  return pixels;
}

void ReleaseGameBackBufferPixels(SumoU8 *p_pixels) { delete[] p_pixels; }

#include "boundary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STBTT_assert(expression) SDL_assert(expression)
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

struct SumoFontSlot {
  const char *retailName;
  const char *assetFile;
  const char *environmentOverride;
  SumoAssetBlob blob;
  const unsigned char *data;
  stbtt_fontinfo info;
  bool loaded;
  bool failed;
};

static SumoFontSlot s_fontSlots[2] = {
    {"Times New Roman",
     "fonts/LiberationSerif-Regular.ttf",
     "SUMOTORI_FONT_TIMES",
     {},
     NULL,
     {},
     false,
     false},
    {"Lucida Console",
     "fonts/DejaVuSansMono.ttf",
     "SUMOTORI_FONT_CONSOLE",
     {},
     NULL,
     {},
     false,
     false},
};

static SumoFontSlot *LoadFont(const char *fontName) {
  SumoFontSlot *slot = &s_fontSlots[0];
  for (int index = 0; index < 2; ++index) {
    if (strcmp(s_fontSlots[index].retailName, fontName) == 0) {
      slot = &s_fontSlots[index];
      break;
    }
  }
  if (slot->loaded)
    return slot;
  if (slot->failed)
    return NULL;

  const char *override = SDL_getenv(slot->environmentOverride);
  if (override != NULL) {
    if (!SumoAssetOpenFile(override, &slot->blob)) {
      fprintf(stderr, "sumotori: font %s not found at %s\n", fontName,
              override);
      slot->failed = true;
      return NULL;
    }
  } else if (!SumoAssetOpen(slot->assetFile, &slot->blob)) {
    fprintf(stderr, "sumotori: font %s not found (%s)\n", fontName,
            slot->assetFile);
    slot->failed = true;
    return NULL;
  }

  slot->data = (const unsigned char *)slot->blob.data;
  if (!stbtt_InitFont(&slot->info, slot->data,
                      stbtt_GetFontOffsetForIndex(slot->data, 0))) {
    fprintf(stderr, "sumotori: font %s failed to parse\n", fontName);
    SumoAssetClose(&slot->blob);
    slot->data = NULL;
    slot->failed = true;
    return NULL;
  }
  slot->loaded = true;
  return slot;
}

static void RasterizeCoverage(SumoFontSlot *font, const char *text,
                              SumoS32 width, SumoS32 height, SumoS32 cellHeight,
                              SumoU8 *coverage, SumoS32 *extentWidth) {
  float scale = stbtt_ScaleForPixelHeight(&font->info, (float)cellHeight);
  int ascent;
  int descent;
  int lineGap;
  stbtt_GetFontVMetrics(&font->info, &ascent, &descent, &lineGap);
  int baseline = (int)((float)ascent * scale + 0.5f);

  float penX = 0.0f;
  for (const char *cursor = text; *cursor != 0; ++cursor) {
    int glyph = stbtt_FindGlyphIndex(&font->info, (unsigned char)*cursor);
    int advance;
    int leftSideBearing;
    stbtt_GetGlyphHMetrics(&font->info, glyph, &advance, &leftSideBearing);

    for (int strike = 0; strike < 2; ++strike) {
      int originX = (int)(penX + 0.5f) + strike;
      int x0;
      int y0;
      int x1;
      int y1;
      stbtt_GetGlyphBitmapBox(&font->info, glyph, scale, scale, &x0, &y0, &x1,
                              &y1);
      int glyphWidth = x1 - x0;
      int glyphHeight = y1 - y0;
      if (glyphWidth <= 0 || glyphHeight <= 0)
        continue;

      SumoU8 *glyphPixels =
          (SumoU8 *)malloc((size_t)(glyphWidth * glyphHeight));
      stbtt_MakeGlyphBitmap(&font->info, glyphPixels, glyphWidth, glyphHeight,
                            glyphWidth, scale, scale, glyph);
      int destinationX = originX + x0;
      int destinationY = baseline + y0;
      for (int row = 0; row < glyphHeight; ++row) {
        int targetY = destinationY + row;
        if (targetY < 0 || targetY >= height)
          continue;
        for (int column = 0; column < glyphWidth; ++column) {
          int targetX = destinationX + column;
          if (targetX < 0 || targetX >= width)
            continue;
          SumoU8 *target = &coverage[targetY * width + targetX];
          SumoU8 value = glyphPixels[row * glyphWidth + column];
          if (value > *target)
            *target = value;
        }
      }
      free(glyphPixels);
    }

    penX += (float)advance * scale;
  }

  SumoS32 extent = (SumoS32)(penX + 0.5f) + 1;
  if (extent > width)
    extent = width;
  *extentWidth = extent;
}

SumoS32 BlendTextIntoTexture(SumoU8 *p_pixels, const char *p_text, SumoS32 p_x,
                             SumoS32 p_y, SumoS32 p_textureWidth,
                             SumoS32 p_width, SumoS32 p_height,
                             SumoS32 p_fontHeight, SumoS32 p_textColor,
                             SumoS32 p_backgroundColor,
                             const char *p_fontName) {
  SumoFontSlot *font = LoadFont(p_fontName);
  if (font == NULL)
    return 0;

  SumoS32 cellHeight = (p_fontHeight * 96 + 36) / 72;

  SumoU8 *coverage = (SumoU8 *)calloc(1, (size_t)(p_width * p_height));
  SumoS32 extentWidth = 0;
  RasterizeCoverage(font, p_text, p_width, p_height, cellHeight, coverage,
                    &extentWidth);

  SumoU32 invertedText = (SumoU32)p_textColor ^ 0xffffffu;
  SumoU32 invertedBackground = (SumoU32)p_backgroundColor ^ 0xffffffu;
  SumoU8 *source = (SumoU8 *)malloc((size_t)(p_width * p_height * 4));
  memset(source, 0, (size_t)(p_width * p_height * 4));
  SumoS32 extentHeight = cellHeight < p_height ? cellHeight : p_height;
  for (SumoS32 row = 0; row < extentHeight; ++row) {
    for (SumoS32 column = 0; column < extentWidth; ++column) {
      SumoU8 *texel = &source[(row * p_width + column) * 4];
      SumoS32 mix = coverage[row * p_width + column];
      for (SumoS32 channel = 0; channel < 3; ++channel) {
        SumoS32 background =
            (SumoS32)((invertedBackground >> (channel * 8)) & 0xff);
        SumoS32 foreground = (SumoS32)((invertedText >> (channel * 8)) & 0xff);
        texel[channel] =
            (SumoU8)(background + (foreground - background) * mix / 255);
      }
    }
  }
  free(coverage);

  SumoU8 *sourceCursor = source;
  SumoU8 *destination =
      p_pixels + (p_y * p_textureWidth + p_x) * sizeof(SumoU32);
  if (p_height > 0) {
    SumoS32 remainingRows = p_height;
    SumoS32 destinationRowAdvance =
        (p_textureWidth - p_width) * (SumoS32)sizeof(SumoU32);
    do {
      if (p_width > 0) {
        SumoS32 remainingColumns = p_width;
        do {
          destination[0] =
              (SumoU8)(((SumoU32)destination[0] * (255 - sourceCursor[0])) >>
                       8);
          destination[1] =
              (SumoU8)(((SumoU32)destination[1] * (255 - sourceCursor[1])) >>
                       8);
          destination[2] =
              (SumoU8)(((SumoU32)destination[2] * (255 - sourceCursor[2])) >>
                       8);
          destination[3] =
              (SumoU8)(((SumoU32)destination[2] * (255 - sourceCursor[2])) >>
                       8);
          sourceCursor += sizeof(SumoU32);
          destination += sizeof(SumoU32);
          --remainingColumns;
        } while (remainingColumns != 0);
      }

      destination += destinationRowAdvance;
      --remainingRows;
    } while (remainingRows != 0);
  }

  free(source);
  return 0;
}

#include "boundary.h"

#include <glad/gl.h>

#include <stdio.h>
#include <string.h>

#include "decomp_keywords.h"

#include "containers.h"
#include "decomp.h"
#include "sumo_portable.h"

extern Vector3 g_gameCameraWorldPosition;
void RenderWaterSurface();

extern SumoS32 g_screenTintLevel;
extern SumoS32 g_gameMode;
extern const SumoF32 g_gameBoxDefaultValue;

SumoS32 WriteGameScreenshot();
Vector3 *ResetGameCameraState();

extern const char g_gameScreenshotFormat[] = "%s%d.bmp";
extern const char g_gameScreenshotReadMode[] = "rb";
extern const char g_gameScreenshotWriteMode[] = "wb";
char *g_gameScreenshotPrefix;
SumoS32 g_gameScreenshotIndex;
SumoS32 g_gameConfiguredWidth;
SumoS32 g_gameConfiguredHeight;

SumoIntPtr g_gameRampTexture;
SumoIntPtr g_gameAttenuationTexture;

extern const SumoF32 g_gameRampBias = 5.1f;
extern const SumoF32 g_gameRampStep32 = 0.03125f;
extern const SumoF32 g_gameFloorHalfExtent = 180.0f;
extern const SumoF32 g_gameArenaVerticalHalfSize = -3.0f;
extern const SumoF32 g_gameRampStep64 = 0.015625f;
extern const double g_gameRampDecayTwoPercent = 0.02f;
extern const double g_gameRampDecayFivePercent = 0.05f;
extern const double g_gameRampDecayOnePercent = 0.01f;
extern const double g_gameProjectionHalfFov = 0.6544984877109528;
extern const SumoF32 g_gameProjectionMinimum = 0.55f;
extern const SumoF32 g_gameNegativeHalf = -0.5f;
extern const SumoF32 g_gameTwo = 2.0f;
extern const SumoF32 g_gameCameraBackDistance = -100.0f;

SumoS32 g_gameAlternateCameraMode;
SumoF32 g_gameCameraDistanceScale = 10.0f;
SumoF32 g_gameCameraMoveScale = 1.5f;
SumoF32 g_gameCameraTurnScale = 0.5f;
Vector3 g_gameCameraPosition;
Vector3 g_gameCameraAngles;
Vector3 g_gameCameraAcceleration;
Vector3 g_gameCameraVelocity;
Vector3 g_gameCameraAngularVelocity;
SumoF32 g_gameCameraInputA;
SumoF32 g_gameCameraInputB;
SumoF32 g_gameAspectRatio = 1.333f;
SumoS32 g_gameRenderWidth = 1024;
SumoS32 g_gameRenderHeight = 768;
SumoF32 g_gameProjectionOffsetX;
SumoF32 g_gameProjectionOffsetY;
SumoF32 g_gameProjectionScaleX;
SumoF32 g_gameProjectionScaleY;
Vector3 g_gameViewOffset;
Matrix3 g_gameViewMatrix;

Vector3 *ResetGameCameraState() {
  g_gameCameraInputB = 0.0f;
  g_gameCameraInputA = 0.0f;

  Vector3 cameraPosition;
  cameraPosition.x = 0.0f;
  cameraPosition.y = 15.0f;
  cameraPosition.z = g_gameCameraBackDistance;

  g_gameCameraDistanceScale = 10.0f;
  g_gameCameraMoveScale = 1.5f;
  g_gameCameraTurnScale = 0.5f;
  g_gameCameraPosition = cameraPosition;

  if (g_gameAlternateCameraMode != 0) {
    cameraPosition.x = g_gameCameraBackDistance;
    cameraPosition.y = 7.0f;
    cameraPosition.z = 0.0f;
    g_gameCameraPosition = cameraPosition;
  }

  g_gameCameraAngles.z = 0.0f;
  g_gameCameraAngles.y = 0.0f;
  g_gameCameraAngles.x = 0.0f;
  if (g_gameMode != 0) {
    cameraPosition.x = g_gameCameraBackDistance;
    cameraPosition.y = 7.0f;
    cameraPosition.z = 0.0f;
    g_gameCameraPosition = cameraPosition;

    Vector3 cameraAngles;
    cameraAngles.x = 0.0f;
    cameraAngles.y = -1.5707964f;
    cameraAngles.z = 0.0f;
    g_gameCameraAngles = cameraAngles;
  }

  g_gameCameraAcceleration.z = 0.0f;
  g_gameCameraAcceleration.y = 0.0f;
  g_gameCameraAcceleration.x = 0.0f;
  g_gameCameraVelocity.z = 0.0f;
  g_gameCameraVelocity.y = 0.0f;
  g_gameCameraVelocity.x = 0.0f;
  g_gameCameraAngularVelocity.z = 0.0f;
  g_gameCameraAngularVelocity.y = 0.0f;
  g_gameCameraAngularVelocity.x = 0.0f;
  return &g_gameCameraPosition;
}

SumoS32 RefreshGameProjection();

SumoS32 g_gameSelectedPlayer = -1;
SumoS32 g_gameRoundTimer;
SumoS32 g_gameRoundEnabled = 1;

static GLuint s_program;
static GLint s_uniformView;
static GLint s_uniformProjection;
static GLint s_uniformFactor;
static GLint s_uniformMode;
static GLuint s_mainVertexBuffer;
static GLuint s_mainVertexArray;
static GLuint s_positionVertexBuffer;
static GLuint s_positionVertexArray;
static GLuint s_streamVertexBuffer;
static GLuint s_streamTextVertexArray;
static GLuint s_streamLineVertexArray;
static SumoF32 s_viewTransform[16];
static SumoF32 s_projectionTransform[16];
static bool s_transformsStored;

enum {
  c_renderModeFlat = 0,
  c_renderModeDot3 = 1,
  c_renderModeAlbedo = 2,
  c_renderModeText = 3,
  c_renderModeLine = 4
};

static const char *const c_vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 aPosition;\n"
    "layout(location = 1) in vec4 aColor;\n"
    "layout(location = 2) in vec2 aTexCoord;\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProjection;\n"
    "out vec4 vColor;\n"
    "out vec2 vTexCoord;\n"
    "void main() {\n"
    "  vec4 clip = uProjection * (uView * vec4(aPosition, 1.0));\n"
    "  gl_Position = vec4(clip.x, clip.y, clip.z * 2.0 - clip.w, clip.w);\n"
    "  vColor = aColor.zyxw;\n"
    "  vTexCoord = aTexCoord;\n"
    "}\n";

static const char *const c_fragmentShaderSource =
    "#version 330 core\n"
    "in vec4 vColor;\n"
    "in vec2 vTexCoord;\n"
    "uniform sampler2D uTexture;\n"
    "uniform vec3 uFactor;\n"
    "uniform int uMode;\n"
    "out vec4 oColor;\n"
    "void main() {\n"
    "  if (uMode == 0) {\n"
    "    oColor = vec4(uFactor, 1.0);\n"
    "  } else if (uMode == 1) {\n"
    "    vec3 t = texture(uTexture, vTexCoord).rgb;\n"
    "    float d = clamp(dot(vColor.rgb * 2.0 - 1.0, t * 2.0 - 1.0),\n"
    "                    0.0, 1.0);\n"
    "    oColor = vec4(d * uFactor, 1.0);\n"
    "  } else if (uMode == 2) {\n"
    "    oColor = vec4(uFactor * texture(uTexture, vTexCoord).rgb, 1.0);\n"
    "  } else if (uMode == 3) {\n"
    "    oColor = vec4(vColor.rgb, texture(uTexture, vTexCoord).a * "
    "vColor.a);\n"
    "  } else {\n"
    "    oColor = vec4(vColor.rgb, 1.0);\n"
    "  }\n"
    "}\n";

static GLuint CompileRenderShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  GLint status = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    char log[1024];
    glGetShaderInfoLog(shader, sizeof(log), NULL, log);
    fprintf(stderr, "sumotori: shader compile failed: %s\n", log);
  }
  return shader;
}

static bool EnsureRenderObjects() {
  if (s_program != 0)
    return true;
  if (!SumoRenderContextReady())
    return false;

  GLuint vertexShader =
      CompileRenderShader(GL_VERTEX_SHADER, c_vertexShaderSource);
  GLuint fragmentShader =
      CompileRenderShader(GL_FRAGMENT_SHADER, c_fragmentShaderSource);
  s_program = glCreateProgram();
  glAttachShader(s_program, vertexShader);
  glAttachShader(s_program, fragmentShader);
  glLinkProgram(s_program);
  GLint status = 0;
  glGetProgramiv(s_program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    char log[1024];
    glGetProgramInfoLog(s_program, sizeof(log), NULL, log);
    fprintf(stderr, "sumotori: shader link failed: %s\n", log);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  s_uniformView = glGetUniformLocation(s_program, "uView");
  s_uniformProjection = glGetUniformLocation(s_program, "uProjection");
  s_uniformFactor = glGetUniformLocation(s_program, "uFactor");
  s_uniformMode = glGetUniformLocation(s_program, "uMode");
  glUseProgram(s_program);
  glUniform1i(glGetUniformLocation(s_program, "uTexture"), 0);

  if (!s_transformsStored) {
    for (SumoS32 index = 0; index < 16; ++index) {
      s_viewTransform[index] = (index % 5) == 0 ? 1.0f : 0.0f;
      s_projectionTransform[index] = (index % 5) == 0 ? 1.0f : 0.0f;
    }
  }

  glGenBuffers(1, &s_mainVertexBuffer);
  glGenBuffers(1, &s_positionVertexBuffer);
  glGenBuffers(1, &s_streamVertexBuffer);
  glGenVertexArrays(1, &s_mainVertexArray);
  glGenVertexArrays(1, &s_positionVertexArray);
  glGenVertexArrays(1, &s_streamTextVertexArray);
  glGenVertexArrays(1, &s_streamLineVertexArray);

  glBindVertexArray(s_mainVertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, s_mainVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 0x240000, NULL, GL_STREAM_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (const void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 24, (const void *)12);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 24, (const void *)16);

  glBindVertexArray(s_positionVertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, s_positionVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 0x120000, NULL, GL_STREAM_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (const void *)0);

  glBindVertexArray(s_streamTextVertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, s_streamVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 0x250120, NULL, GL_STREAM_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (const void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 24, (const void *)12);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 24, (const void *)16);

  glBindVertexArray(s_streamLineVertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, s_streamVertexBuffer);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 16, (const void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 16, (const void *)12);

  glBindVertexArray(0);
  return true;
}

static void SetRenderFactor(SumoU32 packedColor) {
  glUniform3f(s_uniformFactor, (SumoF32)((packedColor >> 16) & 0xff) / 255.0f,
              (SumoF32)((packedColor >> 8) & 0xff) / 255.0f,
              (SumoF32)(packedColor & 0xff) / 255.0f);
}

HRESULT SetGameTransform(SumoU32 state, const SumoF32 *matrix) {
  s_transformsStored = true;
  if (state == 2)
    memcpy(s_viewTransform, matrix, sizeof(s_viewTransform));
  else if (state == 3)
    memcpy(s_projectionTransform, matrix, sizeof(s_projectionTransform));
  if (s_program != 0) {
    glUseProgram(s_program);
    glUniformMatrix4fv(s_uniformView, 1, GL_FALSE, s_viewTransform);
    glUniformMatrix4fv(s_uniformProjection, 1, GL_FALSE, s_projectionTransform);
  }
  return 0;
}

static HRESULT SetGameViewTransform(Matrix3 &matrix, Vector3 &transformed) {
  SumoF32 view[16];
  view[0] = matrix.m00;
  view[1] = matrix.m10;
  view[2] = matrix.m20;
  view[3] = 0.0f;
  view[4] = matrix.m01;
  view[5] = matrix.m11;
  view[6] = matrix.m21;
  view[7] = 0.0f;
  view[8] = matrix.m02;
  view[9] = matrix.m12;
  view[10] = matrix.m22;
  view[11] = 0.0f;
  view[12] = -transformed.x;
  view[13] = -transformed.y;
  view[14] = -transformed.z;
  view[15] = 1.0f;
  return SetGameTransform(2, view);
}

HRESULT ApplyGameViewTransform() {
  Vector3 transformed = g_gameViewMatrix.Transform(g_gameViewOffset);
  return SetGameViewTransform(g_gameViewMatrix, transformed);
}

Vector3 *ResetGameRoundState() {
  g_screenTintLevel = 0;
  g_gameSelectedPlayer = -1;
  g_gameRoundTimer = 0;
  g_gameRoundEnabled = 1;
  return ResetGameCameraState();
}

extern SumoU8 g_renderVertexScratch[];

SumoU8 g_gameLineVertexScratch[0x80000];
SumoU8 *g_gameLineVertexCursor;
SumoU8 *g_renderVertexCursor;

extern SumoIntPtr g_gameFontAtlasTexture;

HRESULT SetGameTexture(SumoU32 stage, SumoIntPtr texture);
Vector3 TransformWavyTextPoint(Vector3 &point);
extern Matrix3 g_gameInverseViewMatrix;
extern const SumoF32 g_wavyTextDisplacement;

struct GameTextVertex {
  Vector3 position;
  SumoU32 color;
  SumoF32 u;
  SumoF32 v;
};

DECOMP_SIZE_ASSERT(GameTextVertex, 0x18);

#define EMIT_GAME_TEXT_VERTEX(positionExpression, vertexColor, textureU,       \
                              textureV)                                        \
  do {                                                                         \
    ((GameTextVertex *)g_renderVertexCursor)->position = (positionExpression); \
    ((GameTextVertex *)g_renderVertexCursor)->color = (vertexColor);           \
    ((GameTextVertex *)g_renderVertexCursor)->u = (textureU);                  \
    ((GameTextVertex *)g_renderVertexCursor)->v = (textureV);                  \
    g_renderVertexCursor += sizeof(GameTextVertex);                            \
  } while (0)

SumoS32 InitializeGameVertexBuffers() {
  RefreshGameProjection();
  EnsureRenderObjects();
  SumoRenderMarkProjectionLive();
  return 0;
}

void ResetRenderVertexScratch() {
  g_renderVertexCursor = g_renderVertexScratch;
}

char *DrawGameText(SumoF32 x, SumoF32 y, char *text, SumoS32 color) {
  Vector3 initialOffset;
  initialOffset.x = g_wavyTextDisplacement;
  initialOffset.y = g_wavyTextDisplacement;
  initialOffset.z = 0.0f;
  Vector3 point = initialOffset;
  Vector3 offset = point.Transform(g_gameInverseViewMatrix);

  const SumoF32 initialX = x;
  const SumoU32 shadowColor = (SumoU32)color & 0xff000000;

  while (*text != 0) {
    SumoF32 nextY;
    Vector3 corners[4];

    point = MakeVector3(x, y, 1.0f);
    corners[0] = TransformWavyTextPoint(point);
    SumoF32 nextX = x + 0.025f;
    Vector3 topRightPoint = MakeVector3(nextX, y, 1.0f);
    corners[1] = TransformWavyTextPoint(topRightPoint);
    nextY = y - 0.038f;
    Vector3 bottomLeftPoint;
    Vector3 bottomRightPoint = MakeVector3(nextX, nextY, 1.0f);
    corners[2] = TransformWavyTextPoint(bottomRightPoint);
    bottomLeftPoint = MakeVector3(x, nextY, 1.0f);
    corners[3] = TransformWavyTextPoint(bottomLeftPoint);

    signed char glyph = (signed char)*text;
    SumoF32 u0 = (SumoF32)(glyph & 15) * g_gameBoxDefaultValue;
    SumoF32 v0 = (SumoF32)(glyph / 16) * g_gameBoxDefaultValue;

    EMIT_GAME_TEXT_VERTEX(corners[0] - offset, shadowColor, u0, v0);
    SumoF32 u1;
    EMIT_GAME_TEXT_VERTEX(corners[1] - offset, shadowColor,
                          u1 = u0 + g_gameBoxDefaultValue, v0);
    SumoF32 v1;
    EMIT_GAME_TEXT_VERTEX(corners[3] - offset, shadowColor, u0,
                          v1 = v0 + g_gameBoxDefaultValue);
    EMIT_GAME_TEXT_VERTEX(corners[1] - offset, shadowColor, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[2] - offset, shadowColor, u1, v1);
    EMIT_GAME_TEXT_VERTEX(corners[3] - offset, shadowColor, u0, v1);

    EMIT_GAME_TEXT_VERTEX(corners[0] + offset, shadowColor, u0, v0);
    EMIT_GAME_TEXT_VERTEX(corners[1] + offset, shadowColor, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[3] + offset, shadowColor, u0, v1);
    EMIT_GAME_TEXT_VERTEX(corners[1] + offset, shadowColor, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[2] + offset, shadowColor, u1, v1);
    EMIT_GAME_TEXT_VERTEX(corners[3] + offset, shadowColor, u0, v1);

    EMIT_GAME_TEXT_VERTEX(corners[0], color, u0, v0);
    EMIT_GAME_TEXT_VERTEX(corners[1], color, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[3], color, u0, v1);
    EMIT_GAME_TEXT_VERTEX(corners[1], color, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[2], color, u1, v1);
    EMIT_GAME_TEXT_VERTEX(corners[3], color, u0, v1);

    ++text;
    x = nextX;
    if (*text == '\n') {
      ++text;
      x = initialX;
      y = nextY;
    }
  }
  return text;
}

#undef EMIT_GAME_TEXT_VERTEX

void FlushGameTextVertices() {
  SumoS32 vertexCount =
      (SumoS32)(g_renderVertexCursor - g_renderVertexScratch) / 24;
  if (vertexCount != 0) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, s_streamVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0x250120, NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * 24,
                    g_renderVertexScratch);

    SetGameTexture(0, g_gameFontAtlasTexture);
    glUniform1i(s_uniformMode, c_renderModeText);
    glBindVertexArray(s_streamTextVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, (vertexCount / 3) * 3);
  }
}

extern SumoU8 g_gameBoxLitVertexStorage[0x240000];
extern SumoU8 g_gameBoxShadowPositionStorage[0x120000];
extern SumoU8 g_gameBoxIndexPairStorage[0x20000];
extern SumoU8 g_gameBoxTextureTriangleCounts[0x100];
extern SumoU8 *g_gameBoxLitVertexCursor;
extern SumoU8 *g_gameBoxShadowPositionCursor;
extern SumoU8 *g_gameBoxIndexPairCursor;
extern Vector3 g_gameBoxLightDirection;
extern SumoIntPtr g_gameTextures[256];
extern SumoU8 g_waterFieldActive;
extern SumoU32 g_screenTintColor;
void RenderGameBoxes(SumoS32);

SumoS32 g_gameRenderQualityCode = 12;
SumoS32 g_gameRenderQualityEnabled = 1;
SumoS32 g_waterGridWidth = 128;
SumoS32 g_waterGridHeight = 64;

extern const SumoF32 g_gameLightPassRotationStep = 5.1999998f;

struct GameSceneIndexPair {
  SumoS16 triangleIndex;
  SumoS16 textureIndex;
};

struct GameLineVertex {
  Vector3 position;
  SumoU32 color;
};

DECOMP_SIZE_ASSERT(GameLineVertex, 0x10);

enum {
  c_gameLinePrimitiveBytes = sizeof(GameLineVertex) * 2,
  c_gameLinePrimitiveShift = 5
};

static __forceinline Vector3 MakeGameRenderVector3(SumoF32 p_x, SumoF32 p_y,
                                                   SumoF32 p_z) {
  Vector3 result;
  result.x = p_x;
  result.y = p_y;
  result.z = p_z;
  return result;
}

SumoS16 g_gameBoxTextureTriangleOffsets[128];

extern SumoS16 g_gameBoxTriangleOrder[];

static SumoU8 s_mainVertexStaging[0x240000];

HRESULT RenderGameScene() {
  if (!EnsureRenderObjects())
    return 0;

  glUseProgram(s_program);
  glUniformMatrix4fv(s_uniformView, 1, GL_FALSE, s_viewTransform);
  glUniformMatrix4fv(s_uniformProjection, 1, GL_FALSE, s_projectionTransform);
  glViewport(0, 0, g_gameRenderWidth, g_gameRenderHeight);

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);
  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  g_gameViewMatrix = g_gameInverseViewMatrix;
  g_gameViewOffset = g_gameCameraWorldPosition;
  ApplyGameViewTransform();

  SumoU32 clearColor =
      (0x80c1u * (((SumoS32)g_screenTintColor >> 2) & 0x3f)) & 0x003f3f3f;
  glDisable(GL_SCISSOR_TEST);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glStencilMask(0xffu);
  glClearColor((SumoF32)((clearColor >> 16) & 0xff) / 255.0f,
               (SumoF32)((clearColor >> 8) & 0xff) / 255.0f,
               (SumoF32)(clearColor & 0xff) / 255.0f, 1.0f);
  glClearDepth(1.0);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  bool firstLightPass = true;
  SumoS32 passCount = g_gameRenderQualityCode;
  SumoS32 pass = 0;
  SumoS16 *triangleCounts = (SumoS16 *)g_gameBoxTextureTriangleCounts;
  if (passCount > 0) {
    do {
      g_gameBoxLightDirection = MakeGameRenderVector3(0.30000001f, 1.0f, 0.5f);
      Vector3 lightRotation = MakeGameRenderVector3(
          0.0f,
          (SumoF32)pass * g_gameLightPassRotationStep / (SumoF32)passCount,
          0.0f);
      SumoU32 textureFactor = 526086u * ((288 / (passCount + 1) + 8) / 16);
      g_gameBoxLightDirection.Rotate(lightRotation);
      g_gameBoxLightDirection.Normalize();

      SumoU32 *triangleCountWords = (SumoU32 *)triangleCounts;
      for (SumoS32 word = 0; word < 64; ++word)
        triangleCountWords[word] = 0;
      g_gameBoxIndexPairCursor = g_gameBoxIndexPairStorage;
      g_gameBoxLitVertexCursor = g_gameBoxLitVertexStorage;
      g_gameBoxShadowPositionCursor = g_gameBoxShadowPositionStorage;
      RenderGameBoxes(0);

      SumoS32 shadowTriangleCount =
          (SumoS32)((Vector3 *)g_gameBoxShadowPositionCursor -
                    (Vector3 *)g_gameBoxShadowPositionStorage) /
          3;
      glBindBuffer(GL_ARRAY_BUFFER, s_positionVertexBuffer);
      glBufferData(GL_ARRAY_BUFFER, 0x120000, NULL, GL_STREAM_DRAW);
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      shadowTriangleCount * 3 * (SumoS32)sizeof(Vector3),
                      g_gameBoxShadowPositionStorage);

      SumoS32 triangleCount = 0;
      for (SumoS32 texture = 0; texture < 128; ++texture) {
        g_gameBoxTextureTriangleOffsets[texture] = (SumoS16)triangleCount;
        triangleCount += triangleCounts[texture];
      }

      GameSceneIndexPair *pair =
          (GameSceneIndexPair *)g_gameBoxIndexPairStorage;
      SumoS32 emittedTriangleCount = 0;
      if ((SumoU8 *)pair < g_gameBoxIndexPairCursor) {
        do {
          g_gameBoxTriangleOrder
              [g_gameBoxTextureTriangleOffsets[pair->textureIndex] +
               pair->triangleIndex] = (SumoS16)emittedTriangleCount;
          ++emittedTriangleCount;
          ++pair;
        } while ((SumoU8 *)pair < g_gameBoxIndexPairCursor);
      }

      GameTextVertex *lockedVertices = (GameTextVertex *)s_mainVertexStaging;
      GameTextVertex *sourceVertices =
          (GameTextVertex *)g_gameBoxLitVertexStorage;
      for (SumoS32 triangle = 0; triangle < emittedTriangleCount; ++triangle) {
        *lockedVertices++ =
            sourceVertices[g_gameBoxTriangleOrder[triangle] * 3];
        *lockedVertices++ =
            sourceVertices[g_gameBoxTriangleOrder[triangle] * 3 + 1];
        *lockedVertices++ =
            sourceVertices[g_gameBoxTriangleOrder[triangle] * 3 + 2];
      }
      glBindBuffer(GL_ARRAY_BUFFER, s_mainVertexBuffer);
      glBufferData(GL_ARRAY_BUFFER, 0x240000, NULL, GL_STREAM_DRAW);
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      emittedTriangleCount * 3 *
                          (SumoS32)sizeof(GameTextVertex),
                      s_mainVertexStaging);
      glBindVertexArray(s_mainVertexArray);

      if (g_gameRenderQualityEnabled) {
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 8, 0xffu);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
      }
      if (firstLightPass) {
        SetRenderFactor(0x00203040);
      } else {
        SetRenderFactor(0);
        glDepthMask(GL_FALSE);
      }
      glUniform1i(s_uniformMode, c_renderModeFlat);
      if (g_gameRenderQualityEnabled || firstLightPass) {
        glDrawArrays(GL_TRIANGLES, 0, triangleCount * 3);
      }

      glDepthMask(GL_FALSE);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
      glEnable(GL_STENCIL_TEST);
      glStencilFunc(GL_ALWAYS, 8, 0xffu);
      glStencilOp(GL_INCR_WRAP, GL_KEEP, GL_INCR_WRAP);
      if (g_gameRenderQualityEnabled) {
        glBindVertexArray(s_positionVertexArray);
        glCullFace(GL_FRONT);
        glDrawArrays(GL_TRIANGLES, 0, shadowTriangleCount * 3);
        glCullFace(GL_BACK);
        glStencilOp(GL_DECR_WRAP, GL_KEEP, GL_DECR_WRAP);
        glDrawArrays(GL_TRIANGLES, 0, shadowTriangleCount * 3);
      }
      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

      if (firstLightPass) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        firstLightPass = false;
      }
      glBindVertexArray(s_mainVertexArray);
      if (g_gameRenderQualityEnabled) {
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_GEQUAL, 8, 0xffu);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
      }
      glUniform1i(s_uniformMode, c_renderModeDot3);
      SetRenderFactor(textureFactor);
      for (SumoS32 texture = 0; texture < 128; ++texture) {
        if (triangleCounts[texture] != 0) {
          SetGameTexture(0, g_gameTextures[texture * 2]);
          glDrawArrays(GL_TRIANGLES,
                       3 * g_gameBoxTextureTriangleOffsets[texture],
                       triangleCounts[texture] * 3);
        }
      }
      glDepthMask(GL_TRUE);
      glDisable(GL_STENCIL_TEST);
    } while (++pass < passCount);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
  glUniform1i(s_uniformMode, c_renderModeAlbedo);
  SetRenderFactor(g_screenTintColor);
  glBindVertexArray(s_mainVertexArray);
  for (SumoS32 texture = 0; texture < 128; ++texture) {
    if (triangleCounts[texture] != 0) {
      SumoIntPtr albedo = g_gameTextures[texture * 2 + 1];
      if (albedo == 0)
        albedo = (SumoIntPtr)UndefinedMaterialTexture(texture);
      SetGameTexture(0, albedo);
      glDrawArrays(GL_TRIANGLES, 3 * g_gameBoxTextureTriangleOffsets[texture],
                   triangleCounts[texture] * 3);
    }
  }

  if (g_waterFieldActive)
    RenderWaterSurface();
  FlushGameTextVertices();
  if ((SumoS32)(g_gameLineVertexCursor - g_gameLineVertexScratch) &
      -c_gameLinePrimitiveBytes) {
    SumoS32 lineVertexCount =
        ((SumoS32)(g_gameLineVertexCursor - g_gameLineVertexScratch) >>
         c_gameLinePrimitiveShift) *
        2;
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glBindBuffer(GL_ARRAY_BUFFER, s_streamVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0x250120, NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, lineVertexCount * 16,
                    g_gameLineVertexScratch);
    glUniform1i(s_uniformMode, c_renderModeLine);
    glBindVertexArray(s_streamLineVertexArray);
    glDrawArrays(GL_LINES, 0, lineVertexCount);
  }

  glBindVertexArray(0);
  glEnable(GL_DEPTH_TEST);
  SumoOverlayDraw();
  SumoRenderPresent();
  return 0;
}

static SumoU8 *s_waterVertexScratch;
static SumoS32 s_waterVertexCapacity;

SumoU8 *BeginGameWaterVertices(SumoS32 byteCount) {
  if (!SumoRenderContextReady() || byteCount <= 0)
    return NULL;
  if (byteCount > 0x250120)
    return NULL;
  if (byteCount > s_waterVertexCapacity) {
    delete[] s_waterVertexScratch;
    s_waterVertexScratch = new SumoU8[(size_t)byteCount];
    s_waterVertexCapacity = byteCount;
  }
  return s_waterVertexScratch;
}

void FinishGameWaterVertices(SumoS32 triangleCount) {
  if (triangleCount <= 0 || s_waterVertexScratch == NULL)
    return;
  glBindBuffer(GL_ARRAY_BUFFER, s_streamVertexBuffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)triangleCount * 3 * 24,
                  s_waterVertexScratch);
  glBindVertexArray(s_streamTextVertexArray);
  glUniform1i(s_uniformMode, c_renderModeFlat);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
  glDisable(GL_CULL_FACE);
  glDrawArrays(GL_TRIANGLES, 0, triangleCount * 3);
  glEnable(GL_CULL_FACE);
}

SumoS32 SaveGameScreenshot(char *p_prefix, SumoS32 p_index) {
  g_gameScreenshotIndex = p_index;
  g_gameScreenshotPrefix = p_prefix;
  return WriteGameScreenshot();
}

void __stdcall IgnoreGameTextureProgress(SumoF32) {}

SumoIntPtr CreateGameTextureFromPixels(void *p_pixels, SumoS32 p_width,
                                       SumoS32 p_height,
                                       SumoS32 p_singleLevel) {
  GLuint texture = 0;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, p_width, p_height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, p_pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_BLUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (p_singleLevel) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  } else {
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
  }
  return (SumoIntPtr)texture;
}

static GLuint s_whiteTexture;

static GLuint WhiteTexture() {
  if (s_whiteTexture == 0) {
    const SumoU8 white[4] = {0xff, 0xff, 0xff, 0xff};
    glGenTextures(1, &s_whiteTexture);
    glBindTexture(GL_TEXTURE_2D, s_whiteTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, white);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  return s_whiteTexture;
}

enum { c_undefinedMaterialSize = 32, c_undefinedMaterialSlots = 128 };

static GLuint s_undefinedMaterial[c_undefinedMaterialSlots];

static SumoU32 UndefinedMaterialHash(SumoU32 seed) {
  seed ^= seed >> 16;
  seed *= 0x7feb352du;
  seed ^= seed >> 15;
  seed *= 0x846ca68bu;
  seed ^= seed >> 16;
  return seed;
}

static GLuint UndefinedMaterialTexture(SumoS32 slot) {
  if (slot < 0 || slot >= c_undefinedMaterialSlots)
    return WhiteTexture();
  if (s_undefinedMaterial[slot] != 0)
    return s_undefinedMaterial[slot];

  SumoU32 first = UndefinedMaterialHash((SumoU32)slot * 2u + 1u);
  SumoU32 second = UndefinedMaterialHash(first);
  SumoU8 fromColor[3];
  SumoU8 toColor[3];
  for (SumoS32 channel = 0; channel < 3; ++channel) {
    fromColor[channel] = (SumoU8)(0x40 + ((first >> (channel * 8)) & 0xbf));
    toColor[channel] = (SumoU8)(0x40 + ((second >> (channel * 8)) & 0xbf));
  }

  SumoU8 pixels[c_undefinedMaterialSize * c_undefinedMaterialSize * 4];
  SumoU8 *cursor = pixels;
  for (SumoS32 y = 0; y < c_undefinedMaterialSize; ++y) {
    for (SumoS32 x = 0; x < c_undefinedMaterialSize; ++x) {
      SumoS32 shade = (x + y) * 255 / (2 * (c_undefinedMaterialSize - 1));
      for (SumoS32 channel = 0; channel < 3; ++channel) {
        cursor[channel] =
            (SumoU8)((fromColor[channel] * (255 - shade) +
                      toColor[channel] * shade) / 255);
      }
      cursor[3] = 0xff;
      cursor += 4;
    }
  }

  GLuint texture = 0;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, c_undefinedMaterialSize,
               c_undefinedMaterialSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  s_undefinedMaterial[slot] = texture;
  return texture;
}

HRESULT SetGameTexture(SumoU32 stage, SumoIntPtr texture) {
  glActiveTexture(GL_TEXTURE0 + stage);
  glBindTexture(GL_TEXTURE_2D,
                texture != 0 ? (GLuint)texture : WhiteTexture());
  glActiveTexture(GL_TEXTURE0);
  return 0;
}
