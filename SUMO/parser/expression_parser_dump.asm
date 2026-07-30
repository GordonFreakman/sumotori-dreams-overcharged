.686
.model flat
option casemap:none

EXTERN _fopen:PROC
EXTERN _fprintf:PROC
EXTERN _fclose:PROC
EXTERN ??AParserRegisterInfoVector@@QAEAAUParserRegisterInfo@@I@Z:PROC

EXTERN ??_C@_01NOFIACDB@w?$AA@:BYTE
EXTERN ??_C@_0BH@DEDDKIJK@Const?3?5r?$CFd?5?$DN?5?$CFg?0?$CFg?0?$CFg?6?$AA@:BYTE
EXTERN ??_C@_08GDKOHEJO@?$CFs?5r?$CFd?0?5?$AA@:BYTE
EXTERN ??_C@_03CAJKGCFM@r?$CFd?$AA@:BYTE
EXTERN ??_C@_01IHBHIGKO@?0?$AA@:BYTE
EXTERN ??_C@_01EEMJAFIK@?6?$AA@:BYTE
EXTERN ??_C@_0N@MMEGJIFO@RESULT?3?5r?$CFd?6?$AA@:BYTE

.code

; FUNCTION: SUMO 0x00405888
; FUNCTION: EDITOR 0x004058aa
PUBLIC ?DumpAssembly@ExpressionParser@@QAEXPAD@Z
?DumpAssembly@ExpressionParser@@QAEXPAD@Z PROC
    push ebp
    mov ebp, esp
    push ecx
    push ebx
    push esi
    push edi
    push OFFSET ??_C@_01NOFIACDB@w?$AA@
    push dword ptr [ebp + 8]
    mov edi, ecx
    call _fopen
    xor ebx, ebx
    cmp dword ptr [edi + 02ch], ebx
    pop ecx
    pop ecx
    mov dword ptr [ebp + 8], eax
    jle short constantsDone
    lea esi, [edi + 034h]
constantLoop:
    push ebx
    lea ecx, [edi + 03088h]
    call ??AParserRegisterInfoVector@@QAEAAUParserRegisterInfo@@I@Z
    cmp dword ptr [eax], -1
    jnz short nextConstant
    fld dword ptr [esi + 4]
    sub esp, 018h
    fstp qword ptr [esp + 010h]
    fld dword ptr [esi]
    fstp qword ptr [esp + 8]
    fld dword ptr [esi - 4]
    fstp qword ptr [esp]
    push ebx
    push OFFSET ??_C@_0BH@DEDDKIJK@Const?3?5r?$CFd?5?$DN?5?$CFg?0?$CFg?0?$CFg?6?$AA@
    push dword ptr [ebp + 8]
    call _fprintf
    add esp, 024h
nextConstant:
    inc ebx
    add esi, 0ch
    cmp ebx, dword ptr [edi + 02ch]
    jl short constantLoop

constantsDone:
    mov esi, dword ptr [edi + 0303ch]
    jmp short compareOperation
operationLoop:
    lea eax, [esi + 020h]
    push dword ptr [eax - 018h]
    push eax
    push OFFSET ??_C@_08GDKOHEJO@?$CFs?5r?$CFd?0?5?$AA@
    push dword ptr [ebp + 8]
    call _fprintf
    and dword ptr [ebp - 4], 0
    add esp, 010h
    cmp dword ptr [esi + 4], 0
    jle short argumentsDone
    lea ebx, [esi + 0ch]
argumentLoop:
    push dword ptr [ebx]
    push OFFSET ??_C@_03CAJKGCFM@r?$CFd?$AA@
    push dword ptr [ebp + 8]
    call _fprintf
    mov eax, dword ptr [esi + 4]
    add esp, 0ch
    dec eax
    cmp dword ptr [ebp - 4], eax
    jz short skipComma
    push OFFSET ??_C@_01IHBHIGKO@?0?$AA@
    push dword ptr [ebp + 8]
    call _fprintf
    pop ecx
    pop ecx
skipComma:
    inc dword ptr [ebp - 4]
    mov eax, dword ptr [ebp - 4]
    add ebx, 4
    cmp eax, dword ptr [esi + 4]
    jl short argumentLoop
argumentsDone:
    push OFFSET ??_C@_01EEMJAFIK@?6?$AA@
    push dword ptr [ebp + 8]
    call _fprintf
    pop ecx
    pop ecx
    add esi, 030h
compareOperation:
    cmp esi, dword ptr [edi + 03040h]
    jb short operationLoop
    push dword ptr [edi + 03048h]
    push OFFSET ??_C@_0N@MMEGJIFO@RESULT?3?5r?$CFd?6?$AA@
    push dword ptr [ebp + 8]
    call _fprintf
    push dword ptr [ebp + 8]
    call _fclose
    add esp, 010h
    pop edi
    pop esi
    pop ebx
    leave
    ret 4
?DumpAssembly@ExpressionParser@@QAEXPAD@Z ENDP

END
