.686
.model flat
option casemap:none

EXTERN ___security_cookie:DWORD
EXTERN __real@be4ccccd:DWORD
EXTERN _sprintf:PROC
EXTERN ?AdvanceGameSimulation@@YAXXZ:PROC
EXTERN ?DrawGameText@@YAPADMMPADH@Z:PROC
EXTERN ?g_freeCameraAimScale@@3MB:DWORD
EXTERN ?g_gameAlternateCameraMode@@3HA:DWORD
EXTERN ?g_gameCameraInputOffsetScale@@3MB:DWORD
EXTERN ?g_gameDemoTimeoutText@@3PADA:DWORD
EXTERN ?g_gameHumanPlayerCount@@3HA:DWORD
EXTERN ?g_gameKeyPressed@@3PAEA:DWORD
EXTERN ?g_gameLineVertexCursor@@3PAEA:DWORD
EXTERN ?g_gameLineVertexScratch@@3EA:DWORD
EXTERN ?g_gameMen@@3PAUGameMan@@A:DWORD
EXTERN ?g_gameMode@@3HA:DWORD
EXTERN ?g_gamePrimaryInputPressed@@3HA:DWORD
EXTERN ?g_gameProjectileSpin@@3MB:DWORD
EXTERN ?g_gameProjectionMinimum@@3MB:DWORD
EXTERN ?g_gameRenderQualityCode@@3HA:DWORD
EXTERN ?g_gameRenderQualityEnabled@@3HA:DWORD
EXTERN ?g_gameReplayFrame@@3HA:DWORD
EXTERN ?g_gameRuntimeMode@@3HA:DWORD
EXTERN ?g_gameScores@@3PAHA:DWORD
EXTERN ?g_gameSimulationPaused@@3HA:DWORD
EXTERN ?g_levelLoadState@@3PAHA:DWORD
EXTERN ?g_nextGameMan@@3PAUGameMan@@A:DWORD
EXTERN ?g_screenTintColor@@3IA:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?GameAudioNoOpCallback@@YAXXZ:PROC
EXTERN ?InitializeGameRuntimeState@@YAHXZ:PROC
EXTERN ?RenderGameScene@@YAJXZ:PROC
EXTERN ?ResetRenderVertexScratch@@YAXXZ:PROC
EXTERN ?RestartGameMusic@@YAXH@Z:PROC
EXTERN ?SaveGameScreenshot@@YAHPADH@Z:PROC
EXTERN ?SetGameFpuControlWord@@YAXXZ:PROC
EXTERN ?StartGameRound@@YAXXZ:PROC
EXTERN ?UpdateFreeGameCamera@@YAXH@Z:PROC
EXTERN ?UpdateGameCamera@@YAXXZ:PROC
EXTERN ?UpdateGameMenuScreen@@YAXE@Z:PROC
EXTERN ?UpdateHiddenGameScreen@@YAHXZ:PROC
EXTERN @__security_check_cookie@4:PROC

.const
PUBLIC gameTimerFormat
gameTimerFormat DB "%2d.%2d", 0
PUBLIC screenshotPrefix
screenshotPrefix DB "sumotori", 0
PUBLIC gameTimeoutTextX
gameTimeoutTextX DD 0bee66666h

PUBLIC __real@3d4ccccd
__real@3d4ccccd DD 03d4ccccdh
PUBLIC __real@3e4ccccd
__real@3e4ccccd DD 03e4ccccdh
PUBLIC __real@3ed70a3d
__real@3ed70a3d DD 03ed70a3dh
PUBLIC __real@be19999a
__real@be19999a DD 0be19999ah
PUBLIC __real@bf4ccccd
__real@bf4ccccd DD 0bf4ccccdh

PUBLIC ??_C@_08EDEIJMPL@Blue?5guy?$AA@
??_C@_08EDEIJMPL@Blue?5guy?$AA@ DB "Blue guy", 0
PUBLIC ??_C@_08HDCEKEID@Grey?5guy?$AA@
??_C@_08HDCEKEID@Grey?5guy?$AA@ DB "Grey guy", 0
PUBLIC ??_C@_09IBGCBBGF@Brown?5guy?$AA@
??_C@_09IBGCBBGF@Brown?5guy?$AA@ DB "Brown guy", 0
PUBLIC ??_C@_09GMKELAO@Green?5guy?$AA@
??_C@_09GMKELAO@Green?5guy?$AA@ DB "Green guy", 0
PUBLIC ??_C@_0BC@CMDHFBOK@Blue?5guy?5?$CIplayer?$CJ?$AA@
??_C@_0BC@CMDHFBOK@Blue?5guy?5?$CIplayer?$CJ?$AA@ DB "Blue guy (player)", 0
PUBLIC ??_C@_0BD@ELJGFIEN@Grey?5guy?5?$CIplayer2?$CJ?$AA@
??_C@_0BD@ELJGFIEN@Grey?5guy?5?$CIplayer2?$CJ?$AA@ DB "Grey guy (player2)", 0
PUBLIC ??_C@_0O@GDOLPJNL@?5Game?5?6?5?5?9?$DO?5?5?$AA@
??_C@_0O@GDOLPJNL@?5Game?5?6?5?5?9?$DO?5?5?$AA@ DB " Game ", 0ah, "  ->  ", 0
PUBLIC ??_C@_0O@HMMHLPJI@?5Game?5?6?5?5?$DM?9?5?5?$AA@
??_C@_0O@HMMHLPJI@?5Game?5?6?5?5?$DM?9?5?5?$AA@ DB " Game ", 0ah, "  <-  ", 0
PUBLIC ??_C@_0CE@IJFEJLDO@?5?5?5?5?5?5?5?5?5?5?5?6?5Game?5Over?5?6?5?5?5?5?5?5?5?5@
??_C@_0CE@IJFEJLDO@?5?5?5?5?5?5?5?5?5?5?5?6?5Game?5Over?5?6?5?5?5?5?5?5?5?5@ DB "           ", 0ah, " Game Over ", 0ah, "           ", 0
PUBLIC ??_C@_0BG@OCKEHAMO@Space?5to?5restart?5game?$AA@
??_C@_0BG@OCKEHAMO@Space?5to?5restart?5game?$AA@ DB "Space to restart game", 0
PUBLIC ??_C@_0GI@MDDNNHKM@Controls?3?6?5DOWN?5?5?5?5?5?5?9?5start?5mat@
??_C@_0GI@MDDNNHKM@Controls?3?6?5DOWN?5?5?5?5?5?5?9?5start?5mat@ DB "Controls:", 0ah, " DOWN      - start match", 0ah, " UP        - walk forward", 0ah, " BACKSPACE - Push", 0ah, " ENTER     - Push 1 hand", 0
PUBLIC ??_C@_0GI@OIFMIMB@Controls?3?6?5S?5?5?5?5?5?5?5?5?5?9?5start?5mat@
??_C@_0GI@OIFMIMB@Controls?3?6?5S?5?5?5?5?5?5?5?5?5?9?5start?5mat@ DB "Controls:", 0ah, " S         - start match", 0ah, " W         - walk forward", 0ah, " SHIFT     - Push", 0ah, " CTRL      - Push 1 hand", 0

.code

; FUNCTION: SUMO 0x0040e1b0
; FUNCTION: EDITOR 0x0040e1d2
PUBLIC ?RunGameFrame@@YAXE@Z
?RunGameFrame@@YAXE@Z PROC
    DB 055h, 08dh, 06ch, 024h, 08ch, 081h, 0ech, 0d4h, 004h, 000h, 000h, 0a1h
    DD ___security_cookie
    DB 053h, 089h, 045h, 070h
    call ?SetGameFpuControlWord@@YAXXZ
    DB 0a1h
    DD ?g_gameMode@@3HA
    DB 033h, 0dbh, 0ffh, 005h
    DD ?g_screenTintLevel@@3HA
    DB 03bh, 0c3h, 089h, 09dh, 0b0h, 0fbh, 0ffh, 0ffh, 0c7h, 005h
    DD ?g_gameLineVertexCursor@@3PAEA
    DD ?g_gameLineVertexScratch@@3EA
    DB 07ch, 019h, 083h, 0f8h, 002h, 07eh, 00fh, 083h, 0f8h, 003h, 075h, 00fh, 06ah, 004h
    call ?UpdateFreeGameCamera@@YAXH@Z
    DB 059h, 0ebh, 005h
    call ?UpdateGameCamera@@YAXXZ
    call ?ResetRenderVertexScratch@@YAXXZ
    DB 039h, 01dh
    DD ?g_gameSimulationPaused@@3HA
    DB 075h, 005h
    call ?AdvanceGameSimulation@@YAXXZ
    DB 0a1h
    DD ?g_levelLoadState@@3PAHA + 010h
    DB 083h, 0f8h, 00ah, 075h, 00bh, 0ffh, 075h, 07ch
    call ?UpdateGameMenuScreen@@YAXE@Z
    DB 059h, 0ebh, 02ah, 083h, 0f8h, 00bh, 075h, 005h
    call ?UpdateHiddenGameScreen@@YAHXZ
    call ?GameAudioNoOpCallback@@YAXXZ
    DB 039h, 01dh
    DD ?g_gamePrimaryInputPressed@@3HA
    DB 074h, 013h, 06ah, 003h, 089h, 01dh
    DD ?g_gamePrimaryInputPressed@@3HA
    call ?RestartGameMusic@@YAXH@Z
    DB 059h
    call ?InitializeGameRuntimeState@@YAHXZ
    DB 080h, 07dh, 07ch, 000h, 00fh, 084h, 0f9h, 003h, 000h, 000h, 080h, 03dh
    DD ?g_gameKeyPressed@@3PAEA + 07h
    DB 000h, 074h, 01fh, 033h, 0c0h, 040h, 0c6h, 005h
    DD ?g_gameKeyPressed@@3PAEA + 07h
    DB 000h, 089h, 085h, 0b0h, 0fbh, 0ffh, 0ffh, 0c7h, 005h
    DD ?g_gameRenderQualityCode@@3HA
    DB 00ch, 000h, 000h, 000h, 0a3h
    DD ?g_gameRenderQualityEnabled@@3HA
    DB 0a1h
    DD ?g_gameMode@@3HA
    DB 03bh, 0c3h, 056h, 00fh, 085h, 0e8h, 002h, 000h, 000h, 057h, 033h, 0c0h, 0beh
    DD ??_C@_08EDEIJMPL@Blue?5guy?$AA@
    DB 08dh, 07dh, 0b8h, 0a5h, 0a5h, 0a4h, 08dh, 07dh, 0c1h, 0abh, 0abh, 0abh, 0abh, 033h, 0c0h, 0beh
    DD ??_C@_08HDCEKEID@Grey?5guy?$AA@
    DB 08dh, 07dh, 0d1h, 0a5h, 0a5h, 0a4h, 08dh, 07dh, 0dah, 0abh, 0abh, 0abh, 0abh, 033h, 0c0h, 0beh
    DD ??_C@_09IBGCBBGF@Brown?5guy?$AA@
    DB 08dh, 07dh, 0eah, 0a5h, 0a5h, 066h, 0a5h, 08dh, 07dh, 0f4h, 0abh, 0abh, 0abh, 066h, 0abh, 0aah
    DB 0beh
    DD ??_C@_09GMKELAO@Green?5guy?$AA@
    DB 08dh, 07dh, 003h, 0a5h, 0a5h, 066h, 0a5h, 033h, 0c0h, 08dh, 07dh, 00dh, 0abh, 0abh, 0abh, 066h
    DB 0abh, 0aah, 0beh
    DD ??_C@_0BC@CMDHFBOK@Blue?5guy?5?$CIplayer?$CJ?$AA@
    DB 08dh, 07dh, 01ch, 0a5h, 0a5h, 0a5h, 0a5h, 066h, 0a5h, 033h, 0c0h, 08dh, 07dh, 02eh, 0abh, 066h
    DB 0abh, 0aah, 0beh
    DD ??_C@_0BD@ELJGFIEN@Grey?5guy?5?$CIplayer2?$CJ?$AA@
    DB 08dh, 07dh, 035h, 0a5h, 0a5h, 0a5h, 0a5h, 066h, 0a5h, 0a4h, 033h, 0c0h, 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 010h
    DB 00bh, 08dh, 07dh, 048h, 0abh, 0c7h, 085h, 0a0h, 0fbh, 0ffh, 0ffh, 0ffh, 080h, 080h, 0e0h, 0c7h
    DB 085h, 0a4h, 0fbh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0c0h, 0c7h, 085h, 0a8h, 0fbh, 0ffh, 0ffh, 000h
    DB 080h, 0c0h, 0e0h, 0c7h, 085h, 0ach, 0fbh, 0ffh, 0ffh, 020h, 0e0h, 020h, 0c0h, 066h, 0abh, 0c7h
    DB 085h, 0b4h, 0fbh, 0ffh, 0ffh, 000h, 000h, 000h, 03fh, 00fh, 084h, 0d6h, 000h, 000h, 000h, 0a1h
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 0bfh
    DD ?g_gameMen@@3PAUGameMan@@A
    DB 02bh, 0c7h, 099h, 0b9h, 030h, 007h, 000h, 000h, 0f7h, 0f9h, 085h, 0c0h, 00fh, 08eh, 0bah, 000h
    DB 000h, 000h, 08dh, 034h, 09dh
    DD ?g_levelLoadState@@3PAHA
    DB 08bh, 006h, 083h, 0f8h, 0ffh, 00fh, 084h, 090h, 000h, 000h, 000h, 0ffh, 0b4h, 085h, 0a0h, 0fbh
    DB 0ffh, 0ffh, 0d9h, 085h, 0b4h, 0fbh, 0ffh, 0ffh, 08ah, 0cbh, 080h, 0c1h, 031h, 08dh, 045h, 07eh
    DB 050h, 0c6h, 045h, 07fh, 000h, 088h, 04dh, 07eh, 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD __real@be4ccccd
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 08bh, 006h, 08bh, 0c8h, 069h, 0c9h, 030h, 007h, 000h, 000h, 083h, 0c4h, 010h, 083h, 0b9h
    DD ?g_gameMen@@3PAUGameMan@@A + 06fch
    DB 001h, 08bh, 0c8h, 075h, 009h, 06bh, 0c9h, 019h, 08dh, 04ch, 00dh, 01ch, 0ebh, 007h, 06bh, 0c9h
    DB 019h, 08dh, 04ch, 00dh, 0b8h, 0ffh, 0b4h, 085h, 0a0h, 0fbh, 0ffh, 0ffh, 0d9h, 085h, 0b4h, 0fbh
    DB 0ffh, 0ffh, 051h, 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD __real@be19999a
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 0d9h, 085h, 0b4h, 0fbh, 0ffh, 0ffh, 083h, 0c4h, 010h, 0d8h, 025h
    DD __real@3d4ccccd
    DB 0d9h, 09dh, 0b4h, 0fbh, 0ffh, 0ffh, 0a1h
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 02bh, 0c7h, 099h, 0b9h, 030h, 007h, 000h, 000h, 0f7h, 0f9h, 043h, 03bh, 0d8h, 00fh, 08ch, 046h
    DB 0ffh, 0ffh, 0ffh, 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 010h
    DB 002h, 00fh, 085h, 0f1h, 000h, 000h, 000h, 0a1h
    DD ?g_gameScores@@3PAHA
    DB 08bh, 00dh
    DD ?g_gameScores@@3PAHA + 04h
    DB 033h, 0dbh, 083h, 0f8h, 005h, 07dh, 009h, 083h, 0f9h, 005h, 00fh, 08ch, 096h, 000h, 000h, 000h
    DB 08dh, 051h, 002h, 03bh, 0c2h, 07dh, 00bh, 08dh, 051h, 0feh, 03bh, 0c2h, 00fh, 08fh, 084h, 000h
    DB 000h, 000h, 033h, 0dbh, 043h, 033h, 0d2h, 03bh, 0c8h, 07eh, 002h, 08bh, 0d3h, 0beh
    DD ??_C@_0O@GDOLPJNL@?5Game?5?6?5?5?9?$DO?5?5?$AA@
    DB 0d9h, 005h
    DD __real@3ed70a3d
    DB 08dh, 07dh, 050h, 0a5h, 0a5h, 0a5h, 0ffh, 0b4h, 095h, 0a0h, 0fbh, 0ffh, 0ffh, 066h, 0a5h, 033h
    DB 0c0h, 08dh, 07dh, 05eh, 066h, 0abh, 0beh
    DD ??_C@_0O@HMMHLPJI@?5Game?5?6?5?5?$DM?9?5?5?$AA@
    DB 08dh, 07dh, 060h, 0a5h, 0a5h, 0a5h, 066h, 0a5h, 08dh, 07dh, 06eh, 0c1h, 0e2h, 004h, 066h, 0abh
    DB 08dh, 044h, 015h, 050h, 050h, 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD ?g_freeCameraAimScale@@3MB
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 0d9h, 005h
    DD ?g_gameProjectileSpin@@3MB
    DB 083h, 0c4h, 010h, 068h, 000h, 0ffh, 0ffh, 0c0h, 068h
    DD ??_C@_0CE@IJFEJLDO@?5?5?5?5?5?5?5?5?5?5?5?6?5Game?5Over?5?6?5?5?5?5?5?5?5?5@
    DB 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD ?g_freeCameraAimScale@@3MB
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 083h, 0c4h, 010h, 0d9h, 005h
    DD ?g_gameProjectionMinimum@@3MB
    DB 068h, 0c0h, 0c0h, 0c0h, 0c0h, 068h
    DD ??_C@_0BG@OCKEHAMO@Space?5to?5restart?5game?$AA@
    DB 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD __real@bf4ccccd
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 083h, 0c4h, 010h, 080h, 03dh
    DD ?g_gameKeyPressed@@3PAEA + 039h
    DB 000h, 074h, 010h, 085h, 0dbh, 074h, 007h
    call ?InitializeGameRuntimeState@@YAHXZ
    DB 0ebh, 005h
    call ?StartGameRound@@YAXXZ
    DB 033h, 0dbh, 039h, 01dh
    DD ?g_levelLoadState@@3PAHA + 010h
    DB 05fh, 00fh, 085h, 0b1h, 000h, 000h, 000h, 0d9h, 005h
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 0beh, 0ffh, 0ffh, 0ffh, 0b0h, 056h, 068h
    DD ??_C@_0GI@MDDNNHKM@Controls?3?6?5DOWN?5?5?5?5?5?5?9?5start?5mat@
    DB 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD __real@3e4ccccd
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 083h, 0c4h, 010h, 039h, 01dh
    DD ?g_gameAlternateCameraMode@@3HA
    DB 075h, 009h, 083h, 03dh
    DD ?g_gameHumanPlayerCount@@3HA
    DB 002h, 07ch, 078h, 056h, 068h
    DD ??_C@_0GI@OIFMIMB@Controls?3?6?5S?5?5?5?5?5?5?5?5?5?9?5start?5mat@
    DB 0ebh, 053h, 080h, 03dh
    DD ?g_gameKeyPressed@@3PAEA + 039h
    DB 000h, 074h, 00ah
    call ?StartGameRound@@YAXXZ
    DB 0a1h
    DD ?g_gameMode@@3HA
    DB 083h, 0f8h, 001h, 074h, 00ah, 083h, 0f8h, 003h, 074h, 005h, 083h, 0f8h, 014h, 075h, 04eh, 0a1h
    DD ?g_gameReplayFrame@@3HA
    DB 03bh, 0c3h, 074h, 045h, 06ah, 064h, 059h, 099h, 0f7h, 0f9h, 052h, 050h, 08dh, 085h, 0b8h, 0fbh
    DB 0ffh, 0ffh, 068h
    DD gameTimerFormat
    DB 050h
    call _sprintf
    DB 083h, 0c4h, 010h, 068h, 0c0h, 0c0h, 0c0h, 0c0h, 08dh, 085h, 0b8h, 0fbh, 0ffh, 0ffh, 050h, 0d9h
    DB 005h
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD __real@bf4ccccd
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 083h, 0c4h, 010h, 083h, 03dh
    DD ?g_gameRuntimeMode@@3HA
    DB 002h, 0c6h, 005h
    DD ?g_gameKeyPressed@@3PAEA + 039h
    DB 000h, 05eh
IF SUMO_REGISTERED_BUILD
    DB 0ebh
ELSE
    DB 075h
ENDIF
    DB 03bh, 0d9h, 005h
    DD __real@3e4ccccd
    DB 068h, 0ffh, 0ffh, 0ffh, 0c0h, 068h
    DD ?g_gameDemoTimeoutText@@3PADA
    DB 051h, 051h, 0d9h, 05ch, 024h, 004h, 0d9h, 005h
    DD gameTimeoutTextX
    DB 0d9h, 01ch, 024h
    call ?DrawGameText@@YAPADMMPADH@Z
    DB 083h, 0c4h, 010h, 0c7h, 005h
    DD ?g_screenTintColor@@3IA
    DB 050h, 050h, 050h, 000h, 0c7h, 005h
    DD ?g_gameSimulationPaused@@3HA
    DB 001h, 000h, 000h, 000h
    call ?RenderGameScene@@YAJXZ
    call ?SetGameFpuControlWord@@YAXXZ
    DB 039h, 09dh, 0b0h, 0fbh, 0ffh, 0ffh, 074h, 00dh, 053h, 068h
    DD screenshotPrefix
    call ?SaveGameScreenshot@@YAHPADH@Z
    DB 059h, 059h, 08bh, 04dh, 070h, 05bh
    call @__security_check_cookie@4
    DB 083h, 0c5h, 074h, 0c9h, 0c3h
?RunGameFrame@@YAXE@Z ENDP

END
