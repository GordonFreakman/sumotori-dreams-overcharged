.686
.model flat
option casemap:none

.data?
ALIGN 4

PUBLIC ?g_gameMen@@3PAUGameMan@@A
?g_gameMen@@3PAUGameMan@@A LABEL BYTE
    BYTE 01cc0h DUP (?)

PUBLIC ?g_gameMenEnd@@3EA
?g_gameMenEnd@@3EA LABEL BYTE
    BYTE ?

END
