.586
.model flat
option casemap:none

EXTERN ?g_textureLayers@@3PAPAEA:DWORD
EXTERN ?g_textureInvSize@@3NB:QWORD
EXTERN ?g_textureWorkBuffer@@3PAIA:DWORD
EXTERN ?SampleTexturePixel@@YAIPAIMM@Z:PROC

.code

; FUNCTION: SUMO 0x0041afd0
; FUNCTION: EDITOR 0x0041aff0
PUBLIC ?DistortTextureByLayers@@YAHHHDHHDH@Z
?DistortTextureByLayers@@YAHHHDHHDH@Z PROC
    sub esp, 20h
    mov eax, dword ptr [esp + 24h]
    mov edx, dword ptr [esp + 28h]
    fild dword ptr [esp + 30h]
    mov ecx, dword ptr [?g_textureLayers@@3PAPAEA + eax * 4]
    mov eax, dword ptr [?g_textureLayers@@3PAPAEA + edx * 4]
    mov dl, byte ptr [esp + 2ch]
    mov dword ptr [esp], ecx
    mov ecx, dword ptr [esp + 34h]
    mov dword ptr [esp + 8], eax
    shl dl, 3
    mov eax, dword ptr [?g_textureLayers@@3PAPAEA + ecx * 4]
    mov cl, 10h
    fmul qword ptr [?g_textureInvSize@@3NB]
    sub cl, dl
    mov dl, byte ptr [esp + 38h]
    mov byte ptr [esp + 28h], cl
    mov cl, 10h
    shl dl, 3
    fstp dword ptr [esp + 0ch]
    fild dword ptr [esp + 3ch]
    sub cl, dl
    push ebx
    mov byte ptr [esp + 38h], cl
    mov ecx, dword ptr [esp + 2ch]
    and ecx, 0ffh
    xor edx, edx
    fmul qword ptr [?g_textureInvSize@@3NB]
    mov dword ptr [esp + 34h], ecx
    mov ecx, dword ptr [esp + 38h]
    xor ebx, ebx
    push ebp
    and ecx, 0ffh
    push esi
    fstp dword ptr [esp + 48h]
    push edi
    mov dword ptr [esp + 14h], eax
    mov dword ptr [esp + 34h], edx
    mov dword ptr [esp + 44h], ecx
    jmp distortLayersRowSetup

distortLayersReloadYMap:
    mov eax, dword ptr [esp + 14h]
    xor edx, edx

distortLayersRowSetup:
    fild dword ptr [esp + 34h]
    mov edi, dword ptr [esp + 18h]
    xor ebp, ebp
    mov dword ptr [esp + 38h], ebp
    lea esi, dword ptr [eax + ebx * 4]
    fstp dword ptr [esp + 3ch]
    sub edi, eax
    jmp distortLayersPixel

distortLayersClearHighWords:
    xor edx, edx

distortLayersPixel:
    db 08bh, 004h, 037h
    mov ecx, dword ptr [esp + 40h]
    shr eax, cl
    mov dword ptr [esp + 24h], edx
    mov ecx, dword ptr [esp + 44h]
    mov dword ptr [esp + 2ch], edx
    and eax, 0ffh
    mov dword ptr [esp + 20h], eax
    mov eax, dword ptr [esi]
    fild qword ptr [esp + 20h]
    shr eax, cl
    fmul dword ptr [esp + 1ch]
    and eax, 0ffh
    fiadd dword ptr [esp + 38h]
    mov dword ptr [esp + 28h], eax
    mov eax, dword ptr [esp + 10h]
    fstp dword ptr [esp + 48h]
    fild qword ptr [esp + 28h]
    mov edx, dword ptr [esp + 48h]
    fmul dword ptr [esp + 4ch]
    fadd dword ptr [esp + 3ch]
    fstp dword ptr [esp + 38h]
    mov ecx, dword ptr [esp + 38h]
    push ecx
    push edx
    push eax
    call ?SampleTexturePixel@@YAIPAIMM@Z
    mov ecx, dword ptr [?g_textureWorkBuffer@@3PAIA]
    add esp, 0ch
    add esi, 4
    mov dword ptr [ecx + ebx * 4], eax
    inc ebx
    inc ebp
    cmp ebp, 100h
    mov dword ptr [esp + 38h], ebp
    jl distortLayersClearHighWords
    mov eax, dword ptr [esp + 34h]
    inc eax
    cmp eax, 100h
    mov dword ptr [esp + 34h], eax
    jl distortLayersReloadYMap
    mov esi, dword ptr [?g_textureWorkBuffer@@3PAIA]
    mov edi, dword ptr [esp + 10h]
    mov ecx, 10000h
    rep movsd
    pop edi
    pop esi
    pop ebp
distortLayersBodyEnd LABEL BYTE
?DistortTextureByLayers@@YAHHHDHHDH@Z ENDP

PUBLIC ?PopTextureLayerDistortionRegister@@YAXXZ
?PopTextureLayerDistortionRegister@@YAXXZ PROC
    pop ebx
?PopTextureLayerDistortionRegister@@YAXXZ ENDP

; FUNCTION: SUMO 0x0041b12a
; FUNCTION: EDITOR 0x0041b14a
PUBLIC ?FinishTextureLayerDistortion@@YAXXZ
?FinishTextureLayerDistortion@@YAXXZ PROC
    add esp, 20h
    ret
?FinishTextureLayerDistortion@@YAXXZ ENDP

END
