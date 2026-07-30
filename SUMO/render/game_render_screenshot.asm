.686
.model flat
option casemap:none

EXTERN _sprintf:PROC
EXTERN _fopen:PROC
EXTERN _fclose:PROC
EXTERN _memcpy:PROC
EXTERN _fwrite:PROC
EXTERN ??3@YAXPAX@Z:PROC
EXTERN ??2@YAPAXI@Z:PROC
EXTERN @__security_check_cookie@4:PROC
EXTERN ___security_cookie:DWORD

EXTERN ?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A:DWORD
EXTERN ?g_gameConfiguredWidth@@3HA:DWORD
EXTERN ?g_gameConfiguredHeight@@3HA:DWORD
EXTERN ?g_gameScreenshotPrefix@@3PADA:DWORD
EXTERN ?g_gameScreenshotIndex@@3HA:DWORD
EXTERN ?g_gameScreenshotFormat@@3QBDB:BYTE
EXTERN ?g_gameScreenshotReadMode@@3QBDB:BYTE
EXTERN ?g_gameScreenshotWriteMode@@3QBDB:BYTE

.code

; FUNCTION: SUMO 0x00414f09
; FUNCTION: EDITOR 0x00414f2b
PUBLIC ?WriteGameScreenshot@@YAHXZ
?WriteGameScreenshot@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 0160h
    mov eax, dword ptr [___security_cookie]
    push ebx
    mov dword ptr [ebp - 004h], eax
    push esi
    xor ebx, ebx
findUnusedName:
    push dword ptr [?g_gameScreenshotIndex@@3HA]
    lea eax, [ebp - 0140h]
    push dword ptr [?g_gameScreenshotPrefix@@3PADA]
    push OFFSET ?g_gameScreenshotFormat@@3QBDB
    push eax
    call _sprintf
    lea eax, [ebp - 0140h]
    push OFFSET ?g_gameScreenshotReadMode@@3QBDB
    push eax
    call _fopen
    mov esi, eax
    add esp, 018h
    cmp esi, ebx
    jz unusedNameFound
    push esi
    call _fclose
    pop ecx
unusedNameFound:
    inc dword ptr [?g_gameScreenshotIndex@@3HA]
    cmp esi, ebx
    jnz findUnusedName

    mov eax, dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    mov ecx, dword ptr [eax]
    lea edx, [ebp - 0150h]
    push edx
    push ebx
    push ebx
    push ebx
    push eax
    call dword ptr [ecx + 048h]
    test eax, eax
    jl releaseSurface

    mov eax, dword ptr [?g_gameConfiguredHeight@@3HA]
    imul eax, dword ptr [?g_gameConfiguredWidth@@3HA]
    shl eax, 2
    push edi
    push eax
    call ??2@YAPAXI@Z
    pop ecx
    push ebx
    push ebx
    lea edx, [ebp - 0160h]
    mov dword ptr [ebp - 0148h], eax
    mov eax, dword ptr [ebp - 0150h]
    mov ecx, dword ptr [eax]
    push edx
    push eax
    call dword ptr [ecx + 034h]

    mov eax, dword ptr [?g_gameConfiguredHeight@@3HA]
    imul eax, dword ptr [ebp - 0160h]
    cdq
    push 4
    pop ecx
    idiv ecx
    shl eax, 2
    push eax
    call ??2@YAPAXI@Z
    mov ecx, dword ptr [?g_gameConfiguredHeight@@3HA]
    imul ecx, dword ptr [ebp - 0160h]
    push ecx
    push dword ptr [ebp - 015ch]
    mov dword ptr [ebp - 0158h], eax
    push eax
    call _memcpy
    mov eax, dword ptr [ebp - 0150h]
    mov ecx, dword ptr [eax]
    add esp, 010h
    push eax
    call dword ptr [ecx + 038h]

    mov esi, dword ptr [?g_gameConfiguredHeight@@3HA]
    cmp esi, ebx
    mov ecx, dword ptr [?g_gameConfiguredWidth@@3HA]
    mov dword ptr [ebp - 0154h], ecx
    mov dword ptr [ebp - 0144h], ebx
    jle rowsCopied
    lea eax, [esi - 1]
    mov dword ptr [ebp - 014ch], eax
    jmp copyRow
nextRow:
    mov ecx, dword ptr [?g_gameConfiguredWidth@@3HA]
copyRow:
    mov eax, ecx
    imul ecx, dword ptr [ebp - 0144h]
    shl eax, 2
    push eax
    mov eax, dword ptr [ebp - 014ch]
    imul eax, dword ptr [ebp - 0160h]
    cdq
    push 4
    pop edi
    idiv edi
    mov edx, dword ptr [ebp - 0158h]
    lea eax, [edx + eax * 4]
    push eax
    mov eax, dword ptr [ebp - 0148h]
    lea eax, [eax + ecx * 4]
    push eax
    call _memcpy
    add esp, 00ch
    inc dword ptr [ebp - 0144h]
    dec dword ptr [ebp - 014ch]
    cmp dword ptr [ebp - 0144h], esi
    jl nextRow
rowsCopied:
    mov ax, word ptr [ebp - 0154h]
    mov word ptr [ebp - 02ah], ax
    lea eax, [ebp - 0140h]
    push OFFSET ?g_gameScreenshotWriteMode@@3QBDB
    push eax
    mov byte ptr [ebp - 03ch], 042h
    mov byte ptr [ebp - 03bh], 04dh
    mov byte ptr [ebp - 03ah], 036h
    mov byte ptr [ebp - 039h], 030h
    mov byte ptr [ebp - 038h], bl
    mov byte ptr [ebp - 037h], bl
    mov byte ptr [ebp - 036h], bl
    mov byte ptr [ebp - 035h], bl
    mov byte ptr [ebp - 034h], bl
    mov byte ptr [ebp - 033h], bl
    mov byte ptr [ebp - 032h], 036h
    mov byte ptr [ebp - 031h], bl
    mov byte ptr [ebp - 030h], bl
    mov byte ptr [ebp - 02fh], bl
    mov byte ptr [ebp - 02eh], 028h
    mov byte ptr [ebp - 02dh], bl
    mov byte ptr [ebp - 02ch], bl
    mov byte ptr [ebp - 02bh], bl
    mov byte ptr [ebp - 028h], bl
    mov byte ptr [ebp - 027h], bl
    mov byte ptr [ebp - 024h], bl
    mov byte ptr [ebp - 023h], bl
    mov byte ptr [ebp - 022h], 1
    mov byte ptr [ebp - 021h], bl
    mov byte ptr [ebp - 020h], 020h
    mov byte ptr [ebp - 01fh], bl
    mov byte ptr [ebp - 01eh], bl
    mov byte ptr [ebp - 01dh], bl
    mov byte ptr [ebp - 01ch], bl
    mov byte ptr [ebp - 01bh], bl
    mov byte ptr [ebp - 01ah], bl
    mov byte ptr [ebp - 019h], 01eh
    mov byte ptr [ebp - 018h], bl
    mov byte ptr [ebp - 017h], bl
    mov byte ptr [ebp - 016h], 0c6h
    mov byte ptr [ebp - 015h], 011h
    mov byte ptr [ebp - 014h], bl
    mov byte ptr [ebp - 013h], bl
    mov byte ptr [ebp - 012h], 0c6h
    mov byte ptr [ebp - 011h], 011h
    mov byte ptr [ebp - 010h], bl
    mov byte ptr [ebp - 00fh], bl
    mov byte ptr [ebp - 00eh], bl
    mov byte ptr [ebp - 00dh], bl
    mov byte ptr [ebp - 00ch], bl
    mov byte ptr [ebp - 00bh], bl
    mov byte ptr [ebp - 00ah], bl
    mov byte ptr [ebp - 009h], bl
    mov byte ptr [ebp - 008h], bl
    mov byte ptr [ebp - 007h], bl
    mov word ptr [ebp - 026h], si
    call _fopen
    mov edi, eax
    push edi
    push 036h
    lea eax, [ebp - 03ch]
    push 1
    push eax
    call _fwrite
    imul esi, dword ptr [ebp - 0154h]
    push edi
    shl esi, 2
    push esi
    push 1
    push dword ptr [ebp - 0148h]
    call _fwrite
    push edi
    call _fclose
    push dword ptr [ebp - 0158h]
    call ??3@YAXPAX@Z
    push dword ptr [ebp - 0148h]
    call ??3@YAXPAX@Z
    add esp, 034h
    pop edi
releaseSurface:
    mov eax, dword ptr [ebp - 0150h]
    mov ecx, dword ptr [eax]
    push eax
    call dword ptr [ecx + 8]
    mov ecx, dword ptr [ebp - 004h]
    pop esi
    pop ebx
    call @__security_check_cookie@4
    leave
    ret
?WriteGameScreenshot@@YAHXZ ENDP

END
