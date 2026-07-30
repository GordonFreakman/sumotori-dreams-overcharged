.686
.model flat
option casemap:none

EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameSimulationStep@@3MA:DWORD
EXTERN ?g_gameInverseSimulationStep@@3MA:DWORD
EXTERN ?g_waterMotionThreshold@@3MB:DWORD
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?ApplyWaterInteraction@GameBox@@QAEXXZ:PROC

.code

; FUNCTION: SUMO 0x0040b588
; FUNCTION: EDITOR 0x0040b5aa
PUBLIC ?ApplyWaterInteractionToMovingBoxes@@YAXXZ
?ApplyWaterInteractionToMovingBoxes@@YAXXZ PROC
    fld1
    mov eax, OFFSET ?g_gameBoxes@@3PAUGameBox@@A
    cmp dword ptr [?g_gameBoxesEnd@@3PAUGameBox@@A], eax
    fdiv dword ptr [?g_gameSimulationStep@@3MA]
    push esi
    mov esi, eax
    fstp dword ptr [?g_gameInverseSimulationStep@@3MA]
    jbe short water_done
water_loop:
    lea ecx, [esi+09ch]
    call ?LengthSquared@Vector3@@QAEMXZ
    fcomp dword ptr [?g_waterMotionThreshold@@3MB]
    fnstsw ax
    test ah, 041h
    jnz short water_next
    mov ecx, esi
    call ?ApplyWaterInteraction@GameBox@@QAEXXZ
water_next:
    add esi, 0fch
    cmp esi, dword ptr [?g_gameBoxesEnd@@3PAUGameBox@@A]
    jb short water_loop
water_done:
    pop esi
    ret
?ApplyWaterInteractionToMovingBoxes@@YAXXZ ENDP

END
