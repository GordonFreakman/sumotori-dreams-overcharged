#include "boundary.h"

#include "sumo_portable.h"

#include <stdlib.h>
#include <string.h>

enum {
  c_iconDirectorySize = 6,
  c_iconEntrySize = 16,
  c_iconBitmapHeaderSize = 40
};

static SumoU32 ReadU32(const SumoU8 *data) {
  return (SumoU32)data[0] | ((SumoU32)data[1] << 8) | ((SumoU32)data[2] << 16) |
         ((SumoU32)data[3] << 24);
}

static SumoU16 ReadU16(const SumoU8 *data) {
  return (SumoU16)((SumoU32)data[0] | ((SumoU32)data[1] << 8));
}

bool SumoDecodeIcon(const void *iconData, SumoU32 iconSize,
                    SumoIconImage *image) {
  image->pixels = NULL;
  image->width = 0;
  image->height = 0;
  if (iconData == NULL || iconSize < c_iconDirectorySize)
    return false;

  const SumoU8 *base = (const SumoU8 *)iconData;
  if (ReadU16(base) != 0 || ReadU16(base + 2) != 1)
    return false;
  SumoU32 count = ReadU16(base + 4);
  if (count == 0 ||
      iconSize < c_iconDirectorySize + count * (SumoU32)c_iconEntrySize)
    return false;

  SumoU32 bestOffset = 0;
  SumoU32 bestWidth = 0;
  SumoU32 bestHeight = 0;
  for (SumoU32 index = 0; index < count; ++index) {
    const SumoU8 *entry = base + c_iconDirectorySize + index * c_iconEntrySize;
    SumoU32 width = entry[0] != 0 ? (SumoU32)entry[0] : 256u;
    SumoU32 height = entry[1] != 0 ? (SumoU32)entry[1] : 256u;
    SumoU32 depth = ReadU16(entry + 6);
    SumoU32 bytes = ReadU32(entry + 8);
    SumoU32 offset = ReadU32(entry + 12);
    if (depth != 32 || bytes == 0 || offset > iconSize ||
        bytes > iconSize - offset)
      continue;
    if (bytes < c_iconBitmapHeaderSize ||
        ReadU32(base + offset) != c_iconBitmapHeaderSize)
      continue;
    if (width * height <= bestWidth * bestHeight)
      continue;
    bestOffset = offset;
    bestWidth = width;
    bestHeight = height;
  }
  if (bestWidth == 0)
    return false;

  const SumoU8 *xorBits = base + bestOffset + c_iconBitmapHeaderSize;
  SumoU32 pixelCount = bestWidth * bestHeight;
  SumoU8 *pixels = (SumoU8 *)malloc((size_t)pixelCount * 4);
  if (pixels == NULL)
    return false;

  for (SumoU32 row = 0; row < bestHeight; ++row) {
    const SumoU8 *source =
        xorBits + (size_t)(bestHeight - 1 - row) * (size_t)bestWidth * 4;
    SumoU8 *destination = pixels + (size_t)row * (size_t)bestWidth * 4;
    for (SumoU32 column = 0; column < bestWidth; ++column) {
      destination[0] = source[2];
      destination[1] = source[1];
      destination[2] = source[0];
      destination[3] = source[3];
      source += 4;
      destination += 4;
    }
  }

  image->pixels = pixels;
  image->width = (SumoS32)bestWidth;
  image->height = (SumoS32)bestHeight;
  return true;
}

void SumoFreeIcon(SumoIconImage *image) {
  free(image->pixels);
  image->pixels = NULL;
  image->width = 0;
  image->height = 0;
}

bool SumoLoadWindowIcon(SumoIconImage *image) {
  const void *data = NULL;
  SumoU32 size = 0;
  if (!SumoLookupEmbeddedAsset("sumo.ico", &data, &size))
    return false;
  return SumoDecodeIcon(data, size, image);
}
