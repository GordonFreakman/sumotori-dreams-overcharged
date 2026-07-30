.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@XZ:PROC
EXTERN ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z:PROC

.code

; FUNCTION: SUMO 0x00408684
; FUNCTION: EDITOR 0x004086a6
PUBLIC ?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z
?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 0ch
    mov ecx, dword ptr [ebp + 0ch]
    push esi
    lea eax, [ebp - 0ch]
    push eax
    call ??GVector3@@QAE?AU0@XZ
    mov esi, dword ptr [ebp + 8]
    mov ecx, dword ptr [esi]
    push eax
    lea eax, [ebp - 0ch]
    push eax
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    push dword ptr [ebp + 0ch]
    mov ecx, dword ptr [esi + 4]
    lea eax, [ebp - 0ch]
    push eax
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    pop esi
    leave
    ret
?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z ENDP

END
