.686
.model flat
option casemap:none

EXTERN ?CreateGameAttenuationTexture@@YAHXZ:PROC
EXTERN ?CreateGameRampTexture@@YAHXZ:PROC
EXTERN ?IgnoreGameTextureProgress@@YGXM@Z:PROC
EXTERN ?BuildTextureSet@@YAPAPAXPAPAXPAX@Z:PROC
EXTERN ?BlendTextIntoTexture@@YAHPAEPBDHHHHHHHH1@Z:PROC
EXTERN ?CreateGameNormalMapTexture@@YAHPAEHHH@Z:PROC
EXTERN ?CreateGameTextureFromPixels@@YAHPAXHHH@Z:PROC

EXTERN ?g_textureLoadFromTga@@3EA:BYTE
EXTERN ?g_textureUseMmxSampler@@3EA:BYTE
EXTERN ?g_gameTexturePrograms@@3PAPAEA:DWORD
EXTERN ?g_gameTextures@@3PAHA:DWORD
EXTERN ?g_gameMenuLabels@@3PAY15BI@DA:BYTE
EXTERN ?g_gameTimesFont@@3PADA:BYTE
EXTERN ?g_gameConsoleFont@@3PADA:BYTE
EXTERN ?g_gameTextureScratch@@3PAIA:DWORD
EXTERN ?g_gameTextureScratchEnd@@3IA:DWORD
EXTERN ?g_gameFontAtlasTexture@@3HA:DWORD

.code

PUBLIC ?InitializeGameTextures@@YAHXZ
?InitializeGameTextures@@YAHXZ PROC
    sub esp, 0ch
    push ebx
    push ebp
    push esi
    push edi
    call ?CreateGameAttenuationTexture@@YAHXZ
    call ?CreateGameRampTexture@@YAHXZ
    push OFFSET ?IgnoreGameTextureProgress@@YGXM@Z
    push OFFSET ?g_gameTexturePrograms@@3PAPAEA
    mov byte ptr [?g_textureLoadFromTga@@3EA], 1
    mov byte ptr [?g_textureUseMmxSampler@@3EA], 1
    call ?BuildTextureSet@@YAPAPAXPAPAXPAX@Z
    xor ebx, ebx
    cmp dword ptr [?g_gameTexturePrograms@@3PAPAEA], ebx
    pop ecx
    pop ecx
    mov ebp, 100h
    je texturePairsComplete
    mov dword ptr [esp + 10h], eax
    sub dword ptr [esp + 10h], OFFSET ?g_gameTextures@@3PAHA
texturePair:
    mov eax, dword ptr [esp + 10h]
    mov eax, dword ptr [eax + ebx * 4 + ?g_gameTextures@@3PAHA]
    mov dword ptr [esp + 18h], eax
    mov eax, ebx
    cdq
    sub eax, edx
    sar eax, 1
    sub eax, 4
    cmp ebx, 8
    jl texturePairUpload
    cmp ebx, 12h
    jge texturePairUpload
    lea ecx, [eax + eax * 8]
    shl ecx, 4
    lea ecx, [ecx + ?g_gameMenuLabels@@3PAY15BI@DA]
    cmp byte ptr [ecx], 0
    je texturePairUpload
    mov edi, ebx
    and edi, 1
    lea esi, [eax + eax * 8]
    imul edi, edi, 7f7f7fh
    shl esi, 4
    mov dword ptr [esp + 14h], 6
    add esi, OFFSET ?g_gameMenuLabels@@3PAY15BI@DA
textureMenuLabel:
    push OFFSET ?g_gameTimesFont@@3PADA
    push 0ffffffh
    push edi
    push 18h
    push 20h
    push 0f6h
    push ebp
    push dword ptr [esp + 30h]
    push 0ah
    push ecx
    push dword ptr [esp + 40h]
    call ?BlendTextIntoTexture@@YAHPAEPBDHHHHHHHH1@Z
    add dword ptr [esp + 40h], 2ah
    add esi, 18h
    add esp, 2ch
    cmp byte ptr [esi], 0
    mov ecx, esi
    jne textureMenuLabel
texturePairUpload:
    test bl, 1
    jne textureColorUpload
    push -64h
    push ebp
    push ebp
    push dword ptr [esp + 24h]
    call ?CreateGameNormalMapTexture@@YAHPAEHHH@Z
    jmp texturePairStored
textureColorUpload:
    push 0
    push ebp
    push ebp
    push dword ptr [esp + 24h]
    call ?CreateGameTextureFromPixels@@YAHPAXHHH@Z
texturePairStored:
    add esp, 10h
    mov dword ptr [?g_gameTextures@@3PAHA + ebx * 4], eax
    inc ebx
    cmp dword ptr [?g_gameTexturePrograms@@3PAPAEA + ebx * 4], 0
    jne texturePair
texturePairsComplete:
    mov esi, OFFSET ?g_gameTextureScratch@@3PAIA
    or eax, -1
    mov ecx, 10000h
    mov edi, esi
    rep stosd
    xor ebx, ebx
fontGlyph:
    push OFFSET ?g_gameConsoleFont@@3PADA
    push 0ffffffh
    push 0
    push 0ch
    push 10h
    push 10h
    push ebp
    push 10h
    pop ecx
    mov eax, ebx
    cdq
    idiv ecx
    mov byte ptr [esp + 2ch], bl
    mov byte ptr [esp + 2dh], 0
    shl eax, 4
    push eax
    mov eax, ebx
    and eax, 0fh
    shl eax, 4
    push eax
    lea eax, [esp + 34h]
    push eax
    push esi
    call ?BlendTextIntoTexture@@YAHPAEPBDHHHHHHHH1@Z
    add esp, 2ch
    inc ebx
    cmp ebx, ebp
    jl fontGlyph
    mov eax, esi
invertFontAtlas:
    not dword ptr [eax]
    add eax, 4
    cmp eax, OFFSET ?g_gameTextureScratchEnd@@3IA
    jl invertFontAtlas
    push 0
    push ebp
    push ebp
    push esi
    call ?CreateGameTextureFromPixels@@YAHPAXHHH@Z
    add esp, 10h
    pop edi
    pop esi
    pop ebp
    mov dword ptr [?g_gameFontAtlasTexture@@3HA], eax
    pop ebx
    add esp, 0ch
    ret
?InitializeGameTextures@@YAHXZ ENDP

END
