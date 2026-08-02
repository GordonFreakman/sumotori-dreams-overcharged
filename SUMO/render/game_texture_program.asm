.686
.model flat
option casemap:none

EXTERN ?InitializeTextureGenerator@@YAPAXXZ:PROC
EXTERN ?ExportTextureTga@@YACPAI@Z:PROC
EXTERN ?ImportTextureTga@@YAHPBDPAI@Z:PROC
EXTERN ?ClearTextureWorkBuffer@@YAHPAX@Z:PROC
EXTERN ?GenerateTextureFractalPlasma@@YAXHDHHHH@Z:PROC
EXTERN ?GenerateTexturePlasma@@YAXHDHHHH@Z:PROC
EXTERN ?GenerateTextureCells@@YAXHDHHHHHH@Z:PROC
EXTERN ?GenerateTextureRadialGradient@@YAXHHDH@Z:PROC
EXTERN ?GenerateTextureCubicNoise@@YAXHDHHHHH@Z:PROC
EXTERN ?DistortTextureSine@@YAHHHHHHHH@Z:PROC
EXTERN ?TranslateTextureLayerWrapped@@YAXHDD@Z:PROC
EXTERN ?DistortTextureTwirl@@YAHHH@Z:PROC
EXTERN ?SubtractShiftedTextureLayer@@YAXHF@Z:PROC
EXTERN ?BlurTextureLayer@@YAHHH@Z:PROC
EXTERN ?DistortTextureByLayers@@YAHHHDHHDH@Z:PROC
EXTERN ?DirectionalBlurTextureLayer@@YAXHHDH@Z:PROC
EXTERN ?SwapTextureChannels@@YAXHDHD@Z:PROC
EXTERN ?ReplicateTextureChannel@@YAHHD@Z:PROC
EXTERN ?CopyTextureChannel@@YAXHDHD@Z:PROC
EXTERN ?MixTextureLayers@@YAXHHH@Z:PROC
EXTERN ?MultiplyTextureLayers@@YAXHH@Z:PROC
EXTERN ?AddTextureLayersSaturated@@YAXHH@Z:PROC
EXTERN ?MaxTextureLayers@@YAXHH@Z:PROC
EXTERN ?AdjustTextureContrast@@YAXHH@Z:PROC
EXTERN ?InvertTextureLayerLowBytes@@YAXH@Z:PROC
EXTERN ?ShadeTextureLayerByChannel@@YAXHHD@Z:PROC
EXTERN ?ApplyTextureColorMap@@YAXHH@Z:PROC
EXTERN ?ApplyTextureCosineWave@@YAXHDH@Z:PROC
EXTERN ?RemapTextureChannelRange@@YAXHDHH@Z:PROC
EXTERN ?AdjustTextureHsv@@YAXHHH@Z:PROC
EXTERN ?ApplyTextureGradient@@YAXHCHHHHHH@Z:PROC
EXTERN ?BlendTextureLayersByMask@@YAXHHHC@Z:PROC
EXTERN ?EmbossTextureLayer@@YAXH@Z:PROC
EXTERN ?ExpandTextureBitmap@@YAPAIHPAEII@Z:PROC
EXTERN ?g_textureWorkBuffer@@3PAIA:DWORD
EXTERN ?g_textureLoadFromTga@@3EA:BYTE
EXTERN ?g_textureProgramCompletedWork@@3HA:DWORD
EXTERN ?g_textureProgramTotalWork@@3HA:DWORD
EXTERN ?g_textureProgressCallback@@3P6GXM@ZA:DWORD
EXTERN ?g_textureByteBuffer@@3PAEA:DWORD
EXTERN ?g_textureChannelSwapBuffer@@3PAIA:DWORD
EXTERN ?g_textureLayers@@3PAPAEA:DWORD
EXTERN ?g_textureCommandCursor@@3PAEA:DWORD
EXTERN ?g_textureExportFilename@@3PADA:BYTE

.code

; FUNCTION: SUMO 0x00419a30
; FUNCTION: EDITOR 0x00419a50
PUBLIC ?ExecuteTextureProgram@@YAXPAXPAI@Z
?ExecuteTextureProgram@@YAXPAXPAI@Z PROC
loc_419a30:
    push	ebx
loc_419a31:
    push	edi
loc_419a32:
    mov	edi, dword ptr [esp + 0ch]
loc_419a36:
    test	edi, edi
loc_419a38:
    je loc_41a0c0
loc_419a3e:
    mov	ebx, dword ptr [esp + 10h]
loc_419a42:
    test	ebx, ebx
loc_419a44:
    je loc_41a0c0
loc_419a4a:
    mov	eax, dword ptr [?g_textureWorkBuffer@@3PAIA]
loc_419a4f:
    test	eax, eax
loc_419a51:
    jne loc_419a58
loc_419a53:
    call ?InitializeTextureGenerator@@YAPAXXZ
loc_419a58:
    mov	al, byte ptr [?g_textureLoadFromTga@@3EA]
loc_419a5d:
    test	al, al
loc_419a5f:
    je loc_419a9f
loc_419a61:
    push	ebx
loc_419a62:
    push OFFSET ?g_textureExportFilename@@3PADA
loc_419a67:
    call ?ImportTextureTga@@YAHPBDPAI@Z
loc_419a6c:
    add	esp, 8h
loc_419a6f:
    test	eax, eax
loc_419a71:
    je loc_419a9f
loc_419a73:
    mov	ecx, dword ptr [?g_textureProgramCompletedWork@@3HA]
loc_419a79:
    xor	eax, eax
loc_419a7b:
    mov	al, byte ptr [edi + 3h]
loc_419a7e:
    add	ecx, eax
loc_419a80:
    mov	dword ptr [?g_textureProgramCompletedWork@@3HA], ecx
loc_419a86:
    push	ecx
loc_419a87:
    fild	dword ptr [?g_textureProgramCompletedWork@@3HA]
loc_419a8d:
    fidiv	dword ptr [?g_textureProgramTotalWork@@3HA]
loc_419a93:
    fstp	dword ptr [esp]
loc_419a96:
    call	dword ptr [?g_textureProgressCallback@@3P6GXM@ZA]
loc_419a9c:
    pop	edi
loc_419a9d:
    pop	ebx
loc_419a9e:
    ret
loc_419a9f:
    mov	edx, dword ptr [?g_textureByteBuffer@@3PAEA]
loc_419aa5:
    mov	ecx, dword ptr [edi]
loc_419aa7:
    mov	dword ptr [edx], ecx
loc_419aa9:
    mov	eax, dword ptr [?g_textureWorkBuffer@@3PAIA]
loc_419aae:
    push	eax
loc_419aaf:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419ab4:
    mov	ecx, dword ptr [?g_textureChannelSwapBuffer@@3PAIA]
loc_419aba:
    push	ecx
loc_419abb:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419ac0:
    mov	edx, dword ptr [?g_textureLayers@@3PAPAEA]
loc_419ac6:
    push	edx
loc_419ac7:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419acc:
    mov	eax, dword ptr [?g_textureLayers@@3PAPAEA + 4]
loc_419ad1:
    push	eax
loc_419ad2:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419ad7:
    mov	ecx, dword ptr [?g_textureLayers@@3PAPAEA + 8]
loc_419add:
    push	ecx
loc_419ade:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419ae3:
    mov	edx, dword ptr [?g_textureLayers@@3PAPAEA + 0ch]
loc_419ae9:
    push	edx
loc_419aea:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419aef:
    mov	eax, dword ptr [?g_textureByteBuffer@@3PAEA]
loc_419af4:
    add	esp, 18h
loc_419af7:
    mov	eax, dword ptr [eax]
loc_419af9:
    mov	ecx, eax
loc_419afb:
    and	ecx, 0ffffffh
loc_419b01:
    cmp	ecx, 475441h
loc_419b07:
    jne loc_41a0c0
loc_419b0d:
    sar	eax, 18h
loc_419b10:
    push	esi
loc_419b11:
    mov	esi, 4h
loc_419b16:
    test	eax, eax
loc_419b18:
    jle loc_41a099
loc_419b1e:
    push	ebp
loc_419b1f:
    xor	ebp, ebp
loc_419b21:
    mov	dword ptr [esp + 14h], eax
loc_419b25:
    db 08dh, 004h, 02eh
loc_419b28:
    xor	edx, edx
loc_419b2a:
    add	eax, edi
loc_419b2c:
    mov	dword ptr [?g_textureCommandCursor@@3PAEA], eax
loc_419b31:
    mov	dl, byte ptr [eax]
loc_419b33:
    inc	eax
loc_419b34:
    mov	dword ptr [?g_textureCommandCursor@@3PAEA], eax
loc_419b39:
    mov	cl, byte ptr [eax]
loc_419b3b:
    cmp	cl, 3h
loc_419b3e:
    ja loc_41a05f
loc_419b44:
    cmp	edx, 1h
loc_419b47:
    jne loc_419b7b
loc_419b49:
    xor	edx, edx
loc_419b4b:
    and	ecx, 0ffh
loc_419b51:
    mov	dl, byte ptr [eax + 6h]
loc_419b54:
    push	edx
loc_419b55:
    xor	edx, edx
loc_419b57:
    mov	dl, byte ptr [eax + 5h]
loc_419b5a:
    push	edx
loc_419b5b:
    xor	edx, edx
loc_419b5d:
    mov	dl, byte ptr [eax + 4h]
loc_419b60:
    push	edx
loc_419b61:
    xor	edx, edx
loc_419b63:
    mov	dl, byte ptr [eax + 3h]
loc_419b66:
    push	edx
loc_419b67:
    xor	edx, edx
loc_419b69:
    mov	dl, byte ptr [eax + 1h]
loc_419b6c:
    push	edx
loc_419b6d:
    push	ecx
loc_419b6e:
    call ?GenerateTextureFractalPlasma@@YAXHDHHHH@Z
loc_419b73:
    add	esp, 18h
loc_419b76:
    jmp loc_41a05f
loc_419b7b:
    cmp	edx, 2h
loc_419b7e:
    jne loc_419bb2
loc_419b80:
    xor	edx, edx
loc_419b82:
    and	ecx, 0ffh
loc_419b88:
    mov	dl, byte ptr [eax + 4h]
loc_419b8b:
    push	edx
loc_419b8c:
    xor	edx, edx
loc_419b8e:
    mov	dl, byte ptr [eax + 3h]
loc_419b91:
    push	edx
loc_419b92:
    xor	edx, edx
loc_419b94:
    mov	dl, byte ptr [eax + 2h]
loc_419b97:
    push	edx
loc_419b98:
    xor	edx, edx
loc_419b9a:
    mov	dl, byte ptr [eax + 1h]
loc_419b9d:
    push	edx
loc_419b9e:
    xor	edx, edx
loc_419ba0:
    mov	dl, byte ptr [eax + 7h]
loc_419ba3:
    push	edx
loc_419ba4:
    push	ecx
loc_419ba5:
    call ?GenerateTexturePlasma@@YAXHDHHHH@Z
loc_419baa:
    add	esp, 18h
loc_419bad:
    jmp loc_41a05f
loc_419bb2:
    cmp	edx, 3h
loc_419bb5:
    jne loc_419bf5
loc_419bb7:
    xor	edx, edx
loc_419bb9:
    and	ecx, 0ffh
loc_419bbf:
    mov	dl, byte ptr [eax + 7h]
loc_419bc2:
    push	edx
loc_419bc3:
    xor	edx, edx
loc_419bc5:
    mov	dl, byte ptr [eax + 6h]
loc_419bc8:
    push	edx
loc_419bc9:
    xor	edx, edx
loc_419bcb:
    mov	dl, byte ptr [eax + 5h]
loc_419bce:
    push	edx
loc_419bcf:
    xor	edx, edx
loc_419bd1:
    mov	dl, byte ptr [eax + 4h]
loc_419bd4:
    push	edx
loc_419bd5:
    xor	edx, edx
loc_419bd7:
    mov	dl, byte ptr [eax + 3h]
loc_419bda:
    push	edx
loc_419bdb:
    xor	edx, edx
loc_419bdd:
    mov	dl, byte ptr [eax + 2h]
loc_419be0:
    push	edx
loc_419be1:
    xor	edx, edx
loc_419be3:
    mov	dl, byte ptr [eax + 1h]
loc_419be6:
    push	edx
loc_419be7:
    push	ecx
loc_419be8:
    call ?GenerateTextureCells@@YAXHDHHHHHH@Z
loc_419bed:
    add	esp, 20h
loc_419bf0:
    jmp loc_41a05f
loc_419bf5:
    cmp	edx, 4h
loc_419bf8:
    jne loc_419c20
loc_419bfa:
    xor	edx, edx
loc_419bfc:
    and	ecx, 0ffh
loc_419c02:
    mov	dl, byte ptr [eax + 3h]
loc_419c05:
    push	edx
loc_419c06:
    xor	edx, edx
loc_419c08:
    mov	dl, byte ptr [eax + 2h]
loc_419c0b:
    push	edx
loc_419c0c:
    xor	edx, edx
loc_419c0e:
    mov	dl, byte ptr [eax + 1h]
loc_419c11:
    push	edx
loc_419c12:
    push	ecx
loc_419c13:
    call ?GenerateTextureRadialGradient@@YAXHHDH@Z
loc_419c18:
    add	esp, 10h
loc_419c1b:
    jmp loc_41a05f
loc_419c20:
    cmp	edx, 5h
loc_419c23:
    jne loc_419c5d
loc_419c25:
    xor	edx, edx
loc_419c27:
    and	ecx, 0ffh
loc_419c2d:
    mov	dl, byte ptr [eax + 6h]
loc_419c30:
    push	edx
loc_419c31:
    xor	edx, edx
loc_419c33:
    mov	dl, byte ptr [eax + 5h]
loc_419c36:
    push	edx
loc_419c37:
    xor	edx, edx
loc_419c39:
    mov	dl, byte ptr [eax + 4h]
loc_419c3c:
    push	edx
loc_419c3d:
    xor	edx, edx
loc_419c3f:
    mov	dl, byte ptr [eax + 3h]
loc_419c42:
    push	edx
loc_419c43:
    xor	edx, edx
loc_419c45:
    mov	dl, byte ptr [eax + 2h]
loc_419c48:
    push	edx
loc_419c49:
    xor	edx, edx
loc_419c4b:
    mov	dl, byte ptr [eax + 1h]
loc_419c4e:
    push	edx
loc_419c4f:
    push	ecx
loc_419c50:
    call ?GenerateTextureCubicNoise@@YAXHDHHHHH@Z
loc_419c55:
    add	esp, 1ch
loc_419c58:
    jmp loc_41a05f
loc_419c5d:
    cmp	edx, 6h
loc_419c60:
    jne loc_419c7d
loc_419c62:
    and	ecx, 0ffh
loc_419c68:
    mov	eax, dword ptr [4*ecx + ?g_textureLayers@@3PAPAEA]
loc_419c6f:
    push	eax
loc_419c70:
    call ?ClearTextureWorkBuffer@@YAHPAX@Z
loc_419c75:
    add	esp, 4h
loc_419c78:
    jmp loc_41a05f
loc_419c7d:
    cmp	edx, 0ah
loc_419c80:
    jne loc_419cba
loc_419c82:
    xor	edx, edx
loc_419c84:
    and	ecx, 0ffh
loc_419c8a:
    mov	dl, byte ptr [eax + 6h]
loc_419c8d:
    push	edx
loc_419c8e:
    xor	edx, edx
loc_419c90:
    mov	dl, byte ptr [eax + 5h]
loc_419c93:
    push	edx
loc_419c94:
    xor	edx, edx
loc_419c96:
    mov	dl, byte ptr [eax + 4h]
loc_419c99:
    push	edx
loc_419c9a:
    xor	edx, edx
loc_419c9c:
    mov	dl, byte ptr [eax + 3h]
loc_419c9f:
    push	edx
loc_419ca0:
    xor	edx, edx
loc_419ca2:
    mov	dl, byte ptr [eax + 2h]
loc_419ca5:
    push	edx
loc_419ca6:
    xor	edx, edx
loc_419ca8:
    mov	dl, byte ptr [eax + 1h]
loc_419cab:
    push	edx
loc_419cac:
    push	ecx
loc_419cad:
    call ?DistortTextureSine@@YAHHHHHHHH@Z
loc_419cb2:
    add	esp, 1ch
loc_419cb5:
    jmp loc_41a05f
loc_419cba:
    cmp	edx, 0bh
loc_419cbd:
    jne loc_419cdf
loc_419cbf:
    xor	edx, edx
loc_419cc1:
    and	ecx, 0ffh
loc_419cc7:
    mov	dl, byte ptr [eax + 2h]
loc_419cca:
    push	edx
loc_419ccb:
    xor	edx, edx
loc_419ccd:
    mov	dl, byte ptr [eax + 1h]
loc_419cd0:
    push	edx
loc_419cd1:
    push	ecx
loc_419cd2:
    call ?TranslateTextureLayerWrapped@@YAXHDD@Z
loc_419cd7:
    add	esp, 0ch
loc_419cda:
    jmp loc_41a05f
loc_419cdf:
    cmp	edx, 0ch
loc_419ce2:
    jne loc_419cfe
loc_419ce4:
    xor	edx, edx
loc_419ce6:
    and	ecx, 0ffh
loc_419cec:
    mov	dl, byte ptr [eax + 1h]
loc_419cef:
    push	edx
loc_419cf0:
    push	ecx
loc_419cf1:
    call ?DistortTextureTwirl@@YAHHH@Z
loc_419cf6:
    add	esp, 8h
loc_419cf9:
    jmp loc_41a05f
loc_419cfe:
    cmp	edx, 0eh
loc_419d01:
    jne loc_419d1d
loc_419d03:
    xor	edx, edx
loc_419d05:
    and	ecx, 0ffh
loc_419d0b:
    mov	dl, byte ptr [eax + 1h]
loc_419d0e:
    push	edx
loc_419d0f:
    push	ecx
loc_419d10:
    call ?SubtractShiftedTextureLayer@@YAXHF@Z
loc_419d15:
    add	esp, 8h
loc_419d18:
    jmp loc_41a05f
loc_419d1d:
    cmp	edx, 0fh
loc_419d20:
    jne loc_419d3c
loc_419d22:
    xor	edx, edx
loc_419d24:
    and	ecx, 0ffh
loc_419d2a:
    mov	dl, byte ptr [eax + 1h]
loc_419d2d:
    push	edx
loc_419d2e:
    push	ecx
loc_419d2f:
    call ?BlurTextureLayer@@YAHHH@Z
loc_419d34:
    add	esp, 8h
loc_419d37:
    jmp loc_41a05f
loc_419d3c:
    cmp	edx, 11h
loc_419d3f:
    jne loc_419d79
loc_419d41:
    xor	edx, edx
loc_419d43:
    and	ecx, 0ffh
loc_419d49:
    mov	dl, byte ptr [eax + 6h]
loc_419d4c:
    push	edx
loc_419d4d:
    xor	edx, edx
loc_419d4f:
    mov	dl, byte ptr [eax + 5h]
loc_419d52:
    push	edx
loc_419d53:
    xor	edx, edx
loc_419d55:
    mov	dl, byte ptr [eax + 4h]
loc_419d58:
    push	edx
loc_419d59:
    xor	edx, edx
loc_419d5b:
    mov	dl, byte ptr [eax + 3h]
loc_419d5e:
    push	edx
loc_419d5f:
    xor	edx, edx
loc_419d61:
    mov	dl, byte ptr [eax + 2h]
loc_419d64:
    push	edx
loc_419d65:
    xor	edx, edx
loc_419d67:
    mov	dl, byte ptr [eax + 1h]
loc_419d6a:
    push	edx
loc_419d6b:
    push	ecx
loc_419d6c:
    call ?DistortTextureByLayers@@YAHHHDHHDH@Z
loc_419d71:
    add	esp, 1ch
loc_419d74:
    jmp loc_41a05f
loc_419d79:
    cmp	edx, 12h
loc_419d7c:
    jne loc_419da4
loc_419d7e:
    xor	edx, edx
loc_419d80:
    and	ecx, 0ffh
loc_419d86:
    mov	dl, byte ptr [eax + 3h]
loc_419d89:
    push	edx
loc_419d8a:
    xor	edx, edx
loc_419d8c:
    mov	dl, byte ptr [eax + 2h]
loc_419d8f:
    push	edx
loc_419d90:
    xor	edx, edx
loc_419d92:
    mov	dl, byte ptr [eax + 1h]
loc_419d95:
    push	edx
loc_419d96:
    push	ecx
loc_419d97:
    call ?DirectionalBlurTextureLayer@@YAXHHDH@Z
loc_419d9c:
    add	esp, 10h
loc_419d9f:
    jmp loc_41a05f
loc_419da4:
    cmp	edx, 14h
loc_419da7:
    jne loc_419dcf
loc_419da9:
    xor	edx, edx
loc_419dab:
    and	ecx, 0ffh
loc_419db1:
    mov	dl, byte ptr [eax + 3h]
loc_419db4:
    push	edx
loc_419db5:
    xor	edx, edx
loc_419db7:
    mov	dl, byte ptr [eax + 2h]
loc_419dba:
    push	edx
loc_419dbb:
    xor	edx, edx
loc_419dbd:
    mov	dl, byte ptr [eax + 1h]
loc_419dc0:
    push	edx
loc_419dc1:
    push	ecx
loc_419dc2:
    call ?SwapTextureChannels@@YAXHDHD@Z
loc_419dc7:
    add	esp, 10h
loc_419dca:
    jmp loc_41a05f
loc_419dcf:
    cmp	edx, 15h
loc_419dd2:
    jne loc_419dee
loc_419dd4:
    xor	edx, edx
loc_419dd6:
    and	ecx, 0ffh
loc_419ddc:
    mov	dl, byte ptr [eax + 1h]
loc_419ddf:
    push	edx
loc_419de0:
    push	ecx
loc_419de1:
    call ?ReplicateTextureChannel@@YAHHD@Z
loc_419de6:
    add	esp, 8h
loc_419de9:
    jmp loc_41a05f
loc_419dee:
    cmp	edx, 17h
loc_419df1:
    jne loc_419e19
loc_419df3:
    xor	edx, edx
loc_419df5:
    and	ecx, 0ffh
loc_419dfb:
    mov	dl, byte ptr [eax + 3h]
loc_419dfe:
    push	edx
loc_419dff:
    xor	edx, edx
loc_419e01:
    mov	dl, byte ptr [eax + 2h]
loc_419e04:
    push	edx
loc_419e05:
    xor	edx, edx
loc_419e07:
    mov	dl, byte ptr [eax + 1h]
loc_419e0a:
    push	edx
loc_419e0b:
    push	ecx
loc_419e0c:
    call ?CopyTextureChannel@@YAXHDHD@Z
loc_419e11:
    add	esp, 10h
loc_419e14:
    jmp loc_41a05f
loc_419e19:
    cmp	edx, 18h
loc_419e1c:
    jne loc_419e3e
loc_419e1e:
    xor	edx, edx
loc_419e20:
    and	ecx, 0ffh
loc_419e26:
    mov	dl, byte ptr [eax + 2h]
loc_419e29:
    push	edx
loc_419e2a:
    xor	edx, edx
loc_419e2c:
    mov	dl, byte ptr [eax + 1h]
loc_419e2f:
    push	edx
loc_419e30:
    push	ecx
loc_419e31:
    call ?MixTextureLayers@@YAXHHH@Z
loc_419e36:
    add	esp, 0ch
loc_419e39:
    jmp loc_41a05f
loc_419e3e:
    cmp	edx, 19h
loc_419e41:
    jne loc_419e5d
loc_419e43:
    xor	edx, edx
loc_419e45:
    and	ecx, 0ffh
loc_419e4b:
    mov	dl, byte ptr [eax + 1h]
loc_419e4e:
    push	edx
loc_419e4f:
    push	ecx
loc_419e50:
    call ?MultiplyTextureLayers@@YAXHH@Z
loc_419e55:
    add	esp, 8h
loc_419e58:
    jmp loc_41a05f
loc_419e5d:
    cmp	edx, 1ah
loc_419e60:
    jne loc_419e7c
loc_419e62:
    xor	edx, edx
loc_419e64:
    and	ecx, 0ffh
loc_419e6a:
    mov	dl, byte ptr [eax + 1h]
loc_419e6d:
    push	edx
loc_419e6e:
    push	ecx
loc_419e6f:
    call ?AddTextureLayersSaturated@@YAXHH@Z
loc_419e74:
    add	esp, 8h
loc_419e77:
    jmp loc_41a05f
loc_419e7c:
    cmp	edx, 1bh
loc_419e7f:
    jne loc_419e9b
loc_419e81:
    xor	edx, edx
loc_419e83:
    and	ecx, 0ffh
loc_419e89:
    mov	dl, byte ptr [eax + 1h]
loc_419e8c:
    push	edx
loc_419e8d:
    push	ecx
loc_419e8e:
    call ?MaxTextureLayers@@YAXHH@Z
loc_419e93:
    add	esp, 8h
loc_419e96:
    jmp loc_41a05f
loc_419e9b:
    cmp	edx, 1eh
loc_419e9e:
    jne loc_419eba
loc_419ea0:
    xor	edx, edx
loc_419ea2:
    and	ecx, 0ffh
loc_419ea8:
    mov	dl, byte ptr [eax + 1h]
loc_419eab:
    push	edx
loc_419eac:
    push	ecx
loc_419ead:
    call ?AdjustTextureContrast@@YAXHH@Z
loc_419eb2:
    add	esp, 8h
loc_419eb5:
    jmp loc_41a05f
loc_419eba:
    cmp	edx, 1fh
loc_419ebd:
    jne loc_419ed3
loc_419ebf:
    and	ecx, 0ffh
loc_419ec5:
    push	ecx
loc_419ec6:
    call ?InvertTextureLayerLowBytes@@YAXH@Z
loc_419ecb:
    add	esp, 4h
loc_419ece:
    jmp loc_41a05f
loc_419ed3:
    cmp	edx, 20h
loc_419ed6:
    jne loc_419ef8
loc_419ed8:
    xor	edx, edx
loc_419eda:
    and	ecx, 0ffh
loc_419ee0:
    mov	dl, byte ptr [eax + 2h]
loc_419ee3:
    push	edx
loc_419ee4:
    xor	edx, edx
loc_419ee6:
    mov	dl, byte ptr [eax + 1h]
loc_419ee9:
    push	edx
loc_419eea:
    push	ecx
loc_419eeb:
    call ?ShadeTextureLayerByChannel@@YAXHHD@Z
loc_419ef0:
    add	esp, 0ch
loc_419ef3:
    jmp loc_41a05f
loc_419ef8:
    cmp	edx, 21h
loc_419efb:
    jne loc_419f17
loc_419efd:
    xor	edx, edx
loc_419eff:
    and	ecx, 0ffh
loc_419f05:
    mov	dl, byte ptr [eax + 1h]
loc_419f08:
    push	edx
loc_419f09:
    push	ecx
loc_419f0a:
    call ?ApplyTextureColorMap@@YAXHH@Z
loc_419f0f:
    add	esp, 8h
loc_419f12:
    jmp loc_41a05f
loc_419f17:
    cmp	edx, 22h
loc_419f1a:
    jne loc_419f3c
loc_419f1c:
    xor	edx, edx
loc_419f1e:
    and	ecx, 0ffh
loc_419f24:
    mov	dl, byte ptr [eax + 2h]
loc_419f27:
    push	edx
loc_419f28:
    xor	edx, edx
loc_419f2a:
    mov	dl, byte ptr [eax + 1h]
loc_419f2d:
    push	edx
loc_419f2e:
    push	ecx
loc_419f2f:
    call ?ApplyTextureCosineWave@@YAXHDH@Z
loc_419f34:
    add	esp, 0ch
loc_419f37:
    jmp loc_41a05f
loc_419f3c:
    cmp	edx, 23h
loc_419f3f:
    jne loc_419f67
loc_419f41:
    xor	edx, edx
loc_419f43:
    and	ecx, 0ffh
loc_419f49:
    mov	dl, byte ptr [eax + 3h]
loc_419f4c:
    push	edx
loc_419f4d:
    xor	edx, edx
loc_419f4f:
    mov	dl, byte ptr [eax + 2h]
loc_419f52:
    push	edx
loc_419f53:
    xor	edx, edx
loc_419f55:
    mov	dl, byte ptr [eax + 1h]
loc_419f58:
    push	edx
loc_419f59:
    push	ecx
loc_419f5a:
    call ?RemapTextureChannelRange@@YAXHDHH@Z
loc_419f5f:
    add	esp, 10h
loc_419f62:
    jmp loc_41a05f
loc_419f67:
    cmp	edx, 24h
loc_419f6a:
    jne loc_419f8c
loc_419f6c:
    xor	edx, edx
loc_419f6e:
    and	ecx, 0ffh
loc_419f74:
    mov	dl, byte ptr [eax + 2h]
loc_419f77:
    push	edx
loc_419f78:
    xor	edx, edx
loc_419f7a:
    mov	dl, byte ptr [eax + 1h]
loc_419f7d:
    push	edx
loc_419f7e:
    push	ecx
loc_419f7f:
    call ?AdjustTextureHsv@@YAXHHH@Z
loc_419f84:
    add	esp, 0ch
loc_419f87:
    jmp loc_41a05f
loc_419f8c:
    cmp	edx, 25h
loc_419f8f:
    jne loc_419fcf
loc_419f91:
    xor	edx, edx
loc_419f93:
    and	ecx, 0ffh
loc_419f99:
    mov	dl, byte ptr [eax + 7h]
loc_419f9c:
    push	edx
loc_419f9d:
    xor	edx, edx
loc_419f9f:
    mov	dl, byte ptr [eax + 6h]
loc_419fa2:
    push	edx
loc_419fa3:
    xor	edx, edx
loc_419fa5:
    mov	dl, byte ptr [eax + 5h]
loc_419fa8:
    push	edx
loc_419fa9:
    xor	edx, edx
loc_419fab:
    mov	dl, byte ptr [eax + 4h]
loc_419fae:
    push	edx
loc_419faf:
    xor	edx, edx
loc_419fb1:
    mov	dl, byte ptr [eax + 3h]
loc_419fb4:
    push	edx
loc_419fb5:
    xor	edx, edx
loc_419fb7:
    mov	dl, byte ptr [eax + 2h]
loc_419fba:
    push	edx
loc_419fbb:
    xor	edx, edx
loc_419fbd:
    mov	dl, byte ptr [eax + 1h]
loc_419fc0:
    push	edx
loc_419fc1:
    push	ecx
loc_419fc2:
    call ?ApplyTextureGradient@@YAXHCHHHHHH@Z
loc_419fc7:
    add	esp, 20h
loc_419fca:
    jmp loc_41a05f
loc_419fcf:
    cmp	edx, 26h
loc_419fd2:
    jne loc_419ff7
loc_419fd4:
    xor	edx, edx
loc_419fd6:
    and	ecx, 0ffh
loc_419fdc:
    mov	dl, byte ptr [eax + 3h]
loc_419fdf:
    push	edx
loc_419fe0:
    xor	edx, edx
loc_419fe2:
    mov	dl, byte ptr [eax + 2h]
loc_419fe5:
    push	edx
loc_419fe6:
    xor	edx, edx
loc_419fe8:
    mov	dl, byte ptr [eax + 1h]
loc_419feb:
    push	edx
loc_419fec:
    push	ecx
loc_419fed:
    call ?BlendTextureLayersByMask@@YAXHHHC@Z
loc_419ff2:
    add	esp, 10h
loc_419ff5:
    jmp loc_41a05f
loc_419ff7:
    cmp	edx, 27h
loc_419ffa:
    jne loc_41a00d
loc_419ffc:
    and	ecx, 0ffh
loc_41a002:
    push	ecx
loc_41a003:
    call ?EmbossTextureLayer@@YAXH@Z
loc_41a008:
    add	esp, 4h
loc_41a00b:
    jmp loc_41a05f
loc_41a00d:
    cmp	edx, 28h
loc_41a010:
    jne loc_41a05f
loc_41a012:
    xor	edx, edx
loc_41a014:
    xor	ebx, ebx
loc_41a016:
    mov	dl, byte ptr [eax + 4h]
loc_41a019:
    mov	bl, byte ptr [eax + 5h]
loc_41a01c:
    shl	edx, 8h
loc_41a01f:
    add	edx, ebx
loc_41a021:
    xor	ebx, ebx
loc_41a023:
    mov	bl, byte ptr [eax + 6h]
loc_41a026:
    add	eax, 8h
loc_41a029:
    shl	edx, 8h
loc_41a02c:
    add	edx, ebx
loc_41a02e:
    xor	ebx, ebx
loc_41a030:
    mov	bl, byte ptr [eax - 6h]
loc_41a033:
    push	edx
loc_41a034:
    xor	edx, edx
loc_41a036:
    and	ecx, 0ffh
loc_41a03c:
    mov	dl, byte ptr [eax - 7h]
loc_41a03f:
    shl	edx, 8h
loc_41a042:
    add	edx, ebx
loc_41a044:
    xor	ebx, ebx
loc_41a046:
    mov	bl, byte ptr [eax - 5h]
loc_41a049:
    shl	edx, 8h
loc_41a04c:
    add	edx, ebx
loc_41a04e:
    push	edx
loc_41a04f:
    push	eax
loc_41a050:
    push	ecx
loc_41a051:
    call ?ExpandTextureBitmap@@YAPAIHPAEII@Z
loc_41a056:
    add	esp, 10h
loc_41a059:
    add	esi, 2000h
loc_41a05f:
    mov	ebx, dword ptr [?g_textureProgramCompletedWork@@3HA]
loc_41a065:
    push	ecx
loc_41a066:
    inc	ebx
loc_41a067:
    mov	dword ptr [?g_textureProgramCompletedWork@@3HA], ebx
loc_41a06d:
    fild	dword ptr [?g_textureProgramCompletedWork@@3HA]
loc_41a073:
    fidiv	dword ptr [?g_textureProgramTotalWork@@3HA]
loc_41a079:
    fstp	dword ptr [esp]
loc_41a07c:
    call	dword ptr [?g_textureProgressCallback@@3P6GXM@ZA]
loc_41a082:
    mov	eax, dword ptr [esp + 14h]
loc_41a086:
    add	ebp, 9h
loc_41a089:
    dec	eax
loc_41a08a:
    mov	dword ptr [esp + 14h], eax
loc_41a08e:
    jne loc_419b25
loc_41a094:
    mov	ebx, dword ptr [esp + 18h]
loc_41a098:
    pop	ebp
loc_41a099:
    mov	esi, dword ptr [?g_textureLayers@@3PAPAEA]
loc_41a09f:
    mov	ecx, 10000h
loc_41a0a4:
    mov	edi, ebx
loc_41a0a6:
    rep movsd
loc_41a0a8:
    mov	al, byte ptr [?g_textureLoadFromTga@@3EA]
loc_41a0ad:
    pop	esi
loc_41a0ae:
    test	al, al
loc_41a0b0:
    je loc_41a0c0
loc_41a0b2:
    mov	eax, dword ptr [?g_textureLayers@@3PAPAEA]
loc_41a0b7:
    push	eax
loc_41a0b8:
    call ?ExportTextureTga@@YACPAI@Z
loc_41a0bd:
    add	esp, 4h
loc_41a0c0:
    pop	edi
loc_41a0c1:
    pop	ebx
loc_41a0c2:
    ret
?ExecuteTextureProgram@@YAXPAXPAI@Z ENDP

END
