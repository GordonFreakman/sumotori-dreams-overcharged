.386
.model flat
option casemap:none

EXTERN ?g_gameOne@@3MB:DWORD

.code

; FUNCTION: SUMO 0x00407e99
; FUNCTION: EDITOR 0x00407ebb
PUBLIC ?Inverted@Matrix3@@QAE?AU1@XZ
?Inverted@Matrix3@@QAE?AU1@XZ PROC
    push ebp
    mov ebp, esp
    sub esp, 2Ch
    fld DWORD PTR [ecx+14h]
    push esi
    fmul DWORD PTR [ecx+18h]
    push edi
    fld DWORD PTR [ecx+20h]
    fmul DWORD PTR [ecx+0Ch]
    fsubp st(1), st
    fld DWORD PTR [ecx+1Ch]
    fmul DWORD PTR [ecx+0Ch]
    fld DWORD PTR [ecx+18h]
    fmul DWORD PTR [ecx+10h]
    fsubp st(1), st
    fstp DWORD PTR [ebp-8]
    fld DWORD PTR [ecx+20h]
    fmul DWORD PTR [ecx+10h]
    fld DWORD PTR [ecx+14h]
    fmul DWORD PTR [ecx+1Ch]
    fsubp st(1), st
    fst DWORD PTR [ebp-4]
    fmul DWORD PTR [ecx]
    fld st(1)
    fmul DWORD PTR [ecx+4]
    faddp st(1), st
    fld DWORD PTR [ebp-8]
    fmul DWORD PTR [ecx+8]
    faddp st(1), st
    fdivr DWORD PTR [?g_gameOne@@3MB]
    fld DWORD PTR [ebp-4]
    fmul st, st(1)
    fstp DWORD PTR [ebp-2Ch]
    fld DWORD PTR [ecx+8]
    fmul DWORD PTR [ecx+1Ch]
    fld DWORD PTR [ecx+20h]
    fmul DWORD PTR [ecx+4]
    fsubp st(1), st
    fmul st, st(1)
    fstp DWORD PTR [ebp-20h]
    fld DWORD PTR [ecx+14h]
    fmul DWORD PTR [ecx+4]
    fld DWORD PTR [ecx+8]
    fmul DWORD PTR [ecx+10h]
    fsubp st(1), st
    fmul st, st(1)
    fstp DWORD PTR [ebp-14h]
    fld st(1)
    fmul st, st(1)
    fstp DWORD PTR [ebp-28h]
    fld DWORD PTR [ecx+20h]
    fmul DWORD PTR [ecx]
    fld DWORD PTR [ecx+8]
    fmul DWORD PTR [ecx+18h]
    fsubp st(1), st
    fmul st, st(1)
    fstp DWORD PTR [ebp-1Ch]
    fld DWORD PTR [ecx+8]
    fmul DWORD PTR [ecx+0Ch]
    fld DWORD PTR [ecx+14h]
    fmul DWORD PTR [ecx]
    fsubp st(1), st
    fmul st, st(1)
    fstp DWORD PTR [ebp-10h]
    fld DWORD PTR [ebp-8]
    fmul st, st(1)
    fstp DWORD PTR [ebp-24h]
    fld DWORD PTR [ecx+18h]
    fmul DWORD PTR [ecx+4]
    fld DWORD PTR [ecx]
    fmul DWORD PTR [ecx+1Ch]
    fsubp st(1), st
    fmul st, st(1)
    fstp DWORD PTR [ebp-18h]
    fld DWORD PTR [ecx]
    fmul DWORD PTR [ecx+10h]
    fld DWORD PTR [ecx+0Ch]
    fmul DWORD PTR [ecx+4]
    mov eax, [ebp+8]
    fsubp st(1), st
    push 9
    pop ecx
    fmul st, st(1)
    lea esi, [ebp-2Ch]
    mov edi, eax
    fstp DWORD PTR [ebp-0Ch]
    rep movsd
    fstp st(0)
    fstp st(0)
    pop edi
    pop esi
    leave
    ret 4
?Inverted@Matrix3@@QAE?AU1@XZ ENDP

END
