.686
.model flat
option casemap:none

EXTERN _tan:PROC
EXTERN ?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A:DWORD
EXTERN ?g_gameProjectionHalfFov@@3NB:QWORD
EXTERN ?g_gameProjectionMinimum@@3MB:DWORD
EXTERN ?g_gameNegativeHalf@@3MB:DWORD
EXTERN ?g_gameTwo@@3MB:DWORD
EXTERN ?g_gameAspectRatio@@3MA:DWORD
EXTERN ?g_gameRenderWidth@@3HA:DWORD
EXTERN ?g_gameRenderHeight@@3HA:DWORD
EXTERN ?g_gameProjectionOffsetX@@3MA:DWORD
EXTERN ?g_gameProjectionOffsetY@@3MA:DWORD
EXTERN ?g_gameProjectionScaleX@@3MA:DWORD
EXTERN ?g_gameProjectionScaleY@@3MA:DWORD

.code

; FUNCTION: SUMO 0x0040386a
; FUNCTION: EDITOR 0x0040386a
PUBLIC ?ApplyGameProjection@@YAHXZ
?ApplyGameProjection@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 44h
    mov eax, dword ptr [?g_gameAspectRatio@@3MA]
    fld qword ptr [?g_gameProjectionHalfFov@@3NB]
    push ecx
    push ecx
    fstp qword ptr [esp]
    mov dword ptr [ebp - 4], eax
    call _tan
    fld dword ptr [ebp - 4]
    fdivr st, st(1)
    pop ecx
    pop ecx
    fstp dword ptr [ebp - 4]
    fld dword ptr [?g_gameProjectionMinimum@@3MB]
    fld dword ptr [ebp - 4]
    fcomp st(1)
    fnstsw ax
    test ah, 5
    jp projectionMinimumReady
    fld st(1)
    fdiv dword ptr [ebp - 4]
    fmul st, st(1)
    fstp st(2)
    fstp dword ptr [ebp - 4]
    jmp projectionAspectReady
projectionMinimumReady:
    fstp st(0)
projectionAspectReady:
    fld1
    mov eax, dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    fdivrp st(1), st
    lea edx, [ebp - 44h]
    push edx
    push 3
    mov dword ptr [ebp - 1ch], 3f8000d2h
    mov dword ptr [ebp - 0ch], 0bdccce1dh
    push eax
    fld1
    fdiv dword ptr [ebp - 4]
    fild dword ptr [?g_gameRenderWidth@@3HA]
    fld dword ptr [?g_gameNegativeHalf@@3MB]
    fmul st, st(1)
    fstp dword ptr [?g_gameProjectionOffsetX@@3MA]
    fild dword ptr [?g_gameRenderHeight@@3HA]
    fld dword ptr [?g_gameNegativeHalf@@3MB]
    fmul st, st(1)
    fstp dword ptr [?g_gameProjectionOffsetY@@3MA]
    fld dword ptr [?g_gameTwo@@3MB]
    fdiv st, st(4)
    fdiv st, st(2)
    fstp dword ptr [?g_gameProjectionScaleX@@3MA]
    fld dword ptr [?g_gameTwo@@3MB]
    fdiv st, st(3)
    fdiv st, st(1)
    fstp dword ptr [?g_gameProjectionScaleY@@3MA]
    fstp st(0)
    fstp st(0)
    fld st(1)
    fstp dword ptr [ebp - 44h]
    fldz
    fstp dword ptr [ebp - 34h]
    fldz
    fstp dword ptr [ebp - 24h]
    fldz
    fstp dword ptr [ebp - 14h]
    fldz
    fstp dword ptr [ebp - 40h]
    fst dword ptr [ebp - 30h]
    fstp st(0)
    fstp st(0)
    fldz
    fstp dword ptr [ebp - 20h]
    fldz
    fstp dword ptr [ebp - 10h]
    fldz
    fstp dword ptr [ebp - 3ch]
    fldz
    fstp dword ptr [ebp - 2ch]
    fldz
    fstp dword ptr [ebp - 38h]
    fldz
    fstp dword ptr [ebp - 28h]
    fld1
    fstp dword ptr [ebp - 18h]
    fldz
    fstp dword ptr [ebp - 8]
    mov ecx, dword ptr [eax]
    call dword ptr [ecx + 0b0h]
    leave
    ret
?ApplyGameProjection@@YAHXZ ENDP

END
