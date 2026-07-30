.686
.model flat
option casemap:none

EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC

.code

; FUNCTION: SUMO 0x0040e874
; FUNCTION: EDITOR 0x0040e896
PUBLIC ?CalculateKineticEnergy@GameMan@@QAEMXZ
?CalculateKineticEnergy@GameMan@@QAEMXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 0ch
    push ebx
    fldz
    push esi
    fstp dword ptr [ebp-4]
    push edi
    mov dword ptr [ebp-8], ecx
    xor ebx, ebx
    jmp short energy_loop
discard_previous:
    fstp st(0)
energy_loop:
    mov eax, dword ptr [ebp-8]
    lea eax, [eax+ebx*4]
    mov esi, dword ptr [eax]
    lea ecx, [esi+09ch]
    mov edi, esi
    call ?LengthSquared@Vector3@@QAEMXZ
    fmul dword ptr [esi+0ach]
    lea ecx, [edi+090h]
    fstp dword ptr [ebp-0ch]
    call ?LengthSquared@Vector3@@QAEMXZ
    fmul dword ptr [edi+0b4h]
    inc ebx
    cmp ebx, 0fh
    fadd dword ptr [ebp-0ch]
    fadd dword ptr [ebp-4]
    fst dword ptr [ebp-4]
    jl short discard_previous
    pop edi
    pop esi
    pop ebx
    leave
    ret
?CalculateKineticEnergy@GameMan@@QAEMXZ ENDP

END
