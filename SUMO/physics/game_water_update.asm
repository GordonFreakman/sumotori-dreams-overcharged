.586
.model flat
option casemap:none

EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_waterHeights@@3VFloatVector@@A:BYTE
EXTERN ?g_waterVelocities@@3VFloatVector@@A:BYTE
EXTERN ?g_waterGridWidth@@3HA:DWORD
EXTERN ?g_waterGridHeight@@3HA:DWORD
EXTERN ?g_waterNeighborCoupling@@3MB:DWORD
EXTERN ?g_waterVelocityDamping@@3MB:DWORD
EXTERN ?g_waterCorrectionScale@@3NB:QWORD
EXTERN ?g_waterBaseHeight@@3MA:DWORD
EXTERN ?g_waterHeightCorrection@@3MA:DWORD
EXTERN ??AFloatVector@@QAEAAMI@Z:PROC

.code

; FUNCTION: SUMO 0x004165b9
; FUNCTION: EDITOR 0x004165db
PUBLIC ?UpdateWaterField@@YAXXZ
?UpdateWaterField@@YAXXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 10h
    mov eax, dword ptr [?g_screenTintLevel@@3HA]
    push 3
    cdq
    pop ecx
    idiv ecx
    test edx, edx
    jnz waterDone
    mov eax, dword ptr [?g_waterHeights@@3VFloatVector@@A+4]
    cmp eax, dword ptr [?g_waterHeights@@3VFloatVector@@A]
    jbe waterDone
    mov ecx, dword ptr [?g_waterGridHeight@@3HA]
    and dword ptr [ebp-4], edx
    push ebx
    push esi
    lea eax, [ecx-1]
    push edi
    test eax, eax
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    mov edi, OFFSET ?g_waterHeights@@3VFloatVector@@A
    mov esi, OFFSET ?g_waterVelocities@@3VFloatVector@@A
    jle integrateWater
    lea edx, [eax-1]

waterRow:
    xor ebx, ebx
    test edx, edx
    jle nextWaterRow

waterColumn:
    imul eax, dword ptr [ebp-4]
    add eax, ebx
    push eax
    mov ecx, edi
    call ??AFloatVector@@QAEAAMI@Z
    mov dword ptr [ebp-8], eax
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    imul eax, dword ptr [ebp-4]
    db 08dh, 044h, 018h, 001h
    push eax
    mov ecx, edi
    call ??AFloatVector@@QAEAAMI@Z
    mov ecx, dword ptr [ebp-8]
    fld dword ptr [ecx]
    mov ecx, esi
    fsub dword ptr [eax]
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    imul eax, dword ptr [ebp-4]
    add eax, ebx
    fmul dword ptr [?g_waterNeighborCoupling@@3MB]
    push eax
    fstp dword ptr [ebp-8]
    call ??AFloatVector@@QAEAAMI@Z
    fld dword ptr [eax]
    mov ecx, esi
    fsub dword ptr [ebp-8]
    fstp dword ptr [eax]
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    imul eax, dword ptr [ebp-4]
    db 08dh, 044h, 018h, 001h
    push eax
    call ??AFloatVector@@QAEAAMI@Z
    mov ecx, edi
    fld dword ptr [ebp-8]
    fadd dword ptr [eax]
    fstp dword ptr [eax]
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    imul eax, dword ptr [ebp-4]
    add eax, ebx
    push eax
    call ??AFloatVector@@QAEAAMI@Z
    mov dword ptr [ebp-8], eax
    mov eax, dword ptr [ebp-4]
    inc eax
    imul eax, dword ptr [?g_waterGridWidth@@3HA]
    add eax, ebx
    push eax
    mov ecx, edi
    call ??AFloatVector@@QAEAAMI@Z
    mov ecx, dword ptr [ebp-8]
    fld dword ptr [ecx]
    mov ecx, esi
    fsub dword ptr [eax]
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    imul eax, dword ptr [ebp-4]
    add eax, ebx
    fmul dword ptr [?g_waterNeighborCoupling@@3MB]
    push eax
    fstp dword ptr [ebp-8]
    call ??AFloatVector@@QAEAAMI@Z
    fld dword ptr [eax]
    mov ecx, esi
    fsub dword ptr [ebp-8]
    fstp dword ptr [eax]
    mov eax, dword ptr [ebp-4]
    inc eax
    imul eax, dword ptr [?g_waterGridWidth@@3HA]
    add eax, ebx
    push eax
    call ??AFloatVector@@QAEAAMI@Z
    inc ebx
    fld dword ptr [ebp-8]
    fadd dword ptr [eax]
    fstp dword ptr [eax]
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    lea edx, [eax-1]
    cmp ebx, edx
    jl waterColumn
    mov ecx, dword ptr [?g_waterGridHeight@@3HA]

nextWaterRow:
    inc dword ptr [ebp-4]
    lea ebx, [ecx-1]
    cmp dword ptr [ebp-4], ebx
    jl waterRow

integrateWater:
    and dword ptr [ebp-4], 0
    fldz
    mov edx, eax
    fstp qword ptr [ebp-10h]
    imul edx, ecx
    test edx, edx
    jle correctWaterMean

integrateWaterCell:
    push dword ptr [ebp-4]
    mov ecx, edi
    call ??AFloatVector@@QAEAAMI@Z
    fld dword ptr [eax]
    fadd qword ptr [ebp-10h]
    push dword ptr [ebp-4]
    mov ecx, edi
    fstp qword ptr [ebp-10h]
    call ??AFloatVector@@QAEAAMI@Z
    push dword ptr [ebp-4]
    mov ecx, esi
    mov ebx, eax
    call ??AFloatVector@@QAEAAMI@Z
    fld dword ptr [ebx]
    fadd dword ptr [eax]
    push dword ptr [ebp-4]
    mov ecx, esi
    fadd dword ptr [?g_waterHeightCorrection@@3MA]
    fstp dword ptr [ebx]
    call ??AFloatVector@@QAEAAMI@Z
    fld dword ptr [eax]
    inc dword ptr [ebp-4]
    fmul dword ptr [?g_waterVelocityDamping@@3MB]
    fstp dword ptr [eax]
    mov eax, dword ptr [?g_waterGridWidth@@3HA]
    mov ecx, dword ptr [?g_waterGridHeight@@3HA]
    mov edx, eax
    imul edx, ecx
    cmp dword ptr [ebp-4], edx
    jl integrateWaterCell

correctWaterMean:
    fld dword ptr [?g_waterBaseHeight@@3MA]
    imul eax, ecx
    mov dword ptr [ebp-8], eax
    pop edi
    pop esi
    fild dword ptr [ebp-8]
    pop ebx
    fdivr qword ptr [ebp-10h]
    fsubp st(1), st(0)
    fmul qword ptr [?g_waterCorrectionScale@@3NB]
    fstp dword ptr [?g_waterHeightCorrection@@3MA]

waterDone:
    leave
    ret
?UpdateWaterField@@YAXXZ ENDP

END
