.686
.model flat
option casemap:none

EXTERN __ftol2:PROC
EXTERN _sqrt:PROC
EXTERN __real@40400000:DWORD
EXTERN ??AFloatVector@@QAEAAMI@Z:PROC
EXTERN ??YVector3@@QAEXAAU0@@Z:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC

EXTERN ?g_boxWaterAngularDamping@@3MB:DWORD
EXTERN ?g_boxWaterBuoyancyScale@@3MB:DWORD
EXTERN ?g_boxWaterDiagonalScale@@3MB:DWORD
EXTERN ?g_boxWaterLinearDamping@@3MB:DWORD
EXTERN ?g_boxWaterSurfaceOffset@@3MB:DWORD
EXTERN ?g_boxWaterVerticalRetention@@3MB:DWORD
EXTERN ?g_boxWaterWaveScale@@3MB:DWORD
EXTERN ?g_gameGravityStep@@3MA:DWORD
EXTERN ?g_gameInverseSimulationStep@@3MA:DWORD
EXTERN ?g_gameOne@@3MB:DWORD
EXTERN ?g_vectorZero@@3MB:DWORD
EXTERN ?g_waterBaseHeight@@3MA:DWORD
EXTERN ?g_waterFieldActive@@3EA:BYTE
EXTERN ?g_waterGridHeight@@3HA:DWORD
EXTERN ?g_waterGridWidth@@3HA:DWORD
EXTERN ?g_waterHeights@@3VFloatVector@@A:BYTE
EXTERN ?g_waterVelocities@@3VFloatVector@@A:BYTE

.code

; FUNCTION: SUMO 0x004096b0
; FUNCTION: EDITOR 0x004096d2
PUBLIC ?ApplyWaterInteraction@GameBox@@QAEXXZ
?ApplyWaterInteraction@GameBox@@QAEXXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 044h
    cmp BYTE PTR [?g_waterFieldActive@@3EA], 0
    push ebx
    mov ebx, ecx
    je waterDoneEbx
    fld DWORD PTR [?g_waterBaseHeight@@3MA]
    fadd DWORD PTR [__real@40400000]
    fcomp DWORD PTR [ebx+088h]
    fnstsw ax
    test ah, 041h
    jne waterDoneEbx
    fld DWORD PTR [?g_gameInverseSimulationStep@@3MA]
    push esi
    fmul DWORD PTR [ebx+084h]
    push edi
    call __ftol2
    fld DWORD PTR [?g_gameInverseSimulationStep@@3MA]
    fmul DWORD PTR [ebx+08ch]
    mov edi, eax
    mov DWORD PTR [ebp-010h], edi
    call __ftol2
    mov esi, eax
    mov eax, DWORD PTR [?g_waterGridWidth@@3HA]
    cmp edi, eax
    mov DWORD PTR [ebp-00ch], esi
    jge waterDone
    test edi, edi
    jl waterDone
    cmp esi, DWORD PTR [?g_waterGridHeight@@3HA]
    jge waterDone
    test esi, esi
    jl waterDone
    imul eax, esi
    add eax, edi
    push eax
    mov ecx, OFFSET ?g_waterHeights@@3VFloatVector@@A
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [eax]
    fsub DWORD PTR [ebx+088h]
    fadd DWORD PTR [?g_boxWaterSurfaceOffset@@3MB]
    fst DWORD PTR [ebp-4]
    fcomp DWORD PTR [?g_gameOne@@3MB]
    fnstsw ax
    test ah, 041h
    jne depthClamped
    fld1
    fstp DWORD PTR [ebp-4]

depthClamped:
    fld DWORD PTR [ebp-4]
    fcomp DWORD PTR [?g_vectorZero@@3MB]
    fnstsw ax
    test ah, 041h
    jne waterDone
    fld DWORD PTR [ebp-4]
    fcomp DWORD PTR [?g_gameOne@@3MB]
    fnstsw ax
    test ah, 005h
    jp buoyancy
    fld DWORD PTR [ebx+038h]
    push ecx
    push ecx
    fstp QWORD PTR [esp]
    call _sqrt
    lea eax, [esi+1]
    mov DWORD PTR [ebp-018h], eax
    cdq
    idiv DWORD PTR [?g_waterGridHeight@@3HA]
    pop ecx
    pop ecx
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    lea esi, [edi+1]
    mov DWORD PTR [ebp-020h], esi
    fmul DWORD PTR [ebp-4]
    fmul DWORD PTR [?g_boxWaterWaveScale@@3MB]
    fst DWORD PTR [ebp-8]
    fmul DWORD PTR [?g_boxWaterDiagonalScale@@3MB]
    fstp DWORD PTR [ebp-014h]
    mov eax, edx
    imul eax, ecx
    mov DWORD PTR [ebp-01ch], eax
    mov eax, esi
    cdq
    idiv ecx
    mov eax, DWORD PTR [ebp-01ch]
    mov esi, OFFSET ?g_waterVelocities@@3VFloatVector@@A
    mov ecx, esi
    add eax, edx
    push eax
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-8]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    lea eax, [edi+ecx-1]
    cdq
    idiv ecx
    mov eax, DWORD PTR [ebp-018h]
    mov edi, edx
    cdq
    idiv DWORD PTR [?g_waterGridHeight@@3HA]
    imul edx, ecx
    add edi, edx
    push edi
    mov ecx, esi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-8]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov ecx, DWORD PTR [?g_waterGridHeight@@3HA]
    mov eax, DWORD PTR [ebp-00ch]
    lea eax, [eax+ecx-1]
    cdq
    idiv ecx
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [ebp-020h]
    mov edi, edx
    cdq
    imul edi, ecx
    idiv ecx
    mov ecx, esi
    add edi, edx
    push edi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-8]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov ecx, DWORD PTR [?g_waterGridHeight@@3HA]
    mov eax, DWORD PTR [ebp-00ch]
    lea eax, [eax+ecx-1]
    cdq
    idiv ecx
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [ebp-010h]
    mov edi, edx
    imul edi, ecx
    lea eax, [eax+ecx-1]
    cdq
    idiv ecx
    mov ecx, esi
    add edi, edx
    push edi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-8]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov eax, DWORD PTR [ebp-00ch]
    cdq
    idiv DWORD PTR [?g_waterGridHeight@@3HA]
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [ebp-010h]
    mov edi, edx
    imul edi, ecx
    inc eax
    cdq
    idiv ecx
    mov ecx, esi
    add edi, edx
    push edi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-014h]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [ebp-010h]
    lea eax, [eax+ecx-1]
    cdq
    idiv ecx
    mov eax, DWORD PTR [ebp-00ch]
    mov edi, edx
    cdq
    idiv DWORD PTR [?g_waterGridHeight@@3HA]
    imul edx, ecx
    add edi, edx
    push edi
    mov ecx, esi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-014h]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov ecx, DWORD PTR [?g_waterGridHeight@@3HA]
    mov eax, DWORD PTR [ebp-00ch]
    lea eax, [eax+ecx-1]
    cdq
    idiv ecx
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [ebp-010h]
    mov edi, edx
    cdq
    imul edi, ecx
    idiv ecx
    mov ecx, esi
    add edi, edx
    push edi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-014h]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    mov eax, DWORD PTR [ebp-018h]
    cdq
    idiv DWORD PTR [?g_waterGridHeight@@3HA]
    mov ecx, DWORD PTR [?g_waterGridWidth@@3HA]
    mov eax, DWORD PTR [ebp-010h]
    mov edi, edx
    cdq
    imul edi, ecx
    idiv ecx
    mov ecx, esi
    add edi, edx
    push edi
    call ??AFloatVector@@QAEAAMI@Z
    fld DWORD PTR [ebp-014h]
    fmul DWORD PTR [ebx+0a0h]
    fadd DWORD PTR [eax]
    fstp DWORD PTR [eax]
    fld DWORD PTR [ebx+0a0h]
    fmul DWORD PTR [?g_boxWaterVerticalRetention@@3MB]
    fstp DWORD PTR [ebx+0a0h]

buoyancy:
    fld DWORD PTR [?g_gameGravityStep@@3MA]
    lea eax, [ebx+0a0h]
    fmul DWORD PTR [ebp-4]
    mov DWORD PTR [ebp-02ch], 03c23d70ah
    lea esi, [ebp-02ch]
    lea edi, [ebp-038h]
    fmul DWORD PTR [?g_boxWaterBuoyancyScale@@3MB]
    lea ecx, [ebp-038h]
    fsubr DWORD PTR [eax]
    fstp DWORD PTR [eax]
    lea eax, [ebx+09ch]
    fld DWORD PTR [?g_boxWaterLinearDamping@@3MB]
    fld DWORD PTR [eax]
    fmul st, st(1)
    fstp DWORD PTR [eax]
    fld DWORD PTR [eax+4]
    fmul st, st(1)
    fstp DWORD PTR [eax+4]
    fld DWORD PTR [eax+8]
    fmul st, st(1)
    fstp DWORD PTR [eax+8]
    mov eax, DWORD PTR [?g_gameGravityStep@@3MA]
    fstp st(0)
    fldz
    fstp DWORD PTR [ebp-028h]
    fldz
    fstp DWORD PTR [ebp-024h]
    fldz
    movsd
    movsd
    movsd
    fstp DWORD PTR [ebp-02ch]
    fldz
    mov DWORD PTR [ebp-028h], eax
    fstp DWORD PTR [ebp-024h]
    lea esi, [ebp-02ch]
    lea edi, [ebp-044h]
    movsd
    movsd
    movsd
    lea esi, [ebx+090h]
    add ebx, 060h
    push ebx
    lea eax, [ebp-02ch]
    push eax
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    push eax
    lea eax, [ebp-038h]
    push eax
    lea ecx, [ebp-044h]
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    push eax
    mov ecx, esi
    call ??YVector3@@QAEXAAU0@@Z
    fld DWORD PTR [?g_boxWaterAngularDamping@@3MB]
    fld DWORD PTR [esi]
    fmul st, st(1)
    fstp DWORD PTR [esi]
    fld DWORD PTR [esi+4]
    fmul st, st(1)
    fstp DWORD PTR [esi+4]
    fld DWORD PTR [esi+8]
    fmul st, st(1)
    fstp DWORD PTR [esi+8]
    fstp st(0)

waterDone:
    pop edi
    pop esi

waterDoneEbx:
    pop ebx
    leave
    ret
?ApplyWaterInteraction@GameBox@@QAEXXZ ENDP

END
