.686
.model flat
option casemap:none

EXTERN _Direct3DCreate9:PROC
EXTERN _realloc:PROC
EXTERN ?FindGameAdapter@@YAHPBU_GUID@@PAUIDirect3D9@@@Z:PROC
EXTERN ?g_gameDisplayModes@@3PAUGameDisplayMode@@A:DWORD

.code

; FUNCTION: SUMO 0x00403a86
; FUNCTION: EDITOR 0x00403a86
PUBLIC _EnumerateGameDisplayModes
_EnumerateGameDisplayModes PROC
    push ebp
    mov ebp, esp
    sub esp, 038h
    push ebx
    push esi
    push edi
    push 020h
    call _Direct3DCreate9
    push 016h
    mov esi, eax
    pop eax
    xor ebx, ebx
    xor edi, edi
    cmp dword ptr [ebp + 8], ebx
    mov dword ptr [ebp - 038h], eax
    mov dword ptr [ebp - 034h], 015h
    mov dword ptr [ebp - 030h], eax
    mov dword ptr [ebp - 02ch], 014h
    mov dword ptr [ebp - 028h], 017h
    jnz adapterRequested
    mov dword ptr [ebp - 004h], ebx
    jmp probeFormat
adapterRequested:
    push esi
    push dword ptr [ebp + 8]
    call ?FindGameAdapter@@YAHPBU_GUID@@PAUIDirect3D9@@@Z
    pop ecx
    pop ecx
    mov dword ptr [ebp - 004h], eax
probeFormat:
    push dword ptr [ebp + edi*4 - 038h]
    mov eax, dword ptr [esi]
    push dword ptr [ebp - 004h]
    push esi
    call dword ptr [eax + 018h]
    inc edi
    cmp eax, ebx
    mov dword ptr [ebp - 010h], eax
    jnz formatsReady
    cmp edi, 5
    jb probeFormat
formatsReady:
    shl eax, 4
    push eax
    push dword ptr [?g_gameDisplayModes@@3PAUGameDisplayMode@@A]
    dec edi
    call _realloc
    pop ecx
    pop ecx
    xor ecx, ecx
    cmp dword ptr [ebp - 010h], ecx
    mov dword ptr [?g_gameDisplayModes@@3PAUGameDisplayMode@@A], eax
    mov dword ptr [ebp - 008h], ebx
    mov dword ptr [ebp - 00ch], ecx
    mov dword ptr [ebp + 008h], ecx
    jle enumerationDone
    mov eax, dword ptr [ebp + edi*4 - 038h]
    mov dword ptr [ebp - 014h], eax
    xor edi, edi
enumerateMode:
    mov eax, dword ptr [esi]
    lea ecx, [ebp - 024h]
    push ecx
    push dword ptr [ebp + 008h]
    push dword ptr [ebp - 014h]
    push dword ptr [ebp - 004h]
    push esi
    call dword ptr [eax + 01ch]
    mov ecx, dword ptr [ebp - 018h]
    mov eax, dword ptr [?g_gameDisplayModes@@3PAUGameDisplayMode@@A]
    xor edx, edx
    sub ecx, 014h
    jz depth24
    dec ecx
    dec ecx
    jz depth32
    dec ecx
    jz nextMode
    dec ecx
    jz nextMode
    jmp validateStoredFormat
depth32:
    push 020h
    pop edx
    jmp acceptStoredFormat
depth24:
    push 018h
    pop edx
validateStoredFormat:
    cmp dword ptr [ebp - 018h], 016h
    jz acceptStoredFormat
    cmp dword ptr [ebp - 018h], 015h
    jnz nextMode
acceptStoredFormat:
    cmp ebx, dword ptr [ebp - 024h]
    jnz storeMode
    mov ecx, dword ptr [ebp - 00ch]
    cmp ecx, dword ptr [ebp - 020h]
    jz nextMode
storeMode:
    inc dword ptr [ebp - 008h]
    db 08dh, 00ch, 007h
    mov dword ptr [ecx + 008h], edx
    mov edx, dword ptr [ebp - 024h]
    mov dword ptr [ecx], edx
    mov edx, dword ptr [ebp - 020h]
    mov dword ptr [ecx + 004h], edx
    mov edx, dword ptr [ebp - 01ch]
    mov dword ptr [ecx + 00ch], edx
    mov ecx, dword ptr [ebp - 020h]
    mov ebx, dword ptr [ebp - 024h]
    mov dword ptr [ebp - 00ch], ecx
    add edi, 010h
nextMode:
    inc dword ptr [ebp + 008h]
    mov ecx, dword ptr [ebp + 008h]
    cmp ecx, dword ptr [ebp - 010h]
    jl enumerateMode
enumerationDone:
    mov ecx, dword ptr [ebp + 00ch]
    mov dword ptr [ecx], eax
    mov eax, dword ptr [ebp + 010h]
    mov ecx, dword ptr [ebp - 008h]
    mov dword ptr [eax], ecx
    mov eax, dword ptr [esi]
    push esi
    call dword ptr [eax + 008h]
    pop edi
    pop esi
    pop ebx
    leave
    ret
_EnumerateGameDisplayModes ENDP

END
