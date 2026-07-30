.386
.model flat
option casemap:none

EXTERN _memset:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z:PROC
EXTERN ?FinishContacts@GameBox@@QAEXH@Z:PROC
EXTERN ?InitializePhysics@GameBox@@QAEXXZ:PROC
EXTERN ?MakeImmovable@GameBox@@QAEXXZ:PROC
EXTERN ?Rotate@Matrix3@@QAEXAAUVector3@@@Z:PROC
EXTERN ?Rotate@Vector3@@QAEXAAU1@@Z:PROC
EXTERN ?RotateRows12@Matrix3@@QAEXM@Z:PROC

EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN ?g_gameContactObjects@@3PAEA:BYTE
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameMen@@3PAUGameMan@@A:BYTE
EXTERN ?g_nextGameMan@@3PAUGameMan@@A:DWORD
EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameFloorHalfExtent@@3MB:DWORD
EXTERN ?g_gameRampStep32@@3MB:DWORD
EXTERN ?g_gameArenaHalfExtent@@3MB:DWORD
EXTERN ?g_gameArenaVerticalHalfSize@@3MB:DWORD
EXTERN ?g_gameBoxDefaultValue@@3MB:DWORD
EXTERN ?g_gameArenaLowerPointScale@@3MB:DWORD
EXTERN ?g_gameWallQuarterTurn@@3MB:DWORD
EXTERN ?g_gameWallCenterSegment@@3MB:DWORD
EXTERN ?g_gameWallSegmentSpacing@@3MB:DWORD
EXTERN ?g_levelLoadState@@3PAHA:DWORD
EXTERN ?g_gameMenuPage@@3HA:DWORD
EXTERN ?g_gameDecorationHeight@@3MA:DWORD
EXTERN ?g_gameProjectileDefaultValue@@3MB:DWORD
EXTERN ?g_gameRimAngleStep@@3MB:DWORD
EXTERN ?g_gameRimTiltAngle@@3MB:DWORD
EXTERN ?g_gameIsRunning@@3HA:DWORD
EXTERN ?g_gameArenaExtent@@3MA:DWORD

.code

; FUNCTION: SUMO 0x00410505
; FUNCTION: EDITOR 0x00410527
PUBLIC ?BuildDefaultGameArena@@YAXH@Z
?BuildDefaultGameArena@@YAXH@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 054h
    push ebx
    push esi
    push edi
    push 0f400h
    push 0
    mov esi, OFFSET ?g_gameContactObjects@@3PAEA
    push esi
    call _memset
    fldz
    fstp DWORD PTR [ebp-018h]
    add esp, 8
    fldz
    mov DWORD PTR [?g_gameContactObjectsEnd@@3PAEA], esi
    fstp DWORD PTR [ebp-010h]
    mov DWORD PTR [ebp-014h], 0c0800000h
    fld DWORD PTR [?g_gameFloorHalfExtent@@3MB]
    lea esi, [ebp-018h]
    fst DWORD PTR [ebp-024h]
    mov DWORD PTR [ebp-020h], 0c0400000h
    fstp DWORD PTR [ebp-01ch]
    mov DWORD PTR [?g_nextGameMan@@3PAUGameMan@@A], OFFSET ?g_gameMen@@3PAUGameMan@@A
    fld DWORD PTR [?g_gameRampStep32@@3MB]
    mov DWORD PTR [?g_gameBoxesEnd@@3PAUGameBox@@A], OFFSET ?g_gameBoxes@@3PAUGameBox@@A
    fstp DWORD PTR [esp]
    push 1
    sub esp, 0ch
    mov edi, esp
    movsd
    movsd
    movsd
    sub esp, 0ch
    lea esi, [ebp-024h]
    mov edi, esp
    movsd
    movsd
    movsd
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    add esp, 020h
    mov ecx, eax
    call ?MakeImmovable@GameBox@@QAEXXZ
    fldz
    sub esp, 0ch
    fstp DWORD PTR [ebp-024h]
    lea eax, [ebp-054h]
    fldz
    mov DWORD PTR [ebp-020h], 040000000h
    fstp DWORD PTR [ebp-01ch]
    fld DWORD PTR [?g_gameArenaHalfExtent@@3MB]
    fstp DWORD PTR [esp+8]
    fld DWORD PTR [?g_gameArenaVerticalHalfSize@@3MB]
    fstp DWORD PTR [esp+4]
    fld DWORD PTR [?g_gameArenaHalfExtent@@3MB]
    fstp DWORD PTR [esp]
    push eax
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    fld DWORD PTR [?g_gameBoxDefaultValue@@3MB]
    add esp, 0ch
    fstp DWORD PTR [esp]
    push DWORD PTR [ebp+8]
    lea esi, [ebp-024h]
    sub esp, 0ch
    mov edi, esp
    movsd
    movsd
    movsd
    sub esp, 0ch
    mov esi, eax
    mov edi, esp
    movsd
    movsd
    movsd
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    add esp, 020h
    mov esi, eax
    xor edx, edx

arenaPointLoop:
    mov eax, DWORD PTR [esi]
    DB 08dh, 00ch, 002h
    fld DWORD PTR [ecx+4]
    fcomp DWORD PTR [?g_vectorZero@@3MB]
    fnstsw ax
    test ah, 5
    jp short arenaPointNext
    fld DWORD PTR [ecx+8]
    fmul DWORD PTR [?g_gameArenaLowerPointScale@@3MB]
    fstp DWORD PTR [ecx+8]

arenaPointNext:
    add edx, 010h
    cmp edx, 080h
    jl short arenaPointLoop
    push 1
    mov ecx, esi
    call ?FinishContacts@GameBox@@QAEXH@Z
    mov ecx, esi
    call ?InitializePhysics@GameBox@@QAEXXZ
    mov ecx, esi
    call ?MakeImmovable@GameBox@@QAEXXZ
    fldz
    and DWORD PTR [ebp-8], 0
    fstp DWORD PTR [ebp-03ch]
    fldz
    mov DWORD PTR [ebp-014h], 040400000h
    fstp DWORD PTR [ebp-034h]
    mov DWORD PTR [ebp-010h], 042580000h
    fldz
    mov DWORD PTR [ebp-030h], 041000000h
    mov DWORD PTR [ebp-02ch], 0c0800000h
    fstp DWORD PTR [ebp-024h]
    mov DWORD PTR [ebp-028h], 03f000000h
    fldz
    fstp DWORD PTR [ebp-01ch]

wallSideLoop:
    fild DWORD PTR [ebp-8]
    and DWORD PTR [ebp-4], 0
    lea esi, [ebp-024h]
    lea edi, [ebp-054h]
    fmul DWORD PTR [?g_gameWallQuarterTurn@@3MB]
    fst DWORD PTR [ebp-0ch]
    fstp DWORD PTR [ebp-020h]
    movsd
    movsd
    movsd

wallSegmentLoop:
    fild DWORD PTR [ebp-4]
    push ecx
    lea esi, [ebp-018h]
    fsub DWORD PTR [?g_gameWallCenterSegment@@3MB]
    fmul DWORD PTR [?g_gameWallSegmentSpacing@@3MB]
    fstp DWORD PTR [ebp-018h]
    fld DWORD PTR [?g_gameBoxDefaultValue@@3MB]
    fstp DWORD PTR [esp]
    push DWORD PTR [ebp+8]
    sub esp, 0ch
    mov edi, esp
    movsd
    movsd
    movsd
    sub esp, 0ch
    lea esi, [ebp-030h]
    mov edi, esp
    movsd
    movsd
    movsd
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    mov ebx, eax
    mov eax, DWORD PTR [ebp-0ch]
    mov DWORD PTR [ebp-038h], eax
    lea esi, [ebp-03ch]
    lea edi, [ebp-048h]
    movsd
    movsd
    add esp, 020h
    lea eax, [ebp-048h]
    push eax
    lea ecx, [ebx+060h]
    movsd
    call ?Rotate@Matrix3@@QAEXAAUVector3@@@Z
    lea eax, [ebp-054h]
    push eax
    lea ecx, [ebx+084h]
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    mov ecx, ebx
    call ?MakeImmovable@GameBox@@QAEXXZ
    push 2
    pop eax
    mov DWORD PTR [ebx+054h], 042200000h
    mov DWORD PTR [ebx+0a8h], 040400000h
    mov DWORD PTR [ebx+0c0h], eax
    mov DWORD PTR [ebx+0c4h], 03f19999ah
    cmp DWORD PTR [?g_levelLoadState@@3PAHA+010h], 0ah
    jne short wallNormal
    cmp DWORD PTR [ebp-8], eax
    jne short wallNormal
    cmp DWORD PTR [ebp-4], 4
    jne short wallNormal
    cmp DWORD PTR [?g_gameMenuPage@@3HA], 0
    jne short wallNormal
    mov DWORD PTR [ebx+0bch], 6

wallNormal:
    inc DWORD PTR [ebp-4]
    cmp DWORD PTR [ebp-4], 6
    jl wallSegmentLoop
    inc DWORD PTR [ebp-8]
    cmp DWORD PTR [ebp-8], 4
    jl wallSideLoop
    fld DWORD PTR [?g_gameDecorationHeight@@3MA]
    and DWORD PTR [ebp-4], 0
    fldz
    mov DWORD PTR [ebp-038h], 040a00000h
    fstp DWORD PTR [ebp-03ch]
    mov DWORD PTR [ebp-030h], 040266666h
    mov DWORD PTR [ebp-02ch], 0be4ccccdh
    mov DWORD PTR [ebp-028h], 03ee66666h
    fstp DWORD PTR [ebp-034h]
    fldz
    fstp DWORD PTR [ebp-024h]
    fldz
    fstp DWORD PTR [ebp-01ch]
    fldz
    fstp DWORD PTR [ebp-018h]
    fldz
    fstp DWORD PTR [ebp-010h]

rimLoop:
    fld DWORD PTR [?g_gameProjectileDefaultValue@@3MB]
    push ecx
    fstp DWORD PTR [esp]
    push DWORD PTR [ebp+8]
    lea esi, [ebp-03ch]
    sub esp, 0ch
    mov edi, esp
    movsd
    movsd
    movsd
    sub esp, 0ch
    lea esi, [ebp-030h]
    mov edi, esp
    movsd
    movsd
    movsd
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    lea esi, [ebp-024h]
    fild DWORD PTR [ebp-4]
    lea edi, [ebp-054h]
    mov ebx, eax
    add esp, 020h
    fmul DWORD PTR [?g_gameRimAngleStep@@3MB]
    lea eax, [ebp-054h]
    lea ecx, [ebx+060h]
    push eax
    fst DWORD PTR [ebp-0ch]
    fstp DWORD PTR [ebp-020h]
    movsd
    movsd
    movsd
    call ?Rotate@Matrix3@@QAEXAAUVector3@@@Z
    mov eax, DWORD PTR [ebp-0ch]
    mov DWORD PTR [ebp-014h], eax
    lea esi, [ebp-018h]
    lea edi, [ebp-048h]
    movsd
    movsd
    lea eax, [ebp-048h]
    push eax
    lea ecx, [ebx+084h]
    movsd
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    push ecx
    fld DWORD PTR [?g_gameRimTiltAngle@@3MB]
    lea ecx, [ebx+060h]
    fstp DWORD PTR [esp]
    call ?RotateRows12@Matrix3@@QAEXM@Z
    mov ecx, ebx
    call ?MakeImmovable@GameBox@@QAEXXZ
    inc DWORD PTR [ebp-4]
    cmp DWORD PTR [ebp-4], 01fh
    jl rimLoop
    cmp DWORD PTR [?g_gameIsRunning@@3HA], 0
    mov DWORD PTR [?g_gameArenaExtent@@3MA], 042200000h
    je short arenaComplete
    mov DWORD PTR [?g_gameArenaExtent@@3MA], 043480000h

arenaComplete:
    pop edi
    pop esi
    pop ebx
    leave
    ret
?BuildDefaultGameArena@@YAXH@Z ENDP

END
