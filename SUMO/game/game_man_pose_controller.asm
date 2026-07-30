.386
.model flat
option casemap:none

EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z:PROC
EXTERN _sqrt:PROC
EXTERN ?g_gameManPoseImpulseGain@@3MB:DWORD

.code

; FUNCTION: SUMO 0x0040ea30
; FUNCTION: EDITOR 0x0040ea52
PUBLIC ?Render@GameMan@@QAEXPAX@Z
?Render@GameMan@@QAEXPAX@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 094h
    push ebx
    push esi
    push edi
    mov edi, [ebp+8]
    mov DWORD PTR [ebp-018h], 03ECCCCCDh
    mov DWORD PTR [ebp-01Ch], 03E800000h
    lea esi, [ecx+03Ch]
    add edi, 018h
    mov DWORD PTR [ebp-014h], 0Eh
    mov ebx, 090h

joint_loop:
    mov eax, [edi+018h]
    mov [ebp+8], eax
    mov eax, [esi]
    mov eax, [eax+4]
    add eax, 060h
    push eax
    mov [ebp-010h], eax
    lea eax, [ebp-040h]
    push eax
    mov ecx, edi
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    mov eax, [esi]
    mov ecx, [eax]
    add ecx, 060h
    push ecx
    lea ecx, [ebp-034h]
    push ecx
    lea ecx, [eax+020h]
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    lea eax, [ebp-018h]
    push eax
    lea eax, [ebp-0Ch]
    push eax
    lea eax, [ebp-034h]
    push eax
    lea eax, [ebp-070h]
    push eax
    lea ecx, [ebp-040h]
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    mov ecx, eax
    call ?Scale@Vector3@@QAE?AU1@AAM@Z

    push DWORD PTR [ebp-010h]
    lea eax, [ebp-04Ch]
    push eax
    lea ecx, [edi+0Ch]
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    mov eax, [esi]
    mov ecx, [eax]
    add ecx, 060h
    push ecx
    lea ecx, [ebp-028h]
    push ecx
    lea ecx, [eax+038h]
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    lea eax, [ebp-01Ch]
    push eax
    lea eax, [ebp-058h]
    push eax
    lea eax, [ebp-018h]
    push eax
    lea eax, [ebp-088h]
    push eax
    lea eax, [ebp-028h]
    push eax
    lea eax, [ebp-064h]
    push eax
    lea ecx, [ebp-04Ch]
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    mov ecx, eax
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    mov ecx, eax
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    fld DWORD PTR [ebp-0Ch]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [ebp-0Ch]
    fld DWORD PTR [ebp-8]
    fadd DWORD PTR [eax+4]
    fstp DWORD PTR [ebp-8]
    fld DWORD PTR [ebp-4]
    fadd DWORD PTR [eax+8]

    mov eax, [esi]
    mov ecx, [eax+4]
    add ecx, ebx
    push ecx
    fstp DWORD PTR [ebp-4]
    lea ecx, [ebp-07Ch]
    push ecx
    mov ecx, [eax]
    add ecx, ebx
    call ??GVector3@@QAE?AU0@AAU0@@Z
    fld DWORD PTR [ebp-0Ch]
    fsub DWORD PTR [eax]
    fst DWORD PTR [ebp-0Ch]
    fld DWORD PTR [ebp-8]
    fsub DWORD PTR [eax+4]
    fst DWORD PTR [ebp-8]
    fld DWORD PTR [ebp-4]
    fsub DWORD PTR [eax+8]
    fst DWORD PTR [ebp-4]
    fld st(0)
    fmul st, st(1)
    fld st(2)
    fmul st, st(3)
    faddp st(1), st
    fld st(3)
    fmul st, st(4)
    faddp st(1), st
    fstp st(3)
    fstp st(0)
    fstp st(0)
    fld DWORD PTR [ebp+8]
    fmul DWORD PTR [ebp+8]
    fld st(1)
    fcompp
    fnstsw ax
    test ah, 041h
    jnz short correction_clamped
    push ecx
    push ecx
    fstp QWORD PTR [esp]
    call _sqrt
    fdivr DWORD PTR [ebp+8]
    pop ecx
    pop ecx
    fld DWORD PTR [ebp-0Ch]
    fmul st, st(1)
    fstp DWORD PTR [ebp-0Ch]
    fld DWORD PTR [ebp-8]
    fmul st, st(1)
    fstp DWORD PTR [ebp-8]
    fld DWORD PTR [ebp-4]
    fmul st, st(1)
    fstp DWORD PTR [ebp-4]

correction_clamped:
    mov eax, [esi]
    fstp st(0)
    mov ecx, [eax+4]
    mov eax, [eax]
    fld DWORD PTR [ecx+0B8h]
    fadd DWORD PTR [eax+0B8h]
    lea eax, [ebp-010h]
    push eax
    lea eax, [ebp-094h]
    fdivr DWORD PTR [?g_gameManPoseImpulseGain@@3MB]
    push eax
    lea ecx, [ebp-0Ch]
    fstp DWORD PTR [ebp-010h]
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    push eax
    push DWORD PTR [esi]
    call ?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z
    pop ecx
    add esi, 4
    add edi, 034h
    dec DWORD PTR [ebp-014h]
    pop ecx
    jne joint_loop

    pop edi
    pop esi
    pop ebx
    leave
    ret 4
?Render@GameMan@@QAEXPAX@Z ENDP

END
