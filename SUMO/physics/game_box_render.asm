.686
.model flat
option casemap:none

EXTERN __ftol2:PROC
EXTERN ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?Resize@RuntimeVector3Vector@@QAEXI@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC

EXTERN ?g_gameArenaExtent@@3MA:DWORD
EXTERN ?g_gameBoxIndexPairCursor@@3PAEA:DWORD
EXTERN ?g_gameBoxLightDirection@@3UVector3@@A:BYTE
EXTERN ?g_gameBoxLightScale@@3MB:DWORD
EXTERN ?g_gameBoxLitVertexCursor@@3PAEA:DWORD
EXTERN ?g_gameBoxNegativeLightScale@@3MB:DWORD
EXTERN ?g_gameBoxShadowPositionCursor@@3PAEA:DWORD
EXTERN ?g_gameBoxTextureTriangleCounts@@3EA:BYTE
EXTERN ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A:BYTE
EXTERN ?g_textureCenterFloat@@3MB:DWORD
EXTERN ?g_vectorZero@@3MB:DWORD

.code

; FUNCTION: SUMO 0x0040c5a5
; FUNCTION: EDITOR 0x0040c5c7
PUBLIC ?Render@GameBox@@QAEXXZ
?Render@GameBox@@QAEXXZ PROC
    DB 055h
    DB 08dh, 06ch, 024h, 088h
    DB 081h, 0ech, 0e0h, 000h, 000h, 000h
    DB 053h
    DB 08bh, 0d9h
    DB 080h, 07bh, 058h, 000h
    DB 00fh, 085h, 0dfh, 004h, 000h, 000h
    DB 08bh, 043h, 004h
    DB 02bh, 003h
    DB 056h
    DB 0c1h, 0f8h, 004h
    DB 057h
    DB 040h
    mov esi, OFFSET ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A
    DB 050h
    DB 08bh, 0ceh
    call ?Resize@RuntimeVector3Vector@@QAEXI@Z
    DB 06ah, 000h
    DB 08bh, 0ceh
    call ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z
    DB 08bh, 00bh
    DB 03bh, 04bh, 004h
    DB 089h, 045h, 070h
    DB 089h, 04dh, 074h
    DB 073h, 03ch
    DB 0ebh, 003h
    DB 08bh, 04dh, 074h
    DB 08dh, 083h, 084h, 000h, 000h, 000h
    DB 050h
    DB 08dh, 045h, 028h
    DB 050h
    DB 08dh, 043h, 060h
    DB 050h
    DB 08dh, 045h, 01ch
    DB 050h
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 07dh, 070h
    DB 083h, 045h, 074h, 010h
    DB 083h, 045h, 070h, 00ch
    DB 08bh, 0f0h
    DB 08bh, 045h, 074h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 03bh, 043h, 004h
    DB 072h, 0c6h
    push OFFSET ?g_gameBoxLightDirection@@3UVector3@@A
    DB 08dh, 045h, 050h
    DB 050h
    DB 08dh, 04bh, 060h
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 08bh, 073h, 010h
    DB 03bh, 073h, 014h
    DB 089h, 075h, 074h
    DB 00fh, 083h, 0d9h, 002h, 000h, 000h
    DB 0ebh, 003h
    DB 08bh, 075h, 074h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04eh, 004h
    DB 0d9h, 045h, 058h
    DB 0d8h, 04eh, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 050h
    DB 0d8h, 00eh
    DB 0deh, 0c1h
    fcomp DWORD PTR [?g_vectorZero@@3MB]
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 005h
    DB 033h, 0c0h
    DB 040h
    DB 0ebh, 002h
    DB 033h, 0c0h
    DB 088h, 046h, 020h
    DB 08dh, 07dh, 038h
    DB 0a5h
    DB 0a5h
    DB 08dh, 04dh, 038h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08dh, 07dh, 01ch
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 03ch
    DB 0d8h, 04dh, 03ch
    DB 0d9h, 045h, 038h
    DB 0d8h, 04dh, 038h
    DB 0d8h, 0d9h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 016h
    DB 0ddh, 0d8h
    DB 08dh, 075h, 010h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 010h
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 014h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 018h
    DB 0ebh, 039h
    DB 0d9h, 0e8h
    DB 08dh, 075h, 004h
    DB 0d9h, 05dh, 004h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 008h
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 00ch
    DB 0d9h, 045h, 040h
    DB 0d8h, 04dh, 040h
    DB 0a5h
    DB 0a5h
    DB 0deh, 0d9h
    DB 0a5h
    DB 0dfh, 0e0h
    DB 0f6h, 0c4h, 041h
    DB 075h, 018h
    DB 0d9h, 0eeh
    DB 08dh, 075h, 0f8h
    DB 0d9h, 05dh, 0f8h
    DB 08dh, 07dh, 01ch
    DB 0d9h, 0e8h
    DB 0d9h, 05dh, 0fch
    DB 0d9h, 0eeh
    DB 0d9h, 05dh, 000h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08dh, 045h, 038h
    DB 050h
    DB 08dh, 045h, 098h
    DB 050h
    DB 08dh, 04dh, 01ch
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 060h
    DB 0a5h
    DB 0a5h
    DB 08dh, 04dh, 060h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 08dh, 045h, 038h
    DB 050h
    DB 0ddh, 0d8h
    DB 08dh, 045h, 0a4h
    DB 050h
    DB 08dh, 04dh, 060h
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    fld DWORD PTR [?g_textureCenterFloat@@3MB]
    DB 08bh, 0f0h
    DB 0d9h, 045h, 058h
    DB 08dh, 07dh, 044h
    DB 0d8h, 04dh, 040h
    DB 0a5h
    DB 0d9h, 045h, 054h
    DB 0d8h, 04dh, 03ch
    DB 0a5h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 050h
    DB 0a5h
    DB 0d8h, 04dh, 038h
    DB 0deh, 0c1h
    fmul DWORD PTR [?g_gameBoxNegativeLightScale@@3MB]
    DB 0d8h, 0c1h
    call __ftol2
    DB 0d9h, 045h, 048h
    DB 0d8h, 04dh, 054h
    DB 08bh, 0f0h
    DB 0d9h, 045h, 04ch
    DB 0f7h, 0deh
    DB 0d8h, 04dh, 058h
    DB 0c1h, 0e6h, 008h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 050h
    DB 0d8h, 04dh, 044h
    DB 0deh, 0c1h
    fmul DWORD PTR [?g_gameBoxLightScale@@3MB]
    DB 0d8h, 0e1h
    call __ftol2
    DB 0d9h, 045h, 064h
    DB 0d8h, 04dh, 054h
    DB 003h, 0f0h
    DB 0d9h, 045h, 068h
    DB 0c1h, 0e6h, 008h
    DB 0d8h, 04dh, 058h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 060h
    DB 0d8h, 04dh, 050h
    DB 0deh, 0c1h
    fmul DWORD PTR [?g_gameBoxLightScale@@3MB]
    DB 0d8h, 0e9h
    call __ftol2
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 060h
    DB 02bh, 0c6h
    DB 0d8h, 04bh, 034h
    DB 089h, 045h, 06ch
    DB 0d9h, 05dh, 060h
    DB 0d9h, 045h, 064h
    DB 0d8h, 04bh, 034h
    DB 0d9h, 05dh, 064h
    DB 0d9h, 045h, 068h
    DB 0d8h, 04bh, 034h
    DB 0d9h, 05dh, 068h
    DB 0d9h, 045h, 044h
    DB 0d8h, 04bh, 034h
    DB 08bh, 04dh, 074h
    DB 0d9h, 05dh, 044h
    DB 0d9h, 045h, 048h
    DB 06ah, 002h
    DB 0d8h, 04bh, 034h
    DB 058h
    DB 039h, 041h, 01ch
    DB 089h, 045h, 070h
    DB 0d9h, 05dh, 048h
    DB 0d9h, 045h, 04ch
    DB 0d8h, 04bh, 034h
    DB 0d9h, 05dh, 04ch
    DB 00fh, 08eh, 01ah, 001h, 000h, 000h
    DB 083h, 065h, 028h, 000h
    DB 0ebh, 003h
    DB 08bh, 045h, 070h
    DB 08dh, 048h, 0ffh
    DB 089h, 045h, 030h
    DB 08bh, 043h, 030h
    DB 066h, 08bh, 004h, 045h
    DD OFFSET ?g_gameBoxTextureTriangleCounts@@3EA
    DB 089h, 04dh, 02ch
    mov ecx, DWORD PTR [?g_gameBoxIndexPairCursor@@3PAEA]
    DB 066h, 089h, 001h
    DB 08bh, 043h, 030h
    mov ecx, DWORD PTR [?g_gameBoxIndexPairCursor@@3PAEA]
    DB 08dh, 004h, 045h
    DD OFFSET ?g_gameBoxTextureTriangleCounts@@3EA
    DB 066h, 0ffh, 000h
    DB 066h, 08bh, 043h, 030h
    DB 066h, 089h, 041h, 002h
    add DWORD PTR [?g_gameBoxIndexPairCursor@@3PAEA], 4
    DB 083h, 065h, 05ch, 000h
    DB 08bh, 045h, 05ch
    DB 08bh, 044h, 085h, 028h
    DB 08bh, 04dh, 074h
    DB 08bh, 049h, 010h
    DB 0c1h, 0e0h, 003h
    DB 0ffh, 074h, 008h, 004h
    mov ecx, OFFSET ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A
    DB 089h, 045h, 034h
    call ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z
    mov edi, DWORD PTR [?g_gameBoxLitVertexCursor@@3PAEA]
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 075h, 074h
    DB 08bh, 07dh, 034h
    DB 08dh, 043h, 020h
    DB 050h
    DB 08dh, 045h, 0bch
    DB 050h
    DB 08bh, 046h, 010h
    DB 08bh, 04ch, 007h, 004h
    DB 0c1h, 0e1h, 004h
    DB 003h, 00bh
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 068h
    DB 0d8h, 048h, 008h
    DB 0d9h, 045h, 064h
    DB 0d8h, 048h, 004h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 060h
    DB 0d8h, 008h
    mov eax, DWORD PTR [?g_gameBoxLitVertexCursor@@3PAEA]
    DB 0deh, 0c1h
    DB 0d9h, 058h, 010h
    DB 08dh, 043h, 020h
    DB 050h
    DB 08dh, 045h, 0b0h
    DB 050h
    DB 08bh, 046h, 010h
    DB 08bh, 04ch, 007h, 004h
    DB 0c1h, 0e1h, 004h
    DB 003h, 00bh
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 04ch
    DB 0d8h, 048h, 008h
    DB 08bh, 04dh, 06ch
    DB 0d9h, 045h, 048h
    DB 0d8h, 048h, 004h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 044h
    DB 0d8h, 008h
    mov eax, DWORD PTR [?g_gameBoxLitVertexCursor@@3PAEA]
    DB 0deh, 0c1h
    DB 0d9h, 058h, 014h
    mov eax, DWORD PTR [?g_gameBoxLitVertexCursor@@3PAEA]
    DB 089h, 048h, 00ch
    add DWORD PTR [?g_gameBoxLitVertexCursor@@3PAEA], 018h
    DB 0ffh, 045h, 05ch
    DB 083h, 07dh, 05ch, 003h
    DB 00fh, 08ch, 043h, 0ffh, 0ffh, 0ffh
    DB 0ffh, 045h, 070h
    DB 08bh, 04dh, 070h
    DB 08bh, 0c6h
    DB 03bh, 048h, 01ch
    DB 00fh, 08ch, 0ech, 0feh, 0ffh, 0ffh
    DB 083h, 045h, 074h, 024h
    DB 08bh, 045h, 074h
    DB 03bh, 043h, 014h
    DB 00fh, 082h, 029h, 0fdh, 0ffh, 0ffh
    fld DWORD PTR [?g_gameArenaExtent@@3MA]
    DB 08dh, 045h, 06ch
    DB 050h
    DB 0d9h, 0e0h
    DB 08dh, 045h, 028h
    DB 0d9h, 05dh, 06ch
    DB 050h
    mov ecx, OFFSET ?g_gameBoxLightDirection@@3UVector3@@A
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 08bh, 043h, 018h
    DB 0e9h, 049h, 001h, 000h, 000h
    DB 08bh, 048h, 008h
    DB 08ah, 049h, 020h
    DB 084h, 0c9h
    DB 075h, 00fh
    DB 08bh, 050h, 00ch
    DB 080h, 07ah, 020h, 001h
    DB 075h, 006h
    DB 083h, 065h, 070h, 000h
    DB 0ebh, 01dh
    DB 08bh, 050h, 00ch
    DB 080h, 07ah, 020h, 000h
    DB 00fh, 085h, 020h, 001h, 000h, 000h
    DB 080h, 0f9h, 001h
    DB 00fh, 085h, 017h, 001h, 000h, 000h
    DB 0c7h, 045h, 070h, 001h, 000h, 000h, 000h
    DB 0ffh, 030h
    mov ecx, OFFSET ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A
    call ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z
    DB 08bh, 04dh, 070h
    DB 083h, 0f1h, 001h
    DB 08dh, 00ch, 049h
    DB 0c1h, 0e1h, 002h
    DB 08dh, 07ch, 00dh, 0c8h
    DB 08bh, 0f0h
    DB 08bh, 045h, 074h
    DB 0ffh, 070h, 004h
    DB 0a5h
    DB 0a5h
    DB 089h, 04dh, 06ch
    mov ecx, OFFSET ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A
    DB 0a5h
    call ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z
    DB 08bh, 04dh, 070h
    DB 08dh, 00ch, 049h
    DB 0c1h, 0e1h, 002h
    DB 08bh, 0f0h
    DB 08dh, 07ch, 00dh, 0c8h
    DB 0a5h
    DB 08dh, 045h, 028h
    DB 050h
    DB 08dh, 045h, 0b0h
    DB 050h
    DB 08bh, 045h, 074h
    DB 0ffh, 070h, 004h
    DB 0a5h
    DB 089h, 04dh, 034h
    mov ecx, OFFSET ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A
    DB 0a5h
    call ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 07dh, 06ch
    DB 08bh, 0f0h
    DB 08dh, 07ch, 03dh, 0e0h
    DB 0a5h
    DB 08dh, 045h, 028h
    DB 050h
    DB 08dh, 045h, 0bch
    DB 050h
    DB 08bh, 045h, 074h
    DB 0ffh, 030h
    DB 0a5h
    mov ecx, OFFSET ?g_gameBoxTransformedPoints@@3VRuntimeVector3Vector@@A
    DB 0a5h
    call ??ARuntimeVector3Vector@@QAEAAUVector3@@I@Z
    DB 08bh, 0c8h
    call ??HVector3@@QAE?AU0@AAU0@@Z
    DB 08bh, 07dh, 034h
    DB 08dh, 07ch, 03dh, 0e0h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    mov edi, DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA]
    DB 08dh, 075h, 0c8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 06ah, 00ch
    DB 058h
    add DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA], eax
    mov edi, DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA]
    DB 08dh, 075h, 0d4h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    add DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA], eax
    mov edi, DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA]
    DB 08dh, 075h, 0e0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    add DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA], eax
    mov edi, DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA]
    DB 08dh, 075h, 0c8h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    add DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA], eax
    mov edi, DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA]
    DB 08dh, 075h, 0e0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    add DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA], eax
    mov edi, DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA]
    DB 08dh, 075h, 0ech
    DB 0a5h
    DB 0a5h
    DB 0a5h
    add DWORD PTR [?g_gameBoxShadowPositionCursor@@3PAEA], eax
    DB 08bh, 045h, 074h
    DB 083h, 0c0h, 010h
    DB 03bh, 043h, 01ch
    DB 089h, 045h, 074h
    DB 00fh, 082h, 0abh, 0feh, 0ffh, 0ffh
    DB 05fh
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 078h
    DB 0c9h
    DB 0c3h
?Render@GameBox@@QAEXXZ ENDP

END
