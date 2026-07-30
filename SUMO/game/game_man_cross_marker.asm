.386
.model flat
option casemap:none

EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?GameAudioNoOpCallback@@YAXXZ:PROC
EXTERN ?g_gameBoxYScale@@3MB:DWORD

.code

; FUNCTION: SUMO 0x0040fdae
; FUNCTION: EDITOR 0x0040fdd0
PUBLIC ?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z
?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 24h
    fld DWORD PTR [?g_gameBoxYScale@@3MB]
    push ebx
    fst DWORD PTR [ebp-0Ch]
    push esi
    push edi
    fldz
    fstp DWORD PTR [ebp-8]
    push DWORD PTR [ebp+0Ch]
    mov ebx, [ebp+8]
    lea esi, [ebp-0Ch]
    fstp DWORD PTR [ebp-4]
    lea edi, [ebp-18h]
    movsd
    fld1
    movsd
    movsd
    fstp DWORD PTR [ebp-0Ch]
    fldz
    fstp DWORD PTR [ebp-8]
    lea esi, [ebp-0Ch]
    fld1
    lea edi, [ebp-24h]
    fstp DWORD PTR [ebp-4]
    movsd
    lea eax, [ebp-18h]
    movsd
    push eax
    lea eax, [ebp-0Ch]
    push eax
    mov ecx, ebx
    movsd
    call ??HVector3@@QAE?AU0@AAU0@@Z
    push eax
    lea eax, [ebp-24h]
    push eax
    lea eax, [ebp-18h]
    push eax
    mov ecx, ebx
    call ??HVector3@@QAE?AU0@AAU0@@Z
    push eax
    call ?GameAudioNoOpCallback@@YAXXZ
    fld DWORD PTR [?g_gameBoxYScale@@3MB]
    fst DWORD PTR [ebp-0Ch]
    lea esi, [ebp-0Ch]
    fldz
    lea edi, [ebp-24h]
    fstp DWORD PTR [ebp-8]
    add esp, 0Ch
    push DWORD PTR [ebp+0Ch]
    fld1
    fstp DWORD PTR [ebp-4]
    lea eax, [ebp-24h]
    fld1
    push eax
    movsd
    movsd
    movsd
    fstp DWORD PTR [ebp-0Ch]
    fldz
    fstp DWORD PTR [ebp-8]
    lea esi, [ebp-0Ch]
    lea edi, [ebp-18h]
    lea eax, [ebp-0Ch]
    fstp DWORD PTR [ebp-4]
    movsd
    movsd
    push eax
    mov ecx, ebx
    movsd
    call ??HVector3@@QAE?AU0@AAU0@@Z
    push eax
    lea eax, [ebp-18h]
    push eax
    lea eax, [ebp-24h]
    push eax
    mov ecx, ebx
    call ??HVector3@@QAE?AU0@AAU0@@Z
    push eax
    call ?GameAudioNoOpCallback@@YAXXZ
    add esp, 0Ch
    pop edi
    pop esi
    pop ebx
    leave
    ret
?RenderGameCrossMarker@@YAXPAUVector3@@PAX@Z ENDP

END
