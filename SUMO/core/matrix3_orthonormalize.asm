.386
.model flat

EXTERN ?Row0@Matrix3@@QAE?AUVector3@@XZ:PROC
EXTERN ?Row1@Matrix3@@QAE?AUVector3@@XZ:PROC
EXTERN ?Row2@Matrix3@@QAE?AUVector3@@XZ:PROC
EXTERN ?Normalized@Vector3@@QAE?AU1@XZ:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC

.code

; FUNCTION: SUMO 0x004090a9
; FUNCTION: EDITOR 0x004090cb
PUBLIC ?Orthonormalize@Matrix3@@QAEXXZ
?Orthonormalize@Matrix3@@QAEXXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 30h
    push ebx
    push esi
    push edi
    lea eax, [ebp-18h]
    push eax
    lea eax, [ebp-24h]
    push eax
    mov ebx, ecx
    call ?Row0@Matrix3@@QAE?AUVector3@@XZ
    mov ecx, eax
    call ?Normalized@Vector3@@QAE?AU1@XZ
    mov esi, eax
    lea edi, [ebp-0Ch]
    movsd
    movsd
    movsd
    mov eax, [ebp-0Ch]
    mov [ebx], eax
    mov eax, [ebp-8]
    mov [ebx+4], eax
    mov eax, [ebp-4]
    mov [ebx+8], eax
    lea eax, [ebp-30h]
    push eax
    lea eax, [ebp-24h]
    push eax
    mov ecx, ebx
    call ?Row1@Matrix3@@QAE?AUVector3@@XZ
    mov ecx, eax
    call ?Normalized@Vector3@@QAE?AU1@XZ
    mov esi, eax
    lea edi, [ebp-0Ch]
    movsd
    movsd
    movsd
    mov eax, [ebp-0Ch]
    mov [ebx+0Ch], eax
    mov eax, [ebp-8]
    mov [ebx+10h], eax
    mov eax, [ebp-4]
    mov [ebx+14h], eax
    lea eax, [ebp-30h]
    push eax
    mov ecx, ebx
    call ?Row1@Matrix3@@QAE?AUVector3@@XZ
    push eax
    lea eax, [ebp-24h]
    push eax
    lea eax, [ebp-18h]
    push eax
    mov ecx, ebx
    call ?Row0@Matrix3@@QAE?AUVector3@@XZ
    mov ecx, eax
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    mov esi, eax
    lea edi, [ebp-0Ch]
    movsd
    movsd
    movsd
    mov eax, [ebp-0Ch]
    mov [ebx+18h], eax
    mov eax, [ebp-8]
    mov [ebx+1Ch], eax
    mov eax, [ebp-4]
    mov [ebx+20h], eax
    lea eax, [ebp-30h]
    push eax
    mov ecx, ebx
    call ?Row0@Matrix3@@QAE?AUVector3@@XZ
    push eax
    lea eax, [ebp-24h]
    push eax
    lea eax, [ebp-18h]
    push eax
    mov ecx, ebx
    call ?Row2@Matrix3@@QAE?AUVector3@@XZ
    mov ecx, eax
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    mov esi, eax
    lea edi, [ebp-0Ch]
    movsd
    movsd
    movsd
    mov eax, [ebp-0Ch]
    mov [ebx+0Ch], eax
    mov eax, [ebp-8]
    mov [ebx+10h], eax
    mov eax, [ebp-4]
    pop edi
    pop esi
    mov [ebx+14h], eax
    pop ebx
    leave
    ret
?Orthonormalize@Matrix3@@QAEXXZ ENDP

END
