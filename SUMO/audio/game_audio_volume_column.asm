.686
.model flat
option casemap:none

.code

; FUNCTION: SUMO 0x00417c7d
; FUNCTION: EDITOR 0x00417c9f
PUBLIC _ApplyTrackerVolumeColumn
_ApplyTrackerVolumeColumn PROC
    push ebp
    mov ebp, esp
    mov cl, byte ptr [ebp+0ch]
    cmp cl, 010h
    jb trackerVolumeSwitch
    cmp cl, 050h
    ja trackerVolumeSwitch
    mov eax, dword ptr [ebp+8]
    movzx ecx, cl
    sub ecx, 010h
    or byte ptr [eax+2], 2
    mov dword ptr [eax+010h], ecx
    pop ebp
    ret

trackerVolumeSwitch:
    movzx eax, cl
    mov edx, eax
    shr edx, 4
    add edx, -6
    cmp edx, 9
    ja trackerVolumeComplete
    jmp dword ptr trackerVolumeJumpTable[edx*4]

trackerVolumeDown:
    mov ecx, dword ptr [ebp+8]
    and eax, 0fh
    sub dword ptr [ecx+010h], eax
    jns trackerVolumeDirty
    and dword ptr [ecx+010h], 0
    jmp trackerVolumeDirty

trackerVolumeUp:
    mov ecx, dword ptr [ebp+8]
    and eax, 0fh
    add dword ptr [ecx+010h], eax
    mov edx, dword ptr [ecx+010h]
    push 040h
    pop eax
    cmp edx, eax
    jle trackerVolumeDirty
    mov dword ptr [ecx+010h], eax

trackerVolumeDirty:
    or byte ptr [ecx+2], 2
    pop ebp
    ret

trackerVibratoSpeed:
    mov eax, dword ptr [ebp+8]
    and cl, 0fh
    mov byte ptr [eax+086h], cl
    pop ebp
    ret

trackerVibratoDepth:
    mov eax, dword ptr [ebp+8]
    and cl, 0fh
    mov byte ptr [eax+087h], cl
    pop ebp
    ret

trackerPanningSet:
    mov ecx, dword ptr [ebp+8]
    and eax, 0fh
    shl eax, 4
    mov dword ptr [ecx+014h], eax
    jmp trackerPanningDirty

trackerPanningDown:
    mov ecx, dword ptr [ebp+8]
    and eax, 0fh
    sub dword ptr [ecx+014h], eax
    jmp trackerPanningDirty

trackerPanningUp:
    mov ecx, dword ptr [ebp+8]
    and eax, 0fh
    add dword ptr [ecx+014h], eax

trackerPanningDirty:
    or byte ptr [ecx+2], 4
    pop ebp
    ret

trackerPortamento:
    test cl, 0fh
    mov eax, dword ptr [ebp+8]
    jz trackerPortamentoTarget
    shl cl, 4
    mov byte ptr [eax+084h], cl

trackerPortamentoTarget:
    mov ecx, dword ptr [eax+068h]
    and byte ptr [eax+2], 0f7h
    mov dword ptr [eax+080h], ecx

trackerVolumeComplete:
    pop ebp
    ret

trackerVolumeJumpTable DWORD trackerVolumeDown
                       DWORD trackerVolumeUp
                       DWORD trackerVolumeDown
                       DWORD trackerVolumeUp
                       DWORD trackerVibratoSpeed
                       DWORD trackerVibratoDepth
                       DWORD trackerPanningSet
                       DWORD trackerPanningDown
                       DWORD trackerPanningUp
                       DWORD trackerPortamento
_ApplyTrackerVolumeColumn ENDP

END
