.686
.model flat
option casemap:none

EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ??YVector3@@QAEXAAU0@@Z:PROC

.code

; FUNCTION: SUMO 0x00408114
; FUNCTION: EDITOR 0x00408136
PUBLIC ?AddTriangle@MassAccumulator@@QAEXAAUVector3@@00M@Z
?AddTriangle@MassAccumulator@@QAEXAAUVector3@@00M@Z PROC
    db 055h, 08dh, 06ch, 024h, 098h, 081h, 0ech, 0a8h, 000h, 000h, 000h, 053h
    db 0d9h, 0eeh, 056h, 08bh, 075h, 070h, 057h, 08dh, 07dh, 03ch, 0a5h, 0a5h
    db 0a5h, 0d9h, 05dh, 044h, 0d9h, 0eeh, 08bh, 075h, 074h, 0ffh, 075h, 074h
    db 08dh, 07dh, 054h, 0a5h, 0a5h, 0a5h, 0d9h, 05dh, 05ch, 0d9h, 0eeh, 08bh
    db 075h, 078h, 08dh, 07dh, 048h, 0a5h, 0a5h, 08dh, 045h, 0c0h, 08bh, 0d9h
    db 0a5h, 0d9h, 05dh, 050h, 050h, 08dh, 04dh, 03ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 0ffh, 075h, 074h, 08bh, 0f0h, 08dh, 045h, 0d8h, 050h, 08dh, 04dh, 054h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 050h, 08dh, 045h, 008h, 050h, 0ffh, 075h, 074h, 08dh, 045h, 0fch, 050h
    db 08dh, 04dh, 048h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    db 0d9h, 046h, 008h, 0d8h, 048h, 008h, 08dh, 04dh, 048h, 0d9h, 046h, 004h
    db 0c7h, 045h, 060h, 000h, 000h, 080h, 03eh, 0d8h, 048h, 004h, 0deh, 0c1h
    db 0d9h, 006h, 0d8h, 008h, 08dh, 045h, 060h, 050h, 08dh, 045h, 014h, 050h
    db 0deh, 0c1h, 08dh, 045h, 054h, 050h, 08dh, 045h, 02ch, 0d9h, 05dh, 064h
    db 050h, 08dh, 045h, 03ch, 050h, 08dh, 045h, 0fch, 050h, 0ffh, 075h, 074h
    db 08dh, 045h, 008h, 050h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    db 08bh, 0f0h, 08dh, 07dh, 054h, 0d9h, 045h, 064h, 0a5h, 0d8h, 003h, 0a5h
    db 08dh, 045h, 064h, 050h, 0a5h, 0d9h, 01bh, 08dh, 045h, 02ch, 08dh, 073h
    db 004h, 050h, 08dh, 04dh, 054h, 089h, 075h, 060h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    db 050h, 08bh, 0ceh
    call ??YVector3@@QAEXAAU0@@Z
    db 08bh, 07dh, 074h, 057h, 08dh, 045h, 02ch, 050h, 08dh, 04dh, 03ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0f0h, 057h, 08dh, 045h, 014h, 050h, 08dh, 04dh, 048h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 04dh, 070h, 050h, 08dh, 045h, 0fch, 050h, 057h, 08dh, 045h, 008h
    db 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    db 0d9h, 046h, 008h, 0d8h, 048h, 008h, 08bh, 04dh, 070h, 0d9h, 046h, 004h
    db 0c7h, 045h, 038h, 000h, 000h, 080h, 03eh, 0d8h, 048h, 004h, 0deh, 0c1h
    db 0d9h, 006h, 0d8h, 008h, 08dh, 045h, 038h, 050h, 08dh, 045h, 0f0h, 050h
    db 0deh, 0c1h, 08dh, 045h, 03ch, 050h, 08dh, 045h, 020h, 0d9h, 05dh, 064h
    db 050h, 08dh, 045h, 048h, 050h, 08dh, 045h, 02ch, 050h, 057h, 08dh, 045h
    db 014h, 050h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    db 0d9h, 045h, 064h, 0d8h, 003h, 08bh, 0f0h, 08dh, 07dh, 054h, 0a5h, 0a5h
    db 0a5h, 0d9h, 01bh, 08dh, 045h, 064h, 050h, 08dh, 045h, 020h, 050h, 08dh
    db 04dh, 054h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    db 08bh, 04dh, 060h, 050h
    call ??YVector3@@QAEXAAU0@@Z
    db 08bh, 07dh, 074h, 057h, 08dh, 045h, 020h, 050h, 08dh, 04dh, 048h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 04dh, 078h, 08bh, 0f0h, 057h, 08dh, 045h, 0f0h, 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 04dh, 070h, 050h, 08dh, 045h, 02ch, 050h, 057h, 08dh, 045h, 014h
    db 050h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    db 0d9h, 046h, 008h, 0d8h, 048h, 008h, 08bh, 04dh, 070h, 0d9h, 046h, 004h
    db 0c7h, 045h, 074h, 000h, 000h, 080h, 03eh, 0d8h, 048h, 004h, 0deh, 0c1h
    db 0d9h, 006h, 0d8h, 008h, 08dh, 045h, 074h, 050h, 08dh, 045h, 0cch, 050h
    db 0deh, 0c1h, 0ffh, 075h, 078h, 08dh, 045h, 0e4h, 050h, 0d9h, 05dh, 064h
    db 08dh, 045h, 048h, 050h, 08dh, 045h, 020h, 050h, 057h, 08dh, 045h, 0f0h
    db 050h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    db 08bh, 0c8h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    db 0d9h, 045h, 064h, 0d8h, 003h, 08bh, 0f0h, 08dh, 07dh, 054h, 0a5h, 0a5h
    db 08dh, 045h, 064h, 050h, 08dh, 045h, 0e4h, 0a5h, 0d9h, 01bh, 050h, 08dh
    db 04dh, 054h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    db 08bh, 04dh, 060h, 050h
    call ??YVector3@@QAEXAAU0@@Z
    db 05fh, 05eh, 05bh, 083h, 0c5h, 068h, 0c9h, 0c2h, 010h, 000h
?AddTriangle@MassAccumulator@@QAEXAAUVector3@@00M@Z ENDP

END
