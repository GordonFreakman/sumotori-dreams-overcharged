#include <windows.h>

#include "big_integer.h"
#include "types.h"

extern SumoS32 g_gameRuntimeMode;
extern SumoS16 g_gameBoxTriangleOrder[];

enum {
  c_gameSettingsTransformIndex = 10252,
  c_gameSettingsTransformByteOffset = 1
};

BigInteger TransformEncodedGameSettings(BigInteger input, SumoS32 modulusValue,
                                        BigInteger bound);


// FUNCTION: SUMO 0x0040431c
bool ValidateEncodedGameSettings(void *p_data, SumoS32 p_length, SumoS32 p_bypassModularPower, SumoS32 p_decodedOutput) {

  const char *alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  BigInteger modulus(0);
  modulus.AppendLimb(0x623b462f);
  modulus.AppendLimb(0x04142647);
  modulus.AppendLimb(0xf92f9f8f);
  modulus.AppendLimb(0xda9d272f);

  BigInteger exponent(97);
  BigInteger encoded((char *)p_data, p_length, alphabet, 36);
  bool encodedIsZero;
  {
    BigInteger zero(0);
    encodedIsZero = encoded == zero;
  }
  if (encodedIsZero) {
    return false;
  }

  BigInteger decoded;
  if (p_bypassModularPower == 0) {
    decoded.ModularPower(encoded, exponent, modulus);
  } else {
    decoded = encoded;
  }

  BigInteger transformed = TransformEncodedGameSettings(
      decoded,
      0x0076adf1,
      modulus);
  if (transformed == decoded) {
    if (p_decodedOutput != 0) {
      decoded.WriteString((char *)p_decodedOutput, 200, alphabet, 36, 0);
    }
    return true;
  }
  return false;
}

// FUNCTION: SUMO 0x0040460f
SumoS32 CheckStoredGameSettings() {
  DWORD dataSize;
  HKEY key;
  BYTE data[200];

  if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Archee\\Sumotori", 0,
                    KEY_READ, &key) == ERROR_SUCCESS) {
    dataSize = 25;
    RegQueryValueExA(key, "settings", 0, 0, data, &dataSize);
    data[25] = 0;
    RegCloseKey(key);
    return ValidateEncodedGameSettings(data, 0, 1, 0);
  }

  return 0;
}
