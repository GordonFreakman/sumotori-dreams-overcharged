.386
.model flat
option casemap:none

EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC

.code

; FUNCTION: SUMO 0x0040e96a
; FUNCTION: EDITOR 0x0040e98c
PUBLIC ?CalculateAngularMomentum@GameMan@@QAE?AUVector3@@AAU2@0@Z
?CalculateAngularMomentum@GameMan@@QAE?AUVector3@@AAU2@0@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 054h
    fldz
    push ebx
    fstp DWORD PTR [ebp-018h]
    push esi
    fldz
    push edi
    fstp DWORD PTR [ebp-014h]
    lea esi, [ebp-018h]
    fldz
    lea edi, [ebp-0Ch]
    mov ebx, ecx
    fstp DWORD PTR [ebp-010h]
    movsd
    movsd
    movsd
    xor edi, edi

body_loop:
    mov eax, [ebx+edi*4]
    lea ecx, [eax+0B4h]
    push ecx
    lea ecx, [ebp-018h]
    push ecx
    lea ecx, [eax+090h]
    mov esi, eax
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    push eax
    lea eax, [ebp-024h]
    push eax
    lea eax, [esi+0ACh]
    push eax
    lea eax, [ebp-030h]
    push eax
    push DWORD PTR [ebp+0Ch]
    lea eax, [ebp-03Ch]
    push eax
    lea ecx, [esi+084h]
    call ??GVector3@@QAE?AU0@AAU0@@Z
    push eax
    lea eax, [ebp-048h]
    push eax
    push DWORD PTR [ebp+010h]
    lea eax, [ebp-054h]
    mov ecx, esi
    push eax
    add ecx, 09Ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    mov ecx, eax
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    mov ecx, eax
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    mov ecx, eax
    call ??HVector3@@QAE?AU0@AAU0@@Z
    fld DWORD PTR [ebp-0Ch]
    fadd DWORD PTR [eax]
    inc edi
    cmp edi, 0Fh
    fstp DWORD PTR [ebp-0Ch]
    fld DWORD PTR [ebp-8]
    fadd DWORD PTR [eax+4]
    fstp DWORD PTR [ebp-8]
    fld DWORD PTR [ebp-4]
    fadd DWORD PTR [eax+8]
    fstp DWORD PTR [ebp-4]
    jl body_loop

    mov eax, [ebp+8]
    lea esi, [ebp-0Ch]
    mov edi, eax
    movsd
    movsd
    movsd
    pop edi
    pop esi
    pop ebx
    leave
    ret 0Ch
?CalculateAngularMomentum@GameMan@@QAE?AUVector3@@AAU2@0@Z ENDP

END
