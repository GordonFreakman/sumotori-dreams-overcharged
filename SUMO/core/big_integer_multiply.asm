.686
.model flat
option casemap:none

EXTERN ??0BigInteger@@QAE@XZ:PROC
EXTERN ??0BigInteger@@QAE@H@Z:PROC
EXTERN ??0BigInteger@@QAE@AAV0@@Z:PROC
EXTERN ?PadTo@U32Vector@@QAEXI@Z:PROC
EXTERN ??AU32Vector@@QAEAAII@Z:PROC
EXTERN ?TrimLeadingZeros@U32Vector@@QAEXXZ:PROC
EXTERN _free:PROC
EXTERN ?g_bigIntegerMultiplyFlag@@3HA:DWORD

.code

PUBLIC ??DBigInteger@@QAE?AV0@AAV0@@Z
??DBigInteger@@QAE?AV0@AAV0@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 028h
    push ebx
    push esi
    mov esi, ecx
    xor ebx, ebx
    push edi
    lea ecx, [ebp - 028h]
    mov dword ptr [ebp - 8], esi
    mov dword ptr [ebp - 018h], ebx
    call ??0BigInteger@@QAE@XZ
    mov edi, dword ptr [ebp + 0ch]
    mov eax, dword ptr [edi + 4]
    mov ecx, dword ptr [esi + 4]
    sub eax, dword ptr [edi]
    sub ecx, dword ptr [esi]
    sar eax, 2
    sar ecx, 2
    add eax, ecx
    push eax
    lea ecx, [ebp - 028h]
    call ?PadTo@U32Vector@@QAEXI@Z
    mov eax, dword ptr [esi + 4]
    sub eax, dword ptr [esi]
    mov dword ptr [ebp - 4], ebx
    sar eax, 2
    jz multiplyFinalize

multiplyOuter:
    mov eax, dword ptr [edi + 4]
    sub eax, dword ptr [edi]
    sar eax, 2
    mov dword ptr [ebp - 018h], eax
    jz multiplyZero
    push dword ptr [ebp - 4]
    lea ecx, [ebp - 028h]
    call ??AU32Vector@@QAEAAII@Z
    push ebx
    mov ecx, edi
    mov dword ptr [ebp - 014h], eax
    call ??AU32Vector@@QAEAAII@Z
    push dword ptr [ebp - 4]
    mov ecx, esi
    mov dword ptr [ebp - 010h], eax
    call ??AU32Vector@@QAEAAII@Z
    mov eax, dword ptr [eax]
    mov dword ptr [ebp - 0ch], eax
    mov ecx, dword ptr [ebp - 018h]
    mov edi, dword ptr [ebp - 014h]
    mov ebx, 0
    mov esi, dword ptr [ebp - 010h]
multiplyInner:
    mov eax, dword ptr [esi]
    mul dword ptr [ebp - 0ch]
    add dword ptr [edi], eax
    adc dword ptr [edi + 4], edx
    jnb short multiplyNextLimb
    push edi
multiplyPropagate:
    add edi, 4
    add dword ptr [edi + 4], 1
    jb short multiplyPropagate
    pop edi
multiplyNextLimb:
    add edi, 4
    add esi, 4
    dec ecx
    jnz short multiplyInner
    mov eax, dword ptr [ebp - 8]
    mov ecx, dword ptr [eax + 4]
    sub ecx, dword ptr [eax]
    inc dword ptr [ebp - 4]
    mov edi, dword ptr [ebp + 0ch]
    sar ecx, 2
    xor ebx, ebx
    cmp dword ptr [ebp - 4], ecx
    mov esi, eax
    jb multiplyOuter

multiplyFinalize:
    mov eax, dword ptr [edi + 0ch]
    imul eax, dword ptr [esi + 0ch]
    lea ecx, [ebp - 028h]
    mov dword ptr [ebp - 01ch], eax
    call ?TrimLeadingZeros@U32Vector@@QAEXXZ
    cmp dword ptr [?g_bigIntegerMultiplyFlag@@3HA], ebx
    je short multiplyCopyResult
    mov dword ptr [?g_bigIntegerMultiplyFlag@@3HA], 1
multiplyCopyResult:
    mov ecx, dword ptr [ebp + 8]
    lea eax, [ebp - 028h]
    push eax
    call ??0BigInteger@@QAE@AAV0@@Z
multiplyCleanup:
    cmp dword ptr [ebp - 028h], ebx
    je short multiplyReturn
    push dword ptr [ebp - 028h]
    call _free
    pop ecx
multiplyReturn:
    mov eax, dword ptr [ebp + 8]
    pop edi
    pop esi
    pop ebx
    leave
    ret 8

multiplyZero:
    mov ecx, dword ptr [ebp + 8]
    push ebx
    call ??0BigInteger@@QAE@H@Z
    jmp short multiplyCleanup
??DBigInteger@@QAE?AV0@AAV0@@Z ENDP

END
