.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??GVector3@@QAE?AU0@XZ:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??_C@_06DOEOPPJL@halott?$AA@:BYTE
EXTERN ?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z:PROC
EXTERN ?ContainsPoint@GameBox@@QAE_NAAUVector3@@@Z:PROC
EXTERN ?FinishContacts@GameBox@@QAEXH@Z:PROC
EXTERN ?InitializePhysics@GameBox@@QAEXXZ:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?LogGameDebugValue@@YAHPBDH@Z:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?Next@GameRandomGenerator@@QAEMXZ:PROC
EXTERN ?PlayGameSound@@YAPAXHMMH@Z:PROC
EXTERN ?ReserveGeometry@GameBox@@QAEXHHH@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?ScaleMassProperties@GameBox@@QAEXM@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?g_clipScratchBox@@3UGameBox@@A:BYTE
EXTERN ?g_cutPlaneBox@@3UGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameBoxesInitialized@@3EA:BYTE
EXTERN ?g_gameBoxesLimit@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameContactObjects@@3PAEA:BYTE
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameMenuSelection@@3HA:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_gameRandom@@3UGameRandomGenerator@@A:BYTE
EXTERN ?g_randomHalf@@3MB:DWORD
EXTERN __real@3bea0ea1:DWORD
EXTERN __real@3e800000:DWORD
EXTERN __real@40400000:DWORD
EXTERN __real@be800000:DWORD
EXTERN _exp:PROC
EXTERN _log:PROC

.code

; FUNCTION: SUMO 0x00409b13
; FUNCTION: EDITOR 0x00409b35
PUBLIC ?FractureGameBoxAtPoint@@YAEAAUVector3@@PAUGameBox@@@Z
?FractureGameBoxAtPoint@@YAEAAUVector3@@PAUGameBox@@@Z PROC
    DB 055h
    DB 08dh, 06ch, 024h, 088h
    DB 081h, 0ech, 01ch, 002h, 000h, 000h
    DB 080h, 07bh, 058h, 000h
    DB 075h, 012h
    DB 0a1h
    DD ?g_gameBoxesLimit@@3PAUGameBox@@A
    DB 005h, 028h, 0f6h, 0ffh, 0ffh
    DB 039h, 005h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 076h, 007h
    DB 032h, 0c0h
    DB 0e9h, 06ah, 004h, 000h, 000h
    DB 056h
    DB 057h
    DB 08dh, 083h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 044h
    DB 050h
    DB 0c7h, 045h, 058h
    DD ?g_cutPlaneBox@@3UGameBox@@A
    DB 0c7h, 045h, 054h
    DD ?g_clipScratchBox@@3UGameBox@@A
    DB 08dh, 073h, 060h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08bh, 0ceh
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 0d9h, 043h, 038h
    DB 0d8h, 00dh
    DD __real@3bea0ea1
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _log
    DB 059h
    DB 059h
    DB 033h, 0f6h
    DB 0d8h, 00dh
    DD __real@be800000
    DB 0d9h, 005h
    DD __real@3e800000
    DB 056h
    DB 083h, 0ech, 00ch
    DB 0d9h, 05ch, 024h, 008h
    DB 0ddh, 01ch, 024h
    call _exp
    DB 0d9h, 0c0h
    DB 083h, 0c4h, 004h
    DB 0d9h, 01ch, 024h
    DB 06ah, 001h
    DB 0ddh, 0d8h
    call ?PlayGameSound@@YAPAXHMMH@Z
    DB 083h, 0c4h, 010h
    DB 039h, 035h
    DD ?g_gameMenuSelection@@3HA
    DB 075h, 00bh
    DB 08bh, 083h, 0bch, 000h, 000h, 000h
    DB 0a3h
    DD ?g_gameMenuSelection@@3HA
    DB 08dh, 085h, 05ch, 0feh, 0ffh, 0ffh
    DB 089h, 075h, 070h
    DB 0c7h, 045h, 05ch, 09ah, 099h, 099h, 03eh
    DB 089h, 045h, 074h
    DB 0beh
    DD ?g_gameRandom@@3UGameRandomGenerator@@A
    DB 08bh, 0ceh
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0dch, 0c0h
    DB 051h
    DB 08bh, 0ceh
    DB 0d8h, 025h
    DD ?g_gameOne@@3MB
    DB 0d9h, 01ch, 024h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0dch, 0c0h
    DB 051h
    DB 08bh, 0ceh
    DB 0d8h, 025h
    DD ?g_gameOne@@3MB
    DB 0d9h, 01ch, 024h
    call ?Next@GameRandomGenerator@@QAEMXZ
    DB 0dch, 0c0h
    DB 051h
    DB 08dh, 045h, 000h
    DB 0d8h, 025h
    DD ?g_gameOne@@3MB
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 083h, 0c4h, 010h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 045h, 00ch
    DB 050h
    DB 08dh, 043h, 02ch
    DB 050h
    DB 08dh, 07dh, 044h
    DB 0a5h
    DB 08dh, 045h, 018h
    DB 050h
    DB 08dh, 045h, 05ch
    DB 0a5h
    DB 050h
    DB 08dh, 045h, 024h
    DB 050h
    DB 08dh, 04dh, 044h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 07dh, 074h
    DB 0ffh, 075h, 074h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 08bh, 0cbh
    DB 0a5h
    call ?ContainsPoint@GameBox@@QAE_NAAUVector3@@@Z
    DB 084h, 0c0h
    DB 00fh, 084h, 066h, 0ffh, 0ffh, 0ffh
    DB 0ffh, 045h, 070h
    DB 083h, 045h, 074h, 00ch
    DB 083h, 07dh, 070h, 005h
    DB 00fh, 08ch, 055h, 0ffh, 0ffh, 0ffh
    DB 083h, 065h, 074h, 000h
    DB 08bh, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 08dh, 085h, 05ch, 0feh, 0ffh, 0ffh
    DB 089h, 045h, 070h
    DB 089h, 05dh, 06ch
    DB 033h, 0ffh
    DB 039h, 07dh, 074h
    DB 00fh, 084h, 0a0h, 000h, 000h, 000h
    DB 083h, 0ffh, 004h
    DB 08bh, 045h, 058h
    DB 089h, 045h, 068h
    DB 074h, 00bh
    DB 083h, 0ffh, 003h
    DB 075h, 01ch
    DB 083h, 07dh, 074h, 004h
    DB 075h, 016h
    DB 0b8h, 000h, 001h, 000h, 000h
    DB 050h
    DB 068h, 000h, 004h, 000h, 000h
    DB 08bh, 0ceh
    DB 050h
    DB 089h, 04dh, 068h
    call ?ReserveGeometry@GameBox@@QAEXHHH@Z
    DB 0ffh, 075h, 070h
    DB 08dh, 045h, 044h
    DB 050h
    DB 08dh, 034h, 07fh
    DB 08dh, 045h, 024h
    DB 08dh, 0b4h, 0b5h, 05ch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0ceh
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0ffh, 075h, 070h
    DB 08dh, 045h, 018h
    DB 050h
    DB 08bh, 0ceh
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 048h
    DB 0d8h, 048h, 004h
    DB 051h
    DB 0d9h, 045h, 04ch
    DB 08bh, 04dh, 068h
    DB 0d8h, 048h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 044h
    DB 0d8h, 008h
    DB 08dh, 045h, 044h
    DB 0deh, 0c1h
    DB 0d8h, 00dh
    DD ?g_randomHalf@@3MB
    DB 0d9h, 01ch, 024h
    DB 050h
    DB 0ffh, 075h, 06ch
    call ?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z
    DB 08bh, 045h, 058h
    DB 08bh, 04dh, 054h
    DB 08bh, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 089h, 045h, 06ch
    DB 089h, 04dh, 058h
    DB 089h, 045h, 054h
    DB 047h
    DB 083h, 0ffh, 005h
    DB 00fh, 08ch, 04dh, 0ffh, 0ffh, 0ffh
    DB 08bh, 046h, 014h
    DB 03bh, 046h, 010h
    DB 00fh, 084h, 01fh, 002h, 000h, 000h
    DB 08bh, 043h, 030h
    DB 089h, 046h, 030h
    DB 0d9h, 043h, 034h
    DB 0a1h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0d9h, 058h, 034h
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    call ?InitializePhysics@GameBox@@QAEXXZ
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 06ah, 0ffh
    call ?FinishContacts@GameBox@@QAEXH@Z
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 083h, 0c1h, 03ch
    DB 08bh, 0f1h
    DB 08dh, 043h, 060h
    DB 050h
    DB 08dh, 07dh, 038h
    DB 0a5h
    DB 08dh, 045h, 00ch
    DB 050h
    DB 08dh, 045h, 034h
    DB 050h
    DB 0a5h
    DB 08dh, 045h, 000h
    DB 050h
    DB 0a5h
    DB 0c7h, 045h, 034h, 0aeh, 047h, 081h, 03fh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0c8h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 050h
    DB 08dh, 045h, 0f4h
    DB 050h
    DB 08dh, 08bh, 084h, 000h, 000h, 000h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 081h, 0c7h, 084h, 000h, 000h, 000h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    call ?InitializePhysics@GameBox@@QAEXXZ
    DB 051h
    DB 0d9h, 083h, 0a8h, 000h, 000h, 000h
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0d9h, 01ch, 024h
    call ?ScaleMassProperties@GameBox@@QAEXM@Z
    DB 08bh, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 081h, 0c7h, 09ch, 000h, 000h, 000h
    DB 08dh, 0b3h, 09ch, 000h, 000h, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 081h, 0c7h, 090h, 000h, 000h, 000h
    DB 08dh, 0b3h, 090h, 000h, 000h, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 06ah, 009h
    DB 059h
    DB 083h, 0c7h, 060h
    DB 08dh, 073h, 060h
    DB 0f3h, 0a5h
    DB 0a1h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 083h, 0a0h, 0e4h, 000h, 000h, 000h, 000h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 045h, 0dch
    DB 050h
    DB 08dh, 04bh, 020h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 083h, 0c7h, 020h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 083h, 0c0h, 000h, 000h, 000h
    DB 08bh, 00dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 089h, 081h, 0c0h, 000h, 000h, 000h
    DB 0d9h, 083h, 0c4h, 000h, 000h, 000h
    DB 0a1h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0d9h, 098h, 0c4h, 000h, 000h, 000h
    DB 080h, 03dh
    DD ?g_gameBoxesInitialized@@3EA
    DB 000h
    DB 074h, 011h
    DB 0d9h, 043h, 054h
    DB 0a1h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0d9h, 058h, 054h
    DB 08bh, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0b8h
    DD ?g_gameContactObjects@@3PAEA
    DB 039h, 005h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 08bh, 0c8h
    DB 089h, 04dh, 068h
    DB 00fh, 086h, 0b5h, 000h, 000h, 000h
    DB 083h, 065h, 064h, 000h
    DB 08dh, 079h, 010h
    DB 08bh, 045h, 064h
    DB 08dh, 004h, 081h
    DB 039h, 018h
    DB 089h, 045h, 030h
    DB 075h, 079h
    DB 083h, 04dh, 05ch, 0ffh
    DB 083h, 065h, 060h, 000h
    DB 08dh, 085h, 05ch, 0feh, 0ffh, 0ffh
    DB 0c7h, 045h, 050h, 0ceh, 097h, 040h, 07bh
    DB 089h, 045h, 06ch
    DB 08bh, 04dh, 06ch
    DB 08dh, 047h, 0f8h
    DB 050h
    DB 08dh, 045h, 0e8h
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d8h, 055h, 050h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 00bh
    DB 08bh, 045h, 060h
    DB 0d9h, 05dh, 050h
    DB 089h, 045h, 05ch
    DB 0ebh, 002h
    DB 0ddh, 0d8h
    DB 0ffh, 045h, 060h
    DB 083h, 045h, 06ch, 00ch
    DB 083h, 07dh, 060h, 005h
    DB 07ch, 0c5h
    DB 08bh, 045h, 05ch
    DB 03bh, 045h, 074h
    DB 075h, 01eh
    DB 08bh, 045h, 030h
    DB 089h, 030h
    DB 0d9h, 047h, 0f8h
    DB 0d8h, 065h, 038h
    DB 0d9h, 05fh, 0f8h
    DB 0d9h, 047h, 0fch
    DB 0d8h, 065h, 03ch
    DB 0d9h, 05fh, 0fch
    DB 0d9h, 007h
    DB 0d8h, 065h, 040h
    DB 0d9h, 01fh
    DB 0ffh, 045h, 064h
    DB 08bh, 04dh, 068h
    DB 083h, 0c7h, 00ch
    DB 083h, 07dh, 064h, 002h
    DB 00fh, 08ch, 067h, 0ffh, 0ffh, 0ffh
    DB 081h, 0c1h, 0f4h, 000h, 000h, 000h
    DB 03bh, 00dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 089h, 04dh, 068h
    DB 00fh, 082h, 04bh, 0ffh, 0ffh, 0ffh
    DB 081h, 0c6h, 0fch, 000h, 000h, 000h
    DB 089h, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0ebh, 014h
    DB 06ah, 000h
    DB 068h
    DD ??_C@_06DOEOPPJL@halott?$AA@
    call ?LogGameDebugValue@@YAHPBDH@Z
    DB 08bh, 035h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 059h
    DB 059h
    DB 0ffh, 045h, 074h
    DB 083h, 045h, 070h, 00ch
    DB 083h, 07dh, 074h, 005h
    DB 00fh, 08ch, 0f8h, 0fch, 0ffh, 0ffh
    DB 05fh
    DB 0c6h, 043h, 058h, 001h
    DB 0b0h, 001h
    DB 05eh
    DB 083h, 0c5h, 078h
    DB 0c9h
    DB 0c3h
?FractureGameBoxAtPoint@@YAEAAUVector3@@PAUGameBox@@@Z ENDP

END
