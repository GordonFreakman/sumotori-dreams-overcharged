.386
.model flat
option casemap:none


EXTERN ?g_pendingManCount@@3IA:DWORD
EXTERN ?g_levelLoadState@@3PAHA:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_gameContactObjects@@3PAEA:BYTE
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameMen@@3PAUGameMan@@A:BYTE
EXTERN ?g_nextGameMan@@3PAUGameMan@@A:DWORD
EXTERN ?g_currentBox@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameIsRunning@@3HA:DWORD
EXTERN ?g_gameLevelEditorEditControl@@3PAUHWND__@@A:DWORD
EXTERN ?g_gameLevelEditorStatusWindow@@3PAUHWND__@@A:DWORD
EXTERN ?g_gameParser@@3VGameExpressionParser@@A:BYTE
EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameBoxDefaultValue@@3MB:DWORD
EXTERN ?g_gameScreenshotWriteMode@@3QBDB:BYTE

EXTERN ?ResetGameBoxes@@YAXXZ:PROC
EXTERN ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z:PROC
EXTERN ?MakeImmovable@GameBox@@QAEXXZ:PROC
EXTERN ?Reset@ExpressionParser@@QAEXXZ:PROC
EXTERN ?AddStandardConstants@ExpressionParser@@QAEXXZ:PROC
EXTERN ?CompileStatements@ExpressionParser@@QAEPADPAD@Z:PROC
EXTERN ?PrepareEvaluation@ExpressionParser@@QAEXXZ:PROC
EXTERN ?Evaluate@ExpressionParser@@QAE?AUVector3@@XZ:PROC
EXTERN ?FinishContacts@GameBox@@QAEXH@Z:PROC
EXTERN ?RecalculateMass@GameBox@@QAEXXZ:PROC
EXTERN ?ClearForces@GameBox@@QAEXXZ:PROC
EXTERN ?InitializePhysics@GameBox@@QAEXXZ:PROC
EXTERN ?FindNearestOpponent@GameMan@@QAEPAU1@AAUVector3@@0@Z:PROC
EXTERN ?RefreshGameContactLists@@YAXXZ:PROC
EXTERN _memset:PROC
EXTERN _fopen:PROC
EXTERN _strlen:PROC
EXTERN _fwrite:PROC
EXTERN _fclose:PROC
EXTERN __imp__GetWindowTextA@12:DWORD
EXTERN __imp__SetWindowTextA@8:DWORD
EXTERN __imp__MessageBoxA@16:DWORD

.const
PUBLIC loadGameLevelErrorCaption
loadGameLevelErrorCaption DB "Error in MOD file", 0
PUBLIC loadGameLevelEditorTitle
loadGameLevelEditorTitle DB "Sumotori Dreams level editor", 0
PUBLIC loadGameLevelEditedFilename
PUBLIC ?g_gameLevelEditedFilename@@3QBDB
?g_gameLevelEditedFilename@@3QBDB LABEL BYTE
loadGameLevelEditedFilename DB "edited.txt", 0
PUBLIC loadGameLevelArenaExtent
loadGameLevelArenaExtent REAL4 100.0

.data?
PUBLIC ?g_gameLevelEditBuffer@@3DA
?g_gameLevelEditBuffer@@3DA BYTE ?
BYTE 7FFFFh DUP (?)

.code

PUBLIC ?LoadGameLevel@@YAXPAD@Z
?LoadGameLevel@@YAXPAD@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 5Ch
    push ebx
    xor ebx, ebx
    or eax, 0FFFFFFFFh
    push esi
    push edi
    mov DWORD PTR [?g_pendingManCount@@3IA], ebx
    mov DWORD PTR [?g_levelLoadState@@3PAHA+10h], ebx
    mov DWORD PTR [?g_levelLoadState@@3PAHA+18h], ebx
    mov DWORD PTR [?g_screenTintLevel@@3HA], ebx
    mov DWORD PTR [?g_levelLoadState@@3PAHA+1Ch], ebx
    mov DWORD PTR [?g_levelLoadState@@3PAHA], eax
    mov DWORD PTR [?g_levelLoadState@@3PAHA+4], eax
    mov DWORD PTR [?g_levelLoadState@@3PAHA+8], eax
    mov DWORD PTR [?g_levelLoadState@@3PAHA+0Ch], eax
    call ?ResetGameBoxes@@YAXXZ
    push 0F400h
    push ebx
    mov esi, OFFSET ?g_gameContactObjects@@3PAEA
    push esi
    call _memset
    fldz
    fstp DWORD PTR [ebp-14h]
    add esp, 8
    fldz
    mov DWORD PTR [?g_gameContactObjectsEnd@@3PAEA], esi
    fstp DWORD PTR [ebp-0Ch]
    mov DWORD PTR [ebp-10h], 0C1A00000h
    fld DWORD PTR [loadGameLevelArenaExtent]
    lea esi, [ebp-14h]
    fst DWORD PTR [ebp-20h]
    mov DWORD PTR [ebp-1Ch], 0C1200000h
    fstp DWORD PTR [ebp-18h]
    mov DWORD PTR [?g_nextGameMan@@3PAUGameMan@@A], OFFSET ?g_gameMen@@3PAUGameMan@@A
    fld DWORD PTR [?g_gameBoxDefaultValue@@3MB]
    fstp DWORD PTR [esp]
    push 1
    sub esp, 0Ch
    mov edi, esp
    movsd
    movsd
    movsd
    sub esp, 0Ch
    lea esi, [ebp-20h]
    mov edi, esp
    movsd
    movsd
    movsd
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    add esp, 20h
    mov ecx, eax
    mov DWORD PTR [?g_currentBox@@3PAUGameBox@@A], eax
    call ?MakeImmovable@GameBox@@QAEXXZ
    cmp DWORD PTR [?g_gameIsRunning@@3HA], ebx
    mov DWORD PTR [?g_currentBox@@3PAUGameBox@@A], ebx
    je short loadGameLevelCompile
    push 80000h
    mov esi, OFFSET ?g_gameLevelEditBuffer@@3DA
    push esi
    push DWORD PTR [?g_gameLevelEditorEditControl@@3PAUHWND__@@A]
    call DWORD PTR [__imp__GetWindowTextA@12]
    push OFFSET ?g_gameScreenshotWriteMode@@3QBDB
    push OFFSET loadGameLevelEditedFilename
    call _fopen
    pop ecx
    pop ecx
    mov edi, eax
    push edi
    push esi
    call _strlen
    pop ecx
    push eax
    push 1
    push esi
    call _fwrite
    push edi
    call _fclose
    add esp, 14h
    mov [ebp+8], esi

loadGameLevelCompile:
    mov esi, OFFSET ?g_gameParser@@3VGameExpressionParser@@A
    mov ecx, esi
    call ?Reset@ExpressionParser@@QAEXXZ
    mov ecx, esi
    call ?AddStandardConstants@ExpressionParser@@QAEXXZ
    push DWORD PTR [ebp+8]
    mov ecx, esi
    mov DWORD PTR [?g_gameParser@@3VGameExpressionParser@@A+3060h], ebx
    call ?CompileStatements@ExpressionParser@@QAEPADPAD@Z
    cmp DWORD PTR [?g_gameIsRunning@@3HA], ebx
    je short loadGameLevelGameDiagnostics
    cmp BYTE PTR [?g_gameParser@@3VGameExpressionParser@@A+0Ch], bl
    je short loadGameLevelEditorSuccess
    push DWORD PTR [?g_gameParser@@3VGameExpressionParser@@A+8]
    push DWORD PTR [?g_gameLevelEditorStatusWindow@@3PAUHWND__@@A]
    call DWORD PTR [__imp__SetWindowTextA@8]
    jmp short loadGameLevelFinalizeCurrent

loadGameLevelEditorSuccess:
    push OFFSET loadGameLevelEditorTitle
    push DWORD PTR [?g_gameLevelEditorStatusWindow@@3PAUHWND__@@A]
    call DWORD PTR [__imp__SetWindowTextA@8]
    mov ecx, esi
    call ?PrepareEvaluation@ExpressionParser@@QAEXXZ
    lea eax, [ebp-38h]
    push eax
    mov ecx, esi
    call ?Evaluate@ExpressionParser@@QAE?AUVector3@@XZ
    jmp short loadGameLevelFinalizeCurrent

loadGameLevelGameDiagnostics:
    cmp BYTE PTR [?g_gameParser@@3VGameExpressionParser@@A+0Ch], bl
    je short loadGameLevelFinalizeCurrent
    push 30h
    push OFFSET loadGameLevelErrorCaption
    push DWORD PTR [?g_gameParser@@3VGameExpressionParser@@A+8]
    push ebx
    call DWORD PTR [__imp__MessageBoxA@16]

loadGameLevelFinalizeCurrent:
    mov eax, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    cmp eax, ebx
    je short loadGameLevelLinkMen
    push 9
    pop ecx
    lea esi, [eax+60h]
    lea edi, [ebp-5Ch]
    rep movsd
    mov ecx, [eax+54h]
    mov [ebp-8], ecx
    mov cl, [eax+0D0h]
    mov [ebp-1], cl
    push 1
    mov ecx, eax
    call ?FinishContacts@GameBox@@QAEXH@Z
    mov ecx, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    call ?RecalculateMass@GameBox@@QAEXXZ
    mov ecx, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    call ?ClearForces@GameBox@@QAEXXZ
    mov ecx, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    call ?InitializePhysics@GameBox@@QAEXXZ
    cmp BYTE PTR [ebp-1], bl
    je short loadGameLevelRestoreCurrent
    mov ecx, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    call ?MakeImmovable@GameBox@@QAEXXZ
loadGameLevelRestoreCurrent:
    mov edi, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    fld DWORD PTR [ebp-8]
    push 9
    add edi, 60h
    pop ecx
    lea esi, [ebp-5Ch]
    rep movsd
    mov eax, DWORD PTR [?g_currentBox@@3PAUGameBox@@A]
    fstp DWORD PTR [eax+54h]

loadGameLevelLinkMen:
    mov eax, OFFSET ?g_gameMen@@3PAUGameMan@@A
    cmp DWORD PTR [?g_nextGameMan@@3PAUGameMan@@A], eax
    mov [ebp-8], eax
    jbe short loadGameLevelErrorRollback
    fldz
    fstp DWORD PTR [ebp-20h]
    fldz
    fstp DWORD PTR [ebp-1Ch]
    fldz
    fstp DWORD PTR [ebp-18h]
    fldz
    fstp DWORD PTR [ebp-14h]
    fldz
    fstp DWORD PTR [ebp-10h]
    fldz
    fstp DWORD PTR [ebp-0Ch]

loadGameLevelLinkLoop:
    mov ecx, [ebp-8]
    lea esi, [ebp-20h]
    lea edi, [ebp-2Ch]
    movsd
    movsd
    movsd
    lea esi, [ebp-14h]
    lea edi, [ebp-38h]
    movsd
    lea eax, [ebp-2Ch]
    movsd
    push eax
    lea eax, [ebp-38h]
    push eax
    movsd
    call ?FindNearestOpponent@GameMan@@QAEPAU1@AAUVector3@@0@Z
    mov ecx, [ebp-8]
    mov [ecx+700h], eax
    add ecx, 730h
    cmp ecx, DWORD PTR [?g_nextGameMan@@3PAUGameMan@@A]
    mov [ebp-8], ecx
    jb short loadGameLevelLinkLoop
    mov eax, OFFSET ?g_gameMen@@3PAUGameMan@@A

loadGameLevelErrorRollback:
    cmp BYTE PTR [?g_gameParser@@3VGameExpressionParser@@A+0Ch], bl
    je short loadGameLevelRefreshContacts
    mov DWORD PTR [?g_gameContactObjectsEnd@@3PAEA], OFFSET ?g_gameContactObjects@@3PAEA
    mov DWORD PTR [?g_nextGameMan@@3PAUGameMan@@A], eax
    mov DWORD PTR [?g_gameBoxesEnd@@3PAUGameBox@@A], OFFSET ?g_gameBoxes@@3PAUGameBox@@A

loadGameLevelRefreshContacts:
    call ?RefreshGameContactLists@@YAXXZ
    pop edi
    pop esi
    pop ebx
    leave
    ret
?LoadGameLevel@@YAXPAD@Z ENDP

END
