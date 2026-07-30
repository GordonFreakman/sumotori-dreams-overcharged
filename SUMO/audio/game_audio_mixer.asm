.686
.model flat
option casemap:none

EXTERN ?g_gameAudioMixerWorkspace@@3PAEA:BYTE
EXTERN ?g_gameAudioMixStep@@3IA:DWORD
EXTERN ?g_gameAudioInverseMixStep@@3MA:DWORD
EXTERN ?g_gameAudioChannelScratch@@3PAUGameAudioMixerChannel@@A:BYTE
EXTERN ?g_gameAudioChannelScratchEnd@@3EA:BYTE
EXTERN ?g_gameAudioPcmScale255@@3MB:DWORD
EXTERN ?g_gameAudioPcmScale256@@3MB:DWORD
EXTERN ?g_gameAudioUnitOver255@@3MB:DWORD
EXTERN ?g_gameAudioUnitOver256@@3MB:DWORD
EXTERN ?g_gameAudioFixedPointScale@@3MB:DWORD

.code

PUBLIC ?MixGameAudioChannels@@YAXPAXHH@Z
?MixGameAudioChannels@@YAXPAXHH@Z PROC
    db 055h, 08bh, 0ech, 08bh, 045h, 00ch, 085h, 0c0h, 053h, 056h, 057h, 00fh
    db 08eh, 049h, 006h, 000h, 000h, 08bh, 04dh, 008h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 08h
    db 08dh, 004h, 0c1h, 089h, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 0ch
    db 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 010h
    db 0c7h, 045h, 00ch
    dd OFFSET ?g_gameAudioChannelScratch@@3PAUGameAudioMixerChannel@@A
    db 0c7h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 00h
    db 040h, 000h, 000h, 000h, 08bh, 045h, 00ch, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04h
    db 055h, 08bh, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 0ch
    db 089h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 014h
    db 08bh, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04h
    db 089h, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 083h, 0f9h, 000h, 00fh, 084h, 0e6h, 005h, 000h, 000h, 08bh, 059h, 01ch
    db 089h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 01ch
    db 083h, 0fbh, 000h, 00fh, 084h, 0d4h, 005h, 000h, 000h, 08bh, 003h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 028h
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 08h
    db 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 08bh, 071h, 028h, 0bdh, 000h, 000h, 000h, 000h, 089h, 02dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 018h
    db 083h, 079h, 038h, 001h, 075h, 016h, 08bh, 053h, 008h, 003h, 053h, 00ch
    db 02bh, 0d6h, 08bh, 041h, 02ch, 033h, 0edh, 02bh, 0e8h, 083h, 0dah, 000h
    db 08bh, 0c5h, 0ebh, 00ch, 08bh, 051h, 028h, 08bh, 041h, 02ch, 083h, 0e8h
    db 000h, 01bh, 053h, 008h, 081h, 0fah, 000h, 000h, 000h, 001h, 073h, 03ah
    db 00fh, 0ach, 0d0h, 008h, 0c1h, 0eah, 008h, 08bh, 069h, 034h, 08bh, 079h
    db 030h, 0c1h, 0e5h, 018h, 0c1h, 0efh, 008h, 081h, 0e7h, 0ffh, 0ffh, 0ffh
    db 000h, 00bh, 0efh, 0f7h, 0f5h, 00bh, 0d2h, 074h, 001h, 040h, 03bh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 077h, 010h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 0bah, 001h, 000h, 000h, 000h, 089h, 015h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 018h
    db 08bh, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 0c7h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 000h, 000h, 000h, 000h, 0c7h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 000h, 000h, 000h, 000h, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 038h
    db 0c7h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 000h, 000h, 000h, 000h, 083h, 079h, 054h, 000h, 074h, 031h, 08bh, 041h
    db 020h, 08bh, 051h, 03ch, 03bh, 0c2h, 075h, 027h, 08bh, 041h, 024h, 08bh
    db 051h, 040h, 03bh, 0c2h, 075h, 01dh, 08bh, 041h, 054h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 08bh, 041h, 04ch, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 08bh, 041h, 050h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 0e9h, 084h, 000h, 000h, 000h, 08bh, 041h, 020h, 08bh, 051h, 044h, 0c1h
    db 0eah, 008h, 089h, 041h, 03ch, 02bh, 0c2h, 083h, 0f8h, 000h, 074h, 02fh
    db 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver255@@3MB
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioInverseMixStep@@3MA
    db 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 089h, 041h, 04ch, 0a1h
    dd OFFSET ?g_gameAudioMixStep@@3IA
    db 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 08bh, 041h, 024h, 08bh, 051h, 048h, 0c1h, 0eah, 008h, 089h, 041h, 040h
    db 02bh, 0c2h, 083h, 0f8h, 000h, 074h, 02fh, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver255@@3MB
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioInverseMixStep@@3MA
    db 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 089h, 041h, 050h, 0a1h
    dd OFFSET ?g_gameAudioMixStep@@3IA
    db 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 083h, 0f8h, 000h, 07eh, 010h, 089h, 041h, 054h, 039h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 076h, 005h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 08bh, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 08bh, 041h, 024h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver255@@3MB
    db 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 030h
    db 08bh, 041h, 020h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver255@@3MB
    db 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 02ch
    db 08bh, 041h, 048h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver256@@3MB
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver255@@3MB
    db 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 040h
    db 08bh, 041h, 044h, 0a3h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver256@@3MB
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioUnitOver255@@3MB
    db 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 03ch
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 08bh, 058h, 030h, 08bh, 048h, 034h, 08bh, 068h, 02ch, 08bh, 070h, 028h
    db 08bh, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 014h
    db 083h, 078h, 038h, 001h, 074h, 00ch, 083h, 0f3h, 0ffh, 083h, 0f1h, 0ffh
    db 083h, 0c3h, 001h, 083h, 0d1h, 000h, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 028h
    db 0d1h, 0e8h, 003h, 0f0h, 08bh, 015h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 083h, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 000h, 00fh, 085h, 033h, 001h, 000h, 000h, 0d1h, 0eah, 00bh, 0d2h, 00fh
    db 084h, 020h, 001h, 000h, 000h, 0d1h, 0edh, 083h, 0c7h, 010h, 0dfh, 044h
    db 036h, 002h, 089h, 02dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dfh, 004h, 036h, 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 003h, 0edh, 003h, 0ebh, 013h, 0f1h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioFixedPointScale@@3MB
    db 0dfh, 044h, 036h, 002h, 0d1h, 0edh, 089h, 02dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dfh, 004h, 036h, 0d9h, 0cdh, 0d8h, 0e4h, 0d1h, 0e5h, 0deh, 0cbh, 0d8h
    db 00dh
    dd OFFSET ?g_gameAudioFixedPointScale@@3MB
    db 0d9h, 0c9h, 0d8h, 0e4h, 003h, 0ebh, 013h, 0f1h, 0deh, 0c9h, 0d9h, 0c9h
    db 0deh, 0c2h, 0d9h, 0c1h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 02ch
    db 0d9h, 0c9h, 0deh, 0c3h, 0d9h, 0c9h, 0ebh, 076h, 08bh, 0ffh, 0d1h, 0edh
    db 089h, 02dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dfh, 044h, 036h, 002h, 0dfh, 004h, 036h, 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 003h, 0edh, 003h, 0ebh, 013h, 0f1h, 083h, 0c7h, 010h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioFixedPointScale@@3MB
    db 0d1h, 0edh, 089h, 02dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dfh, 044h, 036h, 002h, 0d9h, 0cch, 0d8h, 0e3h, 0d1h, 0e5h, 0deh, 0cah
    db 0dfh, 004h, 036h, 0d9h, 0c9h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioFixedPointScale@@3MB
    db 0d9h, 0cch, 0d8h, 0e1h, 003h, 0ebh, 013h, 0f1h, 0deh, 0cch, 0d9h, 0cah
    db 0deh, 0c1h, 0d9h, 0cch, 0d9h, 05fh, 0e4h, 0d9h, 0cch, 0d9h, 05fh, 0e8h
    db 0d9h, 0c2h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 02ch
    db 0d9h, 0c9h, 0deh, 0c4h, 0d9h, 0c9h, 0d9h, 05fh, 0ech, 0d9h, 0c9h, 0d8h
    db 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 030h
    db 0d9h, 0cah, 0d9h, 0c0h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 02ch
    db 0d9h, 0c9h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 030h
    db 0d9h, 0cah, 0d8h, 047h, 0f0h, 0d9h, 0cbh, 0d8h, 047h, 0f4h, 0d9h, 0c9h
    db 0d8h, 047h, 0f8h, 0d9h, 0cbh, 0d9h, 05fh, 0f0h, 0d9h, 0c9h, 0d8h, 047h
    db 0fch, 04ah, 00fh, 085h, 054h, 0ffh, 0ffh, 0ffh, 0d9h, 0c9h, 0d9h, 05fh
    db 0f4h, 0d9h, 0c9h, 0d9h, 05fh, 0f8h, 0d9h, 05fh, 0fch, 08bh, 015h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 083h, 0e2h, 001h, 00bh, 0d2h, 00fh, 084h, 0b3h, 000h, 000h, 000h, 0d9h
    db 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 0d9h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 0d9h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 03ch
    db 0d9h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 040h
    db 0ebh, 00ch, 0ebh, 00ah, 08dh, 0a4h, 024h, 000h, 000h, 000h, 000h, 08dh
    db 049h, 000h, 0d1h, 0edh, 083h, 0c7h, 008h, 0dfh, 044h, 036h, 002h, 089h
    db 02dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0dfh, 004h, 036h, 0dbh, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 034h
    db 0d1h, 0e5h, 003h, 0ebh, 013h, 0f1h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioFixedPointScale@@3MB
    db 0d9h, 0cah, 0d8h, 0e1h, 0deh, 0cah, 0deh, 0c1h, 0d9h, 0c0h, 0d8h, 0cbh
    db 0d9h, 0cbh, 0d8h, 0c5h, 0d9h, 0c9h, 0d8h, 0cah, 0d9h, 0cah, 0d8h, 0c4h
    db 0d9h, 0cbh, 0d8h, 047h, 0f8h, 0d9h, 0cah, 0d8h, 047h, 0fch, 0d9h, 0cah
    db 0d9h, 05fh, 0f8h, 0d9h, 0c9h, 0d9h, 05fh, 0fch, 0d9h, 0c9h, 04ah, 075h
    db 0abh, 0d9h, 0cah, 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 0d9h, 0cah, 0d9h, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioPcmScale255@@3MB
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioPcmScale256@@3MB
    db 0d9h, 0c9h, 0d8h, 00dh
    dd OFFSET ?g_gameAudioPcmScale255@@3MB
    db 0d8h, 00dh
    dd OFFSET ?g_gameAudioPcmScale256@@3MB
    db 033h, 0c0h, 0dbh, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 03ch
    db 0dbh, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 040h
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 028h
    db 0d1h, 0e8h, 02bh, 0f0h, 083h, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 000h, 00fh, 084h, 092h, 000h, 000h, 000h, 08bh, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 01ch
    db 08bh, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 03ch
    db 089h, 041h, 044h, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 040h
    db 089h, 041h, 048h, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 024h
    db 08bh, 015h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 02bh, 0d0h, 0c7h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 048h
    db 000h, 000h, 000h, 000h, 0c7h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 04ch
    db 000h, 000h, 000h, 000h, 089h, 015h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 044h
    db 089h, 051h, 054h, 083h, 0fah, 000h, 075h, 047h, 0c7h, 041h, 04ch, 000h
    db 000h, 000h, 000h, 0c7h, 041h, 050h, 000h, 000h, 000h, 000h, 08bh, 051h
    db 020h, 0c1h, 0e2h, 008h, 089h, 051h, 044h, 08bh, 051h, 024h, 0c1h, 0e2h
    db 008h, 089h, 051h, 048h, 039h, 005h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 038h
    db 074h, 01fh, 089h, 071h, 028h, 089h, 069h, 02ch, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 010h
    db 02bh, 0c7h, 0c1h, 0e8h, 003h, 089h, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 014h
    db 083h, 0f8h, 000h, 00fh, 085h, 02bh, 0fbh, 0ffh, 0ffh, 083h, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 018h
    db 000h, 00fh, 084h, 0dah, 000h, 000h, 000h, 08bh, 01dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 01ch
    db 08bh, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 08ah, 053h, 01dh, 0f6h, 0c2h, 002h, 074h, 031h, 08bh, 043h, 008h, 003h
    db 043h, 00ch, 02bh, 073h, 00ch, 03bh, 0f0h, 073h, 0f9h, 089h, 071h, 028h
    db 089h, 069h, 02ch, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 010h
    db 02bh, 0c7h, 0c1h, 0e8h, 003h, 089h, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 014h
    db 083h, 0f8h, 000h, 00fh, 084h, 09ah, 000h, 000h, 000h, 0e9h, 0d9h, 0fah
    db 0ffh, 0ffh, 0f6h, 0c2h, 004h, 00fh, 084h, 085h, 000h, 000h, 000h, 083h
    db 079h, 038h, 001h, 074h, 030h, 08bh, 043h, 008h, 048h, 0bah, 0ffh, 0ffh
    db 0ffh, 0ffh, 02bh, 0d5h, 01bh, 0c6h, 08bh, 0f0h, 08bh, 0eah, 08bh, 043h
    db 008h, 0bah, 000h, 000h, 000h, 000h, 003h, 0eah, 013h, 0f0h, 0c7h, 041h
    db 038h, 001h, 000h, 000h, 000h, 08bh, 043h, 008h, 003h, 043h, 00ch, 03bh
    db 0f0h, 07dh, 002h, 0ebh, 02fh, 08bh, 043h, 008h, 003h, 043h, 00ch, 0bah
    db 000h, 000h, 000h, 000h, 02bh, 0d5h, 01bh, 0c6h, 08bh, 0f0h, 08bh, 0eah
    db 08bh, 043h, 008h, 003h, 043h, 00ch, 048h, 0bah, 0ffh, 0ffh, 0ffh, 0ffh
    db 003h, 0eah, 013h, 0f0h, 0c7h, 041h, 038h, 002h, 000h, 000h, 000h, 03bh
    db 073h, 008h, 07ch, 0a1h, 089h, 071h, 028h, 089h, 069h, 02ch, 0a1h
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 010h
    db 02bh, 0c7h, 0c1h, 0e8h, 003h, 089h, 03dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 014h
    db 083h, 0f8h, 000h, 074h, 00ch, 0e9h, 04bh, 0fah, 0ffh, 0ffh, 033h, 0edh
    db 033h, 0f6h, 089h, 071h, 01ch, 08bh, 00dh
    dd OFFSET ?g_gameAudioMixerWorkspace@@3PAEA + 020h
    db 089h, 069h, 02ch, 089h, 071h, 028h, 05dh, 083h, 045h, 00ch, 058h, 081h
    db 07dh, 00ch
    dd OFFSET ?g_gameAudioChannelScratchEnd@@3EA
    db 00fh, 08ch, 0deh, 0f9h, 0ffh, 0ffh, 05fh, 05eh, 05bh, 05dh, 0c3h
?MixGameAudioChannels@@YAXPAXHH@Z ENDP

END
