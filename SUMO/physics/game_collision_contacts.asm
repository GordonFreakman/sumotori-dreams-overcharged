.386
.model flat
option casemap:none

EXTERN __alloca_probe:PROC
EXTERN __real@1e3ce508:DWORD
EXTERN __real@3089705f:DWORD
EXTERN __real@43480000:DWORD

EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??GVector3@@QAE?AU0@XZ:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?Multiply@Matrix3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?Pop@GameCollisionCandidateHeap@@QAE?AUVector3@@XZ:PROC
EXTERN ?Push@GameCollisionCandidateHeap@@QAEXMUVector3@@@Z:PROC
EXTERN ?RecalculateMass@GameBox@@QAEXXZ:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?Transposed@Matrix3@@QAE?AU1@XZ:PROC

EXTERN ?g_clipScratchBox@@3UGameBox@@A:BYTE
EXTERN ?g_cutPlaneBox@@3UGameBox@@A:BYTE
EXTERN ?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A:DWORD
EXTERN ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A:DWORD
EXTERN ?g_gameCollisionScale@@3MA:DWORD
EXTERN ?g_gameDecorationHeight@@3MA:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD

.code

; FUNCTION: SUMO 0x00409fac
; FUNCTION: EDITOR 0x00409fce
PUBLIC ?GenerateGameBoxCollisionContacts@@YAHPAUGameBox@@0@Z
?GenerateGameBoxCollisionContacts@@YAHPAUGameBox@@0@Z PROC
    DB 055h
    DB 0b8h, 0e0h, 020h, 000h, 000h
    DB 08dh, 06ch, 024h, 090h
    call __alloca_probe
    DB 08bh, 045h, 078h
    DB 08bh, 088h, 0e8h, 000h, 000h, 000h
    DB 053h
    DB 08bh, 05dh, 07ch
    DB 056h
    DB 057h
    DB 0ebh, 00bh
    DB 039h, 059h, 008h
    DB 00fh, 084h, 092h, 001h, 000h, 000h
    DB 08bh, 009h
    DB 085h, 0c9h
    DB 075h, 0f1h
    DB 021h, 04dh, 090h
    DB 08dh, 048h, 060h
    DB 08dh, 045h, 0dch
    DB 050h
    mov DWORD PTR [ebp+64h], OFFSET ?g_cutPlaneBox@@3UGameBox@@A
    mov DWORD PTR [ebp+6ch], OFFSET ?g_clipScratchBox@@3UGameBox@@A
    DB 08dh, 073h, 060h
    call ?Transposed@Matrix3@@QAE?AU1@XZ
    DB 050h
    DB 08dh, 045h, 094h
    DB 050h
    DB 08dh, 045h, 0b8h
    DB 050h
    DB 08bh, 0ceh
    call ?Transposed@Matrix3@@QAE?AU1@XZ
    DB 08bh, 0c8h
    call ?Multiply@Matrix3@@QAE?AU1@AAU1@@Z
    DB 06ah, 009h
    DB 08bh, 0f0h
    DB 059h
    DB 08dh, 083h, 084h, 000h, 000h, 000h
    DB 08dh, 07dh, 000h
    DB 0f3h, 0a5h
    DB 08bh, 04dh, 078h
    DB 050h
    DB 08dh, 045h, 03ch
    DB 081h, 0c1h, 084h, 000h, 000h, 000h
    DB 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 050h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 04bh, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 0f0h
    DB 08bh, 043h, 010h
    DB 03bh, 043h, 014h
    DB 08dh, 07dh, 054h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 089h, 045h, 068h
    DB 073h, 053h
    DB 0ebh, 003h
    DB 08bh, 045h, 068h
    DB 050h
    DB 08dh, 045h, 03ch
    DB 050h
    DB 08dh, 04dh, 000h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 0d9h, 045h, 058h
    DB 083h, 0ech, 00ch
    DB 08bh, 0fch
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 075h, 068h
    DB 051h
    DB 08dh, 08dh, 090h, 0dfh, 0ffh, 0ffh
    DB 0d8h, 04eh, 004h
    DB 0d9h, 045h, 05ch
    DB 0d8h, 04eh, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 054h
    DB 0d8h, 00eh
    DB 0deh, 0c1h
    DB 0d8h, 06eh, 00ch
    DB 0d9h, 0e0h
    DB 0d9h, 01ch, 024h
    call ?Push@GameCollisionCandidateHeap@@QAEXMUVector3@@@Z
    DB 083h, 0c6h, 024h
    DB 03bh, 073h, 014h
    DB 089h, 075h, 068h
    DB 072h, 0afh
    DB 083h, 07dh, 090h, 000h
    DB 08bh, 075h, 078h
    DB 08bh, 0feh
    DB 089h, 07dh, 068h
    DB 074h, 05dh
    DB 0d9h, 085h, 090h, 0dfh, 0ffh, 0ffh
    DB 08dh, 0b5h, 094h, 0dfh, 0ffh, 0ffh
    DB 08dh, 07dh, 03ch
    DB 0d9h, 0e0h
    DB 0a5h
    DB 0d9h, 05dh, 060h
    DB 0a5h
    DB 08dh, 045h, 048h
    DB 050h
    DB 08dh, 08dh, 090h, 0dfh, 0ffh, 0ffh
    DB 0a5h
    call ?Pop@GameCollisionCandidateHeap@@QAE?AUVector3@@XZ
    DB 08bh, 075h, 064h
    DB 0d9h, 045h, 060h
    DB 051h
    DB 08dh, 045h, 03ch
    DB 0d9h, 01ch, 024h
    DB 050h
    DB 0ffh, 075h, 068h
    DB 08bh, 0ceh
    call ?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z
    DB 08bh, 046h, 014h
    DB 03bh, 046h, 010h
    DB 074h, 06bh
    DB 083h, 07dh, 090h, 000h
    DB 08bh, 045h, 06ch
    DB 089h, 075h, 068h
    DB 089h, 045h, 064h
    DB 089h, 075h, 06ch
    DB 075h, 0a8h
    DB 08bh, 0feh
    DB 08bh, 075h, 078h
    DB 08bh, 0cfh
    call ?RecalculateMass@GameBox@@QAEXXZ
    DB 08dh, 046h, 060h
    DB 050h
    DB 08dh, 045h, 054h
    DB 050h
    DB 08dh, 04fh, 048h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 0d9h, 045h, 05ch
    DB 0d8h, 04dh, 05ch
    DB 0d9h, 045h, 058h
    DB 0d8h, 04dh, 058h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 054h
    DB 0deh, 0c1h
    fcomp DWORD PTR [__real@1e3ce508]
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 00fh, 08bh, 0f9h, 002h, 000h, 000h
    DB 08dh, 04dh, 054h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 08bh, 086h, 0e4h, 000h, 000h, 000h
    DB 083h, 065h, 06ch, 000h
    DB 0ebh, 011h
    DB 033h, 0c0h
    DB 0e9h, 0dfh, 002h, 000h, 000h
    DB 039h, 018h
    DB 074h, 00ch
    DB 08bh, 080h, 0c8h, 000h, 000h, 000h
    DB 085h, 0c0h
    DB 075h, 0f2h
    DB 0ebh, 00ch
    DB 08dh, 048h, 008h
    DB 08bh, 040h, 004h
    DB 089h, 04dh, 064h
    DB 089h, 045h, 06ch
    DB 08bh, 00fh
    DB 0e9h, 0ddh, 000h, 000h, 000h
    DB 080h, 079h, 00dh, 000h
    DB 00fh, 084h, 0d0h, 000h, 000h, 000h
    DB 08dh, 086h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 03ch
    DB 050h
    DB 08dh, 046h, 060h
    DB 050h
    DB 08dh, 045h, 024h
    DB 050h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    mov edi, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 08dh, 045h, 030h
    DB 050h
    DB 08dh, 04dh, 054h
    DB 0a5h
    call ??GVector3@@QAE?AU0@XZ
    mov edi, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 083h, 0c7h, 00ch
    DB 0d9h, 0eeh
    DB 08bh, 0f0h
    DB 0d9h, 05dh, 048h
    DB 08bh, 045h, 078h
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 04ch
    DB 0d9h, 0eeh
    DB 0a5h
    DB 0d9h, 05dh, 050h
    DB 0a5h
    mov ecx, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 089h, 041h, 024h
    mov ecx, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 089h, 059h, 028h
    mov edi, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 083h, 0c7h, 018h
    DB 08dh, 075h, 048h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 080h, 0e0h, 000h, 000h, 000h
    DB 08bh, 08bh, 0e0h, 000h, 000h, 000h
    DB 03bh, 0c1h
    DB 07fh, 002h
    DB 08bh, 0c1h
    DB 083h, 07dh, 06ch, 000h
    mov ecx, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 089h, 041h, 050h
    mov eax, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 0c6h, 040h, 054h, 000h
    DB 074h, 01fh
    mov eax, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 08bh, 075h, 064h
    DB 0ffh, 04dh, 06ch
    DB 0c6h, 040h, 054h, 001h
    mov edi, DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A]
    DB 083h, 0c7h, 018h
    DB 083h, 045h, 064h, 00ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    add DWORD PTR [?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A], 60h
    DB 08bh, 07dh, 068h
    DB 08bh, 075h, 078h
    DB 08bh, 04dh, 060h
    DB 083h, 0c1h, 010h
    DB 03bh, 04fh, 004h
    DB 089h, 04dh, 060h
    DB 00fh, 082h, 017h, 0ffh, 0ffh, 0ffh
    DB 0d9h, 047h, 038h
    fcomp DWORD PTR [__real@3089705f]
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 00fh, 085h, 0bch, 001h, 000h, 000h
    DB 08dh, 086h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 03ch
    DB 050h
    DB 08dh, 046h, 060h
    DB 050h
    DB 08dh, 045h, 030h
    DB 050h
    DB 08dh, 04fh, 03ch
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 086h, 0b0h, 000h, 000h, 000h
    DB 0d8h, 083h, 0b0h, 000h, 000h, 000h
    DB 08dh, 045h, 060h
    DB 050h
    DB 08dh, 045h, 048h
    DB 0d8h, 07fh, 038h
    DB 050h
    DB 08dh, 04dh, 054h
    fmul DWORD PTR [?g_gameCollisionScale@@3MA]
    DB 0d9h, 05dh, 060h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    mov edi, DWORD PTR [?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A]
    DB 083h, 0c7h, 00ch
    DB 08bh, 04dh, 078h
    DB 08dh, 075h, 048h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    mov edi, DWORD PTR [?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A]
    DB 08dh, 075h, 03ch
    DB 0a5h
    DB 0a5h
    DB 0a5h
    mov eax, DWORD PTR [?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A]
    DB 089h, 048h, 018h
    mov eax, DWORD PTR [?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A]
    DB 089h, 058h, 01ch
    add DWORD PTR [?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A], 20h
    DB 083h, 0bbh, 0e8h, 000h, 000h, 000h, 000h
    DB 075h, 07bh
    DB 0d9h, 043h, 038h
    fcomp DWORD PTR [__real@43480000]
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 06bh
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 04ch, 000h, 000h, 0a0h, 040h
    DB 0d9h, 05dh, 048h
    DB 08dh, 075h, 048h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 054h
    DB 0d9h, 05dh, 050h
    DB 08dh, 045h, 054h
    fld DWORD PTR [?g_gameDecorationHeight@@3MA]
    DB 050h
    fadd DWORD PTR [?g_gameOne@@3MB]
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 06ch
    DB 08dh, 045h, 030h
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d9h, 045h, 06ch
    DB 0d8h, 04dh, 06ch
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 00eh
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    DB 08bh, 04dh, 078h
    DB 089h, 081h, 0dch, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    DB 08bh, 04dh, 078h
    DB 089h, 081h, 0d8h, 000h, 000h, 000h
    DB 083h, 0b9h, 0e8h, 000h, 000h, 000h, 000h
    DB 075h, 078h
    DB 0d9h, 041h, 038h
    fcomp DWORD PTR [__real@43480000]
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 068h
    DB 0d9h, 0eeh
    DB 0c7h, 045h, 04ch, 000h, 000h, 0a0h, 040h
    DB 0d9h, 05dh, 048h
    DB 08dh, 075h, 048h
    DB 0d9h, 0eeh
    DB 08dh, 07dh, 054h
    DB 0d9h, 05dh, 050h
    DB 08dh, 045h, 054h
    fld DWORD PTR [?g_gameDecorationHeight@@3MA]
    DB 050h
    fadd DWORD PTR [?g_gameOne@@3MB]
    DB 0a5h
    DB 0a5h
    DB 0d9h, 05dh, 06ch
    DB 08dh, 045h, 030h
    DB 050h
    DB 08dh, 04dh, 03ch
    DB 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 0c8h
    call ?LengthSquared@Vector3@@QAEMXZ
    DB 0d9h, 045h, 06ch
    DB 0d8h, 04dh, 06ch
    DB 0deh, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 005h
    DB 07ah, 00bh
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    DB 089h, 083h, 0dch, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    DB 08bh, 04dh, 078h
    DB 089h, 083h, 0d8h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    DB 089h, 081h, 0d4h, 000h, 000h, 000h
    DB 080h, 0bbh, 0d0h, 000h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    DB 089h, 083h, 0d4h, 000h, 000h, 000h
    DB 075h, 004h
    DB 083h, 061h, 05ch, 000h
    DB 080h, 0b9h, 0d0h, 000h, 000h, 000h, 000h
    DB 075h, 004h
    DB 083h, 063h, 05ch, 000h
    DB 0c6h, 041h, 059h, 000h
    DB 0c6h, 043h, 059h, 000h
    DB 033h, 0c0h
    DB 040h
    DB 05fh
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 070h
    DB 0c9h
    DB 0c3h
?GenerateGameBoxCollisionContacts@@YAHPAUGameBox@@0@Z ENDP

END
