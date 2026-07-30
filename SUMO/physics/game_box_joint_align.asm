.386
.model flat
option casemap:none

EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC

.code

; FUNCTION: SUMO 0x0040e690
; FUNCTION: EDITOR 0x0040e6b2
PUBLIC ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 024h
    mov eax, [ebp+0Ch]
    push ebx
    mov ebx, [ebp+8]
    push esi
    mov esi, [ebx+eax*4]
    push edi
    mov ecx, eax
    xor ecx, 1
    mov edi, [ebx+ecx*4]
    mov [ebp+8], ecx
    push 9
    pop ecx
    add esi, 060h
    add edi, 060h
    rep movsd

    mov ecx, [ebx+eax*4]
    lea edx, [ecx+084h]
    push edx
    lea edx, [ebp-0Ch]
    add ecx, 060h
    push edx
    push ecx
    lea ecx, [ebp-018h]
    lea eax, [eax+eax*2]
    push ecx
    lea ecx, [ebx+eax*4+8]
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    mov ecx, eax
    call ??HVector3@@QAE?AU0@AAU0@@Z

    mov eax, [ebp+8]
    mov edi, [ebx+eax*4]
    lea eax, [eax+eax*2]
    lea eax, [ebx+eax*4+8]
    push eax
    lea eax, [ebp-018h]
    push eax
    lea ecx, [edi+060h]
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    push eax
    lea eax, [ebp-024h]
    push eax
    lea ecx, [ebp-0Ch]
    call ??GVector3@@QAE?AU0@AAU0@@Z

    add edi, 084h
    mov esi, eax
    movsd
    movsd
    movsd
    pop edi
    pop esi
    pop ebx
    leave
    ret
?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z ENDP

END
