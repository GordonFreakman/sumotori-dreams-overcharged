#include "types.h"

#define Direct3DCreate9 Direct3DCreate9Stdcall
#include <d3d9.h>
#undef Direct3DCreate9
#include <windows.h>

extern IDirect3D9 *g_gameD3D;
extern IDirect3DDevice9 *g_gameD3DDevice;
extern void *g_gameDeviceResource;
extern D3DCAPS9 g_gameDeviceCaps;
extern SumoS32 g_gameConfiguredWidth;
extern SumoS32 g_gameConfiguredHeight;
extern SumoU8 g_gameUseDesktopSize;
extern SumoF32 g_gameAspectRatio;
extern HWND g_gameWindow;

extern "C" IDirect3D9 *__cdecl Direct3DCreate9(UINT p_sdkVersion);

typedef IDirect3D9 *(__stdcall *GameDirect3DCreate9Proc)(UINT p_sdkVersion);

// FUNCTION: SUMO 0x00403c36
// FUNCTION: EDITOR 0x00403c36
SumoS32 InitializeGameD3DDevice() {
  g_gameD3D = ((GameDirect3DCreate9Proc)Direct3DCreate9)(D3D_SDK_VERSION);

  HWND desktopWindow = GetDesktopWindow();
  HDC desktopDc = GetWindowDC(desktopWindow);
  if (g_gameConfiguredWidth * g_gameConfiguredHeight == 0) {
    g_gameConfiguredWidth = GetDeviceCaps(desktopDc, HORZRES);
    g_gameConfiguredHeight = GetDeviceCaps(desktopDc, VERTRES);
  }

  g_gameAspectRatio = (SumoF32)g_gameConfiguredWidth / g_gameConfiguredHeight;
  ReleaseDC(desktopWindow, desktopDc);

  D3DPRESENT_PARAMETERS parameters;
  parameters.BackBufferWidth = g_gameConfiguredWidth;
  parameters.BackBufferHeight = g_gameConfiguredHeight;
  parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
  parameters.BackBufferCount = 1;
  parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
  parameters.MultiSampleQuality = 0;
  parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  parameters.hDeviceWindow = g_gameWindow;
  parameters.Windowed = FALSE;
  parameters.EnableAutoDepthStencil = TRUE;
  parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
  parameters.Flags = 0;
  parameters.FullScreen_RefreshRateInHz = 0;
  parameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

  g_gameD3DDevice = NULL;
  if (!g_gameUseDesktopSize) {
    g_gameD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_gameWindow,
                            D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters,
                            &g_gameD3DDevice);
    if (g_gameD3DDevice == NULL) {
      g_gameD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_gameWindow,
                              D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters,
                              &g_gameD3DDevice);
    }
  }

  if (g_gameD3DDevice == NULL) {
    ShowWindow(g_gameWindow, SW_SHOWNORMAL);
    g_gameAspectRatio = 1.3333f;
    parameters.FullScreen_RefreshRateInHz = 0;
    parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    parameters.Windowed = TRUE;

    D3DDISPLAYMODE displayMode;
    g_gameD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
    parameters.BackBufferFormat = displayMode.Format;
  }

  if (g_gameD3DDevice == NULL) {
    g_gameD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_gameWindow,
                            D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters,
                            &g_gameD3DDevice);
  }
  if (g_gameD3DDevice == NULL) {
    g_gameD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_gameWindow,
                            D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters,
                            &g_gameD3DDevice);
  }

  g_gameD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
                                 (IDirect3DSurface9 **)&g_gameDeviceResource);

  D3DVIEWPORT9 viewport;
  viewport.X = 0;
  viewport.Y = 0;
  viewport.Width = g_gameConfiguredWidth;
  viewport.Height = g_gameConfiguredHeight;
  viewport.MinZ = 0.0f;
  viewport.MaxZ = 1.0f;
  g_gameD3DDevice->SetViewport(&viewport);

  return g_gameD3DDevice->GetDeviceCaps(&g_gameDeviceCaps);
}
