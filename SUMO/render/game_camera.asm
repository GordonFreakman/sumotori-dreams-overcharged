.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?CalculateCenterOfMassPosition@GameMan@@QAE?AUVector3@@XZ:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?Normalized@Vector3@@QAE?AU1@XZ:PROC
EXTERN ?Rotate@Vector3@@QAEXAAU1@@Z:PROC
EXTERN ?RotateColumns01@Matrix3@@QAEXM@Z:PROC
EXTERN ?RotateColumns02@Matrix3@@QAEXM@Z:PROC
EXTERN ?RotateColumns12@Matrix3@@QAEXM@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?SetIdentity@Matrix3@@QAEXXZ:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?g_gameAlternateCameraMode@@3HA:DWORD
EXTERN ?g_gameCameraAcceleration@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraAimDamping@@3MB:DWORD
EXTERN ?g_gameCameraAngles@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraAngularVelocity@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraDistanceBias@@3MB:DWORD
EXTERN ?g_gameCameraDistanceScale@@3MA:DWORD
EXTERN ?g_gameCameraFacingEpsilon@@3MB:DWORD
EXTERN ?g_gameCameraFastSpringDistanceSquared@@3NB:QWORD
EXTERN ?g_gameCameraFocus@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraGroupRadiusScale@@3MB:DWORD
EXTERN ?g_gameCameraHeightBaseline@@3MB:DWORD
EXTERN ?g_gameCameraHeightOffset@@3MB:DWORD
EXTERN ?g_gameCameraHeightScale@@3MB:DWORD
EXTERN ?g_gameCameraInputB@@3MA:DWORD
EXTERN ?g_gameCameraInputDamping@@3MB:DWORD
EXTERN ?g_gameCameraInputOffsetScale@@3MB:DWORD
EXTERN ?g_gameCameraMinimumDistance@@3MB:DWORD
EXTERN ?g_gameCameraMinimumDistanceScale@@3MB:DWORD
EXTERN ?g_gameCameraMoveScale@@3MA:DWORD
EXTERN ?g_gameCameraNormalTurnStep@@3MB:DWORD
EXTERN ?g_gameCameraPitchResponse@@3MB:DWORD
EXTERN ?g_gameCameraPosition@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraTurnScale@@3MA:DWORD
EXTERN ?g_gameCameraVelocity@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraVelocityDamping@@3MB:DWORD
EXTERN ?g_gameCameraWorldPosition@@3UVector3@@A:BYTE
EXTERN ?g_gameCameraYawResponse@@3MB:DWORD
EXTERN ?g_gameCameraZoomStep@@3MB:DWORD
EXTERN ?g_gameCameraZoomVelocity@@3MA:DWORD
EXTERN ?g_gameInverseViewMatrix@@3UMatrix3@@A:BYTE
EXTERN ?g_gameKeyDown@@3PAEA:BYTE
EXTERN ?g_gameManPoseImpulseGain@@3MB:DWORD
EXTERN ?g_gameMen@@3PAUGameMan@@A:BYTE
EXTERN ?g_gameMode@@3HA:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_gameProjectileSpin@@3MB:DWORD
EXTERN ?g_levelLoadState@@3PAHA:BYTE
EXTERN ?g_nextGameMan@@3PAUGameMan@@A:DWORD
EXTERN ?g_wavyTextCosineRate@@3MB:DWORD
EXTERN ?g_wavyTextPhaseScale@@3MB:DWORD
EXTERN ?g_wavyTextTimeScale@@3MB:DWORD
EXTERN __real@40400000:DWORD
EXTERN _cos:PROC
EXTERN _sin:PROC
EXTERN _sqrt:PROC

.code

; FUNCTION: SUMO 0x00402f1b
; FUNCTION: EDITOR 0x00402f1b
PUBLIC ?UpdateGameCamera@@YAXXZ
?UpdateGameCamera@@YAXXZ PROC
    DB 055h
    DB 08dh, 06ch, 024h, 088h
    DB 081h, 0ech, 098h, 000h, 000h, 000h
    DB 0a1h
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 044h
    DB 053h
    DB 056h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 048h
    DB 057h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 044h
    DB 08dh, 07dh, 02ch
    DB 0d9h, 05dh, 04ch
    DB 0b9h
    DD ?g_gameMen@@3PAUGameMan@@A
    DB 02bh, 0c1h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 099h
    DB 0beh, 030h, 007h, 000h, 000h
    DB 0f7h, 0feh
    DB 0c7h, 045h, 070h, 000h, 000h, 048h, 042h
    DB 0bbh
    DD ?g_gameCameraFocus@@3UVector3@@A
    DB 085h, 0c0h
    DB 00fh, 08eh, 084h, 001h, 000h, 000h
    DB 08bh, 0f3h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 02ch
    DB 0d9h, 05dh, 044h
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 048h
    DB 0a5h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 02ch
    DB 0d9h, 05dh, 064h
    DB 08dh, 07dh, 050h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 068h
    DB 0a5h
    DB 0a5h
    DB 08dh, 075h, 044h
    DB 08dh, 07dh, 0ech
    DB 0a5h
    DB 0a5h
    DB 0c7h, 045h, 05ch, 0cdh, 0cch, 0cch, 03dh
    DB 0c7h, 045h, 028h, 00ch, 013h, 09ah, 079h
    DB 0a5h
    DB 0c7h, 045h, 070h, 040h, 000h, 000h, 000h
    DB 0ebh, 005h
    DB 0b9h
    DD ?g_gameMen@@3PAUGameMan@@A
    DB 039h, 00dh
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 0d9h, 0eeh
    DB 08dh, 075h, 060h
    DB 0d9h, 05dh, 06ch
    DB 08dh, 07dh, 044h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 076h, 07ch
    DB 0c7h, 045h, 074h
    DD ?g_gameMen@@3PAUGameMan@@A + 0c8h
    DB 08bh, 04dh, 074h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 045h, 010h
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 05dh, 06ch
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 03dh
    DB 08bh, 04dh, 074h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d9h, 05dh, 06ch
    DB 08bh, 04dh, 074h
    DB 08dh, 045h, 004h
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 045h, 0e0h
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Normalized@Vector3@@QAE?AU1@XZ
    DB 08bh, 0f0h
    DB 08dh, 07dh, 044h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 081h, 045h, 074h, 030h, 007h, 000h, 000h
    DB 08bh, 045h, 074h
    DB 005h, 038h, 0ffh, 0ffh, 0ffh
    DB 03bh, 005h
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 072h, 08bh
    DB 0d9h, 045h, 028h
    DB 0d8h, 05dh, 06ch
    DB 0d9h, 045h, 05ch
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 01ah
    DB 0d8h, 00dh
    DD ?g_gameManPoseImpulseGain@@3MB
    DB 08dh, 075h, 050h
    DB 08dh, 07dh, 02ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 075h, 0ech
    DB 08dh, 07dh, 044h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0ebh, 00ch
    DB 08bh, 045h, 06ch
    DB 0d8h, 00dh
    DD ?g_wavyTextPhaseScale@@3MB
    DB 089h, 045h, 028h
    DB 08dh, 075h, 02ch
    DB 0d9h, 05dh, 05ch
    DB 08dh, 07dh, 050h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 075h, 044h
    DB 08dh, 07dh, 0ech
    DB 0a5h
    DB 08dh, 045h, 05ch
    DB 050h
    DB 0a5h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 08dh, 04dh, 044h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0ffh, 04dh, 070h
    DB 0d9h, 045h, 02ch
    DB 0d8h, 000h
    DB 0d9h, 05dh, 02ch
    DB 0d9h, 045h, 030h
    DB 0d8h, 040h, 004h
    DB 0d9h, 05dh, 030h
    DB 0d9h, 045h, 034h
    DB 0d8h, 040h, 008h
    DB 0d9h, 05dh, 034h
    DB 00fh, 085h, 0ebh, 0feh, 0ffh, 0ffh
    DB 0d9h, 045h, 06ch
    DB 08dh, 075h, 050h
    DB 08dh, 07dh, 02ch
    DB 0a5h
    DB 0a5h
    DB 051h
    DB 051h
    DB 0a5h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 059h
    DB 059h
    DB 0d9h, 05dh, 070h
    DB 0b9h
    DD ?g_gameMen@@3PAUGameMan@@A
    DB 0a1h
    DD ?g_gameMode@@3HA
    DB 0d9h, 0eeh
    DB 08bh, 0fbh
    DB 0d9h, 05dh, 06ch
    DB 08bh, 01dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 083h, 0fbh, 002h
    DB 08dh, 075h, 02ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 074h, 00ah
    DB 083h, 0fbh, 00bh
    DB 074h, 005h
    DB 083h, 0f8h, 003h
    DB 075h, 005h
    DB 083h, 0f8h, 001h
    DB 075h, 022h
    DB 083h, 0fbh, 001h
    DB 0d9h, 0eeh
    DB 0d9h, 01dh
    DD ?g_gameCameraTurnScale@@3MA
    DB 075h, 04fh
    DB 083h, 03dh
    DD ?g_gameAlternateCameraMode@@3HA
    DB 000h
    DB 075h, 046h
    DB 0c7h, 005h
    DD ?g_gameCameraTurnScale@@3MA
    DB 000h, 000h, 000h, 03fh
    DB 0ebh, 03ah
    DB 083h, 0fbh, 00bh
    DB 0d9h, 0eeh
    DB 0d9h, 01dh
    DD ?g_gameCameraTurnScale@@3MA
    DB 0d9h, 005h
    DD ?g_gameCameraNormalTurnStep@@3MB
    DB 075h, 008h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_wavyTextTimeScale@@3MB
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 49h
    DB 000h
    DB 074h, 003h
    DB 0d9h, 055h, 06ch
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 47h
    DB 000h
    DB 074h, 008h
    DB 0d9h, 045h, 06ch
    DB 0d8h, 0e1h
    DB 0d9h, 05dh, 06ch
    DB 0ddh, 0d8h
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 4eh
    DB 000h
    DB 0d9h, 005h
    DD ?g_gameCameraZoomVelocity@@3MA
    DB 074h, 006h
    DB 0d8h, 025h
    DD ?g_gameCameraZoomStep@@3MB
    DB 080h, 03dh
    DD ?g_gameKeyDown@@3PAEA + 4ah
    DB 000h
    DB 074h, 006h
    DB 0d8h, 005h
    DD ?g_gameCameraZoomStep@@3MB
    DB 0d8h, 00dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0d9h, 015h
    DD ?g_gameCameraZoomVelocity@@3MA
    DB 0d9h, 005h
    DD ?g_gameCameraDistanceScale@@3MA
    DB 0d8h, 0c1h
    DB 0d9h, 01dh
    DD ?g_gameCameraDistanceScale@@3MA
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameCameraMinimumDistance@@3MB
    DB 0d9h, 005h
    DD ?g_gameCameraDistanceScale@@3MA
    DB 0d8h, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 008h
    DB 0d9h, 01dh
    DD ?g_gameCameraDistanceScale@@3MA
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameCameraInputB@@3MA
    DB 0a1h
    DD ?g_nextGameMan@@3PAUGameMan@@A
    DB 03bh, 0c1h
    DB 0d8h, 045h, 06ch
    DB 08dh, 075h, 044h
    DB 08dh, 07dh, 0ech
    DB 0d9h, 01dh
    DD ?g_gameCameraInputB@@3MA
    DB 0c7h, 045h, 064h, 000h, 000h, 020h, 042h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 068h, 000h, 000h, 0c8h, 0c2h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 048h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 060h
    DB 0a5h
    DB 0a5h
    DB 08dh, 075h, 060h
    DB 08dh, 07dh, 044h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 00fh, 086h, 0b4h, 002h, 000h, 000h
    DB 02bh, 0c1h
    DB 099h
    DB 0b9h, 030h, 007h, 000h, 000h
    DB 0f7h, 0f9h
    DB 0beh
    DD ?g_gameMen@@3PAUGameMan@@A + 0c8h
    DB 08dh, 07dh, 0f8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 085h, 0c0h
    DB 00fh, 08ch, 0abh, 000h, 000h, 000h
    DB 083h, 0f8h, 001h
    DB 00fh, 08eh, 092h, 000h, 000h, 000h
    DB 083h, 0f8h, 002h
    DB 074h, 035h
    DB 00fh, 08eh, 097h, 000h, 000h, 000h
    DB 083h, 0f8h, 004h
    DB 00fh, 08fh, 08eh, 000h, 000h, 000h
    DB 0d9h, 005h
    DD ?g_gameCameraDistanceScale@@3MA
    DB 08dh, 075h, 02ch
    DB 0d8h, 00dh
    DD ?g_gameProjectileSpin@@3MB
    DB 08dh, 07dh, 0f8h
    DB 0a5h
    DB 0a5h
    DB 0d8h, 04dh, 070h
    DB 0a5h
    DB 0d8h, 00dh
    DD ?g_gameCameraGroupRadiusScale@@3MB
    DB 0d9h, 05dh, 074h
    DB 08dh, 075h, 02ch
    DB 0ebh, 062h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 0b9h
    DD ?g_gameMen@@3PAUGameMan@@A + 730h
    call ?CalculateCenterOfMassPosition@GameMan@@QAE?AUVector3@@XZ
    DB 08bh, 0f0h
    DB 08dh, 07dh, 004h
    DB 0a5h
    DB 08dh, 045h, 004h
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 0e0h
    DB 050h
    DB 08dh, 04dh, 0f8h
    DB 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 00dh
    DD ?g_wavyTextCosineRate@@3MB
    DB 0d9h, 005h
    DD ?g_gameCameraDistanceScale@@3MA
    DB 059h
    DB 0d8h, 00dh
    DD __real@40400000
    DB 059h
    DB 0deh, 0c1h
    DB 0d8h, 025h
    DD ?g_gameCameraDistanceBias@@3MB
    DB 0d9h, 05dh, 074h
    DB 0ebh, 010h
    DB 08dh, 075h, 0f8h
    DB 0c7h, 045h, 074h, 000h, 000h, 048h, 042h
    DB 08dh, 07dh, 004h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 005h
    DD ?g_gameCameraDistanceScale@@3MA
    DB 0d8h, 00dh
    DD ?g_gameCameraMinimumDistanceScale@@3MB
    DB 0d9h, 045h, 074h
    DB 0d8h, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 005h
    DB 0d9h, 05dh, 074h
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 08dh, 045h, 0f8h
    DB 050h
    DB 08dh, 045h, 060h
    DB 050h
    DB 08dh, 04dh, 004h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 0d9h, 045h, 068h
    DB 0d8h, 04dh, 068h
    DB 0d9h, 045h, 060h
    DB 0d8h, 04dh, 060h
    DB 0deh, 0c1h
    DB 0d8h, 01dh
    DD ?g_gameCameraFacingEpsilon@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 01ah
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 050h, 000h, 000h, 080h, 0bfh
    DB 0d9h, 05dh, 054h
    DB 08dh, 075h, 050h
    DB 0d9h, 0e8h
    DB 08dh, 07dh, 060h
    DB 0d9h, 05dh, 058h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 04dh, 060h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 083h, 03dh
    DD ?g_gameMode@@3HA
    DB 003h
    DB 075h, 018h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 050h
    DB 0d9h, 05dh, 050h
    DB 08dh, 07dh, 060h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 058h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 005h
    DD ?g_gameCameraMoveScale@@3MA
    DB 051h
    DB 0d8h, 025h
    DD ?g_gameCameraTurnScale@@3MA
    DB 051h
    DB 0d9h, 055h, 070h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 028h
    DB 0d9h, 045h, 070h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 045h, 01ch
    DB 0d9h, 0eeh
    DB 0d9h, 01ch, 024h
    DB 0d9h, 045h, 028h
    DB 051h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 0d9h, 0eeh
    DB 08bh, 0f0h
    DB 0d9h, 05dh, 038h
    DB 08dh, 07dh, 050h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 040h
    DB 0a5h
    DB 0a5h
    DB 0c7h, 045h, 03ch, 000h, 000h, 040h, 03fh
    DB 08dh, 075h, 038h
    DB 08dh, 07dh, 010h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 08dh, 045h, 010h
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 08dh, 04dh, 050h
    DB 0a5h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 050h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 058h
    DB 0d8h, 04dh, 068h
    DB 0d9h, 045h, 050h
    DB 08dh, 075h, 038h
    DB 0d8h, 04dh, 060h
    DB 08dh, 07dh, 010h
    DB 08dh, 045h, 010h
    DB 050h
    DB 0deh, 0c1h
    DB 08dh, 04dh, 050h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 064h
    DB 0deh, 0c1h
    DB 0d8h, 075h, 074h
    DB 0d8h, 00dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0d8h, 005h
    DD ?g_gameCameraMoveScale@@3MA
    DB 0d9h, 01dh
    DD ?g_gameCameraMoveScale@@3MA
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 038h
    DB 0d9h, 005h
    DD ?g_gameCameraInputB@@3MA
    DB 0d8h, 005h
    DD ?g_gameCameraTurnScale@@3MA
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 040h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Rotate@Vector3@@QAEXAAU1@@Z
    DB 0d9h, 045h, 050h
    DB 0d8h, 04dh, 074h
    DB 0d9h, 05dh, 050h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 074h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 045h, 058h
    DB 08dh, 045h, 004h
    DB 0d8h, 04dh, 074h
    DB 050h
    DB 08dh, 045h, 0e0h
    DB 050h
    DB 08dh, 04dh, 0f8h
    DB 0d9h, 05dh, 058h
    DB 0c7h, 045h, 070h, 000h, 000h, 000h, 03fh
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 0ech
    DB 0a5h
    DB 08dh, 045h, 050h
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 08dh, 04dh, 0ech
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 01dh
    DD ?g_levelLoadState@@3PAHA + 10h
    DB 0d9h, 045h, 074h
    DB 08bh, 0f0h
    DB 0d8h, 025h
    DD ?g_gameCameraHeightBaseline@@3MB
    DB 08dh, 07dh, 044h
    DB 0a5h
    DB 0a5h
    DB 0d8h, 00dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0a5h
    DB 0d8h, 045h, 030h
    DB 0d8h, 005h
    DD ?g_gameCameraHeightOffset@@3MB
    DB 0d9h, 05dh, 048h
    DB 083h, 0fbh, 002h
    DB 0c7h, 045h, 05ch, 052h, 049h, 09dh, 039h
    DB 075h, 02ch
    DB 068h
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 08dh, 045h, 01ch
    DB 050h
    DB 08dh, 04dh, 044h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0dch, 01dh
    DD ?g_gameCameraFastSpringDistanceSquared@@3NB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 007h
    DB 0c7h, 045h, 05ch, 06fh, 012h, 003h, 03bh
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 08dh, 045h, 05ch
    DB 050h
    DB 08dh, 045h, 0e0h
    DB 050h
    DB 068h
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 08dh, 045h, 004h
    DB 050h
    DB 068h
    DD ?g_gameCameraAngularVelocity@@3UVector3@@A
    DB 08dh, 045h, 010h
    DB 050h
    DB 08dh, 04dh, 044h
    DB 0c7h, 045h, 070h, 000h, 000h, 0f0h, 041h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d8h, 000h
    DB 08dh, 075h, 038h
    DB 08dh, 07dh, 010h
    DB 08dh, 04dh, 010h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d8h, 040h, 004h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 8
    DB 0d8h, 040h, 008h
    DB 08dh, 045h, 05ch
    DB 050h
    DB 08dh, 045h, 060h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A + 8
    DB 050h
    DB 0d9h, 045h, 06ch
    DB 068h
    DD ?g_gameInverseViewMatrix@@3UMatrix3@@A
    DB 0d8h, 00dh
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 08dh, 045h, 01ch
    DB 050h
    DB 0d9h, 05dh, 038h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 03ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 040h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 050h
    DB 08dh, 045h, 0e0h
    DB 050h
    DB 068h
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 08dh, 045h, 004h
    DB 050h
    DB 08dh, 04dh, 044h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d8h, 000h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d8h, 040h, 004h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 8
    DB 0d8h, 040h, 008h
    DB 0d9h, 005h
    DD ?g_gameCameraVelocityDamping@@3MB
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d8h, 0c9h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d8h, 0c9h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d9h, 0c1h
    DB 08dh, 075h, 044h
    DB 0d8h, 0c9h
    DB 0bfh
    DD ?g_gameCameraAngularVelocity@@3UVector3@@A
    DB 0a5h
    DB 0d9h, 01dh
    DD ?g_gameCameraVelocity@@3UVector3@@A + 8
    DB 0a5h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 045h, 01ch
    DB 050h
    DB 0a5h
    DB 0bfh
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 057h
    DB 08dh, 045h, 0e0h
    DB 050h
    DB 08dh, 04dh, 044h
    DB 0c7h, 045h, 070h, 00ah, 0d7h, 023h, 03ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 083h, 0fbh, 00ah
    DB 0d9h, 005h
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 0d8h, 000h
    DB 0d9h, 01dh
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_gameCameraPosition@@3UVector3@@A + 4
    DB 0d8h, 040h, 004h
    DB 0d9h, 01dh
    DD ?g_gameCameraPosition@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_gameCameraPosition@@3UVector3@@A + 8
    DB 0d8h, 040h, 008h
    DB 0d9h, 005h
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 0d8h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A
    DB 0d9h, 01dh
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_gameCameraPosition@@3UVector3@@A + 4
    DB 0d8h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 4
    DB 0d9h, 01dh
    DD ?g_gameCameraPosition@@3UVector3@@A + 4
    DB 0d8h, 005h
    DD ?g_gameCameraVelocity@@3UVector3@@A + 8
    DB 0d9h, 01dh
    DD ?g_gameCameraPosition@@3UVector3@@A + 8
    DB 075h, 03eh
    DB 0c7h, 045h, 038h, 000h, 000h, 001h, 0c3h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 03ch, 000h, 000h, 088h, 041h
    DB 0c7h, 045h, 040h, 000h, 000h, 0c0h, 040h
    DB 08dh, 075h, 038h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 040h
    DB 0c7h, 045h, 038h, 0cdh, 0cch, 04ch, 03dh
    DB 0c7h, 045h, 03ch, 02ah, 020h, 0d5h, 0bfh
    DB 08dh, 075h, 038h
    DB 0bfh
    DD ?g_gameCameraAngles@@3UVector3@@A
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0bfh
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 08bh, 0f7h
    DB 0bfh
    DD ?g_gameCameraWorldPosition@@3UVector3@@A
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0beh
    DD ?g_gameInverseViewMatrix@@3UMatrix3@@A
    DB 08bh, 0ceh
    call ?SetIdentity@Matrix3@@QAEXXZ
    DB 051h
    DB 0d9h, 005h
    DD ?g_gameCameraAngles@@3UVector3@@A
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    call ?RotateColumns12@Matrix3@@QAEXM@Z
    DB 0d9h, 005h
    DD ?g_gameCameraAngles@@3UVector3@@A + 4
    DB 051h
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    call ?RotateColumns02@Matrix3@@QAEXM@Z
    DB 0d9h, 005h
    DD ?g_gameCameraAngles@@3UVector3@@A + 8
    DB 051h
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    call ?RotateColumns01@Matrix3@@QAEXM@Z
    DB 068h
    DD ?g_gameCameraPosition@@3UVector3@@A
    DB 08dh, 045h, 01ch
    DB 050h
    DB 08dh, 04dh, 0ech
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 045h, 060h
    DB 050h
    DB 08bh, 0ceh
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 0d9h, 045h, 068h
    DB 0d8h, 04dh, 068h
    DB 051h
    DB 0d9h, 045h, 064h
    DB 051h
    DB 0d8h, 04dh, 064h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 060h
    DB 0d8h, 04dh, 060h
    DB 0deh, 0c1h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 03dh
    DD ?g_gameOne@@3MB
    DB 059h
    DB 059h
    DB 0d9h, 045h, 060h
    DB 0d8h, 0c9h
    DB 0d8h, 00dh
    DD ?g_gameCameraYawResponse@@3MB
    DB 0d8h, 02dh
    DD ?g_gameCameraAcceleration@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_gameCameraAimDamping@@3MB
    DB 0d9h, 045h, 064h
    DB 0d8h, 0cbh
    DB 0d8h, 00dh
    DD ?g_gameCameraPitchResponse@@3MB
    DB 0d8h, 02dh
    DD ?g_gameCameraAcceleration@@3UVector3@@A
    DB 0d8h, 0c9h
    DB 0d9h, 01dh
    DD ?g_gameCameraAcceleration@@3UVector3@@A
    DB 0d9h, 0c1h
    DB 0d8h, 0c9h
    DB 0d9h, 01dh
    DD ?g_gameCameraAcceleration@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_gameCameraAcceleration@@3UVector3@@A + 8
    DB 0d8h, 0c9h
    DB 0d9h, 01dh
    DD ?g_gameCameraAcceleration@@3UVector3@@A + 8
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameCameraAcceleration@@3UVector3@@A
    DB 0d8h, 005h
    DD ?g_gameCameraAngles@@3UVector3@@A
    DB 0d9h, 01dh
    DD ?g_gameCameraAngles@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_gameCameraAcceleration@@3UVector3@@A + 4
    DB 0d8h, 005h
    DD ?g_gameCameraAngles@@3UVector3@@A + 4
    DB 0d9h, 01dh
    DD ?g_gameCameraAngles@@3UVector3@@A + 4
    DB 0d9h, 005h
    DD ?g_gameCameraAcceleration@@3UVector3@@A + 8
    DB 0d8h, 005h
    DD ?g_gameCameraAngles@@3UVector3@@A + 8
    DB 05fh
    DB 0d9h, 01dh
    DD ?g_gameCameraAngles@@3UVector3@@A + 8
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 078h
    DB 0c9h
    DB 0c3h
?UpdateGameCamera@@YAXXZ ENDP

END
