.386
.model flat
option casemap:none

EXTERN ___security_cookie:DWORD
EXTERN @__security_check_cookie@4:PROC
EXTERN ?SkipWhitespace@@YAXPAPAD@Z:PROC
EXTERN ?IsIdentifierStart@ExpressionParser@@QAEHD@Z:PROC
EXTERN ?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z:PROC
EXTERN ?FindUserFunction@ExpressionParser@@QAEPAUUserFunction@@PAD@Z:PROC
EXTERN ??ABuiltinFunctionVector@@QAEAAUBuiltinFunctionEntry@@I@Z:PROC
EXTERN ?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z:PROC
EXTERN ?CompileExpressionArguments@ExpressionParser@@QAEHPAUParserExpression@@H@Z:PROC
EXTERN ?CompileOperation@ExpressionParser@@QAE?AUParserExpression@@P6AXPAUParserBuiltinCall@@@ZHPAU2@PAD@Z:PROC
EXTERN ?CompileStatements@ExpressionParser@@QAEPADPAD@Z:PROC
EXTERN ?FindVariableAtCursor@ExpressionParser@@QAEPAUParserVariable@@PAD@Z:PROC
EXTERN ?IsDigit@ExpressionParser@@QAEHD@Z:PROC
EXTERN ??ACharVector@@QAEAADI@Z:PROC
EXTERN ?g_gameSoundLogBase@@3NB:QWORD
EXTERN _strcmp:PROC
EXTERN _strcpy:PROC

.const
PUBLIC compileValueFractionScale
compileValueFractionScale REAL8 0.1
PUBLIC compileValueExpectedError
compileValueExpectedError DB "Value or ( expected", 0
PUBLIC compileValueUnknownNameError
compileValueUnknownNameError DB "No such command or variable", 0
PUBLIC compileValueUndefinedFunctionError
compileValueUndefinedFunctionError DB "Undefined Function", 0
PUBLIC compileValueMinusError
compileValueMinusError DB "minus not supported now", 0
PUBLIC compileValueParameterError
compileValueParameterError DB "No parameter expected", 0

.code

; FUNCTION: SUMO 0x00406565
; FUNCTION: EDITOR 0x00406587
PUBLIC ?CompileValue@ExpressionParser@@QAE?AUParserExpression@@H@Z
?CompileValue@ExpressionParser@@QAE?AUParserExpression@@H@Z PROC
    push ebp
    lea ebp, [esp-358h]
    sub esp, 410h
    mov eax, DWORD PTR [___security_cookie]
    push ebx
    push esi
    push edi
    mov ebx, ecx
    lea esi, [ebx+1Ch]
    mov [ebp+7Ch], esi
    lea edi, [ebp+48h]
    movsd
    movsd
    movsd
    movsd
    mov [ebp+354h], eax
    mov BYTE PTR [ebp+83h], 0
    lea esi, [ebx+4]
    jmp short compileValueSkipSpaceTest

compileValueSkipSpace:
    inc DWORD PTR [esi]
compileValueSkipSpaceTest:
    mov eax, [esi]
    cmp BYTE PTR [eax], 20h
    je short compileValueSkipSpace
    mov cl, [eax]
    cmp cl, 28h
    jne short compileValueUnaryMinusTest
    inc eax
    mov [esi], eax
    mov eax, [ebp+364h]
    inc eax
    push eax
    push DWORD PTR [ebp+360h]
    mov ecx, ebx
    call ?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z
    mov eax, [ebp+360h]
    jmp compileValueCookie

compileValueUnaryMinusTest:
    cmp cl, 2Dh
    jne short compileValueToken
compileValueUnaryMinus:
    xor BYTE PTR [ebp+83h], 1
    inc DWORD PTR [esi]
    push esi
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov eax, [esi]
    cmp BYTE PTR [eax], 2Dh
    pop ecx
    je short compileValueUnaryMinus

compileValueToken:
    mov edi, [esi]
    xor eax, eax
    mov al, [edi]
    mov ecx, ebx
    mov BYTE PTR [ebp+364h], al
    push eax
    call ?IsIdentifierStart@ExpressionParser@@QAEHD@Z
    test eax, eax
    mov ecx, ebx
    je compileValueNumberTest
    lea eax, [ebp+344h]
    push eax
    push edi
    call ?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z
    mov [ebp+78h], eax
    lea eax, [ebp+78h]
    push eax
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov eax, [ebp+78h]
    cmp BYTE PTR [eax], 28h
    pop ecx
    jne compileValueVariable
    inc eax
    mov [esi], eax
    lea esi, [ebx+3068h]
    mov eax, [esi+4]
    sub eax, [esi]
    push 18h
    cdq
    pop ecx
    idiv ecx
    xor edi, edi
    test eax, eax
    jle short compileValueFindUser

compileValueFindBuiltin:
    push edi
    mov ecx, esi
    call ??ABuiltinFunctionVector@@QAEAAUBuiltinFunctionEntry@@I@Z
    push eax
    lea eax, [ebp+344h]
    push eax
    call _strcmp
    test eax, eax
    pop ecx
    pop ecx
    je short compileValueBuiltin
    mov eax, [esi+4]
    sub eax, [esi]
    push 18h
    cdq
    pop ecx
    idiv ecx
    inc edi
    cmp edi, eax
    jl short compileValueFindBuiltin

compileValueFindUser:
    lea eax, [ebp+344h]
    push eax
    mov ecx, ebx
    call ?FindUserFunction@ExpressionParser@@QAEPAUUserFunction@@PAD@Z
    mov esi, eax
    test esi, esi
    mov [ebp+74h], esi
    je compileValueUndefinedFunction
    mov eax, [esi+110h]
    test eax, eax
    mov edi, [ebx+3060h]
    mov [ebp+64h], edi
    je compileValueNoParameters
    push eax
    lea eax, [ebp-0B8h]
    push eax
    mov ecx, ebx
    call ?CompileExpressionArguments@ExpressionParser@@QAEHPAUParserExpression@@H@Z
    cmp BYTE PTR [ebx+0Ch], 0
    je short compileValueBuildParameters
    mov [ebx+3060h], edi
    jmp compileValueErrorResult

compileValueBuiltin:
    push edi
    mov ecx, esi
    call ??ABuiltinFunctionVector@@QAEAAUBuiltinFunctionEntry@@I@Z
    push DWORD PTR [eax+10h]
    lea eax, [ebp-0B8h]
    push eax
    mov ecx, ebx
    call ?CompileExpressionArguments@ExpressionParser@@QAEHPAUParserExpression@@H@Z
    cmp BYTE PTR [ebx+0Ch], 0
    jne compileValueErrorResult
    push edi
    mov ecx, esi
    call ??ABuiltinFunctionVector@@QAEAAUBuiltinFunctionEntry@@I@Z
    push eax
    lea eax, [ebp-0B8h]
    push eax
    push edi
    mov ecx, esi
    call ??ABuiltinFunctionVector@@QAEAAUBuiltinFunctionEntry@@I@Z
    push DWORD PTR [eax+10h]
    mov ecx, esi
    push edi
    call ??ABuiltinFunctionVector@@QAEAAUBuiltinFunctionEntry@@I@Z
    push DWORD PTR [eax+14h]
    lea eax, [ebp+58h]
    push eax
    mov ecx, ebx
    call ?CompileOperation@ExpressionParser@@QAE?AUParserExpression@@P6AXPAUParserBuiltinCall@@@ZHPAU2@PAD@Z
    mov esi, eax
    jmp compileValueNegationCheck

compileValueBuildParameters:
    xor eax, eax
    cmp [esi+110h], eax
    mov [ebp+364h], eax
    jle short compileValueTerminateParameters
    lea edi, [ebp+94h]
    lea eax, [ebp-0B8h]
    add esi, 10h
    mov [ebp+78h], edi
    mov [ebp+68h], eax
    mov [ebp+6Ch], esi
    jmp short compileValueCopyParameter

compileValueParameterLoop:
    mov edi, [ebp+78h]
compileValueCopyParameter:
    push DWORD PTR [ebp+6Ch]
    lea eax, [edi-10h]
    push eax
    call _strcpy
    mov esi, [ebp+68h]
    mov eax, [ebp+78h]
    and DWORD PTR [eax+10h], 0
    and DWORD PTR [eax+18h], 0
    inc DWORD PTR [ebp+364h]
    add DWORD PTR [ebp+6Ch], 10h
    add DWORD PTR [ebp+68h], 10h
    movsd
    movsd
    pop ecx
    pop ecx
    lea ecx, [eax+1Ch]
    mov [eax+14h], ecx
    mov ecx, [ebp+364h]
    movsd
    add eax, 2Ch
    mov [ebp+78h], eax
    mov eax, [ebp+74h]
    movsd
    cmp ecx, [eax+110h]
    jl short compileValueParameterLoop
    mov esi, [ebp+74h]
    mov eax, ecx

compileValueTerminateParameters:
    imul eax, 2Ch
    DB 083h, 064h, 005h, 07Ch, 000h
    lea eax, [ebp+84h]
    mov [ebx+3060h], eax
    jmp short compileValueCompileUserBody

compileValueNoParameters:
    lea edi, [ebx+4]
    push edi
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov eax, [edi]
    cmp BYTE PTR [eax], 29h
    pop ecx
    je short compileValueConsumeClose
    cmp BYTE PTR [ebx+0Ch], 0
    jne short compileValueRestoreVariables
    mov BYTE PTR [ebx+0Ch], 1
    mov DWORD PTR [ebx+8], OFFSET compileValueParameterError
compileValueRestoreVariables:
    mov eax, [ebp+64h]
    mov [ebx+3060h], eax
    jmp compileValueErrorResult
compileValueConsumeClose:
    inc eax
    mov [edi], eax

compileValueCompileUserBody:
    mov eax, [ebx+4]
    push 0
    lea ecx, [esi+114h]
    mov [ebp+74h], eax
    call ??ACharVector@@QAEAADI@Z
    push eax
    mov ecx, ebx
    mov [ebx+4], eax
    call ?CompileStatements@ExpressionParser@@QAEPADPAD@Z
    mov eax, [ebp+74h]
    mov [ebx+4], eax
    mov eax, [ebp+64h]
    lea esi, [ebx+304Ch]
    mov [ebx+3060h], eax

compileValueNegationCheck:
    cmp BYTE PTR [ebp+83h], 0
    lea edi, [ebp+48h]
    movsd
    movsd
    movsd
    movsd
    je compileValueLocalResult
    cmp BYTE PTR [ebx+0Ch], 0
    jne short compileValueErrorResult
    mov DWORD PTR [ebx+8], OFFSET compileValueMinusError
    jmp short compileValueSetError

compileValueUndefinedFunction:
    cmp BYTE PTR [ebx+0Ch], 0
    jne short compileValueErrorResult
    mov DWORD PTR [ebx+8], OFFSET compileValueUndefinedFunctionError
    jmp short compileValueSetError

compileValueVariable:
    push DWORD PTR [esi]
    mov ecx, ebx
    call ?FindVariableAtCursor@ExpressionParser@@QAEPAUParserVariable@@PAD@Z
    mov edi, eax
    test edi, edi
    je short compileValueUnknownName
    push 0
    push DWORD PTR [esi]
    mov ecx, ebx
    call ?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z
    mov [esi], eax
    lea esi, [edi+10h]
    jmp compileValueCopyResult

compileValueUnknownName:
    cmp BYTE PTR [ebx+0Ch], 0
    jne short compileValueErrorResult
    mov DWORD PTR [ebx+8], OFFSET compileValueUnknownNameError
    jmp short compileValueSetError

compileValueNumberTest:
    push DWORD PTR [ebp+364h]
    call ?IsDigit@ExpressionParser@@QAEHD@Z
    test eax, eax
    jne short compileValueIntegerStart
    cmp BYTE PTR [ebx+0Ch], al
    jne short compileValueErrorResult
    mov DWORD PTR [ebx+8], OFFSET compileValueExpectedError
compileValueSetError:
    mov BYTE PTR [ebx+0Ch], 1
compileValueErrorResult:
    mov esi, [ebp+7Ch]
    jmp compileValueCopyResult

compileValueIntegerStart:
    fld1
    fstp QWORD PTR [ebp+70h]
    fldz
    fstp QWORD PTR [ebp+60h]
compileValueIntegerLoop:
    mov eax, [esi]
    movsx ecx, BYTE PTR [eax]
    sub ecx, 30h
    mov [ebp+364h], ecx
    lea edi, [eax+1]
    mov eax, edi
    fild DWORD PTR [ebp+364h]
    mov [esi], edi
    fld QWORD PTR [ebp+60h]
    movsx eax, BYTE PTR [eax]
    fmul QWORD PTR [?g_gameSoundLogBase@@3NB]
    push eax
    faddp st(1), st
    mov ecx, ebx
    fstp QWORD PTR [ebp+60h]
    call ?IsDigit@ExpressionParser@@QAEHD@Z
    test eax, eax
    jne short compileValueIntegerLoop
    cmp BYTE PTR [edi], 2Eh
    jne short compileValueApplySign
    inc edi
    mov [esi], edi
    mov al, [edi]
    jmp short compileValueFractionTest

compileValueFractionLoop:
    movsx eax, BYTE PTR [edi]
    fld QWORD PTR [ebp+70h]
    fmul QWORD PTR [compileValueFractionScale]
    sub eax, 30h
    mov [ebp+364h], eax
    inc edi
    fstp QWORD PTR [ebp+70h]
    mov eax, edi
    fild DWORD PTR [ebp+364h]
    mov [esi], edi
    movsx eax, BYTE PTR [eax]
    fmul QWORD PTR [ebp+70h]
    fadd QWORD PTR [ebp+60h]
    fstp QWORD PTR [ebp+60h]
compileValueFractionTest:
    mov ecx, ebx
    push eax
    call ?IsDigit@ExpressionParser@@QAEHD@Z
    test eax, eax
    jne short compileValueFractionLoop

compileValueApplySign:
    cmp BYTE PTR [ebp+83h], 0
    je short compileValueConvert
    fld QWORD PTR [ebp+60h]
    fchs
    fstp QWORD PTR [ebp+60h]
compileValueConvert:
    fld QWORD PTR [ebp+60h]
    mov eax, [ebx]
    or DWORD PTR [ebp+48h], 0FFFFFFFFh
    push ecx
    push ecx
    lea ecx, [ebp+5Ch]
    fstp QWORD PTR [esp]
    push ecx
    mov ecx, ebx
    call DWORD PTR [eax]
    mov esi, eax
    lea edi, [ebp+4Ch]
    movsd
    movsd
    movsd

compileValueLocalResult:
    lea esi, [ebp+48h]
compileValueCopyResult:
    mov eax, [ebp+360h]
    mov edi, eax
    movsd
    movsd
    movsd
    movsd
compileValueCookie:
    mov ecx, [ebp+354h]
    pop edi
    pop esi
    pop ebx
    call @__security_check_cookie@4
    add ebp, 358h
    leave
    ret 8
?CompileValue@ExpressionParser@@QAE?AUParserExpression@@H@Z ENDP

END
