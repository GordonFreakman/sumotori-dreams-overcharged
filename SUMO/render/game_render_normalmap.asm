.686
.model flat
option casemap:none

EXTERN ??2@YAPAXI@Z:PROC
EXTERN ??3@YAXPAX@Z:PROC
EXTERN _sqrt:PROC
EXTERN __ftol2:PROC
EXTERN ?CreateGameTextureFromPixels@@YAHPAXHHH@Z:PROC

.code

PUBLIC ?CreateGameNormalMapTexture@@YAHPAEHHH@Z
?CreateGameNormalMapTexture@@YAHPAEHHH@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 28h
    push ebx
    mov ebx, dword ptr [ebp + 10h]
    push esi
    push edi
    mov edi, dword ptr [ebp + 0ch]
    mov eax, edi
    imul eax, ebx
    shl eax, 2
    push eax
    call ??2@YAPAXI@Z
    pop ecx
    lea ecx, [ebx - 1]
    imul ecx, edi
    mov esi, eax
    mov eax, dword ptr [ebp + 8]
    lea edx, [eax + ecx * 4]
    mov dword ptr [ebp + 8], eax
    mov eax, dword ptr [ebp + 14h]
    imul eax, eax
    cmp dword ptr [ebp + 14h], 0
    mov dword ptr [ebp - 10h], esi
    mov dword ptr [ebp - 4], 2
    mov dword ptr [ebp - 18h], eax
    jge normalScaleReady
    mov dword ptr [ebp - 4], -2
normalScaleReady:
    test ebx, ebx
    jle normalRowsComplete
    mov eax, edi
    shl eax, 2
    mov dword ptr [ebp - 0ch], ebx
normalRow:
    test edi, edi
    mov ebx, dword ptr [ebp + 8]
    db 08dh, 04ch, 018h, 0fch
    jle normalColumnsComplete
    mov eax, dword ptr [ebp + 14h]
    fild dword ptr [ebp - 4]
    shl eax, 8
    sub edx, ebx
    fstp dword ptr [ebp - 20h]
    mov dword ptr [ebp - 28h], eax
    mov dword ptr [ebp - 14h], edx
    mov dword ptr [ebp - 8], edi
    jmp normalColumnEntry
normalColumn:
    mov edx, dword ptr [ebp - 14h]
normalColumnEntry:
    movzx ecx, byte ptr [ecx]
    movzx eax, byte ptr [ebx]
    mov edi, eax
    sub edi, ecx
    db 00fh, 0b6h, 00ch, 01ah
    sub eax, ecx
    mov ecx, eax
    imul ecx, eax
    add ecx, dword ptr [ebp - 18h]
    mov dword ptr [ebp - 24h], eax
    mov eax, edi
    imul eax, edi
    add eax, ecx
    mov dword ptr [ebp - 1ch], eax
    push ecx
    push ecx
    fild dword ptr [ebp - 1ch]
    fstp qword ptr [esp]
    call _sqrt
    fmul dword ptr [ebp - 20h]
    pop ecx
    pop ecx
    call __ftol2
    mov ecx, eax
    mov eax, edi
    shl eax, 8
    cdq
    idiv ecx
    add al, 7fh
    mov byte ptr [esi], al
    mov eax, dword ptr [ebp - 24h]
    shl eax, 8
    cdq
    idiv ecx
    inc esi
    add al, 7fh
    mov byte ptr [esi], al
    mov eax, dword ptr [ebp - 28h]
    cdq
    idiv ecx
    inc esi
    mov ecx, ebx
    add ebx, 4
    add al, 7fh
    mov byte ptr [esi], al
    inc esi
    mov byte ptr [esi], 0
    inc esi
    dec dword ptr [ebp - 8]
    jne normalColumn
    mov edi, dword ptr [ebp + 0ch]
normalColumnsComplete:
    mov edx, dword ptr [ebp + 8]
    mov eax, edi
    shl eax, 2
    add dword ptr [ebp + 8], eax
    dec dword ptr [ebp - 0ch]
    jne normalRow
    mov ebx, dword ptr [ebp + 10h]
normalRowsComplete:
    push 0
    push ebx
    push edi
    push dword ptr [ebp - 10h]
    call ?CreateGameTextureFromPixels@@YAHPAXHHH@Z
    push dword ptr [ebp - 10h]
    mov esi, eax
    call ??3@YAXPAX@Z
    add esp, 14h
    pop edi
    mov eax, esi
    pop esi
    pop ebx
    leave
    ret
?CreateGameNormalMapTexture@@YAHPAEHHH@Z ENDP

END
