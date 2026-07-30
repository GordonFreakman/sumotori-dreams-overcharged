.686
.model flat
option casemap:none

EXTERN _log:PROC
EXTERN _exp:PROC
EXTERN __ftol2:PROC
EXTERN ?CreateGameTextureFromPixels@@YAHPAXHHH@Z:PROC

EXTERN ?g_textureByteMaximumFloat@@3MB:DWORD
EXTERN ?g_gameRampBias@@3MB:DWORD
EXTERN ?g_gameRampStep32@@3MB:DWORD
EXTERN ?g_gameRampStep64@@3MB:DWORD
EXTERN ?g_gameRampDecayTwoPercent@@3NB:QWORD
EXTERN ?g_gameRampDecayFivePercent@@3NB:QWORD
EXTERN ?g_gameRampDecayOnePercent@@3NB:QWORD
EXTERN ?g_gameTextureScratch@@3PAIA:DWORD
EXTERN ?g_gameRampTexture@@3HA:DWORD
EXTERN ?g_gameAttenuationTexture@@3HA:DWORD

.code

PUBLIC ?CreateGameRampTexture@@YAHXZ
?CreateGameRampTexture@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 18h
    fld dword ptr [?g_textureByteMaximumFloat@@3MB]
    push ebx
    push esi
    fst dword ptr [ebp - 8]
    push edi
    fst dword ptr [ebp - 0ch]
    fstp dword ptr [ebp - 10h]
    push ecx
    fld qword ptr [?g_gameRampDecayTwoPercent@@3NB]
    push ecx
    mov esi, OFFSET ?g_gameTextureScratch@@3PAIA
    fstp qword ptr [esp]
    mov edi, esi
    call _log
    fmul dword ptr [?g_gameRampStep32@@3MB]
    fstp qword ptr [esp]
    call _exp
    fstp dword ptr [ebp - 14h]
    fld qword ptr [?g_gameRampDecayTwoPercent@@3NB]
    fstp qword ptr [esp]
    call _log
    fmul dword ptr [?g_gameRampStep32@@3MB]
    fstp qword ptr [esp]
    call _exp
    fstp dword ptr [ebp - 18h]
    fld qword ptr [?g_gameRampDecayTwoPercent@@3NB]
    fstp qword ptr [esp]
    call _log
    fmul dword ptr [?g_gameRampStep32@@3MB]
    fstp qword ptr [esp]
    call _exp
    fld dword ptr [?g_gameRampBias@@3MB]
    pop ecx
    fld dword ptr [ebp - 8]
    pop ecx
    fld dword ptr [ebp - 0ch]
    fld dword ptr [ebp - 10h]
    mov dword ptr [ebp - 4], 20h
rampPixel:
    fld st(2)
    fsub st, st(4)
    call __ftol2
    fld st(1)
    mov ebx, eax
    fsub st, st(4)
    shl ebx, 8
    call __ftol2
    fld st(0)
    add ebx, eax
    fsub st, st(4)
    shl ebx, 8
    call __ftol2
    fld dword ptr [ebp - 14h]
    fmulp st(3), st
    add ebx, eax
    fld dword ptr [ebp - 18h]
    mov dword ptr [edi], ebx
    fmulp st(2), st
    add edi, 4
    dec dword ptr [ebp - 4]
    fld st(4)
    fmulp st(1), st
    jne rampPixel
    fstp st(0)
    push 1
    fstp st(0)
    push 1
    fstp st(0)
    push 20h
    fstp st(0)
    push esi
    fstp st(0)
    call ?CreateGameTextureFromPixels@@YAHPAXHHH@Z
    add esp, 10h
    pop edi
    pop esi
    mov dword ptr [?g_gameRampTexture@@3HA], eax
    pop ebx
    leave
    ret
?CreateGameRampTexture@@YAHXZ ENDP

PUBLIC ?CreateGameAttenuationTexture@@YAHXZ
?CreateGameAttenuationTexture@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 1ch
    and dword ptr [ebp - 4], 0
    push ebx
    push esi
    mov esi, OFFSET ?g_gameTextureScratch@@3PAIA
    push edi
    mov edi, esi
attenuationRow:
    fld dword ptr [?g_textureByteMaximumFloat@@3MB]
    push ecx
    fst dword ptr [ebp - 14h]
    push ecx
    fst dword ptr [ebp - 18h]
    fstp dword ptr [ebp - 1ch]
    fld qword ptr [?g_gameRampDecayOnePercent@@3NB]
    fstp qword ptr [esp]
    call _log
    fmul dword ptr [?g_gameRampStep64@@3MB]
    fstp qword ptr [esp]
    call _exp
    fstp dword ptr [ebp - 8]
    fld qword ptr [?g_gameRampDecayTwoPercent@@3NB]
    fstp qword ptr [esp]
    call _log
    fmul dword ptr [?g_gameRampStep64@@3MB]
    fstp qword ptr [esp]
    call _exp
    fstp dword ptr [ebp - 0ch]
    fld qword ptr [?g_gameRampDecayFivePercent@@3NB]
    fstp qword ptr [esp]
    call _log
    fmul dword ptr [?g_gameRampStep64@@3MB]
    fstp qword ptr [esp]
    call _exp
    cmp dword ptr [ebp - 4], 8
    pop ecx
    pop ecx
    jle attenuationRatesReady
    fstp dword ptr [ebp - 10h]
    mov eax, dword ptr [ebp - 10h]
    fld dword ptr [ebp - 8]
    mov dword ptr [ebp - 0ch], eax
attenuationRatesReady:
    fld dword ptr [ebp - 14h]
    mov dword ptr [ebp - 10h], 40h
    fld dword ptr [ebp - 18h]
    fld dword ptr [ebp - 1ch]
attenuationPixel:
    fld st(2)
    call __ftol2
    fld st(1)
    mov ebx, eax
    shl ebx, 8
    call __ftol2
    fld st(0)
    add ebx, eax
    shl ebx, 8
    call __ftol2
    fld dword ptr [ebp - 8]
    fmulp st(3), st
    add ebx, eax
    fld dword ptr [ebp - 0ch]
    mov dword ptr [edi], ebx
    fmulp st(2), st
    add edi, 4
    dec dword ptr [ebp - 10h]
    fld st(3)
    fmulp st(1), st
    jne attenuationPixel
    inc dword ptr [ebp - 4]
    fstp st(0)
    cmp dword ptr [ebp - 4], 10h
    fstp st(0)
    fstp st(0)
    fstp st(0)
    jl attenuationRow
    push 0
    push 10h
    push 40h
    push esi
    call ?CreateGameTextureFromPixels@@YAHPAXHHH@Z
    add esp, 10h
    pop edi
    pop esi
    mov dword ptr [?g_gameAttenuationTexture@@3HA], eax
    pop ebx
    leave
    ret
?CreateGameAttenuationTexture@@YAHXZ ENDP

END
