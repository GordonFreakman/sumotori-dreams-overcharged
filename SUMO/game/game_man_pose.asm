.386
.model flat
option casemap:none

EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC

.code

; FUNCTION: SUMO 0x0040e718
; FUNCTION: EDITOR 0x0040e73a
PUBLIC ?InitializeJointTransforms@GameManPose@@QAEXPAUGameMan@@@Z
?InitializeJointTransforms@GameManPose@@QAEXPAUGameMan@@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 034h
    push ebx
    mov ebx, [ebp+8]
    add ecx, 024h
    push esi
    push edi
    mov [ebp-4], ecx
    add ebx, 03Ch
    mov DWORD PTR [ebp+8], 0Eh

joint_loop:
    mov eax, [ebx]
    mov ecx, [eax]
    add ecx, 060h
    push ecx
    lea ecx, [ebp-010h]
    push ecx
    lea ecx, [eax+020h]
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    push eax
    lea eax, [ebp-01Ch]
    push eax
    mov eax, [ebx]
    mov ecx, [eax+4]
    add ecx, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    mov edi, [ebp-4]
    add edi, -0Ch
    mov esi, eax
    movsd
    movsd
    movsd

    mov eax, [ebx]
    mov ecx, [eax]
    add ecx, 060h
    push ecx
    lea ecx, [ebp-028h]
    push ecx
    lea ecx, [eax+038h]
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    push eax
    lea eax, [ebp-034h]
    push eax
    mov eax, [ebx]
    mov ecx, [eax+4]
    add ecx, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    mov edi, [ebp-4]
    add DWORD PTR [ebp-4], 034h
    mov esi, eax
    movsd
    movsd
    add ebx, 4
    dec DWORD PTR [ebp+8]
    movsd
    jnz short joint_loop

    pop edi
    pop esi
    pop ebx
    leave
    ret 4
?InitializeJointTransforms@GameManPose@@QAEXPAUGameMan@@@Z ENDP

END
