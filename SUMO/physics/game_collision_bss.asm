.686
.model flat
option casemap:none

.data?
ALIGN 4

PUBLIC ?g_gameCollisionCorrections@@3PAUGameCollisionCorrectionRecord@@A
?g_gameCollisionCorrections@@3PAUGameCollisionCorrectionRecord@@A LABEL BYTE
    BYTE 010000h DUP (?)

PUBLIC ?g_gameContactObjects@@3PAEA
?g_gameContactObjects@@3PAEA LABEL BYTE
    BYTE 0f400h DUP (?)

PUBLIC ?g_cutPlaneBox@@3UGameBox@@A
?g_cutPlaneBox@@3UGameBox@@A LABEL BYTE
    BYTE 0fch DUP (?)
    BYTE 4 DUP (?)

PUBLIC ?g_clipScratchBox@@3UGameBox@@A
?g_clipScratchBox@@3UGameBox@@A LABEL BYTE
    BYTE 0fch DUP (?)
    BYTE 4 DUP (?)

PUBLIC ?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A
?g_gameCollisionPoints@@3PAUGameCollisionPointRecord@@A LABEL BYTE
    BYTE 030000h DUP (?)

PUBLIC ?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A
?g_gameCollisionFeatureLinksEnd@@3PAUGameCollisionFeatureLink@@A LABEL DWORD
    DWORD ?

PUBLIC ?g_gameContactObjectsEnd@@3PAEA
?g_gameContactObjectsEnd@@3PAEA LABEL DWORD
    DWORD ?

PUBLIC ?g_gameBoxesEnd@@3PAUGameBox@@A
?g_gameBoxesEnd@@3PAUGameBox@@A LABEL DWORD
    DWORD ?

PUBLIC ?g_gameContactLinksEnd@@3PAEA
?g_gameContactLinksEnd@@3PAEA LABEL DWORD
    DWORD ?

PUBLIC ?g_gameContactLinks@@3PAEA
?g_gameContactLinks@@3PAEA LABEL BYTE
    BYTE 01800h DUP (?)

PUBLIC ?g_gameMenuSelection@@3HA
?g_gameMenuSelection@@3HA LABEL DWORD
    DWORD ?

PUBLIC ?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A
?g_gameCollisionCorrectionsEnd@@3PAUGameCollisionCorrectionRecord@@A LABEL DWORD
    DWORD ?

PUBLIC ?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A
?g_gameCollisionPointsEnd@@3PAUGameCollisionPointRecord@@A LABEL DWORD
    DWORD ?
    DWORD ?

PUBLIC ?g_gameCollisionGroupSentinel@@3EA
?g_gameCollisionGroupSentinel@@3EA LABEL BYTE
    BYTE ?

END
