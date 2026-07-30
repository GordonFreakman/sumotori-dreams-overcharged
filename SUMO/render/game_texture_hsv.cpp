#include "types.h"

extern "C" SumoS32 __ftol();
extern "C" double _floor(double);
extern const double g_textureOne;
extern const double g_textureHueSectorTwo;
extern const double g_textureHueSectorFour;
extern const double g_textureHueDegreesPerSector;
extern const double g_textureHueCircle;
extern const double g_textureZero;

extern const double g_textureHueSectorScale;
extern const double g_textureHueByteToDegrees;
extern const double g_textureInvByteMaximum;
extern SumoU8* g_textureLayers[4];

SumoU32 ConvertTextureHsvToRgb(
    SumoF32 hue, SumoF32 saturation, SumoF32 value);

// FUNCTION: SUMO 0x0041bef0
// FUNCTION: EDITOR 0x0041bf10
__declspec(naked) void ConvertTextureRgbToHsv(
    SumoF32 red, SumoF32 green, SumoF32 blue,
    SumoF32* hue, SumoF32* saturation, SumoF32* value)
{
  __asm {
    fld dword ptr [esp + 4]
    fcomp dword ptr [esp + 8]
    sub esp, 8
    fnstsw ax
    test ah, 41h
    jne rgbHsvMaximumGreen
    fld dword ptr [esp + 0ch]
    jmp rgbHsvCompareMaximumBlue
rgbHsvMaximumGreen:
    fld dword ptr [esp + 10h]
rgbHsvCompareMaximumBlue:
    fld dword ptr [esp + 14h]
    fcomp st(1)
    fnstsw ax
    test ah, 41h
    jne rgbHsvMaximumReady
    fstp st
    fld dword ptr [esp + 14h]
rgbHsvMaximumReady:
    fld dword ptr [esp + 0ch]
    fcomp dword ptr [esp + 10h]
    fnstsw ax
    test ah, 1
    je rgbHsvMinimumGreen
    fld dword ptr [esp + 0ch]
    jmp rgbHsvCompareMinimumBlue
rgbHsvMinimumGreen:
    fld dword ptr [esp + 10h]
rgbHsvCompareMinimumBlue:
    fld dword ptr [esp + 14h]
    fcomp st(1)
    fnstsw ax
    test ah, 1
    je rgbHsvExtremaReady
    fstp st
    fld dword ptr [esp + 14h]
rgbHsvExtremaReady:
    mov eax, dword ptr [esp + 20h]
    mov ecx, dword ptr [esp + 1ch]
    fld st(1)
    fstp dword ptr [eax]
    fld st(1)
    fcomp qword ptr [g_textureZero]
    mov dword ptr [ecx], 0
    fnstsw ax
    test ah, 40h
    jne rgbHsvSaturationReady
    fld st(1)
    fsub st, st(1)
    fdiv st, st(2)
    fstp dword ptr [ecx]
rgbHsvSaturationReady:
    fld dword ptr [ecx]
    fcomp qword ptr [g_textureZero]
    fnstsw ax
    test ah, 40h
    je rgbHsvChromatic
    mov ecx, dword ptr [esp + 18h]
    fstp st
    fstp st
    mov dword ptr [ecx], 0bf800000h
    add esp, 8
    ret
rgbHsvChromatic:
    fld st(1)
    fsub st, st(1)
    mov ecx, dword ptr [esp + 18h]
    fstp dword ptr [esp + 20h]
    fstp st
    fld st
    fsub dword ptr [esp + 0ch]
    fstp dword ptr [esp + 4]
    fld st
    fsub dword ptr [esp + 10h]
    _emit 0d9h
    _emit 05ch
    _emit 024h
    _emit 000h
    fld st
    fsub dword ptr [esp + 14h]
    fstp dword ptr [esp + 1ch]
    fld dword ptr [esp + 0ch]
    fcomp st(1)
    fnstsw ax
    test ah, 40h
    je rgbHsvCheckGreenMaximum
    fstp st
    fld dword ptr [esp + 1ch]
    _emit 0d8h
    _emit 064h
    _emit 024h
    _emit 000h
    fdiv dword ptr [esp + 20h]
    jmp rgbHsvStoreSector
rgbHsvCheckGreenMaximum:
    fld dword ptr [esp + 10h]
    fcomp st(1)
    fnstsw ax
    test ah, 40h
    je rgbHsvCheckBlueMaximum
    fstp st
    fld dword ptr [esp + 4]
    fsub dword ptr [esp + 1ch]
    fdiv dword ptr [esp + 20h]
    fadd qword ptr [g_textureHueSectorTwo]
    jmp rgbHsvStoreSector
rgbHsvCheckBlueMaximum:
    fld dword ptr [esp + 14h]
    fcomp st(1)
    fnstsw ax
    test ah, 40h
    fstp st
    je rgbHsvScaleHue
    _emit 0d9h
    _emit 044h
    _emit 024h
    _emit 000h
    fsub dword ptr [esp + 4]
    fdiv dword ptr [esp + 20h]
    fadd qword ptr [g_textureHueSectorFour]
rgbHsvStoreSector:
    fstp dword ptr [ecx]
rgbHsvScaleHue:
    fld dword ptr [ecx]
    fmul qword ptr [g_textureHueDegreesPerSector]
    fst dword ptr [ecx]
    fcomp qword ptr [g_textureZero]
    fnstsw ax
    test ah, 1
    je rgbHsvRemoveLargeHue
rgbHsvAddCircle:
    fld dword ptr [ecx]
    fadd qword ptr [g_textureHueCircle]
    fst dword ptr [ecx]
    fcomp qword ptr [g_textureZero]
    fnstsw ax
    test ah, 1
    jne rgbHsvAddCircle
rgbHsvRemoveLargeHue:
    fld dword ptr [ecx]
    fcomp qword ptr [g_textureHueCircle]
    fnstsw ax
    test ah, 1
    jne rgbHsvDone
rgbHsvSubtractCircle:
    fld dword ptr [ecx]
    fsub qword ptr [g_textureHueCircle]
    fst dword ptr [ecx]
    fcomp qword ptr [g_textureHueCircle]
    fnstsw ax
    test ah, 1
    je rgbHsvSubtractCircle
rgbHsvDone:
    add esp, 8
    ret
  }
}

// FUNCTION: SUMO 0x0041c080
// FUNCTION: EDITOR 0x0041c0a0
__declspec(naked) void AdjustTextureHsv(
    SumoS32 layerIndex, SumoS32 hueOffset, SumoS32 saturationReduction)
{
  __asm {
    sub esp, 0ch
    fild dword ptr [esp + 14h]
    mov eax, dword ptr [esp + 10h]
    push esi
    mov ecx, 0ffh
    push edi
    mov esi, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [esp + 20h]
    fmul qword ptr [g_textureHueByteToDegrees]
    sub ecx, eax
    mov edi, 10000h
    mov dword ptr [esp + 18h], ecx
    fstp dword ptr [esp + 8]
    fild dword ptr [esp + 18h]
    fmul qword ptr [g_textureInvByteMaximum]
    fstp dword ptr [esp + 0ch]
adjustHsvNextPixel:
    mov eax, dword ptr [esi]
    lea edx, dword ptr [esp + 10h]
    lea ecx, dword ptr [esp + 18h]
    push edx
    push ecx
    mov ecx, eax
    lea edx, dword ptr [esp + 24h]
    and ecx, 0ffh
    push edx
    mov dword ptr [esp + 2ch], ecx
    fild dword ptr [esp + 2ch]
    mov edx, eax
    push ecx
    shr edx, 8
    fstp dword ptr [esp]
    and edx, 0ffh
    push ecx
    mov dword ptr [esp + 34h], edx
    fild dword ptr [esp + 34h]
    shr eax, 10h
    and eax, 0ffh
    fstp dword ptr [esp]
    mov dword ptr [esp + 34h], eax
    push ecx
    fild dword ptr [esp + 38h]
    fstp dword ptr [esp]
    call ConvertTextureRgbToHsv
    fld dword ptr [esp + 34h]
    fadd dword ptr [esp + 20h]
    mov eax, dword ptr [esp + 28h]
    push eax
    fstp dword ptr [esp + 38h]
    fld dword ptr [esp + 34h]
    fmul dword ptr [esp + 28h]
    mov edx, dword ptr [esp + 38h]
    fstp dword ptr [esp + 34h]
    mov ecx, dword ptr [esp + 34h]
    push ecx
    push edx
    call ConvertTextureHsvToRgb
    mov dword ptr [esi], eax
    add esp, 24h
    add esi, 4
    dec edi
    jne adjustHsvNextPixel
    pop edi
    pop esi
    add esp, 0ch
    ret
  }
}
