#ifndef SUMO_PORTABLE_H
#define SUMO_PORTABLE_H

#include "types.h"

#if !defined(_HRESULT_DEFINED)
#define _HRESULT_DEFINED
typedef SumoS32 HRESULT;
#endif

struct SumoPortableWindow;
typedef SumoPortableWindow *HWND;

SumoU32 timeGetTime();

SumoS32 GetWindowText(HWND window, char *buffer, SumoS32 capacity);
SumoS32 SetWindowText(HWND window, const char *text);

#define MB_ICONEXCLAMATION 0x00000030
SumoS32 MessageBox(void *owner, const char *text, const char *caption,
                   SumoU32 type);

SumoU8 *BeginGameWaterVertices(SumoS32 byteCount);
void FinishGameWaterVertices(SumoS32 triangleCount);

SumoU8 *AcquireGameBackBufferPixels(SumoS32 *p_pitch);
void ReleaseGameBackBufferPixels(SumoU8 *p_pixels);

SumoS32 SumoLookupEmbeddedAsset(const char *name, const void **data,
                                SumoU32 *size);

#endif
