.386
.model flat
option casemap:none

EXTERN ?PushBack@Vector3Vector@@QAEXABUVector3@@@Z:PROC
EXTERN ??AVector3Vector@@QAEAAUVector3@@I@Z:PROC
EXTERN ?PushBack@CompiledOperationVector@@QAEXABUCompiledOperation@@@Z:PROC
EXTERN ?DumpAssembly@ExpressionParser@@QAEXPAD@Z:PROC

.const
PUBLIC prepareEvaluationDumpFilename
prepareEvaluationDumpFilename DB "asm.txt", 0

.code

; FUNCTION: SUMO 0x00405d33
; FUNCTION: EDITOR 0x00405d55
PUBLIC ?PrepareEvaluation@ExpressionParser@@QAEXXZ
?PrepareEvaluation@ExpressionParser@@QAEXXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 38h
    push ebx
    mov ebx, ecx
    lea eax, [ebx+3030h]
    mov ecx, [eax]
    push esi
    push edi
    mov [eax+4], ecx
    lea edi, [ebx+3088h]
    mov eax, [edi]
    mov [edi+4], eax
    mov eax, [ebx+2Ch]
    xor esi, esi
    cmp eax, esi
    jne short prepareEvaluationHasValues
    mov [ebx+3048h], esi
    jmp prepareEvaluationReturn

prepareEvaluationHasValues:
    jle short prepareEvaluationScanParsed
    or DWORD PTR [ebp-1Ch], 0FFFFFFFFh
    or DWORD PTR [ebp-18h], 0FFFFFFFFh
prepareEvaluationInitializeMappings:
    lea eax, [ebp-1Ch]
    push eax
    mov ecx, edi
    mov [ebp-14h], esi
    call ?PushBack@Vector3Vector@@QAEXABUVector3@@@Z
    inc esi
    cmp esi, [ebx+2Ch]
    jl short prepareEvaluationInitializeMappings

prepareEvaluationScanParsed:
    mov esi, [ebx+303Ch]
    mov eax, [ebx+3040h]
    and DWORD PTR [ebp-8], 0
    cmp esi, eax
    jae short prepareEvaluationResultLifetime
prepareEvaluationParsedLoop:
    push DWORD PTR [esi+8]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    cmp DWORD PTR [eax], 0FFFFFFFFh
    jne short prepareEvaluationArguments
    push DWORD PTR [esi+8]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov ecx, [ebp-8]
    mov [eax], ecx
prepareEvaluationArguments:
    and DWORD PTR [ebp-0Ch], 0
    cmp DWORD PTR [esi+4], 0
    jle short prepareEvaluationNextParsed
    lea eax, [esi+0Ch]
    mov [ebp-4], eax
prepareEvaluationArgumentLoop:
    mov eax, [ebp-4]
    push DWORD PTR [eax]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov ecx, [ebp-8]
    inc DWORD PTR [ebp-0Ch]
    add DWORD PTR [ebp-4], 4
    mov [eax+4], ecx
    mov eax, [ebp-0Ch]
    cmp eax, [esi+4]
    jl short prepareEvaluationArgumentLoop
prepareEvaluationNextParsed:
    inc DWORD PTR [ebp-8]
    add esi, 30h
    cmp esi, [ebx+3040h]
    jb prepareEvaluationParsedLoop

prepareEvaluationResultLifetime:
    mov eax, [edi+4]
    sub eax, [edi]
    push 0Ch
    cdq
    pop esi
    idiv esi
    mov ecx, [ebx+3048h]
    cmp ecx, eax
    jge short prepareEvaluationInvalidResult
    push ecx
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov ecx, [ebp-8]
    mov [eax+4], ecx
    jmp short prepareEvaluationCompileParsed
prepareEvaluationInvalidResult:
    and DWORD PTR [ebx+3048h], 0

prepareEvaluationCompileParsed:
    mov esi, [ebx+303Ch]
    and DWORD PTR [ebp-8], 0
    cmp esi, [ebx+3040h]
    jae prepareEvaluationResolveResult
    add esi, 8
    mov [ebp-10h], esi

prepareEvaluationOperationLoop:
    mov eax, [esi-8]
    and DWORD PTR [ebp-4], 0
    cmp DWORD PTR [esi-4], 0
    mov [ebp-38h], eax
    jle short prepareEvaluationSelectOutput
    lea eax, [esi+4]
    mov [ebp-0Ch], eax
prepareEvaluationPatchArgument:
    mov eax, [ebp-0Ch]
    push DWORD PTR [eax]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov eax, [eax+8]
    mov ecx, [ebp-0Ch]
    mov [ecx], eax
    add eax, 4
    lea eax, [eax+eax*2]
    lea edx, [ebx+eax*4]
    mov eax, [ebp-4]
    mov [ebp+eax*4-30h], edx
    inc eax
    add ecx, 4
    cmp eax, [esi-4]
    mov [ebp-4], eax
    mov [ebp-0Ch], ecx
    jl short prepareEvaluationPatchArgument

prepareEvaluationSelectOutput:
    push DWORD PTR [esi]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov eax, [eax+8]
    and DWORD PTR [ebp-4], 0
    cmp DWORD PTR [ebx+2Ch], 0
    mov [ebp-0Ch], eax
    jle prepareEvaluationPatchOutput

prepareEvaluationRegisterLoop:
    push DWORD PTR [ebp-4]
    lea edi, [ebx+3088h]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov ecx, [ebp-8]
    cmp [eax+4], ecx
    jg short prepareEvaluationNextRegister
    push DWORD PTR [ebp-4]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    cmp DWORD PTR [eax], 0
    jl short prepareEvaluationNextRegister
    mov eax, [ebp-4]
    cmp eax, [ebp-0Ch]
    je short prepareEvaluationNextRegister
    push eax
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    cmp DWORD PTR [eax+4], 0FFFFFFFFh
    je short prepareEvaluationNextRegister
    push DWORD PTR [ebp-0Ch]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    push DWORD PTR [ebp-4]
    mov ecx, edi
    mov esi, eax
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    push DWORD PTR [ebp-0Ch]
    mov edi, eax
    movsd
    movsd
    lea ecx, [ebx+3088h]
    movsd
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov ecx, [ebp-4]
    mov esi, [ebp-10h]
    mov [eax+8], ecx
    mov eax, [ebx+2Ch]
    mov [ebp-4], eax
prepareEvaluationNextRegister:
    inc DWORD PTR [ebp-4]
    mov eax, [ebp-4]
    cmp eax, [ebx+2Ch]
    jl prepareEvaluationRegisterLoop

prepareEvaluationPatchOutput:
    push DWORD PTR [esi]
    lea edi, [ebx+3088h]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov eax, [eax+8]
    mov [esi], eax
    lea eax, [eax+eax*2+0Ch]
    lea eax, [ebx+eax*4]
    mov [ebp-34h], eax
    lea eax, [ebp-38h]
    push eax
    lea ecx, [ebx+3030h]
    call ?PushBack@CompiledOperationVector@@QAEXABUCompiledOperation@@@Z
    mov eax, [ebx+3040h]
    inc DWORD PTR [ebp-8]
    add esi, 30h
    lea ecx, [esi-8]
    cmp ecx, eax
    mov [ebp-10h], esi
    jb prepareEvaluationOperationLoop

prepareEvaluationResolveResult:
    push DWORD PTR [ebx+3048h]
    mov ecx, edi
    call ??AVector3Vector@@QAEAAUVector3@@I@Z
    mov eax, [eax+8]
    push OFFSET prepareEvaluationDumpFilename
    mov ecx, ebx
    mov [ebx+3048h], eax
    call ?DumpAssembly@ExpressionParser@@QAEXPAD@Z

prepareEvaluationReturn:
    pop edi
    pop esi
    pop ebx
    leave
    ret
?PrepareEvaluation@ExpressionParser@@QAEXXZ ENDP

END
