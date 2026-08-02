#include "types.h"

#include <string.h>
#include <windows.h>

// FUNCTION: SUMO 0x00403e16
// FUNCTION: EDITOR 0x00403e16
SumoS32 BlendTextIntoTexture(SumoU8 *p_pixels, const char *p_text, SumoS32 p_x, SumoS32 p_y, SumoS32 p_textureWidth, SumoS32 p_width, SumoS32 p_height, SumoS32 p_fontHeight, SumoS32 p_textColor, SumoS32 p_backgroundColor, const char *p_fontName) {
  BITMAPINFO bitmapInfo;
  SumoS32 destinationRowAdvance;
  SumoU8 *bitmapPixels;
  HFONT font;

  memset(&bitmapInfo, 0, sizeof(BITMAPINFOHEADER));
  bitmapInfo.bmiHeader.biWidth = p_width;
  bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bitmapInfo.bmiHeader.biHeight = -p_height;
  bitmapInfo.bmiHeader.biPlanes = 1;
  bitmapInfo.bmiHeader.biCompression = BI_RGB;
  bitmapInfo.bmiHeader.biBitCount = 32;

  HDC deviceContext = CreateCompatibleDC(NULL);
  HBITMAP bitmap = CreateDIBSection(deviceContext, &bitmapInfo, DIB_RGB_COLORS,
                                    (void **)&bitmapPixels, NULL, 0);
  SetMapMode(deviceContext, MM_TEXT);
  SumoS32 scaledFontHeight =
      MulDiv(p_fontHeight, GetDeviceCaps(deviceContext, LOGPIXELSY), 72);
  font = CreateFont(scaledFontHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                    ANTIALIASED_QUALITY, VARIABLE_PITCH, p_fontName);
  if (font != NULL) {
    SelectObject(deviceContext, bitmap);
    SelectObject(deviceContext, font);
    SetTextColor(deviceContext, p_textColor ^ 0xffffff);
    SetBkColor(deviceContext, p_backgroundColor ^ 0xffffff);
    SetTextAlign(deviceContext, 0);
    ExtTextOut(deviceContext, 0, 0, ETO_OPAQUE, NULL, p_text, strlen(p_text),
               NULL);

    SumoU8 *source = bitmapPixels;
    SumoU8 *destination =
        p_pixels + (p_y * p_textureWidth + p_x) * sizeof(SumoU32);
    if (p_height > 0) {
      SumoS32 remainingRows = p_height;
      destinationRowAdvance = (p_textureWidth - p_width) * sizeof(SumoU32);
      do {
        if (p_width > 0) {
          p_height = p_width;
          do {
            destination[0] = ((SumoU32)destination[0] * (255 - source[0])) >> 8;
            destination[1] = ((SumoU32)destination[1] * (255 - source[1])) >> 8;
            destination[2] = ((SumoU32)destination[2] * (255 - source[2])) >> 8;
            destination[3] = ((SumoU32)destination[2] * (255 - source[2])) >> 8;
            source += sizeof(SumoU32);
            destination += sizeof(SumoU32);
            --p_height;
          } while (p_height != 0);
        }

        destination += destinationRowAdvance;
        --remainingRows;
      } while (remainingRows != 0);
    }
  }

  return 0;
}
