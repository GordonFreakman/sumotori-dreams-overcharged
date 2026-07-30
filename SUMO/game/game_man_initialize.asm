.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??YVector3@@QAEXAAU0@@Z:PROC
EXTERN ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z:PROC
EXTERN ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z:PROC
EXTERN ?InitializeJointTransforms@GameManPose@@QAEXPAUGameMan@@@Z:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?Next@GameRandomGenerator@@QAEMXZ:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?RotateRows02@Matrix3@@QAEXM@Z:PROC
EXTERN ?ScaleMassProperties@GameBox@@QAEXM@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?g_boxWaterDiagonalScale@@3MB:DWORD
EXTERN ?g_gameBoxYScale@@3MB:DWORD
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameCameraAimDamping@@3MB:DWORD
EXTERN ?g_gameCameraHeightScale@@3MB:DWORD
EXTERN ?g_gameCameraInputOffsetScale@@3MB:DWORD
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameFloorHalfExtent@@3MB:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_gameProjectileDefaultValue@@3MB:DWORD
EXTERN ?g_gameProjectileHalfSize@@3MB:DWORD
EXTERN ?g_gameProjectileSpin@@3MB:DWORD
EXTERN ?g_gameTwo@@3MB:DWORD
EXTERN ?g_randomHalf@@3MB:DWORD
EXTERN ?g_simulationRandom@@3UGameRandomGenerator@@A:BYTE
EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN ?g_waterNeighborCoupling@@3MB:DWORD
EXTERN ?g_wavyTextPhaseScale@@3MB:DWORD
EXTERN __ftol2:PROC
EXTERN __real@3ba3d70a:DWORD
EXTERN __real@3e23d70b:DWORD
EXTERN __real@3e800000:DWORD
EXTERN __real@3eb851ec:DWORD
EXTERN __real@3f23d70b:DWORD
EXTERN __real@3f4f5c28:DWORD
EXTERN __real@3fd9999a:DWORD
EXTERN __real@3ff33333:DWORD
EXTERN __real@400ccccd:DWORD
EXTERN __real@40400000:DWORD
EXTERN __real@404ccccd:DWORD
EXTERN __real@42f00000:DWORD
EXTERN __real@43960000:DWORD
EXTERN __real@bf8ccccd:DWORD
EXTERN __real@bfc00000:DWORD
EXTERN __real@bfe66666:DWORD
EXTERN _memset:PROC
EXTERN _sqrt:PROC

.const
PUBLIC __real@3efae147
__real@3efae147 DD 03efae147h
PUBLIC __real@3f75dcc7
__real@3f75dcc7 DD 03f75dcc7h
PUBLIC __real@3f41c433
__real@3f41c433 DD 03f41c433h
PUBLIC __real@c0fccccd
__real@c0fccccd DD 0c0fccccdh

.code

; FUNCTION: SUMO 0x0040ebeb
; FUNCTION: EDITOR 0x0040ec0d
PUBLIC ?Initialize@GameMan@@QAEXAAUVector3@@MHH@Z
?Initialize@GameMan@@QAEXAAUVector3@@MHH@Z PROC
    DB 055h
    DB 08dh, 06ch, 024h, 098h
    DB 081h, 0ech, 0b8h, 001h, 000h, 000h
    DB 053h
    DB 056h
    DB 057h
    DB 08bh, 0d9h
    DB 033h, 0c0h
    DB 068h, 030h, 007h, 000h, 000h
    DB 050h
    DB 0b9h, 0cch, 001h, 000h, 000h
    DB 08bh, 0fbh
    DB 053h
    DB 089h, 05dh, 038h
    DB 0f3h, 0abh
    call _memset
    DB 0beh
    DD ?g_simulationRandom@@3UGameRandomGenerator@@A
    DB 083h, 0c4h, 00ch
    DB 08bh, 0ceh
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 005h
    DD ?g_gameOne@@3MB
    DB 0d8h, 00dh
    DD __real@43960000
    call __ftol2
    DB 08bh, 0ceh
    DB 089h, 083h, 018h, 007h, 000h, 000h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 005h
    DD ?g_gameOne@@3MB
    DB 0d8h, 00dh
    DD __real@43960000
    call __ftol2
    DB 08bh, 0ceh
    DB 089h, 083h, 01ch, 007h, 000h, 000h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 00dh
    DD ?g_gameFloorHalfExtent@@3MB
    call __ftol2
    DB 083h, 0a3h, 02ch, 007h, 000h, 000h, 000h
    DB 08bh, 0ceh
    DB 089h, 083h, 028h, 007h, 000h, 000h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 01dh
    DD ?g_randomHalf@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 028h
    DB 08bh, 045h, 07ch
    DB 085h, 0c0h
    DB 074h, 021h
    DB 083h, 0b8h, 0fch, 006h, 000h, 000h, 002h
    DB 075h, 018h
    DB 08bh, 0ceh
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 00dh
    DD __real@42f00000
    call __ftol2
    DB 089h, 083h, 02ch, 007h, 000h, 000h
    DB 08bh, 0ceh
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0d8h, 01dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 005h
    DB 033h, 0c0h
    DB 040h
    DB 0ebh, 002h
    DB 033h, 0c0h
    DB 0ffh, 075h, 070h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 050h
    DB 0c7h, 045h, 054h, 0cdh, 0cch, 05ch, 041h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 050h
    DB 0d9h, 05dh, 058h
    DB 08dh, 07dh, 040h
    DB 089h, 083h, 024h, 007h, 000h, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 085h, 01ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 040h
    DB 0c7h, 045h, 050h, 033h, 033h, 033h, 040h
    DB 0c7h, 045h, 054h, 0cdh, 0cch, 00ch, 0c0h
    DB 0c7h, 045h, 058h, 000h, 000h, 000h, 040h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 051h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08bh, 0f0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 050h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 0d8h
    DB 0d9h, 045h, 074h
    DB 083h, 0c4h, 01ch
    DB 08dh, 04bh, 060h
    DB 0d9h, 01ch, 024h
    DB 089h, 09dh, 02ch, 0ffh, 0ffh, 0ffh
    DB 0c7h, 083h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    call ?RotateRows02@Matrix3@@QAEXM@Z
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 058h, 0cdh, 0cch, 0cch, 03dh
    DB 0d9h, 05dh, 050h
    DB 08dh, 075h, 050h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 040h
    DB 0d9h, 05dh, 054h
    DB 08dh, 045h, 040h
    DB 050h
    DB 0a5h
    DB 0a5h
    DB 08dh, 085h, 010h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04bh, 060h
    DB 0a5h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 050h
    DB 08dh, 08bh, 09ch, 000h, 000h, 000h
    call ??YVector3@@QAEXAAU0@@Z
    DB 0d9h, 0eeh
    DB 051h
    DB 0d9h, 05dh, 050h
    DB 08dh, 075h, 050h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 054h, 000h, 000h, 0f0h, 041h
    DB 0d9h, 05dh, 058h
    DB 0c7h, 083h, 0c0h, 000h, 000h, 000h, 004h, 000h, 000h, 000h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 0c7h, 083h, 0c4h, 000h, 000h, 000h, 00ah, 0d7h, 023h, 03ch
    DB 0d9h, 01ch, 024h
    DB 0c7h, 045h, 05ch, 0cdh, 0cch, 02ch, 040h
    DB 0c7h, 045h, 060h, 0cdh, 0cch, 00ch, 0c0h
    DB 0ffh, 075h, 078h
    DB 0c7h, 045h, 064h, 000h, 000h, 0c0h, 03fh
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 05ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 083h, 0c4h, 01ch
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 060h, 000h, 000h, 010h, 042h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 075h, 05ch
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 054h, 000h, 000h, 0c0h, 0bfh
    DB 0d9h, 05dh, 064h
    DB 089h, 045h, 030h
    DB 0d9h, 005h
    DD ?g_gameProjectileHalfSize@@3MB
    DB 0c7h, 080h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0d9h, 055h, 050h
    DB 0c7h, 080h, 0c0h, 000h, 000h, 000h, 004h, 000h, 000h, 000h
    DB 0d9h, 05dh, 058h
    DB 0c7h, 080h, 0c4h, 000h, 000h, 000h, 00ah, 0d7h, 023h, 03ch
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 050h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 0c7h, 080h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0c7h, 045h, 060h, 09ah, 099h, 019h, 040h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 089h, 045h, 074h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 089h, 018h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 083h, 0c7h, 008h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 055h, 060h
    DB 083h, 0c7h, 020h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0d9h, 0e8h
    DB 0a5h
    DB 08bh, 04dh, 030h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0eeh
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 083h, 0c7h, 038h
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 05ch
    DB 083h, 0c7h, 014h
    DB 0c7h, 045h, 060h, 0cdh, 0cch, 00ch, 0c0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0d9h, 0eeh
    DB 06ah, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 060h
    DB 083h, 0c7h, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0d9h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0eeh
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 083h, 0c7h, 044h
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0d9h, 005h
    DD ?g_waterNeighborCoupling@@3MB
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3e23d70b
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 001h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 0d9h, 0eeh
    DB 08bh, 045h, 030h
    DB 0d9h, 05dh, 05ch
    DB 0bbh, 0f4h, 000h, 000h, 000h
    DB 0d9h, 0eeh
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 064h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 089h, 001h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 0c7h, 045h, 060h, 0cdh, 0cch, 02ch, 040h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 055h, 060h
    DB 0d9h, 0eeh
    DB 083h, 0c7h, 020h
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0d9h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 064h
    DB 08bh, 04dh, 074h
    DB 0d9h, 0eeh
    DB 083h, 0c7h, 038h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0eeh
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 064h
    DB 089h, 048h, 004h
    DB 0d9h, 0eeh
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 014h
    DB 0c7h, 045h, 060h, 000h, 000h, 0c0h, 0bfh
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 060h
    DB 083h, 0c7h, 02ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0d9h, 0e8h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0d9h, 0eeh
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 083h, 0c7h, 044h
    DB 0d9h, 05dh, 064h
    DB 08dh, 075h, 05ch
    DB 0d9h, 005h
    DD __real@3efae147
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 06ah, 000h
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3f4f5c28
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 074h
    DB 083h, 0c4h, 030h
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 064h
    DB 0c7h, 045h, 060h, 033h, 033h, 033h, 03fh
    DB 0d9h, 005h
    DD ?g_gameProjectileHalfSize@@3MB
    DB 0c7h, 045h, 054h, 033h, 033h, 033h, 0bfh
    DB 0d9h, 055h, 050h
    DB 0c7h, 045h, 058h, 000h, 000h, 000h, 040h
    DB 0d9h, 005h
    DD __real@400ccccd
    DB 0c7h, 045h, 000h, 033h, 033h, 013h, 0c0h
    DB 0d9h, 055h, 094h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 098h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 004h
    DB 0d9h, 095h, 07ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 080h
    DB 0d9h, 0c1h
    DB 0c7h, 045h, 0e8h, 000h, 000h, 040h, 0c0h
    DB 0d9h, 05dh, 0e4h
    DB 0c7h, 045h, 0b8h, 000h, 000h, 000h, 0c0h
    DB 0d9h, 0c1h
    DB 0c7h, 085h, 038h, 0ffh, 0ffh, 0ffh, 0cdh, 0cch, 0cch, 03dh
    DB 0d9h, 05dh, 0ech
    DB 0c7h, 045h, 0a4h, 09ah, 099h, 019h, 0bfh
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 024h, 033h, 033h, 013h, 040h
    DB 0d9h, 09dh, 060h, 0ffh, 0ffh, 0ffh
    DB 0c7h, 085h, 070h, 0ffh, 0ffh, 0ffh, 000h, 000h, 020h, 0c0h
    DB 0c7h, 085h, 040h, 0ffh, 0ffh, 0ffh, 0cdh, 0cch, 04ch, 0beh
    DB 0c7h, 045h, 0c4h, 066h, 066h, 0e6h, 0bfh
    DB 0d9h, 095h, 064h, 0ffh, 0ffh, 0ffh
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 068h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0cch
    DB 0d9h, 005h
    DD ?g_gameBoxYScale@@3MB
    DB 0d9h, 055h, 0d0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0d4h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 04ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 050h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0bch
    DB 0d9h, 095h, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0a0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 020h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 028h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 084h
    DB 0d9h, 055h, 088h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 08ch
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 058h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 05ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 074h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 03ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 095h, 044h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 018h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 01ch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 008h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 00ch
    DB 0d9h, 055h, 010h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 055h, 0f4h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0dch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0e0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0c0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0c8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0a8h
    DB 0d9h, 05dh, 0ach
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0b0h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 03ch, 002h, 000h, 000h, 000h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 074h
    DB 0ffh, 075h, 070h
    DB 0d8h, 00dh
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 08dh, 075h, 05ch
    DB 08dh, 0bdh, 0ech, 0feh, 0ffh, 0ffh
    DB 08dh, 085h, 0e0h, 0feh, 0ffh, 0ffh
    DB 0d9h, 055h, 034h
    DB 050h
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a5h
    DB 08dh, 08dh, 0ech, 0feh, 0ffh, 0ffh
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 051h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08bh, 0f0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 050h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 0f0h
    DB 0d9h, 005h
    DD __real@40400000
    DB 083h, 0c4h, 01ch
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    DB 089h, 075h, 02ch
    call ?ScaleMassProperties@GameBox@@QAEXM@Z
    DB 08dh, 086h, 0b4h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0ffh, 075h, 070h
    DB 0d8h, 00dh
    DD ?g_randomHalf@@3MB
    DB 0c7h, 086h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0c7h, 086h, 0c0h, 000h, 000h, 000h, 003h, 000h, 000h, 000h
    DB 0c7h, 086h, 0c4h, 000h, 000h, 000h, 06fh, 012h, 003h, 03bh
    DB 0d9h, 018h
    DB 08dh, 086h, 0b8h, 000h, 000h, 000h
    DB 0d9h, 000h
    DB 0c7h, 086h, 0c8h, 000h, 000h, 000h, 000h, 000h, 0c8h, 043h
    DB 0dch, 0c0h
    DB 08dh, 075h, 090h
    DB 08dh, 0bdh, 0f8h, 0feh, 0ffh, 0ffh
    DB 08dh, 08dh, 0f8h, 0feh, 0ffh, 0ffh
    DB 0d9h, 018h
    DB 08bh, 045h, 034h
    DB 089h, 045h, 090h
    DB 0a5h
    DB 0a5h
    DB 08dh, 085h, 0bch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 051h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08bh, 0f0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 0fch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 0f0h
    DB 089h, 075h, 04ch
    DB 0d9h, 005h
    DD __real@3fd9999a
    DB 083h, 0c4h, 01ch
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    call ?ScaleMassProperties@GameBox@@QAEXM@Z
    DB 0d9h, 045h, 074h
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0ffh, 075h, 070h
    DB 0c7h, 086h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0c7h, 086h, 0c0h, 000h, 000h, 000h, 004h, 000h, 000h, 000h
    DB 0c7h, 086h, 0c4h, 000h, 000h, 000h, 00ah, 0d7h, 0a3h, 03bh
    DB 0d9h, 09dh, 078h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0b5h, 078h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0bdh, 004h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 08dh, 085h, 0d4h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 004h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 051h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08bh, 0f0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 0e4h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 0c7h, 080h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0c7h, 080h, 0c0h, 000h, 000h, 000h, 004h, 000h, 000h, 000h
    DB 0c7h, 080h, 0c4h, 000h, 000h, 000h, 00ah, 0d7h, 0a3h, 03bh
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 001h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 08dh, 0b5h, 060h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 08dh, 075h, 0cch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 038h
    DB 08bh, 08dh, 02ch, 0ffh, 0ffh, 0ffh
    DB 089h, 085h, 028h, 0ffh, 0ffh, 0ffh
    DB 08bh, 045h, 074h
    DB 089h, 085h, 048h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0b5h, 048h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08dh, 070h, 008h
    DB 08dh, 0bdh, 010h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 034h
    DB 083h, 0c4h, 020h
    DB 083h, 0c7h, 014h
    DB 089h, 045h, 0b4h
    DB 08dh, 075h, 0b4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 045h, 074h
    DB 0d8h, 00dh
    DD ?g_gameCameraAimDamping@@3MB
    DB 083h, 0c7h, 02ch
    DB 08dh, 0b5h, 030h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 09dh, 030h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c1h, 02ch
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 074h
    DB 0ddh, 0d8h
    DB 089h, 045h, 09ch
    DB 083h, 0c7h, 044h
    DB 08dh, 075h, 09ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c1h, 044h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0ddh, 0d8h
    DB 06ah, 001h
    DB 0d9h, 005h
    DD __real@3f23d70b
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3eb851ec
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 04ch
    DB 059h
    DB 059h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 001h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 08bh, 045h, 074h
    DB 08dh, 075h, 020h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 08dh, 075h, 084h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 038h
    DB 08bh, 08dh, 028h, 0ffh, 0ffh, 0ffh
    DB 089h, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0b5h, 054h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08dh, 070h, 008h
    DB 08dh, 0bdh, 01ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 014h
    DB 08dh, 0b5h, 06ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 08dh, 0b5h, 03ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c1h, 02ch
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 074h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD __real@3f75dcc7
    DB 089h, 045h, 014h
    DB 083h, 0c7h, 044h
    DB 08dh, 075h, 014h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08dh, 08dh, 010h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3e800000
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0e8h
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c0h, 014h
    DB 050h
    DB 08dh, 085h, 0c8h, 0feh, 0ffh, 0ffh
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 045h, 038h
    DB 0d9h, 058h, 074h
    DB 06ah, 001h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 0d9h, 045h, 074h
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 055h, 0d8h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 02ch
    DB 089h, 001h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 08dh, 075h, 008h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 08bh, 04dh, 04ch
    DB 08dh, 075h, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 038h
    DB 08dh, 075h, 0d8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c4h, 010h
    DB 083h, 0c7h, 014h
    DB 08dh, 075h, 0c0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 0d9h, 05dh, 040h
    DB 0d9h, 005h
    DD __real@3efae147
    DB 08dh, 075h, 0a8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 044h
    DB 08dh, 075h, 040h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08dh, 08dh, 01ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3e800000
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c0h, 014h
    DB 050h
    DB 08dh, 085h, 0b0h, 0feh, 0ffh, 0ffh
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 045h, 038h
    DB 0d9h, 058h, 078h
    DB 06ah, 001h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c4h, 010h
    DB 0ffh, 04dh, 03ch
    DB 0c7h, 045h, 074h, 000h, 000h, 080h, 0bfh
    DB 00fh, 085h, 01dh, 0fbh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0c7h, 045h, 0ach, 0cdh, 0cch, 04ch, 0bfh
    DB 0d9h, 05dh, 074h
    DB 0c7h, 045h, 0dch, 033h, 033h, 033h, 0bfh
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 0e0h, 0cdh, 0cch, 04ch, 03fh
    DB 0d9h, 05dh, 040h
    DB 0c7h, 045h, 008h, 033h, 033h, 0b3h, 03fh
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 00ch, 09ah, 099h, 099h, 0beh
    DB 0c7h, 045h, 018h, 000h, 000h, 000h, 040h
    DB 0d9h, 05dh, 044h
    DB 0c7h, 085h, 044h, 0ffh, 0ffh, 0ffh, 0cdh, 0cch, 04ch, 03eh
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 0a4h, 09ah, 099h, 099h, 0beh
    DB 0d9h, 05dh, 048h
    DB 0d9h, 005h
    DD __real@3ff33333
    DB 0d9h, 055h, 0a8h
    DB 0d9h, 005h
    DD ?g_wavyTextPhaseScale@@3MB
    DB 0d9h, 055h, 0b0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0c0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0c4h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0c8h
    DB 0d9h, 0c1h
    DB 0d9h, 05dh, 0d8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f4h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0f8h
    DB 0d9h, 055h, 010h
    DB 0ddh, 0d8h
    DB 0ddh, 0d8h
    DB 0d9h, 005h
    DD ?g_gameProjectileSpin@@3MB
    DB 0d9h, 055h, 01ch
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 040h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 070h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 074h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 058h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 05ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 088h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 08ch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 024h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 028h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0a0h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 034h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 038h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0b4h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 0b8h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0bch
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 04ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 050h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0d0h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0d4h
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 060h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0e8h
    DB 0d9h, 09dh, 064h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 03ch, 002h, 000h, 000h, 000h
    DB 0d9h, 09dh, 068h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0e8h
    DB 0d9h, 05dh, 0ech
    DB 0d9h, 0eeh
    DB 0d9h, 09dh, 07ch, 0ffh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 080h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 004h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 094h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 098h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 060h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 064h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 050h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 058h
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 051h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 08dh, 075h, 040h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 0a8h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 083h, 0c4h, 01ch
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08dh, 075h, 0c0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 089h, 045h, 070h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 0d8h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0c7h, 080h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 083h, 0c4h, 01ch
    DB 0d9h, 005h
    DD ?g_gameProjectileDefaultValue@@3MB
    DB 08dh, 075h, 0f0h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 075h, 078h
    DB 089h, 045h, 04ch
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 083h, 0ech, 00ch
    DB 08dh, 075h, 008h
    DB 08bh, 0fch
    DB 0a5h
    DB 0a5h
    DB 0c7h, 080h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0a5h
    call ?CreateGameBox@@YAPAUGameBox@@UVector3@@0HM@Z
    DB 08bh, 075h, 04ch
    DB 0d9h, 005h
    DD __real@3ba3d70a
    DB 08bh, 055h, 070h
    DB 0d9h, 090h, 0c4h, 000h, 000h, 000h
    DB 06ah, 004h
    DB 059h
    DB 089h, 088h, 0c0h, 000h, 000h, 000h
    DB 0c7h, 080h, 0e0h, 000h, 000h, 000h, 028h, 000h, 000h, 000h
    DB 0d9h, 096h, 0c4h, 000h, 000h, 000h
    DB 089h, 08eh, 0c0h, 000h, 000h, 000h
    DB 0d9h, 09ah, 0c4h, 000h, 000h, 000h
    DB 089h, 08ah, 0c0h, 000h, 000h, 000h
    DB 0d9h, 005h
    DD ?g_gameTwo@@3MB
    DB 083h, 0c4h, 01ch
    DB 08bh, 0c8h
    DB 0d9h, 01ch, 024h
    DB 089h, 045h, 02ch
    call ?ScaleMassProperties@GameBox@@QAEXM@Z
    DB 0d9h, 005h
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 051h
    DB 08bh, 0ceh
    DB 0d9h, 01ch, 024h
    call ?ScaleMassProperties@GameBox@@QAEXM@Z
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 04dh, 030h
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 045h, 074h
    DB 0d8h, 00dh
    DD __real@404ccccd
    DB 08bh, 045h, 074h
    DB 083h, 0c7h, 014h
    DB 08dh, 075h, 014h
    DB 0d9h, 05dh, 014h
    DB 0a5h
    DB 0d9h, 045h, 074h
    DB 0a5h
    DB 0d8h, 00dh
    DD ?g_vectorZero@@3MB
    DB 0d9h, 09dh, 06ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 089h, 085h, 03ch, 0ffh, 0ffh, 0ffh
    DB 08dh, 0b5h, 03ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 044h
    DB 08dh, 0b5h, 06ch, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c1h, 044h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 04dh, 070h
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 074h
    DB 089h, 008h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d8h, 00dh
    DD __real@bfc00000
    DB 08bh, 045h, 074h
    DB 083h, 0c7h, 008h
    DB 0d9h, 09dh, 054h, 0ffh, 0ffh, 0ffh
    DB 08dh, 0b5h, 054h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0d9h, 045h, 074h
    DB 0d8h, 00dh
    DD ?g_randomHalf@@3MB
    DB 0a5h
    DB 0d9h, 05dh, 020h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 089h, 045h, 084h
    DB 08dh, 075h, 084h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 038h
    DB 08dh, 075h, 020h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c1h, 038h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0ddh, 0d8h
    DB 06ah, 001h
    DB 0d9h, 005h
    DD __real@3f75dcc7
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3efae147
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 070h
    DB 059h
    DB 059h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 045h, 074h
    DB 0d8h, 00dh
    DD ?g_boxWaterDiagonalScale@@3MB
    DB 089h, 001h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 008h
    DB 0d9h, 055h, 034h
    DB 08dh, 075h, 09ch
    DB 0d9h, 05dh, 09ch
    DB 0a5h
    DB 0d9h, 045h, 074h
    DB 0d8h, 00dh
    DD ?g_gameCameraInputOffsetScale@@3MB
    DB 0a5h
    DB 0d9h, 09dh, 030h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 020h
    DB 08dh, 0b5h, 030h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c1h, 020h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 04dh, 04ch
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 074h
    DB 083h, 0c7h, 038h
    DB 0d9h, 005h
    DD __real@bfe66666
    DB 08dh, 075h, 0b4h
    DB 0a5h
    DB 0d8h, 0c9h
    DB 0a5h
    DB 0d9h, 09dh, 048h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 05dh, 0cch
    DB 0d9h, 005h
    DD __real@3f41c433
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 014h
    DB 08dh, 0b5h, 048h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 08dh, 075h, 0cch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 044h
    DB 08dh, 0b5h, 060h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 06ah, 000h
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3e800000
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0e8h
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 04ch
    DB 08bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 001h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 045h, 034h
    DB 083h, 0c7h, 008h
    DB 08dh, 075h, 0e4h
    DB 089h, 045h, 0e4h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 074h
    DB 0d9h, 095h, 078h, 0ffh, 0ffh, 0ffh
    DB 0a5h
    DB 0d9h, 005h
    DD __real@bf8ccccd
    DB 0d8h, 0c9h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 05dh, 090h
    DB 083h, 0c7h, 020h
    DB 08bh, 04dh, 02ch
    DB 0d9h, 05dh, 05ch
    DB 08dh, 0b5h, 078h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 005h
    DD __real@3e800000
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 038h
    DB 08dh, 075h, 0fch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 048h, 004h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 014h
    DB 08dh, 075h, 090h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 02ch
    DB 08dh, 075h, 05ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c7h, 044h
    DB 08dh, 075h, 050h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 06ah, 000h
    DB 0d9h, 058h, 054h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 005h
    DD __real@3f23d70b
    DB 0d9h, 058h, 058h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 050h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 0c6h, 040h, 060h, 000h
    DB 0ffh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    call ?AlignGameBoxJointTransform@@YAXPAUGameBoxJoint@@H@Z
    DB 001h, 01dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 083h, 0c4h, 010h
    DB 0ffh, 04dh, 03ch
    DB 0c7h, 045h, 074h, 000h, 000h, 080h, 0bfh
    DB 00fh, 085h, 003h, 0fch, 0ffh, 0ffh
    DB 08bh, 055h, 038h
    DB 08bh, 0cah
    DB 0b8h, 03ch, 0f1h, 0ffh, 0ffh
    DB 08bh, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 003h, 0f0h
    DB 089h, 031h
    DB 005h, 0fch, 000h, 000h, 000h
    DB 083h, 0c1h, 004h
    DB 085h, 0c0h
    DB 07ch, 0eah
    DB 0b8h, 0a8h, 0f2h, 0ffh, 0ffh
    DB 08dh, 04ah, 03ch
    DB 08bh, 035h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 003h, 0f0h
    DB 089h, 031h
    DB 003h, 0c3h
    DB 083h, 0c1h, 004h
    DB 085h, 0c0h
    DB 07ch, 0edh
    DB 0d9h, 005h
    DD __real@c0fccccd
    DB 0c7h, 045h, 040h, 000h, 000h, 000h, 03fh
    DB 0d9h, 055h, 044h
    DB 08dh, 07ah, 07ch
    DB 0d9h, 092h, 0f0h, 000h, 000h, 000h
    DB 08dh, 075h, 040h
    DB 0d9h, 0eeh
    DB 052h
    DB 0d9h, 05dh, 048h
    DB 08dh, 08ah, 04ch, 001h, 000h, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 048h
    DB 0c7h, 045h, 040h, 000h, 000h, 000h, 0bfh
    DB 08dh, 0bah, 088h, 000h, 000h, 000h
    DB 08dh, 075h, 040h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    call ?InitializeJointTransforms@GameManPose@@QAEXPAUGameMan@@@Z
    DB 08bh, 075h, 038h
    DB 056h
    DB 08dh, 08eh, 024h, 004h, 000h, 000h
    call ?InitializeJointTransforms@GameManPose@@QAEXPAUGameMan@@@Z
    DB 08bh, 045h, 07ch
    DB 05fh
    DB 089h, 086h, 000h, 007h, 000h, 000h
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 068h
    DB 0c9h
    DB 0c2h, 010h, 000h
?Initialize@GameMan@@QAEXAAUVector3@@MHH@Z ENDP

END
