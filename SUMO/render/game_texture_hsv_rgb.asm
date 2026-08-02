.686
.model flat
option casemap:none

EXTERN ___ftol:PROC
EXTERN __floor:PROC
EXTERN ?g_textureZero@@3NB:QWORD
EXTERN ?g_textureHueCircle@@3NB:QWORD
EXTERN ?g_textureHueSectorScale@@3NB:QWORD
EXTERN ?g_textureOne@@3NB:QWORD

.code

; FUNCTION: SUMO 0x0041bd10
; FUNCTION: EDITOR 0x0041bd30
PUBLIC ?ConvertTextureHsvToRgb@@YAIMMM@Z
?ConvertTextureHsvToRgb@@YAIMMM@Z PROC
    fld dword ptr [esp + 8]
    fcomp qword ptr [?g_textureZero@@3NB]
    sub esp, 8
    fnstsw ax
    test ah, 40h
    jz hsvRgbChromatic
    mov eax, dword ptr [esp + 14h]
    fld dword ptr [esp + 14h]
    mov ecx, eax
    mov dword ptr [esp + 0ch], eax
    mov dword ptr [esp + 14h], ecx
    jmp hsvRgbPack

hsvRgbChromatic:
    fld dword ptr [esp + 0ch]
    fcom qword ptr [?g_textureHueCircle@@3NB]
    fnstsw ax
    test ah, 1
    jnz hsvRgbCheckNegativeHue
hsvRgbSubtractCircle:
    fsub qword ptr [?g_textureHueCircle@@3NB]
    fcom qword ptr [?g_textureHueCircle@@3NB]
    fnstsw ax
    test ah, 1
    jz hsvRgbSubtractCircle
hsvRgbCheckNegativeHue:
    fcom qword ptr [?g_textureZero@@3NB]
    fnstsw ax
    test ah, 1
    jz hsvRgbHueReady
hsvRgbAddCircle:
    fadd qword ptr [?g_textureHueCircle@@3NB]
    fcom qword ptr [?g_textureZero@@3NB]
    fnstsw ax
    test ah, 1
    jnz hsvRgbAddCircle
hsvRgbHueReady:
    fmul qword ptr [?g_textureHueSectorScale@@3NB]
    sub esp, 8
    fst dword ptr [esp + 14h]
    fstp qword ptr [esp]
    call __floor
    fld dword ptr [esp + 14h]
    fsub st, st(1)
    fld dword ptr [esp + 18h]
    fsubr qword ptr [?g_textureOne@@3NB]
    fmul dword ptr [esp + 1ch]
    add esp, 8
    db 0d9h, 05ch, 024h, 000h
    fld st
    fmul dword ptr [esp + 10h]
    fsubr qword ptr [?g_textureOne@@3NB]
    fmul dword ptr [esp + 14h]
    fstp dword ptr [esp + 4]
    fsubr qword ptr [?g_textureOne@@3NB]
    fmul dword ptr [esp + 10h]
    fsubr qword ptr [?g_textureOne@@3NB]
    fmul dword ptr [esp + 14h]
    fstp dword ptr [esp + 10h]
    call ___ftol
    cmp eax, 5
    ja hsvRgbDefault
    jmp dword ptr [hsvRgbJumpTable + eax * 4]

hsvRgbCase0::
    mov edx, dword ptr [esp + 10h]
    db 08bh, 044h, 024h, 000h
    fld dword ptr [esp + 14h]
    mov dword ptr [esp + 0ch], edx
    mov dword ptr [esp + 14h], eax
    jmp hsvRgbPack

hsvRgbCase1::
    mov ecx, dword ptr [esp + 14h]
    db 08bh, 054h, 024h, 000h
    fld dword ptr [esp + 4]
    mov dword ptr [esp + 0ch], ecx
    mov dword ptr [esp + 14h], edx
    jmp hsvRgbPack

hsvRgbCase2::
    mov eax, dword ptr [esp + 14h]
    mov ecx, dword ptr [esp + 10h]
    db 0d9h, 044h, 024h, 000h
    mov dword ptr [esp + 0ch], eax
    mov dword ptr [esp + 14h], ecx
    jmp hsvRgbPack

hsvRgbCase3::
    mov edx, dword ptr [esp + 4]
    mov eax, dword ptr [esp + 14h]
    db 0d9h, 044h, 024h, 000h
    mov dword ptr [esp + 0ch], edx
    mov dword ptr [esp + 14h], eax
    jmp hsvRgbPack

hsvRgbCase4::
    db 08bh, 04ch, 024h, 000h
    mov edx, dword ptr [esp + 14h]
    fld dword ptr [esp + 10h]
    mov dword ptr [esp + 0ch], ecx
    mov dword ptr [esp + 14h], edx
    jmp hsvRgbPack

hsvRgbCase5::
    db 08bh, 044h, 024h, 000h
    mov ecx, dword ptr [esp + 4]
    fld dword ptr [esp + 14h]
    mov dword ptr [esp + 0ch], eax
    mov dword ptr [esp + 14h], ecx
    jmp hsvRgbPack

hsvRgbDefault:
    fld dword ptr [esp + 14h]

hsvRgbPack:
    push esi
    push edi
    call ___ftol
    fld dword ptr [esp + 14h]
    mov esi, eax
    call ___ftol
    fld dword ptr [esp + 1ch]
    mov edi, eax
    call ___ftol
    cmp esi, 0ffh
    mov ecx, eax
    jle hsvRgbRedReady
    mov esi, 0ffh
hsvRgbRedReady:
    cmp edi, 0ffh
    jle hsvRgbGreenReady
    mov edi, 0ffh
hsvRgbGreenReady:
    cmp ecx, 0ffh
    jle hsvRgbBlueReady
    mov ecx, 0ffh
hsvRgbBlueReady:
    mov eax, esi
    shl eax, 8
    or eax, edi
    pop edi
    shl eax, 8
    or eax, ecx
    pop esi
    add esp, 8
    ret
?ConvertTextureHsvToRgb@@YAIMMM@Z ENDP

hsvRgbJumpTable DD OFFSET hsvRgbCase0
                   DD OFFSET hsvRgbCase1
                   DD OFFSET hsvRgbCase2
                   DD OFFSET hsvRgbCase3
                   DD OFFSET hsvRgbCase4
                   DD OFFSET hsvRgbCase5

END
