#include "boundary.h"

#define IM_ASSERT(_EXPR) SDL_assert(_EXPR)
#include <imgui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

#include "types.h"

void LoadLevelScriptFile(char *fileName);

extern SumoS32 g_selectedLevelScript;
extern char *g_externalLevelScriptOverride;

static const SumoS32 c_maxEntries = 512;
static const size_t c_maxPath = 1024;

struct ModPickerEntry {
  char name[256];
  bool isDirectory;
};

static bool s_active;
static char s_directory[c_maxPath];
static char s_typedPath[c_maxPath];
static char s_pickerStatus[256];
static ModPickerEntry s_entries[c_maxEntries];
static SumoS32 s_entryCount;
static SumoS32 s_selected = -1;

static bool PathIsSeparator(char value) {
#if defined(_WIN32)
  return value == '\\' || value == '/';
#else
  return value == '/';
#endif
}

static void JoinPath(char *out, size_t capacity, const char *directory,
                     const char *leaf) {
  size_t length = strlen(directory);
  if (length != 0 && PathIsSeparator(directory[length - 1]))
    SDL_snprintf(out, capacity, "%s%s", directory, leaf);
  else
#if defined(_WIN32)
    SDL_snprintf(out, capacity, "%s\\%s", directory, leaf);
#else
    SDL_snprintf(out, capacity, "%s/%s", directory, leaf);
#endif
}

static bool ParentPath(char *path) {
  size_t length = strlen(path);
  while (length > 1 && PathIsSeparator(path[length - 1]))
    --length;
  while (length > 0 && !PathIsSeparator(path[length - 1]))
    --length;
  if (length == 0)
    return false;
  while (length > 1 && PathIsSeparator(path[length - 1]))
    --length;
  path[length] = '\0';
  return true;
}

static bool HasSmoExtension(const char *name) {
  size_t length = strlen(name);
  if (length < 5)
    return false;
  const char *tail = name + length - 4;
  return (tail[0] == '.') && (tail[1] == 's' || tail[1] == 'S') &&
         (tail[2] == 'm' || tail[2] == 'M') &&
         (tail[3] == 'o' || tail[3] == 'O');
}

static int CompareEntries(const void *left, const void *right) {
  const ModPickerEntry *a = (const ModPickerEntry *)left;
  const ModPickerEntry *b = (const ModPickerEntry *)right;
  if (a->isDirectory != b->isDirectory)
    return a->isDirectory ? -1 : 1;
  return SDL_strcasecmp(a->name, b->name);
}

static void AppendEntry(const char *name, bool isDirectory) {
  if (s_entryCount >= c_maxEntries)
    return;
  if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
    return;
  if (!isDirectory && !HasSmoExtension(name))
    return;
  SDL_strlcpy(s_entries[s_entryCount].name, name,
              sizeof(s_entries[s_entryCount].name));
  s_entries[s_entryCount].isDirectory = isDirectory;
  ++s_entryCount;
}

bool SumoModPickerSetDirectory(const char *path) {
  if (path == NULL || path[0] == '\0')
    return false;

  char candidate[c_maxPath];
  SDL_strlcpy(candidate, path, sizeof(candidate));

#if defined(_WIN32)
  char pattern[c_maxPath];
  JoinPath(pattern, sizeof(pattern), candidate, "*");
  WIN32_FIND_DATAA find;
  HANDLE handle = FindFirstFileA(pattern, &find);
  if (handle == INVALID_HANDLE_VALUE)
    return false;
  s_entryCount = 0;
  s_selected = -1;
  do {
    AppendEntry(find.cFileName,
                (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
  } while (FindNextFileA(handle, &find));
  FindClose(handle);
#else
  DIR *directory = opendir(candidate);
  if (directory == NULL)
    return false;
  s_entryCount = 0;
  s_selected = -1;
  for (struct dirent *entry = readdir(directory); entry != NULL;
       entry = readdir(directory)) {
    char full[c_maxPath];
    JoinPath(full, sizeof(full), candidate, entry->d_name);
    struct stat info;
    bool isDirectory = stat(full, &info) == 0 && S_ISDIR(info.st_mode);
    AppendEntry(entry->d_name, isDirectory);
  }
  closedir(directory);
#endif

  if (s_entryCount > 1)
    qsort(s_entries, (size_t)s_entryCount, sizeof(s_entries[0]),
          CompareEntries);
  SDL_strlcpy(s_directory, candidate, sizeof(s_directory));
  return true;
}

const char *SumoModPickerDirectory() { return s_directory; }
SumoS32 SumoModPickerEntryCount() { return s_entryCount; }

const char *SumoModPickerEntryName(SumoS32 index) {
  if (index < 0 || index >= s_entryCount)
    return "";
  return s_entries[index].name;
}

bool SumoModPickerEntryIsDirectory(SumoS32 index) {
  if (index < 0 || index >= s_entryCount)
    return false;
  return s_entries[index].isDirectory;
}

bool SumoModPickerLoadFile(const char *path) {
  if (path == NULL || path[0] == '\0')
    return false;
  FILE *probe = fopen(path, "rb");
  if (probe == NULL) {
    SDL_snprintf(s_pickerStatus, sizeof(s_pickerStatus), "cannot open %s",
                 path);
    return false;
  }
  fclose(probe);

  char mutablePath[c_maxPath];
  SDL_strlcpy(mutablePath, path, sizeof(mutablePath));
  LoadLevelScriptFile(mutablePath);
  if (g_selectedLevelScript != -1) {
    SDL_snprintf(s_pickerStatus, sizeof(s_pickerStatus), "could not read %s",
                 path);
    return false;
  }
  s_active = false;
  return true;
}

bool SumoModPickerChoose(SumoS32 index) {
  if (index < 0 || index >= s_entryCount)
    return false;
  char full[c_maxPath];
  JoinPath(full, sizeof(full), s_directory, s_entries[index].name);
  if (s_entries[index].isDirectory)
    return SumoModPickerSetDirectory(full);
  return SumoModPickerLoadFile(full);
}

void SumoModPickerCancel() {
  s_active = false;
  s_pickerStatus[0] = '\0';
}

bool SumoModPickerActive() { return s_active; }

static void ChooseStartDirectory() {
  if (s_directory[0] != '\0' && SumoModPickerSetDirectory(s_directory))
    return;

#if SUMO_SDL_VERSION == 3
  const char *documents = SDL_GetUserFolder(SDL_FOLDER_DOCUMENTS);
  if (documents != NULL && SumoModPickerSetDirectory(documents))
    return;
#else
  const char *home = SDL_getenv("HOME");
  if (home == NULL)
    home = SDL_getenv("USERPROFILE");
  if (home != NULL) {
    char documents[c_maxPath];
    JoinPath(documents, sizeof(documents), home, "Documents");
    if (SumoModPickerSetDirectory(documents))
      return;
    if (SumoModPickerSetDirectory(home))
      return;
  }
#endif

#if SUMO_SDL_VERSION == 3
  const char *base = SDL_GetBasePath();
#else
  char *base = SDL_GetBasePath();
#endif
  if (base != NULL) {
    bool ok = SumoModPickerSetDirectory(base);
#if SUMO_SDL_VERSION == 2
    SDL_free(base);
#endif
    if (ok)
      return;
  }
  SumoModPickerSetDirectory(".");
}

void SumoRequestModFilePicker() {
  s_active = true;
  s_selected = -1;
  s_pickerStatus[0] = '\0';
  s_typedPath[0] = '\0';
  ChooseStartDirectory();
}

void SumoModPickerDrawPanel() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::SetNextWindowPos(
      ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
      ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  ImGui::SetNextWindowSize(
      ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.6f),
      ImGuiCond_Appearing);

  bool open = true;
  if (ImGui::Begin("Load mod file", &open, ImGuiWindowFlags_NoCollapse)) {
    ImGui::TextWrapped("%s", s_directory);
    ImGui::Separator();

    ImVec2 available = ImGui::GetContentRegionAvail();
    available.y -= ImGui::GetFrameHeightWithSpacing() * 3.0f;
    if (ImGui::BeginChild("##entries", available, ImGuiChildFlags_Borders)) {
      if (ImGui::Selectable(".. (up)", false,
                            ImGuiSelectableFlags_AllowDoubleClick) &&
          ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
        char parent[c_maxPath];
        SDL_strlcpy(parent, s_directory, sizeof(parent));
        if (ParentPath(parent))
          SumoModPickerSetDirectory(parent);
      }
      for (SumoS32 index = 0; index < s_entryCount; ++index) {
        char label[288];
        SDL_snprintf(label, sizeof(label), "%s%s",
                     s_entries[index].isDirectory ? "[dir] " : "      ",
                     s_entries[index].name);
        if (ImGui::Selectable(label, s_selected == index,
                              ImGuiSelectableFlags_AllowDoubleClick)) {
          s_selected = index;
          if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            SumoModPickerChoose(index);
        }
      }
    }
    ImGui::EndChild();

    ImGui::SetNextItemWidth(-1.0f);
    ImGui::InputTextWithHint("##typed", "or type a path to a .smo file",
                             s_typedPath, sizeof(s_typedPath));

    if (ImGui::Button("LOAD")) {
      if (s_typedPath[0] != '\0')
        SumoModPickerLoadFile(s_typedPath);
      else if (s_selected >= 0)
        SumoModPickerChoose(s_selected);
    }
    ImGui::SameLine();
    if (ImGui::Button("CANCEL"))
      SumoModPickerCancel();
    if (s_pickerStatus[0] != '\0') {
      ImGui::SameLine();
      ImGui::TextDisabled("%s", s_pickerStatus);
    }
  }
  ImGui::End();

  if (!open)
    SumoModPickerCancel();
}
