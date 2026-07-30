.586
.model flat
option casemap:none
ASSUME FS:NOTHING

EXTERN __EH_prolog:PROC
EXTERN ___CxxFrameHandler:PROC
EXTERN ??0BigInteger@@QAE@H@Z:PROC
EXTERN ??1BigInteger@@QAE@XZ:PROC
EXTERN ??4BigInteger@@QAEAAV0@AAV0@@Z:PROC
EXTERN ??DBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??YBigInteger@@QAEXAAV0@@Z:PROC
EXTERN ?SetPositive@BigInteger@@QAEXI@Z:PROC
EXTERN _free:PROC

.data
PUBLIC stringConstructorDecimalDigits
stringConstructorDecimalDigits BYTE "0123456789", 0
ALIGN 4
PUBLIC stringConstructorEhDescriptor
stringConstructorEhDescriptor DWORD 019930520h, 0, 0, 0, 0, 0, 0, 0

.code

stringConstructorThisCleanup:
    mov ecx, dword ptr [ebp-10h]
    jmp ??1BigInteger@@QAE@XZ

stringConstructorPlaceCleanup:
    lea ecx, [ebp-20h]
    jmp ??1BigInteger@@QAE@XZ

stringConstructorDigitCleanup:
    lea ecx, [ebp-40h]
    jmp ??1BigInteger@@QAE@XZ

stringConstructorProductCleanup:
    lea ecx, [ebp-30h]
    jmp ??1BigInteger@@QAE@XZ

PUBLIC stringConstructorEhHandler
stringConstructorEhHandler:
    mov eax, OFFSET stringConstructorEhDescriptor
    jmp ___CxxFrameHandler

; FUNCTION: SUMO 0x0040180e
; FUNCTION: EDITOR 0x0040180e
PUBLIC ??0BigInteger@@QAE@PADHPBDH@Z
??0BigInteger@@QAE@PADHPBDH@Z PROC
    mov eax, OFFSET stringConstructorEhHandler
    call __EH_prolog
    sub esp, 54h
    push ebx
    push esi
    xor ebx, ebx
    push edi
    mov edi, ecx
    mov dword ptr [ebp-10h], edi
    mov dword ptr [edi], ebx
    mov dword ptr [edi+4], ebx
    mov dword ptr [edi+8], ebx
    mov esi, dword ptr [ebp+0ch]
    cmp esi, ebx
    mov dword ptr [ebp-4], ebx
    jnz stringConstructorHaveLength
    mov eax, dword ptr [ebp+8]
    jmp stringConstructorTestLength

stringConstructorCountLength:
    inc eax
    inc esi

stringConstructorTestLength:
    cmp byte ptr [eax], bl
    jnz stringConstructorCountLength

stringConstructorHaveLength:
    cmp dword ptr [ebp+10h], ebx
    jnz stringConstructorHaveAlphabet
    mov dword ptr [ebp+10h], OFFSET stringConstructorDecimalDigits

stringConstructorHaveAlphabet:
    push ebx
    mov ecx, edi
    call ?SetPositive@BigInteger@@QAEXI@Z
    push 1
    lea ecx, [ebp-20h]
    call ??0BigInteger@@QAE@H@Z
    add dword ptr [ebp+8], esi
    cmp esi, ebx
    mov byte ptr [ebp-4], 1
    jle stringConstructorDestroyPlace

stringConstructorNextInput:
    dec dword ptr [ebp+8]
    xor eax, eax
    cmp dword ptr [ebp+14h], ebx
    jle stringConstructorAdvanceInput
    mov ecx, dword ptr [ebp+8]
    mov cl, byte ptr [ecx]

stringConstructorFindDigit:
    mov edx, dword ptr [ebp+10h]
    db 038h, 00ch, 010h
    jz stringConstructorApplyDigit
    inc eax
    cmp eax, dword ptr [ebp+14h]
    jl stringConstructorFindDigit
    jmp stringConstructorAdvanceInput

stringConstructorApplyDigit:
    push eax
    lea ecx, [ebp-40h]
    call ??0BigInteger@@QAE@H@Z
    push eax
    lea eax, [ebp-30h]
    push eax
    lea ecx, [ebp-20h]
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    mov ecx, edi
    mov byte ptr [ebp-4], 3
    call ??YBigInteger@@QAEXAAV0@@Z
    cmp dword ptr [ebp-30h], ebx
    jz stringConstructorDigitProductDestroyed
    push dword ptr [ebp-30h]
    call _free
    pop ecx
    mov dword ptr [ebp-30h], ebx

stringConstructorDigitProductDestroyed:
    cmp dword ptr [ebp-40h], ebx
    mov byte ptr [ebp-4], 1
    jz stringConstructorMultiplyPlace
    push dword ptr [ebp-40h]
    call _free
    pop ecx
    mov dword ptr [ebp-40h], ebx

stringConstructorMultiplyPlace:
    push dword ptr [ebp+14h]
    lea ecx, [ebp-60h]
    call ??0BigInteger@@QAE@H@Z
    push eax
    lea eax, [ebp-50h]
    push eax
    lea ecx, [ebp-20h]
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-20h]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-50h], ebx
    jz stringConstructorRadixProductDestroyed
    push dword ptr [ebp-50h]
    call _free
    pop ecx
    mov dword ptr [ebp-50h], ebx

stringConstructorRadixProductDestroyed:
    cmp dword ptr [ebp-60h], ebx
    jz stringConstructorAdvanceInput
    push dword ptr [ebp-60h]
    call _free
    pop ecx
    mov dword ptr [ebp-60h], ebx

stringConstructorAdvanceInput:
    dec esi
    jnz stringConstructorNextInput

stringConstructorDestroyPlace:
    cmp dword ptr [ebp-20h], ebx
    jz stringConstructorReturn
    push dword ptr [ebp-20h]
    call _free
    pop ecx

stringConstructorReturn:
    mov ecx, dword ptr [ebp-0ch]
    mov eax, edi
    pop edi
    pop esi
    pop ebx
    mov dword ptr fs:[0], ecx
    leave
    ret 10h
??0BigInteger@@QAE@PADHPBDH@Z ENDP

END
