.386
.model flat
option casemap:none


.code

; FUNCTION: SUMO 0x00417b8a
; FUNCTION: EDITOR 0x00417bac
PUBLIC ?UpdateTrackerEnvelope@@YAXPAUTrackerChannelState@@PAH1EHPAUTrackerEnvelopePoint@@EEE11PAE1E@Z
?UpdateTrackerEnvelope@@YAXPAUTrackerChannelState@@PAH1EHPAUTrackerEnvelopePoint@@EEE11PAE1E@Z PROC
    push ebp
    mov ebp, esp
    push ecx
    push ebx
    push esi
    mov esi, [ebp+10h]
    push edi
    mov edi, [ebp+0Ch]
    mov eax, [edi]
    cmp eax, [ebp+18h]
    jge near ptr envelope_publish
    mov edx, [ebp+1Ch]
    movzx ecx, WORD PTR [edx+eax*4]
    cmp [esi], ecx
    jnz near ptr envelope_accumulate
    test BYTE PTR [ebp+14h], 4
    jz short envelope_load_points
    movzx ecx, BYTE PTR [ebp+20h]
    cmp eax, ecx
    jnz short envelope_load_points
    movzx eax, BYTE PTR [ebp+24h]
    mov [edi], eax
    movzx eax, WORD PTR [edx+eax*4]
    mov [esi], eax
envelope_load_points:
    mov ecx, [edi]
    lea eax, [edx+ecx*4]
    movzx esi, WORD PTR [eax]
    movzx ebx, WORD PTR [eax+2]
    lea edx, [edx+ecx*4+4]
    movzx eax, WORD PTR [edx+2]
    mov [ebp-4], esi
    movzx esi, WORD PTR [edx]
    mov edx, [ebp+18h]
    mov [ebp+0Ch], esi
    mov esi, ebx
    shl esi, 10h
    shl eax, 10h
    dec edx
    cmp ecx, edx
    jnz short envelope_check_sustain
    mov eax, [ebp+2Ch]
    mov cl, [ebp+3Ch]
    mov [eax], ebx
    mov eax, [ebp+34h]
    mov BYTE PTR [eax], 1
    mov eax, [ebp+8]
    or [eax+2], cl
    jmp short envelope_done
envelope_check_sustain:
    test BYTE PTR [ebp+14h], 2
    jz short envelope_build_segment_with_channel
    movzx edx, BYTE PTR [ebp+28h]
    cmp ecx, edx
    jnz short envelope_build_segment_with_channel
    mov ecx, [ebp+8]
    cmp BYTE PTR [ecx+65h], 0
    jnz short envelope_build_segment
    mov eax, [ebp+2Ch]
    mov [eax], ebx
    jmp short envelope_dirty
envelope_build_segment_with_channel:
    mov ecx, [ebp+8]
envelope_build_segment:
    mov edx, [ebp+0Ch]
    sub edx, [ebp-4]
    mov ebx, edx
    jz short envelope_zero_slope
    sub eax, esi
    cdq
    idiv ebx
    mov edx, [ebp+38h]
    mov [edx], eax
    jmp short envelope_store_segment
envelope_zero_slope:
    mov eax, [ebp+38h]
    and DWORD PTR [eax], 0
envelope_store_segment:
    mov eax, [ebp+30h]
    mov [eax], esi
    inc DWORD PTR [edi]
    mov esi, [ebp+10h]
    jmp short envelope_output
envelope_accumulate:
    mov eax, [ebp+38h]
    mov ecx, [eax]
    mov eax, [ebp+30h]
    add [eax], ecx
envelope_publish:
    mov ecx, [ebp+8]
envelope_output:
    mov eax, [ebp+30h]
    movsx eax, WORD PTR [eax+2]
    mov edx, [ebp+2Ch]
    mov [edx], eax
    inc DWORD PTR [esi]
envelope_dirty:
    mov al, [ebp+3Ch]
    or [ecx+2], al
envelope_done:
    pop edi
    pop esi
    pop ebx
    leave
    ret
?UpdateTrackerEnvelope@@YAXPAUTrackerChannelState@@PAH1EHPAUTrackerEnvelopePoint@@EEE11PAE1E@Z ENDP

END
