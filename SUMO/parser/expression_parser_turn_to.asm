.686
.model flat
option casemap:none

EXTERN ?g_currentBox@@3PAUGameBox@@A:DWORD

EXTERN ?ParserAtan2Value@@YAMMM@Z:PROC
EXTERN ?RotateRows02@Matrix3@@QAEXM@Z:PROC
EXTERN ?RotateRows12@Matrix3@@QAEXM@Z:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN _sqrt:PROC

.code

; FUNCTION: SUMO 0x00404d6d
; FUNCTION: EDITOR 0x00404d8f
PUBLIC ?ParserBuiltinTurnTo@@YAXPAUParserBuiltinCall@@@Z
?ParserBuiltinTurnTo@@YAXPAUParserBuiltinCall@@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 018h
    push ebx
    fldz
    mov ebx, dword ptr [ebp+8]
    mov eax, dword ptr [ebx]
    fstp dword ptr [eax+8]
    fldz
    fstp dword ptr [eax+4]
    fldz
    fstp dword ptr [eax]
    cmp dword ptr [?g_currentBox@@3PAUGameBox@@A], 0
    jz turnToComplete

    mov eax, dword ptr [ebx+4]
    fld dword ptr [eax+8]
    push esi
    push edi
    push ecx
    push ecx
    fstp dword ptr [esp+4]
    fld dword ptr [eax]
    fstp dword ptr [esp]
    call ?ParserAtan2Value@@YAMMM@Z
    pop ecx
    mov ecx, dword ptr [?g_currentBox@@3PAUGameBox@@A]
    fstp dword ptr [esp]
    add ecx, 060h
    call ?RotateRows02@Matrix3@@QAEXM@Z

    fldz
    mov eax, dword ptr [ebx+4]
    sub esp, 0ch
    fstp dword ptr [esp+8]
    fld dword ptr [eax+8]
    fstp dword ptr [esp+4]
    fld dword ptr [eax]
    lea eax, [ebp-018h]
    fstp dword ptr [esp]
    push eax
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    mov esi, eax
    lea edi, [ebp-0ch]
    movsd
    movsd
    movsd
    fld dword ptr [ebp-4]
    fmul dword ptr [ebp-4]
    fld dword ptr [ebp-8]
    add esp, 8
    fmul dword ptr [ebp-8]
    faddp st(1), st
    fld dword ptr [ebp-0ch]
    fmul dword ptr [ebp-0ch]
    faddp st(1), st
    fstp qword ptr [esp]
    call _sqrt
    fstp dword ptr [esp+4]
    mov eax, dword ptr [ebx+4]
    fld dword ptr [eax+4]
    fstp dword ptr [esp]
    call ?ParserAtan2Value@@YAMMM@Z
    pop ecx
    mov ecx, dword ptr [?g_currentBox@@3PAUGameBox@@A]
    fstp dword ptr [esp]
    add ecx, 060h
    call ?RotateRows12@Matrix3@@QAEXM@Z
    pop edi
    pop esi

turnToComplete:
    pop ebx
    leave
    ret
?ParserBuiltinTurnTo@@YAXPAUParserBuiltinCall@@@Z ENDP

END
