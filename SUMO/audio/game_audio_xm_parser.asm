.686
.model flat
option casemap:none

EXTERN _InvokeGameAudioBlockHead:PROC
EXTERN _InvokeGameAudioBlockTail:PROC
EXTERN _ReleaseGameAudioOwnedBlock:PROC
EXTERN _GameAudioNoOpCallback:PROC
EXTERN _GameAudioParsedTick:DWORD
EXTERN _calloc:PROC
EXTERN _free:PROC
EXTERN @__security_check_cookie@4:PROC
EXTERN ___security_cookie:DWORD
EXTERN _g_gameAudioEmptySample:DWORD
EXTERN _g_gameAudioXmSignature:BYTE

.code

; FUNCTION: SUMO 0x0041895c
; FUNCTION: EDITOR 0x0041897e
PUBLIC _ParseGameAudioModule
_ParseGameAudioModule PROC
    DB 055h, 08dh, 0ach, 024h, 048h, 0ffh, 0ffh, 0ffh, 081h, 0ech, 034h, 001h, 000h, 000h, 0a1h
    DD ___security_cookie
    DB 053h, 056h, 08bh, 0b5h, 0c4h, 000h, 000h, 000h, 033h, 0dbh, 053h, 053h, 056h, 089h, 085h, 0b4h
    DB 000h, 000h, 000h, 089h, 05dh, 090h
    call _InvokeGameAudioBlockHead
    DB 056h, 08dh, 045h, 0b4h, 06ah, 011h, 050h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 018h, 033h, 0c0h, 08ah, 04ch, 005h, 0b4h, 03ah, 088h
    DD _g_gameAudioXmSignature
    DB 00fh, 085h, 0c8h, 001h, 000h, 000h, 040h, 083h, 0f8h, 011h, 07ch, 0eah, 057h, 08bh, 0bdh, 0c0h
    DB 000h, 000h, 000h, 053h, 06ah, 03ch, 056h, 0c7h, 087h, 05ch, 001h, 000h, 000h
    DD _GameAudioParsedTick
    DB 0c6h, 087h, 028h, 001h, 000h, 000h, 040h
    call _InvokeGameAudioBlockHead
    DB 056h, 08dh, 045h, 088h, 06ah, 004h, 050h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 05fh, 010h, 06ah, 006h, 053h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 045h, 090h, 06ah, 002h, 050h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 047h, 020h, 068h, 008h, 001h, 000h, 000h, 050h
    call _InvokeGameAudioBlockTail
    DB 08bh, 045h, 088h, 06ah, 000h, 083h, 0c0h, 03ch, 050h, 056h
    call _InvokeGameAudioBlockHead
    DB 083h, 067h, 018h, 000h, 083h, 0c4h, 048h, 066h, 083h, 03bh, 000h, 07eh, 026h, 0c7h, 045h, 0ach
    DB 0d8h, 0ffh, 0ffh, 0ffh, 029h, 07dh, 0ach, 08dh, 047h, 028h, 00fh, 0b6h, 008h, 03bh, 04fh, 018h
    DB 07ch, 004h, 041h, 089h, 04fh, 018h, 08bh, 04dh, 0ach, 00fh, 0bfh, 013h, 040h, 003h, 0c8h, 03bh
    DB 0cah, 07ch, 0e7h, 00fh, 0b7h, 045h, 090h, 08bh, 04fh, 018h, 03bh, 0c8h, 07eh, 002h, 08bh, 0c1h
    DB 089h, 047h, 01ch, 0c1h, 0e0h, 003h, 06ah, 001h, 050h
    call _calloc
    DB 083h, 065h, 0a0h, 000h, 066h, 083h, 07dh, 090h, 000h, 059h, 059h, 089h, 007h, 00fh, 086h, 05fh
    DB 001h, 000h, 000h, 08bh, 007h, 08bh, 04dh, 0a0h, 056h, 08dh, 01ch, 0c8h, 08dh, 045h, 08ch, 06ah
    DB 004h, 050h, 0c6h, 045h, 0abh, 000h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 045h, 0abh, 06ah, 001h, 050h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 045h, 0a4h, 06ah, 002h, 050h
    call _InvokeGameAudioBlockTail
    DB 00fh, 0b7h, 045h, 0a4h, 056h, 089h, 003h, 08dh, 045h, 09eh, 06ah, 002h, 050h
    call _InvokeGameAudioBlockTail
    DB 00fh, 0bfh, 047h, 014h, 00fh, 0afh, 003h, 08dh, 004h, 080h, 06ah, 001h, 050h
    call _calloc
    DB 083h, 0c4h, 038h, 089h, 043h, 004h, 066h, 083h, 07dh, 09eh, 000h, 00fh, 086h, 0eah, 000h, 000h
    DB 000h, 083h, 065h, 094h, 000h, 089h, 045h, 0ach, 00fh, 0bfh, 047h, 014h, 00fh, 0afh, 003h, 085h
    DB 0c0h, 00fh, 08eh, 0d4h, 000h, 000h, 000h, 08bh, 045h, 0ach, 040h, 089h, 045h, 098h, 056h, 08dh
    DB 045h, 0b3h, 06ah, 001h, 050h
    call _InvokeGameAudioBlockTail
    DB 08ah, 045h, 0b3h, 083h, 0c4h, 00ch, 084h, 0c0h, 079h, 06dh, 0a8h, 001h, 074h, 00eh, 056h, 06ah
    DB 001h, 0ffh, 075h, 0ach
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 00ch, 0f6h, 045h, 0b3h, 002h, 074h, 00eh, 056h, 06ah, 001h, 0ffh, 075h, 098h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 00ch, 0f6h, 045h, 0b3h, 004h, 074h, 010h, 08bh, 045h, 098h, 056h, 040h, 06ah, 001h
    DB 050h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 00ch, 0f6h, 045h, 0b3h, 008h, 074h, 012h, 08bh, 045h, 098h, 056h, 083h, 0c0h, 002h
    DB 06ah, 001h, 050h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 00ch, 0f6h, 045h, 0b3h, 010h, 074h, 028h, 08bh, 045h, 098h, 056h, 06ah, 001h, 083h
    DB 0c0h, 003h, 050h, 0ebh, 014h, 032h, 0c0h, 0e9h, 06eh, 004h, 000h, 000h, 074h, 005h, 08bh, 04dh
    DB 0ach, 088h, 001h, 056h, 06ah, 004h, 0ffh, 075h, 098h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 00ch, 08bh, 04dh, 0ach, 080h, 039h, 061h, 075h, 003h, 0c6h, 001h, 0ffh, 08bh, 045h
    DB 098h, 080h, 038h, 080h, 076h, 003h, 0c6h, 000h, 000h, 083h, 0c0h, 005h, 089h, 045h, 098h, 00fh
    DB 0bfh, 047h, 014h, 00fh, 0afh, 003h, 083h, 0c1h, 005h, 0ffh, 045h, 094h, 039h, 045h, 094h, 089h
    DB 04dh, 0ach, 00fh, 08ch, 033h, 0ffh, 0ffh, 0ffh, 00fh, 0b7h, 045h, 090h, 0ffh, 045h, 0a0h, 039h
    DB 045h, 0a0h, 00fh, 08ch, 0a1h, 0feh, 0ffh, 0ffh, 00fh, 0b7h, 045h, 090h, 08bh, 04fh, 018h, 03bh
    DB 0c1h, 07dh, 033h, 089h, 045h, 0a0h, 08bh, 007h, 08bh, 04dh, 0a0h, 08dh, 01ch, 0c8h, 0c7h, 003h
    DB 040h, 000h, 000h, 000h, 00fh, 0bfh, 047h, 014h, 08dh, 004h, 080h, 0c1h, 0e0h, 006h, 06ah, 001h
    DB 050h
    call _calloc
    DB 0ffh, 045h, 0a0h, 089h, 043h, 004h, 08bh, 045h, 0a0h, 03bh, 047h, 018h, 059h, 059h, 07ch, 0d0h
    DB 00fh, 0bfh, 047h, 020h, 069h, 0c0h, 054h, 001h, 000h, 000h, 06ah, 001h, 050h
    call _calloc
    DB 089h, 047h, 004h, 033h, 0c0h, 066h, 039h, 047h, 020h, 059h, 059h, 089h, 045h, 0a0h, 00fh, 08eh
    DB 0adh, 003h, 000h, 000h, 089h, 045h, 098h, 0ebh, 006h, 08bh, 0b5h, 0c4h, 000h, 000h, 000h, 08bh
    DB 05fh, 004h, 003h, 05dh, 098h, 056h
    call _ReleaseGameAudioOwnedBlock
    DB 056h, 089h, 045h, 0ach, 08dh, 045h, 08ch, 06ah, 004h, 050h
    call _InvokeGameAudioBlockTail
    DB 08bh, 045h, 08ch, 001h, 045h, 0ach, 06ah, 001h, 06ah, 017h, 056h
    call _InvokeGameAudioBlockHead
    DB 056h, 08dh, 045h, 0a4h, 06ah, 002h, 050h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 028h, 066h, 083h, 07dh, 0a4h, 010h, 00fh, 087h, 075h, 003h, 000h, 000h, 00fh, 0b7h
    DB 045h, 0a4h, 089h, 003h, 066h, 083h, 07dh, 0a4h, 000h, 00fh, 086h, 00fh, 003h, 000h, 000h, 056h
    DB 08dh, 045h, 084h, 06ah, 004h, 050h, 0c6h, 045h, 0b3h, 000h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 043h, 044h, 06ah, 060h, 050h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 083h, 0a4h, 000h, 000h, 000h, 06ah, 030h, 050h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 083h, 0f4h, 000h, 000h, 000h, 06ah, 030h, 050h
    call _InvokeGameAudioBlockTail
    DB 056h, 08dh, 083h, 044h, 001h, 000h, 000h, 06ah, 010h, 050h
    call _InvokeGameAudioBlockTail
    DB 066h, 0d1h, 0a3h, 052h, 001h, 000h, 000h, 083h, 0c4h, 03ch, 080h, 0bbh, 044h, 001h, 000h, 000h
    DB 002h, 073h, 007h, 0c6h, 083h, 04ch, 001h, 000h, 000h, 000h, 080h, 0bbh, 045h, 001h, 000h, 000h
    DB 002h, 073h, 007h, 0c6h, 083h, 04dh, 001h, 000h, 000h, 000h, 06ah, 000h, 0ffh, 075h, 0ach, 056h
    call _InvokeGameAudioBlockHead
    DB 083h, 065h, 09ch, 000h, 083h, 0c4h, 00ch, 066h, 083h, 07dh, 0a4h, 000h, 00fh, 086h, 02dh, 001h
    DB 000h, 000h, 08dh, 043h, 004h, 089h, 045h, 094h, 06ah, 001h, 06ah, 030h
    call _calloc
    DB 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 08bh, 0f0h, 08bh, 045h, 094h, 089h, 030h, 08dh, 046h, 004h
    DB 06ah, 00eh, 050h
    call _InvokeGameAudioBlockTail
    DB 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 08dh, 045h, 0abh, 06ah, 001h, 050h, 0c6h, 046h, 01dh, 001h
    DB 0c6h, 046h, 01ch, 008h
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 020h, 0f6h, 045h, 0abh, 001h, 074h, 00ah, 08ah, 046h, 01dh, 024h, 0feh, 00ch, 002h
    DB 088h, 046h, 01dh, 0f6h, 045h, 0abh, 002h, 074h, 00ah, 08ah, 046h, 01dh, 024h, 0fch, 00ch, 004h
    DB 088h, 046h, 01dh, 0f6h, 045h, 0abh, 010h, 074h, 004h, 0c6h, 046h, 01ch, 010h, 0f6h, 046h, 01dh
    DB 001h, 074h, 00ah, 08bh, 046h, 004h, 083h, 066h, 008h, 000h, 089h, 046h, 00ch, 080h, 07eh, 01ch
    DB 010h, 075h, 009h, 0d1h, 06eh, 004h, 0d1h, 06eh, 008h, 0d1h, 06eh, 00ch, 083h, 07eh, 00ch, 000h
    DB 075h, 00eh, 08bh, 046h, 004h, 083h, 066h, 008h, 000h, 089h, 046h, 00ch, 0c6h, 046h, 01dh, 001h
    DB 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 08dh, 045h, 0b3h, 06ah, 001h, 050h
    call _InvokeGameAudioBlockTail
    DB 00fh, 0b6h, 045h, 0b3h, 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 089h, 046h, 018h, 08dh, 045h, 0b3h
    DB 06ah, 001h, 050h
    call _InvokeGameAudioBlockTail
    DB 08ah, 045h, 0b3h, 06ah, 001h, 06ah, 017h, 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 088h, 046h, 01fh
    call _InvokeGameAudioBlockHead
    DB 08bh, 046h, 004h, 0d1h, 0e0h, 089h, 045h, 0ach, 08bh, 006h, 083h, 0c4h, 024h, 085h, 0c0h, 074h
    DB 007h, 050h
    call _free
    DB 059h, 083h, 07dh, 0ach, 000h, 074h, 014h, 08bh, 045h, 0ach, 083h, 0c0h, 010h, 06ah, 001h, 050h
    call _calloc
    DB 059h, 059h, 089h, 006h, 0ebh, 003h, 083h, 026h, 000h, 00fh, 0b7h, 045h, 0a4h, 0ffh, 045h, 09ch
    DB 083h, 045h, 094h, 004h, 039h, 045h, 09ch, 00fh, 082h, 0dfh, 0feh, 0ffh, 0ffh, 083h, 07dh, 09ch
    DB 010h, 073h, 019h, 08bh, 045h, 09ch, 06ah, 010h, 059h, 08dh, 07ch, 083h, 004h, 02bh, 0c8h, 0b8h
    DD _g_gameAudioEmptySample
    DB 0f3h, 0abh, 08bh, 0bdh, 0c0h, 000h, 000h, 000h, 083h, 065h, 09ch, 000h, 066h, 083h, 07dh, 0a4h
    DB 000h, 00fh, 086h, 050h, 001h, 000h, 000h, 083h, 0c3h, 004h, 089h, 05dh, 094h, 08bh, 045h, 094h
    DB 08bh, 018h, 00fh, 0b6h, 073h, 01ch, 08bh, 043h, 004h, 00fh, 0afh, 0f0h, 0c1h, 0eeh, 003h, 085h
    DB 0c0h, 00fh, 084h, 0f4h, 000h, 000h, 000h, 08dh, 044h, 000h, 010h, 06ah, 001h, 050h
    call _calloc
    DB 089h, 045h, 0ach, 08bh, 087h, 060h, 001h, 000h, 000h, 085h, 0c0h, 059h, 059h, 074h, 024h, 0ffh
    DB 075h, 09ch, 00fh, 0b6h, 04bh, 01ch, 0ffh, 075h, 0a0h, 051h, 056h, 0ffh, 075h, 0ach, 0ffh, 0d0h
    DB 06ah, 001h, 056h, 0ffh, 0b5h, 0c4h, 000h, 000h, 000h
    call _InvokeGameAudioBlockHead
    DB 083h, 0c4h, 020h, 0ebh, 012h, 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 056h, 0ffh, 075h, 0ach
    call _InvokeGameAudioBlockTail
    DB 083h, 0c4h, 00ch, 080h, 07bh, 01ch, 008h, 075h, 02ah, 08bh, 033h, 033h, 0c0h, 039h, 043h, 004h
    DB 07eh, 013h, 08bh, 055h, 0ach, 033h, 0c9h, 08ah, 02ch, 010h, 066h, 089h, 00eh, 046h, 046h, 040h
    DB 03bh, 043h, 004h, 07ch, 0edh, 0ffh, 075h, 0ach, 0c6h, 043h, 01ch, 010h
    call _free
    DB 0ebh, 00ch, 0ffh, 033h
    call _free
    DB 08bh, 045h, 0ach, 089h, 003h, 059h, 0ffh, 075h, 09ch, 0ffh, 075h, 0a0h, 053h, 053h
    call _GameAudioNoOpCallback
    DB 033h, 0f6h, 083h, 0c4h, 010h, 039h, 0b7h, 060h, 001h, 000h, 000h, 075h, 01bh, 08bh, 00bh, 033h
    DB 0d2h, 039h, 073h, 004h, 076h, 012h, 00fh, 0b7h, 001h, 003h, 0c6h, 066h, 089h, 001h, 041h, 041h
    DB 042h, 03bh, 053h, 004h, 08bh, 0f0h, 072h, 0eeh, 08ah, 04bh, 01dh, 080h, 0f9h, 004h, 08bh, 003h
    DB 075h, 012h, 08bh, 04bh, 00ch, 003h, 04bh, 008h, 08dh, 004h, 048h, 066h, 08bh, 048h, 0feh, 066h
    DB 089h, 008h, 0ebh, 015h, 080h, 0f9h, 002h, 075h, 010h, 08bh, 04bh, 008h, 08bh, 053h, 00ch, 003h
    DB 0d1h, 066h, 08bh, 00ch, 048h, 066h, 089h, 00ch, 050h, 00fh, 0b7h, 045h, 0a4h, 0ffh, 045h, 09ch
    DB 083h, 045h, 094h, 004h, 039h, 045h, 09ch, 00fh, 082h, 0deh, 0feh, 0ffh, 0ffh, 0ebh, 026h, 06ah
    DB 010h, 059h, 06ah, 000h, 0ffh, 075h, 0ach, 0b8h
    DD _g_gameAudioEmptySample
    DB 0ffh, 0b5h, 0c4h, 000h, 000h, 000h, 08dh, 07bh, 004h, 0f3h, 0abh
    call _InvokeGameAudioBlockHead
    DB 08bh, 0bdh, 0c0h, 000h, 000h, 000h, 083h, 0c4h, 00ch, 00fh, 0bfh, 047h, 020h, 0ffh, 045h, 0a0h
    DB 081h, 045h, 098h, 054h, 001h, 000h, 000h, 039h, 045h, 0a0h, 00fh, 08ch, 058h, 0fch, 0ffh, 0ffh
    DB 0b0h, 001h, 05fh, 08bh, 08dh, 0b4h, 000h, 000h, 000h, 05eh, 05bh
    call @__security_check_cookie@4
    DB 081h, 0c5h, 0b8h, 000h, 000h, 000h, 0c9h, 0c3h, 032h, 0c0h, 0ebh, 0e6h
_ParseGameAudioModule ENDP

END
