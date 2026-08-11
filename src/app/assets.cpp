#include "boundary.h"

#include "sumo_portable.h"

#include <stdio.h>
#include <stdlib.h>

static char *DiskAssetPath(const char *relative) {
  static char path[1024];
  const char *override = SDL_getenv("SUMOTORI_ASSET_DIR");
  if (override != NULL) {
    SDL_snprintf(path, sizeof(path), "%s/%s", override, relative);
    return path;
  }
  static const char *base;
  if (base == NULL) {
    base = SDL_GetBasePath();
    if (base == NULL)
      base = "";
  }
  SDL_snprintf(path, sizeof(path), "%sassets/%s", base, relative);
  return path;
}

static bool ReadWholeFile(const char *path, SumoAssetBlob *blob) {
  FILE *stream = fopen(path, "rb");
  if (stream == NULL)
    return false;
  if (fseek(stream, 0, SEEK_END) != 0) {
    fclose(stream);
    return false;
  }
  long length = ftell(stream);
  if (length < 0 || fseek(stream, 0, SEEK_SET) != 0) {
    fclose(stream);
    return false;
  }
  void *buffer = malloc((size_t)length + 1);
  if (buffer == NULL) {
    fclose(stream);
    return false;
  }
  size_t readBytes = fread(buffer, 1, (size_t)length, stream);
  fclose(stream);
  if (readBytes != (size_t)length) {
    free(buffer);
    return false;
  }
  ((unsigned char *)buffer)[length] = 0;
  blob->data = buffer;
  blob->size = (SumoU32)length;
  blob->owned = true;
  return true;
}

bool SumoAssetOpen(const char *relative, SumoAssetBlob *blob) {
  blob->data = NULL;
  blob->size = 0;
  blob->owned = false;

  if (SDL_getenv("SUMOTORI_ASSET_DIR") != NULL &&
      ReadWholeFile(DiskAssetPath(relative), blob))
    return true;

  const void *data = NULL;
  SumoU32 size = 0;
  if (SumoLookupEmbeddedAsset(relative, &data, &size)) {
    blob->data = data;
    blob->size = size;
    blob->owned = false;
    return true;
  }

  return ReadWholeFile(DiskAssetPath(relative), blob);
}

bool SumoAssetOpenFile(const char *path, SumoAssetBlob *blob) {
  blob->data = NULL;
  blob->size = 0;
  blob->owned = false;
  return ReadWholeFile(path, blob);
}

void SumoAssetClose(SumoAssetBlob *blob) {
  if (blob->owned)
    free((void *)blob->data);
  blob->data = NULL;
  blob->size = 0;
  blob->owned = false;
}
