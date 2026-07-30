.686
.model flat
option casemap:none

EXTERN __ftol2:PROC
EXTERN _log:PROC
EXTERN ?ReleaseNextQueuedRenderResource@@YAIXZ:PROC
EXTERN ?ReplayRecordCommand@@YAXHHHH@Z:PROC

EXTERN ?g_gameSoundInitialized@@3HA:DWORD
EXTERN ?g_gameDirectSound@@3PAUIDirectSound8@@A:DWORD
EXTERN ?g_deferredReleaseWriteIndex@@3HA:DWORD
EXTERN ?g_deferredReleaseSlots@@3PAPAPAUIDirect3DResource9@@A:DWORD
EXTERN ?g_gameActiveSoundSlots@@3PAPAPAUIDirectSoundBuffer@@A:DWORD
EXTERN ?g_gameSoundSlotFrequency0@@3HA:DWORD
EXTERN ?g_gameSoundLogBase@@3NB:QWORD
EXTERN ?g_gameSoundVolumeScale@@3MB:DWORD

.code

; FUNCTION: SUMO 0x004151f4
; FUNCTION: EDITOR 0x00415216
PUBLIC ?PlaySound@GameSoundSlot@@QAEPAXMMH@Z
?PlaySound@GameSoundSlot@@QAEPAXMMH@Z PROC
    push ebp
    mov ebp, esp
    push ecx
    push esi
    push edi
    xor edi, edi
    cmp dword ptr [?g_gameSoundInitialized@@3HA], edi
    mov esi, ecx
    jnz soundReady
    xor eax, eax
    jmp playbackDone
soundReady:
    mov dword ptr [esi + 01e4h], edi
scanClone:
    mov eax, dword ptr [esi + 01e4h]
    lea eax, [esi + eax * 4 + 4]
    cmp dword ptr [eax], edi
    jz cloneScanDone
    mov eax, dword ptr [eax]
    mov ecx, dword ptr [eax]
    lea edx, [ebp - 4]
    push edx
    push eax
    call dword ptr [ecx + 024h]
    test byte ptr [ebp - 4], 1
    jz cloneScanDone
    inc dword ptr [esi + 01e4h]
    cmp dword ptr [esi + 01e4h], 078h
    jl scanClone
cloneScanDone:
    cmp dword ptr [esi + 01e4h], 078h
    jnz ensureClone
    mov dword ptr [esi + 01e4h], edi
    jmp ensureClone
duplicateClone:
    mov edx, dword ptr [esi + 01e4h]
    mov eax, dword ptr [?g_gameDirectSound@@3PAUIDirectSound8@@A]
    mov ecx, dword ptr [eax]
    lea edx, [esi + edx * 4 + 4]
    push edx
    push dword ptr [esi + 4]
    push eax
    call dword ptr [ecx + 014h]
    test eax, eax
    jz queueClone
    call ?ReleaseNextQueuedRenderResource@@YAIXZ
    jmp ensureClone
queueClone:
    mov eax, dword ptr [esi + 01e4h]
    lea ecx, [esi + eax * 4 + 4]
    mov eax, dword ptr [?g_deferredReleaseWriteIndex@@3HA]
    mov dword ptr [?g_deferredReleaseSlots@@3PAPAPAUIDirect3DResource9@@A + eax * 4], ecx
    inc eax
    and eax, 03ffh
    mov dword ptr [?g_deferredReleaseWriteIndex@@3HA], eax
ensureClone:
    mov eax, dword ptr [esi + 01e4h]
    cmp dword ptr [esi + eax * 4 + 4], edi
    jz duplicateClone
    lea eax, [esi + eax * 4 + 4]
    cmp dword ptr [eax], edi
    jz advanceClone

    fild dword ptr [esi]
    mov edi, dword ptr [eax]
    push ebx
    mov ebx, dword ptr [edi]
    fmul dword ptr [ebp + 8]
    call __ftol2
    push eax
    push edi
    call dword ptr [ebx + 044h]

    fld qword ptr [?g_gameSoundLogBase@@3NB]
    push ecx
    push ecx
    fstp qword ptr [esp]
    call _log
    mov eax, dword ptr [esi + 01e4h]
    mov eax, dword ptr [esi + eax * 4 + 4]
    mov edi, dword ptr [eax]
    fstp dword ptr [ebp + 8]
    fld dword ptr [ebp + 0ch]
    fstp qword ptr [esp]
    call _log
    fdiv dword ptr [ebp + 8]
    pop ecx
    pop ecx
    fmul dword ptr [?g_gameSoundVolumeScale@@3MB]
    call __ftol2
    push eax
    mov eax, dword ptr [esi + 01e4h]
    push dword ptr [esi + eax * 4 + 4]
    call dword ptr [edi + 03ch]
    mov eax, dword ptr [esi + 01e4h]
    mov eax, dword ptr [esi + eax * 4 + 4]
    mov ecx, dword ptr [eax]
    xor edi, edi
    push edi
    push eax
    call dword ptr [ecx + 034h]
    mov eax, dword ptr [esi + 01e4h]
    mov eax, dword ptr [esi + eax * 4 + 4]
    mov ecx, dword ptr [eax]
    push edi
    push edi
    push edi
    push eax
    call dword ptr [ecx + 030h]
    pop ebx
advanceClone:
    mov ecx, dword ptr [esi + 01e4h]
    lea eax, [esi + ecx * 4 + 4]
    inc ecx
    cmp ecx, 078h
    mov dword ptr [esi + 01e4h], ecx
    jnz recordChannel
    mov dword ptr [esi + 01e4h], edi
recordChannel:
    mov ecx, dword ptr [esi + 01e4h]
    mov edx, dword ptr [ebp + 010h]
    lea ecx, [esi + ecx * 4 + 4]
    mov dword ptr [?g_gameActiveSoundSlots@@3PAPAPAUIDirectSoundBuffer@@A + edx * 4], ecx
playbackDone:
    pop edi
    pop esi
    leave
    ret 0ch
?PlaySound@GameSoundSlot@@QAEPAXMMH@Z ENDP

; FUNCTION: SUMO 0x00415369
; FUNCTION: EDITOR 0x0041538b
PUBLIC ?PlayGameSound@@YAPAXHMMH@Z
?PlayGameSound@@YAPAXHMMH@Z PROC
    push ebp
    mov ebp, esp
    fld dword ptr [ebp + 010h]
    push esi
    mov esi, dword ptr [ebp + 014h]
    push esi
    push ecx
    push ecx
    fstp dword ptr [esp + 4]
    fld dword ptr [ebp + 00ch]
    fstp dword ptr [esp]
    push dword ptr [ebp + 8]
    call ?ReplayRecordCommand@@YAXHHHH@Z
    add esp, 010h
    test esi, esi
    jz dispatchSound
    lea eax, dword ptr [?g_gameActiveSoundSlots@@3PAPAPAUIDirectSoundBuffer@@A + esi * 4]
    mov ecx, dword ptr [eax]
    test ecx, ecx
    jz dispatchSound
    cmp dword ptr [ecx], 0
    jz dispatchSound
    mov eax, ecx
    mov eax, dword ptr [eax]
    mov ecx, dword ptr [eax]
    push eax
    call dword ptr [ecx + 048h]
dispatchSound:
    fld dword ptr [ebp + 010h]
    push esi
    push ecx
    push ecx
    mov ecx, dword ptr [ebp + 8]
    fstp dword ptr [esp + 4]
    fld dword ptr [ebp + 00ch]
    imul ecx, 01e8h
    fstp dword ptr [esp]
    add ecx, OFFSET ?g_gameSoundSlotFrequency0@@3HA
    call ?PlaySound@GameSoundSlot@@QAEPAXMMH@Z
    pop esi
    pop ebp
    ret
?PlayGameSound@@YAPAXHMMH@Z ENDP

END
