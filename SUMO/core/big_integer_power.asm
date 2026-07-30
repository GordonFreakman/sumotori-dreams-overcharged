.586
.model flat
option casemap:none
ASSUME FS:NOTHING

EXTERN __EH_prolog:PROC
EXTERN ___CxxFrameHandler:PROC
EXTERN ??0BigInteger@@QAE@XZ:PROC
EXTERN ??0BigInteger@@QAE@H@Z:PROC
EXTERN ??0BigInteger@@QAE@AAV0@@Z:PROC
EXTERN ??1BigInteger@@QAE@XZ:PROC
EXTERN ??4BigInteger@@QAEAAV0@AAV0@@Z:PROC
EXTERN ??HBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??DBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??OBigInteger@@QAE_NAAV0@@Z:PROC
EXTERN ?SetPositive@BigInteger@@QAEXI@Z:PROC
EXTERN _free:PROC

.data
ALIGN 4
PUBLIC powerEhDescriptor
powerEhDescriptor DWORD 019930520h, 0, 0, 0, 0, 0, 0, 0

.code

powerEhResultCleanup:
    lea ecx, [ebp-40h]
    jmp ??1BigInteger@@QAE@XZ

powerEhFactorCleanup:
    lea ecx, [ebp-30h]
    jmp ??1BigInteger@@QAE@XZ

powerEhBitValueCleanup:
    lea ecx, [ebp-20h]
    jmp ??1BigInteger@@QAE@XZ

powerEhExponentCleanup:
    lea ecx, [ebp-50h]
    jmp ??1BigInteger@@QAE@XZ

PUBLIC powerEhHandler
powerEhHandler:
    mov eax, OFFSET powerEhDescriptor
    jmp ___CxxFrameHandler

; FUNCTION: SUMO 0x00401cff
; FUNCTION: EDITOR 0x00401cff
PUBLIC ?Power@BigInteger@@QAE?AV1@H@Z
?Power@BigInteger@@QAE?AV1@H@Z PROC
    mov eax, OFFSET powerEhHandler
    call __EH_prolog
    sub esp, 74h
    push esi
    push edi
    mov edi, ecx
    xor esi, esi
    lea ecx, [ebp-40h]
    mov [ebp-10h], esi
    call ??0BigInteger@@QAE@XZ
    push 1
    lea ecx, [ebp-40h]
    mov [ebp-4], esi
    call ?SetPositive@BigInteger@@QAEXI@Z
    push edi
    lea ecx, [ebp-30h]
    call ??0BigInteger@@QAE@AAV0@@Z
    push 1
    lea ecx, [ebp-20h]
    call ??0BigInteger@@QAE@H@Z
    mov edi, dword ptr [ebp+0ch]
    mov byte ptr [ebp-4], 2
    mov [ebp-10h], esi
    push ebx

powerProcessBit:
    mov ecx, dword ptr [ebp-10h]
    xor eax, eax
    inc eax
    shl eax, cl
    db 085h, 0c7h
    jz powerAdvanceBit
    lea eax, [ebp-30h]
    push eax
    lea eax, [ebp-60h]
    push eax
    lea ecx, [ebp-40h]
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-40h]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-60h], esi
    jz powerAdvanceBit
    push dword ptr [ebp-60h]
    call _free
    pop ecx
    mov dword ptr [ebp-60h], esi

powerAdvanceBit:
    inc dword ptr [ebp-10h]
    lea eax, [ebp-20h]
    push eax
    lea eax, [ebp-70h]
    push eax
    lea ecx, [ebp-20h]
    call ??HBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-20h]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-70h], esi
    jz powerSquareFactor
    push dword ptr [ebp-70h]
    call _free
    pop ecx
    mov dword ptr [ebp-70h], esi

powerSquareFactor:
    lea eax, [ebp-30h]
    push eax
    lea eax, [ebp-80h]
    push eax
    lea ecx, [ebp-30h]
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-30h]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-80h], esi
    jz powerTestLimit
    push dword ptr [ebp-80h]
    call _free
    pop ecx
    mov dword ptr [ebp-80h], esi

powerTestLimit:
    push edi
    lea ecx, [ebp-50h]
    call ??0BigInteger@@QAE@H@Z
    lea eax, [ebp-50h]
    push eax
    lea ecx, [ebp-20h]
    mov byte ptr [ebp-4], 3
    call ??OBigInteger@@QAE_NAAV0@@Z
    mov bl, al
    neg bl
    sbb bl, bl
    inc bl
    cmp dword ptr [ebp-50h], esi
    mov byte ptr [ebp-4], 2
    jz powerLimitTemporaryDone
    push dword ptr [ebp-50h]
    call _free
    pop ecx
    mov dword ptr [ebp-50h], esi

powerLimitTemporaryDone:
    test bl, bl
    jnz powerProcessBit
    mov ecx, dword ptr [ebp+8]
    lea eax, [ebp-40h]
    push eax
    call ??0BigInteger@@QAE@AAV0@@Z
    cmp dword ptr [ebp-20h], esi
    pop ebx
    jz powerDestroyFactor
    push dword ptr [ebp-20h]
    call _free
    pop ecx
    mov dword ptr [ebp-20h], esi

powerDestroyFactor:
    cmp dword ptr [ebp-30h], esi
    jz powerDestroyResult
    push dword ptr [ebp-30h]
    call _free
    pop ecx

powerDestroyResult:
    cmp dword ptr [ebp-40h], esi
    pop edi
    pop esi
    jz powerReturn
    push dword ptr [ebp-40h]
    call _free
    pop ecx

powerReturn:
    mov ecx, dword ptr [ebp-0ch]
    mov eax, dword ptr [ebp+8]
    mov dword ptr fs:[0], ecx
    leave
    ret 8
?Power@BigInteger@@QAE?AV1@H@Z ENDP

END
