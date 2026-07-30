.686
.model flat
option casemap:none

EXTERN ?PadTo@U32Vector@@QAEXI@Z:PROC
EXTERN ??AU32Vector@@QAEAAII@Z:PROC
EXTERN ?Invert@U32Vector@@QAEXXZ:PROC
EXTERN ?TrimLeadingZeros@U32Vector@@QAEXXZ:PROC
EXTERN ??EBigInteger@@QAEXH@Z:PROC
EXTERN ?SumoAssert@@YAX_N@Z:PROC

.code

PUBLIC ??ZBigInteger@@QAEXAAV0@@Z
??ZBigInteger@@QAEXAAV0@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 010h
    push ebx
    mov ebx, ecx
    mov eax, dword ptr [ebx + 0ch]
    push esi
    mov esi, dword ptr [ebp + 8]
    cmp eax, dword ptr [esi + 0ch]
    je short subtractMagnitudes
    neg eax
    push esi
    mov dword ptr [ebx + 0ch], eax
    call ??YBigInteger@@QAEXAAV0@@Z
    neg dword ptr [ebx + 0ch]
    jmp subtractReturn

subtractMagnitudes:
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [ebx + 4]
    sub eax, dword ptr [esi]
    sub ecx, dword ptr [ebx]
    sar eax, 2
    sar ecx, 2
    cmp ecx, eax
    jbe short subtractSizeReady
    mov eax, ecx
subtractSizeReady:
    inc eax
    push eax
    mov ecx, ebx
    call ?PadTo@U32Vector@@QAEXI@Z
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    test eax, 0fffffffch
    jz subtractReturn
    push edi
    xor edi, edi
    push edi
    mov ecx, esi
    call ??AU32Vector@@QAEAAII@Z
    push edi
    mov ecx, ebx
    mov dword ptr [ebp - 010h], eax
    call ??AU32Vector@@QAEAAII@Z
    mov ecx, dword ptr [ebx + 4]
    sub ecx, dword ptr [ebx]
    mov dword ptr [ebp - 00ch], eax
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    sar ecx, 2
    sar eax, 2
    sub ecx, eax
    cmp eax, edi
    mov dword ptr [ebp - 8], eax
    mov dword ptr [ebp - 4], ecx
    je short subtractNormalize
    mov dword ptr [ebp + 8], edi
    mov esi, dword ptr [ebp - 010h]
    mov edi, dword ptr [ebp - 00ch]
    xor edx, edx
    mov ecx, dword ptr [ebp - 8]
subtractSourceLimbs:
    mov eax, dword ptr [esi]
    sub dword ptr [edi], edx
    mov edx, 0
    adc edx, 0
    sub dword ptr [edi], eax
    adc edx, 0
    add edi, 4
    add esi, 4
    dec ecx
    jnz short subtractSourceLimbs
    mov ecx, dword ptr [ebp - 4]
subtractCarryLimbs:
    sub dword ptr [edi], edx
    mov edx, 0
    adc edx, 0
    add edi, 4
    dec ecx
    jnz short subtractCarryLimbs
    mov dword ptr [ebp + 8], edx
    cmp dword ptr [ebp + 8], 0
    je short subtractNormalize
    neg dword ptr [ebx + 0ch]
    mov ecx, ebx
    call ?Invert@U32Vector@@QAEXXZ
    push 0
    mov ecx, ebx
    call ??EBigInteger@@QAEXH@Z
subtractNormalize:
    mov ecx, ebx
    call ?TrimLeadingZeros@U32Vector@@QAEXXZ
    pop edi
subtractReturn:
    pop esi
    pop ebx
    leave
    ret 4
??ZBigInteger@@QAEXAAV0@@Z ENDP

PUBLIC ??YBigInteger@@QAEXAAV0@@Z
??YBigInteger@@QAEXAAV0@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 0ch
    push ebx
    push esi
    mov esi, dword ptr [ebp + 8]
    mov ebx, ecx
    cmp esi, ebx
    setnz al
    push eax
    call ?SumoAssert@@YAX_N@Z
    mov eax, dword ptr [ebx + 0ch]
    add esp, 4
    cmp eax, dword ptr [esi + 0ch]
    je short addMagnitudes
    neg eax
    push esi
    mov dword ptr [ebx + 0ch], eax
    call ??ZBigInteger@@QAEXAAV0@@Z
    neg dword ptr [ebx + 0ch]
    jmp addReturn

addMagnitudes:
    mov eax, dword ptr [esi + 4]
    mov ecx, dword ptr [ebx + 4]
    sub eax, dword ptr [esi]
    sub ecx, dword ptr [ebx]
    sar eax, 2
    sar ecx, 2
    cmp ecx, eax
    jbe short addSizeReady
    mov eax, ecx
addSizeReady:
    inc eax
    push eax
    mov ecx, ebx
    call ?PadTo@U32Vector@@QAEXI@Z
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    test eax, 0fffffffch
    jz short addReturn
    push 0
    mov ecx, esi
    call ??AU32Vector@@QAEAAII@Z
    push 0
    mov ecx, ebx
    mov dword ptr [ebp - 0ch], eax
    call ??AU32Vector@@QAEAAII@Z
    mov ecx, dword ptr [ebx + 4]
    sub ecx, dword ptr [ebx]
    mov dword ptr [ebp - 8], eax
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    sar ecx, 2
    sar eax, 2
    sub ecx, eax
    test eax, eax
    mov dword ptr [ebp - 4], eax
    mov dword ptr [ebp + 8], ecx
    je short addNormalize
    push edi
    mov esi, dword ptr [ebp - 0ch]
    mov edi, dword ptr [ebp - 8]
    xor edx, edx
    mov ecx, dword ptr [ebp - 4]
addSourceLimbs:
    mov eax, dword ptr [esi]
    add dword ptr [edi], edx
    mov edx, 0
    adc edx, 0
    add dword ptr [edi], eax
    adc edx, 0
    add edi, 4
    add esi, 4
    dec ecx
    jnz short addSourceLimbs
    mov ecx, dword ptr [ebp + 8]
addCarryLimbs:
    add dword ptr [edi], edx
    mov edx, 0
    adc edx, 0
    add edi, 4
    dec ecx
    jnz short addCarryLimbs
    pop edi
addNormalize:
    mov ecx, ebx
    call ?TrimLeadingZeros@U32Vector@@QAEXXZ
addReturn:
    pop esi
    pop ebx
    leave
    ret 4
??YBigInteger@@QAEXAAV0@@Z ENDP

END
