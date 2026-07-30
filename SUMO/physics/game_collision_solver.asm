.386
.model flat
option casemap:none

EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??GVector3@@QAE?AU0@XZ:PROC
EXTERN ??HMatrix3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z:PROC
EXTERN ?ApplyGameManPoseConstraints@@YAXXZ:PROC
EXTERN ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z:PROC
EXTERN ?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z:PROC
EXTERN ?CalculateImpulseResponseMatrix@GameBox@@QAE?AUMatrix3@@AAUVector3@@0@Z:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?FractureGameBoxAtPoint@@YAEAAUVector3@@PAUGameBox@@@Z:PROC
EXTERN ?GenerateGameBoxCollisionContacts@@YAHPAUGameBox@@0@Z:PROC
EXTERN ?Inverted@Matrix3@@QAE?AU1@XZ:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?ParserAtan2Value@@YAMMM@Z:PROC
EXTERN ?PlayGameSound@@YAPAXHMMH@Z:PROC
EXTERN ?Rotate@Vector3@@QAEXAAU1@MM@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?VelocityAtPoint@GameBox@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameCameraHeightScale@@3MB:DWORD
EXTERN ?g_gameCameraInputDamping@@3MB:DWORD
EXTERN ?g_gameCollisionCorrections@@3PAUGameCollisionCorrectionRecord@@A:BYTE
EXTERN ?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A:DWORD
EXTERN ?g_gameCollisionFeatureLinks@@3PAUGameCollisionFeatureLink@@A:BYTE
EXTERN ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A:DWORD
EXTERN ?g_gameCollisionGroupRoot@@3PAXA:DWORD
EXTERN ?g_gameCollisionGroupSentinel@@3EA:BYTE
EXTERN ?g_gameCollisionPointScratchFlag@@3EA:BYTE
EXTERN ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A:BYTE
EXTERN ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A:DWORD
EXTERN ?g_gameContactObjects@@3PAEA:BYTE
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameNegativeHalf@@3MB:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN __real@3d23d70a:DWORD
EXTERN __real@3e4ccccd:DWORD
EXTERN __real@3f4f5c28:DWORD
EXTERN __real@40400000:DWORD
EXTERN __real@be4ccccd:DWORD
EXTERN __real@be800000:DWORD
EXTERN _cos:PROC
EXTERN _exp:PROC
EXTERN _log:PROC
EXTERN _sin:PROC
EXTERN _sqrt:PROC

.code

; FUNCTION: SUMO 0x0040a455
; FUNCTION: EDITOR 0x0040a477
PUBLIC ?ResolveGameCollisions@@YAXXZ
?ResolveGameCollisions@@YAXXZ PROC
    DB 055h
    DB 08dh, 06ch, 024h, 088h
    DB 081h, 0ech, 05ch, 002h, 000h, 000h
    DB 081h, 03dh
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 053h
    DB 056h
    DB 057h
    DB 0c7h, 005h
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DD ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A
    DB 0c7h, 005h
    DD ?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A
    DD ?g_gameCollisionCorrections@@3PAUGameCollisionCorrectionRecord@@A
    DB 0beh, 0fch, 000h, 000h, 000h
    DB 00fh, 086h, 03bh, 001h, 000h, 000h
    DB 083h, 04dh, 074h, 0ffh
    DB 0bfh
    DD ?g_gameBoxes@@3PAUGameBox@@A + 0d0h
    DB 0c7h, 045h, 070h
    DD ?g_gameBoxes@@3PAUGameBox@@A + 58h
    DB 08bh, 045h, 070h
    DB 080h, 038h, 000h
    DB 00fh, 085h, 005h, 001h, 000h, 000h
    DB 080h, 03fh, 000h
    DB 00fh, 085h, 081h, 000h, 000h, 000h
    DB 080h, 07fh, 089h, 000h
    DB 075h, 07bh
    DB 08dh, 087h, 030h, 0ffh, 0ffh, 0ffh
    DB 03dh
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 00fh, 086h, 0e5h, 000h, 000h, 000h
    DB 08bh, 045h, 074h
    DB 033h, 0d2h
    DB 08bh, 0ceh
    DB 0f7h, 0f1h
    DB 0bbh
    DD ?g_gameBoxes@@3PAUGameBox@@A + 84h
    DB 040h
    DB 089h, 045h, 06ch
    DB 080h, 07bh, 0d4h, 000h
    DB 075h, 049h
    DB 080h, 03fh, 000h
    DB 075h, 044h
    DB 0d9h, 043h, 0a8h
    DB 053h
    DB 0d8h, 087h, 05ch, 0ffh, 0ffh, 0ffh
    DB 08dh, 045h, 0c0h
    DB 050h
    DB 08dh, 04fh, 0b4h
    DB 0d9h, 05dh, 068h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d9h, 045h, 068h
    DB 0d8h, 04dh, 068h
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 015h
    DB 08dh, 083h, 07ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 087h, 030h, 0ffh, 0ffh, 0ffh
    DB 050h
    call ?GenerateGameBoxCollisionContacts@@YAHPAUGameBox@@0@Z
    DB 059h
    DB 059h
    DB 003h, 0deh
    DB 0ffh, 04dh, 06ch
    DB 075h, 0aah
    DB 0ebh, 07bh
    DB 08dh, 087h, 030h, 0ffh, 0ffh, 0ffh
    DB 03dh
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 076h, 06eh
    DB 08bh, 045h, 074h
    DB 033h, 0d2h
    DB 08bh, 0ceh
    DB 0f7h, 0f1h
    DB 0bbh
    DD ?g_gameBoxes@@3PAUGameBox@@A + 59h
    DB 040h
    DB 089h, 045h, 068h
    DB 080h, 07bh, 0ffh, 000h
    DB 075h, 04fh
    DB 080h, 03bh, 000h
    DB 075h, 04ah
    DB 080h, 07bh, 077h, 000h
    DB 075h, 044h
    DB 0d9h, 043h, 0d3h
    DB 08dh, 043h, 02bh
    DB 0d8h, 087h, 05ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 04fh, 0b4h
    DB 0d9h, 05dh, 06ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d9h, 045h, 06ch
    DB 0d8h, 04dh, 06ch
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 012h
    DB 08dh, 043h, 0a7h
    DB 050h
    DB 08dh, 087h, 030h, 0ffh, 0ffh, 0ffh
    DB 050h
    call ?GenerateGameBoxCollisionContacts@@YAHPAUGameBox@@0@Z
    DB 059h
    DB 059h
    DB 003h, 0deh
    DB 0ffh, 04dh, 068h
    DB 075h, 0a4h
    DB 001h, 075h, 070h
    DB 001h, 075h, 074h
    DB 003h, 0feh
    DB 08dh, 087h, 030h, 0ffh, 0ffh, 0ffh
    DB 03bh, 005h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 00fh, 082h, 0d5h, 0feh, 0ffh, 0ffh
    DB 081h, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DD ?g_gameContactObjects@@3PAEA
    DB 00fh, 086h, 02dh, 005h, 000h, 000h
    DB 0a1h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 02dh
    DD ?g_gameContactObjects@@3PAEA
    DB 048h
    DB 033h, 0d2h
    DB 0b9h, 0f4h, 000h, 000h, 000h
    DB 0f7h, 0f1h
    DB 0bbh
    DD ?g_gameContactObjects@@3PAEA + 14h
    DB 040h
    DB 089h, 045h, 064h
    DB 08bh, 073h, 0ech
    DB 080h, 07eh, 058h, 000h
    DB 00fh, 085h, 0f4h, 004h, 000h, 000h
    DB 08bh, 07bh, 0f0h
    DB 080h, 07fh, 058h, 000h
    DB 00fh, 085h, 0e7h, 004h, 000h, 000h
    DB 08dh, 087h, 090h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 0c0h
    DB 050h
    DB 08dh, 08eh, 090h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 086h, 0b8h, 000h, 000h, 000h
    DB 0d8h, 087h, 0b8h, 000h, 000h, 000h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 018h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 03dh
    DD __real@be4ccccd
    DB 050h
    DB 08dh, 04dh, 0c0h
    DB 0d9h, 05dh, 06ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 073h, 0ech
    DB 056h
    call ?ApplyPairedAngularImpulse@@YAXPAPAUGameBox@@AAUVector3@@@Z
    DB 08bh, 03eh
    DB 083h, 0a3h, 0dch, 000h, 000h, 000h, 000h
    DB 059h
    DB 059h
    DB 08dh, 087h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    DB 08dh, 047h, 060h
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04bh, 0f4h
    DB 089h, 07dh, 06ch
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 073h, 0f0h
    DB 08dh, 086h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 046h, 060h
    DB 050h
    DB 08dh, 085h, 0e8h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cbh
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 085h, 0ach, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    DB 050h
    DB 08dh, 085h, 040h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0ceh
    call ?CalculateImpulseResponseMatrix@GameBox@@QAE?AUMatrix3@@AAUVector3@@0@Z
    DB 050h
    DB 08dh, 085h, 088h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    DB 050h
    DB 08dh, 085h, 064h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cfh
    call ?CalculateImpulseResponseMatrix@GameBox@@QAE?AUMatrix3@@AAUVector3@@0@Z
    DB 08bh, 0c8h
    call ??HMatrix3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Inverted@Matrix3@@QAE?AU1@XZ
    DB 0d9h, 0e8h
    DB 06ah, 009h
    DB 08dh, 07bh, 05ch
    DB 059h
    DB 08bh, 0f0h
    DB 0f3h, 0a5h
    DB 08dh, 045h, 070h
    DB 0d9h, 05dh, 070h
    DB 050h
    DB 08dh, 085h, 000h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08bh, 0a4h, 000h, 000h, 000h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 0f0h
    DB 08bh, 045h, 06ch
    DB 080h, 0b8h, 0d0h, 000h, 000h, 000h, 000h
    DB 08dh, 07dh, 0cch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 075h, 01ch
    DB 08dh, 085h, 060h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0cch
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 04dh, 06ch
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08bh, 04bh, 0f0h
    DB 080h, 0b9h, 0d0h, 000h, 000h, 000h, 000h
    DB 075h, 00dh
    DB 08dh, 045h, 0cch
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08bh, 043h, 0ech
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 0dch
    DB 050h
    DB 08dh, 04bh, 00ch
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 043h, 0f0h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 0f0h
    DB 050h
    DB 08dh, 04bh, 018h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08dh, 045h, 0f0h
    DB 050h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 04dh, 0dch
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 0d9h, 045h, 048h
    DB 0d8h, 04dh, 048h
    DB 08dh, 075h, 048h
    DB 0d9h, 045h, 050h
    DB 08dh, 07dh, 02ch
    DB 0d8h, 04dh, 050h
    DB 0a5h
    DB 0a5h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 04dh, 04ch
    DB 08dh, 04dh, 02ch
    DB 0a5h
    DB 0deh, 0c1h
    DB 0d9h, 05dh, 068h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08bh, 073h, 0ech
    DB 0ddh, 0d8h
    DB 08dh, 046h, 060h
    DB 050h
    DB 08dh, 045h, 020h
    DB 050h
    DB 08dh, 04bh, 024h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 043h, 0f0h
    DB 083h, 0c0h, 060h
    DB 050h
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 04bh, 030h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 045h, 054h
    DB 050h
    DB 08dh, 04dh, 020h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 0d9h, 005h
    DD ?g_vectorZero@@3MB
    DB 0d9h, 043h, 03ch
    DB 0dah, 0e9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 044h
    DB 00fh, 08bh, 0cdh, 000h, 000h, 000h
    DB 08dh, 045h, 074h
    DB 050h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 054h
    DB 0c7h, 045h, 074h, 00ah, 0d7h, 023h, 03ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    DB 08bh, 0ceh
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 074h
    DB 050h
    DB 08dh, 085h, 00ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 085h, 0d0h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 054h
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04bh, 0f0h
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 083h, 08bh, 0dch, 000h, 000h, 000h, 004h
    DB 08dh, 04dh, 054h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 08bh, 083h, 0d8h, 000h, 000h, 000h
    DB 08dh, 0bbh, 0c8h, 000h, 000h, 000h
    DB 08dh, 075h, 054h
    DB 0a5h
    DB 089h, 045h, 074h
    DB 08dh, 045h, 074h
    DB 050h
    DB 0a5h
    DB 08dh, 085h, 048h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 054h
    DB 0a5h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04bh, 0ech
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 074h
    DB 050h
    DB 08dh, 085h, 0dch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 085h, 030h, 0ffh, 0ffh, 0ffh
    DB 08dh, 04dh, 054h
    DB 050h
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04bh, 0f0h
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 0e9h, 06bh, 001h, 000h, 000h
    DB 0d9h, 045h, 068h
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d9h, 045h, 0f0h
    DB 0d8h, 04dh, 0dch
    DB 0d9h, 045h, 0f8h
    DB 0d8h, 04dh, 0e4h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 0f4h
    DB 0d8h, 04dh, 0e0h
    DB 0deh, 0c1h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 01ch, 024h
    call ?ParserAtan2Value@@YAMMM@Z
    DB 0d9h, 0e0h
    DB 0d9h, 055h, 070h
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 070h
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 045h, 02ch
    DB 0d9h, 045h, 06ch
    DB 08dh, 04dh, 020h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@MM@Z
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 054h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 04dh, 05ch
    DB 0deh, 0c1h
    DB 0d9h, 045h, 058h
    DB 0d8h, 04dh, 058h
    DB 0deh, 0c1h
    DB 0d9h, 055h, 060h
    DB 0d8h, 05bh, 044h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 0dch, 000h, 000h, 000h
    DB 083h, 08bh, 0dch, 000h, 000h, 000h, 002h
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 045h, 008h
    DB 050h
    DB 08dh, 04dh, 020h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 0d9h, 045h, 070h
    DB 0d8h, 00dh
    DD ?g_gameNegativeHalf@@3MB
    DB 051h
    DB 051h
    DB 0d9h, 055h, 06ch
    DB 0ddh, 01ch, 024h
    call _cos
    DB 0d9h, 05dh, 070h
    DB 0d9h, 045h, 06ch
    DB 0ddh, 01ch, 024h
    call _sin
    DB 0d9h, 05ch, 024h, 004h
    DB 08dh, 045h, 02ch
    DB 0d9h, 045h, 070h
    DB 08dh, 04dh, 008h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?Rotate@Vector3@@QAEXAAU1@MM@Z
    DB 08dh, 04dh, 008h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0d9h, 043h, 044h
    DB 08dh, 0bbh, 0c8h, 000h, 000h, 000h
    DB 08dh, 075h, 008h
    DB 0a5h
    DB 0a5h
    DB 051h
    DB 051h
    DB 0a5h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 073h, 0ech
    DB 0d9h, 05dh, 06ch
    DB 0d9h, 045h, 060h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 043h, 0f0h
    DB 0d8h, 065h, 06ch
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d9h, 086h, 0b8h, 000h, 000h, 000h
    DB 08dh, 04dh, 008h
    DB 0d8h, 080h, 0b8h, 000h, 000h, 000h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 085h, 0f4h, 0feh, 0ffh, 0ffh
    DB 0deh, 0f9h
    DB 050h
    DB 0d8h, 083h, 0d8h, 000h, 000h, 000h
    DB 0d9h, 05dh, 06ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    DB 08bh, 0ceh
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 045h, 09ch
    DB 050h
    DB 08dh, 045h, 0b4h
    DB 08dh, 04dh, 008h
    DB 0e9h, 07eh, 0feh, 0ffh, 0ffh
    DB 0d9h, 0eeh
    DB 0d9h, 09bh, 0d8h, 000h, 000h, 000h
    DB 0d9h, 045h, 068h
    DB 0d8h, 05bh, 040h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 001h
    DB 00fh, 085h, 09dh, 000h, 000h, 000h
    DB 0d9h, 043h, 040h
    DB 083h, 08bh, 0dch, 000h, 000h, 000h, 001h
    DB 08dh, 0bbh, 0bch, 000h, 000h, 000h
    DB 08dh, 075h, 02ch
    DB 0a5h
    DB 0a5h
    DB 051h
    DB 051h
    DB 0a5h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 073h, 0ech
    DB 0d9h, 05dh, 060h
    DB 0d9h, 045h, 068h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 08bh, 043h, 0f0h
    DB 0d8h, 065h, 060h
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD __real@3e4ccccd
    DB 0d9h, 086h, 0b8h, 000h, 000h, 000h
    DB 08dh, 04dh, 02ch
    DB 0d8h, 080h, 0b8h, 000h, 000h, 000h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 045h, 0a8h
    DB 0deh, 0f9h
    DB 050h
    DB 0d8h, 083h, 0d4h, 000h, 000h, 000h
    DB 0d9h, 05dh, 06ch
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 014h
    DB 050h
    DB 08bh, 0ceh
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 045h, 090h
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 02ch
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04bh, 0f0h
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 081h, 0c3h, 0f4h, 000h, 000h, 000h
    DB 0ffh, 04dh, 064h
    DB 00fh, 085h, 0f0h, 0fah, 0ffh, 0ffh
    DB 0bbh
    DD ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A
    DB 039h, 01dh
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DB 0c7h, 005h
    DD ?g_gameCollisionGroupRoot@@3PAXA
    DD ?g_gameCollisionGroupSentinel@@3EA
    DB 00fh, 086h, 08fh, 000h, 000h, 000h
    DB 08bh, 04bh, 024h
    DB 053h
    DB 053h
    DB 08dh, 085h, 064h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 0c7h, 043h, 058h
    DD ?g_gameCollisionGroupSentinel@@3EA
    call ?CalculateImpulseResponseMatrix@GameBox@@QAE?AUMatrix3@@AAUVector3@@0@Z
    DB 06ah, 009h
    DB 059h
    DB 053h
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 0ach, 0feh, 0ffh, 0ffh
    DB 053h
    DB 08dh, 085h, 088h, 0feh, 0ffh, 0ffh
    DB 0f3h, 0a5h
    DB 08bh, 04bh, 028h
    DB 050h
    call ?CalculateImpulseResponseMatrix@GameBox@@QAE?AUMatrix3@@AAUVector3@@0@Z
    DB 050h
    DB 08dh, 085h, 040h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 0ach, 0feh, 0ffh, 0ffh
    call ??HMatrix3@@QAE?AU0@AAU0@@Z
    DB 06ah, 009h
    DB 059h
    DB 08bh, 0f0h
    DB 08dh, 0bdh, 0ach, 0feh, 0ffh, 0ffh
    DB 0f3h, 0a5h
    DB 08dh, 085h, 01ch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08dh, 0ach, 0feh, 0ffh, 0ffh
    DB 0c7h, 043h, 05ch
    DD ?g_gameCollisionGroupSentinel@@3EA
    DB 0c6h, 005h
    DD ?g_gameCollisionPointScratchFlag@@3EA
    DB 000h
    call ?Inverted@Matrix3@@QAE?AU1@XZ
    DB 08dh, 07bh, 02ch
    DB 06ah, 009h
    DB 083h, 0c3h, 060h
    DB 03bh, 01dh
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DB 059h
    DB 08bh, 0f0h
    DB 0f3h, 0a5h
    DB 00fh, 082h, 071h, 0ffh, 0ffh, 0ffh
    DB 083h, 065h, 068h, 000h
    DB 081h, 03dh
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DD ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A
    DB 00fh, 086h, 006h, 002h, 000h, 000h
    DB 0bbh
    DD ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A + 1ch
    DB 08bh, 043h, 034h
    DB 085h, 0c0h
    DB 00fh, 084h, 0e4h, 001h, 000h, 000h
    DB 048h
    DB 083h, 07dh, 068h, 000h
    DB 089h, 043h, 034h
    DB 00fh, 084h, 083h, 001h, 000h, 000h
    DB 08bh, 04bh, 00ch
    DB 08dh, 073h, 0e4h
    DB 056h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 050h
    call ?VelocityAtPoint@GameBox@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 04bh, 008h
    DB 050h
    DB 08dh, 045h, 0c0h
    DB 050h
    DB 056h
    DB 08dh, 045h, 090h
    DB 050h
    call ?VelocityAtPoint@GameBox@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 043h, 010h
    DB 050h
    DB 08dh, 045h, 0a8h
    DB 050h
    DB 08dh, 04dh, 0c0h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 048h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 048h
    DB 0d8h, 043h, 0fch
    DB 08dh, 073h, 0f0h
    DB 08dh, 045h, 074h
    DB 0d9h, 05dh, 048h
    DB 050h
    DB 0d9h, 045h, 04ch
    DB 08dh, 045h, 0b4h
    DB 0d8h, 003h
    DB 050h
    DB 08bh, 0ceh
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 045h, 050h
    DB 0d8h, 043h, 004h
    DB 0d9h, 05dh, 050h
    DB 0d9h, 045h, 050h
    DB 0d8h, 04bh, 0f8h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 04bh, 0f4h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 048h
    DB 0d8h, 00eh
    DB 0deh, 0c1h
    DB 0d9h, 05dh, 074h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 054h
    DB 050h
    DB 08dh, 04dh, 048h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 074h
    DB 0d8h, 01dh
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 017h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 020h
    DB 0d9h, 05dh, 020h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 024h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 028h
    DB 0e9h, 08ch, 000h, 000h, 000h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 04dh, 05ch
    DB 0d9h, 045h, 058h
    DB 0d8h, 04dh, 058h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 054h
    DB 0deh, 0c1h
    DB 0d9h, 005h
    DD ?g_vectorZero@@3MB
    DB 0d9h, 0c1h
    DB 0dah, 0e9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 044h
    DB 07bh, 042h
    DB 0d9h, 045h, 074h
    DB 0d8h, 04dh, 074h
    DB 0d8h, 00dh
    DD __real@3f4f5c28
    DB 0d8h, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 02dh
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0d8h, 07dh, 074h
    DB 059h
    DB 059h
    DB 0d8h, 00dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0d9h, 045h, 054h
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 045h, 058h
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 058h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 0c9h
    DB 0d9h, 05dh, 05ch
    DB 08dh, 045h, 074h
    DB 0ddh, 0d8h
    DB 050h
    DB 08dh, 045h, 09ch
    DB 050h
    DB 08bh, 0ceh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 0f4h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 054h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 048h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 045h, 048h
    DB 0d8h, 063h, 0fch
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 023h
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 045h, 050h
    DB 0d8h, 063h, 004h
    DB 0d9h, 05dh, 050h
    DB 0d9h, 045h, 048h
    DB 0d8h, 043h, 0fch
    DB 0d9h, 05bh, 0fch
    DB 0d9h, 045h, 04ch
    DB 0d8h, 003h
    DB 0d9h, 01bh
    DB 0d9h, 045h, 050h
    DB 0d8h, 043h, 004h
    DB 0d9h, 05bh, 004h
    DB 0ebh, 009h
    DB 08dh, 073h, 0fch
    DB 08dh, 07dh, 048h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 073h, 008h
    DB 080h, 0beh, 0d0h, 000h, 000h, 000h, 000h
    DB 075h, 01bh
    DB 08dh, 085h, 030h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 048h
    call ??GVector3@@QAE?AU0@XZ
    DB 050h
    DB 08dh, 043h, 0e4h
    DB 050h
    DB 08bh, 0ceh
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08bh, 04bh, 00ch
    DB 080h, 0b9h, 0d0h, 000h, 000h, 000h, 000h
    DB 075h, 00dh
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 043h, 0e4h
    DB 050h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08bh, 043h, 008h
    DB 083h, 0a0h, 0e4h, 000h, 000h, 000h, 000h
    DB 083h, 0c3h, 060h
    DB 08dh, 043h, 0e4h
    DB 03bh, 005h
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DB 00fh, 082h, 0ffh, 0fdh, 0ffh, 0ffh
    DB 081h, 03dh
    DD ?g_gameContactObjectsEnd@@3PAEA
    DD ?g_gameContactObjects@@3PAEA
    DB 00fh, 086h, 07ah, 003h, 000h, 000h
    DB 0beh
    DD ?g_gameContactObjects@@3PAEA + 0e4h
    DB 08bh, 0beh, 01ch, 0ffh, 0ffh, 0ffh
    DB 080h, 07fh, 058h, 000h
    DB 00fh, 085h, 04dh, 003h, 000h, 000h
    DB 08bh, 09eh, 020h, 0ffh, 0ffh, 0ffh
    DB 080h, 07bh, 058h, 000h
    DB 00fh, 085h, 03dh, 003h, 000h, 000h
    DB 08dh, 087h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 047h, 060h
    DB 050h
    DB 08dh, 085h, 0dch, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08eh, 024h, 0ffh, 0ffh, 0ffh
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 083h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 043h, 060h
    DB 050h
    DB 08dh, 085h, 048h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08eh, 030h, 0ffh, 0ffh, 0ffh
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 085h, 0d0h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cbh
    call ?VelocityAtPoint@GameBox@@QAE?AUVector3@@AAU2@@Z
    DB 050h
    DB 08dh, 045h, 0cch
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 085h, 00ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0cfh
    call ?VelocityAtPoint@GameBox@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 0c8h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 046h, 08ch
    DB 050h
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 045h, 060h
    DB 050h
    DB 08dh, 085h, 054h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08dh, 085h, 060h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 038h
    DB 0c7h, 045h, 060h, 08fh, 0c2h, 0f5h, 03ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 085h, 000h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0cch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 080h, 0bfh, 0d0h, 000h, 000h, 000h, 000h
    DB 075h, 01bh
    DB 08dh, 085h, 0e8h, 0feh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 04dh, 0fch
    call ??GVector3@@QAE?AU0@XZ
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08bh, 0cfh
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08bh, 08eh, 020h, 0ffh, 0ffh, 0ffh
    DB 080h, 0b9h, 0d0h, 000h, 000h, 000h, 000h
    DB 075h, 00dh
    DB 08dh, 045h, 0fch
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 0f6h, 046h, 00ch, 004h
    DB 00fh, 084h, 0b3h, 000h, 000h, 000h
    DB 08bh, 09eh, 020h, 0ffh, 0ffh, 0ffh
    DB 08bh, 0beh, 01ch, 0ffh, 0ffh, 0ffh
    DB 08dh, 083h, 090h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 085h, 06ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08fh, 090h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 087h, 0b8h, 000h, 000h, 000h
    DB 0d8h, 083h, 0b8h, 000h, 000h, 000h
    DB 08dh, 04eh, 0f8h
    DB 0d8h, 03dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0d9h, 040h, 004h
    DB 0d8h, 04eh, 0fch
    DB 0d9h, 040h, 008h
    DB 0d8h, 00eh
    DB 0deh, 0c1h
    DB 0d9h, 000h
    DB 0d8h, 009h
    DB 0deh, 0c1h
    DB 0deh, 0c9h
    DB 0d8h, 046h, 008h
    DB 0d8h, 015h
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d8h, 066h, 008h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 018h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 055h, 070h
    DB 050h
    DB 0d8h, 046h, 008h
    DB 0d9h, 05eh, 008h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08bh, 0cfh
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 0d9h, 045h, 070h
    DB 08dh, 045h, 064h
    DB 0d9h, 0e0h
    DB 050h
    DB 0d9h, 05dh, 064h
    DB 08dh, 045h, 0dch
    DB 050h
    DB 08dh, 04eh, 0f8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 08eh, 020h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 0f6h, 046h, 00ch, 001h
    DB 00fh, 084h, 0aeh, 000h, 000h, 000h
    DB 08bh, 09eh, 020h, 0ffh, 0ffh, 0ffh
    DB 08bh, 0beh, 01ch, 0ffh, 0ffh, 0ffh
    DB 08dh, 083h, 090h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 0f0h
    DB 050h
    DB 08dh, 08fh, 090h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 087h, 0b8h, 000h, 000h, 000h
    DB 0d8h, 083h, 0b8h, 000h, 000h, 000h
    DB 08dh, 04eh, 0ech
    DB 0d8h, 03dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0d9h, 046h, 0f4h
    DB 0d8h, 048h, 008h
    DB 0d9h, 040h, 004h
    DB 0d8h, 04eh, 0f0h
    DB 0deh, 0c1h
    DB 0d9h, 000h
    DB 0d8h, 009h
    DB 0deh, 0c1h
    DB 0deh, 0c9h
    DB 0d8h, 046h, 004h
    DB 0d8h, 015h
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d8h, 066h, 004h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 045h, 008h
    DB 0d9h, 055h, 070h
    DB 050h
    DB 0d8h, 046h, 004h
    DB 0d9h, 05eh, 004h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08bh, 0cfh
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 0d9h, 045h, 070h
    DB 08dh, 045h, 064h
    DB 0d9h, 0e0h
    DB 050h
    DB 0d9h, 05dh, 064h
    DB 08dh, 045h, 014h
    DB 050h
    DB 08dh, 04eh, 0ech
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 08eh, 020h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 0f6h, 046h, 00ch, 002h
    DB 00fh, 084h, 0b3h, 000h, 000h, 000h
    DB 08bh, 09eh, 020h, 0ffh, 0ffh, 0ffh
    DB 08bh, 0beh, 01ch, 0ffh, 0ffh, 0ffh
    DB 08dh, 083h, 090h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 085h, 03ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 08fh, 090h, 000h, 000h, 000h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 087h, 0b8h, 000h, 000h, 000h
    DB 0d8h, 083h, 0b8h, 000h, 000h, 000h
    DB 08dh, 04eh, 0f8h
    DB 0d8h, 03dh
    DD ?g_gameCameraInputDamping@@3MB
    DB 0d9h, 040h, 004h
    DB 0d8h, 04eh, 0fch
    DB 0d9h, 040h, 008h
    DB 0d8h, 00eh
    DB 0deh, 0c1h
    DB 0d9h, 001h
    DB 0d8h, 008h
    DB 0deh, 0c1h
    DB 0deh, 0c9h
    DB 0d8h, 046h, 008h
    DB 0d8h, 015h
    DD ?g_vectorZero@@3MB
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 004h
    DB 0ddh, 0d8h
    DB 0d9h, 0eeh
    DB 0d8h, 066h, 008h
    DB 08dh, 045h, 070h
    DB 050h
    DB 08dh, 085h, 024h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 055h, 070h
    DB 050h
    DB 0d8h, 046h, 008h
    DB 0d9h, 05eh, 008h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 02ch
    DB 050h
    DB 08bh, 0cfh
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 0d9h, 045h, 070h
    DB 08dh, 045h, 064h
    DB 0d9h, 0e0h
    DB 050h
    DB 0d9h, 05dh, 064h
    DB 08dh, 045h, 084h
    DB 050h
    DB 08dh, 04eh, 0f8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 08eh, 020h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 045h, 038h
    DB 050h
    call ?ApplyAngularImpulse@GameBox@@QAEXAAUVector3@@0@Z
    DB 081h, 0c6h, 0f4h, 000h, 000h, 000h
    DB 08dh, 086h, 01ch, 0ffh, 0ffh, 0ffh
    DB 03bh, 005h
    DD ?g_gameContactObjectsEnd@@3PAEA
    DB 00fh, 082h, 08bh, 0fch, 0ffh, 0ffh
    call ?ApplyGameManPoseConstraints@@YAXXZ
    DB 0ffh, 045h, 068h
    DB 083h, 07dh, 068h, 028h
    DB 00fh, 08ch, 04eh, 0fah, 0ffh, 0ffh
    DB 0a1h
    DD ?g_gameBoxesEnd@@3PAUGameBox@@A
    DB 0b9h
    DD ?g_gameBoxes@@3PAUGameBox@@A
    DB 03bh, 0c1h
    DB 076h, 011h
    DB 083h, 0a1h, 0e4h, 000h, 000h, 000h, 000h
    DB 081h, 0c1h, 0fch, 000h, 000h, 000h
    DB 03bh, 0c8h
    DB 072h, 0efh
    DB 0a1h
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DB 0c7h, 005h
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DD ?g_gameCollisionFeatureLinks@@3PAUGameCollisionFeatureLink@@A
    DB 083h, 060h, 028h, 000h
    DB 0bbh
    DD ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A
    DB 039h, 01dh
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DB 00fh, 086h, 098h, 003h, 000h, 000h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 020h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 024h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 028h
    DB 0a1h
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 0d9h, 0eeh
    DB 083h, 060h, 004h, 000h
    DB 0d9h, 05dh, 074h
    DB 08bh, 043h, 028h
    DB 083h, 065h, 070h, 000h
    DB 08dh, 075h, 020h
    DB 08dh, 07dh, 054h
    DB 0a5h
    DB 089h, 045h, 064h
    DB 08bh, 043h, 024h
    DB 0a5h
    DB 089h, 045h, 060h
    DB 08ah, 043h, 054h
    DB 089h, 05dh, 068h
    DB 0a5h
    DB 088h, 045h, 047h
    DB 08bh, 045h, 060h
    DB 039h, 043h, 024h
    DB 075h, 069h
    DB 0a1h
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 083h, 078h, 004h, 010h
    DB 07dh, 05eh
    DB 08dh, 073h, 018h
    DB 08bh, 0ceh
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 051h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _sqrt
    DB 0a1h
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 0d8h, 045h, 074h
    DB 0ffh, 045h, 070h
    DB 059h
    DB 0d9h, 05dh, 074h
    DB 059h
    DB 0d9h, 045h, 054h
    DB 08bh, 048h, 004h
    DB 0d8h, 003h
    DB 08dh, 00ch, 049h
    DB 08dh, 07ch, 088h, 008h
    DB 083h, 0c3h, 060h
    DB 0d9h, 05dh, 054h
    DB 0d9h, 045h, 058h
    DB 0d8h, 043h, 0a4h
    DB 0d9h, 05dh, 058h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 043h, 0a8h
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 05ch
    DB 0a5h
    DB 0a1h
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 0ffh, 040h, 004h
    DB 08bh, 045h, 064h
    DB 039h, 043h, 028h
    DB 074h, 08fh
    DB 0d9h, 045h, 074h
    DB 083h, 0ebh, 060h
    DB 0d8h, 01dh
    DD ?g_gameCameraHeightScale@@3MB
    DB 089h, 05dh, 064h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 042h, 001h, 000h, 000h
    DB 080h, 07dh, 047h, 000h
    DB 00fh, 085h, 038h, 001h, 000h, 000h
    DB 08bh, 04bh, 024h
    DB 0d9h, 081h, 0ach, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d8h, 05dh, 074h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 069h
    DB 083h, 0b9h, 0c0h, 000h, 000h, 000h, 000h
    DB 074h, 060h
    DB 0d9h, 081h, 0cch, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0d8h, 05dh, 074h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 04ah
    DB 08bh, 0c1h
    DB 0d9h, 040h, 038h
    DB 051h
    DB 0d8h, 0b0h, 0c8h, 000h, 000h, 000h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _log
    DB 0d8h, 00dh
    DD __real@be800000
    DB 0ddh, 01ch, 024h
    call _exp
    DB 08bh, 043h, 024h
    DB 0d9h, 045h, 074h
    DB 0d8h, 088h, 0c4h, 000h, 000h, 000h
    DB 059h
    DB 059h
    DB 06ah, 000h
    DB 051h
    DB 051h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 0b0h, 0c0h, 000h, 000h, 000h
    call ?PlayGameSound@@YAPAXHMMH@Z
    DB 083h, 0c4h, 010h
    DB 08bh, 043h, 024h
    DB 0d9h, 045h, 074h
    DB 08dh, 088h, 0cch, 000h, 000h, 000h
    DB 0d8h, 019h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 005h
    DB 08bh, 045h, 074h
    DB 089h, 001h
    DB 08bh, 04bh, 028h
    DB 0d9h, 081h, 0ach, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@3d23d70a
    DB 0d8h, 05dh, 074h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 069h
    DB 083h, 0b9h, 0c0h, 000h, 000h, 000h, 000h
    DB 074h, 060h
    DB 0d9h, 081h, 0cch, 000h, 000h, 000h
    DB 0d8h, 00dh
    DD __real@40400000
    DB 0d8h, 05dh, 074h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 04ah
    DB 08bh, 0c1h
    DB 0d9h, 040h, 038h
    DB 051h
    DB 0d8h, 0b0h, 0c8h, 000h, 000h, 000h
    DB 051h
    DB 0ddh, 01ch, 024h
    call _log
    DB 0d8h, 00dh
    DD __real@be800000
    DB 0ddh, 01ch, 024h
    call _exp
    DB 08bh, 043h, 028h
    DB 0d9h, 045h, 074h
    DB 0d8h, 088h, 0c4h, 000h, 000h, 000h
    DB 059h
    DB 059h
    DB 06ah, 000h
    DB 051h
    DB 051h
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 01ch, 024h
    DB 0ffh, 0b0h, 0c0h, 000h, 000h, 000h
    call ?PlayGameSound@@YAPAXHMMH@Z
    DB 083h, 0c4h, 010h
    DB 08bh, 043h, 028h
    DB 0d9h, 045h, 074h
    DB 08dh, 088h, 0cch, 000h, 000h, 000h
    DB 0d8h, 019h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 005h
    DB 08bh, 045h, 074h
    DB 089h, 001h
    DB 08bh, 043h, 024h
    DB 0d9h, 045h, 074h
    DB 0d8h, 058h, 054h
    DB 08bh, 07dh, 068h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 094h, 000h, 000h, 000h
    DB 03bh, 0fbh
    DB 073h, 061h
    DB 0c7h, 045h, 06ch, 000h, 000h, 080h, 03eh
    DB 0c7h, 045h, 0ech, 000h, 000h, 080h, 03eh
    DB 08dh, 077h, 018h
    DB 08dh, 045h, 06ch
    DB 050h
    DB 08dh, 045h, 084h
    DB 050h
    DB 08bh, 0ceh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04eh, 00ch
    DB 050h
    DB 057h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 0ech
    DB 050h
    DB 08dh, 085h, 024h, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08dh, 085h, 03ch, 0ffh, 0ffh, 0ffh
    DB 050h
    DB 08bh, 0ceh
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04eh, 010h
    DB 050h
    DB 057h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 083h, 0c7h, 060h
    DB 083h, 0c6h, 060h
    DB 03bh, 0fbh
    DB 072h, 0b3h
    DB 089h, 07dh, 068h
    DB 0dbh, 045h, 070h
    DB 08dh, 045h, 060h
    DB 050h
    DB 08dh, 085h, 078h, 0ffh, 0ffh, 0ffh
    DB 0d8h, 03dh
    DD ?g_gameOne@@3MB
    DB 050h
    DB 08dh, 04dh, 054h
    DB 0d9h, 05dh, 060h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 05bh, 024h
    DB 08bh, 0c8h
    call ?FractureGameBoxAtPoint@@YAEAAUVector3@@PAUGameBox@@@Z
    DB 08bh, 07dh, 068h
    DB 08bh, 05dh, 064h
    DB 08bh, 043h, 028h
    DB 0d9h, 045h, 074h
    DB 0d8h, 058h, 054h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 085h, 000h, 000h, 000h
    DB 03bh, 0fbh
    DB 073h, 058h
    DB 0c7h, 045h, 0e8h, 000h, 000h, 080h, 03eh
    DB 0c7h, 045h, 0d8h, 000h, 000h, 080h, 03eh
    DB 08dh, 077h, 018h
    DB 08dh, 045h, 0e8h
    DB 050h
    DB 08dh, 045h, 090h
    DB 050h
    DB 08bh, 0ceh
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04eh, 00ch
    DB 050h
    DB 057h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 0d8h
    DB 050h
    DB 08dh, 045h, 0a8h
    DB 050h
    DB 08dh, 045h, 0b4h
    DB 050h
    DB 08bh, 0ceh
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 04eh, 010h
    DB 050h
    DB 057h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 083h, 0c7h, 060h
    DB 083h, 0c6h, 060h
    DB 03bh, 0fbh
    DB 072h, 0b9h
    DB 0dbh, 045h, 070h
    DB 08dh, 045h, 060h
    DB 050h
    DB 08dh, 045h, 09ch
    DB 0d8h, 03dh
    DD ?g_gameOne@@3MB
    DB 050h
    DB 08dh, 04dh, 054h
    DB 0d9h, 05dh, 060h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 05bh, 028h
    DB 08bh, 0c8h
    call ?FractureGameBoxAtPoint@@YAEAAUVector3@@PAUGameBox@@@Z
    DB 08bh, 05dh, 064h
    DB 08bh, 043h, 024h
    DB 08bh, 080h, 0e4h, 000h, 000h, 000h
    DB 08bh, 00dh
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 089h, 081h, 0c8h, 000h, 000h, 000h
    DB 08bh, 043h, 028h
    DB 08bh, 00dh
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 089h, 001h
    DB 08bh, 043h, 024h
    DB 08bh, 00dh
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 089h, 088h, 0e4h, 000h, 000h, 000h
    DB 081h, 005h
    DD ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
    DB 0cch, 000h, 000h, 000h
    DB 083h, 0c3h, 060h
    DB 03bh, 01dh
    DD ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
    DB 00fh, 082h, 077h, 0fch, 0ffh, 0ffh
    DB 081h, 03dh
    DD ?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A
    DD ?g_gameCollisionCorrections@@3PAUGameCollisionCorrectionRecord@@A
    DB 076h, 035h
    DB 0beh
    DD ?g_gameCollisionCorrections@@3PAUGameCollisionCorrectionRecord@@A + 0ch
    DB 08bh, 04eh, 00ch
    DB 056h
    DB 08dh, 07eh, 0f4h
    DB 057h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 08dh, 045h, 084h
    DB 050h
    DB 08bh, 0ceh
    call ??GVector3@@QAE?AU0@XZ
    DB 08bh, 04eh, 010h
    DB 050h
    DB 057h
    call ?ApplyImpulseAtPoint@GameBox@@QAEXAAUVector3@@0@Z
    DB 083h, 0c6h, 020h
    DB 08dh, 046h, 0f4h
    DB 03bh, 005h
    DD ?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A
    DB 072h, 0d0h
    DB 05fh
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 078h
    DB 0c9h
    DB 0c3h
?ResolveGameCollisions@@YAXXZ ENDP

END
