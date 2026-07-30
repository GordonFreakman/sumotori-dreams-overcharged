.386
.model flat

.code

; FUNCTION: SUMO 0x00408f5b
; FUNCTION: EDITOR 0x00408f7d
PUBLIC ?Push@GameCollisionCandidateHeap@@QAEXMUVector3@@@Z
?Push@GameCollisionCandidateHeap@@QAEXMUVector3@@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 10h
    mov eax, [ebp+8]
    push esi
    push edi
    mov [ebp-10h], eax
    lea esi, [ebp+0Ch]
    lea edi, [ebp-0Ch]
    movsd
    movsd
    movsd
    mov edi, [ecx+2000h]
    shl edi, 4
    add edi, ecx
    lea esi, [ebp-10h]
    movsd
    movsd
    movsd
    movsd
    inc DWORD PTR [ecx+2000h]
    mov eax, [ecx+2000h]
    lea esi, [eax-1]
    test esi, esi
    jz short heap_done
    push ebx

heap_bubble:
    lea eax, [esi-1]
    cdq
    sub eax, edx
    sar eax, 1
    mov [ebp+8], eax
    shl eax, 4
    db 08Dh, 014h, 008h
    shl esi, 4
    fld DWORD PTR [edx]
    db 08Dh, 01Ch, 00Eh
    fcomp DWORD PTR [ebx]
    fnstsw ax
    test ah, 41h
    jnz short heap_pop_ebx
    mov esi, edx
    lea edi, [ebp-10h]
    movsd
    movsd
    movsd
    movsd
    mov esi, ebx
    mov edi, edx
    movsd
    movsd
    movsd
    movsd
    lea esi, [ebp-10h]
    mov edi, ebx
    movsd
    movsd
    movsd
    movsd
    mov esi, [ebp+8]
    test esi, esi
    jnz short heap_bubble

heap_pop_ebx:
    pop ebx
heap_done:
    pop edi
    pop esi
    leave
    ret 10h
?Push@GameCollisionCandidateHeap@@QAEXMUVector3@@@Z ENDP

; FUNCTION: SUMO 0x00408fe2
; FUNCTION: EDITOR 0x00409004
PUBLIC ?Pop@GameCollisionCandidateHeap@@QAE?AUVector3@@XZ
?Pop@GameCollisionCandidateHeap@@QAE?AUVector3@@XZ PROC
    push ebp
    mov ebp, esp
    sub esp, 20h
    mov eax, [ecx+2000h]
    push ebx
    xor ebx, ebx
    push esi
    inc ebx
    cmp eax, ebx
    push edi
    lea esi, [ecx+4]
    jle pop_small_heap
    lea edi, [ebp-10h]
    movsd
    movsd
    movsd
    shl eax, 4
    db 08Dh, 074h, 008h, 0F0h
    mov edi, ecx
    movsd
    movsd
    movsd
    xor edx, edx
    movsd
    cmp DWORD PTR [ecx+2000h], ebx
    jle short pop_finish_nonempty

pop_bubble:
    mov esi, [ecx+2000h]
    lea eax, [esi-1]
    cmp ebx, eax
    jge short pop_have_child
    mov eax, ebx
    shl eax, 4
    add eax, ecx
    fld DWORD PTR [eax]
    fcomp DWORD PTR [eax+10h]
    fnstsw ax
    test ah, 41h
    jnz short pop_have_child
    inc ebx

pop_have_child:
    mov eax, ebx
    shl eax, 4
    add eax, ecx
    fld DWORD PTR [eax]
    shl edx, 4
    add edx, ecx
    fcomp DWORD PTR [edx]
    mov [ebp-4], eax
    fnstsw ax
    test ah, 5
    jp short pop_stop_bubbling
    mov esi, edx
    lea edi, [ebp-20h]
    movsd
    movsd
    movsd
    movsd
    mov esi, [ebp-4]
    mov edi, edx
    movsd
    movsd
    movsd
    movsd
    mov edi, [ebp-4]
    lea esi, [ebp-20h]
    movsd
    movsd
    movsd
    movsd
    mov edx, ebx
    jmp short pop_next_level

pop_stop_bubbling:
    mov edx, esi

pop_next_level:
    lea ebx, [edx+edx+1]
    cmp ebx, [ecx+2000h]
    jl short pop_bubble
    jmp short pop_finish_nonempty

pop_small_heap:
    test eax, eax
    jz short pop_copy_result
    lea edi, [ebp-10h]
    movsd
    movsd
    movsd

pop_finish_nonempty:
    dec DWORD PTR [ecx+2000h]
    lea esi, [ebp-10h]

pop_copy_result:
    mov eax, [ebp+8]
    mov edi, eax
    movsd
    movsd
    movsd
    pop edi
    pop esi
    pop ebx
    leave
    ret 4
?Pop@GameCollisionCandidateHeap@@QAE?AUVector3@@XZ ENDP

END
