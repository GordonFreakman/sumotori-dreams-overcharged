.386
.model flat
option casemap:none

EXTERN __ftol2:PROC
EXTERN ??AFloatVector@@QAEAAMI@Z:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?MakeVector3@@YA?AUVector3@@MMM@Z:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC

EXTERN ?g_freeCameraPositionRecordScale@@3MB:DWORD
EXTERN ?g_gameArenaHalfExtent@@3MB:DWORD
EXTERN ?g_gameCameraWorldPosition@@3UVector3@@A:BYTE
EXTERN ?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A:DWORD
EXTERN ?g_gameMainVertexBuffer@@3PAUIDirect3DVertexBuffer9@@A:DWORD
EXTERN ?g_gameMainVertexFvf@@3IA:DWORD
EXTERN ?g_gameSimulationStep@@3MA:DWORD
EXTERN ?g_waterGridHeight@@3HA:DWORD
EXTERN ?g_waterGridWidth@@3HA:DWORD
EXTERN ?g_waterHeights@@3VFloatVector@@A:BYTE

.code

; FUNCTION: SUMO 0x0040c157
; FUNCTION: EDITOR 0x0040c179
PUBLIC ?RenderWaterSurface@@YAXXZ
?RenderWaterSurface@@YAXXZ PROC
    DB 055h
    DB 08dh, 06ch, 024h, 088h
    DB 081h, 0ech, 0cch, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_waterHeights@@3VFloatVector@@A+4]
    cmp eax, DWORD PTR [?g_waterHeights@@3VFloatVector@@A]
    DB 00fh, 086h, 0d0h, 003h, 000h, 000h
    mov eax, DWORD PTR [?g_waterGridWidth@@3HA]
    DB 053h
    mov edx, DWORD PTR [?g_gameMainVertexBuffer@@3PAUIDirect3DVertexBuffer9@@A]
    DB 056h
    DB 057h
    DB 08bh, 03ah
    DB 08dh, 048h, 001h
    DB 089h, 04dh, 004h
    DB 068h, 000h, 020h, 000h, 000h
    DB 08dh, 04dh, 070h
    DB 051h
    mov ecx, DWORD PTR [?g_waterGridHeight@@3HA]
    DB 00fh, 0afh, 0c8h
    DB 033h, 0f6h
    DB 089h, 045h, 0fch
    DB 089h, 045h, 008h
    DB 08dh, 004h, 0c9h
    DB 0c1h, 0e0h, 004h
    DB 050h
    DB 033h, 0dbh
    DB 043h
    DB 056h
    DB 052h
    DB 089h, 075h, 0f4h
    DB 089h, 05dh, 0f8h
    DB 089h, 05dh, 000h
    DB 089h, 075h, 00ch
    DB 089h, 05dh, 010h
    DB 089h, 075h, 014h
    DB 089h, 05dh, 018h
    DB 089h, 05dh, 01ch
    DB 089h, 075h, 020h
    DB 089h, 075h, 024h
    DB 089h, 075h, 028h
    DB 089h, 05dh, 02ch
    DB 089h, 075h, 030h
    DB 089h, 05dh, 034h
    DB 089h, 05dh, 038h
    DB 0ffh, 057h, 02ch
    mov eax, DWORD PTR [?g_waterGridHeight@@3HA]
    DB 048h
    DB 085h, 0c0h
    DB 089h, 075h, 074h
    DB 089h, 075h, 068h
    DB 00fh, 08eh, 011h, 002h, 000h, 000h
    mov eax, DWORD PTR [?g_waterGridWidth@@3HA]
    DB 048h
    DB 085h, 0c0h
    DB 089h, 075h, 060h
    DB 00fh, 08eh, 0ebh, 001h, 000h, 000h
    DB 0dbh, 045h, 068h
    DB 0d9h, 05dh, 048h
    DB 0ffh, 075h, 074h
    mov esi, OFFSET ?g_waterHeights@@3VFloatVector@@A
    DB 08bh, 0ceh
    call ??AFloatVector@@QAEAAMI@Z
    DB 08bh, 04dh, 074h
    DB 08bh, 0f8h
    mov eax, DWORD PTR [?g_waterGridWidth@@3HA]
    DB 003h, 0c8h
    DB 051h
    DB 08bh, 0ceh
    call ??AFloatVector@@QAEAAMI@Z
    DB 0ffh, 075h, 074h
    DB 08bh, 0ceh
    DB 089h, 045h, 06ch
    call ??AFloatVector@@QAEAAMI@Z
    DB 089h, 045h, 064h
    DB 08bh, 045h, 074h
    DB 040h
    DB 050h
    DB 08bh, 0ceh
    DB 089h, 045h, 04ch
    call ??AFloatVector@@QAEAAMI@Z
    DB 0d9h, 007h
    DB 08bh, 04dh, 06ch
    DB 0d8h, 021h
    DB 08bh, 04dh, 064h
    DB 083h, 0ech, 00ch
    DB 0d9h, 05ch, 024h, 008h
    fld DWORD PTR [?g_gameSimulationStep@@3MA]
    DB 0d9h, 05ch, 024h, 004h
    DB 0d9h, 001h
    DB 0d8h, 020h
    DB 08dh, 045h, 0d0h
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 050h
    DB 0a5h
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 08dh, 04dh, 050h
    DB 0a5h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ffh, 075h, 074h
    mov ecx, OFFSET ?g_waterHeights@@3VFloatVector@@A
    DB 0ddh, 0d8h
    call ??AFloatVector@@QAEAAMI@Z
    DB 0d9h, 045h, 048h
    DB 083h, 0ech, 00ch
    fmul DWORD PTR [?g_gameSimulationStep@@3MA]
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 000h
    DB 08dh, 045h, 0b8h
    DB 0d9h, 05ch, 024h, 004h
    DB 0dbh, 045h, 060h
    fmul DWORD PTR [?g_gameSimulationStep@@3MA]
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 08bh, 0f0h
    DB 08dh, 07dh, 0dch
    DB 0a5h
    DB 083h, 0c4h, 010h
    DB 0a5h
    push OFFSET ?g_gameCameraWorldPosition@@3UVector3@@A
    DB 08dh, 045h, 03ch
    DB 050h
    DB 08dh, 04dh, 0dch
    DB 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 0d9h, 045h, 044h
    DB 0d8h, 04dh, 058h
    DB 0d9h, 045h, 040h
    DB 0d8h, 04dh, 054h
    DB 0deh, 0c1h
    DB 0d9h, 045h, 03ch
    DB 0d8h, 04dh, 050h
    DB 0deh, 0c1h
    DB 0dch, 0c0h
    DB 08dh, 045h, 064h
    DB 0d9h, 05dh, 064h
    DB 050h
    DB 08dh, 045h, 0c4h
    DB 050h
    DB 08dh, 04dh, 050h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    DB 050h
    DB 08dh, 045h, 0e8h
    DB 050h
    DB 08dh, 04dh, 03ch
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 08dh, 04dh, 0e8h
    call ?Normalize@Vector3@@QAEMXZ
    DB 0ddh, 0d8h
    DB 0d9h, 045h, 0ech
    fmul DWORD PTR [?g_gameArenaHalfExtent@@3MB]
    fadd DWORD PTR [?g_freeCameraPositionRecordScale@@3MB]
    call __ftol2
    DB 069h, 0c0h, 001h, 004h, 003h, 001h
    DB 005h, 0c0h, 000h, 000h, 000h
    DB 033h, 0f6h
    DB 089h, 045h, 064h
    DB 089h, 075h, 06ch
    DB 0ebh, 006h
    DB 08bh, 075h, 06ch
    DB 08bh, 045h, 064h
    DB 08bh, 04dh, 070h
    DB 089h, 041h, 00ch
    DB 08bh, 044h, 035h, 0f4h
    DB 003h, 045h, 074h
    mov ecx, OFFSET ?g_waterHeights@@3VFloatVector@@A
    DB 050h
    call ??AFloatVector@@QAEAAMI@Z
    DB 08bh, 04ch, 035h, 024h
    DB 003h, 04dh, 068h
    DB 083h, 0ech, 00ch
    DB 089h, 04dh, 05ch
    DB 0dbh, 045h, 05ch
    fmul DWORD PTR [?g_gameSimulationStep@@3MA]
    DB 0d9h, 05ch, 024h, 008h
    DB 0d9h, 000h
    DB 08bh, 044h, 035h, 00ch
    DB 003h, 045h, 060h
    DB 0d9h, 05ch, 024h, 004h
    DB 089h, 045h, 05ch
    DB 0dbh, 045h, 05ch
    DB 08dh, 045h, 0ach
    fmul DWORD PTR [?g_gameSimulationStep@@3MA]
    DB 0d9h, 01ch, 024h
    DB 050h
    call ?MakeVector3@@YA?AUVector3@@MMM@Z
    DB 0d9h, 0eeh
    DB 08bh, 07dh, 070h
    DB 083h, 045h, 06ch, 004h
    DB 08bh, 0f0h
    DB 0a5h
    DB 0a5h
    DB 0a5h
    DB 08bh, 045h, 070h
    DB 083h, 0c4h, 010h
    DB 0d9h, 058h, 010h
    DB 08bh, 045h, 070h
    DB 0d9h, 0eeh
    DB 0d9h, 058h, 014h
    DB 083h, 045h, 070h, 018h
    DB 083h, 07dh, 06ch, 018h
    DB 00fh, 08ch, 076h, 0ffh, 0ffh, 0ffh
    DB 08bh, 045h, 04ch
    DB 0ffh, 045h, 060h
    DB 089h, 045h, 074h
    mov eax, DWORD PTR [?g_waterGridWidth@@3HA]
    DB 048h
    DB 039h, 045h, 060h
    DB 00fh, 08ch, 01dh, 0feh, 0ffh, 0ffh
    DB 033h, 0f6h
    DB 0ffh, 045h, 074h
    DB 0ffh, 045h, 068h
    mov eax, DWORD PTR [?g_waterGridHeight@@3HA]
    DB 048h
    DB 039h, 045h, 068h
    DB 00fh, 08ch, 0efh, 0fdh, 0ffh, 0ffh
    mov eax, DWORD PTR [?g_gameMainVertexBuffer@@3PAUIDirect3DVertexBuffer9@@A]
    DB 08bh, 008h
    DB 050h
    DB 0ffh, 051h, 030h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 06ah, 003h
    DB 05fh
    DB 057h
    DB 053h
    DB 056h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 057h
    DB 06ah, 002h
    DB 056h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 056h
    DB 057h
    DB 056h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 053h
    DB 053h
    DB 053h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 057h
    DB 06ah, 004h
    DB 056h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 057h
    DB 06ah, 005h
    DB 056h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 056h
    DB 06ah, 006h
    DB 056h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 053h
    DB 06ah, 004h
    DB 053h
    DB 050h
    DB 0ffh, 091h, 00ch, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 053h
    DB 06ah, 01bh
    DB 050h
    DB 0ffh, 091h, 0e4h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 06ah, 006h
    DB 06ah, 013h
    DB 050h
    DB 0ffh, 091h, 0e4h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 06ah, 005h
    DB 06ah, 014h
    DB 050h
    DB 0ffh, 091h, 0e4h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 053h
    DB 06ah, 016h
    DB 050h
    DB 0ffh, 091h, 0e4h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 056h
    DB 06ah, 034h
    DB 050h
    DB 0ffh, 091h, 0e4h, 000h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    push DWORD PTR [?g_gameMainVertexFvf@@3IA]
    DB 08bh, 008h
    DB 050h
    DB 0ffh, 091h, 064h, 001h, 000h, 000h
    mov edx, DWORD PTR [?g_waterGridHeight@@3HA]
    mov ebx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 04ah
    DB 04bh
    DB 00fh, 0afh, 0d3h
    DB 0d1h, 0e2h
    DB 052h
    DB 056h
    DB 06ah, 004h
    DB 050h
    DB 0ffh, 091h, 044h, 001h, 000h, 000h
    mov eax, DWORD PTR [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    DB 08bh, 008h
    DB 057h
    DB 06ah, 016h
    DB 050h
    DB 0ffh, 091h, 0e4h, 000h, 000h, 000h
    DB 05fh
    DB 05eh
    DB 05bh
    DB 083h, 0c5h, 078h
    DB 0c9h
    DB 0c3h
?RenderWaterSurface@@YAXXZ ENDP

END
