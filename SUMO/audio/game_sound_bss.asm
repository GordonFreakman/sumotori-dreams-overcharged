.686
.model flat
option casemap:none

.data?
ALIGN 4

PUBLIC ?g_gameSoundSlotFrequency0@@3HA
?g_gameSoundSlotFrequency0@@3HA LABEL DWORD
    DWORD ?

PUBLIC ?g_gameSoundSlots@@3PAEA
?g_gameSoundSlots@@3PAEA LABEL BYTE
    BYTE 03cfch DUP (?)

PUBLIC ?g_deferredReleaseIndex@@3IA
?g_deferredReleaseIndex@@3IA LABEL DWORD
    DWORD ?

PUBLIC ?g_gamePrimarySoundBuffer@@3PAUIDirectSoundBuffer@@A
?g_gamePrimarySoundBuffer@@3PAUIDirectSoundBuffer@@A LABEL DWORD
    DWORD ?

PUBLIC ?g_deferredReleaseSlots@@3PAPAPAUIDirect3DResource9@@A
?g_deferredReleaseSlots@@3PAPAPAUIDirect3DResource9@@A LABEL DWORD
    DWORD 0400h DUP (?)

PUBLIC ?g_deferredReleaseWriteIndex@@3HA
?g_deferredReleaseWriteIndex@@3HA LABEL DWORD
    DWORD ?

PUBLIC ?g_gameDirectSound@@3PAUIDirectSound8@@A
?g_gameDirectSound@@3PAUIDirectSound8@@A LABEL DWORD
    DWORD ?

PUBLIC ?g_gameActiveSoundSlots@@3PAPAPAUIDirectSoundBuffer@@A
?g_gameActiveSoundSlots@@3PAPAPAUIDirectSoundBuffer@@A LABEL DWORD
    DWORD 9 DUP (?)

PUBLIC ?g_gameSoundInitialized@@3HA
?g_gameSoundInitialized@@3HA LABEL DWORD
    DWORD ?

END
