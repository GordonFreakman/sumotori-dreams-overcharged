.686
.model flat
option casemap:none

EXTERN _memset:PROC
EXTERN _strlen:PROC
EXTERN __imp__CreateCompatibleDC@4:DWORD
EXTERN __imp__CreateDIBSection@24:DWORD
EXTERN __imp__SetMapMode@8:DWORD
EXTERN __imp__GetDeviceCaps@8:DWORD
EXTERN __imp__MulDiv@12:DWORD
EXTERN __imp__CreateFontA@56:DWORD
EXTERN __imp__SelectObject@8:DWORD
EXTERN __imp__SetTextColor@8:DWORD
EXTERN __imp__SetBkColor@8:DWORD
EXTERN __imp__SetTextAlign@8:DWORD
EXTERN __imp__ExtTextOutA@32:DWORD

.code

PUBLIC ?BlendTextIntoTexture@@YAHPAEPBDHHHHHHHH1@Z
?BlendTextIntoTexture@@YAHPAEPBDHHHHHHHH1@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 38h
    push ebx
    push esi
    push edi
    push 28h
    pop edi
    push edi
    xor esi, esi
    lea eax, [ebp - 38h]
    push esi
    push eax
    call _memset
    mov eax, dword ptr [ebp + 1ch]
    mov dword ptr [ebp - 34h], eax
    mov eax, dword ptr [ebp + 20h]
    add esp, 0ch
    neg eax
    push esi
    mov dword ptr [ebp - 38h], edi
    mov dword ptr [ebp - 30h], eax
    mov word ptr [ebp - 2ch], 1
    mov dword ptr [ebp - 28h], esi
    mov word ptr [ebp - 2ah], 20h
    call dword ptr [__imp__CreateCompatibleDC@4]
    push esi
    mov edi, eax
    push esi
    lea eax, [ebp - 8]
    push eax
    push esi
    lea eax, [ebp - 38h]
    push eax
    push edi
    call dword ptr [__imp__CreateDIBSection@24]
    push 1
    push edi
    mov ebx, eax
    call dword ptr [__imp__SetMapMode@8]
    push 48h
    push 5ah
    push edi
    call dword ptr [__imp__GetDeviceCaps@8]
    push eax
    push dword ptr [ebp + 24h]
    call dword ptr [__imp__MulDiv@12]
    push dword ptr [ebp + 30h]
    push 2
    push 4
    push esi
    push esi
    push 1
    push esi
    push esi
    push esi
    push 2bch
    push esi
    push esi
    push esi
    push eax
    call dword ptr [__imp__CreateFontA@56]
    cmp eax, esi
    mov dword ptr [ebp - 4], eax
    je textBlendComplete
    push ebx
    mov ebx, dword ptr [__imp__SelectObject@8]
    push edi
    call ebx
    push dword ptr [ebp - 4]
    push edi
    call ebx
    mov eax, dword ptr [ebp + 28h]
    mov ebx, 0ffffffh
    xor eax, ebx
    push eax
    push edi
    call dword ptr [__imp__SetTextColor@8]
    mov eax, dword ptr [ebp + 2ch]
    xor eax, ebx
    push eax
    push edi
    call dword ptr [__imp__SetBkColor@8]
    push esi
    push edi
    call dword ptr [__imp__SetTextAlign@8]
    push esi
    push dword ptr [ebp + 0ch]
    call _strlen
    pop ecx
    push eax
    push dword ptr [ebp + 0ch]
    push esi
    push 2
    push esi
    push esi
    push edi
    call dword ptr [__imp__ExtTextOutA@32]
    mov eax, dword ptr [ebp + 14h]
    mov ecx, dword ptr [ebp + 18h]
    mov edx, dword ptr [ebp + 8]
    imul eax, ecx
    add eax, dword ptr [ebp + 10h]
    mov edi, dword ptr [ebp - 8]
    lea eax, [edx + eax * 4]
    mov edx, dword ptr [ebp + 20h]
    cmp edx, esi
    jle textBlendComplete
    sub ecx, dword ptr [ebp + 1ch]
    mov dword ptr [ebp - 4], edx
    shl ecx, 2
    mov dword ptr [ebp - 0ch], ecx
textBlendRow:
    mov ecx, dword ptr [ebp + 1ch]
    cmp ecx, esi
    jle textBlendNextRow
    mov dword ptr [ebp + 20h], ecx
textBlendPixel:
    movzx edx, byte ptr [edi]
    mov ecx, 0ffh
    mov ebx, ecx
    sub ebx, edx
    movzx edx, byte ptr [eax]
    imul ebx, edx
    shr ebx, 8
    mov byte ptr [eax], bl
    movzx edx, byte ptr [edi + 1]
    mov ebx, ecx
    sub ebx, edx
    movzx edx, byte ptr [eax + 1]
    imul ebx, edx
    shr ebx, 8
    mov byte ptr [eax + 1], bl
    movzx edx, byte ptr [edi + 2]
    sub ecx, edx
    movzx edx, byte ptr [eax + 2]
    imul ecx, edx
    shr ecx, 8
    mov byte ptr [eax + 2], cl
    movzx edx, byte ptr [edi + 2]
    mov ebx, 0ffh
    sub ebx, edx
    movzx ecx, cl
    imul ebx, ecx
    shr ebx, 8
    mov byte ptr [eax + 3], bl
    add edi, 4
    add eax, 4
    dec dword ptr [ebp + 20h]
    jne textBlendPixel
textBlendNextRow:
    add eax, dword ptr [ebp - 0ch]
    dec dword ptr [ebp - 4]
    jne textBlendRow
textBlendComplete:
    pop edi
    pop esi
    xor eax, eax
    pop ebx
    leave
    ret
?BlendTextIntoTexture@@YAHPAEPBDHHHHHHHH1@Z ENDP

END
