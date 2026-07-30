.686
.model flat
option casemap:none

.code

; FUNCTION: SUMO 0x004058ce
; FUNCTION: EDITOR 0x004058f0
PUBLIC ?Evaluate@ExpressionParser@@QAE?AUVector3@@XZ
?Evaluate@ExpressionParser@@QAE?AUVector3@@XZ PROC
    push esi
    mov esi, ecx
    cmp dword ptr [esi + 02ch], 0
    push edi
    jnz short evaluateOperations
    add esi, 010h
    jmp short copyResult
evaluateOperations:
    mov edi, dword ptr [esi + 03030h]
    jmp short compareOperation
executeOperation:
    lea eax, [edi + 4]
    push eax
    call dword ptr [edi]
    pop ecx
    add edi, 01ch
compareOperation:
    cmp edi, dword ptr [esi + 03034h]
    jb short executeOperation
    mov eax, dword ptr [esi + 03048h]
    add eax, 4
    lea eax, [eax + eax * 2]
    lea esi, [esi + eax * 4]
copyResult:
    mov eax, dword ptr [esp + 0ch]
    mov edi, eax
    movsd
    movsd
    movsd
    pop edi
    pop esi
    ret 4
?Evaluate@ExpressionParser@@QAE?AUVector3@@XZ ENDP

END
