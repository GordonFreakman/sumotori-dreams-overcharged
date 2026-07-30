.386
.model flat
option casemap:none

EXTERN _sin:PROC
EXTERN _fabs:PROC
EXTERN __ftol2:PROC
EXTERN ?g_trackerVibratoPhaseScale@@3NB:QWORD
EXTERN ?g_textureSize@@3NB:QWORD

.code

; FUNCTION: SUMO 0x004179f9
; FUNCTION: EDITOR 0x00417a1b
PUBLIC ?UpdateTrackerVibrato@@YAXPAUTrackerChannelState@@@Z
?UpdateTrackerVibrato@@YAXPAUTrackerChannelState@@@Z PROC
    push ebp
    mov ebp, esp
    push esi
    mov esi, [ebp+8]
    xor eax, eax
    mov al, [esi+0A2h]
    and eax, 3
    jz short sine_wave
    cmp eax, 1
    jz short ramp_wave
    jle short waveform_ready_fallback
    cmp eax, 3
    jg short waveform_ready_fallback
    mov eax, 0FFh
    jmp short waveform_ready

ramp_wave:
    mov cl, [esi+085h]
    mov al, cl
    shl al, 3
    test cl, cl
    jge short ramp_positive
    or cl, 0FFh
    sub cl, al
    mov al, cl
ramp_positive:
    movzx eax, al
    jmp short waveform_ready

sine_wave:
    movsx eax, BYTE PTR [esi+085h]
    mov [ebp+8], eax
    push ecx
    push ecx
    fild DWORD PTR [ebp+8]
    db 0DCh, 0C0h
    fmul QWORD PTR [?g_trackerVibratoPhaseScale@@3NB]
    fstp QWORD PTR [esp]
    call _sin
    fmul QWORD PTR [?g_textureSize@@3NB]
    fstp QWORD PTR [esp]
    call _fabs
    pop ecx
    pop ecx
    call __ftol2
    jmp short waveform_ready

waveform_ready_fallback:
    mov eax, [ebp+8]
waveform_ready:
    movzx ecx, BYTE PTR [esi+087h]
    imul ecx, eax
    sar ecx, 5
    and ecx, 0FFFFFFFCh
    cmp BYTE PTR [esi+085h], 0
    jl short signed_offset_ready
    neg ecx
signed_offset_ready:
    or BYTE PTR [esi+2], 1
    mov [esi+01Ch], ecx
    pop esi
    pop ebp
    ret
?UpdateTrackerVibrato@@YAXPAUTrackerChannelState@@@Z ENDP

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

; FUNCTION: SUMO 0x00417f89
; FUNCTION: EDITOR 0x00417fab
PUBLIC ?ResetTrackerChannelState@@YAXPAUTrackerChannelState@@PAUGameAudioParsedSample@@@Z
?ResetTrackerChannelState@@YAXPAUTrackerChannelState@@PAUGameAudioParsedSample@@@Z PROC
    mov eax, [esp+4]
    mov ecx, [esp+8]
    movzx edx, BYTE PTR [ecx+010h]
    mov [eax+010h], edx
    mov ecx, [ecx+018h]
    mov dl, [eax+0A2h]
    push ebx
    mov bl, dl
    and bl, 0Fh
    mov [eax+014h], ecx
    xor ecx, ecx
    cmp bl, 4
    mov DWORD PTR [eax+034h], 040h
    mov [eax+02Ch], ecx
    mov [eax+028h], ecx
    mov [eax+038h], ecx
    mov DWORD PTR [eax+04Ch], 020h
    mov [eax+044h], ecx
    mov [eax+040h], ecx
    mov [eax+050h], ecx
    mov [eax+065h], cl
    mov DWORD PTR [eax+058h], 10000h
    mov [eax+03Ch], cl
    mov [eax+054h], cl
    mov [eax+060h], ecx
    mov [eax+05Ch], ecx
    pop ebx
    jnb short low_memory_kept
    mov [eax+085h], cl
low_memory_kept:
    and dl, 0F0h
    cmp dl, 040h
    jnb short high_memory_kept
    mov [eax+089h], cl
high_memory_kept:
    or BYTE PTR [eax+2], 6
    mov [eax+092h], cl
    ret
?ResetTrackerChannelState@@YAXPAUTrackerChannelState@@PAUGameAudioParsedSample@@@Z ENDP

END
