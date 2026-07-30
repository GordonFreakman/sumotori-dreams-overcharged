.686
.model flat
option casemap:none

.data?
ALIGN 4

PUBLIC ?g_gameCollisionFeatureLinks@@3PAUGameCollisionFeatureLink@@A
?g_gameCollisionFeatureLinks@@3PAUGameCollisionFeatureLink@@A LABEL BYTE
    BYTE 0198000h DUP (?)
    BYTE 8 DUP (?)

PUBLIC ?g_gameBoxes@@3PAUGameBox@@A
?g_gameBoxes@@3PAUGameBox@@A LABEL BYTE
    BYTE 01f800h DUP (?)
    BYTE 8 DUP (?)

PUBLIC ?g_gameRandom@@3UGameRandomGenerator@@A
?g_gameRandom@@3UGameRandomGenerator@@A LABEL BYTE
    BYTE 019ch DUP (?)

END
