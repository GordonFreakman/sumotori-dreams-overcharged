.386
.model flat
option casemap:none

EXTERN ??2@YAPAXI@Z:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??_C@_06IGLAKLEJ@in?4dat?$AA@:BYTE
EXTERN ?BuildDefaultGameArena@@YAXH@Z:PROC
EXTERN ?EnsureSpace@ReplayStream@@QAEXI@Z:PROC
EXTERN ?GameAudioNoOpCallback@@YAXXZ:PROC
EXTERN ?InitializePhysics@GameBox@@QAEXXZ:PROC
EXTERN ?InitializeWaterField@@YAXXZ:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?LoadFile@ReplayStream@@QAEXPAD@Z:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?PlayGameSound@@YAPAXHMMH@Z:PROC
EXTERN ?ReplayWriteBoundary@@YAXXZ:PROC
EXTERN ?Reset@ReplayStream@@QAEXXZ:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?SetIdentity@Matrix3@@QAEXXZ:PROC
EXTERN ?SetSceneTransform@@YAXAAUVector3@@M@Z:PROC
EXTERN ?StartGameRound@@YAXXZ:PROC
EXTERN ?StartReplayRecording@@YAXXZ:PROC
EXTERN ?StopReplayRecording@@YAXXZ:PROC
EXTERN ?SumoAssert@@YAX_N@Z:PROC
EXTERN ?UpdateFacePlane@GameBox@@QAEXAAUGameBoxFace@@@Z:PROC
EXTERN ?g_freeCameraTarget@@3UVector3@@A:BYTE
EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameCameraWorldPosition@@3UVector3@@A:BYTE
EXTERN ?g_gameCommandLineFile@@3PADA:DWORD
EXTERN ?g_gameInverseViewMatrix@@3UMatrix3@@A:BYTE
EXTERN ?g_gameIsRunning@@3HA:DWORD
EXTERN ?g_gameKeyDown@@3PAEA:BYTE
EXTERN ?g_gameKeyPressed@@3PAEA:BYTE
EXTERN ?g_gameLevelEditorCloseRequested@@3HA:DWORD
EXTERN ?g_gameMode@@3HA:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_gameReplayFrame@@3HA:DWORD
EXTERN ?g_replayPlaybackStream@@3VReplayStream@@A:BYTE
EXTERN ?g_replayRecording@@3_NA:BYTE
EXTERN ?g_replayStream@@3VReplayStream@@A:BYTE
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN @__security_check_cookie@4:PROC
EXTERN ___security_cookie:DWORD
EXTERN __real@358637be:DWORD

.code

; FUNCTION: SUMO 0x0040d7ad
; FUNCTION: EDITOR 0x0040d7cf
PUBLIC ?UpdateGameReplay@@YAHXZ
?UpdateGameReplay@@YAHXZ PROC
    DB 055h
    DB 08dh, 0ach, 024h, 0ech, 0fbh, 0ffh, 0ffh
    DB 081h, 0ech, 094h, 004h, 000h, 000h
    DB 080h, 03dh
    DD ?g_gameKeyPressed@@3PAEA + 5
    DB 000h
    DB 0a1h
    DD ___security_cookie
    DB 089h, 085h, 010h, 004h, 000h, 000h
    DB 074h, 01ch
    DB 080h, 03dh
    DD ?g_replayRecording@@3_NA
    DB 000h
    DB 0c6h, 005h
    DD ?g_gameKeyPressed@@3PAEA + 5
    DB 000h
    DB 074h, 007h
    call ?StopReplayRecording@@YAXXZ
    DB 0ebh, 005h
    call ?StartReplayRecording@@YAXXZ
    DB 053h
    DB 033h, 0dbh
    DB 056h
    DB 043h
    DB 080h, 03dh
    DD ?g_gameKeyPressed@@3PAEA + 4
    DB 000h
    DB 057h
    DB 0bfh
    DD ?g_replayStream@@3VReplayStream@@A
    DB 074h, 03fh
    DB 039h, 01dh
    DD ?g_gameMode@@3HA
    DB 075h, 037h
    DB 083h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 000h
    DB 0c6h, 005h
    DD ?g_gameKeyPressed@@3PAEA + 4
    DB 000h
    DB 074h, 00dh
    DB 088h, 01dh
    DD ?g_gameKeyPressed@@3PAEA + 3ch
    call ?GameAudioNoOpCallback@@YAXXZ
    DB 0ebh, 005h
    call ?StartGameRound@@YAXXZ
    DB 08bh, 0cfh
    call ?Reset@ReplayStream@@QAEXXZ
    DB 083h, 025h
    DD ?g_replayStream@@3VReplayStream@@A
    DB 000h
    DB 0c6h, 005h
    DD ?g_replayRecording@@3_NA
    DB 000h
    DB 080h, 03dh
    DD ?g_gameKeyPressed@@3PAEA + 6
    DB 000h
    DB 074h, 026h
    DB 080h, 03dh
    DD ?g_replayRecording@@3_NA
    DB 000h
    DB 0c6h, 005h
    DD ?g_gameKeyPressed@@3PAEA + 6
    DB 000h
    DB 074h, 005h
    call ?StopReplayRecording@@YAXXZ
    DB 0c6h, 005h
    DD ?g_gameKeyPressed@@3PAEA + 3ch
    DB 001h
    call ?GameAudioNoOpCallback@@YAXXZ
    call ?StartReplayRecording@@YAXXZ
    DB 0a1h
    DD ?g_gameMode@@3HA
    DB 03bh, 0c3h
    DB 06ah, 004h
    DB 05eh
    DB 074h, 009h
    DB 083h, 0f8h, 003h
    DB 00fh, 085h, 0cbh, 002h, 000h, 000h
    DB 080h, 03dh
    DD ?g_replayRecording@@3_NA
    DB 000h
    DB 00fh, 084h, 0beh, 002h, 000h, 000h
    DB 068h, 000h, 000h, 001h, 000h
    DB 08bh, 0cfh
    call ?EnsureSpace@ReplayStream@@QAEXI@Z
    DB 083h, 065h, 00ch, 000h
    DB 081h, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 00fh, 086h, 040h, 002h, 000h, 000h
    DB 0bbh
    DD ?g_gameBoxes@@3PAUGameBox@@A + 4
    DB 080h, 07bh, 054h, 000h
    DB 08dh, 083h, 0e8h, 000h, 000h, 000h
    DB 00fh, 085h, 0e6h, 001h, 000h, 000h
    DB 080h, 038h, 000h
    DB 00fh, 085h, 044h, 001h, 000h, 000h
    DB 0c6h, 000h, 001h
    DB 0a1h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0c7h, 000h, 003h, 000h, 000h, 000h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 045h, 00ch
    DB 089h, 001h
    DB 08bh, 003h
    DB 02bh, 043h, 0fch
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0c1h, 0f8h, 004h
    DB 089h, 001h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 085h, 0c0h
    DB 07eh, 02eh
    DB 083h, 065h, 004h, 000h
    DB 089h, 045h, 008h
    DB 08bh, 04bh, 0fch
    DB 003h, 04dh, 004h
    DB 06ah, 003h
    DB 05ah
    DB 08bh, 001h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 007h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 003h, 0ceh
    DB 04ah
    DB 075h, 0ebh
    DB 083h, 045h, 004h, 010h
    DB 0ffh, 04dh, 008h
    DB 075h, 0d9h
    DB 08bh, 043h, 008h
    DB 02bh, 043h, 004h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0c1h, 0f8h, 003h
    DB 089h, 001h
    DB 08bh, 043h, 010h
    DB 02bh, 043h, 00ch
    DB 06ah, 024h
    DB 099h
    DB 059h
    DB 0f7h, 0f9h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 001h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 085h, 0c0h
    DB 07eh, 054h
    DB 033h, 0c9h
    DB 089h, 045h, 008h
    DB 08bh, 043h, 00ch
    DB 08bh, 015h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08dh, 044h, 001h, 01ch
    DB 08bh, 000h
    DB 089h, 002h
    DB 08bh, 053h, 00ch
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 033h, 0c0h
    DB 039h, 044h, 011h, 01ch
    DB 07eh, 025h
    DB 08bh, 053h, 00ch
    DB 08bh, 054h, 011h, 010h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08dh, 054h, 0c2h, 004h
    DB 08bh, 012h
    DB 089h, 017h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 053h, 00ch
    DB 040h
    DB 03bh, 044h, 011h, 01ch
    DB 07ch, 0dbh
    DB 083h, 0c1h, 024h
    DB 0ffh, 04dh, 008h
    DB 075h, 0b1h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 043h, 02ch
    DB 089h, 001h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 043h, 030h
    DB 089h, 001h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 06ah, 003h
    DB 08dh, 043h, 01ch
    DB 059h
    DB 08bh, 010h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 017h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 003h, 0c6h
    DB 049h
    DB 075h, 0ebh
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 043h, 050h
    DB 089h, 001h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08dh, 083h, 080h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 0c8h
    DB 08dh, 0bbh, 0ech, 000h, 000h, 000h
    DB 050h
    DB 08bh, 0cfh
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@358637be
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 093h, 000h, 000h, 000h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 055h, 00ch
    DB 08dh, 083h, 080h, 000h, 000h, 000h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 06ah, 004h
    DB 0c7h, 001h, 002h, 000h, 000h, 000h
    DB 059h
    DB 001h, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 016h
    DB 001h, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 06ah, 003h
    DB 05ah
    DB 08bh, 030h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 037h
    DB 001h, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 003h, 0c1h
    DB 04ah
    DB 075h, 0ebh
    DB 06ah, 009h
    DB 08dh, 043h, 05ch
    DB 05ah
    DB 08bh, 030h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 037h
    DB 001h, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 003h, 0c1h
    DB 04ah
    DB 075h, 0ebh
    DB 06ah, 004h
    DB 05eh
    DB 0ebh, 02ah
    DB 080h, 038h, 001h
    DB 075h, 025h
    DB 0c6h, 000h, 000h
    DB 0a1h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0c7h, 000h, 005h, 000h, 000h, 000h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 00dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 08bh, 045h, 00ch
    DB 089h, 001h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0ffh, 045h, 00ch
    DB 081h, 0c3h, 0fch, 000h, 000h, 000h
    DB 08dh, 043h, 0fch
    DB 03bh, 005h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 00fh, 082h, 0c8h, 0fdh, 0ffh, 0ffh
    DB 033h, 0dbh
    DB 043h
    DB 0a1h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 018h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0a1h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 0c7h, 000h, 006h, 000h, 000h, 000h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 06ah, 003h
    DB 0b8h
    DD ?g_gameCameraWorldPosition@@3UVector3@@A
    DB 059h
    DB 08bh, 010h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 017h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 003h, 0c6h
    DB 049h
    DB 075h, 0ebh
    DB 06ah, 009h
    DB 0b8h
    DD ?g_gameInverseViewMatrix@@3UMatrix3@@A
    DB 059h
    DB 08bh, 010h
    DB 08bh, 03dh
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 089h, 017h
    DB 001h, 035h
    DD ?g_replayStream@@3VReplayStream@@A + 10h
    DB 003h, 0c6h
    DB 049h
    DB 075h, 0ebh
    DB 0ffh, 005h
    DD ?g_replayStream@@3VReplayStream@@A
    DB 0a1h
    DD ?g_gameMode@@3HA
    DB 06ah, 002h
    DB 059h
    DB 03bh, 0c1h
    DB 074h, 009h
    DB 083h, 0f8h, 003h
    DB 00fh, 085h, 0cch, 005h, 000h, 000h
    DB 0a1h
    DD ?g_screenTintLevel@@3HA
    DB 040h
    DB 099h
    DB 08bh, 0f1h
    DB 0f7h, 0feh
    DB 085h, 0d2h
    DB 074h, 00dh
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 3dh
    DB 000h
    DB 00fh, 085h, 0b0h, 005h, 000h, 000h
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 3eh
    DB 000h
    DB 089h, 05dh, 004h
    DB 074h, 003h
    DB 089h, 04dh, 004h
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 03bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 14h
    DB 072h, 022h
    DB 0a1h
    DD ?g_gameCommandLineFile@@3PADA
    DB 080h, 038h, 000h
    DB 0b9h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A
    DB 074h, 003h
    DB 050h
    DB 0ebh, 005h
    DB 068h
    DD ??_C@_06IGLAKLEJ@in?4dat?$AA@
    call ?LoadFile@ReplayStream@@QAEXPAD@Z
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f4h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0ech
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 008h
    DB 06ah, 004h
    DB 05fh
    DB 08bh, 00dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 14h
    DB 033h, 0c0h
    DB 040h
    DB 03bh, 0d9h
    DB 089h, 045h, 0f8h
    DB 072h, 007h
    DB 0a3h
    DD ?g_gameLevelEditorCloseRequested@@3HA
    DB 0ebh, 01eh
    DB 08bh, 003h
    DB 003h, 0dfh
    DB 085h, 0c0h
    DB 089h, 045h, 0f8h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 07ch, 005h
    DB 083h, 0f8h, 007h
    DB 07eh, 008h
    DB 08bh, 0d9h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 048h
    DB 048h
    DB 00fh, 084h, 0f3h, 003h, 000h, 000h
    DB 048h
    DB 00fh, 084h, 036h, 001h, 000h, 000h
    DB 048h
    DB 00fh, 084h, 0dah, 000h, 000h, 000h
    DB 048h
    DB 00fh, 084h, 0b7h, 000h, 000h, 000h
    DB 048h
    DB 074h, 059h
    DB 048h
    DB 00fh, 085h, 075h, 004h, 000h, 000h
    DB 08bh, 003h
    DB 003h, 0dfh
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 00bh
    DB 003h, 0dfh
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 089h, 04dh, 0e8h
    DB 08bh, 00bh
    DB 003h, 0dfh
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 089h, 04dh, 0e0h
    DB 0d9h, 045h, 0e0h
    DB 08bh, 00bh
    DB 051h
    DB 051h
    DB 051h
    DB 0d9h, 05ch, 024h, 004h
    DB 003h, 0dfh
    DB 0d9h, 045h, 0e8h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?PlayGameSound@@YAPAXHMMH@Z
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 083h, 0c4h, 010h
    DB 0e9h, 052h, 0ffh, 0ffh, 0ffh
    DB 06ah, 003h
    DB 059h
    DB 039h, 00dh
    DD ?g_gameMode@@3HA
    DB 075h, 01ch
    DB 06ah, 00ch
    DB 08dh, 045h, 010h
    DB 059h
    DB 08bh, 013h
    DB 089h, 010h
    DB 003h, 0dfh
    DB 003h, 0c7h
    DB 049h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 075h, 0efh
    DB 0e9h, 02bh, 0ffh, 0ffh, 0ffh
    DB 0b8h
    DD ?g_gameCameraWorldPosition@@3UVector3@@A
    DB 08bh, 013h
    DB 089h, 010h
    DB 003h, 0dfh
    DB 003h, 0c7h
    DB 049h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 075h, 0efh
    DB 06ah, 009h
    DB 0b8h
    DD ?g_gameInverseViewMatrix@@3UMatrix3@@A
    DB 059h
    DB 08bh, 013h
    DB 089h, 010h
    DB 003h, 0dfh
    DB 003h, 0c7h
    DB 049h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 075h, 0efh
    DB 0e9h, 0f7h, 0feh, 0ffh, 0ffh
    DB 08bh, 003h
    DB 003h, 0dfh
    DB 069h, 0c0h, 0fch, 000h, 000h, 000h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 0c6h, 080h
    DD ?g_gameBoxes@@3PAUGameBox@@A + 58h
    DB 001h
    DB 0e9h, 0dbh, 0feh, 0ffh, 0ffh
    call ?InitializeWaterField@@YAXXZ
    DB 033h, 0dbh
    DB 053h
    call ?BuildDefaultGameArena@@YAXH@Z
    DB 059h
    DB 089h, 01dh
    DD ?g_screenTintLevel@@3HA
    call ?ReplayWriteBoundary@@YAXXZ
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 0d4h, 000h, 000h, 020h, 042h
    DB 0c7h, 045h, 0d8h, 000h, 000h, 00ch, 042h
    DB 0c7h, 045h, 0dch, 000h, 000h, 020h, 0c1h
    DB 08dh, 075h, 0d4h
    DB 08dh, 07dh, 0b0h
    DB 0a5h
    DB 053h
    DB 0a5h
    DB 051h
    DB 08dh, 045h, 0b0h
    DB 0a5h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?SetSceneTransform@@YAXAAUVector3@@M@Z
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 083h, 0c4h, 00ch
    DB 0e9h, 083h, 0feh, 0ffh, 0ffh
    DB 08bh, 033h
    DB 089h, 075h, 0fch
    DB 069h, 0f6h, 0fch, 000h, 000h, 000h
    DB 081h, 0c6h
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 003h, 0dfh
    DB 039h, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 089h, 075h, 0f8h
    DB 077h, 021h
    DB 0a1h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0c6h, 040h, 058h, 001h
    DB 081h, 005h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0fch, 000h, 000h, 000h
    DB 039h, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 076h, 0e5h
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 0c6h, 046h, 058h, 000h
    DB 08bh, 03bh
    DB 083h, 0c3h, 004h
    DB 083h, 0ffh, 064h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 00fh, 08fh, 0a3h, 003h, 000h, 000h
    DB 085h, 0ffh
    DB 00fh, 08ch, 09bh, 003h, 000h, 000h
    DB 08bh, 0dfh
    DB 0c1h, 0e3h, 004h
    DB 053h
    call ??2@YAPAXI@Z
    DB 085h, 0c0h
    DB 089h, 006h
    DB 00fh, 095h, 0c0h
    DB 050h
    call ?SumoAssert@@YAX_N@Z
    DB 08bh, 006h
    DB 003h, 0c3h
    DB 083h, 0c4h, 008h
    DB 085h, 0ffh
    DB 089h, 046h, 004h
    DB 07eh, 03ch
    DB 033h, 0c9h
    DB 08bh, 006h
    DB 06ah, 003h
    DB 003h, 0c1h
    DB 05ah
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 01bh
    DB 089h, 018h
    DB 083h, 005h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 004h
    DB 083h, 0c0h, 004h
    DB 04ah
    DB 075h, 0e9h
    DB 08bh, 006h
    DB 0c6h, 044h, 008h, 00ch, 000h
    DB 08bh, 006h
    DB 0c6h, 044h, 008h, 00dh, 000h
    DB 08bh, 006h
    DB 066h, 083h, 064h, 008h, 00eh, 000h
    DB 083h, 0c1h, 010h
    DB 04fh
    DB 075h, 0c6h
    DB 0a1h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 008h
    DB 083h, 0c0h, 004h
    DB 0a3h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 038h
    DB 083h, 0c0h, 004h
    DB 083h, 0f9h, 064h
    DB 089h, 04dh, 000h
    DB 0a3h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 00fh, 08fh, 01ch, 003h, 000h, 000h
    DB 085h, 0c9h
    DB 00fh, 08ch, 014h, 003h, 000h, 000h
    DB 083h, 0ffh, 064h
    DB 00fh, 08fh, 013h, 003h, 000h, 000h
    DB 085h, 0ffh
    DB 00fh, 08ch, 00bh, 003h, 000h, 000h
    DB 08dh, 01ch, 0ffh
    DB 0c1h, 0e3h, 002h
    DB 053h
    call ??2@YAPAXI@Z
    DB 089h, 046h, 010h
    DB 003h, 0c3h
    DB 08bh, 05dh, 000h
    DB 0c1h, 0e3h, 003h
    DB 053h
    DB 089h, 046h, 014h
    call ??2@YAPAXI@Z
    DB 085h, 0ffh
    DB 059h
    DB 059h
    DB 08dh, 00ch, 018h
    DB 089h, 046h, 008h
    DB 089h, 04eh, 00ch
    DB 089h, 045h, 00ch
    DB 00fh, 08eh, 0c8h, 000h, 000h, 000h
    DB 033h, 0dbh
    DB 089h, 07dh, 000h
    DB 08bh, 00dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 0d9h, 0eeh
    DB 08bh, 046h, 010h
    DB 08bh, 009h
    DB 08dh, 044h, 018h, 01ch
    DB 089h, 008h
    DB 08bh, 046h, 010h
    DB 083h, 005h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 004h
    DB 08bh, 04dh, 00ch
    DB 089h, 04ch, 018h, 010h
    DB 08bh, 046h, 010h
    DB 003h, 0c3h
    DB 0d9h, 058h, 008h
    DB 033h, 0c9h
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 004h
    DB 0d9h, 0eeh
    DB 0d9h, 018h
    DB 08bh, 046h, 010h
    DB 039h, 04ch, 018h, 01ch
    DB 07eh, 06ah
    DB 0a1h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 000h
    DB 08bh, 055h, 00ch
    DB 089h, 042h, 004h
    DB 083h, 005h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 004h
    DB 08bh, 046h, 010h
    DB 08bh, 044h, 018h, 010h
    DB 083h, 07ch, 0c8h, 004h, 000h
    DB 00fh, 09dh, 0c0h
    DB 050h
    call ?SumoAssert@@YAX_N@Z
    DB 08bh, 056h, 004h
    DB 02bh, 016h
    DB 08bh, 046h, 010h
    DB 08bh, 044h, 018h, 010h
    DB 0c1h, 0fah, 004h
    DB 039h, 054h, 0c8h, 004h
    DB 00fh, 09ch, 0c0h
    DB 050h
    call ?SumoAssert@@YAX_N@Z
    DB 08bh, 046h, 010h
    DB 08bh, 044h, 018h, 010h
    DB 083h, 045h, 00ch, 008h
    DB 08dh, 004h, 0c8h
    DB 08bh, 050h, 004h
    DB 0c1h, 0e2h, 004h
    DB 003h, 016h
    DB 083h, 0c4h, 008h
    DB 089h, 010h
    DB 08bh, 046h, 010h
    DB 041h
    DB 03bh, 04ch, 018h, 01ch
    DB 07ch, 096h
    DB 08bh, 046h, 010h
    DB 003h, 0c3h
    DB 050h
    DB 08bh, 0ceh
    call ?UpdateFacePlane@GameBox@@QAEXAAUGameBoxFace@@@Z
    DB 083h, 0c3h, 024h
    DB 0ffh, 04dh, 000h
    DB 00fh, 085h, 03dh, 0ffh, 0ffh, 0ffh
    DB 0a1h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 008h
    DB 06ah, 004h
    DB 05fh
    DB 003h, 0c7h
    DB 089h, 04eh, 030h
    DB 0a3h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 08bh, 008h
    DB 089h, 04eh, 034h
    DB 003h, 0c7h
    DB 08bh, 0ceh
    DB 0a3h
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    call ?InitializePhysics@GameBox@@QAEXXZ
    DB 08bh, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 06ah, 003h
    DB 083h, 0c6h, 020h
    DB 058h
    DB 08bh, 00bh
    DB 089h, 00eh
    DB 003h, 0dfh
    DB 003h, 0f7h
    DB 048h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 075h, 0efh
    DB 08bh, 003h
    DB 08bh, 04dh, 0f8h
    DB 089h, 041h, 054h
    DB 08bh, 045h, 0fch
    DB 08dh, 048h, 00ch
    DB 089h, 04dh, 0fch
    DB 0dbh, 045h, 0fch
    DB 083h, 0ech, 00ch
    DB 08dh, 044h, 000h, 00ch
    DB 0d9h, 054h, 024h, 008h
    DB 089h, 045h, 0fch
    DB 08dh, 045h, 080h
    DB 0d9h, 05ch, 024h, 004h
    DB 083h, 0c3h, 004h
    DB 0dbh, 045h, 0fch
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08bh, 045h, 0f8h
    DB 08dh, 07dh, 0bch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 0b8h, 084h, 000h, 000h, 000h
    DB 08dh, 075h, 0bch
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 08dh, 048h, 060h
    DB 0a5h
    call ?SetIdentity@Matrix3@@QAEXXZ
    DB 08bh, 045h, 0f8h
    DB 0c6h, 080h, 0d0h, 000h, 000h, 000h, 001h
    DB 0e9h, 0cdh, 0fbh, 0ffh, 0ffh
    DB 08bh, 003h
    DB 069h, 0c0h, 0fch, 000h, 000h, 000h
    DB 06ah, 004h
    DB 05ah
    DB 003h, 0dah
    DB 005h
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 08dh, 088h, 084h, 000h, 000h, 000h
    DB 08bh, 0f1h
    DB 08dh, 07dh, 0c8h
    DB 0a5h
    DB 0a5h
    DB 06ah, 003h
    DB 0a5h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 089h, 045h, 0fch
    DB 089h, 04dh, 000h
    DB 05eh
    DB 08bh, 03bh
    DB 089h, 039h
    DB 003h, 0dah
    DB 003h, 0cah
    DB 04eh
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 075h, 0efh
    DB 06ah, 009h
    DB 083h, 0c0h, 060h
    DB 059h
    DB 08bh, 033h
    DB 089h, 030h
    DB 003h, 0dah
    DB 003h, 0c2h
    DB 049h
    DB 089h, 01dh
    DD ?g_replayPlaybackStream@@3VReplayStream@@A + 10h
    DB 075h, 0efh
    DB 08bh, 04dh, 000h
    DB 08dh, 045h, 0c8h
    DB 050h
    DB 08dh, 045h, 0a4h
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 0ech
    DB 08bh, 07dh, 0fch
    DB 081h, 0c7h, 09ch, 000h, 000h, 000h
    DB 08bh, 0f0h
    DB 08bh, 045h, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d8h, 000h
    DB 06ah, 004h
    DB 0d9h, 05dh, 0ech
    DB 05fh
    DB 0d9h, 045h, 0f0h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 045h, 0f4h
    DB 0d8h, 040h, 008h
    DB 0d9h, 05dh, 0f4h
    DB 0d9h, 045h, 008h
    DB 0d8h, 005h
    DD ?g_gameOne@@3MB
    DB 0d9h, 05dh, 008h
    DB 083h, 07dh, 0f8h, 001h
    DB 00fh, 085h, 025h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 08dh, 045h, 0e4h
    DB 0d8h, 075h, 008h
    DB 050h
    DB 08dh, 045h, 08ch
    DB 050h
    DB 068h
    DD ?g_freeCameraTarget@@3UVector3@@A
    DB 08dh, 045h, 098h
    DB 050h
    DB 08dh, 04dh, 0ech
    DB 0c7h, 045h, 0e4h, 00ah, 0d7h, 0a3h, 03ch
    DB 0d9h, 045h, 0ech
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 0ech
    DB 0d9h, 045h, 0f0h
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 045h, 0f4h
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 0f4h
    DB 0ddh, 0d8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 005h
    DD ?g_freeCameraTarget@@3UVector3@@A
    DB 0d8h, 000h
    DB 0ffh, 04dh, 004h
    DB 083h, 07dh, 004h, 000h
    DB 0d9h, 01dh
    DD ?g_freeCameraTarget@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_freeCameraTarget@@3UVector3@@A + 4
    DB 0d8h, 040h, 004h
    DB 0d9h, 01dh
    DD ?g_freeCameraTarget@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_freeCameraTarget@@3UVector3@@A + 8
    DB 0d8h, 040h, 008h
    DB 0d9h, 01dh
    DD ?g_freeCameraTarget@@3UVector3@@A + 8
    DB 00fh, 08fh, 065h, 0fah, 0ffh, 0ffh
    DB 0a1h
    DD ?g_replayStream@@3VReplayStream@@A
    DB 08bh, 08dh, 010h, 004h, 000h, 000h
    DB 05fh
    DB 05eh
    DB 0a3h
    DD ?g_gameReplayFrame@@3HA
    DB 05bh
    call @__security_check_cookie@4
    DB 081h, 0c5h, 014h, 004h, 000h, 000h
    DB 0c9h
    DB 0c3h
    DB 033h, 0c0h
    DB 040h
    DB 0c6h, 000h, 07fh
    DB 0ebh, 0fah
    DB 033h, 0c0h
    DB 040h
    DB 0c6h, 000h, 07fh
    DB 0ebh, 0fah
    DB 033h, 0c0h
    DB 040h
    DB 0c6h, 000h, 07fh
    DB 0ebh, 0fah
?UpdateGameReplay@@YAHXZ ENDP

END
