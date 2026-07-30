.386
.model flat
option casemap:none

EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN ?g_gameOne@@3MB:DWORD

.code

; FUNCTION: SUMO 0x0040b776
; FUNCTION: EDITOR 0x0040b798
PUBLIC ?Next@GameRandomGenerator@@QAEMXZ
?Next@GameRandomGenerator@@QAEMXZ PROC
    mov eax, dword ptr [ecx + 194h]
    lea edx, [ecx + eax * 4]
    mov eax, dword ptr [ecx + 198h]
    fld dword ptr [edx]
    fsub dword ptr [ecx + eax * 4]
    fcom dword ptr [?g_vectorZero@@3MB]
    fnstsw ax
    test ah, 5
    jp short valueReady
    fadd dword ptr [?g_gameOne@@3MB]
valueReady:
    fst dword ptr [edx]
    dec dword ptr [ecx + 194h]
    push 61h
    pop eax
    jnz short firstIndexReady
    mov dword ptr [ecx + 194h], eax
firstIndexReady:
    dec dword ptr [ecx + 198h]
    jnz short secondIndexReady
    mov dword ptr [ecx + 198h], eax
secondIndexReady:
    fld dword ptr [ecx + 188h]
    fsub dword ptr [ecx + 18ch]
    fcom dword ptr [?g_vectorZero@@3MB]
    fst dword ptr [ecx + 188h]
    fnstsw ax
    test ah, 5
    jp short carryReady
    fadd dword ptr [ecx + 190h]
    fstp dword ptr [ecx + 188h]
    jmp short subtractCarry
carryReady:
    fstp st(0)
subtractCarry:
    fsub dword ptr [ecx + 188h]
    fcom dword ptr [?g_vectorZero@@3MB]
    fnstsw ax
    test ah, 5
    jp short randomReady
    fadd dword ptr [?g_gameOne@@3MB]
randomReady:
    ret
?Next@GameRandomGenerator@@QAEMXZ ENDP

END
