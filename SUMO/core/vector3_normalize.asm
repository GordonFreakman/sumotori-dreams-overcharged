.386
.model flat
option casemap:none

EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN _sqrt:PROC

.code

; FUNCTION: SUMO 0x004022c1
; FUNCTION: EDITOR 0x004022c1
PUBLIC ?Normalize@Vector3@@QAEMXZ
?Normalize@Vector3@@QAEMXZ PROC
    push esi
    mov esi, ecx
    call ?LengthSquared@Vector3@@QAEMXZ
    push ecx
    push ecx
    fstp qword ptr [esp]
    call _sqrt
    fld dword ptr [?g_vectorZero@@3MB]
    fld st(1)
    pop ecx
    fucompp
    pop ecx
    fnstsw ax
    test ah, 44h
    jnp short normalizeScaleReady
    fld1
    fdivrp st(1), st
normalizeScaleReady:
    fld st(0)
    fmul dword ptr [esi]
    fstp dword ptr [esi]
    fld st(0)
    fmul dword ptr [esi + 4]
    fstp dword ptr [esi + 4]
    fld st(0)
    fmul dword ptr [esi + 8]
    fstp dword ptr [esi + 8]
    pop esi
    ret
?Normalize@Vector3@@QAEMXZ ENDP

; FUNCTION: SUMO 0x00402302
; FUNCTION: EDITOR 0x00402302
PUBLIC ?Normalized@Vector3@@QAE?AU1@XZ
?Normalized@Vector3@@QAE?AU1@XZ PROC
    push ebp
    mov ebp, esp
    sub esp, 0ch
    push esi
    push edi
    mov esi, ecx
    call ?LengthSquared@Vector3@@QAEMXZ
    push ecx
    push ecx
    fstp qword ptr [esp]
    call _sqrt
    fld dword ptr [?g_vectorZero@@3MB]
    fld st(1)
    pop ecx
    fucompp
    pop ecx
    fnstsw ax
    test ah, 44h
    jnp short normalizedScaleReady
    fld1
    fdivrp st(1), st
normalizedScaleReady:
    mov eax, dword ptr [ebp + 8]
    lea edi, [ebp - 0ch]
    movsd
    movsd
    movsd
    fld dword ptr [ebp - 0ch]
    fmul st, st(1)
    lea esi, [ebp - 0ch]
    mov edi, eax
    fstp dword ptr [ebp - 0ch]
    fld dword ptr [ebp - 8]
    fmul st, st(1)
    fstp dword ptr [ebp - 8]
    fld dword ptr [ebp - 4]
    fmul st, st(1)
    fstp dword ptr [ebp - 4]
    movsd
    movsd
    fstp st(0)
    movsd
    pop edi
    pop esi
    leave
    ret 4
?Normalized@Vector3@@QAE?AU1@XZ ENDP

END
