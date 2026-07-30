.386
.model flat
option casemap:none

EXTERN ___security_cookie:DWORD
EXTERN @__security_check_cookie@4:PROC
EXTERN ?CompileValue@ExpressionParser@@QAE?AUParserExpression@@H@Z:PROC
EXTERN ?SkipWhitespace@@YAXPAPAD@Z:PROC
EXTERN ?FindOperator@ExpressionParser@@QAEHD@Z:PROC
EXTERN ??AOperatorEntryVector@@QAEAAUOperatorEntry@@I@Z:PROC
EXTERN ?CompileOperation@ExpressionParser@@QAE?AUParserExpression@@P6AXPAUParserBuiltinCall@@@ZHPAU2@PAD@Z:PROC

.const
PUBLIC compileExpressionInvalidError
compileExpressionInvalidError DB "Unknown Error", 0
PUBLIC compileExpressionCloseError
compileExpressionCloseError DB "Expected )", 0
PUBLIC compileExpressionOperatorError
compileExpressionOperatorError DB "Operator expected", 0
PUBLIC compileExpressionUnexpectedCloseError
compileExpressionUnexpectedCloseError DB "Unexpected )", 0

.code

; FUNCTION: SUMO 0x00405f93
; FUNCTION: EDITOR 0x00405fb5
PUBLIC ?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z
?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z PROC
    push ebp
    lea ebp, [esp-70h]
    sub esp, 494h
    mov eax, DWORD PTR [___security_cookie]
    and DWORD PTR [ebp+24h], 0
    push ebx
    mov [ebp+6Ch], eax
    push esi
    lea eax, [ebp-424h]
    push edi
    mov ebx, ecx
    mov [ebp+28h], eax

compileExpressionParseValue:
    push DWORD PTR [ebp+7Ch]
    lea eax, [ebp-4]
    push eax
    mov ecx, ebx
    call ?CompileValue@ExpressionParser@@QAE?AUParserExpression@@H@Z
    cmp BYTE PTR [ebx+0Ch], 0
    mov edi, [ebp+28h]
    mov esi, eax
    movsd
    movsd
    movsd
    movsd
    jnz compileExpressionErrorResult
    lea esi, [ebx+4]
    push esi
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov eax, [esi]
    pop ecx
    mov cl, [eax]
    test cl, cl
    jz short compileExpressionParsedToken
    cmp cl, 3Bh
    jz short compileExpressionParsedToken
    cmp cl, 29h
    jz short compileExpressionParsedToken
    cmp cl, 2Ch
    jz short compileExpressionParsedToken
    inc eax
    push ecx
    mov ecx, ebx
    mov [esi], eax
    call ?FindOperator@ExpressionParser@@QAEHD@Z
    cmp al, 0FFh
    mov ecx, [ebp+24h]
    DB 088h, 044h, 00Dh, 02Ch
    jz short compileExpressionOperatorFailure

compileExpressionParsedToken:
    inc DWORD PTR [ebp+24h]
    add DWORD PTR [ebp+28h], 10h
    cmp BYTE PTR [ebx+0Ch], 0
    jnz short compileExpressionParseDone
    mov eax, [esi]
    mov al, [eax]
    test al, al
    jz short compileExpressionParseDone
    cmp al, 3Bh
    jz short compileExpressionParseDone
    cmp al, 29h
    jz short compileExpressionParseDone
    cmp al, 2Ch
    jnz compileExpressionParseValue

compileExpressionParseDone:
    mov eax, [ebx+4]
    mov cl, [eax]
    cmp cl, 29h
    jnz short compileExpressionRequireClose
    cmp DWORD PTR [ebp+7Ch], 0
    jnz short compileExpressionConsumeClose
    cmp BYTE PTR [ebx+0Ch], 0
    jnz compileExpressionErrorResult
    mov BYTE PTR [ebx+0Ch], 1
    mov DWORD PTR [ebx+8], OFFSET compileExpressionUnexpectedCloseError
    jmp compileExpressionErrorResult

compileExpressionOperatorFailure:
    cmp BYTE PTR [ebx+0Ch], 0
    jnz compileExpressionErrorResult
    mov BYTE PTR [ebx+0Ch], 1
    mov DWORD PTR [ebx+8], OFFSET compileExpressionOperatorError
    jmp compileExpressionErrorResult

compileExpressionConsumeClose:
    cmp cl, 29h
    jz short compileExpressionAdvanceClose

compileExpressionRequireClose:
    cmp DWORD PTR [ebp+7Ch], 0
    jz short compileExpressionMaybeAdvanceClose
    cmp BYTE PTR [ebx+0Ch], 0
    jnz compileExpressionErrorResult
    mov BYTE PTR [ebx+0Ch], 1
    mov DWORD PTR [ebx+8], OFFSET compileExpressionCloseError
    jmp compileExpressionErrorResult

compileExpressionMaybeAdvanceClose:
    cmp cl, 29h
    jnz short compileExpressionReduceSetup

compileExpressionAdvanceClose:
    inc eax
    mov [ebx+4], eax

compileExpressionReduceSetup:
    mov eax, [ebx+3078h]
    test eax, eax
    mov [ebp+18h], eax
    jl compileExpressionValidate

compileExpressionPrecedenceLoop:
    xor edi, edi
    inc edi
    cmp [ebp+24h], edi
    mov [ebp+1Ch], edi
    mov [ebp+7Ch], edi
    jle compileExpressionFinishPrecedence
    lea eax, [ebp-414h]
    mov [ebp+20h], eax
    lea eax, [ebp+2Ch]
    lea esi, [ebp-424h]
    dec eax
    mov [ebp+28h], esi
    mov [ebp+10h], eax
    jmp short compileExpressionReduceTest

compileExpressionReduceContinue:
    mov edi, [ebp+7Ch]
    mov eax, [ebp+10h]
    mov esi, [ebp+28h]

compileExpressionReduceTest:
    DB 00Fh, 0BEh, 004h, 038h
    push eax
    lea ecx, [ebx+307Ch]
    mov [ebp+0Ch], eax
    call ??AOperatorEntryVector@@QAEAAUOperatorEntry@@I@Z
    movsx eax, BYTE PTR [eax+1]
    cmp eax, [ebp+18h]
    jnz short compileExpressionCarryOperator
    lea edi, [ebp-24h]
    movsd
    movsd
    movsd
    push DWORD PTR [ebp+0Ch]
    movsd
    mov esi, [ebp+20h]
    lea edi, [ebp-14h]
    movsd
    movsd
    movsd
    movsd
    lea esi, [ebx+307Ch]
    mov ecx, esi
    mov DWORD PTR [ebp+14h], 58706Fh
    call ??AOperatorEntryVector@@QAEAAUOperatorEntry@@I@Z
    mov al, [eax]
    mov [ebp+16h], al
    lea eax, [ebp+14h]
    push eax
    lea eax, [ebp-24h]
    push eax
    push 2
    push DWORD PTR [ebp+0Ch]
    mov ecx, esi
    call ??AOperatorEntryVector@@QAEAAUOperatorEntry@@I@Z
    push DWORD PTR [eax+4]
    lea eax, [ebp-4]
    push eax
    mov ecx, ebx
    call ?CompileOperation@ExpressionParser@@QAE?AUParserExpression@@P6AXPAUParserBuiltinCall@@@ZHPAU2@PAD@Z
    mov ecx, [ebp+10h]
    mov edx, [ebp+1Ch]
    mov edi, [ebp+28h]
    mov esi, eax
    mov eax, [ebp+7Ch]
    DB 08Ah, 044h, 005h, 02Ch
    inc DWORD PTR [ebp+7Ch]
    add DWORD PTR [ebp+20h], 10h
    DB 088h, 004h, 011h
    jmp short compileExpressionCopyReduced

compileExpressionCarryOperator:
    DB 08Ah, 044h, 03Dh, 02Ch
    mov ecx, [ebp+1Ch]
    inc DWORD PTR [ebp+7Ch]
    lea edi, [esi+10h]
    mov esi, [ebp+20h]
    add DWORD PTR [ebp+20h], 10h
    inc DWORD PTR [ebp+1Ch]
    add DWORD PTR [ebp+28h], 10h
    DB 088h, 044h, 00Dh, 02Ch

compileExpressionCopyReduced:
    mov eax, [ebp+7Ch]
    cmp eax, [ebp+24h]
    movsd
    movsd
    movsd
    movsd
    jl compileExpressionReduceContinue

compileExpressionFinishPrecedence:
    dec DWORD PTR [ebp+18h]
    mov eax, [ebp+1Ch]
    mov [ebp+24h], eax
    jns compileExpressionPrecedenceLoop

compileExpressionValidate:
    cmp DWORD PTR [ebp+24h], 1
    jz short compileExpressionFinalErrorCheck
    cmp BYTE PTR [ebx+0Ch], 0
    jnz short compileExpressionErrorResult
    mov BYTE PTR [ebx+0Ch], 1
    mov DWORD PTR [ebx+8], OFFSET compileExpressionInvalidError

compileExpressionFinalErrorCheck:
    cmp BYTE PTR [ebx+0Ch], 0
    jz short compileExpressionSuccessResult

compileExpressionErrorResult:
    lea esi, [ebx+1Ch]
    jmp short compileExpressionReturn

compileExpressionSuccessResult:
    lea esi, [ebp-424h]

compileExpressionReturn:
    mov eax, [ebp+78h]
    mov ecx, [ebp+6Ch]
    mov edi, eax
    movsd
    movsd
    movsd
    movsd
    pop edi
    pop esi
    pop ebx
    call @__security_check_cookie@4
    add ebp, 70h
    leave
    ret 8
?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z ENDP

END
