#include <windows.h>

#include <string.h>

bool ValidateEncodedGameSettings(void* data, int output,
                                 int useModularPower, int writeDecoded);

// FUNCTION: SUMO 0x0040451c
LONG SaveGameSettings(BYTE* data)
{
  HKEY key;
  // STRING: SUMO 0x0042c2b0
  LONG result = RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Archee\\Sumotori", &key);
  if (result == ERROR_SUCCESS) {
    // STRING: SUMO 0x0042c2a4
    RegSetValueExA(key, "settings", 0, REG_BINARY, data,
                   strlen((const char*) data));
    return RegCloseKey(key);
  }
  return result;
}

// FUNCTION: SUMO 0x00404562
int ValidateAndSaveGameSettingsCode(char* text, char saveToRegistry)
{
  BYTE data[300];

  for (int index = 0; index < 25; ++index) {
    while (*text != 0 &&
           !(*text >= 'a' && *text <= 'z') &&
           !(*text >= 'A' && *text <= 'Z') &&
           !(*text >= '0' && *text <= '9')) {
      ++text;
    }

    char value = *text;
    BYTE* destination = &data[index];
    *destination = value;
    if (value >= 'a' && value <= 'z') {
      *destination = value - ('a' - 'A');
    }
    if (value != 0) {
      ++text;
    }
    destination[1] = 0;
  }

  if (data[0] == 0) {
    return 1;
  }
  if (ValidateEncodedGameSettings(data, 0, 0, (int) data)) {
    if (saveToRegistry) {
      SaveGameSettings(data);
    }
    return 0;
  }
  return 2;
}
