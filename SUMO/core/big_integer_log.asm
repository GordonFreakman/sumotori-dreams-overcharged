.586
.model flat
option casemap:none
ASSUME FS:NOTHING

EXTERN __EH_prolog:PROC
EXTERN ___CxxFrameHandler:PROC
EXTERN ??_L@YGXPAXIHP6EX0@Z1@Z:PROC
EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ??0BigInteger@@QAE@XZ:PROC
EXTERN ??0BigInteger@@QAE@AAV0@@Z:PROC
EXTERN ??1BigInteger@@QAE@XZ:PROC
EXTERN ??4BigInteger@@QAEAAV0@AAV0@@Z:PROC
EXTERN ??DBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??OBigInteger@@QAE_NAAV0@@Z:PROC
EXTERN _free:PROC

.data
ALIGN 4
PUBLIC logEhDescriptor
logEhDescriptor DWORD 019930520h, 0, 0, 0, 0, 0, 0, 0

.code

logEhVectorCleanup:
    push OFFSET ??1BigInteger@@QAE@XZ
    push 20h
    push 10h
    lea eax, [ebp-230h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret

logEhAccumulatedCleanup:
    lea ecx, [ebp-20h]
    jmp ??1BigInteger@@QAE@XZ

logEhCandidateCleanup:
    lea ecx, [ebp-30h]
    jmp ??1BigInteger@@QAE@XZ

PUBLIC logEhHandler
logEhHandler:
    mov eax, OFFSET logEhDescriptor
    jmp ___CxxFrameHandler

; FUNCTION: SUMO 0x00401bb9
; FUNCTION: EDITOR 0x00401bb9
PUBLIC ?Log@BigInteger@@QAEHAAV1@@Z
?Log@BigInteger@@QAEHAAV1@@Z PROC
    mov eax, OFFSET logEhHandler
    call __EH_prolog
    sub esp, 224h
    push esi
    push edi
    push OFFSET ??1BigInteger@@QAE@XZ
    push OFFSET ??0BigInteger@@QAE@XZ
    push 20h
    push 10h
    lea eax, [ebp-230h]
    push eax
    mov [ebp-10h], ecx
    call ??_L@YGXPAXIHP6EX0@Z1@Z
    push dword ptr [ebp+8]
    xor esi, esi
    lea ecx, [ebp-230h]
    mov [ebp-4], esi
    xor edi, edi
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    push dword ptr [ebp-10h]
    mov ecx, dword ptr [ebp+8]
    call ??OBigInteger@@QAE_NAAV0@@Z
    test al, al
    jnz logDestroyPowers
    push ebx
    lea ebx, [ebp-230h]
    mov esi, ebx

logBuildPower:
    push ebx
    lea eax, [ebp-20h]
    push eax
    mov ecx, ebx
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [esi+10h]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-20h], 0
    jz logPowerTemporaryDone
    push dword ptr [ebp-20h]
    call _free
    and dword ptr [ebp-20h], 0
    pop ecx

logPowerTemporaryDone:
    push dword ptr [ebp-10h]
    add esi, 10h
    mov ecx, esi
    inc edi
    mov ebx, esi
    call ??OBigInteger@@QAE_NAAV0@@Z
    test al, al
    jz logBuildPower
    dec edi
    mov eax, edi
    shl eax, 4
    db 08dh, 09ch, 005h, 0d0h, 0fdh, 0ffh, 0ffh
    push ebx
    lea ecx, [ebp-20h]
    call ??0BigInteger@@QAE@AAV0@@Z
    xor esi, esi
    inc esi
    mov ecx, edi
    shl esi, cl
    jmp logTestNextPower

logGreedyPower:
    sub ebx, 10h
    push ebx
    lea eax, [ebp-30h]
    push eax
    lea ecx, [ebp-20h]
    dec edi
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push dword ptr [ebp-10h]
    lea ecx, [ebp-30h]
    mov byte ptr [ebp-4], 2
    call ??OBigInteger@@QAE_NAAV0@@Z
    test al, al
    jnz logCandidateRejected
    xor eax, eax
    inc eax
    mov ecx, edi
    shl eax, cl
    lea ecx, [ebp-20h]
    or esi, eax
    lea eax, [ebp-30h]
    push eax
    call ??4BigInteger@@QAEAAV0@AAV0@@Z

logCandidateRejected:
    cmp dword ptr [ebp-30h], 0
    jz logTestNextPower
    push dword ptr [ebp-30h]
    call _free
    and dword ptr [ebp-30h], 0
    pop ecx

logTestNextPower:
    test edi, edi
    jg logGreedyPower
    cmp dword ptr [ebp-20h], 0
    pop ebx
    jz logDestroyPowers
    push dword ptr [ebp-20h]
    call _free
    pop ecx

logDestroyPowers:
    or dword ptr [ebp-4], 0ffffffffh
    push OFFSET ??1BigInteger@@QAE@XZ
    push 20h
    push 10h
    lea eax, [ebp-230h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    mov ecx, dword ptr [ebp-0ch]
    pop edi
    mov eax, esi
    pop esi
    mov dword ptr fs:[0], ecx
    leave
    ret 4
?Log@BigInteger@@QAEHAAV1@@Z ENDP

END
