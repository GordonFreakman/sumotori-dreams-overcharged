.686
.model flat
option casemap:none

.data?
ALIGN 4

PUBLIC ?g_gameAudioChannelScratch@@3PAUGameAudioMixerChannel@@A
?g_gameAudioChannelScratch@@3PAUGameAudioMixerChannel@@A LABEL BYTE
    BYTE 01600h DUP (?)

PUBLIC ?g_gameAudioChannelScratchEnd@@3EA
?g_gameAudioChannelScratchEnd@@3EA LABEL BYTE
    BYTE 04200h DUP (?)
    BYTE 020h DUP (?)

PUBLIC ?g_gameAudioChannelStates@@3PAEA
?g_gameAudioChannelStates@@3PAEA LABEL BYTE
    BYTE 01600h DUP (?)

END
