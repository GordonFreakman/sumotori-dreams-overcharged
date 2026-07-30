.686
.model flat
option casemap:none

EXTERN __imp__DefWindowProcA@16:DWORD
EXTERN ?g_gameKeyDown@@3PAEA:BYTE
EXTERN ?g_gameKeyPressed@@3PAEA:BYTE
EXTERN ?g_gameMouseX@@3HA:DWORD
EXTERN ?g_gameMouseY@@3HA:DWORD
EXTERN ?g_gamePrimaryInputPressed@@3HA:DWORD

.code

; FUNCTION: SUMO 0x004169a1
; FUNCTION: EDITOR 0x004169c3
PUBLIC ?GameWindowProc@@YGJPAUHWND__@@IIJ@Z
?GameWindowProc@@YGJPAUHWND__@@IIJ@Z PROC
    push ebp
    mov ebp, esp
    mov eax, dword ptr [ebp + 0ch]
    sub eax, 010h
    jz closeMessage
    sub eax, 0f0h
    mov edx, dword ptr [ebp + 014h]
    jz keyDown
    dec eax
    jz keyUp
    sub eax, 0100h
    jnz callDefaultProc
    movzx eax, dx
    mov dword ptr [?g_gameMouseX@@3HA], eax
    mov eax, edx
    shr eax, 010h
    mov dword ptr [?g_gameMouseY@@3HA], eax
    jmp callDefaultProc
keyUp:
    movzx eax, byte ptr [ebp + 016h]
    mov byte ptr [?g_gameKeyDown@@3PAEA + eax], 0
    jmp callDefaultProc
keyDown:
    mov eax, edx
    sar eax, 010h
    xor ecx, ecx
    and eax, 0ffh
    inc ecx
    cmp eax, ecx
    jnz latchKey
    mov dword ptr [?g_gamePrimaryInputPressed@@3HA], ecx
latchKey:
    mov byte ptr [?g_gameKeyDown@@3PAEA + eax], cl
    mov byte ptr [?g_gameKeyPressed@@3PAEA + eax], cl
callDefaultProc:
    push edx
    push dword ptr [ebp + 010h]
    push dword ptr [ebp + 00ch]
    push dword ptr [ebp + 008h]
    call dword ptr [__imp__DefWindowProcA@16]
    jmp windowProcDone
closeMessage:
    xor eax, eax
windowProcDone:
    pop ebp
    ret 010h
?GameWindowProc@@YGJPAUHWND__@@IIJ@Z ENDP

END
