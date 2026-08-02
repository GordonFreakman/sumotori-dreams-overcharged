.586
.model flat
option casemap:none
ASSUME FS:NOTHING

EXTERN __EH_prolog:PROC
EXTERN ___CxxFrameHandler:PROC
EXTERN ??AU32Vector@@QAEAAII@Z:PROC
EXTERN ??0BigInteger@@QAE@H@Z:PROC
EXTERN ??0BigInteger@@QAE@AAV0@@Z:PROC
EXTERN ??1BigInteger@@QAE@XZ:PROC
EXTERN ??4BigInteger@@QAEAAV0@AAV0@@Z:PROC
EXTERN ??DBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??KBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??ZBigInteger@@QAEXAAV0@@Z:PROC
EXTERN ?Log@BigInteger@@QAEHAAV1@@Z:PROC
EXTERN ?Power@BigInteger@@QAE?AV1@H@Z:PROC
EXTERN _free:PROC
EXTERN ??_C@_0L@FPFMPDDA@0123456789?$AA@:BYTE

.data
ALIGN 4
PUBLIC writeStringEhDescriptor
writeStringEhDescriptor DWORD 019930520h, 0, 0, 0, 0, 0, 0, 0

.code

writeStringPlaceCleanup:
    lea ecx, [ebp-30h]
    jmp ??1BigInteger@@QAE@XZ

writeStringRadixCleanup:
    lea ecx, [ebp-70h]
    jmp ??1BigInteger@@QAE@XZ

writeStringRemainingCleanup:
    lea ecx, [ebp-40h]
    jmp ??1BigInteger@@QAE@XZ

writeStringDigitCleanup:
    lea ecx, [ebp-20h]
    jmp ??1BigInteger@@QAE@XZ

writeStringProductCleanup:
    lea ecx, [ebp-50h]
    jmp ??1BigInteger@@QAE@XZ

writeStringQuotientCleanup:
    lea ecx, [ebp-60h]
    jmp ??1BigInteger@@QAE@XZ

PUBLIC writeStringEhHandler
writeStringEhHandler:
    mov eax, OFFSET writeStringEhDescriptor
    jmp ___CxxFrameHandler

; FUNCTION: SUMO 0x00401fb4
; FUNCTION: EDITOR 0x00401fb4
PUBLIC ?WriteString@BigInteger@@QAEXPADHPBDHH@Z
?WriteString@BigInteger@@QAEXPADHPBDHH@Z PROC
    mov eax, OFFSET writeStringEhHandler
    call __EH_prolog
    sub esp, 64h
    push ebx
    xor ebx, ebx
    cmp dword ptr [ebp+10h], ebx
    mov dword ptr [ebp-10h], ecx
    jnz writeStringHaveAlphabet
    mov dword ptr [ebp+10h], OFFSET ??_C@_0L@FPFMPDDA@0123456789?$AA@

writeStringHaveAlphabet:
    mov eax, dword ptr [ebp+0ch]
    push esi
    push edi
    mov edi, dword ptr [ebp+8]
    push dword ptr [ebp+14h]
    db 08dh, 044h, 007h, 0ffh
    lea ecx, [ebp-30h]
    mov dword ptr [ebp+0ch], eax
    call ??0BigInteger@@QAE@H@Z
    mov ecx, dword ptr [ebp-10h]
    lea eax, [ebp-30h]
    push eax
    mov dword ptr [ebp-4], ebx
    call ?Log@BigInteger@@QAEHAAV1@@Z
    cmp dword ptr [ebp-30h], ebx
    mov esi, eax
    jz writeStringTestMinimum
    push dword ptr [ebp-30h]
    call _free
    pop ecx

writeStringTestMinimum:
    mov eax, dword ptr [ebp+18h]
    cmp eax, ebx
    jz writeStringBuildPlace
    dec eax
    cmp esi, eax
    jge writeStringBuildPlace
    mov esi, eax

writeStringBuildPlace:
    push dword ptr [ebp+14h]
    lea ecx, [ebp-70h]
    call ??0BigInteger@@QAE@H@Z
    push esi
    lea ecx, [ebp-30h]
    push ecx
    mov ecx, eax
    mov dword ptr [ebp-4], 1
    call ?Power@BigInteger@@QAE?AV1@H@Z
    cmp dword ptr [ebp-70h], ebx
    jz writeStringCopyRemaining
    push dword ptr [ebp-70h]
    call _free
    pop ecx

writeStringCopyRemaining:
    push dword ptr [ebp-10h]
    lea ecx, [ebp-40h]
    call ??0BigInteger@@QAE@AAV0@@Z
    cmp esi, ebx
    mov byte ptr [ebp-4], 4
    mov dword ptr [ebp+8], ebx
    jl writeStringTerminate
    inc esi

writeStringNextDigit:
    lea eax, [ebp-30h]
    push eax
    lea eax, [ebp-20h]
    push eax
    lea ecx, [ebp-40h]
    call ??KBigInteger@@QAE?AV0@AAV0@@Z
    mov ecx, dword ptr [ebp-1ch]
    sub ecx, dword ptr [ebp-20h]
    xor eax, eax
    test ecx, 0FFFFFFFCh
    jz writeStringHaveDigit
    push ebx
    lea ecx, [ebp-20h]
    call ??AU32Vector@@QAEAAII@Z
    mov eax, dword ptr [eax]

writeStringHaveDigit:
    cmp dword ptr [ebp+0ch], edi
    jbe writeStringSubtractDigit
    cmp dword ptr [ebp+8], 5
    jnz writeStringEmitDigit
    cmp dword ptr [ebp+18h], ebx
    jz writeStringEmitDigit
    mov byte ptr [edi], 2dh
    mov dword ptr [ebp+8], ebx
    inc edi

writeStringEmitDigit:
    mov ecx, dword ptr [ebp+10h]
    db 08ah, 004h, 008h
    mov byte ptr [edi], al
    inc edi
    inc dword ptr [ebp+8]

writeStringSubtractDigit:
    lea eax, [ebp-20h]
    push eax
    lea eax, [ebp-50h]
    push eax
    lea ecx, [ebp-30h]
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-40h]
    mov byte ptr [ebp-4], 6
    call ??ZBigInteger@@QAEXAAV0@@Z
    cmp dword ptr [ebp-50h], ebx
    jz writeStringDividePlace
    push dword ptr [ebp-50h]
    call _free
    pop ecx
    mov dword ptr [ebp-50h], ebx

writeStringDividePlace:
    push dword ptr [ebp+14h]
    lea ecx, [ebp-70h]
    call ??0BigInteger@@QAE@H@Z
    push eax
    lea eax, [ebp-60h]
    push eax
    lea ecx, [ebp-30h]
    mov byte ptr [ebp-4], 7
    call ??KBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-30h]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-60h], ebx
    jz writeStringRadixDestroyed
    push dword ptr [ebp-60h]
    call _free
    pop ecx
    mov dword ptr [ebp-60h], ebx

writeStringRadixDestroyed:
    cmp dword ptr [ebp-70h], ebx
    jz writeStringDigitDestroyed
    push dword ptr [ebp-70h]
    call _free
    pop ecx
    mov dword ptr [ebp-70h], ebx

writeStringDigitDestroyed:
    cmp dword ptr [ebp-20h], ebx
    mov byte ptr [ebp-4], 4
    jz writeStringContinue
    push dword ptr [ebp-20h]
    call _free
    pop ecx
    mov dword ptr [ebp-20h], ebx

writeStringContinue:
    dec esi
    jnz writeStringNextDigit

writeStringTerminate:
    cmp dword ptr [ebp-40h], ebx
    mov byte ptr [edi], bl
    pop edi
    pop esi
    jz writeStringDestroyPlace
    push dword ptr [ebp-40h]
    call _free
    pop ecx
    mov dword ptr [ebp-40h], ebx

writeStringDestroyPlace:
    cmp dword ptr [ebp-30h], ebx
    pop ebx
    jz writeStringReturn
    push dword ptr [ebp-30h]
    call _free
    pop ecx

writeStringReturn:
    mov ecx, dword ptr [ebp-0ch]
    mov dword ptr fs:[0], ecx
    leave
    ret 14h
?WriteString@BigInteger@@QAEXPADHPBDHH@Z ENDP

END
