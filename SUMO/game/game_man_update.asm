.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??GVector3@@QAE?AU0@XZ:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??YVector3@@QAEXAAU0@@Z:PROC
EXTERN ?CalculateAngularMomentum@GameMan@@QAE?AUVector3@@AAU2@0@Z:PROC
EXTERN ?CalculateCenterOfMassPosition@GameMan@@QAE?AUVector3@@XZ:PROC
EXTERN ?CalculateCenterOfMassVelocity@GameMan@@QAE?AUVector3@@XZ:PROC
EXTERN ?CalculateKineticEnergy@GameMan@@QAEMXZ:PROC
EXTERN ?CalculateLimbAngleCosine@@YAMMMM@Z:PROC
EXTERN ?ChooseAiInput@GameMan@@QAEIPAU1@@Z:PROC
EXTERN ?Column1@Matrix3@@QAE?AUVector3@@XZ:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?FindNearestOpponent@GameMan@@QAEPAU1@AAUVector3@@0@Z:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?Normalized@Vector3@@QAE?AU1@XZ:PROC
EXTERN ?ReadGameManInputMask@@YIHH@Z:PROC
EXTERN ?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z:PROC
EXTERN ?Rotate@Vector3@@QAEXAAU1@@Z:PROC
EXTERN ?Rotate@Vector3@@QAEXAAU1@MM@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?SetGameManAudioState@@YAXPAUGameMan@@H@Z:PROC
EXTERN ?SubtractOffset@GameBoxPoint@@QAEXAAUVector3@@@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?g_boxWaterBuoyancyScale@@3MB:DWORD
EXTERN ?g_boxWaterDiagonalScale@@3MB:DWORD
EXTERN ?g_boxWaterSurfaceOffset@@3MB:DWORD
EXTERN ?g_freeCameraAimScale@@3MB:DWORD
EXTERN ?g_gameActivityDecay@@3MB:DWORD
EXTERN ?g_gameAiLateralRecoveryThreshold@@3MB:DWORD
EXTERN ?g_gameAiMotionSquaredLimit@@3MB:DWORD
EXTERN ?g_gameBoxYScale@@3MB:DWORD
EXTERN ?g_gameCameraAimDamping@@3MB:DWORD
EXTERN ?g_gameCameraDistanceBias@@3MB:DWORD
EXTERN ?g_gameCameraHeightScale@@3MB:DWORD
EXTERN ?g_gameCameraInputDamping@@3MB:DWORD
EXTERN ?g_gameCameraInputOffsetScale@@3MB:DWORD
EXTERN ?g_gameCameraMinimumDistance@@3MB:DWORD
EXTERN ?g_gameCameraMinimumDistanceScale@@3MB:DWORD
EXTERN ?g_gameDecorationHeight@@3MA:DWORD
EXTERN ?g_gameIsRunning@@3HA:DWORD
EXTERN ?g_gameKeyDown@@3PAEA:BYTE
EXTERN ?g_gameLevelArenaExtent@@3MB:DWORD
EXTERN ?g_gameManPoseImpulseGain@@3MB:DWORD
EXTERN ?g_gameMen@@3PAUGameMan@@A:BYTE
EXTERN ?g_gameMode@@3HA:DWORD
EXTERN ?g_gameNegativeHalf@@3MB:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_gameProjectileHalfSize@@3MB:DWORD
EXTERN ?g_gameProjectileSpin@@3MB:DWORD
EXTERN ?g_gameRoundPlayerCount@@3HA:DWORD
EXTERN ?g_gameTwo@@3MB:DWORD
EXTERN ?g_gameWallCenterSegment@@3MB:DWORD
EXTERN ?g_gameWallSegmentSpacing@@3MB:DWORD
EXTERN ?g_inertiaRadiusScale@@3MB:DWORD
EXTERN ?g_levelLoadState@@3PAHA:DWORD
EXTERN ?g_nextGameMan@@3PAUGameMan@@A:DWORD
EXTERN ?g_parserMinimumBreakability@@3MB:DWORD
EXTERN ?g_parserPi@@3MB:DWORD
EXTERN ?g_randomHalf@@3MB:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_selectedLevelScript@@3HA:DWORD
EXTERN ?g_textureHalf@@3NB:QWORD
EXTERN ?g_unk0x00c09ce0@@3MA:DWORD
EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN ?g_waterBaseHeight@@3MA:DWORD
EXTERN ?g_waterCorrectionScale@@3NB:QWORD
EXTERN ?g_waterNeighborCoupling@@3MB:DWORD
EXTERN ?g_wavyTextDisplacement@@3MB:DWORD
EXTERN ?g_wavyTextPhaseScale@@3MB:DWORD
EXTERN ?g_wavyTextTimeScale@@3MB:DWORD
EXTERN __real@37fba882:DWORD
EXTERN __real@3827c5ac:DWORD
EXTERN __real@3983126f:DWORD
EXTERN __real@3b03126f:DWORD
EXTERN __real@3b9a0275:DWORD
EXTERN __real@3bda740e:DWORD
EXTERN __real@3bea0ea1:DWORD
EXTERN __real@3c23d70a:DWORD
EXTERN __real@3c360b61:DWORD
EXTERN __real@3c7c0fc1:DWORD
EXTERN __real@3c888889:DWORD
EXTERN __real@3c909091:DWORD
EXTERN __real@3c9374bc:DWORD
EXTERN __real@3ca6223e:DWORD
EXTERN __real@3cd67750:DWORD
EXTERN __real@3cf5c28f:DWORD
EXTERN __real@3d088889:DWORD
EXTERN __real@3d1d89d9:DWORD
EXTERN __real@3d23d70a:DWORD
EXTERN __real@3d23d710:DWORD
EXTERN __real@3d4ccccc:DWORD
EXTERN __real@3d4ccccd:DWORD
EXTERN __real@3d70f0f1:DWORD
EXTERN __real@3d75c28f:DWORD
EXTERN __real@3da3d70a:DWORD
EXTERN __real@3dbd3c19:DWORD
EXTERN __real@3dc391d1:DWORD
EXTERN __real@3de147ae:DWORD
EXTERN __real@3e0f5c29:DWORD
EXTERN __real@3e19999a:DWORD
EXTERN __real@3e23d70a:DWORD
EXTERN __real@3e23d70b:DWORD
EXTERN __real@3e4ccccd:DWORD
EXTERN __real@3e6147ae:DWORD
EXTERN __real@3e800000:DWORD
EXTERN __real@3ea8f5c2:DWORD
EXTERN __real@3eb33333:DWORD
EXTERN __real@3eb851ec:DWORD
EXTERN __real@3ec08313:DWORD
EXTERN __real@3f23d70b:DWORD
EXTERN __real@3f28f5c2:DWORD
EXTERN __real@3f75c28f:DWORD
EXTERN __real@3fd3333340000000:QWORD
EXTERN __real@3fd47ae1:DWORD
EXTERN __real@3fd851ea:DWORD
EXTERN __real@3fe66666:DWORD
EXTERN __real@3ffae147:DWORD
EXTERN __real@402ccccd:DWORD
EXTERN __real@40400000:DWORD
EXTERN __real@40933333:DWORD
EXTERN __real@40c00000:DWORD
EXTERN __real@40c80000:DWORD
EXTERN __real@40c90fdb:DWORD
EXTERN __real@41080000:DWORD
EXTERN __real@410b3333:DWORD
EXTERN __real@4114cccd:DWORD
EXTERN __real@43960000:DWORD
EXTERN __real@44c80000:DWORD
EXTERN __real@be19999a:DWORD
EXTERN __real@be4ccccd:DWORD
EXTERN __real@be99999a:DWORD
EXTERN __real@bf19999a:DWORD
EXTERN __real@bf400000:DWORD
EXTERN __real@bfc00000:DWORD
EXTERN __real@c0800000:DWORD
EXTERN __real@c1080000:DWORD
EXTERN _cos:PROC
EXTERN _exp:PROC
EXTERN _fabs:PROC
EXTERN _sin:PROC
EXTERN _sqrt:PROC
EXTERN _tan:PROC

.code

; FUNCTION: SUMO 0x00410b3e
; FUNCTION: EDITOR 0x00410b60
PUBLIC ?Update@GameMan@@QAEXH@Z
?Update@GameMan@@QAEXH@Z PROC
    DB 055h
    DB 08dh, 06ch, 024h, 08ch
    DB 081h, 0ech, 05ch, 005h, 000h, 000h
    DB 053h
    DB 0d9h, 0eeh
    DB 056h
    DB 0d9h, 05dh, 0f0h
    DB 057h
    DB 0d9h, 0eeh
    DB 08dh, 045h, 0e4h
    DB 0d9h, 05dh, 0e0h
    DB 050h
    DB 08bh, 0d9h
    call ?CalculateCenterOfMassPosition@GameMan@@QAE?AUVector3@@XZ
    DB 08dh, 045h, 03ch
    DB 050h
    DB 08bh, 0cbh
    call ?CalculateCenterOfMassVelocity@GameMan@@QAE?AUVector3@@XZ
    DB 08dh, 045h, 03ch
    DB 050h
    DB 08dh, 045h, 0e4h
    DB 050h
    DB 08dh, 045h, 090h
    DB 050h
    DB 08bh, 0cbh
    call ?CalculateAngularMomentum@GameMan@@QAE?AUVector3@@AAU2@0@Z
    DB 08bh, 045h, 07ch
    DB 08dh, 0bbh, 0c8h, 000h, 000h, 000h
    DB 08dh, 075h, 0e4h
    DB 0a5h
    DB 0a5h
    DB 02bh, 0c3h
    DB 0a5h
    DB 099h
    DB 0beh, 030h, 007h, 000h, 000h
    DB 0f7h, 0feh
    DB 033h, 0c9h
    DB 041h
    DB 089h, 04dh, 020h
    DB 03bh, 0c1h
    DB 07eh, 007h
    DB 0c7h, 045h, 020h, 002h, 000h, 000h, 000h
    DB 033h, 0c0h
    DB 039h, 045h, 07ch
    DB 075h, 003h
    DB 089h, 05dh, 07ch
    DB 08bh, 00dh
    DD ?g_screenTintLevel@@3HA
    DB 083h, 0c1h, 0ceh
    DB 039h, 00dh
    DD ?g_levelLoadState@@3PAHA + 18h
    DB 0beh
    DD ?g_gameMen@@3PAUGameMan@@A
    DB 00fh, 08dh, 0beh, 000h, 000h, 000h
    DB 089h, 045h, 024h
    DB 08bh, 015h
    DD ?g_screenTintLevel@@3HA
    DB 08bh, 00ch, 083h
    DB 04ah
    DB 039h, 091h, 0d8h, 000h, 000h, 000h
    DB 07ch, 079h
    DB 083h, 0f8h, 003h
    DB 074h, 074h
    DB 083h, 0f8h, 006h
    DB 074h, 06fh
    DB 083h, 0f8h, 004h
    DB 074h, 06ah
    DB 083h, 0f8h, 007h
    DB 074h, 065h
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 000h
    DB 074h, 05ch
    DB 08dh, 083h, 010h, 007h, 000h, 000h
    DB 083h, 038h, 000h
    DB 075h, 03ch
    DB 0c7h, 000h, 001h, 000h, 000h, 000h
    DB 08bh, 0c3h
    DB 02bh, 0c6h
    DB 099h
    DB 0bfh, 030h, 007h, 000h, 000h
    DB 0f7h, 0ffh
    DB 08bh, 00dh
    DD ?g_gameRoundPlayerCount@@3HA
    DB 049h
    DB 083h, 0f9h, 001h
    DB 089h, 00dh
    DD ?g_gameRoundPlayerCount@@3HA
    DB 089h, 004h, 08dh
    DD ?g_levelLoadState@@3PAHA
    DB 075h, 011h
    DB 083h, 025h
    DD ?g_levelLoadState@@3PAHA + 1ch
    DB 000h
    DB 0c7h, 005h
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 002h, 000h, 000h, 000h
    DB 08bh, 04dh, 07ch
    DB 06ah, 005h
    DB 058h
    DB 089h, 083h, 040h, 001h, 000h, 000h
    DB 089h, 081h, 040h, 001h, 000h, 000h
    DB 08bh, 045h, 024h
    DB 040h
    DB 083h, 0f8h, 00fh
    DB 089h, 045h, 024h
    DB 00fh, 08ch, 068h, 0ffh, 0ffh, 0ffh
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 002h
    DB 075h, 01ah
    DB 083h, 0bbh, 010h, 007h, 000h, 000h, 000h
    DB 075h, 011h
    DB 08bh, 0c3h
    DB 02bh, 0c6h
    DB 099h
    DB 0b9h, 030h, 007h, 000h, 000h
    DB 0f7h, 0f9h
    DB 0a3h
    DD ?g_levelLoadState@@3PAHA
    DB 0ffh, 005h
    DD ?g_levelLoadState@@3PAHA + 1ch
    DB 0d9h, 0e8h
    DB 08bh, 003h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 058h
    DB 08dh, 07dh, 000h
    DB 0d9h, 0eeh
    DB 083h, 0c0h, 060h
    DB 050h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 045h, 0ach
    DB 050h
    DB 0a5h
    DB 0a5h
    DB 08dh, 04dh, 000h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08dh, 04dh, 0ach
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0b0h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 054h
    DB 08dh, 07dh, 000h
    DB 0d9h, 0e8h
    DB 08dh, 045h, 000h
    DB 050h
    DB 0d9h, 05dh, 058h
    DB 08dh, 045h, 0c4h
    DB 0d9h, 0eeh
    DB 050h
    DB 08dh, 04dh, 0ach
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 0a1h
    DD ?g_screenTintLevel@@3HA
    DB 02bh, 005h
    DD ?g_levelLoadState@@3PAHA + 18h
    DB 03dh, 068h, 001h, 000h, 000h
    DB 07eh, 01ch
    DB 08dh, 045h, 0ach
    DB 050h
    DB 08dh, 045h, 0c4h
    DB 050h
    DB 08bh, 0cbh
    call ?FindNearestOpponent@GameMan@@QAEPAU1@AAUVector3@@0@Z
    DB 085h, 0c0h
    DB 074h, 009h
    DB 089h, 045h, 07ch
    DB 089h, 083h, 000h, 007h, 000h, 000h
    DB 08bh, 08bh, 0fch, 006h, 000h, 000h
    DB 083h, 065h, 00ch, 000h
    DB 085h, 0c9h
    DB 07ch, 01eh
    DB 083h, 0f9h, 001h
    DB 07eh, 011h
    DB 083h, 0f9h, 002h
    DB 075h, 014h
    DB 0ffh, 075h, 07ch
    DB 08bh, 0cbh
    call ?ChooseAiInput@GameMan@@QAEIPAU1@@Z
    DB 0ebh, 005h
    call ?ReadGameManInputMask@@YIHH@Z
    DB 089h, 045h, 00ch
    DB 08bh, 035h
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 033h, 0c9h
    DB 041h
    DB 039h, 00dh
    DD ?g_gameMode@@3HA
    DB 074h, 01ah
    DB 08bh, 083h, 040h, 001h, 000h, 000h
    DB 085h, 0c0h
    DB 074h, 025h
    DB 083h, 0f8h, 003h
    DB 074h, 020h
    DB 083h, 0f8h, 005h
    DB 074h, 01bh
    DB 083h, 065h, 00ch, 008h
    DB 0ebh, 015h
    DB 083h, 0bbh, 0fch, 006h, 000h, 000h, 002h
    DB 075h, 00ch
    DB 03bh, 0f1h
    DB 074h, 008h
    call ?ReadGameManInputMask@@YIHH@Z
    DB 089h, 045h, 00ch
    DB 081h, 03dh
    DD ?g_levelLoadState@@3PAHA + 1ch
    DB 0c8h, 000h, 000h, 000h
    DB 07dh, 005h
    DB 083h, 0feh, 002h
    DB 074h, 020h
    DB 08bh, 045h, 07ch
    DB 085h, 0c0h
    DB 00fh, 084h, 0aah, 000h, 000h, 000h
    DB 083h, 0b8h, 0a4h, 000h, 000h, 000h, 003h
    DB 00fh, 085h, 09dh, 000h, 000h, 000h
    DB 085h, 0f6h
    DB 00fh, 085h, 095h, 000h, 000h, 000h
    DB 08bh, 04dh, 07ch
    DB 08dh, 045h, 0e4h
    DB 050h
    DB 08dh, 045h, 09ch
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    call ?CalculateCenterOfMassPosition@GameMan@@QAE?AUVector3@@XZ
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0a0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 038h
    DB 0d9h, 045h, 09ch
    DB 0d8h, 04dh, 09ch
    DB 0d9h, 045h, 0a4h
    DB 0d8h, 04dh, 0a4h
    DB 0deh, 0c1h
    DB 0d8h, 01dh
    DD __real@44c80000
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 01fh
    DB 08dh, 08bh, 024h, 001h, 000h, 000h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3e23d70b
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 007h
    DB 0c7h, 045h, 038h, 000h, 000h, 060h, 040h
    DB 0d9h, 045h, 038h
    DB 08dh, 045h, 028h
    DB 0d8h, 00dh
    DD __real@3d23d710
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 028h
    DB 050h
    DB 08dh, 04dh, 09ch
    call ?Normalized@Vector3@@QAE?AU1@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 08bh, 000h, 001h, 000h, 000h
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 0eeh
    DB 051h
    DB 0d9h, 05dh, 064h
    DB 051h
    DB 0d9h, 045h, 0e4h
    DB 0ddh, 01ch, 024h
    call _fabs
    DB 0d9h, 0c0h
    DB 0d9h, 005h
    DD ?g_gameDecorationHeight@@3MA
    DB 059h
    DB 0d8h, 025h
    DD ?g_gameCameraMinimumDistance@@3MB
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 028h
    DB 0d9h, 045h, 0e4h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _fabs
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 005h
    DD ?g_gameDecorationHeight@@3MA
    DB 0d8h, 005h
    DD ?g_gameWallSegmentSpacing@@3MB
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 041h
    DB 074h, 050h
    DB 0d9h, 045h, 0ech
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _fabs
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 005h
    DD ?g_gameDecorationHeight@@3MA
    DB 0d8h, 025h
    DD ?g_gameCameraMinimumDistance@@3MB
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 02fh
    DB 0d9h, 045h, 0ech
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _fabs
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 005h
    DD ?g_gameDecorationHeight@@3MA
    DB 0d8h, 005h
    DD ?g_gameWallSegmentSpacing@@3MB
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 041h
    DB 075h, 007h
    DB 0c7h, 045h, 064h, 000h, 000h, 0c0h, 03fh
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 002h
    DB 075h, 03bh
    DB 081h, 03dh
    DD ?g_levelLoadState@@3PAHA + 1ch
    DB 02ch, 001h, 000h, 000h
    DB 07eh, 02fh
    DB 08dh, 08bh, 024h, 001h, 000h, 000h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3f23d70b
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 017h
    DB 08bh, 083h, 0a4h, 000h, 000h, 000h
    DB 083h, 0f8h, 00ch
    DB 074h, 00ch
    DB 083h, 0f8h, 00dh
    DB 074h, 007h
    DB 0c7h, 045h, 064h, 09ah, 099h, 019h, 03fh
    DB 083h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 000h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 0e4h
    DB 08dh, 07dh, 02ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 030h
    DB 075h, 04ch
    DB 083h, 03dh
    DD ?g_selectedLevelScript@@3HA
    DB 000h
    DB 075h, 043h
    DB 08dh, 045h, 028h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 045h, 064h
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 02ch
    DB 0c7h, 045h, 028h, 010h, 0d7h, 023h, 03dh
    call ?Normalized@Vector3@@QAE?AU1@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 08bh, 000h, 001h, 000h, 000h
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 005h
    DD ?g_wavyTextTimeScale@@3MB
    DB 08dh, 083h, 07ch, 001h, 000h, 000h
    DB 0c7h, 045h, 024h, 0cdh, 0cch, 0cch, 03dh
    DB 033h, 0c9h
    DB 089h, 085h, 030h, 0ffh, 0ffh, 0ffh
    DB 083h, 0f9h, 008h
    DB 0d9h, 005h
    DD ?g_gameProjectileSpin@@3MB
    DB 07ch, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0c0h
    DB 0d9h, 018h
    DB 041h
    DB 083h, 0c0h, 034h
    DB 083h, 0f9h, 00eh
    DB 07ch, 0e6h
    DB 0d9h, 093h, 084h, 003h, 000h, 000h
    DB 0c7h, 045h, 058h, 0ach, 0c5h, 027h, 0b7h
    DB 0d9h, 09bh, 020h, 004h, 000h, 000h
    DB 08dh, 075h, 054h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 000h
    DB 0d9h, 05dh, 054h
    DB 08dh, 045h, 000h
    DB 0d9h, 0eeh
    DB 050h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 0a5h
    DB 0a5h
    DB 08dh, 04dh, 090h
    DB 0c7h, 083h, 0b0h, 001h, 000h, 000h, 0a6h, 09bh, 044h, 03bh
    DB 0a5h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 0f6h, 045h, 00ch, 004h
    DB 0d9h, 045h, 03ch
    DB 0d8h, 000h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 040h, 008h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f4h
    DB 074h, 023h
    DB 08dh, 045h, 028h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 045h, 028h, 073h, 012h, 003h, 03dh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 08bh, 000h, 001h, 000h, 000h
    call ??YVector3@@QAEXAAU0@@Z
    DB 0f6h, 045h, 00ch, 001h
    DB 0d9h, 0eeh
    DB 074h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@3d75c28f
    DB 0f6h, 045h, 00ch, 002h
    DB 074h, 006h
    DB 0d8h, 025h
    DD __real@3d75c28f
    DB 08bh, 0bbh, 0a4h, 000h, 000h, 000h
    DB 083h, 0ffh, 003h
    DB 08dh, 083h, 004h, 007h, 000h, 000h
    DB 0d8h, 020h
    DB 06ah, 005h
    DB 0c6h, 045h, 0fbh, 000h
    DB 0c6h, 045h, 053h, 000h
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 05eh
    DB 0d8h, 000h
    DB 0d9h, 010h
    DB 0d9h, 05dh, 028h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 044h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 050h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 0d9h, 095h, 020h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 09dh, 02ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 005h
    DD __real@3e4ccccd
    DB 0d9h, 095h, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 09dh, 040h, 0ffh, 0ffh, 0ffh
    DB 075h, 00dh
    DB 08dh, 083h, 040h, 001h, 000h, 000h
    DB 039h, 030h
    DB 07dh, 003h
    DB 083h, 020h, 000h
    DB 08bh, 083h, 040h, 001h, 000h, 000h
    DB 0d9h, 0eeh
    DB 083h, 0f8h, 008h
    DB 0d9h, 05dh, 0a8h
    DB 00fh, 087h, 0c9h, 005h, 000h, 000h
    DB 0ffh, 024h, 085h
    DD _GameManUpdateDispatchTable0
GameManUpdate_00411105 LABEL BYTE
    DB 083h, 065h, 00ch, 000h
    DB 08dh, 08bh, 024h, 001h, 000h, 000h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3eb851ec
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 08dh, 083h, 044h, 001h, 000h, 000h
    DB 07ah, 00fh
    DB 083h, 038h, 064h
    DB 07eh, 00dh
    DB 0c7h, 083h, 040h, 001h, 000h, 000h, 001h, 000h, 000h, 000h
    DB 083h, 020h, 000h
    DB 0ffh, 000h
    DB 0e9h, 087h, 005h, 000h, 000h
GameManUpdate_00411140 LABEL BYTE
    DB 08bh, 083h, 044h, 001h, 000h, 000h
    DB 083h, 065h, 00ch, 000h
    DB 083h, 0f8h, 03ch
    DB 089h, 045h, 01ch
    DB 0dbh, 045h, 01ch
    DB 0c6h, 045h, 053h, 001h
    DB 0d8h, 00dh
    DD __real@3c888889
    DB 0d9h, 05dh, 060h
    DB 07eh, 005h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 060h
    DB 083h, 0f8h, 046h
    DB 074h, 005h
    DB 083h, 0f8h, 004h
    DB 075h, 046h
    DB 08bh, 083h, 0f0h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 089h, 045h, 058h
    DB 0d9h, 05dh, 05ch
    DB 0c7h, 045h, 054h, 066h, 066h, 0a6h, 03fh
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 08dh, 045h, 000h
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04bh, 07ch
    DB 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3e23d70b
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 004h
    DB 0c6h, 045h, 0fbh, 001h
    DB 083h, 07dh, 01ch, 050h
    DB 075h, 01bh
    DB 083h, 0a3h, 044h, 001h, 000h, 000h, 000h
    DB 0c7h, 083h, 030h, 001h, 000h, 000h, 003h, 000h, 000h, 000h
    DB 0c7h, 083h, 040h, 001h, 000h, 000h, 002h, 000h, 000h, 000h
    DB 0d9h, 045h, 060h
    DB 08dh, 045h, 070h
    DB 0d8h, 04dh, 060h
    DB 050h
    DB 0d9h, 005h
    DD __real@40400000
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 0d8h, 0c9h
    DB 08dh, 04dh, 0c4h
    DB 0d9h, 0c1h
    DB 0d8h, 04dh, 060h
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0d8h, 00dh
    DD ?g_gameProjectileHalfSize@@3MB
    DB 0d9h, 05dh, 0f4h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 0d8h, 065h, 060h
    DB 0d8h, 04dh, 060h
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d9h, 05dh, 070h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 0e4h
    DB 083h, 0bbh, 0a4h, 000h, 000h, 000h, 000h
    DB 0d8h, 020h
    DB 0d9h, 05dh, 0e4h
    DB 0d9h, 045h, 0e8h
    DB 0d8h, 060h, 004h
    DB 0d9h, 05dh, 0e8h
    DB 0d9h, 045h, 0ech
    DB 0d8h, 060h, 008h
    DB 0d9h, 05dh, 0ech
    DB 00fh, 084h, 07ch, 004h, 000h, 000h
    DB 08bh, 083h, 044h, 001h, 000h, 000h
    DB 06ah, 05ah
    DB 059h
    DB 03bh, 0c1h
    DB 07eh, 00bh
    DB 089h, 08bh, 044h, 001h, 000h, 000h
    DB 0e9h, 06ah, 004h, 000h, 000h
    DB 085h, 0c0h
    DB 00fh, 08eh, 062h, 004h, 000h, 000h
    DB 048h
    DB 089h, 083h, 044h, 001h, 000h, 000h
    DB 0e9h, 056h, 004h, 000h, 000h
GameManUpdate_00411271 LABEL BYTE
    DB 08bh, 083h, 044h, 001h, 000h, 000h
    DB 083h, 0f8h, 05ah
    DB 089h, 045h, 01ch
    DB 0dbh, 045h, 01ch
    DB 0c6h, 045h, 053h, 001h
    DB 0d8h, 00dh
    DD __real@3c360b61
    DB 0d9h, 055h, 038h
    DB 07eh, 007h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 0d9h, 055h, 038h
    DB 0d9h, 0c0h
    DB 040h
    DB 0d8h, 0c9h
    DB 089h, 083h, 044h, 001h, 000h, 000h
    DB 0d9h, 005h
    DD __real@40400000
    DB 08dh, 045h, 070h
    DB 050h
    DB 0d8h, 0c9h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0c1h
    DB 050h
    DB 0d8h, 0cbh
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 045h, 0f4h, 000h, 000h, 0a0h, 03fh
    DB 0c7h, 045h, 070h, 096h, 043h, 08bh, 0bch
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0ddh, 0dah
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 024h
    DB 0d8h, 00dh
    DD ?g_wavyTextPhaseScale@@3MB
    DB 0d9h, 05dh, 0f0h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 03ch
    DB 0c7h, 045h, 054h, 0cdh, 0cch, 0cch, 0bdh
    DB 0d8h, 000h
    DB 08dh, 075h, 054h
    DB 08dh, 0bdh, 0a8h, 0feh, 0ffh, 0ffh
    DB 08dh, 08dh, 0a8h, 0feh, 0ffh, 0ffh
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 040h, 008h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0c7h, 045h, 054h, 0cdh, 0cch, 0cch, 03dh
    DB 0ddh, 0d8h
    DB 08dh, 075h, 054h
    DB 0d9h, 0eeh
    DB 08dh, 0bdh, 0cch, 0feh, 0ffh, 0ffh
    DB 0d9h, 05dh, 058h
    DB 08dh, 08dh, 0cch, 0feh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0f6h, 045h, 00ch, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 020h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 02ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 075h, 00ch
    DB 081h, 0bbh, 044h, 001h, 000h, 000h, 0bch, 002h, 000h, 000h
    DB 07eh, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 033h, 0f6h
    DB 046h
    DB 039h, 035h
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 075h, 018h
    DB 083h, 0a3h, 030h, 001h, 000h, 000h, 000h
    DB 083h, 0a3h, 044h, 001h, 000h, 000h, 000h
    DB 0c7h, 083h, 040h, 001h, 000h, 000h, 003h, 000h, 000h, 000h
    DB 08bh, 00dh
    DD ?g_screenTintLevel@@3HA
    DB 08bh, 053h, 02ch
    DB 08dh, 041h, 0ech
    DB 039h, 082h, 0d4h, 000h, 000h, 000h
    DB 07fh, 00bh
    DB 08bh, 053h, 038h
    DB 039h, 082h, 0d8h, 000h, 000h, 000h
    DB 07eh, 025h
    DB 08bh, 055h, 07ch
    DB 08bh, 07ah, 02ch
    DB 039h, 087h, 0d8h, 000h, 000h, 000h
    DB 07fh, 00bh
    DB 08bh, 052h, 038h
    DB 039h, 082h, 0d8h, 000h, 000h, 000h
    DB 07eh, 00ch
    DB 089h, 035h
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 089h, 00dh
    DD ?g_levelLoadState@@3PAHA + 18h
    DB 08dh, 083h, 048h, 001h, 000h, 000h
    DB 0d8h, 020h
    DB 083h, 065h, 00ch, 000h
    DB 0d8h, 00dh
    DD __real@3e23d70a
    DB 0d8h, 000h
    DB 0d9h, 010h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0ddh, 0d9h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0d8h, 00dh
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 0ddh, 0d9h
    DB 0d9h, 095h, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 09dh, 040h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 038h
    DB 0d8h, 00dh
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 0d9h, 095h, 044h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 09dh, 050h, 0ffh, 0ffh, 0ffh
    DB 0e9h, 08ch, 002h, 000h, 000h
GameManUpdate_0041143b LABEL BYTE
    DB 083h, 065h, 00ch, 0f7h
    DB 0d9h, 0eeh
    DB 08dh, 045h, 070h
    DB 0d9h, 05dh, 070h
    DB 050h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0c4h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 03ch
    DB 0d8h, 020h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 060h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 060h, 008h
    DB 08bh, 083h, 044h, 001h, 000h, 000h
    DB 083h, 0f8h, 041h
    DB 089h, 045h, 01ch
    DB 0d9h, 05dh, 044h
    DB 0dbh, 045h, 01ch
    DB 0d8h, 00dh
    DD __real@3c7c0fc1
    DB 07eh, 00bh
    DB 083h, 0a3h, 040h, 001h, 000h, 000h, 000h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 005h
    DD __real@40400000
    DB 0d8h, 0c9h
    DB 0d9h, 0c1h
    DB 0d8h, 0cbh
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0ddh, 0dah
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameProjectileHalfSize@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 0f4h
    DB 0d9h, 005h
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 024h
    DB 0d8h, 00dh
    DD ?g_wavyTextPhaseScale@@3MB
    DB 0d9h, 05dh, 0f0h
    DB 0e9h, 0f5h, 000h, 000h, 000h
GameManUpdate_004114d5 LABEL BYTE
    DB 08dh, 08bh, 024h, 001h, 000h, 000h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3eb851ec
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 004h
    DB 085h, 0ffh
    DB 074h, 007h
    DB 083h, 0a3h, 044h, 001h, 000h, 000h, 000h
    DB 083h, 0bbh, 044h, 001h, 000h, 000h, 064h
    DB 08bh, 045h, 07ch
    DB 07eh, 021h
    DB 08bh, 088h, 044h, 001h, 000h, 000h
    DB 083h, 0f9h, 064h
    DB 07fh, 00dh
    DB 083h, 0f9h, 0f6h
    DB 07dh, 011h
    DB 081h, 0f9h, 038h, 0ffh, 0ffh, 0ffh
    DB 07eh, 009h
    DB 083h, 0b8h, 040h, 001h, 000h, 000h, 007h
    DB 075h, 009h
    DB 083h, 0b8h, 040h, 001h, 000h, 000h, 006h
    DB 075h, 011h
    DB 083h, 0a3h, 044h, 001h, 000h, 000h, 000h
    DB 0c7h, 083h, 040h, 001h, 000h, 000h, 006h, 000h, 000h, 000h
    DB 081h, 0bbh, 044h, 001h, 000h, 000h, 0bch, 002h, 000h, 000h
    DB 00fh, 08eh, 072h, 001h, 000h, 000h
    DB 083h, 0a3h, 044h, 001h, 000h, 000h, 000h
    DB 0c7h, 083h, 040h, 001h, 000h, 000h, 007h, 000h, 000h, 000h
    DB 0e9h, 05ch, 001h, 000h, 000h
GameManUpdate_00411565 LABEL BYTE
    DB 0dbh, 083h, 044h, 001h, 000h, 000h
    DB 051h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3bea0ea1
    DB 0d8h, 00dh
    DD __real@40c90fdb
    DB 0ddh, 01ch, 024h
    call _cos
    DB 08bh, 083h, 044h, 001h, 000h, 000h
    DB 03dh, 08ch, 000h, 000h, 000h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d9h, 055h, 0f0h
    DB 0d9h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 09bh, 0d4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 05dh, 0e0h
    DB 07eh, 014h
    DB 083h, 0a3h, 040h, 001h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0d4h, 000h, 000h, 000h
    DB 040h
    DB 0e9h, 096h, 0fch, 0ffh, 0ffh
GameManUpdate_004115d0 LABEL BYTE
    DB 0dbh, 083h, 044h, 001h, 000h, 000h
    DB 051h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3bea0ea1
    DB 0d8h, 00dh
    DD __real@41490fdb
    DB 0ddh, 01ch, 024h
    call _sin
    DB 081h, 0bbh, 044h, 001h, 000h, 000h, 08ch, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameNegativeHalf@@3MB
    DB 059h
    DB 059h
    DB 0d9h, 055h, 0f0h
    DB 0d9h, 005h
    DD __real@3fe66666
    DB 0d8h, 0c9h
    DB 0d9h, 09bh, 0d4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 05dh, 0e0h
    DB 00fh, 08eh, 0a3h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 089h, 0b3h, 040h, 001h, 000h, 000h
    DB 0d9h, 05dh, 0f0h
    DB 0c7h, 083h, 044h, 001h, 000h, 000h, 00ch, 0feh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0d4h, 000h, 000h, 000h
    DB 0e9h, 081h, 000h, 000h, 000h
GameManUpdate_00411640 LABEL BYTE
    DB 0dbh, 083h, 044h, 001h, 000h, 000h
    DB 051h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3c5a740e
    DB 0d8h, 00dh
    DD __real@41c90fdb
    DB 0ddh, 01ch, 024h
    call _cos
    DB 083h, 0bbh, 044h, 001h, 000h, 000h, 04bh
    DB 0d8h, 025h
    DD ?g_gameOne@@3MB
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD __real@be19999a
    DB 0d9h, 055h, 0f4h
    DB 0d9h, 0c0h
    DB 0d9h, 0e0h
    DB 0d9h, 09bh, 0d4h, 000h, 000h, 000h
    DB 0d8h, 025h
    DD __real@3e19999a
    DB 0dch, 0c0h
    DB 0d9h, 05dh, 0e0h
    DB 07eh, 036h
    DB 089h, 0b3h, 040h, 001h, 000h, 000h
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 00bh
    DB 074h, 009h
    DB 083h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 000h
    DB 074h, 007h
    DB 083h, 0a3h, 040h, 001h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0c7h, 083h, 044h, 001h, 000h, 000h, 038h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 09bh, 0d4h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f4h
GameManUpdate_004116c1 LABEL BYTE
    DB 0ffh, 083h, 044h, 001h, 000h, 000h
    DB 08bh, 083h, 030h, 001h, 000h, 000h
    DB 033h, 0f6h
    DB 02bh, 0c6h
    DB 0c6h, 045h, 0d3h, 000h
    DB 00fh, 084h, 09eh, 001h, 000h, 000h
    DB 048h
    DB 00fh, 084h, 03ah, 002h, 000h, 000h
    DB 048h
    DB 00fh, 085h, 00bh, 004h, 000h, 000h
    DB 08bh, 083h, 038h, 001h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 089h, 045h, 064h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 083h, 01ch, 003h, 000h, 000h, 08fh, 0c2h, 075h, 03dh
    DB 0c7h, 083h, 050h, 003h, 000h, 000h, 08fh, 0c2h, 075h, 03dh
    DB 0c7h, 083h, 0b8h, 003h, 000h, 000h, 08fh, 0c2h, 075h, 03dh
    DB 0c7h, 083h, 0ech, 003h, 000h, 000h, 08fh, 0c2h, 075h, 03dh
    DB 0c7h, 045h, 070h, 033h, 033h, 033h, 0bfh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 0e4h
    DB 0d8h, 000h
    DB 0d9h, 05dh, 0e4h
    DB 0d9h, 045h, 0e8h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 0e8h
    DB 0d9h, 045h, 0ech
    DB 0d8h, 040h, 008h
    DB 08bh, 083h, 034h, 001h, 000h, 000h
    DB 083h, 0f8h, 014h
    DB 089h, 045h, 06ch
    DB 0d9h, 05dh, 0ech
    DB 0dbh, 045h, 06ch
    DB 0d8h, 00dh
    DD __real@3d4ccccd
    DB 07eh, 01ah
    DB 089h, 0b3h, 030h, 001h, 000h, 000h
    DB 089h, 0b3h, 034h, 001h, 000h, 000h
    DB 0c7h, 083h, 03ch, 001h, 000h, 000h, 00ah, 000h, 000h, 000h
    DB 0c6h, 045h, 0d3h, 001h
    DB 0d9h, 0c0h
    DB 08bh, 045h, 064h
    DB 0d8h, 0c9h
    DB 0c1h, 0e0h, 002h
    DB 0c7h, 045h, 058h, 000h, 000h, 000h, 0c0h
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 068h
    DB 08dh, 07dh, 000h
    DB 0d9h, 0e8h
    DB 0d8h, 0e1h
    DB 0d9h, 055h, 038h
    DB 0d8h, 0c9h
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0d8h, 045h, 0f0h
    DB 0d9h, 05dh, 0f0h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d8h, 005h
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 0d9h, 09ch, 005h, 044h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d8h, 065h, 068h
    DB 0d8h, 00dh
    DD __real@402ccccd
    DB 0d9h, 09ch, 005h, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 005h
    DD ?g_boxWaterSurfaceOffset@@3MB
    DB 0d9h, 09ch, 005h, 020h, 0ffh, 0ffh, 0ffh
    DB 08dh, 045h, 000h
    DB 0d9h, 0eeh
    DB 050h
    DB 0d9h, 05dh, 054h
    DB 08dh, 045h, 02ch
    DB 0d9h, 0eeh
    DB 050h
    DB 08bh, 045h, 07ch
    DB 0d9h, 05dh, 05ch
    DB 08bh, 048h, 008h
    DB 0a5h
    DB 0a5h
    DB 081h, 0c1h, 084h, 000h, 000h, 000h
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 081h, 0bbh, 03ch, 001h, 000h, 000h, 0c8h, 000h, 000h, 000h
    DB 08bh, 045h, 064h
    DB 08dh, 03ch, 040h
    DB 08dh, 0bch, 0bdh, 0f0h, 0feh, 0ffh, 0ffh
    DB 08dh, 075h, 02ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 07eh, 049h
    DB 0d9h, 045h, 038h
    DB 06ah, 003h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 058h
    DB 02bh, 045h, 064h
    DB 08dh, 075h, 02ch
    DB 0d8h, 005h
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 08dh, 03ch, 040h
    DB 08dh, 0bch, 0bdh, 0f0h, 0feh, 0ffh, 0ffh
    DB 0a5h
    DB 0d9h, 09ch, 085h, 044h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 068h
    DB 0a5h
    DB 0d8h, 00dh
    DD __real@402ccccd
    DB 0d9h, 09ch, 085h, 034h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0d9h, 005h
    DD ?g_boxWaterSurfaceOffset@@3MB
    DB 0d9h, 09ch, 085h, 020h, 0ffh, 0ffh, 0ffh
    DB 0ffh, 083h, 034h, 001h, 000h, 000h
    DB 0e9h, 094h, 000h, 000h, 000h
    DB 0f6h, 045h, 00ch, 010h
    DB 074h, 010h
    DB 089h, 0b3h, 034h, 001h, 000h, 000h
    DB 0c7h, 083h, 030h, 001h, 000h, 000h, 001h, 000h, 000h, 000h
    DB 0f6h, 045h, 00ch, 020h
    DB 00fh, 084h, 05bh, 002h, 000h, 000h
    DB 08bh, 04bh, 038h
    DB 0b8h, 084h, 000h, 000h, 000h
    DB 003h, 0c8h
    DB 051h
    DB 08dh, 08dh, 078h, 0ffh, 0ffh, 0ffh
    DB 051h
    DB 08bh, 04bh, 02ch
    DB 033h, 0f6h
    DB 003h, 0c8h
    DB 089h, 0b3h, 034h, 001h, 000h, 000h
    DB 0c7h, 083h, 030h, 001h, 000h, 000h, 002h, 000h, 000h, 000h
    DB 0c7h, 083h, 038h, 001h, 000h, 000h, 001h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 0c8h
    DB 0d8h, 048h, 004h
    DB 0d9h, 045h, 0cch
    DB 0d8h, 048h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0c4h
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 006h
    DB 089h, 0b3h, 038h, 001h, 000h, 000h
    DB 08dh, 083h, 03ch, 001h, 000h, 000h
    DB 039h, 030h
    DB 00fh, 08eh, 0edh, 001h, 000h, 000h
    DB 0c7h, 000h, 0e8h, 003h, 000h, 000h
    DB 080h, 07dh, 0d3h, 000h
    DB 00fh, 085h, 0b0h, 0fdh, 0ffh, 0ffh
    DB 0e9h, 0d8h, 001h, 000h, 000h
    DB 08bh, 04bh, 004h
    DB 0d9h, 005h
    DD __real@3e0f5c29
    DB 0b8h, 084h, 000h, 000h, 000h
    DB 0d9h, 093h, 01ch, 003h, 000h, 000h
    DB 003h, 0c8h
    DB 0d9h, 093h, 050h, 003h, 000h, 000h
    DB 051h
    DB 0d9h, 093h, 0b8h, 003h, 000h, 000h
    DB 08dh, 04dh, 02ch
    DB 0d9h, 09bh, 0ech, 003h, 000h, 000h
    DB 051h
    DB 08bh, 04dh, 07ch
    DB 08bh, 049h, 004h
    DB 003h, 0c8h
    DB 0c7h, 045h, 0a8h, 000h, 000h, 000h, 03fh
    DB 0c7h, 045h, 04ch, 066h, 066h, 0a6h, 0bfh
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0eeh
    DB 08dh, 04dh, 02ch
    DB 0d9h, 05dh, 030h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0a1h
    DD ?g_screenTintLevel@@3HA
    DB 08bh, 04bh, 038h
    DB 083h, 0c0h, 0f6h
    DB 039h, 081h, 0d4h, 000h, 000h, 000h
    DB 07eh, 007h
    DB 0c7h, 045h, 04ch, 000h, 000h, 000h, 0c0h
    DB 08bh, 04bh, 02ch
    DB 039h, 081h, 0d4h, 000h, 000h, 000h
    DB 07eh, 00ch
    DB 0d9h, 045h, 04ch
    DB 0d8h, 025h
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 0d9h, 05dh, 04ch
    DB 08dh, 045h, 04ch
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0c4h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 0e4h
    DB 0d8h, 000h
    DB 0d9h, 05dh, 0e4h
    DB 0d9h, 045h, 0e8h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 0e8h
    DB 0d9h, 045h, 0ech
    DB 0d8h, 040h, 008h
    DB 08bh, 083h, 034h, 001h, 000h, 000h
    DB 083h, 0f8h, 008h
    DB 08dh, 048h, 0f8h
    DB 0d9h, 05dh, 0ech
    DB 089h, 04dh, 070h
    DB 0dbh, 045h, 070h
    DB 0d8h, 00dh
    DD __real@3d088889
    DB 07dh, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 083h, 0f8h, 026h
    DB 07eh, 015h
    DB 083h, 0f8h, 02bh
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 07eh, 00ch
    DB 089h, 0b3h, 030h, 001h, 000h, 000h
    DB 089h, 0b3h, 034h, 001h, 000h, 000h
    DB 0d9h, 0c0h
    DB 08bh, 045h, 07ch
    DB 0d8h, 0c9h
    DB 08bh, 040h, 004h
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0d9h, 055h, 038h
    DB 005h, 084h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 083h, 065h, 04ch, 000h
    DB 089h, 045h, 068h
    DB 08dh, 085h, 0f0h, 0feh, 0ffh, 0ffh
    DB 0d8h, 045h, 0f0h
    DB 089h, 045h, 064h
    DB 0d9h, 05dh, 0f0h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d8h, 005h
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 0d9h, 05dh, 070h
    DB 0d9h, 0e8h
    DB 0d8h, 065h, 038h
    DB 0d9h, 005h
    DD __real@402ccccd
    DB 0c7h, 045h, 038h, 000h, 000h, 080h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 0d8h, 00dh
    DD ?g_gameCameraMinimumDistanceScale@@3MB
    DB 0d8h, 02dh
    DD ?g_gameTwo@@3MB
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 045h, 04ch
    DB 0d9h, 045h, 070h
    DB 0d9h, 09ch, 005h, 044h, 0ffh, 0ffh, 0ffh
    DB 08dh, 08bh, 024h, 001h, 000h, 000h
    DB 0d9h, 045h, 06ch
    DB 0d9h, 09ch, 005h, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 0d9h, 09ch, 005h, 020h, 0ffh, 0ffh, 0ffh
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 068h
    DB 050h
    DB 08dh, 045h, 084h
    DB 050h
    DB 08dh, 045h, 000h
    DB 050h
    DB 08dh, 085h, 060h, 0ffh, 0ffh, 0ffh
    DB 050h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 07dh, 064h
    DB 083h, 045h, 04ch, 00ch
    DB 083h, 045h, 064h, 024h
    DB 083h, 07dh, 04ch, 00ch
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 07eh, 091h
    DB 0ffh, 083h, 034h, 001h, 000h, 000h
    DB 0ffh, 08bh, 03ch, 001h, 000h, 000h
    DB 083h, 0bbh, 030h, 001h, 000h, 000h, 003h
    DB 00fh, 084h, 02eh, 001h, 000h, 000h
    DB 0d9h, 0e8h
    DB 0c7h, 045h, 054h, 000h, 000h, 060h, 040h
    DB 0d9h, 05dh, 05ch
    DB 0c7h, 045h, 058h, 09ah, 099h, 019h, 040h
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 073h, 004h
    DB 08dh, 07eh, 060h
    DB 057h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04dh, 000h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08eh, 084h, 000h, 000h, 000h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 0f0h, 0feh, 0ffh, 0ffh
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cfh
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 0a8h, 0feh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 085h, 0b0h, 0feh, 0ffh, 0ffh
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 008h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 0b0h, 0feh, 0ffh, 0ffh
    DB 08dh, 08dh, 0a8h, 0feh, 0ffh, 0ffh
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 0c7h, 045h, 054h, 000h, 000h, 060h, 0c0h
    DB 0d9h, 05dh, 05ch
    DB 0c7h, 045h, 058h, 09ah, 099h, 019h, 040h
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 073h, 004h
    DB 08dh, 07eh, 060h
    DB 057h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04dh, 000h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08eh, 084h, 000h, 000h, 000h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 014h, 0ffh, 0ffh, 0ffh
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cfh
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 0cch, 0feh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 085h, 0d4h, 0feh, 0ffh, 0ffh
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 008h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 0d4h, 0feh, 0ffh, 0ffh
    DB 08dh, 08dh, 0cch, 0feh, 0ffh, 0ffh
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 08dh, 0b3h, 000h, 001h, 000h, 000h
    DB 050h
    DB 08bh, 0ceh
    DB 0c7h, 045h, 070h, 0cdh, 0cch, 0cch, 03dh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 03ch
    DB 0d8h, 020h
    DB 08bh, 0cbh
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 060h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 060h, 008h
    DB 08dh, 045h, 09ch
    DB 050h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 005h
    DD __real@3f75c28f
    DB 0d9h, 006h
    DB 0d8h, 0c9h
    DB 0d9h, 01eh
    DB 0d9h, 046h, 004h
    DB 0d8h, 0c9h
    DB 0d9h, 05eh, 004h
    DB 0d9h, 046h, 008h
    DB 0d8h, 0c9h
    DB 0d9h, 05eh, 008h
    DB 0ddh, 0d8h
    call ?CalculateCenterOfMassPosition@GameMan@@QAE?AUVector3@@XZ
    DB 08dh, 045h, 09ch
    DB 068h, 000h, 000h, 0ffh, 000h
    DB 050h
    DB 0c7h, 045h, 0a0h, 000h, 000h, 0a0h, 040h
    call ?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z
    DB 0d9h, 0eeh
    DB 08bh, 083h, 0ech, 000h, 000h, 000h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 05ch, 0cdh, 0cch, 0cch, 0beh
    DB 0d9h, 05dh, 058h
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 0a5h
    DB 089h, 045h, 038h
    DB 0a5h
    DB 08bh, 073h, 04ch
    DB 08bh, 006h
    DB 059h
    DB 059h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04dh, 000h
    DB 089h, 075h, 06ch
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 00eh
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 081h, 0c1h, 084h, 000h, 000h, 000h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0f0h
    DB 0d9h, 0eeh
    DB 08dh, 0bdh, 008h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 054h
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0a5h
    DB 0a5h
    DB 0c7h, 045h, 05ch, 0cdh, 0cch, 0cch, 0beh
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 073h, 058h
    DB 08bh, 006h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 08dh, 04dh, 000h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 00eh
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 081h, 0c1h, 084h, 000h, 000h, 000h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0e8h
    DB 0d8h, 065h, 038h
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 014h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 070h
    DB 08dh, 07dh, 000h
    DB 0d9h, 0eeh
    DB 08dh, 045h, 070h
    DB 0d9h, 05dh, 054h
    DB 050h
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 055h, 058h
    DB 050h
    DB 0d9h, 005h
    DD ?g_wavyTextTimeScale@@3MB
    DB 08dh, 04dh, 000h
    DB 0d9h, 055h, 05ch
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0c1h
    DB 0d9h, 05dh, 058h
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 02ch
    DB 0d9h, 055h, 05ch
    DB 0a5h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0a5h
    DB 0a5h
    DB 08bh, 073h, 058h
    DB 08bh, 006h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 0d4h
    DB 050h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 00eh
    DB 050h
    DB 08dh, 045h, 084h
    DB 0beh, 084h, 000h, 000h, 000h
    DB 050h
    DB 003h, 0ceh
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 07dh, 06ch
    DB 050h
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 085h, 060h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 007h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 04dh, 02ch
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 00fh
    DB 050h
    DB 08dh, 085h, 048h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 003h, 0ceh
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 075h, 0b8h
    DB 08dh, 07dh, 09ch
    DB 0a5h
    DB 0a5h
    DB 08dh, 045h, 09ch
    DB 068h, 000h, 0ffh, 0ffh, 000h
    DB 0a5h
    DB 050h
    DB 0c7h, 045h, 0a0h, 000h, 000h, 0a0h, 040h
    call ?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z
    DB 08dh, 083h, 000h, 001h, 000h, 000h
    DB 0dbh, 083h, 09ch, 000h, 000h, 000h
    DB 059h
    DB 059h
    DB 0d8h, 025h
    DD ?g_randomHalf@@3MB
    DB 0dch, 0c0h
    DB 0d9h, 05dh, 060h
    DB 0d9h, 045h, 0c8h
    DB 0d8h, 048h, 004h
    DB 0d9h, 045h, 0cch
    DB 0d8h, 048h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0c4h
    DB 0d8h, 008h
    DB 08bh, 043h, 008h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD __real@3e19999a
    DB 0d8h, 06dh, 024h
    DB 0d9h, 05dh, 024h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 020h, 001h, 000h, 000h
    DB 0d9h, 045h, 0bch
    DB 0d8h, 005h
    DD __real@4114cccd
    DB 0d8h, 098h, 088h, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 006h, 001h, 000h, 000h
    DB 08bh, 083h, 0a4h, 000h, 000h, 000h
    DB 083h, 0f8h, 00ch
    DB 00fh, 084h, 0f7h, 000h, 000h, 000h
    DB 083h, 0f8h, 00dh
    DB 00fh, 084h, 0eeh, 000h, 000h, 000h
    DB 083h, 0f8h, 00eh
    DB 00fh, 084h, 0e5h, 000h, 000h, 000h
    DB 06ah, 003h
    DB 059h
    DB 03bh, 0c1h
    DB 00fh, 084h, 0dah, 000h, 000h, 000h
    DB 089h, 08bh, 0a4h, 000h, 000h, 000h
    DB 081h, 03dh
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DD ?g_gameMen@@3PAUGameMan@@A
    DB 00fh, 086h, 0c4h, 000h, 000h, 000h
    DB 0beh
    DD ?g_gameMen@@3PAUGameMan@@A + 8
    DB 033h, 0ffh
    DB 08dh, 046h, 0f8h
    DB 03bh, 0c3h
    DB 00fh, 084h, 09dh, 000h, 000h, 000h
    DB 08bh, 046h, 010h
    DB 0d9h, 080h, 088h, 000h, 000h, 000h
    DB 08bh, 056h, 004h
    DB 0d8h, 082h, 088h, 000h, 000h, 000h
    DB 08bh, 00eh
    DB 0d8h, 00dh
    DD ?g_randomHalf@@3MB
    DB 0d8h, 005h
    DD __real@40400000
    DB 0d8h, 099h, 088h, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07bh, 021h
    DB 039h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 074h, 068h
    DB 0d9h, 005h
    DD ?g_waterBaseHeight@@3MA
    DB 0d8h, 025h
    DD ?g_gameOne@@3MB
    DB 0d8h, 099h, 088h, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 04fh
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 002h
    DB 074h, 008h
    DB 039h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 074h, 03eh
    DB 08bh, 086h, 038h, 001h, 000h, 000h
    DB 083h, 0f8h, 005h
    DB 074h, 00dh
    DB 083h, 0f8h, 007h
    DB 074h, 008h
    DB 039h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 074h, 026h
    DB 08dh, 08eh, 01ch, 001h, 000h, 000h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3ffae147
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 00eh
    DB 0ffh, 075h, 020h
    DB 08dh, 046h, 0f8h
    DB 050h
    call ?SetGameManAudioState@@YAXPAUGameMan@@H@Z
    DB 059h
    DB 059h
    DB 081h, 0c6h, 030h, 007h, 000h, 000h
    DB 08dh, 046h, 0f8h
    DB 03bh, 005h
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 00fh, 082h, 043h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 005h
    DD ?g_waterBaseHeight@@3MA
    DB 08bh, 03bh
    DB 0d8h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 06ah, 00eh
    DB 05ah
    DB 0d8h, 09fh, 088h, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 006h
    DB 089h, 093h, 0a4h, 000h, 000h, 000h
    DB 08bh, 083h, 0a4h, 000h, 000h, 000h
    DB 03bh, 0c2h
    DB 00fh, 087h, 07eh, 020h, 000h, 000h
    DB 0ffh, 024h, 085h
    DD _GameManUpdateDispatchTable1
GameManUpdate_00411fd1 LABEL BYTE
    DB 0c7h, 083h, 0ech, 000h, 000h, 000h, 000h, 000h, 000h, 03fh
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 3
    DB 000h
    DB 074h, 008h
    DB 0d9h, 0e8h
    DB 0d9h, 09bh, 0ech, 000h, 000h, 000h
    DB 08bh, 083h, 0f0h, 000h, 000h, 000h
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 089h, 083h, 080h, 000h, 000h, 000h
    DB 089h, 083h, 08ch, 000h, 000h, 000h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 048h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 070h, 000h, 000h, 098h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 0cch, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 04dh, 0b8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 050h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08bh, 000h, 001h, 000h, 000h
    DB 0c7h, 045h, 070h, 000h, 000h, 040h, 040h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 010h
    DB 0d8h, 020h
    DB 0d9h, 05dh, 010h
    DB 0d9h, 040h, 004h
    DB 0d9h, 0e0h
    DB 0d9h, 045h, 018h
    DB 0d8h, 060h, 008h
    DB 0a1h
    DD ?g_screenTintLevel@@3HA
    DB 03dh, 0fah, 000h, 000h, 000h
    DB 0d9h, 05dh, 018h
    DB 07fh, 016h
    DB 083h, 03dh
    DD ?g_gameIsRunning@@3HA
    DB 000h
    DB 00fh, 084h, 08ah, 003h, 000h, 000h
    DB 083h, 0f8h, 064h
    DB 00fh, 08eh, 081h, 003h, 000h, 000h
    DB 08bh, 04bh, 00ch
    DB 083h, 0c0h, 0e2h
    DB 039h, 081h, 0d4h, 000h, 000h, 000h
    DB 07fh, 00fh
    DB 08bh, 04bh, 018h
    DB 039h, 081h, 0d4h, 000h, 000h, 000h
    DB 00fh, 08eh, 064h, 003h, 000h, 000h
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 002h
    DB 0d9h, 005h
    DD ?g_gameCameraInputDamping@@3MB
    DB 075h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 0d9h, 0c1h
    DB 0d8h, 0cah
    DB 0d9h, 045h, 010h
    DB 0d8h, 04dh, 010h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 018h
    DB 0d8h, 04dh, 018h
    DB 0deh, 0c1h
    DB 0d9h, 0c1h
    DB 0d8h, 0cah
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 005h
    DB 0ddh, 0d8h
    DB 00fh, 08ah, 02bh, 002h, 000h, 000h
    DB 080h, 07dh, 053h, 000h
    DB 00fh, 085h, 021h, 002h, 000h, 000h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 038h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 070h, 000h, 000h, 020h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 020h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 085h, 008h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0b8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 010h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 010h
    DB 0d8h, 04dh, 010h
    DB 0d9h, 045h, 018h
    DB 051h
    DB 0d8h, 04dh, 018h
    DB 051h
    DB 0deh, 0c1h
    DB 0d9h, 055h, 064h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 00dh
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 059h
    DB 059h
    DB 0d9h, 055h, 04ch
    DB 0d8h, 01dh
    DD ?g_boxWaterBuoyancyScale@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 007h
    DB 0c7h, 045h, 04ch, 033h, 033h, 0b3h, 03fh
    DB 0d9h, 045h, 064h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 008h, 000h, 000h, 000h
    call _sqrt
    DB 0d9h, 05dh, 070h
    DB 0d9h, 045h, 064h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d9h, 045h, 0ach
    DB 0d8h, 04dh, 010h
    DB 08dh, 085h, 0f0h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 020h
    DB 0d9h, 045h, 0b0h
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 0d9h, 05dh, 068h
    DB 0d9h, 045h, 0b4h
    DB 0d8h, 04dh, 018h
    DB 0d9h, 05dh, 064h
    DB 0d9h, 045h, 010h
    DB 0d8h, 04dh, 0c4h
    DB 0d9h, 045h, 018h
    DB 0d8h, 04dh, 0cch
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0c8h
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 0deh, 0c1h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 075h, 070h
    DB 0d9h, 0e0h
    DB 0deh, 0c9h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    DB 0d9h, 045h, 04ch
    DB 051h
    DB 0d8h, 0f1h
    DB 0d8h, 00dh
    DD __real@bf19999a
    DB 0d9h, 045h, 068h
    DB 0d8h, 045h, 064h
    DB 0d8h, 045h, 020h
    DB 0deh, 0c9h
    DB 0d9h, 01ch, 024h
    DB 050h
    DB 0ddh, 0d8h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 08bh, 0bch, 000h, 000h, 000h
    DB 08bh, 0f9h
    DB 08dh, 075h, 000h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 00dh
    DD ?g_gameCameraAimDamping@@3MB
    DB 059h
    DB 059h
    DB 0d8h, 005h
    DD ?g_randomHalf@@3MB
    DB 08dh, 073h, 07ch
    DB 056h
    DB 08dh, 085h, 0d8h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 09bh, 0a8h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 08bh, 088h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 040h, 008h
    DB 08dh, 08bh, 0bch, 000h, 000h, 000h
    DB 0d8h, 049h, 008h
    DB 0d9h, 040h, 004h
    DB 0d8h, 049h, 004h
    DB 0deh, 0c1h
    DB 0d9h, 001h
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0dbh, 083h, 09ch, 000h, 000h, 000h
    DB 0d8h, 025h
    DD ?g_randomHalf@@3MB
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 0d8h, 045h, 068h
    DB 0d8h, 045h, 064h
    DB 0d8h, 045h, 020h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 00ch
    DB 0c7h, 083h, 09ch, 000h, 000h, 000h, 001h, 000h, 000h, 000h
    DB 0ebh, 007h
    DB 083h, 0a3h, 09ch, 000h, 000h, 000h, 000h
    DB 08bh, 093h, 09ch, 000h, 000h, 000h
    DB 0d9h, 006h
    DB 085h, 0d2h
    DB 08dh, 08bh, 0bch, 000h, 000h, 000h
    DB 074h, 019h
    DB 0d8h, 021h
    DB 0d8h, 01dh
    DD __real@3e800000
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 023h
    DB 0d9h, 006h
    DB 0d8h, 025h
    DD __real@3e800000
    DB 0ebh, 017h
    DB 0d8h, 001h
    DB 0d8h, 01dh
    DD __real@3e800000
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 00ah
    DB 0d9h, 005h
    DD __real@3e800000
    DB 0d8h, 026h
    DB 0d9h, 019h
    DB 085h, 0d2h
    DB 0d9h, 006h
    DB 0d8h, 025h
    DD ?g_randomHalf@@3MB
    DB 0d8h, 00dh
    DD __real@3e4ccccd
    DB 0d8h, 025h
    DD __real@3e23d70a
    DB 074h, 004h
    DB 0d8h, 001h
    DB 0ebh, 002h
    DB 0d8h, 029h
    DB 0d9h, 019h
    DB 08bh, 083h, 0a0h, 000h, 000h, 000h
    DB 083h, 0f8h, 05ah
    DB 074h, 01fh
    DB 083h, 0f8h, 00ah
    DB 07eh, 010h
    DB 0d9h, 043h, 07ch
    DB 0d8h, 01dh
    DD __real@3e800000
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07bh, 00ah
    DB 080h, 07dh, 0fbh, 000h
    DB 00fh, 084h, 0d1h, 000h, 000h, 000h
    DB 08bh, 083h, 0f0h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 089h, 045h, 058h
    DB 0d9h, 05dh, 05ch
    DB 0c7h, 045h, 054h, 0cdh, 0cch, 08ch, 03fh
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0a5h
    DB 08dh, 043h, 07ch
    DB 0a5h
    DB 050h
    DB 08dh, 085h, 0c0h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 000h
    DB 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 08bh, 0bch, 000h, 000h, 000h
    DB 08bh, 0f0h
    DB 08bh, 0f9h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 01dh
    DD __real@3e23d70b
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 074h, 006h
    DB 080h, 07dh, 0fbh, 000h
    DB 074h, 07bh
    DB 083h, 0a3h, 09ch, 000h, 000h, 000h, 000h
    DB 08dh, 08bh, 0bch, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 008h, 000h, 000h, 000h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 059h
    DB 059h
    DB 0d8h, 005h
    DD ?g_randomHalf@@3MB
    DB 0d9h, 09bh, 0a8h, 000h, 000h, 000h
    DB 0d9h, 083h, 0c4h, 000h, 000h, 000h
    DB 0d8h, 01dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 02eh
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 08dh, 083h, 0bch, 000h, 000h, 000h
    DB 0c7h, 083h, 09ch, 000h, 000h, 000h, 001h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0d8h, 0c9h
    DB 0d9h, 018h
    DB 0d9h, 040h, 004h
    DB 0d8h, 0c9h
    DB 0d9h, 058h, 004h
    DB 0d9h, 040h, 008h
    DB 0d8h, 0c9h
    DB 0d9h, 058h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 0a8h
    DB 0e9h, 02bh, 01ch, 000h, 000h
GameManUpdate_0041241d LABEL BYTE
    DB 0dbh, 083h, 09ch, 000h, 000h, 000h
    DB 0d8h, 093h, 0ech, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 012h
    DB 0d9h, 083h, 0ech, 000h, 000h, 000h
    DB 0d8h, 005h
    DD __real@3c23d70a
    DB 0d9h, 09bh, 0ech, 000h, 000h, 000h
    DB 0d8h, 09bh, 0ech, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 012h
    DB 0d9h, 083h, 0ech, 000h, 000h, 000h
    DB 0d8h, 025h
    DD __real@3c23d70a
    DB 0d9h, 09bh, 0ech, 000h, 000h, 000h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 0a8h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 070h, 000h, 000h, 0f0h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 090h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 04dh, 0b8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0eeh
    DB 0ffh, 08bh, 0a0h, 000h, 000h, 000h
    DB 0d9h, 05dh, 014h
    DB 0d9h, 083h, 0ech, 000h, 000h, 000h
    DB 08bh, 0b3h, 0a0h, 000h, 000h, 000h
    DB 0d8h, 01dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07bh, 013h
    DB 0d9h, 083h, 0ech, 000h, 000h, 000h
    DB 0d8h, 01dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 053h
    DB 0d9h, 045h, 010h
    DB 0d8h, 04dh, 010h
    DB 0d9h, 045h, 018h
    DB 0d8h, 04dh, 018h
    DB 0deh, 0c1h
    DB 0d8h, 01dh
    DD __real@3fd851ea
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07bh, 023h
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 085h, 078h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04fh, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 0d9h, 040h, 008h
    DB 0d8h, 01dh
    DD __real@be4ccccd
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 00eh
    DB 085h, 0f6h
    DB 07fh, 011h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 001h, 000h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 08bh, 003h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 0c7h, 045h, 05ch, 00ah, 0d7h, 023h, 03ch
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 058h
    DB 08dh, 07dh, 000h
    DB 083h, 0c0h, 060h
    DB 0a5h
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 04dh, 000h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08dh, 045h, 070h
    DB 050h
    DB 0d9h, 0eeh
    DB 08dh, 085h, 060h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 030h
    DB 050h
    DB 08dh, 0b3h, 0ach, 000h, 000h, 000h
    DB 056h
    DB 08dh, 085h, 048h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 02ch
    DB 0c7h, 045h, 070h, 08fh, 0c2h, 075h, 03dh
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 0ceh
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 045h, 03ch
    DB 0d8h, 026h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 066h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 066h, 008h
    DB 0d9h, 05dh, 044h
    DB 0e9h, 09fh, 01ah, 000h, 000h
GameManUpdate_004125a9 LABEL BYTE
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3dbd3c19
    DB 0d9h, 055h, 06ch
    DB 0d8h, 01dh
    DD ?g_parserPi@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 018h
    DB 083h, 0b3h, 09ch, 000h, 000h, 000h, 001h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 002h, 000h, 000h, 000h
    DB 083h, 0bbh, 09ch, 000h, 000h, 000h, 000h
    DB 075h, 010h
    DB 0d9h, 0e8h
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3c909091
    DB 0ebh, 018h
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3c909091
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 08bh, 003h
    DB 0d9h, 09bh, 0ech, 000h, 000h, 000h
    DB 0d9h, 005h
    DD __real@3cf5c28f
    DB 08dh, 075h, 054h
    DB 0d9h, 0c1h
    DB 08dh, 07dh, 000h
    DB 0d8h, 0c9h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 02ch
    DB 0d9h, 05dh, 054h
    DB 050h
    DB 0d9h, 0eeh
    DB 08dh, 04dh, 000h
    DB 0d9h, 05dh, 058h
    DB 0d9h, 055h, 05ch
    DB 0a5h
    DB 0ddh, 0d8h
    DB 0a5h
    DB 0ddh, 0d8h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08dh, 045h, 070h
    DB 050h
    DB 0d9h, 0eeh
    DB 08dh, 085h, 030h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 030h
    DB 050h
    DB 08dh, 0b3h, 0ach, 000h, 000h, 000h
    DB 056h
    DB 08dh, 085h, 018h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 02ch
    DB 0c7h, 045h, 070h, 08fh, 0c2h, 075h, 03dh
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 0ceh
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 045h, 03ch
    DB 0d8h, 026h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0c0h, 00bh
    DB 08dh, 004h, 040h
    DB 0d9h, 05dh, 03ch
    DB 08dh, 004h, 083h
    DB 0d9h, 045h, 040h
    DB 051h
    DB 0d8h, 066h, 004h
    DB 051h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 066h, 008h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 000h
    DB 0d8h, 005h
    DD __real@3d70f0f1
    DB 0d9h, 018h
    DB 0d9h, 045h, 06ch
    DB 0dch, 0c0h
    DB 0d9h, 055h, 068h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 08dh, 004h, 040h
    DB 0d8h, 00dh
    DD ?g_wavyTextPhaseScale@@3MB
    DB 0d8h, 025h
    DD __real@41080000
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 0d9h, 045h, 068h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d8h, 02dh
    DD __real@c1080000
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0f0h, 001h
    DB 08dh, 004h, 040h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0f0h, 001h
    DB 083h, 0c0h, 00bh
    DB 08dh, 004h, 040h
    DB 08dh, 004h, 083h
    DB 0d9h, 000h
    DB 0d8h, 025h
    DD __real@3d70f0f1
    DB 0d9h, 018h
    DB 0e9h, 004h, 019h, 000h, 000h
GameManUpdate_0041273e LABEL BYTE
    DB 0d9h, 0eeh
    DB 08dh, 083h, 070h, 001h, 000h, 000h
    DB 0d9h, 05dh, 054h
    DB 08bh, 0cah
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 090h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 094h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 098h
    DB 08dh, 078h, 0f4h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 058h, 00ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 0f8h
    DB 08dh, 075h, 090h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c0h, 034h
    DB 049h
    DB 0a5h
    DB 075h, 0e4h
    DB 081h, 0bbh, 0a0h, 000h, 000h, 000h, 040h, 01fh, 000h, 000h
    DB 07dh, 014h
    DB 08bh, 0cbh
    call ?CalculateKineticEnergy@GameMan@@QAEMXZ
    DB 0d8h, 01dh
    DD ?g_gameTwo@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 011h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 00ch, 000h, 000h, 000h
    DB 0a1h
    DD ?g_screenTintLevel@@3HA
    DB 08bh, 04bh, 004h
    DB 083h, 0c0h, 09ch
    DB 039h, 081h, 0d8h, 000h, 000h, 000h
    DB 00fh, 08dh, 0abh, 000h, 000h, 000h
    DB 08bh, 04bh, 008h
    DB 039h, 081h, 0d8h, 000h, 000h, 000h
    DB 00fh, 08dh, 09ch, 000h, 000h, 000h
    DB 0d9h, 045h, 0bch
    DB 08dh, 083h, 050h, 003h, 000h, 000h
    DB 0d8h, 005h
    DD __real@40400000
    DB 089h, 045h, 07ch
    DB 08dh, 043h, 02ch
    DB 089h, 045h, 0e0h
    DB 0d9h, 05dh, 028h
    DB 0c7h, 045h, 038h, 002h, 000h, 000h, 000h
    DB 08bh, 045h, 0e0h
    DB 08bh, 000h
    DB 0d9h, 080h, 088h, 000h, 000h, 000h
    DB 0d8h, 05dh, 028h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 055h
    DB 08bh, 045h, 07ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 08dh, 075h, 054h
    DB 0d9h, 0e8h
    DB 08dh, 07dh, 000h
    DB 0d9h, 05dh, 058h
    DB 0c7h, 040h, 0cch, 00ah, 0d7h, 023h, 03ch
    DB 0d9h, 0eeh
    DB 0c7h, 000h, 00ah, 0d7h, 023h, 03ch
    DB 08bh, 04bh, 004h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 045h, 000h
    DB 050h
    DB 0a5h
    DB 0a5h
    DB 08dh, 085h, 024h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 083h, 0c1h, 060h
    DB 0a5h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 04dh, 07ch
    DB 08dh, 079h, 0b4h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 0b1h, 0c0h, 002h, 000h, 000h
    DB 08dh, 079h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 045h, 0e0h, 00ch
    DB 081h, 045h, 07ch, 09ch, 000h, 000h, 000h
    DB 0ffh, 04dh, 038h
    DB 075h, 086h
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 0e9h, 0d1h, 025h, 000h, 000h
GameManUpdate_0041287e LABEL BYTE
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 08bh, 083h, 0a0h, 000h, 000h, 000h
    DB 089h, 045h, 064h
    DB 0dbh, 045h, 064h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d9h, 055h, 0f4h
    DB 0d8h, 01dh
    DD ?g_gameProjectileHalfSize@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 000h, 001h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 005h, 000h, 000h, 000h
    DB 0e9h, 0eah, 000h, 000h, 000h
GameManUpdate_004128c0 LABEL BYTE
    DB 0d9h, 045h, 060h
    DB 08bh, 003h
    DB 0d8h, 00dh
    DD __real@3e4ccccd
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 0d9h, 05dh, 054h
    DB 083h, 0c0h, 060h
    DB 0d9h, 0eeh
    DB 050h
    DB 0d9h, 05dh, 058h
    DB 08dh, 045h, 02ch
    DB 0d9h, 0eeh
    DB 050h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 04dh, 000h
    DB 0c7h, 045h, 0f4h, 09ah, 099h, 099h, 03fh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 083h, 0bbh, 0a0h, 000h, 000h, 000h, 00ah
    DB 0d9h, 045h, 03ch
    DB 08bh, 045h, 040h
    DB 0d8h, 065h, 02ch
    DB 089h, 045h, 040h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 044h
    DB 0d8h, 065h, 034h
    DB 0d9h, 05dh, 044h
    DB 00fh, 08eh, 025h, 017h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 006h, 000h, 000h, 000h
    DB 0e9h, 00fh, 017h, 000h, 000h
GameManUpdate_00412939 LABEL BYTE
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 08bh, 083h, 0a0h, 000h, 000h, 000h
    DB 089h, 045h, 064h
    DB 0dbh, 045h, 064h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d8h, 00dh
    DD __real@3ca6223e
    DB 0d8h, 02dh
    DD ?g_gameProjectileHalfSize@@3MB
    DB 0d9h, 05dh, 0f4h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@c1000000
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 0d9h, 045h, 0f4h
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 024h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d9h, 005h
    DD __real@c10b3333
    DB 083h, 0a3h, 0a4h, 000h, 000h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 0d9h, 045h, 060h
    DB 08bh, 003h
    DB 0d8h, 00dh
    DD __real@3e4ccccd
    DB 08dh, 075h, 054h
    DB 08dh, 07dh, 000h
    DB 083h, 0c0h, 060h
    DB 0d9h, 05dh, 054h
    DB 050h
    DB 0d9h, 0eeh
    DB 08dh, 045h, 02ch
    DB 0d9h, 05dh, 058h
    DB 050h
    DB 0d9h, 0eeh
    DB 08dh, 04dh, 000h
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 045h, 040h
    DB 0d9h, 045h, 03ch
    DB 089h, 045h, 040h
    DB 0d8h, 065h, 02ch
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 044h
    DB 0d8h, 065h, 034h
    DB 0e9h, 0ach, 0fbh, 0ffh, 0ffh
GameManUpdate_004129f5 LABEL BYTE
    DB 08bh, 083h, 0a0h, 000h, 000h, 000h
    DB 083h, 0f8h, 078h
    DB 07dh, 009h
    DB 040h
    DB 089h, 083h, 0a0h, 000h, 000h, 000h
    DB 0ebh, 007h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 08bh, 003h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0c7h, 045h, 054h, 0cdh, 0cch, 04ch, 03dh
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 07dh, 000h
    DB 083h, 0c0h, 060h
    DB 0a5h
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 04dh, 000h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 045h, 040h
    DB 08bh, 08bh, 09ch, 000h, 000h, 000h
    DB 0d9h, 045h, 03ch
    DB 0d8h, 065h, 02ch
    DB 089h, 045h, 040h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 024h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 044h
    DB 050h
    DB 0d8h, 065h, 034h
    DB 08bh, 0c1h
    DB 083h, 0f0h, 001h
    DB 08dh, 004h, 040h
    DB 08dh, 084h, 085h, 008h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 044h
    DB 050h
    DB 08dh, 085h, 00ch, 0feh, 0ffh, 0ffh
    DB 08dh, 00ch, 049h
    DB 050h
    DB 08dh, 08ch, 08dh, 008h, 0ffh, 0ffh, 0ffh
    DB 0c7h, 045h, 070h, 000h, 000h, 000h, 03fh
    DB 0c7h, 045h, 06ch, 000h, 000h, 020h, 042h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 08ch, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 0f4h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 051h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3cd67750
    DB 0ddh, 01ch, 024h
    call _sin
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d8h, 025h
    DD __real@410b3333
    DB 059h
    DB 08dh, 004h, 040h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 059h
    DB 0e9h, 052h, 015h, 000h, 000h
GameManUpdate_00412af6 LABEL BYTE
    DB 0d9h, 005h
    DD __real@3d4ccccd
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 0d8h, 0c9h
    DB 0d8h, 0abh, 0f0h, 000h, 000h, 000h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 083h, 0bbh, 0a0h, 000h, 000h, 000h, 006h
    DB 07ch, 011h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 009h, 000h, 000h, 000h
    DB 08dh, 045h, 070h
    DB 0d9h, 0eeh
    DB 050h
    DB 0d9h, 05dh, 070h
    DB 08dh, 085h, 03ch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 0d9h, 05dh, 06ch
    DB 050h
    DB 08dh, 085h, 0dch, 0fdh, 0ffh, 0ffh
    DB 08dh, 0b3h, 0bch, 000h, 000h, 000h
    DB 050h
    DB 08bh, 0ceh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 08dh, 04ch, 083h, 07ch
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 0eeh
    DB 08dh, 045h, 070h
    DB 0d9h, 05dh, 070h
    DB 050h
    DB 08dh, 085h, 074h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 0c4h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0ceh
    DB 0c7h, 045h, 06ch, 0cdh, 0cch, 04ch, 03dh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0f0h, 001h
    DB 08dh, 004h, 040h
    DB 08dh, 04ch, 083h, 07ch
    call ?SubtractOffset@GameBoxPoint@@QAEXAAUVector3@@@Z
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 06ch, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 0d8h, 00dh
    DD __real@3d4ccccc
    DB 08dh, 0b3h, 0c4h, 000h, 000h, 000h
    DB 056h
    DB 08dh, 085h, 0ach, 0fdh, 0ffh, 0ffh
    DB 0d9h, 05dh, 070h
    DB 050h
    DB 08dh, 04dh, 0c4h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 0b8h
    DB 0d8h, 020h
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 045h, 070h, 0cdh, 0cch, 0cch, 0bch
    DB 0d9h, 05dh, 0b8h
    DB 0d9h, 045h, 0bch
    DB 0d8h, 060h, 004h
    DB 0d9h, 05dh, 0bch
    DB 0d9h, 045h, 0c0h
    DB 0d8h, 060h, 008h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 05ch, 0fch, 0ffh, 0ffh
    DB 050h
    DB 0d9h, 05dh, 0c0h
    DB 056h
    DB 08dh, 085h, 094h, 0fdh, 0ffh, 0ffh
    DB 050h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 03ch
    DB 083h, 03dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 001h
    DB 0d8h, 000h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 040h, 008h
    DB 0d9h, 05dh, 044h
    DB 00fh, 085h, 0e2h, 013h, 000h, 000h
    DB 0e9h, 0a8h, 0f7h, 0ffh, 0ffh
GameManUpdate_00412c6b LABEL BYTE
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 051h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3d4ccccd
    DB 0d9h, 0e8h
    DB 0d8h, 0e1h
    DB 0d8h, 0c9h
    DB 0d8h, 00dh
    DD __real@40c00000
    DB 0d9h, 05dh, 068h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 005h
    DD __real@40400000
    DB 0d8h, 0c9h
    DB 0d9h, 0c1h
    DB 0d8h, 0cbh
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0d9h, 05dh, 04ch
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 00dh
    DD ?g_parserPi@@3MB
    DB 0d9h, 055h, 064h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d8h, 08bh, 0a8h, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 0d8h, 083h, 0f0h, 000h, 000h, 000h
    DB 0d8h, 025h
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d9h, 045h, 064h
    DB 0d8h, 00dh
    DD __real@3dc391d1
    DB 0deh, 0c1h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 0d9h, 045h, 064h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d8h, 08bh, 0a8h, 000h, 000h, 000h
    DB 059h
    DB 033h, 0ffh
    DB 0d8h, 00dh
    DD __real@3e4ccccd
    DB 059h
    DB 047h
    DB 033h, 0c7h
    DB 0d8h, 0abh, 0f0h, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 08dh, 0b3h, 0bch, 000h, 000h, 000h
    DB 08bh, 0ceh
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 08dh, 045h, 068h
    DB 050h
    DB 0d9h, 0e8h
    DB 08dh, 085h, 0b4h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 070h
    DB 050h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 07ch, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 044h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 0c7h, 045h, 06ch, 0cdh, 0cch, 04ch, 03dh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 08dh, 04ch, 083h, 07ch
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 070h
    DB 0c7h, 045h, 06ch, 0cdh, 0cch, 04ch, 03dh
    DB 08dh, 045h, 068h
    DB 050h
    DB 08dh, 085h, 064h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 03ch, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 04ch, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0ceh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 033h, 0c7h
    DB 08dh, 004h, 040h
    DB 08dh, 04ch, 083h, 07ch
    call ?SubtractOffset@GameBoxPoint@@QAEXAAUVector3@@@Z
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 083h, 0bbh, 0a0h, 000h, 000h, 000h, 014h
    DB 07ch, 042h
    DB 031h, 0bbh, 09ch, 000h, 000h, 000h
    DB 0d9h, 083h, 0f0h, 000h, 000h, 000h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0a3h, 0a4h, 000h, 000h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d9h, 083h, 0f0h, 000h, 000h, 000h
    DB 033h, 0c7h
    DB 08dh, 004h, 040h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 02ch, 0fch, 0ffh, 0ffh
    DB 0d8h, 005h
    DD __real@40c00000
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 0d8h, 00dh
    DD __real@3d1d89d9
    DB 08dh, 085h, 034h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 0d8h, 065h, 04ch
    DB 08dh, 0b3h, 0c4h, 000h, 000h, 000h
    DB 056h
    DB 08dh, 085h, 09ch, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 06ch
    DB 050h
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 045h, 070h, 066h, 066h, 0a6h, 03fh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 0b8h
    DB 0d8h, 020h
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 045h, 070h, 0cdh, 0cch, 0cch, 0bch
    DB 0d9h, 05dh, 0b8h
    DB 0d9h, 045h, 0bch
    DB 0d8h, 060h, 004h
    DB 0d9h, 05dh, 0bch
    DB 0d9h, 045h, 0c0h
    DB 0d8h, 060h, 008h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 01ch, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 0d9h, 05dh, 0c0h
    DB 056h
    DB 08dh, 085h, 014h, 0fch, 0ffh, 0ffh
    DB 050h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 03ch
    DB 0d8h, 000h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 040h, 008h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 0eeh
    DB 0e9h, 03dh, 0f5h, 0ffh, 0ffh
GameManUpdate_00412ed8 LABEL BYTE
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 051h
    DB 051h
    DB 0c7h, 083h, 0ech, 000h, 000h, 000h, 000h, 000h, 000h, 03fh
    DB 0d8h, 00dh
    DD __real@3d088889
    DB 0d9h, 05dh, 064h
    DB 0d9h, 045h, 064h
    DB 0d8h, 00dh
    DD ?g_parserPi@@3MB
    DB 0d9h, 055h, 068h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0dch, 0c0h
    DB 08dh, 004h, 040h
    DB 0c7h, 045h, 070h, 0cdh, 0cch, 04ch, 0bdh
    DB 0d8h, 083h, 0f0h, 000h, 000h, 000h
    DB 0d8h, 045h, 064h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d9h, 005h
    DD __real@3de147ae
    DB 08dh, 004h, 040h
    DB 08dh, 044h, 083h, 07ch
    DB 0d9h, 000h
    DB 0d8h, 0c1h
    DB 0d9h, 018h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0f0h, 001h
    DB 08dh, 004h, 040h
    DB 08dh, 044h, 083h, 07ch
    DB 0d9h, 000h
    DB 0d8h, 0e1h
    DB 0d9h, 018h
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 068h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 059h
    DB 059h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 004h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 054h, 0fbh, 0ffh, 0ffh
    DB 0d9h, 05dh, 06ch
    DB 050h
    DB 08dh, 04dh, 0ach
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 045h, 03ch
    DB 0d8h, 000h
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 040h
    DB 0d9h, 045h, 044h
    DB 0d8h, 040h, 008h
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 045h, 064h
    DB 0d8h, 01dh
    DD ?g_gameOne@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 085h, 010h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 00bh, 000h, 000h, 000h
    DB 0e9h, 06fh, 010h, 000h, 000h
GameManUpdate_00412fd9 LABEL BYTE
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 08dh, 004h, 040h
    DB 0c7h, 083h, 0ech, 000h, 000h, 000h, 000h, 000h, 000h, 03fh
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0d9h, 0e8h
    DB 0d8h, 0e1h
    DB 0d8h, 083h, 0f0h, 000h, 000h, 000h
    DB 0d9h, 09ch, 083h, 080h, 000h, 000h, 000h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 0d9h, 005h
    DD __real@3ea8f5c2
    DB 08dh, 004h, 040h
    DB 08dh, 044h, 083h, 07ch
    DB 0d9h, 000h
    DB 0d8h, 0e1h
    DB 0d9h, 018h
    DB 08bh, 083h, 09ch, 000h, 000h, 000h
    DB 083h, 0f0h, 001h
    DB 08dh, 004h, 040h
    DB 08dh, 044h, 083h, 07ch
    DB 0d9h, 000h
    DB 0d8h, 0c1h
    DB 0d9h, 018h
    DB 0ddh, 0d8h
    DB 0d8h, 01dh
    DD ?g_gameOne@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 0f7h, 00fh, 000h, 000h
    DB 083h, 0a3h, 0a4h, 000h, 000h, 000h, 000h
    DB 0e9h, 0ebh, 00fh, 000h, 000h
GameManUpdate_00413057 LABEL BYTE
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 054h
    DB 08dh, 0bbh, 000h, 001h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 0a5h
    DB 0a5h
    DB 0d8h, 00dh
    DD __real@3983126f
    DB 0a5h
    DB 0d8h, 015h
    DD __real@3d4ccccd
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@3d4ccccd
    DB 06ah, 00eh
    DB 08dh, 083h, 04ch, 001h, 000h, 000h
    DB 05ah
    DB 06ah, 00dh
    DB 08dh, 0b0h, 0d8h, 002h, 000h, 000h
    DB 08bh, 0f8h
    DB 059h
    DB 0f3h, 0a5h
    DB 0d9h, 050h, 030h
    DB 083h, 0c0h, 034h
    DB 04ah
    DB 075h, 0eah
    DB 08bh, 08bh, 0a0h, 000h, 000h, 000h
    DB 0ddh, 0d8h
    DB 089h, 04dh, 060h
    DB 0dbh, 045h, 060h
    DB 0d8h, 00dh
    DD __real@3c9374bc
    DB 0d8h, 025h
    DD ?g_randomHalf@@3MB
    DB 0d8h, 015h
    DD ?g_vectorZero@@3MB
    DB 0d9h, 055h, 01ch
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 007h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 055h, 01ch
    DB 0d8h, 01dh
    DD ?g_gameTwo@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 007h
    DB 0c7h, 045h, 01ch, 000h, 000h, 000h, 040h
    DB 083h, 0f9h, 064h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 064h
    DB 0c6h, 045h, 053h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 070h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 020h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 04ch
    DB 075h, 05dh
    DB 08bh, 003h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 08dh, 075h, 054h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 000h
    DB 0d9h, 05dh, 058h
    DB 083h, 0c0h, 060h
    DB 0d9h, 0e8h
    DB 050h
    DB 08dh, 085h, 0ech, 0fch, 0ffh, 0ffh
    DB 0d9h, 05dh, 05ch
    DB 050h
    DB 08dh, 04dh, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 0d9h, 040h, 004h
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 020h
    DB 083h, 0b3h, 018h, 001h, 000h, 000h, 001h
    DB 0d9h, 0eeh
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0d9h, 09bh, 010h, 001h, 000h, 000h
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 00dh, 000h, 000h, 000h
    DB 08bh, 083h, 0a0h, 000h, 000h, 000h
    DB 083h, 0f8h, 064h
    DB 089h, 045h, 060h
    DB 00fh, 08eh, 0cfh, 006h, 000h, 000h
    DB 0d9h, 0e8h
    DB 08bh, 003h
    DB 0d9h, 05dh, 054h
    DB 08dh, 075h, 054h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 02ch
    DB 0d9h, 05dh, 058h
    DB 08dh, 04dh, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 08dh, 075h, 054h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 000h
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 070h, 060h
    DB 056h
    DB 08dh, 085h, 0fch, 0fbh, 0ffh, 0ffh
    DB 050h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0f8h
    DB 056h
    DB 08dh, 085h, 0d4h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 02ch
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 0d9h, 047h, 004h
    DB 0d8h, 048h, 004h
    DB 0d8h, 01dh
    DD __real@3e800000
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 00dh
    DB 081h, 07dh, 060h, 02ch, 001h, 000h, 000h
    DB 07eh, 004h
    DB 0c6h, 045h, 053h, 001h
    DB 0dbh, 045h, 060h
    DB 0d9h, 005h
    DD ?g_gameLevelArenaExtent@@3MB
    DB 0d8h, 0e9h
    DB 0d8h, 00dh
    DD __real@3c23d70a
    DB 0d8h, 015h
    DD ?g_gameOne@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 081h, 07dh, 060h, 0aah, 000h, 000h, 000h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 005h
    DD __real@40400000
    DB 0d8h, 0c9h
    DB 0d9h, 0c1h
    DB 0d8h, 0cbh
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0ddh, 0dah
    DB 0ddh, 0d8h
    DB 0d8h, 00dh
    DD ?g_gameWallCenterSegment@@3MB
    DB 0d9h, 055h, 04ch
    DB 0d9h, 05dh, 020h
    DB 00fh, 08eh, 055h, 005h, 000h, 000h
    DB 0d9h, 005h
    DD __real@432a0000
    DB 0d8h, 0e9h
    DB 0d8h, 00dh
    DD __real@3bda740e
    DB 0d8h, 015h
    DD ?g_gameOne@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 081h, 07dh, 060h, 02ch, 001h, 000h, 000h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 005h
    DD __real@40400000
    DB 0d8h, 0c9h
    DB 0d9h, 0c1h
    DB 0d8h, 0cbh
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0ddh, 0dah
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@3fe66666
    DB 0d8h, 0c9h
    DB 0d8h, 02dh
    DD ?g_gameTwo@@3MB
    DB 0d9h, 05dh, 01ch
    DB 0d8h, 00dh
    DD ?g_gameWallCenterSegment@@3MB
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0d9h, 05dh, 064h
    DB 00fh, 08eh, 0dfh, 004h, 000h, 000h
    DB 0d8h, 025h
    DD __real@43960000
    DB 0d8h, 00dh
    DD __real@3c23d70a
    DB 0d9h, 055h, 068h
    DB 0d8h, 01dh
    DD ?g_gameOne@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 005h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 068h
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 08dh, 085h, 084h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 0bch, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 06ch, 000h, 000h, 048h, 043h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 0e4h, 0fbh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 08dh, 085h, 0a4h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 030h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 06ch, 000h, 000h, 0a0h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 018h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 0c8h
    DB 0d8h, 048h, 004h
    DB 051h
    DB 0d9h, 045h, 0cch
    DB 051h
    DB 0d8h, 048h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0c4h
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 045h, 068h
    DB 0d8h, 00dh
    DD ?g_gameAiLateralRecoveryThreshold@@3MB
    DB 0ddh, 01ch, 024h
    call _exp
    DB 08bh, 083h, 010h, 001h, 000h, 000h
    DB 0d9h, 0e8h
    DB 0d8h, 0e1h
    DB 089h, 045h, 04ch
    DB 08bh, 083h, 0a0h, 000h, 000h, 000h
    DB 03dh, 010h, 027h, 000h, 000h
    DB 0d8h, 08bh, 00ch, 001h, 000h, 000h
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD ?g_wavyTextTimeScale@@3MB
    DB 089h, 045h, 060h
    DB 0d8h, 0abh, 00ch, 001h, 000h, 000h
    DB 0d9h, 055h, 068h
    DB 0ddh, 0d9h
    DB 0d9h, 093h, 00ch, 001h, 000h, 000h
    DB 0d9h, 05dh, 020h
    DB 00fh, 08eh, 065h, 001h, 000h, 000h
    DB 0dbh, 045h, 060h
    DB 0d8h, 025h
    DD __real@469c4000
    DB 0d8h, 00dh
    DD __real@3bda740e
    DB 0d8h, 015h
    DD ?g_gameOne@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 0d9h, 0c0h
    DB 0a1h
    DD ?g_screenTintLevel@@3HA
    DB 0d8h, 0c9h
    DB 08bh, 04bh, 00ch
    DB 0d9h, 005h
    DD __real@40400000
    DB 005h, 0d4h, 0feh, 0ffh, 0ffh
    DB 039h, 081h, 0d8h, 000h, 000h, 000h
    DB 0d8h, 0c9h
    DB 0d9h, 0c1h
    DB 0d8h, 0cbh
    DB 0dch, 0c0h
    DB 0deh, 0e9h
    DB 0ddh, 0d9h
    DB 0d9h, 005h
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 0d8h, 0c9h
    DB 0d8h, 045h, 01ch
    DB 0d9h, 05dh, 01ch
    DB 0d9h, 005h
    DD __real@402ccccd
    DB 0d8h, 0c9h
    DB 0d8h, 045h, 064h
    DB 0d9h, 05dh, 064h
    DB 0d8h, 00dh
    DD ?g_gameWallCenterSegment@@3MB
    DB 0d9h, 05dh, 070h
    DB 07ch, 00bh
    DB 08bh, 04bh, 018h
    DB 039h, 081h, 0d8h, 000h, 000h, 000h
    DB 07dh, 004h
    DB 0c6h, 045h, 053h, 001h
    DB 0d9h, 045h, 0fch
    DB 0d8h, 0a3h, 014h, 001h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0d9h, 045h, 0fch
    DB 0d8h, 00dh
    DD __real@3b03126f
    DB 0deh, 0c1h
    DB 0d9h, 005h
    DD __real@3e4ccccd
    DB 0d8h, 065h, 068h
    DB 0d8h, 00dh
    DD __real@3c23d70a
    DB 0deh, 0e9h
    DB 0d8h, 045h, 068h
    DB 0d9h, 055h, 06ch
    DB 0d9h, 093h, 00ch, 001h, 000h, 000h
    DB 0d8h, 01dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 004h
    DB 0c6h, 045h, 053h, 001h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0d8h, 01dh
    DD __real@3e6147ae
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 057h
    DB 0d9h, 045h, 0fch
    DB 0d8h, 04dh, 0fch
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0d8h, 005h
    DD ?g_gameOne@@3MB
    DB 0d8h, 03dh
    DD ?g_gameOne@@3MB
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0d8h, 025h
    DD __real@3d4ccccd
    DB 0deh, 0c9h
    DB 0d8h, 0c9h
    DB 0d8h, 0c9h
    DB 0d8h, 00dh
    DD __real@3eb33333
    DB 0ddh, 0d9h
    DB 0d8h, 015h
    DD __real@3d4ccccd
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@3d4ccccd
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0d8h, 0e1h
    DB 0d9h, 09bh, 010h, 001h, 000h, 000h
    DB 0ebh, 004h
    DB 0c6h, 045h, 053h, 001h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameWallCenterSegment@@3MB
    DB 0d8h, 093h, 010h, 001h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 008h
    DB 0d9h, 09bh, 010h, 001h, 000h, 000h
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 08bh, 045h, 06ch
    DB 089h, 045h, 020h
    DB 08bh, 083h, 010h, 001h, 000h, 000h
    DB 089h, 045h, 04ch
    DB 0ebh, 076h
    DB 0d9h, 005h
    DD ?g_gameCameraDistanceBias@@3MB
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 0d9h, 055h, 06ch
    DB 08dh, 085h, 000h, 0feh, 0ffh, 0ffh
    DB 0d9h, 05dh, 068h
    DB 050h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 0e8h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 0d0h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 08dh, 085h, 0b8h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 068h
    DB 050h
    DB 08dh, 085h, 0a0h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 088h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 070h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 06ch, 000h, 000h, 0a0h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 0c7h, 045h, 058h, 000h, 000h, 0a0h, 0c0h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 07dh, 000h
    DB 08dh, 045h, 06ch
    DB 0a5h
    DB 050h
    DB 0a5h
    DB 08dh, 085h, 058h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0c4h
    DB 0c7h, 045h, 06ch, 0cdh, 0cch, 0cch, 0bdh
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 045h, 000h
    DB 050h
    DB 08dh, 085h, 040h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 085h, 028h, 0fdh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0b8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 04dh, 010h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0ddh, 005h
    DD ?g_waterCorrectionScale@@3NB
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 0e0h
    DB 0d9h, 045h, 014h
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 013h
    DB 0b8h, 020h, 04eh, 000h, 000h
    DB 039h, 083h, 0a0h, 000h, 000h, 000h
    DB 07dh, 006h
    DB 089h, 083h, 0a0h, 000h, 000h, 000h
    DB 0ddh, 005h
    DD __real@3fd3333340000000
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 0e0h
    DB 0d9h, 045h, 014h
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 041h
    DB 075h, 051h
    DB 0ddh, 005h
    DD __real@3fd3333340000000
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _tan
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 014h
    DB 0d8h, 04dh, 014h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 0d8h, 075h, 06ch
    DB 059h
    DB 059h
    DB 08dh, 04dh, 010h
    DB 0deh, 0c9h
    DB 0d9h, 05dh, 014h
    call ?Normalize@Vector3@@QAEMXZ
    DB 081h, 0bbh, 0a0h, 000h, 000h, 000h, 058h, 002h, 000h, 000h
    DB 0ddh, 0d8h
    DB 07eh, 004h
    DB 0c6h, 045h, 053h, 001h
    DB 08dh, 083h, 034h, 002h, 000h, 000h
    DB 089h, 045h, 068h
    DB 08dh, 043h, 04ch
    DB 089h, 045h, 060h
    DB 0c7h, 045h, 06ch, 002h, 000h, 000h, 000h
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 045h, 054h
    DB 050h
    DB 08bh, 045h, 060h
    DB 08bh, 000h
    DB 08bh, 048h, 004h
    DB 083h, 0c1h, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 0ddh, 005h
    DD ?g_textureHalf@@3NB
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 0e0h
    DB 0d9h, 045h, 058h
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 041h
    DB 075h, 041h
    DB 0ddh, 005h
    DD ?g_textureHalf@@3NB
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _tan
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 058h
    DB 0d8h, 04dh, 058h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 0d8h, 075h, 048h
    DB 059h
    DB 059h
    DB 08dh, 04dh, 054h
    DB 0deh, 0c9h
    DB 0d9h, 05dh, 058h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 08bh, 07dh, 068h
    DB 083h, 045h, 060h, 00ch
    DB 081h, 045h, 068h, 09ch, 000h, 000h, 000h
    DB 0ffh, 04dh, 06ch
    DB 08dh, 075h, 054h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 00fh, 085h, 066h, 0ffh, 0ffh, 0ffh
    DB 08bh, 045h, 0fch
    DB 089h, 083h, 014h, 001h, 000h, 000h
    DB 0ebh, 014h
    DB 08bh, 045h, 020h
    DB 089h, 083h, 00ch, 001h, 000h, 000h
    DB 08bh, 045h, 04ch
    DB 089h, 083h, 010h, 001h, 000h, 000h
    DB 0ddh, 0d8h
    DB 080h, 07dh, 053h, 000h
    DB 00fh, 084h, 0a4h, 000h, 000h, 000h
    DB 08bh, 083h, 0f0h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 01ch, 001h, 000h, 000h
    DB 083h, 0a3h, 0a4h, 000h, 000h, 000h, 000h
    DB 089h, 045h, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0c7h, 045h, 054h, 09ah, 099h, 099h, 03eh
    DB 08dh, 07bh, 07ch
    DB 0d9h, 0eeh
    DB 08dh, 075h, 054h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 045h, 0bch
    DB 0d8h, 005h
    DD ?g_parserMinimumBreakability@@3MB
    DB 089h, 045h, 058h
    DB 08bh, 043h, 008h
    DB 0c7h, 045h, 054h, 09ah, 099h, 099h, 0beh
    DB 08dh, 0bbh, 088h, 000h, 000h, 000h
    DB 08dh, 075h, 054h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d8h, 098h, 088h, 000h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 00ah
    DB 0c7h, 083h, 0a4h, 000h, 000h, 000h, 003h, 000h, 000h, 000h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0d8h, 000h, 000h, 000h
    DB 0c7h, 083h, 0ech, 000h, 000h, 000h, 000h, 000h, 000h, 03fh
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0e4h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0e0h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0dch, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0e8h, 000h, 000h, 000h
    DB 0d9h, 0e8h
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 0fch
    DB 08dh, 0bdh, 078h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 08dh, 083h, 004h, 003h, 000h, 000h
    DB 0d9h, 05dh, 010h
    DB 0c7h, 045h, 06ch, 002h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 018h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 060h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 064h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 084h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 08ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 034h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 045h, 020h
    DB 0a5h
    DB 0d9h, 0e0h
    DB 0a5h
    DB 0a5h
    DB 08dh, 075h, 054h
    DB 0d9h, 05dh, 068h
    DB 08dh, 07dh, 0d4h
    DB 0d9h, 0e8h
    DB 089h, 045h, 020h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 0fch
    DB 08dh, 075h, 010h
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 08dh, 07dh, 000h
    DB 08dh, 045h, 064h
    DB 050h
    DB 0d9h, 055h, 048h
    DB 08dh, 085h, 010h, 0fdh, 0ffh, 0ffh
    DB 0d9h, 05dh, 014h
    DB 0a5h
    DB 0a5h
    DB 050h
    DB 08dh, 04dh, 000h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 020h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 08bh, 045h, 0fch
    DB 089h, 085h, 068h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0b5h, 060h, 0ffh, 0ffh, 0ffh
    DB 08dh, 07dh, 054h
    DB 0a5h
    DB 08dh, 045h, 070h
    DB 0a5h
    DB 050h
    DB 08dh, 085h, 0f8h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 054h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 020h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 08bh, 045h, 048h
    DB 089h, 045h, 088h
    DB 08dh, 075h, 084h
    DB 08dh, 0bdh, 054h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 08dh, 045h, 01ch
    DB 0a5h
    DB 050h
    DB 08dh, 085h, 0e0h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 054h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 020h
    DB 050h
    DB 083h, 0c1h, 034h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0d9h, 045h, 0fch
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d8h, 00dh
    DD __real@be99999a
    DB 050h
    DB 08dh, 075h, 02ch
    DB 08dh, 0bdh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 030h
    DB 0a5h
    DB 08dh, 085h, 0c8h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 04ch
    DB 050h
    DB 0a5h
    DB 08dh, 085h, 0b0h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 078h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 075h, 020h
    DB 050h
    DB 08dh, 08eh, 0c8h, 0feh, 0ffh, 0ffh
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 08dh, 045h, 068h
    DB 050h
    DB 08dh, 085h, 098h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0d4h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 08eh, 0fch, 0feh, 0ffh, 0ffh
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 081h, 0c6h, 09ch, 000h, 000h, 000h
    DB 0ffh, 04dh, 06ch
    DB 0c7h, 045h, 0fch, 000h, 000h, 080h, 0bfh
    DB 089h, 075h, 020h
    DB 00fh, 085h, 0ddh, 0feh, 0ffh, 0ffh
    DB 0e9h, 04ah, 006h, 000h, 000h
GameManUpdate_004139f8 LABEL BYTE
    DB 0dbh, 083h, 0a0h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3983126f
    DB 0d8h, 015h
    DD __real@3d4ccccd
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@3d4ccccd
    DB 08dh, 083h, 04ch, 001h, 000h, 000h
    DB 06ah, 00dh
    DB 08dh, 0b0h, 0d8h, 002h, 000h, 000h
    DB 08bh, 0f8h
    DB 059h
    DB 0f3h, 0a5h
    DB 0d9h, 050h, 030h
    DB 083h, 0c0h, 034h
    DB 04ah
    DB 075h, 0eah
    DB 08bh, 003h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 02ch
    DB 0d9h, 05dh, 02ch
    DB 08dh, 07dh, 0d4h
    DB 0d9h, 0eeh
    DB 083h, 0c0h, 060h
    DB 0d9h, 05dh, 030h
    DB 050h
    DB 0d9h, 0e8h
    DB 08dh, 045h, 054h
    DB 050h
    DB 0d9h, 05dh, 034h
    DB 08dh, 04dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 054h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 04dh, 05ch
    DB 0deh, 0c1h
    DB 0d8h, 01dh
    DD __real@3eb851ec
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 008h
    DB 0d8h, 005h
    DD __real@3d23d70a
    DB 0ebh, 019h
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 012h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0d8h, 025h
    DD __real@3da3d70a
    DB 0d9h, 09bh, 010h, 001h, 000h, 000h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0d8h, 01dh
    DD __real@40933333
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 074h, 00ch
    DB 081h, 0bbh, 0a0h, 000h, 000h, 000h, 058h, 002h, 000h, 000h
    DB 07eh, 012h
    DB 083h, 0a3h, 0a0h, 000h, 000h, 000h, 000h
    DB 06ah, 003h
    DB 059h
    DB 089h, 08bh, 0a4h, 000h, 000h, 000h
    DB 0ebh, 003h
    DB 06ah, 003h
    DB 059h
    DB 0d9h, 0e8h
    DB 033h, 0c0h
    DB 039h, 083h, 018h, 001h, 000h, 000h
    DB 0d8h, 0a3h, 010h, 001h, 000h, 000h
    DB 089h, 04dh, 070h
    DB 0d9h, 05dh, 068h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d8h, 005h
    DD ?g_gameOne@@3MB
    DB 0d9h, 05dh, 048h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 01ch
    DB 075h, 00dh
    DB 083h, 065h, 070h, 000h
    DB 08bh, 0c1h
    DB 0c7h, 045h, 01ch, 000h, 000h, 080h, 0bfh
    DB 0d9h, 0eeh
    DB 06bh, 0c0h, 034h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 045h, 01ch
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 05dh, 030h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 02ch
    DB 0d9h, 05dh, 034h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 003h, 0c3h
    DB 089h, 045h, 06ch
    DB 0a5h
    DB 08dh, 0b0h, 004h, 003h, 000h, 000h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 085h, 080h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 064h
    DB 050h
    DB 08dh, 085h, 068h, 0fch, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0d4h
    DB 0c7h, 045h, 064h, 000h, 000h, 080h, 0bfh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08bh, 0ceh
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0d9h, 0eeh
    DB 083h, 0ech, 00ch
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 08dh, 085h, 054h, 0feh, 0ffh, 0ffh
    DB 0dch, 00dh
    DD ?g_textureHalf@@3NB
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 045h, 01ch
    DB 0d8h, 08bh, 010h, 001h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@be4ccccd
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 04dh, 06ch
    DB 08bh, 0f0h
    DB 08dh, 07dh, 02ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 02ch
    DB 081h, 0c1h, 004h, 003h, 000h, 000h
    DB 083h, 0c4h, 010h
    DB 0d8h, 001h
    DB 0d9h, 019h
    DB 0d9h, 045h, 030h
    DB 0d8h, 041h, 004h
    DB 0d9h, 059h, 004h
    DB 0d9h, 045h, 034h
    DB 0d8h, 041h, 008h
    DB 0d9h, 059h, 008h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 045h, 01ch
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 089h, 045h, 030h
    DB 08bh, 045h, 070h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0eeh
    DB 08dh, 075h, 02ch
    DB 06bh, 0c0h, 034h
    DB 0d9h, 05dh, 034h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 034h, 018h
    DB 0c7h, 045h, 048h, 0cdh, 0cch, 08ch, 03fh
    DB 089h, 075h, 070h
    DB 08dh, 045h, 068h
    DB 050h
    DB 08dh, 085h, 060h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 085h, 084h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0d4h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 08eh, 004h, 003h, 000h, 000h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0d9h, 045h, 01ch
    DB 0dch, 00dh
    DD __real@bff3333333333333
    DB 083h, 0ech, 00ch
    DB 08dh, 085h, 06ch, 0feh, 0ffh, 0ffh
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 045h, 01ch
    DB 0d8h, 08bh, 010h, 001h, 000h, 000h
    DB 0dch, 00dh
    DD __real@3ff8000000000000
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0dch, 02dh
    DD __real@3feccccccccccccd
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 04dh, 06ch
    DB 08bh, 0f0h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 081h, 0c1h, 0cch, 001h, 000h, 000h
    DB 0a5h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0c7h, 045h, 02ch, 09ah, 099h, 099h, 0beh
    DB 0d9h, 0eeh
    DB 08dh, 075h, 02ch
    DB 0d9h, 05dh, 030h
    DB 08dh, 07dh, 0d4h
    DB 0d9h, 0eeh
    DB 08dh, 045h, 068h
    DB 0d9h, 05dh, 034h
    DB 050h
    DB 0a5h
    DB 0a5h
    DB 08dh, 085h, 090h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0d4h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 070h
    DB 050h
    DB 081h, 0c1h, 0cch, 001h, 000h, 000h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 08bh, 0b3h, 0a0h, 000h, 000h, 000h
    DB 083h, 0feh, 064h
    DB 00fh, 08eh, 057h, 003h, 000h, 000h
    DB 08bh, 0cbh
    call ?CalculateKineticEnergy@GameMan@@QAEMXZ
    DB 0d8h, 01dh
    DD ?g_randomHalf@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 00fh, 08ah, 03fh, 003h, 000h, 000h
    DB 083h, 0c6h, 00ah
    DB 089h, 0b3h, 0a0h, 000h, 000h, 000h
    DB 0e9h, 031h, 003h, 000h, 000h
GameManUpdate_00413d11 LABEL BYTE
    DB 08dh, 083h, 04ch, 001h, 000h, 000h
    DB 06ah, 00dh
    DB 08dh, 0b0h, 0d8h, 002h, 000h, 000h
    DB 08bh, 0f8h
    DB 059h
    DB 0f3h, 0a5h
    DB 0c7h, 040h, 030h, 00ah, 0d7h, 0a3h, 03bh
    DB 083h, 0c0h, 034h
    DB 04ah
    DB 075h, 0e6h
    DB 08bh, 043h, 008h
    DB 0d9h, 040h, 07ch
    DB 051h
    DB 0d8h, 00dh
    DD __real@3d4ccccd
    DB 051h
    DB 0d8h, 0abh, 010h, 001h, 000h, 000h
    DB 0d9h, 09bh, 010h, 001h, 000h, 000h
    DB 08bh, 040h, 07ch
    DB 0d9h, 0eeh
    DB 089h, 045h, 04ch
    DB 0d9h, 05dh, 068h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 020h
    DB 0d9h, 045h, 04ch
    DB 0ddh, 01ch, 024h
    call _fabs
    DB 0d9h, 0c0h
    DB 059h
    DB 0d8h, 01dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 059h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 005h
    DB 07bh, 076h
    DB 0d9h, 045h, 04ch
    DB 051h
    DB 0d8h, 04dh, 04ch
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 07dh, 04ch
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d8h, 06dh, 04ch
    DB 0d8h, 015h
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 021h
    DB 0d9h, 005h
    DD __real@bfc00000
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 005h
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 068h
    DB 0d9h, 005h
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 020h
    DB 0d8h, 015h
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 01bh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 068h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d9h, 05dh, 020h
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 0d9h, 0e8h
    DB 08dh, 075h, 02ch
    DB 0d9h, 05dh, 060h
    DB 08dh, 0bdh, 078h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 08dh, 083h, 000h, 002h, 000h, 000h
    DB 0d9h, 05dh, 084h
    DB 089h, 045h, 064h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 070h, 002h, 000h, 000h, 000h
    DB 0d9h, 05dh, 08ch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 034h
    DB 0d9h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 08dh, 075h, 02ch
    DB 0d9h, 0eeh
    DB 08dh, 0bdh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 034h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 060h
    DB 08dh, 075h, 084h
    DB 0d8h, 00dh
    DD __real@be99999a
    DB 08dh, 07dh, 0d4h
    DB 051h
    DB 051h
    DB 0d9h, 05dh, 088h
    DB 0a5h
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 0a5h
    DB 0ddh, 01ch, 024h
    DB 0a5h
    call _sin
    DB 059h
    DB 0d8h, 04dh, 060h
    DB 059h
    DB 08dh, 045h, 0d4h
    DB 050h
    DB 0dch, 00dh
    DD __real@3fd3333333333333
    DB 08dh, 085h, 078h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 048h
    DB 0d8h, 045h, 068h
    DB 050h
    DB 08dh, 085h, 09ch, 0feh, 0ffh, 0ffh
    DB 0d9h, 05dh, 048h
    DB 050h
    DB 08dh, 08dh, 078h, 0ffh, 0ffh, 0ffh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 04dh, 064h
    DB 050h
    DB 083h, 0c1h, 0cch
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0d9h, 083h, 010h, 001h, 000h, 000h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d8h, 04dh, 060h
    DB 059h
    DB 059h
    DB 08dh, 045h, 048h
    DB 0dch, 00dh
    DD __real@3fd3333333333333
    DB 050h
    DB 08dh, 085h, 0d8h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 0d8h, 065h, 0fch
    DB 08dh, 08dh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 048h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 064h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 081h, 045h, 064h, 09ch, 000h, 000h, 000h
    DB 0ffh, 04dh, 070h
    DB 0c7h, 045h, 060h, 000h, 000h, 080h, 0bfh
    DB 00fh, 085h, 03fh, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 020h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 020h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 0e4h, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 048h
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 08bh, 098h, 001h, 000h, 000h
    DB 08bh, 0f9h
    DB 08dh, 075h, 0d4h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 083h, 065h, 04ch, 000h
    DB 0ddh, 0d8h
    DB 08dh, 083h, 004h, 003h, 000h, 000h
    DB 0d9h, 0e8h
    DB 0c7h, 083h, 0b0h, 001h, 000h, 000h, 017h, 0b7h, 051h, 03ah
    DB 0d9h, 05dh, 060h
    DB 089h, 045h, 064h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 034h
    DB 08bh, 045h, 04ch
    DB 0d9h, 0eeh
    DB 0d9h, 09ch, 085h, 034h, 0ffh, 0ffh, 0ffh
    DB 051h
    DB 08bh, 083h, 010h, 001h, 000h, 000h
    DB 089h, 045h, 070h
    DB 0d9h, 045h, 070h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 070h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d8h, 04dh, 060h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 02dh
    DD ?g_randomHalf@@3MB
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 045h, 060h
    DB 0d8h, 04dh, 048h
    DB 0d9h, 0e0h
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 045h, 060h
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 07dh, 064h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 075h, 064h
    DB 083h, 0c4h, 010h
    DB 08bh, 0ceh
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 0ceh
    DB 0ddh, 0d8h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 045h, 060h
    DB 0ddh, 0d8h
    DB 08dh, 04eh, 068h
    DB 089h, 045h, 02ch
    DB 08bh, 0f9h
    DB 08dh, 075h, 02ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 083h, 045h, 04ch, 003h
    DB 081h, 045h, 064h, 09ch, 000h, 000h, 000h
    DB 0ddh, 0d8h
    DB 083h, 07dh, 04ch, 003h
    DB 0c7h, 045h, 060h, 000h, 000h, 080h, 0bfh
    DB 00fh, 08eh, 04bh, 0ffh, 0ffh, 0ffh
    DB 0ffh, 083h, 0a0h, 000h, 000h, 000h
    DB 08bh, 083h, 0a4h, 000h, 000h, 000h
    DB 083h, 0f8h, 00ch
    DB 00fh, 084h, 0f8h, 00dh, 000h, 000h
    DB 083h, 0f8h, 00dh
    DB 00fh, 084h, 0efh, 00dh, 000h, 000h
    DB 083h, 0f8h, 00eh
    DB 00fh, 084h, 0e6h, 00dh, 000h, 000h
    DB 08bh, 00bh
    DB 0b8h, 084h, 000h, 000h, 000h
    DB 003h, 0c8h
    DB 051h
    DB 08dh, 04dh, 010h
    DB 051h
    DB 08bh, 04dh, 07ch
    DB 08bh, 009h
    DB 003h, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 083h, 084h, 000h, 000h, 000h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d8h, 01dh
    DD __real@40c80000
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 041h
    DB 075h, 005h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0a8h
    DB 0d9h, 045h, 010h
    DB 051h
    DB 0d8h, 04dh, 010h
    DB 051h
    DB 0d9h, 045h, 018h
    DB 0d8h, 04dh, 018h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 014h
    DB 0d8h, 04dh, 014h
    DB 0deh, 0c1h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 03dh
    DD ?g_gameOne@@3MB
    DB 059h
    DB 059h
    DB 0d9h, 045h, 014h
    DB 0d8h, 04dh, 0b0h
    DB 0d9h, 045h, 010h
    DB 0d8h, 04dh, 0ach
    DB 0deh, 0c1h
    DB 0d9h, 045h, 018h
    DB 0d8h, 04dh, 0b4h
    DB 0deh, 0c1h
    DB 0deh, 0c9h
    DB 0d8h, 00dh
    DD ?g_freeCameraAimScale@@3MB
    DB 0d9h, 093h, 020h, 001h, 000h, 000h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d8h, 01dh
    DD __real@3ad1b717
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 020h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _fabs
    DB 0d8h, 0bbh, 020h, 001h, 000h, 000h
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d9h, 09bh, 020h, 001h, 000h, 000h
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 0d9h, 083h, 020h, 001h, 000h, 000h
    DB 0d8h, 01dh
    DD ?g_gameLevelArenaExtent@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07bh, 01bh
    DB 0d9h, 083h, 020h, 001h, 000h, 000h
    DB 0d8h, 01dh
    DD ?g_gameLevelArenaExtent@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 074h, 008h
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 020h, 001h, 000h, 000h
    DB 083h, 0bbh, 0fch, 006h, 000h, 000h, 002h
    DB 0d9h, 045h, 028h
    DB 0d8h, 083h, 020h, 001h, 000h, 000h
    DB 0d9h, 09bh, 020h, 001h, 000h, 000h
    DB 075h, 015h
    DB 08bh, 083h, 040h, 001h, 000h, 000h
    DB 083h, 0f8h, 004h
    DB 074h, 00ah
    DB 083h, 0f8h, 001h
    DB 074h, 005h
    DB 083h, 0f8h, 002h
    DB 075h, 009h
    DB 08bh, 045h, 028h
    DB 089h, 083h, 020h, 001h, 000h, 000h
    DB 0d9h, 045h, 0a8h
    DB 08dh, 073h, 07ch
    DB 0d8h, 08bh, 020h, 001h, 000h, 000h
    DB 08dh, 0bdh, 008h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0d9h, 093h, 020h, 001h, 000h, 000h
    DB 0d9h, 055h, 07ch
    DB 0a5h
    DB 08dh, 0b3h, 088h, 000h, 000h, 000h
    DB 08dh, 0bdh, 014h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 051h
    DB 051h
    DB 0a5h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 07ch
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d8h, 04bh, 07ch
    DB 0d9h, 045h, 048h
    DB 0d8h, 08bh, 084h, 000h, 000h, 000h
    DB 0deh, 0c1h
    DB 0d9h, 05dh, 068h
    DB 0d9h, 045h, 07ch
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 07ch
    DB 0ddh, 01ch, 024h
    call _cos
    DB 08bh, 045h, 068h
    DB 0d8h, 08bh, 084h, 000h, 000h, 000h
    DB 0d9h, 045h, 048h
    DB 059h
    DB 0d8h, 04bh, 07ch
    DB 089h, 043h, 07ch
    DB 059h
    DB 0deh, 0e9h
    DB 0d9h, 09bh, 084h, 000h, 000h, 000h
    DB 0d9h, 045h, 068h
    DB 0d9h, 0e0h
    DB 0d9h, 09bh, 088h, 000h, 000h, 000h
    DB 0d9h, 083h, 084h, 000h, 000h, 000h
    DB 0d9h, 0e0h
    DB 0d9h, 09bh, 090h, 000h, 000h, 000h
    DB 0d9h, 045h, 068h
    DB 0d8h, 01dh
    DD __real@3e4ccccd
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 01bh
    DB 08dh, 0b5h, 008h, 0ffh, 0ffh, 0ffh
    DB 08dh, 07bh, 07ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 0b5h, 014h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0bbh, 088h, 000h, 000h, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 0f4h
    DB 08dh, 075h, 0b8h
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 08dh, 07dh, 084h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 055h, 07ch
    DB 0d8h, 045h, 024h
    DB 0a5h
    DB 0d9h, 05dh, 024h
    DB 08dh, 075h, 0b8h
    DB 08dh, 07dh, 09ch
    DB 0a5h
    DB 0a5h
    DB 08dh, 045h, 09ch
    DB 068h, 000h, 0ffh, 000h, 000h
    DB 0a5h
    DB 050h
    DB 0c7h, 045h, 0a0h, 000h, 000h, 0a0h, 040h
    call ?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z
    DB 059h
    DB 059h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0c7h, 045h, 048h, 000h, 000h, 0a0h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 000h
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 04dh, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 08dh, 083h, 01ch, 001h, 000h, 000h
    DB 0d9h, 0e8h
    DB 08dh, 0bbh, 024h, 001h, 000h, 000h
    DB 0d8h, 020h
    DB 08dh, 075h, 02ch
    DB 0a5h
    DB 0a5h
    DB 0d8h, 00dh
    DD __real@3c23d70a
    DB 08dh, 04dh, 03ch
    DB 0d8h, 000h
    DB 0a5h
    DB 0d9h, 010h
    DB 08dh, 045h, 084h
    DB 0d9h, 05dh, 028h
    DB 050h
    DB 08dh, 085h, 0e4h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 0c7h, 045h, 048h, 000h, 000h, 070h, 041h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 0d8h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0e4h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 083h, 0dch, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_parserMinimumBreakability@@3MB
    DB 0d8h, 083h, 0d8h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 0d9h, 045h, 0c8h
    DB 0d8h, 048h, 004h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0cch
    DB 0d8h, 048h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0c4h
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d9h, 045h, 094h
    DB 0d8h, 04dh, 0b0h
    DB 0d9h, 045h, 090h
    DB 0d8h, 04dh, 0ach
    DB 0deh, 0c1h
    DB 0d9h, 045h, 098h
    DB 0d8h, 04dh, 0b4h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD __real@3827c5ac
    DB 0deh, 0c1h
    DB 0d8h, 0a3h, 0e0h, 000h, 000h, 000h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 055h, 048h
    DB 0d8h, 01dh
    DD ?g_waterNeighborCoupling@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 017h
    DB 0ddh, 0d8h
    DB 051h
    DB 0d9h, 045h, 048h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 059h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 059h
    DB 0d8h, 04dh, 028h
    DB 08dh, 045h, 084h
    DB 050h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0c0h
    DB 050h
    DB 0d8h, 0a3h, 0dch, 000h, 000h, 000h
    DB 08dh, 04dh, 0e4h
    DB 0d8h, 00dh
    DD __real@3c23d70a
    DB 0d8h, 083h, 0dch, 000h, 000h, 000h
    DB 0d9h, 09bh, 0dch, 000h, 000h, 000h
    DB 0d8h, 045h, 07ch
    DB 0d8h, 083h, 0d8h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameCameraAimDamping@@3MB
    DB 0d9h, 093h, 0d8h, 000h, 000h, 000h
    DB 0d8h, 065h, 024h
    DB 0d8h, 0a3h, 0e0h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_wavyTextDisplacement@@3MB
    DB 0d8h, 083h, 0e0h, 000h, 000h, 000h
    DB 0d9h, 09bh, 0e0h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 0b4h
    DB 0d8h, 048h, 008h
    DB 0d9h, 045h, 0b0h
    DB 0d8h, 048h, 004h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0ach
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0ach
    DB 0d8h, 04dh, 03ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 04dh, 0b0h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0b4h
    DB 0d8h, 04dh, 044h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD ?g_gameCameraDistanceBias@@3MB
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD __real@3b03126f
    DB 0d9h, 045h, 094h
    DB 0d8h, 04dh, 0c8h
    DB 0d9h, 045h, 098h
    DB 0d8h, 04dh, 0cch
    DB 0deh, 0c1h
    DB 0d9h, 045h, 090h
    DB 0d8h, 04dh, 0c4h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD __real@37fba882
    DB 0deh, 0c1h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d9h, 055h, 07ch
    DB 0d8h, 01dh
    DD ?g_waterNeighborCoupling@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 017h
    DB 0ddh, 0d8h
    DB 051h
    DB 0d9h, 045h, 07ch
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 059h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 059h
    DB 0d8h, 04dh, 028h
    DB 08dh, 075h, 02ch
    DB 08dh, 0bdh, 078h, 0ffh, 0ffh, 0ffh
    DB 083h, 065h, 024h, 000h
    DB 0d8h, 083h, 0e4h, 000h, 000h, 000h
    DB 08dh, 043h, 04ch
    DB 089h, 045h, 068h
    DB 08dh, 083h, 0cch, 001h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameActivityDecay@@3MB
    DB 0c7h, 085h, 068h, 0ffh, 0ffh, 0ffh, 0cdh, 0cch, 0cch, 0bdh
    DB 0d9h, 045h, 038h
    DB 089h, 045h, 07ch
    DB 0d8h, 025h
    DD ?g_randomHalf@@3MB
    DB 0d8h, 00dh
    DD __real@3b9a0275
    DB 0deh, 0c1h
    DB 0d9h, 083h, 020h, 001h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3ec08313
    DB 0deh, 0c1h
    DB 0d9h, 09bh, 0e4h, 000h, 000h, 000h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 084h
    DB 0d9h, 045h, 0f4h
    DB 0dch, 0c0h
    DB 0d9h, 05dh, 064h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 08ch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 034h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 08dh, 075h, 02ch
    DB 0d9h, 0e8h
    DB 08dh, 0bdh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 034h
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 064h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 030h
    DB 08dh, 075h, 02ch
    DB 0d9h, 0eeh
    DB 08dh, 0bdh, 054h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 034h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 083h, 0d8h, 000h, 000h, 000h
    DB 0d9h, 083h, 0d8h, 000h, 000h, 000h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    DB 089h, 045h, 048h
    call _cos
    DB 0d9h, 05dh, 070h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 028h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 048h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 028h
    DB 0d8h, 04dh, 070h
    DB 0d9h, 0e0h
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 045h, 060h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d8h, 045h, 06ch
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08bh, 045h, 024h
    DB 099h
    DB 06ah, 003h
    DB 059h
    DB 0f7h, 0f9h
    DB 08bh, 07dh, 07ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 07dh, 09ch
    DB 083h, 0c4h, 004h
    DB 08dh, 004h, 040h
    DB 08dh, 074h, 083h, 07ch
    DB 089h, 075h, 028h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 0a4h
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 0eeh
    DB 08dh, 085h, 0e4h, 0feh, 0ffh, 0ffh
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 045h, 09ch
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 00bh
    DB 08bh, 0f0h
    DB 08dh, 07dh, 054h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 08dh, 085h, 0d8h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 083h, 0c1h, 060h
    DB 0a5h
    call ?Column1@Matrix3@@QAE?AUVector3@@XZ
    DB 0d9h, 045h, 0a4h
    DB 0d8h, 048h, 008h
    DB 0d9h, 045h, 09ch
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 0d9h, 045h, 060h
    DB 0d8h, 08bh, 0e4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_randomHalf@@3MB
    DB 08bh, 04dh, 028h
    DB 08dh, 075h, 084h
    DB 08dh, 07dh, 0d4h
    DB 0deh, 0c1h
    DB 0d9h, 040h, 004h
    DB 08dh, 045h, 0d4h
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 050h
    DB 08dh, 045h, 010h
    DB 050h
    DB 0deh, 0c1h
    DB 08dh, 085h, 09ch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 0d8h, 065h, 064h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 054h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 04dh, 05ch
    DB 0deh, 0c1h
    DB 0d9h, 045h, 058h
    DB 0d8h, 04dh, 058h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 0deh, 0c1h
    DB 0d9h, 05dh, 088h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 083h, 07dh, 024h, 000h
    DB 074h, 018h
    DB 0d9h, 005h
    DD ?g_unk0x00c09ce0@@3MA
    DB 0d9h, 045h, 018h
    DB 0d8h, 0e1h
    DB 0d9h, 05dh, 018h
    DB 0d9h, 045h, 014h
    DB 0d8h, 0e1h
    DB 0d9h, 05dh, 014h
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 014h
    DB 051h
    DB 0d8h, 04dh, 014h
    DB 051h
    DB 0d9h, 045h, 018h
    DB 0d8h, 04dh, 018h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 010h
    DB 0d8h, 04dh, 010h
    DB 0deh, 0c1h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d9h, 05dh, 028h
    DB 0d9h, 045h, 0f0h
    DB 0d8h, 083h, 0d8h, 000h, 000h, 000h
    DB 0d9h, 055h, 070h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 070h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 06ch
    DB 08dh, 04dh, 010h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@MM@Z
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 08bh, 083h, 0e4h, 000h, 000h, 000h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    DB 089h, 045h, 04ch
    call _cos
    DB 0d9h, 05dh, 070h
    DB 0d9h, 045h, 04ch
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 0e0h
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 070h
    DB 08dh, 04dh, 010h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@MM@Z
    DB 08dh, 085h, 078h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 010h
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 07dh, 07ch
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 07dh, 07ch
    DB 08bh, 0cfh
    call ?Normalize@Vector3@@QAEMXZ
    DB 083h, 0ech, 00ch
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 028h
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 043h, 078h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 043h, 074h
    DB 0d9h, 01ch, 024h
    call ?CalculateLimbAngleCosine@@YAMMMM@Z
    DB 0d9h, 055h, 070h
    DB 083h, 0c4h, 004h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0ddh, 01ch, 024h
    DB 0ddh, 0d8h
    call _sqrt
    DB 0d9h, 0e0h
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 090h, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 070h
    DB 0d9h, 0e0h
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08dh, 04fh, 00ch
    DB 083h, 0c1h, 028h
    DB 08bh, 0f0h
    DB 08bh, 0f9h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 083h, 0ech, 00ch
    DB 0ddh, 0d8h
    DB 0d9h, 043h, 078h
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 045h, 028h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 043h, 074h
    DB 0d9h, 01ch, 024h
    call ?CalculateLimbAngleCosine@@YAMMMM@Z
    DB 08bh, 04dh, 07ch
    DB 0d9h, 05dh, 038h
    DB 08bh, 045h, 060h
    DB 083h, 0c1h, 00ch
    DB 089h, 085h, 060h, 0ffh, 0ffh, 0ffh
    DB 08bh, 0f9h
    DB 08dh, 0b5h, 060h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 00ch
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 051h
    DB 0ddh, 0d8h
    DB 051h
    DB 0d9h, 045h, 038h
    DB 0d8h, 04dh, 038h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 04dh, 07ch
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 045h, 038h
    DB 08dh, 045h, 060h
    DB 0d9h, 0e0h
    DB 083h, 0c1h, 00ch
    DB 0d9h, 01ch, 024h
    DB 050h
    DB 08dh, 085h, 06ch, 0feh, 0ffh, 0ffh
    DB 050h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04dh, 07ch
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@MM@Z
    DB 08bh, 04dh, 07ch
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 090h
    DB 050h
    DB 08dh, 045h, 000h
    DB 050h
    DB 08dh, 085h, 084h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0b8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 04dh, 090h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0ddh, 005h
    DD __real@3fd3333340000000
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 0c0h
    DB 059h
    DB 0d9h, 0e0h
    DB 0d9h, 045h, 094h
    DB 059h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0ddh, 0d8h
    DB 0f6h, 0c4h, 041h
    DB 075h, 041h
    DB 0ddh, 005h
    DD __real@3fd3333340000000
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _tan
    DB 0d9h, 05dh, 028h
    DB 0d9h, 045h, 094h
    DB 0d8h, 04dh, 094h
    DB 0d8h, 02dh
    DD ?g_gameOne@@3MB
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 0d8h, 075h, 028h
    DB 059h
    DB 059h
    DB 08dh, 04dh, 090h
    DB 0deh, 0c9h
    DB 0d9h, 05dh, 094h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 08dh, 045h, 090h
    DB 050h
    DB 08dh, 085h, 060h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 045h, 068h
    DB 08bh, 000h
    DB 08bh, 048h, 004h
    DB 083h, 0c1h, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 07dh, 07ch
    DB 083h, 045h, 024h, 003h
    DB 083h, 045h, 068h, 00ch
    DB 081h, 045h, 07ch, 09ch, 000h, 000h, 000h
    DB 083h, 0c7h, 068h
    DB 083h, 07dh, 024h, 003h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0c7h, 045h, 060h, 000h, 000h, 080h, 0bfh
    DB 00fh, 08eh, 0fdh, 0fbh, 0ffh, 0ffh
    DB 08dh, 043h, 07ch
    DB 050h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08bh, 088h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 040h, 008h
    DB 0d9h, 0c0h
    DB 0d8h, 0c9h
    DB 0d8h, 01dh
    DD ?g_gameAiMotionSquaredLimit@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 01bh
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 008h
    DB 0d9h, 005h
    DD __real@c0800000
    DB 0ebh, 006h
    DB 0d9h, 005h
    DD ?g_gameCameraMinimumDistanceScale@@3MB
    DB 0d9h, 05dh, 028h
    DB 051h
    DB 0d9h, 083h, 0d8h, 000h, 000h, 000h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3e800000
    DB 0d9h, 055h, 07ch
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 070h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3e800000
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 048h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3e800000
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 07ch
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 048h
    DB 0d8h, 04dh, 070h
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 045h, 06ch
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 08bh, 064h, 001h, 000h, 000h
    DB 08bh, 0f9h
    DB 08dh, 075h, 0d4h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08dh, 08bh, 070h, 001h, 000h, 000h
    DB 0ddh, 0d8h
    DB 0c7h, 045h, 02ch, 000h, 000h, 020h, 042h
    DB 0d9h, 0eeh
    DB 08bh, 0f9h
    DB 0d9h, 05dh, 030h
    DB 08dh, 075h, 02ch
    DB 0d9h, 045h, 028h
    DB 0d9h, 0e0h
    DB 0d9h, 05dh, 034h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 051h
    DB 0ddh, 0d8h
    DB 051h
    DB 0d9h, 083h, 0d8h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3e800000
    DB 0d9h, 045h, 0f0h
    DB 0d8h, 00dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0deh, 0e9h
    DB 0d8h, 065h, 0e0h
    DB 0d9h, 055h, 07ch
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 070h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3e800000
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 048h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3e800000
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 07ch
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 045h, 048h
    DB 0d8h, 04dh, 070h
    DB 0d8h, 00dh
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 045h, 06ch
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 08bh, 098h, 001h, 000h, 000h
    DB 08bh, 0f9h
    DB 08dh, 075h, 0d4h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 045h, 0f4h
    DB 0ddh, 0d8h
    DB 083h, 065h, 024h, 000h
    DB 0d9h, 0e8h
    DB 089h, 083h, 0b8h, 000h, 000h, 000h
    DB 0d9h, 05dh, 060h
    DB 08dh, 085h, 0a8h, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 0f0h
    DB 089h, 045h, 0e0h
    DB 0dch, 0c0h
    DB 08dh, 083h, 004h, 003h, 000h, 000h
    DB 089h, 045h, 07ch
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 0f4h
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d9h, 05dh, 064h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 030h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 034h
    DB 0d9h, 083h, 0d8h, 000h, 000h, 000h
    DB 051h
    DB 0d8h, 025h
    DD __real@3da3d70a
    DB 051h
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0d8h, 083h, 0d4h, 000h, 000h, 000h
    DB 0d8h, 065h, 048h
    DB 0d8h, 065h, 064h
    DB 0d9h, 055h, 070h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 068h
    DB 0d9h, 083h, 0e4h, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD ?g_gameCameraMinimumDistanceScale@@3MB
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 045h, 028h
    DB 0d8h, 04dh, 060h
    DB 0d9h, 055h, 06ch
    DB 0d8h, 00dh
    DD __real@3d4ccccd
    DB 0d9h, 05dh, 038h
    DB 0d9h, 045h, 070h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d8h, 06dh, 038h
    DB 08dh, 085h, 014h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 045h, 068h
    DB 0d9h, 0e0h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 04dh, 060h
    DB 0deh, 0e9h
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d9h, 045h, 060h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 07dh, 07ch
    DB 08bh, 04dh, 07ch
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 075h, 0e0h
    DB 08dh, 07dh, 000h
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 060h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 075h, 024h
    DB 08bh, 07dh, 07ch
    DB 08dh, 045h, 070h
    DB 0d8h, 08ch, 035h, 034h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 085h, 0e4h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 0d8h, 00dh
    DD __real@bf400000
    DB 08dh, 04fh, 00ch
    DB 0d9h, 05dh, 070h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 04dh, 000h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0d9h, 0e8h
    DB 08dh, 084h, 035h, 044h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 020h
    DB 050h
    DB 08dh, 085h, 0d8h, 0feh, 0ffh, 0ffh
    DB 0d9h, 055h, 068h
    DB 0d9h, 05dh, 070h
    DB 050h
    DB 08dh, 04dh, 000h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 09ch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 078h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cfh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 04dh, 07ch
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 06ch
    DB 0d8h, 00dh
    DD __real@3e4ccccd
    DB 0d8h, 02dh
    DD __real@3f28f5c2
    DB 0d9h, 05dh, 038h
    DB 0d9h, 005h
    DD __real@3fd47ae1
    DB 0d9h, 045h, 038h
    DB 0d8h, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 005h
    DB 0d9h, 05dh, 038h
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 08bh, 07dh, 024h
    DB 051h
    DB 08dh, 0b4h, 03dh, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 006h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 070h
    DB 0d9h, 006h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 006h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 006h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 045h, 070h
    DB 08dh, 084h, 03dh, 044h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 00dh
    DD __real@3fd47ae1
    DB 0d8h, 065h, 06ch
    DB 0d8h, 008h
    DB 0d9h, 045h, 068h
    DB 0d8h, 04dh, 038h
    DB 0deh, 0c1h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    DB 051h
    DB 0d8h, 00dh
    DD __real@3fd47ae1
    DB 0d8h, 045h, 04ch
    DB 0d8h, 008h
    DB 08dh, 085h, 090h, 0feh, 0ffh, 0ffh
    DB 0d8h, 045h, 068h
    DB 0d8h, 04dh, 060h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 04dh, 07ch
    DB 083h, 0c1h, 034h
    DB 08bh, 0f0h
    DB 08bh, 0f9h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 045h, 060h
    DB 08bh, 07dh, 07ch
    DB 0ddh, 0d8h
    DB 089h, 045h, 02ch
    DB 08bh, 045h, 024h
    DB 083h, 0c7h, 068h
    DB 08dh, 075h, 02ch
    DB 0a5h
    DB 08dh, 084h, 005h, 020h, 0ffh, 0ffh, 0ffh
    DB 08bh, 008h
    DB 0a5h
    DB 0d9h, 000h
    DB 051h
    DB 051h
    DB 0a5h
    DB 0ddh, 01ch, 024h
    DB 089h, 04dh, 020h
    call _cos
    DB 0d9h, 05dh, 070h
    DB 051h
    DB 0d9h, 0eeh
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 045h, 020h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 0e0h
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 085h, 06ch, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 070h
    DB 0d8h, 04dh, 060h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08bh, 045h, 068h
    DB 08dh, 07dh, 0d4h
    DB 0a5h
    DB 089h, 045h, 0fch
    DB 08bh, 045h, 024h
    DB 083h, 0c4h, 010h
    DB 08dh, 084h, 005h, 044h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 050h
    DB 08dh, 085h, 084h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0d4h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 07dh, 07ch
    DB 050h
    DB 08dh, 085h, 060h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 085h, 054h, 0feh, 0ffh, 0ffh
    DB 083h, 0c7h, 068h
    DB 050h
    DB 08bh, 0cfh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 04dh, 07ch
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c1h, 068h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 083h, 045h, 024h, 00ch
    DB 083h, 045h, 0e0h, 024h
    DB 0ddh, 0d8h
    DB 081h, 045h, 07ch, 09ch, 000h, 000h, 000h
    DB 083h, 07dh, 024h, 00ch
    DB 0c7h, 045h, 060h, 000h, 000h, 080h, 0bfh
    DB 00fh, 08eh, 023h, 0fdh, 0ffh, 0ffh
    DB 08bh, 09bh, 040h, 001h, 000h, 000h
    DB 085h, 0dbh
    DB 074h, 005h
    DB 083h, 0fbh, 005h
    DB 075h, 019h
    DB 0f6h, 045h, 00ch, 008h
    DB 074h, 013h
    DB 08bh, 085h, 030h, 0ffh, 0ffh, 0ffh
    DB 06ah, 008h
    DB 059h
    DB 0d9h, 0eeh
    DB 0d9h, 018h
    DB 083h, 0c0h, 034h
    DB 049h
    DB 075h, 0f6h
    DB 05fh
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 074h
    DB 0c9h
    DB 0c2h, 004h, 000h
?Update@GameMan@@QAEXH@Z ENDP

.const
PUBLIC __real@3ad1b717
__real@3ad1b717 DWORD 03ad1b717h
PUBLIC __real@3c5a740e
__real@3c5a740e DWORD 03c5a740eh
PUBLIC __real@3fd3333333333333
__real@3fd3333333333333 QWORD 03fd3333333333333h
PUBLIC __real@3feccccccccccccd
__real@3feccccccccccccd QWORD 03feccccccccccccdh
PUBLIC __real@3ff8000000000000
__real@3ff8000000000000 QWORD 03ff8000000000000h
PUBLIC __real@41490fdb
__real@41490fdb DWORD 041490fdbh
PUBLIC __real@41c90fdb
__real@41c90fdb DWORD 041c90fdbh
PUBLIC __real@42c80000
__real@42c80000 DWORD 042c80000h
PUBLIC __real@432a0000
__real@432a0000 DWORD 0432a0000h
PUBLIC __real@469c4000
__real@469c4000 DWORD 0469c4000h
PUBLIC __real@bff3333333333333
__real@bff3333333333333 QWORD 0bff3333333333333h
PUBLIC __real@c1000000
__real@c1000000 DWORD 0c1000000h
PUBLIC __real@c10b3333
__real@c10b3333 DWORD 0c10b3333h
PUBLIC _GameManUpdateDispatchTable0
_GameManUpdateDispatchTable0 LABEL DWORD
    DD GameManUpdate_004116c1
    DD GameManUpdate_00411140
    DD GameManUpdate_00411271
    DD GameManUpdate_0041143b
    DD GameManUpdate_00411105
    DD GameManUpdate_004114d5
    DD GameManUpdate_00411565
    DD GameManUpdate_004115d0
    DD GameManUpdate_00411640
PUBLIC _GameManUpdateDispatchTable1
_GameManUpdateDispatchTable1 LABEL DWORD
    DD GameManUpdate_00411fd1
    DD GameManUpdate_004125a9
    DD GameManUpdate_0041241d
    DD GameManUpdate_0041273e
    DD GameManUpdate_0041287e
    DD GameManUpdate_004128c0
    DD GameManUpdate_00412939
    DD GameManUpdate_004129f5
    DD GameManUpdate_00412af6
    DD GameManUpdate_00412c6b
    DD GameManUpdate_00412ed8
    DD GameManUpdate_00412fd9
    DD GameManUpdate_00413057
    DD GameManUpdate_004139f8
    DD GameManUpdate_00413d11

END
