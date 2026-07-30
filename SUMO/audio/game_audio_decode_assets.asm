.686
.model flat
option casemap:none

EXTERN ??2@YAPAXI@Z:PROC
EXTERN _acmStreamOpen@32:PROC
EXTERN _acmStreamPrepareHeader@12:PROC
EXTERN _acmStreamConvert@12:PROC
EXTERN @__security_check_cookie@4:PROC
EXTERN ___security_cookie:DWORD

EXTERN ?g_gameSoundSources@@3PAPAEA:DWORD
EXTERN ?g_gameSoundSlots@@3PAEA:BYTE
EXTERN ?g_gameDirectSound@@3PAUIDirectSound8@@A:DWORD
EXTERN ?g_gameUsePrimaryBuffer@@3HA:DWORD
EXTERN ?g_gameNullGuid@@3U_GUID@@B:BYTE
EXTERN ?g_gameTimeScaleDenominator@@3IA:DWORD

.code

; FUNCTION: SUMO 0x004153d2
; FUNCTION: EDITOR 0x004153f4
PUBLIC ?DecodeGameSoundAssets@@YAEXZ
?DecodeGameSoundAssets@@YAEXZ PROC
    push ebp
    lea ebp, [esp - 078h]
    sub esp, 0cch
    mov eax, dword ptr [___security_cookie]
    push ebx
    xor ebx, ebx
    cmp dword ptr [?g_gameSoundSources@@3PAPAEA], ebx
    push esi
    mov dword ptr [ebp + 074h], eax
    push edi
    mov dword ptr [ebp + 04ch], OFFSET ?g_gameSoundSources@@3PAPAEA
    jz decodeSucceeded
    mov dword ptr [ebp + 044h], OFFSET ?g_gameSoundSlots@@3PAEA
decodeNext:
    mov eax, dword ptr [ebp + 04ch]
    mov esi, dword ptr [eax]
    mov edi, 10000h
    push edi
    call ??2@YAPAXI@Z
    pop ecx
    mov ecx, dword ptr [esi + 038h]
    mov dword ptr [ebp - 024h], eax
    mov dword ptr [ebp + 020h], eax
    lea eax, [esi + 014h]
    lea edx, [esi + 03ch]
    mov dword ptr [ebp - 034h], edx
    mov dword ptr [ebp - 030h], ecx
    mov dword ptr [ebp - 040h], 054h
    mov dword ptr [ebp - 03ch], ebx
    mov dword ptr [ebp - 038h], ebx
    mov dword ptr [ebp - 02ch], ebx
    mov dword ptr [ebp - 028h], ebx
    mov dword ptr [ebp - 020h], edi
    mov dword ptr [ebp - 01ch], ebx
    mov dword ptr [ebp - 018h], ebx
    mov word ptr [ebp + 038h], bx
    mov word ptr [ebp + 028h], 1
    mov cx, word ptr [eax + 2]
    mov word ptr [ebp + 02ah], cx
    mov ecx, dword ptr [eax + 4]
    mov dword ptr [ebp + 02ch], ecx
    mov edx, dword ptr [ebp + 02ah]
    push 4
    add edx, edx
    push ebx
    mov word ptr [ebp + 034h], dx
    movzx edx, dx
    push ebx
    imul edx, ecx
    push ebx
    lea ecx, [ebp + 028h]
    push ecx
    push eax
    push ebx
    lea eax, [ebp + 03ch]
    push eax
    mov word ptr [ebp + 036h], 010h
    mov dword ptr [ebp + 030h], edx
    call _acmStreamOpen@32
    test eax, eax
    jnz decodeFailed
    push ebx
    lea eax, [ebp - 040h]
    push eax
    push dword ptr [ebp + 03ch]
    call _acmStreamPrepareHeader@12
    test eax, eax
    jnz decodeFailed
    push 030h
    lea eax, [ebp - 040h]
    push eax
    push dword ptr [ebp + 03ch]
    call _acmStreamConvert@12
    test eax, eax
    jnz decodeFailed
    mov ecx, dword ptr [ebp + 02ch]
    mov eax, dword ptr [ebp - 01ch]
    lea esi, [ebp + 028h]
    lea edi, [ebp - 054h]
    movsd
    movsd
    movsd
    mov dword ptr [ebp + 018h], ecx
    xor ecx, ecx
    cmp dword ptr [?g_gameUsePrimaryBuffer@@3HA], ebx
    movsd
    setz cl
    movsw
    mov dword ptr [ebp + 058h], eax
    mov dword ptr [ebp + 040h], eax
    mov dword ptr [ebp + 050h], 024h
    mov dword ptr [ebp + 05ch], ebx
    lea ecx, [ecx*4 + 100b4h]
    mov dword ptr [ebp + 054h], ecx
    lea eax, [ebp - 054h]
    mov dword ptr [ebp + 060h], eax
    mov eax, dword ptr [?g_gameDirectSound@@3PAUIDirectSound8@@A]
    mov esi, OFFSET ?g_gameNullGuid@@3U_GUID@@B
    lea edi, [ebp + 064h]
    movsd
    movsd
    movsd
    movsd
    mov esi, dword ptr [ebp + 044h]
    mov ecx, dword ptr [eax]
    push ebx
    push esi
    lea edx, [ebp + 050h]
    push edx
    push eax
    call dword ptr [ecx + 00ch]
    cmp eax, ebx
    jnz decodeFailed
    mov eax, dword ptr [esi]
    mov ecx, dword ptr [eax]
    push 2
    lea edx, [ebp + 024h]
    push edx
    lea edx, [ebp + 014h]
    push edx
    lea edx, [ebp + 01ch]
    push edx
    lea edx, [ebp + 048h]
    push edx
    push ebx
    push ebx
    push eax
    call dword ptr [ecx + 02ch]
    xor eax, eax
    cmp dword ptr [ebp + 040h], ebx
    jle copyComplete
copyPcm:
    mov ecx, dword ptr [ebp + 020h]
    db 08ah, 00ch, 008h
    mov edx, dword ptr [ebp + 048h]
    db 088h, 00ch, 010h
    inc eax
    cmp eax, dword ptr [ebp + 040h]
    jl copyPcm
copyComplete:
    push dword ptr [ebp + 024h]
    mov eax, dword ptr [esi]
    push dword ptr [ebp + 014h]
    mov ecx, dword ptr [eax]
    push dword ptr [ebp + 01ch]
    push dword ptr [ebp + 048h]
    push eax
    call dword ptr [ecx + 04ch]
    xor eax, eax
    push 077h
    lea edi, [esi + 4]
    pop ecx
    rep stosd
    mov eax, dword ptr [ebp + 018h]
    cdq
    idiv dword ptr [?g_gameTimeScaleDenominator@@3IA]
    add dword ptr [ebp + 04ch], 4
    mov dword ptr [esi + 1e0h], ebx
    add esi, 1e8h
    mov dword ptr [ebp + 044h], esi
    mov dword ptr [esi - 1ech], eax
    mov eax, dword ptr [ebp + 04ch]
    cmp dword ptr [eax], ebx
    jnz decodeNext
decodeSucceeded:
    mov al, 1
decodeReturn:
    mov ecx, dword ptr [ebp + 074h]
    pop edi
    pop esi
    pop ebx
    call @__security_check_cookie@4
    add ebp, 078h
    leave
    ret
decodeFailed:
    xor al, al
    jmp decodeReturn
?DecodeGameSoundAssets@@YAEXZ ENDP

END
