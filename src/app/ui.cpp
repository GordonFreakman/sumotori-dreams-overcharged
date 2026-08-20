#include "boundary.h"

#define IM_ASSERT(_EXPR) SDL_assert(_EXPR)
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#if SUMO_SDL_VERSION == 3
#include <imgui_impl_sdl3.h>
#else
#include <imgui_impl_sdl2.h>
#endif

static bool s_imguiReady;

static bool AnyPanelActive() {
  return SumoEditorActive() || SumoModPickerActive();
}

void StyleColorsSumo(ImGuiStyle *dst) {
  ImGuiStyle *style = dst ? dst : &ImGui::GetStyle();
  ImVec4 *colors = style->Colors;

  colors[ImGuiCol_Text] = ImVec4(0.5f, 0.5f, 0.76f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.08f, 1.0f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.25f, 0.33f, 0.41f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.26f, 0.44f, 0.78f, 0.5f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.76f, 0.76f, 0.5f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
  colors[ImGuiCol_TitleBgActive] =
      ImVec4(0.38f / 2, 0.38f / 2, 0.76f / 2, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_CheckboxSelectedBg] =
      ImLerp(colors[ImGuiCol_FrameBg], colors[ImGuiCol_FrameBgHovered], 0.65f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.23f, 0.39f, 0.56f, 0.75f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.52f, 0.73f, 0.75f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 0.25f);
  colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_InputTextCursor] = colors[ImGuiCol_Text];
  colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
  colors[ImGuiCol_Tab] =
      ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
  colors[ImGuiCol_TabSelected] = ImLerp(colors[ImGuiCol_HeaderActive],
                                        colors[ImGuiCol_TitleBgActive], 0.60f);
  colors[ImGuiCol_TabSelectedOverline] = colors[ImGuiCol_HeaderActive];
  colors[ImGuiCol_TabDimmed] =
      ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
  colors[ImGuiCol_TabDimmedSelected] =
      ImLerp(colors[ImGuiCol_TabSelected], colors[ImGuiCol_TitleBg], 0.40f);
  colors[ImGuiCol_TabDimmedSelectedOverline] =
      ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
  colors[ImGuiCol_TableBorderStrong] =
      ImVec4(0.31f, 0.31f, 0.35f, 1.00f); // Prefer using Alpha=1.0 here
  colors[ImGuiCol_TableBorderLight] =
      ImVec4(0.23f, 0.23f, 0.25f, 1.00f); // Prefer using Alpha=1.0 here
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextLink] = colors[ImGuiCol_HeaderActive];
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors[ImGuiCol_TreeLines] = colors[ImGuiCol_Border];
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_DragDropTargetBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_UnsavedMarker] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_NavCursor] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

 float proportionalScale = 1.f;

static void EnsureImGui() {
  if (s_imguiReady)
    return;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  StyleColorsSumo(NULL);
 
  SDL_Window *window = SumoPlatformWindow();
  if (window != NULL) {
    int width = 0;
    int height = 0;
#if SUMO_SDL_VERSION == 3
    SDL_GetWindowSizeInPixels(window, &width, &height);
#else
    SDL_GL_GetDrawableSize(window, &width, &height);
#endif
    proportionalScale = height / 720.f;
    ImGui::GetStyle().FontScaleMain = proportionalScale;
    ImGui::GetStyle().ScaleAllSizes(proportionalScale);
  }
#if SUMO_SDL_VERSION == 3
  ImGui_ImplSDL3_InitForOpenGL(SumoPlatformWindow(),
                               SDL_GL_GetCurrentContext());
#else
  ImGui_ImplSDL2_InitForOpenGL(SumoPlatformWindow(),
                               SDL_GL_GetCurrentContext());
#endif
  ImGui_ImplOpenGL3_Init("#version 330 core");
  s_imguiReady = true;
}

void SumoOverlayProcessEvent(void *sdlEvent) {
  if (!s_imguiReady || !AnyPanelActive())
    return;
#if SUMO_SDL_VERSION == 3
  ImGui_ImplSDL3_ProcessEvent((const SDL_Event *)sdlEvent);
#else
  ImGui_ImplSDL2_ProcessEvent((const SDL_Event *)sdlEvent);
#endif
}

bool SumoOverlayWantCaptureKeyboard() {
  return s_imguiReady && AnyPanelActive() && ImGui::GetIO().WantCaptureKeyboard;
}

bool SumoOverlayWantCaptureMouse() {
  return s_imguiReady && AnyPanelActive() && ImGui::GetIO().WantCaptureMouse;
}

void SumoOverlayDraw() {
  if (!AnyPanelActive())
    return;
  EnsureImGui();

  ImGui_ImplOpenGL3_NewFrame();
#if SUMO_SDL_VERSION == 3
  ImGui_ImplSDL3_NewFrame();
#else
  ImGui_ImplSDL2_NewFrame();
#endif
  ImGui::NewFrame();

  if (SumoEditorActive())
    SumoEditorDrawPanel();
  if (SumoModPickerActive())
    SumoModPickerDrawPanel();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#include "boundary.h"

#include <glad/gl.h>

#define IM_ASSERT(_EXPR) SDL_assert(_EXPR)
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#if SUMO_SDL_VERSION == 3
#include <imgui_impl_sdl3.h>
#else
#include <imgui_impl_sdl2.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SumoU8 g_gameAudioEnabled;
extern float g_gameRenderQualityCode;

static const float c_qualityCodes[5] = {0.25, 0.5, 1, 1.5, 2};
static const char *c_qualityLabels[5] = {
    "LOW (25%)", "MEDIUM (50%)", "HIGH (100%)",
    "ULTRA (150%)", "OVERCHARGED (200%)"};

static const char *c_audioBackendLabels[2] = {"SDL", "miniaudio"};

static char *SettingsPath() {
  static char path[1024];
  if (path[0] == 0) {
    char *pref = SDL_GetPrefPath("Archee", "SumotoriOvercharged");
    SDL_snprintf(path, sizeof(path), "%ssettings.ini", pref ? pref : "");
#if SUMO_SDL_VERSION == 2
    SDL_free(pref);
#endif
  }
  return path;
}

void SumoLoadStartupConfig(SumoStartupConfig *config) {
  config->width = 1024;
  config->height = 768;
  config->fullscreen = false;
  config->quality = 1;
  config->soundEnabled = true;
  config->audioBackend = SumoAudioGetBackend();
  config->editorRequested = false;
  config->modPath[0] = '\0';

  FILE *stream = fopen(SettingsPath(), "r");
  if (stream == NULL)
    return;
  char line[128];
  while (fgets(line, sizeof(line), stream) != NULL) {
    int value = 0;
    if (sscanf(line, "width=%d", &value) == 1)
      config->width = value;
    else if (sscanf(line, "height=%d", &value) == 1)
      config->height = value;
    else if (sscanf(line, "fullscreen=%d", &value) == 1)
      config->fullscreen = value != 0;
    else if (sscanf(line, "quality=%d", &value) == 1)
      config->quality = value;
    else if (sscanf(line, "sound=%d", &value) == 1)
      config->soundEnabled = value != 0;
    else if (sscanf(line, "audio=%d", &value) == 1)
      config->audioBackend = value == c_sumoAudioBackendMiniaudio
                                 ? c_sumoAudioBackendMiniaudio
                                 : c_sumoAudioBackendSdl;
  }
  fclose(stream);
}

void SumoSaveStartupConfig(const SumoStartupConfig *config) {
  FILE *stream = fopen(SettingsPath(), "w");
  if (stream == NULL)
    return;
  fprintf(stream,
          "width=%d\nheight=%d\nfullscreen=%d\nquality=%d\nsound=%d\n"
          "audio=%d\n",
          config->width, config->height, config->fullscreen ? 1 : 0,
          config->quality, config->soundEnabled ? 1 : 0,
          (int)config->audioBackend);
  fclose(stream);
}

struct SumoDisplayMode {
  int width;
  int height;
};

static SumoDisplayMode s_modes[64];
static char s_modeLabels[64][32];
static const char *s_modeLabelPointers[64];
static int s_modeCount;

static void AddDisplayMode(int width, int height) {
  if (s_modeCount >= 64 || width <= 0 || height <= 0)
    return;
  for (int index = 0; index < s_modeCount; ++index) {
    if (s_modes[index].width == width && s_modes[index].height == height)
      return;
  }
  s_modes[s_modeCount].width = width;
  s_modes[s_modeCount].height = height;
  SDL_snprintf(s_modeLabels[s_modeCount], sizeof(s_modeLabels[0]), "%dx%d",
               width, height);
  s_modeLabelPointers[s_modeCount] = s_modeLabels[s_modeCount];
  ++s_modeCount;
}

static void CollectDisplayModes() {
  if (s_modeCount != 0)
    return;
  s_modes[0].width = 0;
  s_modes[0].height = 0;
  SDL_snprintf(s_modeLabels[0], sizeof(s_modeLabels[0]), "Desktop resolution");
  s_modeLabelPointers[0] = s_modeLabels[0];
  s_modeCount = 1;

#if SUMO_SDL_VERSION == 3
  SDL_DisplayID display = SDL_GetPrimaryDisplay();
  int count = 0;
  SDL_DisplayMode **modes = SDL_GetFullscreenDisplayModes(display, &count);
  if (modes != NULL) {
    for (int index = 0; index < count; ++index)
      AddDisplayMode(modes[index]->w, modes[index]->h);
    SDL_free(modes);
  }
#else
  int count = SDL_GetNumDisplayModes(0);
  for (int index = 0; index < count; ++index) {
    SDL_DisplayMode mode;
    if (SDL_GetDisplayMode(0, index, &mode) == 0)
      AddDisplayMode(mode.w, mode.h);
  }
#endif
}

static void ApplyWindowFullscreen(bool fullscreen) {
#if SUMO_SDL_VERSION == 3
  SDL_SetWindowFullscreen(SumoPlatformWindow(), fullscreen);
#else
  SDL_SetWindowFullscreen(SumoPlatformWindow(),
                          fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
#endif
}

bool SumoRunStartupUI(SumoStartupConfig *config) 
{
  EnsureImGui();

  int qualityIndex = config->quality;
  bool sound = config->soundEnabled;
  bool audioIndex = config->audioBackend == c_sumoAudioBackendMiniaudio ? 1 : 0;
  bool fullscreen = config->fullscreen;
  bool appliedFullscreen = fullscreen;
  CollectDisplayModes();
  int modeIndex = 0;
  for (int index = 0; index < s_modeCount; ++index) {
    if (s_modes[index].width == config->width &&
        s_modes[index].height == config->height)
      modeIndex = index;
  }
  int result = 0;

  while (result == 0) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
#if SUMO_SDL_VERSION == 3
      ImGui_ImplSDL3_ProcessEvent(&event);
      if (event.type == SDL_EVENT_QUIT)
        result = -1;
#else
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        result = -1;
#endif
    }

#if SUMO_SDL_VERSION == 3
    ImGui_ImplSDL3_NewFrame();
#else
    ImGui_ImplSDL2_NewFrame();
#endif
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Always,
                            ImVec2(0.5f, 0.5f));
    ImGui::Begin("Sumotori Dreams: Overcharged", NULL,
                 ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    ImGui::Combo("Shadow mode", &qualityIndex, c_qualityLabels, 5);
    ImGui::Combo("Display mode", &modeIndex, s_modeLabelPointers, s_modeCount);
    ImGui::Checkbox("Sound", &sound);
    ImGui::Checkbox("Sound randomization", &audioIndex);
    ImGui::Checkbox("Fullscreen", &fullscreen);
    if (fullscreen != appliedFullscreen) {
      ApplyWindowFullscreen(fullscreen);
      appliedFullscreen = fullscreen;
    }

    ImGui::Separator();
    if (ImGui::Button("PLAY GAME", ImVec2(160 * proportionalScale, 0)))
      result = 1;
    ImGui::SameLine();
    if (ImGui::Button("QUIT", ImVec2(160 * proportionalScale, 0)))
      result = -1;
    if (ImGui::Button("LEVEL EDITOR", ImVec2(160 * proportionalScale, 0))) {
      config->editorRequested = true;
      result = 1;
    }
    ImGui::SameLine();
    if (ImGui::Button("PLAY MOD", ImVec2(160 * proportionalScale, 0)))
      ImGui::OpenPopup("Play Mod");
    if (ImGui::BeginPopupModal("Play Mod", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
      static char modPath[1024];
      ImGui::TextUnformatted("Path to a .smo level script:");
      ImGui::SetNextItemWidth(420.0f * proportionalScale);
      ImGui::InputText("##modpath", modPath, sizeof(modPath));
      if (ImGui::Button("LOAD", ImVec2(120, 0)) && modPath[0] != '\0') {
        SDL_snprintf(config->modPath, sizeof(config->modPath), "%s", modPath);
        result = 1;
        ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine();
      if (ImGui::Button("CANCEL", ImVec2(120 * proportionalScale, 0)))
        ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
    ImGui::End();

    ImGui::Render();
    int drawableWidth = 0;
    int drawableHeight = 0;
#if SUMO_SDL_VERSION == 3
    SDL_GetWindowSizeInPixels(SumoPlatformWindow(), &drawableWidth,
                              &drawableHeight);
#else
    SDL_GL_GetDrawableSize(SumoPlatformWindow(), &drawableWidth,
                           &drawableHeight);
#endif
    glViewport(0, 0, drawableWidth, drawableHeight);
    glClearColor(0.12f, 0.12f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SumoRenderPresent();
  }


  config->quality = qualityIndex;
  config->soundEnabled = sound;
  config->audioBackend = audioIndex;
  config->fullscreen = fullscreen;
  config->width = s_modes[modeIndex].width;
  config->height = s_modes[modeIndex].height;
  SumoSaveStartupConfig(config);

  if (result == 1 && s_modes[modeIndex].width > 0) {
    SDL_SetWindowSize(SumoPlatformWindow(), s_modes[modeIndex].width,
                      s_modes[modeIndex].height);
    if (fullscreen)
      ApplyWindowFullscreen(true);
  }

  g_gameAudioEnabled = sound ? 1 : 0;
  SumoAudioSetBackend((SumoAudioBackend)config->audioBackend);
  ApplyGameQuality(config->quality);
  return result == 1;
}

#include "boundary.h"

#include "sumo_portable.h"

#define IM_ASSERT(_EXPR) SDL_assert(_EXPR)
#include <imgui.h>
#include <imgui_stdlib.h>

#include <stdio.h>
#include <string>

#include "decomp_keywords.h"

#include "containers.h"
#ifdef SUMO_REPLAY
void ReplayWriteBoundary();
#endif
void InitializeGameParser();
void SetGameCursorVisible(SumoU8 visible);
void RestartGameMusic(SumoS32 playbackMode);
void ResetAndSetSceneTransform(Vector3 &position, SumoF32 angle);
Vector3 *ResetGameRoundState();
void LoadGameLevel(char *source);

extern const char g_gameLevelEditedFilename[];
extern char *g_externalLevelScriptOverride;

struct SumoPortableWindow {
  int unused;
};

static SumoPortableWindow s_editControlSentinel;
static SumoPortableWindow s_statusWindowSentinel;

// GLOBAL: retail 0x00c06008
SumoF32 g_gameArenaExtent;

// GLOBAL: retail 0x005115fc
SumoS32 g_gameEditorControlMode;

// GLOBAL: retail 0x00467348
HWND g_gameLevelEditorEditControl = &s_editControlSentinel;

// GLOBAL: retail 0x004e73d4
HWND g_gameLevelEditorStatusWindow = &s_statusWindowSentinel;

// GLOBAL: retail 0x00d0f1fc
SumoS32 g_gameLevelEditorCloseRequested;

static bool s_editorActive;
static std::string s_document;
static std::string s_editorStatus;

// FUNCTION: retail 0x00406c37
void StartGameLevelEditor(char *source) {
    #ifdef SUMO_REPLAY
  ReplayWriteBoundary();
  #endif
  g_gameArenaExtent = 150.0f;
  InitializeGameParser();
  SetGameCursorVisible(1);
  //RestartGameMusic(6);

  Vector3 position;
  position.x = 60.0f;
  position.y = 35.0f;
  position.z = -97.0f;
  ResetAndSetSceneTransform(position, 0.0f);
  ResetGameRoundState();
  g_gameEditorControlMode = 4;
  LoadGameLevel(source);
}

SumoS32 GetWindowText(HWND window, char *buffer, SumoS32 capacity) {
  if (buffer == NULL || capacity <= 0)
    return 0;
  if (window != g_gameLevelEditorEditControl) {
    buffer[0] = '\0';
    return 0;
  }
  SumoS32 length = (SumoS32)s_document.size();
  if (length > capacity - 1)
    length = capacity - 1;
  memcpy(buffer, s_document.data(), (size_t)length);
  buffer[length] = '\0';
  return length;
}

SumoS32 SetWindowText(HWND window, const char *text) {
  if (window == g_gameLevelEditorStatusWindow && text != NULL)
    s_editorStatus = text;
  return 1;
}

void SumoEditorEnter() {
  if (s_editorActive)
    return;
  s_editorActive = true;
  s_editorStatus = "Sumotori Dreams level editor";
  if (g_externalLevelScriptOverride != NULL &&
      g_externalLevelScriptOverride[0] != '\0') {
    s_document = g_externalLevelScriptOverride;
    return;
  }
  FILE *stream = fopen(g_gameLevelEditedFilename, "rb");
  if (stream != NULL) {
    std::string buffer(0x7ffff, '\0');
    size_t size = fread(&buffer[0], 1, buffer.size(), stream);
    fclose(stream);
    buffer.resize(size);
    s_document = buffer;
    if (!s_document.empty())
      return;
  }
  SumoAssetBlob blob;
  if (SumoAssetOpen("levels/editor_default.smo", &blob)) {
    s_document.assign((const char *)blob.data, blob.size);
    SumoAssetClose(&blob);
  }
}

bool SumoEditorActive() { return s_editorActive; }

void SumoEditorDrawPanel() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(
      ImVec2(io.DisplaySize.x * 0.42f, io.DisplaySize.y * 0.6f),
      ImGuiCond_FirstUseEver);
  if (ImGui::Begin("Level Editor", NULL, ImGuiWindowFlags_NoCollapse)) {
    ImGui::TextWrapped("%s", s_editorStatus.c_str());
    ImGui::Separator();
    ImVec2 available = ImGui::GetContentRegionAvail();
    available.y -= ImGui::GetFrameHeightWithSpacing();
    if (ImGui::InputTextMultiline("##script", &s_document, available,
                                  ImGuiInputTextFlags_AllowTabInput))
      LoadGameLevel(0);
    if (ImGui::Button("CLOSE EDITOR"))
      g_gameLevelEditorCloseRequested = 1;
    ImGui::SameLine();
    ImGui::TextDisabled("edits autosave to %s", g_gameLevelEditedFilename);
  }
  ImGui::End();
}

void SumoEditorSetDocument(const char *text) {
  s_document = text != NULL ? text : "";
}

const char *SumoEditorStatus() { return s_editorStatus.c_str(); }

#include "boundary.h"

SumoU8 g_gameAudioEnabled = 1;

extern float g_gameRenderQualityCode;
extern SumoS32 g_gameRenderQualityEnabled;

void ApplyGameQuality(int qualityCode) {
  g_gameRenderQualityCode = c_qualityCodes[qualityCode];
 // g_gameRenderQualityEnabled = qualityCode != 1;
}

SumoS32 CheckStoredGameSettings() { return 1; }
