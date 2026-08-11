#include "boundary.h"

extern SumoU8 g_gameKeyDown[256];
extern SumoU8 g_gameKeyPressed[256];
extern SumoS32 g_gameMouseX;
extern SumoS32 g_gameMouseY;
extern SumoS32 g_gamePrimaryInputPressed;

static SDL_Window *s_window;
static bool s_quitRequested;

bool SumoPlatformCreateWindow(SumoS32 width, SumoS32 height, bool fullscreen) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return false;
  }
  SumoS32 desktopWidth = 0;
  SumoS32 desktopHeight = 0;
  const SDL_DisplayMode *desktop =
      SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay());
  if (desktop != NULL) {
    desktopWidth = desktop->w;
    desktopHeight = desktop->h;
  }
  SumoResolveWindowSize(width, height, desktopWidth, desktopHeight, &width,
                        &height);

  SumoRenderRequestGLAttributes();
  s_window = SDL_CreateWindow("Sumotori", width, height,
                              SDL_WINDOW_OPENGL |
                                  (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
  if (s_window == NULL)
    return false;
  SumoApplyWindowIcon(s_window);
  return true;
}

void SumoApplyWindowIcon(SDL_Window *window) {
  SumoIconImage image;
  if (!SumoLoadWindowIcon(&image))
    return;
  SDL_Surface *surface =
      SDL_CreateSurfaceFrom(image.width, image.height, SDL_PIXELFORMAT_RGBA32,
                            image.pixels, image.width * 4);
  if (surface != NULL) {
    SDL_SetWindowIcon(window, surface);
    SDL_DestroySurface(surface);
  }
  SumoFreeIcon(&image);
}

void SumoPlatformDestroyWindow() {
  if (s_window != NULL) {
    SDL_DestroyWindow(s_window);
    s_window = NULL;
  }
}

SDL_Window *SumoPlatformWindow() { return s_window; }

bool SumoPlatformQuitRequested() { return s_quitRequested; }

static void HandleLeftMouseDownDrawable(SumoS32 x, SumoS32 y) {
  int logicalWidth = 0;
  int logicalHeight = 0;
  int drawableWidth = 0;
  int drawableHeight = 0;
  SDL_GetWindowSize(s_window, &logicalWidth, &logicalHeight);
  SDL_GetWindowSizeInPixels(s_window, &drawableWidth, &drawableHeight);
  if (logicalWidth > 0 && logicalHeight > 0 && drawableWidth > 0 &&
      drawableHeight > 0) {
    x = x * drawableWidth / logicalWidth;
    y = y * drawableHeight / logicalHeight;
  }
  SumoHandleLeftMouseDown(x, y);
}

void PumpGameMessages() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    SumoOverlayProcessEvent(&event);
    switch (event.type) {
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
      SumoRenderUpdateTargetSize();
      break;
    case SDL_EVENT_QUIT: s_quitRequested = true; break;
    case SDL_EVENT_KEY_DOWN:
      if (!SumoOverlayWantCaptureKeyboard())
        SumoHandleKeyDown((SumoS32)event.key.scancode);
      break;
    case SDL_EVENT_KEY_UP:
      if (!SumoOverlayWantCaptureKeyboard())
        SumoHandleKeyUp((SumoS32)event.key.scancode);
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (event.button.button == SDL_BUTTON_LEFT &&
          !SumoOverlayWantCaptureMouse()) {
        HandleLeftMouseDownDrawable((SumoS32)event.button.x,
                                    (SumoS32)event.button.y);
      }
      break;
    default: break;
    }
  }
}
