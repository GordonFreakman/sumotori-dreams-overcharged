.386
.model flat
option casemap:none

EXTERN ___security_cookie:DWORD
EXTERN @__security_check_cookie@4:PROC
EXTERN __ftol2:PROC
EXTERN ?SkipWhitespace@@YAXPAPAD@Z:PROC
EXTERN ?IsIdentifierStart@ExpressionParser@@QAEHD@Z:PROC
EXTERN ?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z:PROC
EXTERN ?CompileExpressionStatement@ExpressionParser@@QAEPADPAD@Z:PROC
EXTERN ?CompileExpressionArguments@ExpressionParser@@QAEHPAUParserExpression@@H@Z:PROC
EXTERN ?CompileBlockStatements@ExpressionParser@@QAEPADPAD@Z:PROC
EXTERN ?FindVariable@ExpressionParser@@QAEPAUParserVariable@@PAD@Z:PROC
EXTERN ?AllocateVariable@ExpressionParser@@QAEPAUParserVariable@@XZ:PROC
EXTERN ?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z:PROC
EXTERN ?CompileFunctionDefinition@ExpressionParser@@QAEPADPAD00@Z:PROC
EXTERN _strcmp:PROC
EXTERN _strcpy:PROC

.const
PUBLIC compileStatementConstantError
compileStatementConstantError DB "Constant cannot be modified", 0
PUBLIC compileStatementRepeatCloseError
compileStatementRepeatCloseError DB "{ for repeat must be closed by }", 0
PUBLIC compileStatementRepeatBraceError
compileStatementRepeatBraceError DB "{ expected for repeat", 0
PUBLIC compileStatementRepeatNegativeError
compileStatementRepeatNegativeError DB "Parameter of repeat cannot be negative", 0
PUBLIC compileStatementRepeatConstantError
compileStatementRepeatConstantError DB "Parameter of repeat must be definit", 0
PUBLIC compileStatementRepeatParenthesisError
compileStatementRepeatParenthesisError DB "( expected after repeat", 0
PUBLIC compileStatementRepeatKeyword
compileStatementRepeatKeyword DB "repeat", 0

.code

; FUNCTION: SUMO 0x004062e4
; FUNCTION: EDITOR 0x00406306
PUBLIC ?CompileStatement@ExpressionParser@@QAEPADPAD@Z
?CompileStatement@ExpressionParser@@QAEPADPAD@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 68h
    mov eax, DWORD PTR [___security_cookie]
    mov [ebp-4], eax
    mov eax, [ebp+8]
    cmp BYTE PTR [eax], 0
    push ebx
    mov ebx, ecx
    jnz short compileStatementNonempty
    xor eax, eax
    jmp compileStatementCookie

compileStatementNonempty:
    lea eax, [ebp+8]
    push edi
    push eax
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov edi, [ebp+8]
    xor eax, eax
    mov al, [edi]
    pop ecx
    mov ecx, ebx
    push eax
    call ?IsIdentifierStart@ExpressionParser@@QAEHD@Z
    test eax, eax
    mov ecx, ebx
    jnz short compileStatementIdentifier
    push edi
    call ?CompileExpressionStatement@ExpressionParser@@QAEPADPAD@Z
    jmp compileStatementPopEdi

compileStatementIdentifier:
    push esi
    lea eax, [ebp-14h]
    push eax
    push edi
    call ?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z
    mov [ebp-18h], eax
    lea eax, [ebp-18h]
    push eax
    call ?SkipWhitespace@@YAXPAPAD@Z
    lea eax, [ebp-14h]
    mov DWORD PTR [esp], OFFSET compileStatementRepeatKeyword
    push eax
    call _strcmp
    test eax, eax
    pop ecx
    pop ecx
    jnz compileStatementNotRepeat
    mov eax, [ebp-18h]
    cmp BYTE PTR [eax], 28h
    jz short compileStatementRepeatArguments
    cmp BYTE PTR [ebx+0Ch], 0
    jnz short compileStatementReturnNull
    mov DWORD PTR [ebx+8], OFFSET compileStatementRepeatParenthesisError

compileStatementSetError:
    mov BYTE PTR [ebx+0Ch], 1

compileStatementReturnNull:
    xor eax, eax
    jmp compileStatementPopEsi

compileStatementRepeatArguments:
    inc DWORD PTR [ebp-18h]
    lea eax, [ebp-18h]
    push eax
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov eax, [ebp-18h]
    pop ecx
    lea esi, [ebx+4]
    mov [esi], eax
    push 1
    lea eax, [ebp-68h]
    push eax
    mov ecx, ebx
    call ?CompileExpressionArguments@ExpressionParser@@QAEHPAUParserExpression@@H@Z
    cmp DWORD PTR [ebp-68h], 0FFFFFFFFh
    jz short compileStatementRepeatCount
    cmp BYTE PTR [ebx+0Ch], 0
    jnz short compileStatementReturnNull
    mov DWORD PTR [ebx+8], OFFSET compileStatementRepeatConstantError
    jmp short compileStatementSetError

compileStatementRepeatCount:
    fld DWORD PTR [ebp-64h]
    call __ftol2
    test eax, eax
    mov [ebp+8], eax
    jge short compileStatementRepeatBody
    cmp BYTE PTR [ebx+0Ch], 0
    jnz short compileStatementReturnNull
    mov DWORD PTR [ebx+8], OFFSET compileStatementRepeatNegativeError
    jmp short compileStatementSetError

compileStatementRepeatBody:
    push esi
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov edi, [esi]
    cmp BYTE PTR [edi], 7Bh
    pop ecx
    jz short compileStatementRepeatLoopSetup
    cmp BYTE PTR [ebx+0Ch], 0
    jnz short compileStatementReturnNull
    mov DWORD PTR [ebx+8], OFFSET compileStatementRepeatBraceError
    jmp short compileStatementSetError

compileStatementRepeatLoopSetup:
    mov eax, [ebp+8]
    inc edi
    test eax, eax
    mov [esi], edi
    jle short compileStatementRepeatLoopDone
    mov [ebp+8], eax

compileStatementRepeatLoop:
    push edi
    mov ecx, ebx
    mov [esi], edi
    call ?CompileBlockStatements@ExpressionParser@@QAEPADPAD@Z
    dec DWORD PTR [ebp+8]
    mov [esi], eax
    jnz short compileStatementRepeatLoop

compileStatementRepeatLoopDone:
    mov eax, [esi]
    cmp BYTE PTR [eax], 7Dh
    jz short compileStatementRepeatSuccess
    cmp BYTE PTR [ebx+0Ch], 0
    jnz compileStatementReturnNull
    mov DWORD PTR [ebx+8], OFFSET compileStatementRepeatCloseError
    jmp compileStatementSetError

compileStatementRepeatSuccess:
    inc eax
    mov [esi], eax
    jmp compileStatementPopEsi

compileStatementNotRepeat:
    mov esi, [ebp-18h]
    mov al, [esi]
    cmp al, 3Dh
    jnz short compileStatementMaybeFunction
    lea eax, [ebp-14h]
    push eax
    mov ecx, ebx
    call ?FindVariable@ExpressionParser@@QAEPAUParserVariable@@PAD@Z
    test eax, eax
    mov [ebp-18h], eax
    jnz short compileStatementHaveVariable
    mov ecx, ebx
    call ?AllocateVariable@ExpressionParser@@QAEPAUParserVariable@@XZ
    lea ecx, [ebp-14h]
    push ecx
    push eax
    mov [ebp-18h], eax
    call _strcpy
    pop ecx
    pop ecx

compileStatementHaveVariable:
    mov eax, [ebp-18h]
    test BYTE PTR [eax+20h], 1
    jz short compileStatementAssign
    cmp BYTE PTR [ebx+0Ch], 0
    jnz compileStatementReturnNull
    mov DWORD PTR [ebx+8], OFFSET compileStatementConstantError
    jmp compileStatementSetError

compileStatementAssign:
    push 0
    lea eax, [ebp-38h]
    inc esi
    push eax
    mov ecx, ebx
    mov [ebx+4], esi
    call ?CompileExpression@ExpressionParser@@QAE?AUParserExpression@@H@Z
    mov esi, eax
    lea edi, [ebp-28h]
    movsd
    movsd
    movsd
    movsd
    mov edi, [ebp-18h]
    add edi, 10h
    lea esi, [ebp-28h]
    movsd
    movsd
    movsd
    movsd
    mov eax, [ebx+4]
    jmp short compileStatementPopEsi

compileStatementMaybeFunction:
    cmp al, 28h
    jnz short compileStatementExpression
    inc esi
    mov al, [esi]
    mov ecx, esi
    jmp short compileStatementFunctionScanTest

compileStatementFunctionScan:
    cmp al, 28h
    jz short compileStatementFunctionCloseCheck
    cmp al, 29h
    jz short compileStatementFunctionFoundClose
    inc ecx
    mov al, [ecx]

compileStatementFunctionScanTest:
    test al, al
    jnz short compileStatementFunctionScan

compileStatementFunctionCloseCheck:
    cmp BYTE PTR [ecx], 29h
    jnz short compileStatementExpression

compileStatementFunctionFoundClose:
    lea eax, [ebp-18h]
    inc ecx
    push eax
    mov [ebp-18h], ecx
    call ?SkipWhitespace@@YAXPAPAD@Z
    mov eax, [ebp-18h]
    cmp BYTE PTR [eax], 3Dh
    pop ecx
    jnz short compileStatementExpression
    inc eax
    push eax
    push esi
    lea eax, [ebp-14h]
    push eax
    mov ecx, ebx
    call ?CompileFunctionDefinition@ExpressionParser@@QAEPADPAD00@Z
    jmp short compileStatementPopEsi

compileStatementExpression:
    mov ecx, ebx
    push edi
    call ?CompileExpressionStatement@ExpressionParser@@QAEPADPAD@Z

compileStatementPopEsi:
    pop esi

compileStatementPopEdi:
    pop edi

compileStatementCookie:
    mov ecx, [ebp-4]
    pop ebx
    call @__security_check_cookie@4
    leave
    ret 4
?CompileStatement@ExpressionParser@@QAEPADPAD@Z ENDP

END
