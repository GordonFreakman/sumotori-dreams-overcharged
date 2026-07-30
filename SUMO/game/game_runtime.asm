.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@XZ:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?BuildDefaultGameArena@@YAXH@Z:PROC
EXTERN ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z:PROC
EXTERN ?MakeImmovable@GameBox@@QAEXXZ:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?Next@GameRandomGenerator@@QAEMXZ:PROC
EXTERN ?RefreshGameContactLists@@YAXXZ:PROC
EXTERN ?RotateColumns02@Matrix3@@QAEXM@Z:PROC
EXTERN ?SetGameCursorVisible@@YAXE@Z:PROC
EXTERN ?StartGameLevelEditor@@YAXPAD@Z:PROC
EXTERN ?g_gameAlternateCameraMode@@3HA:DWORD
EXTERN ?g_gameArenaExtent@@3MA:DWORD
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameCameraDistanceBias@@3MB:DWORD
EXTERN ?g_gameCameraInputDamping@@3MB:DWORD
EXTERN ?g_gameCameraInputOffsetScale@@3MB:DWORD
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameIsRunning@@3HA:DWORD
EXTERN ?g_gameLevelEditorActive@@3EA:BYTE
EXTERN ?g_gameLevelEditorCloseRequested@@3HA:DWORD
EXTERN ?g_gameMenuAlternateLayout@@3HA:DWORD
EXTERN ?g_gameMenuPage@@3HA:DWORD
EXTERN ?g_gameMenuSelection@@3HA:DWORD
EXTERN ?g_gameMouseX@@3HA:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_gameProjectileDefaultValue@@3MB:DWORD
EXTERN ?g_gameRandom@@3UGameRandomGenerator@@A:BYTE
EXTERN ?g_levelLoadState@@3PAHA:DWORD
EXTERN ?g_randomHalf@@3MB:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN __real@3cf5c28f:DWORD
EXTERN __real@3eaaaaab:DWORD
EXTERN __real@3f4f5c28:DWORD
EXTERN __real@3f4f5c29:DWORD
EXTERN __real@3f9ae148:DWORD
EXTERN __real@3fd0a3d70a3d70a4:QWORD
EXTERN __real@3fe66666:DWORD
EXTERN __real@403d0000:DWORD
EXTERN __real@40400000:DWORD
EXTERN __real@40e00000:DWORD
EXTERN __real@41100000:DWORD
EXTERN __real@42055556:DWORD
EXTERN __real@bd638e39:DWORD
EXTERN __real@bfa47ae147ae147b:QWORD
EXTERN __real@c0a00000:DWORD
EXTERN __real@c2aa0000:DWORD

.const
PUBLIC __real@bf666666
__real@bf666666 DD 0bf666666h

.code

; FUNCTION: SUMO 0x00406e98
; FUNCTION: EDITOR 0x00406eba
PUBLIC ?InitializeGameRuntimeState@@YAHXZ
?InitializeGameRuntimeState@@YAHXZ PROC
    DB 055h
    DB 08dh, 06ch, 024h, 088h
    DB 081h, 0ech, 010h, 002h, 000h, 000h
    DB 053h
    DB 056h
    DB 033h, 0f6h
    DB 039h, 035h
    DD ?g_gameIsRunning@@3HA
    DB 057h
    DB 074h, 02ch
    DB 080h, 03dh
    DD ?g_gameLevelEditorActive@@3EA
    DB 000h
    DB 074h, 00ah
    DB 0c7h, 005h
    DD ?g_gameLevelEditorCloseRequested@@3HA
    DB 001h, 000h, 000h, 000h
    DB 056h
    DB 0c6h, 005h
    DD ?g_gameLevelEditorActive@@3EA
    DB 001h
    DB 089h, 035h
    DD ?g_gameAlternateCameraMode@@3HA
    call ?StartGameLevelEditor@@YAXPAD@Z
    DB 059h
    DB 0e9h, 089h, 008h, 000h, 000h
    DB 06ah, 001h
    DB 089h, 035h
    DD ?g_screenTintLevel@@3HA
    call ?SetGameCursorVisible@@YAXE@Z
    DB 083h, 00dh
    DD ?g_gameMouseX@@3HA
    DB 0ffh
    DB 056h
    DB 0c7h, 005h
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 00ah, 000h, 000h, 000h
    call ?BuildDefaultGameArena@@YAXH@Z
    DB 0d9h, 0e8h
    DB 059h
    DB 0d9h, 05dh, 058h
    DB 059h
    DB 0d9h, 0e8h
    DB 06ah, 003h
    DB 0d9h, 05dh, 060h
    DB 058h
    DB 06ah, 004h
    DB 05bh
    DB 0c7h, 005h
    DD ?g_gameArenaExtent@@3MA
    DB 000h, 000h, 0a0h, 042h
    DB 089h, 035h
    DD ?g_gameMenuSelection@@3HA
    DB 0c7h, 045h, 000h, 000h, 000h, 0e0h, 0c0h
    DB 0c7h, 045h, 004h, 000h, 000h, 0e0h, 040h
    DB 0c7h, 045h, 008h, 000h, 000h, 0e0h, 040h
    DB 089h, 045h, 0ach
    DB 089h, 045h, 0b0h
    DB 089h, 05dh, 0b4h
    DB 089h, 05dh, 010h
    DB 089h, 05dh, 014h
    DB 089h, 045h, 018h
    DB 0c7h, 045h, 06ch, 0fch, 0ffh, 0ffh, 0ffh
    DB 0c7h, 045h, 04ch, 000h, 000h, 0a0h, 0c2h
    DB 0c7h, 045h, 050h, 000h, 000h, 070h, 041h
    DB 0c7h, 045h, 05ch, 000h, 000h, 0c8h, 0c1h
    DB 0dbh, 045h, 06ch
    DB 051h
    DB 08dh, 075h, 04ch
    DB 0d8h, 00dh
    DD __real@40e00000
    DB 0d9h, 05dh, 054h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 0d9h, 01ch, 024h
    DB 06ah, 001h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 058h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 083h, 0c4h, 020h
    DB 08bh, 0c8h
    call ?MakeImmovable@GameBox@@QAEXXZ
    DB 0ffh, 045h, 06ch
    DB 083h, 07dh, 06ch, 005h
    DB 07ch, 0bah
    DB 0d9h, 0eeh
    DB 051h
    DB 0d9h, 05dh, 054h
    DB 0c7h, 045h, 04ch, 000h, 000h, 0a0h, 0c2h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 0c7h, 045h, 050h, 000h, 000h, 020h, 042h
    DB 0d9h, 01ch, 024h
    DB 08dh, 075h, 04ch
    DB 06ah, 001h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 0c7h, 045h, 058h, 000h, 000h, 080h, 040h
    DB 0c7h, 045h, 05ch, 000h, 000h, 0c0h, 0bfh
    DB 0c7h, 045h, 060h, 000h, 000h, 0f0h, 041h
    DB 08dh, 075h, 058h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 0f0h
    DB 083h, 0c4h, 020h
    DB 08bh, 0ceh
    call ?MakeImmovable@GameBox@@QAEXXZ
    DB 0a1h
    DD ?g_gameMenuPage@@3HA
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 08bh, 0d6h
    DB 0d9h, 0eeh
    DB 033h, 0ffh
    DB 0d9h, 05dh, 050h
    DB 033h, 0f6h
    DB 0d9h, 0eeh
    DB 047h
    DB 03bh, 0c6h
    DB 08dh, 048h, 004h
    DB 0d9h, 05dh, 04ch
    DB 089h, 055h, 020h
    DB 089h, 075h, 040h
    DB 089h, 04dh, 03ch
    DB 089h, 07dh, 06ch
    DB 075h, 00eh
    DB 0c7h, 045h, 06ch, 003h, 000h, 000h, 000h
    DB 0c7h, 045h, 054h, 000h, 000h, 0a0h, 041h
    DB 083h, 0f8h, 003h
    DB 06ah, 002h
    DB 059h
    DB 075h, 00ch
    DB 089h, 04dh, 06ch
    DB 089h, 075h, 010h
    DB 089h, 04dh, 040h
    DB 089h, 05dh, 03ch
    DB 03bh, 0c7h
    DB 075h, 017h
    DB 0c7h, 045h, 054h, 000h, 000h, 020h, 041h
    DB 089h, 04dh, 06ch
    DB 089h, 04dh, 014h
    DB 089h, 075h, 040h
    DB 0c7h, 045h, 03ch, 007h, 000h, 000h, 000h
    DB 033h, 0dbh
    DB 039h, 075h, 06ch
    DB 089h, 05dh, 034h
    DB 00fh, 08eh, 0e1h, 006h, 000h, 000h
    DB 0d9h, 005h
    DD __real@c0a00000
    DB 0c7h, 045h, 060h, 000h, 000h, 0e0h, 0c0h
    DB 0d9h, 055h, 058h
    DB 08dh, 075h, 058h
    DB 0d9h, 0eeh
    DB 08dh, 0bdh, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0c7h, 045h, 060h, 000h, 000h, 0e0h, 040h
    DB 08dh, 075h, 058h
    DB 08dh, 0bdh, 0d4h, 0feh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0ebh, 003h
    DB 08bh, 055h, 020h
    DB 08dh, 045h, 04ch
    DB 050h
    DB 08dh, 085h, 068h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 034h, 0ffh, 0ffh, 0ffh
    DB 089h, 055h, 060h
    DB 089h, 055h, 05ch
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 010h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 08dh, 045h, 04ch
    DB 050h
    DB 0a5h
    DB 08dh, 085h, 0c8h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 0d4h, 0feh, 0ffh, 0ffh
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 083h, 065h, 068h, 000h
    DB 08bh, 0f0h
    DB 08bh, 044h, 09dh, 010h
    DB 085h, 0c0h
    DB 08dh, 0bdh, 01ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0c7h, 045h, 064h, 000h, 000h, 020h, 042h
    DB 089h, 045h, 02ch
    DB 00fh, 08eh, 022h, 006h, 000h, 000h
    DB 0d9h, 0eeh
    DB 08bh, 044h, 09dh, 0ach
    DB 0d9h, 05dh, 0d8h
    DB 089h, 045h, 030h
    DB 0d9h, 005h
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 08bh, 045h, 03ch
    DB 0d9h, 055h, 0b8h
    DB 003h, 0c3h
    DB 0d9h, 005h
    DD __real@41100000
    DB 0c1h, 0e3h, 004h
    DB 0d9h, 055h, 0c0h
    DB 043h
    DB 0d9h, 0c1h
    DB 0c7h, 045h, 0d0h, 000h, 000h, 0aah, 0c2h
    DB 0d9h, 05dh, 0a0h
    DB 089h, 045h, 01ch
    DB 089h, 05dh, 024h
    DB 0d9h, 055h, 0a8h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 088h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 08ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 090h
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 070h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 074h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 078h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 058h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 05ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 060h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 040h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 044h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 048h, 0ffh, 0ffh, 0ffh
    DB 083h, 065h, 048h, 000h
    DB 083h, 07dh, 030h, 000h
    DB 00fh, 08eh, 076h, 002h, 000h, 000h
    DB 0d9h, 005h
    DD ?g_randomHalf@@3MB
    DB 0c7h, 085h, 050h, 0ffh, 0ffh, 0ffh, 066h, 066h, 066h, 03fh
    DB 0d9h, 055h, 0dch
    DB 0d9h, 005h
    DD __real@bf666666
    DB 0d9h, 055h, 0e0h
    DB 0d9h, 0c1h
    DB 0d9h, 05dh, 0e4h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 064h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 068h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 07ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 080h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 084h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f4h
    DB 0d9h, 055h, 0f8h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 04ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 054h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 094h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 098h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 09ch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 0e8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0ech
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 045h, 064h
    DB 083h, 065h, 070h, 000h
    DB 0d8h, 005h
    DD ?g_gameCameraInputDamping@@3MB
    DB 08dh, 085h, 010h, 0ffh, 0ffh, 0ffh
    DB 089h, 045h, 074h
    DB 0d9h, 05dh, 028h
    DB 0dbh, 045h, 048h
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 0d9h, 05dh, 038h
    DB 08bh, 045h, 070h
    DB 0d9h, 044h, 005h, 000h
    DB 083h, 0ech, 00ch
    DB 0d9h, 05ch, 024h, 008h
    DB 08dh, 085h, 08ch, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 028h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 005h
    DD __real@c2aa0000
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 0e0h, 0feh, 0ffh, 0ffh
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 08dh, 045h, 04ch
    DB 0a5h
    DB 050h
    DB 08dh, 085h, 0a4h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 0e0h, 0feh, 0ffh, 0ffh
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 051h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08bh, 0f0h
    DB 0d9h, 01ch, 024h
    DB 06ah, 000h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 0dch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 0d8h
    DB 0d9h, 045h, 038h
    DB 083h, 0c4h, 01ch
    DB 08dh, 04bh, 060h
    DB 0d9h, 01ch, 024h
    call ?RotateColumns02@Matrix3@@QAEXM@Z
    DB 08bh, 075h, 074h
    DB 08dh, 083h, 0b4h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0d9h, 018h
    DB 08dh, 083h, 0b8h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0d8h, 00dh
    DD __real@3eaaaaab
    DB 0d9h, 018h
    DB 08bh, 015h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 070h
    DB 08dh, 044h, 005h, 05ch
    DB 08bh, 008h
    DB 089h, 00ah
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 083h, 07dh, 048h, 000h
    DB 08dh, 0b5h, 064h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 075h, 026h
    DB 083h, 07dh, 068h, 000h
    DB 075h, 020h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0c4h
    DB 083h, 0c7h, 020h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 0c8h, 000h, 000h, 080h, 0bfh
    DB 0d9h, 05dh, 0cch
    DB 08dh, 075h, 0c4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3f4f5c29
    DB 083h, 0c7h, 038h
    DB 08dh, 0b5h, 07ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 08bh, 015h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 081h, 0c1h, 004h, 0ffh, 0ffh, 0ffh
    DB 089h, 04ah, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 014h
    DB 08dh, 075h, 0f4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 07dh, 074h
    DB 08dh, 0b5h, 04ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 08dh, 075h, 094h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 045h, 070h, 004h
    DB 083h, 045h, 074h, 00ch
    DB 083h, 0c7h, 044h
    DB 08dh, 075h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 018h
    DB 0d9h, 059h, 054h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3f9ae148
    DB 0d9h, 059h, 058h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 059h, 050h
    DB 081h, 005h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0f4h, 000h, 000h, 000h
    DB 083h, 07dh, 070h, 008h
    DB 00fh, 08ch, 054h, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 064h
    DB 0ffh, 045h, 048h
    DB 0d8h, 005h
    DD __real@3fe66666
    DB 08bh, 045h, 048h
    DB 03bh, 045h, 030h
    DB 0d9h, 05dh, 064h
    DB 00fh, 08ch, 014h, 0feh, 0ffh, 0ffh
    DB 083h, 07dh, 034h, 002h
    DB 0c7h, 045h, 044h, 066h, 066h, 0e6h, 03fh
    DB 075h, 028h
    DB 0a1h
    DD ?g_gameMenuAlternateLayout@@3HA
    DB 033h, 0c9h
    DB 041h
    DB 039h, 04dh, 068h
    DB 0c7h, 045h, 044h, 033h, 033h, 0f3h, 03fh
    DB 075h, 007h
    DB 085h, 0c0h
    DB 074h, 010h
    DB 089h, 04dh, 040h
    DB 083h, 07dh, 068h, 002h
    DB 075h, 007h
    DB 085h, 0c0h
    DB 075h, 003h
    DB 089h, 04dh, 040h
    DB 0d9h, 045h, 044h
    DB 08dh, 075h, 0d0h
    DB 0d8h, 045h, 064h
    DB 08dh, 0bdh, 0f8h, 0feh, 0ffh, 0ffh
    DB 08dh, 045h, 04ch
    DB 050h
    DB 0d9h, 05dh, 0d4h
    DB 0a5h
    DB 0d9h, 045h, 044h
    DB 0a5h
    DB 0d9h, 0e0h
    DB 0d9h, 055h, 074h
    DB 0d9h, 05dh, 0bch
    DB 08dh, 085h, 074h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 0f8h, 0feh, 0ffh, 0ffh
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 051h
    DB 0d9h, 005h
    DD __real@bd638e39
    DB 08bh, 0f0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 01ch
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 0b8h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 04dh, 024h
    DB 08bh, 0d8h
    DB 08bh, 045h, 068h
    DB 003h, 0c8h
    DB 089h, 08bh, 0bch, 000h, 000h, 000h
    DB 08bh, 04dh, 040h
    DB 003h, 0c1h
    DB 089h, 045h, 038h
    DB 08dh, 075h, 0a0h
    DB 0dbh, 045h, 038h
    DB 08dh, 0bdh, 028h, 0ffh, 0ffh, 0ffh
    DB 083h, 0c4h, 020h
    DB 08dh, 085h, 0bch, 0feh, 0ffh, 0ffh
    DB 0d8h, 00dh
    DD __real@403d0000
    DB 050h
    DB 08dh, 08dh, 028h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 06dh, 074h
    DB 0d9h, 05dh, 0a4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0f0h
    DB 0d9h, 005h
    DD __real@3cf5c28f
    DB 08dh, 07bh, 020h
    DB 0a5h
    DB 0a5h
    DB 08dh, 083h, 0ach, 000h, 000h, 000h
    DB 0a5h
    DB 0d9h, 000h
    DB 0d8h, 0c9h
    DB 0d9h, 018h
    DB 08dh, 083h, 0b0h, 000h, 000h, 000h
    DB 0d9h, 005h
    DD __real@42055556
    DB 0d9h, 000h
    DB 0d8h, 0c9h
    DB 0d9h, 018h
    DB 08dh, 083h, 0a8h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0d8h, 0cah
    DB 0d9h, 018h
    DB 08dh, 083h, 0b4h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0d8h, 0cah
    DB 0d9h, 018h
    DB 08dh, 083h, 0b8h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 051h
    DB 0d8h, 0c9h
    DB 0beh
    DD ?g_gameRandom@@3UGameRandomGenerator@@A
    DB 08bh, 0ceh
    DB 0c7h, 083h, 0c0h, 000h, 000h, 000h, 002h, 000h, 000h, 000h
    DB 0d9h, 018h
    DB 0c7h, 083h, 0c4h, 000h, 000h, 000h, 000h, 000h, 040h, 040h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0dch, 00dh
    DD __real@3fd0a3d70a3d70a4
    DB 051h
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 005h
    DD ?g_gameOne@@3MB
    DB 051h
    DB 08dh, 085h, 0b0h, 0feh, 0ffh, 0ffh
    DB 0dch, 00dh
    DD __real@bfa47ae147ae147b
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 0d9h, 045h, 044h
    DB 08bh, 0f0h
    DB 0dch, 0c0h
    DB 08bh, 045h, 074h
    DB 08dh, 0bdh, 004h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 045h, 064h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 064h
    DB 0a5h
    DB 08dh, 0bbh, 09ch, 000h, 000h, 000h
    DB 08dh, 0b5h, 004h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 089h, 045h, 00ch
    DB 08dh, 085h, 010h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 089h, 045h, 074h
    DB 033h, 0c0h
    DB 0a5h
    DB 0c7h, 043h, 054h, 000h, 000h, 070h, 041h
    DB 089h, 045h, 070h
    DB 0ebh, 003h
    DB 08bh, 045h, 070h
    DB 08bh, 015h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 044h, 005h, 000h
    DB 08bh, 04ch, 005h, 05ch
    DB 08bh, 075h, 074h
    DB 089h, 00ah
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 08dh, 075h, 088h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 038h
    DB 08dh, 0b5h, 070h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 0a5h
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 045h, 00ch
    DB 0d9h, 05ch, 024h, 004h
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 08bh, 015h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08dh, 085h, 098h, 0feh, 0ffh, 0ffh
    DB 081h, 0c1h, 004h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 089h, 04ah, 004h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08bh, 045h, 070h
    DB 08dh, 0bdh, 0ech, 0feh, 0ffh, 0ffh
    DB 0d9h, 044h, 005h, 000h
    DB 0a5h
    DB 0d9h, 05ch, 024h, 00ch
    DB 0d9h, 045h, 044h
    DB 0a5h
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 014h
    DB 083h, 0c4h, 004h
    DB 08dh, 0b5h, 0ech, 0feh, 0ffh, 0ffh
    DB 0a5h
    DB 0d9h, 01ch, 024h
    DB 0a5h
    DB 08dh, 085h, 080h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 0a5h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 07dh, 074h
    DB 08bh, 0f0h
    DB 0d9h, 005h
    DD __real@3f4f5c28
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 08dh, 0b5h, 058h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c4h, 010h
    DB 083h, 0c7h, 044h
    DB 08dh, 0b5h, 040h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3f9ae148
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 083h, 045h, 074h, 00ch
    DB 0d9h, 058h, 050h
    DB 08bh, 045h, 070h
    DB 083h, 045h, 070h, 004h
    DB 081h, 005h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0f4h, 000h, 000h, 000h
    DB 083h, 07dh, 070h, 008h
    DB 089h, 05ch, 005h, 05ch
    DB 00fh, 08ch, 0ceh, 0feh, 0ffh, 0ffh
    DB 0ffh, 045h, 068h
    DB 08bh, 045h, 068h
    DB 03bh, 045h, 02ch
    DB 00fh, 08ch, 075h, 0fah, 0ffh, 0ffh
    DB 0d9h, 045h, 054h
    DB 08bh, 05dh, 034h
    DB 0d8h, 025h
    DD ?g_gameCameraDistanceBias@@3MB
    DB 043h
    DB 03bh, 05dh, 06ch
    DB 089h, 05dh, 034h
    DB 0d9h, 05dh, 054h
    DB 00fh, 08ch, 05dh, 0f9h, 0ffh, 0ffh
    call ?RefreshGameContactLists@@YAXXZ
    DB 05fh
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 078h
    DB 0c9h
    DB 0c3h
?InitializeGameRuntimeState@@YAHXZ ENDP

END
