.586
.model flat
option casemap:none

EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_wavyTextTimeScale@@3MB:DWORD
EXTERN ?g_wavyTextCosineRate@@3MB:DWORD
EXTERN ?g_wavyTextSineRate@@3MB:DWORD
EXTERN ?g_wavyTextPhaseScale@@3MB:DWORD
EXTERN ?g_wavyTextDisplacement@@3MB:DWORD
EXTERN ?g_parserMinimumBreakability@@3MB:DWORD
EXTERN ?g_gameInverseViewMatrix@@3UMatrix3@@A:DWORD
EXTERN ?g_gameCameraWorldPosition@@3UVector3@@A:DWORD
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN _cos:PROC
EXTERN _sin:PROC

.code

; FUNCTION: SUMO 0x0040b86a
; FUNCTION: EDITOR 0x0040b88c
PUBLIC ?TransformWavyTextPoint@@YA?AUVector3@@AAU1@@Z
?TransformWavyTextPoint@@YA?AUVector3@@AAU1@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 02ch
    fild dword ptr [?g_screenTintLevel@@3HA]
    push esi
    push edi
    push ecx
    fmul dword ptr [?g_wavyTextTimeScale@@3MB]
    push ecx
    fst dword ptr [ebp-4]
    fmul dword ptr [?g_wavyTextCosineRate@@3MB]
    fstp qword ptr [esp]
    call _cos
    fadd dword ptr [ebp-4]
    fstp dword ptr [ebp-8]
    fld dword ptr [ebp-4]
    fmul dword ptr [?g_wavyTextSineRate@@3MB]
    fstp qword ptr [esp]
    call _sin
    mov esi, dword ptr [ebp+0ch]
    lea edi, [ebp-014h]
    movsd
    movsd
    fadd dword ptr [ebp-4]
    pop ecx
    pop ecx
    fstp dword ptr [ebp-4]
    lea ecx, [ebp-014h]
    movsd
    call ?Normalize@Vector3@@QAEMXZ
    push 3
    fstp st(0)
    pop esi
    fld1
    fstp dword ptr [ebp-0ch]
    fld dword ptr [ebp-8]
    fmul dword ptr [?g_wavyTextPhaseScale@@3MB]
    fstp dword ptr [ebp-8]

wavyPass:
    fld dword ptr [ebp-010h]
    push ecx
    fmul dword ptr [?g_parserMinimumBreakability@@3MB]
    push ecx
    fadd dword ptr [ebp-4]
    fstp qword ptr [esp]
    call _sin
    fmul dword ptr [?g_wavyTextDisplacement@@3MB]
    fadd dword ptr [ebp-014h]
    fst dword ptr [ebp-014h]
    fmul dword ptr [?g_parserMinimumBreakability@@3MB]
    fadd dword ptr [ebp-8]
    fstp qword ptr [esp]
    call _cos
    dec esi
    fmul dword ptr [?g_wavyTextDisplacement@@3MB]
    pop ecx
    pop ecx
    fadd dword ptr [ebp-010h]
    fstp dword ptr [ebp-010h]
    jnz wavyPass

    push OFFSET ?g_gameCameraWorldPosition@@3UVector3@@A
    lea eax, [ebp-014h]
    push eax
    push OFFSET ?g_gameInverseViewMatrix@@3UMatrix3@@A
    lea eax, [ebp-020h]
    push eax
    push dword ptr [ebp+0ch]
    lea eax, [ebp-02ch]
    push eax
    lea ecx, [ebp-014h]
    call ??HVector3@@QAE?AU0@AAU0@@Z
    mov ecx, eax
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    mov ecx, eax
    call ??HVector3@@QAE?AU0@AAU0@@Z
    mov esi, eax
    mov eax, dword ptr [ebp+8]
    mov edi, eax
    movsd
    movsd
    movsd
    pop edi
    pop esi
    leave
    ret
?TransformWavyTextPoint@@YA?AUVector3@@AAU1@@Z ENDP

END
