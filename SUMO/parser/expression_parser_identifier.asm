.686
.model flat
option casemap:none

EXTERN ?IsIdentifierStart@ExpressionParser@@QAEHD@Z:PROC
EXTERN ?IsIdentifierContinue@ExpressionParser@@QAEHD@Z:PROC
EXTERN ?g_parserIdentifierTooLong@@3QBDB:BYTE

.code

PUBLIC ?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z
?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z PROC
    db 055h, 08bh, 0ech, 051h, 053h, 056h, 08bh, 075h, 00ch, 085h, 0f6h, 057h
    db 08bh, 0f9h, 089h, 07dh, 0fch, 075h, 044h, 08bh, 075h, 008h, 033h, 0c0h
    db 08ah, 006h, 050h
    call ?IsIdentifierStart@ExpressionParser@@QAEHD@Z
    db 085h, 0c0h, 074h, 02fh, 06ah, 00eh, 046h, 05bh, 0ebh, 006h, 085h, 0dbh
    db 074h, 014h, 046h, 04bh, 033h, 0c0h, 08ah, 006h, 08bh, 0cfh, 050h
    call ?IsIdentifierContinue@ExpressionParser@@QAEHD@Z
    db 085h, 0c0h, 075h, 0eah, 0ebh, 011h, 080h, 07fh, 00ch, 000h, 075h, 00bh
    db 0c6h, 047h, 00ch, 001h, 0c7h, 047h, 008h
    dd OFFSET ?g_parserIdentifierTooLong@@3QBDB
    db 08bh, 0c6h, 0ebh, 044h, 08bh, 07dh, 008h, 08bh, 04dh, 0fch, 033h, 0dbh
    db 08ah, 01fh, 053h
    call ?IsIdentifierStart@ExpressionParser@@QAEHD@Z
    db 085h, 0c0h, 074h, 02bh, 088h, 01eh, 046h, 047h, 0c7h, 045h, 008h, 00eh
    db 000h, 000h, 000h, 0ebh, 00dh, 083h, 07dh, 008h, 000h, 074h, 024h, 088h
    db 01eh, 046h, 047h, 0ffh, 04dh, 008h, 08bh, 04dh, 0fch, 033h, 0dbh, 08ah
    db 01fh, 053h
    call ?IsIdentifierContinue@ExpressionParser@@QAEHD@Z
    db 085h, 0c0h, 075h, 0e2h, 0c6h, 006h, 000h, 08bh, 0c7h, 05fh, 05eh, 05bh
    db 0c9h, 0c2h, 008h, 000h, 08bh, 045h, 0fch, 0c6h, 006h, 000h, 080h, 078h
    db 00ch, 000h, 075h, 0ebh, 0c6h, 040h, 00ch, 001h, 0c7h, 040h, 008h
    dd OFFSET ?g_parserIdentifierTooLong@@3QBDB
    db 0ebh, 0deh
?ReadIdentifier@ExpressionParser@@QAEPADPAD0@Z ENDP

END
