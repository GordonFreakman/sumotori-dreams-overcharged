.386
.model flat
option casemap:none

EXTERN ??2@YAPAXI@Z:PROC

.code

; FUNCTION: SUMO 0x004089bc
; FUNCTION: EDITOR 0x004089de
PUBLIC ?BuildEdges@GameBox@@QAEXXZ
?BuildEdges@GameBox@@QAEXXZ PROC
    push ebp
    mov ebp, esp
    push ecx
    push ecx
    push ebx
    push esi
    mov esi, ecx
    mov eax, dword ptr [esi + 0ch]
    sub eax, dword ptr [esi + 8]
    push edi
    sar eax, 3
    shl eax, 4
    push eax
    call ??2@YAPAXI@Z
    mov dword ptr [esi + 18h], eax
    mov dword ptr [esi + 1ch], eax
    mov eax, dword ptr [esi + 10h]
    pop ecx
    jmp short firstFaceTest

firstFaceLoop:
    mov ecx, dword ptr [eax + 1ch]
    and dword ptr [ebp - 4], 0
    test ecx, ecx
    jle short firstFaceNext
    lea edi, [ecx * 8 - 8]

firstEdgeLoop:
    mov ecx, dword ptr [ebp - 4]
    mov edx, dword ptr [eax + 10h]
    shl ecx, 3
    mov ebx, dword ptr [edx + ecx * 1 + 4]
    cmp ebx, dword ptr [edi + edx * 1 + 4]
    jle short firstEdgeNext
    mov edx, dword ptr [edx + ecx * 1 + 4]
    mov ebx, dword ptr [esi + 1ch]
    mov dword ptr [ebx], edx
    mov edx, dword ptr [eax + 10h]
    mov edx, dword ptr [edx + edi * 1 + 4]
    mov ebx, dword ptr [esi + 1ch]
    mov dword ptr [ebx + 4], edx
    mov edx, dword ptr [esi + 1ch]
    mov dword ptr [edx + 8], eax
    mov edx, dword ptr [esi + 1ch]
    and dword ptr [edx + 0ch], 0
    add dword ptr [esi + 1ch], 10h

firstEdgeNext:
    inc dword ptr [ebp - 4]
    mov edi, ecx
    mov ecx, dword ptr [ebp - 4]
    cmp ecx, dword ptr [eax + 1ch]
    jl short firstEdgeLoop

firstFaceNext:
    add eax, 24h

firstFaceTest:
    cmp eax, dword ptr [esi + 14h]
    jb short firstFaceLoop

    mov eax, dword ptr [esi + 10h]
    jmp short secondFaceTest

secondFaceLoop:
    mov ecx, dword ptr [eax + 1ch]
    xor ebx, ebx
    cmp ecx, ebx
    mov dword ptr [ebp - 4], ebx
    jle short secondFaceNext
    lea ecx, [ecx * 8 - 8]

secondEdgeLoop:
    mov edx, dword ptr [eax + 10h]
    mov edi, dword ptr [ebx + edx * 1 + 4]
    cmp edi, dword ptr [ecx + edx * 1 + 4]
    jge short secondEdgeNext
    mov edi, dword ptr [eax + 10h]
    mov ecx, dword ptr [ecx + edi * 1 + 4]
    mov edx, dword ptr [esi + 18h]
    mov dword ptr [ebp - 8], ecx

edgeSearchLoop:
    mov ecx, dword ptr [ebp - 8]
    cmp dword ptr [edx], ecx
    jne short edgeSearchNext
    mov ecx, dword ptr [edx + 4]
    cmp ecx, dword ptr [ebx + edi * 1 + 4]
    je short edgeSearchFound

edgeSearchNext:
    add edx, 10h
    jmp short edgeSearchLoop

edgeSearchFound:
    mov dword ptr [edx + 0ch], eax

secondEdgeNext:
    inc dword ptr [ebp - 4]
    mov edx, dword ptr [ebp - 4]
    mov ecx, ebx
    add ebx, 8
    cmp edx, dword ptr [eax + 1ch]
    jl short secondEdgeLoop

secondFaceNext:
    add eax, 24h

secondFaceTest:
    cmp eax, dword ptr [esi + 14h]
    jb short secondFaceLoop

    pop edi
    pop esi
    pop ebx
    leave
    ret
?BuildEdges@GameBox@@QAEXXZ ENDP

END
