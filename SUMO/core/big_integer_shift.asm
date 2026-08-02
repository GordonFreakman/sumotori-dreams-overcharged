.686
.model flat
option casemap:none

EXTERN ??0BigInteger@@QAE@XZ:PROC
EXTERN ??0BigInteger@@QAE@AAV0@@Z:PROC
EXTERN ?PadTo@U32Vector@@QAEXI@Z:PROC
EXTERN ??AU32Vector@@QAEAAII@Z:PROC
EXTERN ?TrimLeadingZeros@U32Vector@@QAEXXZ:PROC
EXTERN _free:PROC

.code

; FUNCTION: SUMO 0x00401680
; FUNCTION: EDITOR 0x00401680
PUBLIC ??6BigInteger@@QAE?AV0@H@Z
??6BigInteger@@QAE?AV0@H@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 018h
    and dword ptr [ebp - 8], 0
    push ebx
    push esi
    mov esi, ecx
    push edi
    lea ecx, [ebp - 018h]
    call ??0BigInteger@@QAE@XZ
    mov edi, dword ptr [ebp + 0ch]
    push 020h
    lea eax, [edi + 01fh]
    cdq
    pop ebx
    idiv ebx
    mov ecx, dword ptr [esi + 4]
    sub ecx, dword ptr [esi]
    sar ecx, 2
    shl ecx, 5
    add ecx, eax
    push ecx
    lea ecx, [ebp - 018h]
    call ?PadTo@U32Vector@@QAEXI@Z
    mov eax, edi
    cdq
    push ebx
    pop ecx
    idiv ecx
    and dword ptr [ebp + 0ch], 0
    mov dword ptr [ebp - 8], eax
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    mov dword ptr [ebp - 4], edx
    sar eax, 2
    jz short shiftNormalize

shiftLoop:
    mov eax, dword ptr [ebp + 0ch]
    mov ecx, dword ptr [ebp - 8]
    db 08dh, 01ch, 008h
    push ebx
    lea ecx, [ebp - 018h]
    call ??AU32Vector@@QAEAAII@Z
    push dword ptr [ebp + 0ch]
    mov ecx, esi
    mov edi, eax
    call ??AU32Vector@@QAEAAII@Z
    mov eax, dword ptr [eax]
    mov ecx, dword ptr [ebp - 4]
    shl eax, cl
    add dword ptr [edi], eax
    test ecx, ecx
    jz short shiftNextSource
    push dword ptr [ebp + 0ch]
    mov ecx, esi
    call ??AU32Vector@@QAEAAII@Z
    inc ebx
    push ebx
    lea ecx, [ebp - 018h]
    mov edi, eax
    call ??AU32Vector@@QAEAAII@Z
    mov edx, dword ptr [edi]
    push 020h
    pop ecx
    sub ecx, dword ptr [ebp - 4]
    shr edx, cl
    mov dword ptr [eax], edx
shiftNextSource:
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    inc dword ptr [ebp + 0ch]
    sar eax, 2
    cmp dword ptr [ebp + 0ch], eax
    jb short shiftLoop

shiftNormalize:
    lea ecx, [ebp - 018h]
    call ?TrimLeadingZeros@U32Vector@@QAEXXZ
    mov eax, dword ptr [esi + 0ch]
    mov ecx, dword ptr [ebp + 8]
    mov dword ptr [ebp - 0ch], eax
    lea eax, [ebp - 018h]
    push eax
    call ??0BigInteger@@QAE@AAV0@@Z
    cmp dword ptr [ebp - 018h], 0
    pop edi
    pop esi
    pop ebx
    je short shiftReturn
    push dword ptr [ebp - 018h]
    call _free
    pop ecx
shiftReturn:
    mov eax, dword ptr [ebp + 8]
    leave
    ret 8
??6BigInteger@@QAE?AV0@H@Z ENDP

END
