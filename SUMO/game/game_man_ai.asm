.686
.model flat
option casemap:none

EXTERN __real@3e800000:DWORD
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?CalculateCenterOfMassVelocity@GameMan@@QAE?AUVector3@@XZ:PROC
EXTERN ?Cross@Vector3@@QAE?AU1@AAU1@@Z:PROC
EXTERN ?LengthSquared@Vector3@@QAEMXZ:PROC
EXTERN ?Normalize@Vector3@@QAEMXZ:PROC
EXTERN ?SetGameManAudioState@@YAXPAUGameMan@@H@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC

EXTERN ?g_gameAiForwardDistanceSquaredLimit@@3MB:DWORD
EXTERN ?g_gameAiLateralRecoveryThreshold@@3MB:DWORD
EXTERN ?g_gameAiMotionSquaredLimit@@3MB:DWORD
EXTERN ?g_gameAiOpponentMotionSquaredLimit@@3MB:DWORD
EXTERN ?g_gameAiPushDistanceThreshold@@3MB:DWORD
EXTERN ?g_gameAiStabilitySquaredLimit@@3MB:DWORD
EXTERN ?g_gameAiStateScale@@3MB:DWORD
EXTERN ?g_gameAiVelocityProjectionScale@@3MB:DWORD
EXTERN ?g_gameMenuAlternateLayout@@3HA:DWORD
EXTERN ?g_gameNegativeHalf@@3MB:DWORD
EXTERN ?g_levelLoadState@@3PAHA:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_vectorZero@@3MB:DWORD

.code

; FUNCTION: SUMO 0x0040ff2a
; FUNCTION: EDITOR 0x0040ff4c
PUBLIC ?ChooseAiInput@GameMan@@QAEIPAU1@@Z
?ChooseAiInput@GameMan@@QAEIPAU1@@Z PROC
    push ebp
    mov ebp, esp
    sub esp, 060h
    cmp DWORD PTR [?g_levelLoadState@@3PAHA+010h], 0bh
    push ebx
    mov ebx, ecx
    jne aiMain
    mov ecx, DWORD PTR [ebx]
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    cmp DWORD PTR [ecx+0d4h], eax
    jne aiReturnZero
    cmp eax, 0ah
    jle aiReturnZero
    cmp DWORD PTR [ebx+0a4h], 0
    jne aiReturnZero
    cmp DWORD PTR [ebx+140h], 0
    jne aiReturnZero
    push 1
    push ebx
    call ?SetGameManAudioState@@YAXPAUGameMan@@H@Z
    pop ecx
    pop ecx

aiReturnZero:
    xor eax, eax
    jmp aiReturnEbx

aiMain:
    push esi
    push edi
    lea eax, [ebp-048h]
    push eax
    mov ecx, ebx
    call ?CalculateCenterOfMassVelocity@GameMan@@QAE?AUVector3@@XZ
    mov ecx, DWORD PTR [ebp+8]
    lea eax, [ebp-054h]
    push eax
    call ?CalculateCenterOfMassVelocity@GameMan@@QAE?AUVector3@@XZ
    fld1
    mov eax, DWORD PTR [ebx]
    fstp DWORD PTR [ebp-03ch]
    and DWORD PTR [ebp-8], 0
    fldz
    fstp DWORD PTR [ebp-038h]
    lea esi, [ebp-03ch]
    fldz
    lea edi, [ebp-030h]
    add eax, 060h
    fstp DWORD PTR [ebp-034h]
    push eax
    lea eax, [ebp-03ch]
    movsd
    movsd
    push eax
    lea ecx, [ebp-030h]
    movsd
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    lea ecx, [ebp-03ch]
    fldz
    fstp DWORD PTR [ebp-038h]
    call ?Normalize@Vector3@@QAEMXZ
    fstp st(0)
    fldz
    lea esi, [ebp-030h]
    fstp DWORD PTR [ebp-030h]
    lea edi, [ebp-060h]
    fld1
    lea eax, [ebp-060h]
    push eax
    fstp DWORD PTR [ebp-02ch]
    lea eax, [ebp-024h]
    fldz
    push eax
    lea ecx, [ebp-03ch]
    fstp DWORD PTR [ebp-028h]
    movsd
    movsd
    movsd
    call ?Cross@Vector3@@QAE?AU1@AAU1@@Z
    mov ecx, DWORD PTR [ebx]
    mov edi, DWORD PTR [ebp+8]
    mov eax, 084h
    add ecx, eax
    push ecx
    lea ecx, [ebp-030h]
    push ecx
    mov ecx, DWORD PTR [edi]
    add ecx, eax
    call ??GVector3@@QAE?AU0@AAU0@@Z
    fld DWORD PTR [ebp-020h]
    lea esi, [ebx+124h]
    fmul DWORD PTR [esi+4]
    fld DWORD PTR [ebp-01ch]
    fmul DWORD PTR [esi+8]
    faddp st(1), st
    fld DWORD PTR [ebp-024h]
    fmul DWORD PTR [esi]
    faddp st(1), st
    fstp DWORD PTR [ebp-014h]
    fld DWORD PTR [ebp-034h]
    fmul DWORD PTR [ebp-028h]
    fld DWORD PTR [ebp-03ch]
    fmul DWORD PTR [ebp-030h]
    faddp st(1), st
    fld DWORD PTR [ebp-038h]
    fmul DWORD PTR [?g_vectorZero@@3MB]
    faddp st(1), st
    fstp DWORD PTR [ebp-0ch]
    fld DWORD PTR [ebp-028h]
    fmul DWORD PTR [ebp-01ch]
    cmp DWORD PTR [edi+130h], 0
    fld DWORD PTR [ebp-030h]
    lea ecx, [edi+124h]
    fmul DWORD PTR [ebp-024h]
    setne BYTE PTR [ebp-2]
    faddp st(1), st
    fld DWORD PTR [ebp-020h]
    fmul DWORD PTR [?g_vectorZero@@3MB]
    faddp st(1), st
    fstp DWORD PTR [ebp-010h]
    call ?LengthSquared@Vector3@@QAEMXZ
    fcomp DWORD PTR [?g_gameAiOpponentMotionSquaredLimit@@3MB]
    mov BYTE PTR [ebp-1], 1
    fnstsw ax
    test ah, 041h
    je opponentMotionReady
    mov BYTE PTR [ebp-1], 0

opponentMotionReady:
    lea ecx, [edi+100h]
    call ?LengthSquared@Vector3@@QAEMXZ
    fcomp DWORD PTR [?g_gameAiStabilitySquaredLimit@@3MB]
    mov BYTE PTR [ebp+0bh], 1
    fnstsw ax
    test ah, 5
    jnp opponentStabilityReady
    mov BYTE PTR [ebp+0bh], 0

opponentStabilityReady:
    fld DWORD PTR [ebp-0ch]
    push 4
    fmul DWORD PTR [ebp-0ch]
    pop edi
    fst DWORD PTR [ebp-018h]
    fld DWORD PTR [ebp-028h]
    fmul DWORD PTR [ebp-028h]
    fld DWORD PTR [ebp-030h]
    fmul DWORD PTR [ebp-030h]
    faddp st(1), st
    fmul DWORD PTR [__real@3e800000]
    fld st(1)
    fcompp
    fnstsw ax
    test ah, 5
    jnp discardForwardDistance
    fcomp DWORD PTR [?g_gameAiMotionSquaredLimit@@3MB]
    fnstsw ax
    test ah, 5
    jp choosePushDistance
    jmp short testOwnMotion

discardForwardDistance:
    fstp st(0)

testOwnMotion:
    mov ecx, esi
    call ?LengthSquared@Vector3@@QAEMXZ
    fcomp DWORD PTR [?g_gameAiMotionSquaredLimit@@3MB]
    fnstsw ax
    test ah, 5
    jp choosePushDistance
    fld DWORD PTR [ebp-010h]
    fcomp DWORD PTR [?g_vectorZero@@3MB]
    fnstsw ax
    test ah, 041h
    jne choosePushDistance
    cmp BYTE PTR [ebp-1], 0
    jne choosePushDistance
    cmp DWORD PTR [ebx+714h], 0a0h
    jl short chooseWalkDistance
    fld DWORD PTR [ebp-020h]
    fmul DWORD PTR [esi+4]
    fld DWORD PTR [ebp-01ch]
    fmul DWORD PTR [esi+8]
    faddp st(1), st
    fld DWORD PTR [ebp-024h]
    fmul DWORD PTR [esi]
    faddp st(1), st
    fcomp DWORD PTR [?g_gameAiLateralRecoveryThreshold@@3MB]
    fnstsw ax
    test ah, 041h
    jne choosePushDistance

chooseWalkDistance:
    cmp BYTE PTR [ebp+0bh], 0
    mov DWORD PTR [ebp-0ch], 03fcccccdh
    je short scaleWalkDistance
    mov DWORD PTR [ebp-0ch], 03fb33333h

scaleWalkDistance:
    cmp DWORD PTR [ebx+140h], 3
    jne short chooseWalkDirection
    fild DWORD PTR [ebx+144h]
    fmul DWORD PTR [ebp-0ch]
    fmul DWORD PTR [?g_gameAiStateScale@@3MB]
    fstp DWORD PTR [ebp-0ch]

chooseWalkDirection:
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    sub eax, DWORD PTR [?g_levelLoadState@@3PAHA+018h]
    cmp DWORD PTR [ebx+728h], eax
    jge short chooseAlternateWalk
    lea ecx, [ebx+100h]
    call ?LengthSquared@Vector3@@QAEMXZ
    fld DWORD PTR [ebp-0ch]
    fmul DWORD PTR [ebp-0ch]
    fcompp
    fnstsw ax
    test ah, 041h
    jne short choosePushDistance
    mov DWORD PTR [ebp-8], edi
    jmp short choosePushDistance

chooseAlternateWalk:
    cmp DWORD PTR [ebx+72ch], eax
    jle short choosePushDistance
    mov DWORD PTR [ebp-8], 1

choosePushDistance:
    cmp BYTE PTR [ebp+0bh], 0
    mov DWORD PTR [ebp-0ch], 040a33333h
    je short calculateClosingDistance
    cmp BYTE PTR [ebp-2], 0
    mov DWORD PTR [ebp-0ch], 04099999ah
    je short calculateClosingDistance
    mov DWORD PTR [ebp-0ch], 041000000h

calculateClosingDistance:
    lea eax, [ebp-048h]
    push eax
    lea eax, [ebp-060h]
    push eax
    lea ecx, [ebp-054h]
    call ??GVector3@@QAE?AU0@AAU0@@Z
    mov esi, eax
    lea eax, [ebp-048h]
    push eax
    lea eax, [ebp-03ch]
    push eax
    lea ecx, [ebp-054h]
    call ??GVector3@@QAE?AU0@AAU0@@Z
    fld DWORD PTR [ebp-020h]
    fmul DWORD PTR [esi+4]
    fld DWORD PTR [ebp-01ch]
    fmul DWORD PTR [esi+8]
    faddp st(1), st
    fld DWORD PTR [ebp-024h]
    fmul DWORD PTR [esi]
    faddp st(1), st
    fmul DWORD PTR [?g_gameAiVelocityProjectionScale@@3MB]
    fadd DWORD PTR [ebp-010h]
    fld DWORD PTR [ebp-020h]
    fmul DWORD PTR [eax+4]
    fld DWORD PTR [ebp-01ch]
    fmul DWORD PTR [eax+8]
    faddp st(1), st
    fld DWORD PTR [ebp-024h]
    fmul DWORD PTR [eax]
    faddp st(1), st
    fmul DWORD PTR [?g_gameAiVelocityProjectionScale@@3MB]
    fadd DWORD PTR [ebp-010h]
    fmulp st(1), st
    fld DWORD PTR [ebp-0ch]
    fmul DWORD PTR [ebp-0ch]
    fcompp
    fnstsw ax
    test ah, 041h
    jne short approachMiss
    fld DWORD PTR [ebp-014h]
    fcomp DWORD PTR [?g_gameNegativeHalf@@3MB]
    fnstsw ax
    test ah, 041h
    jne short approachMiss
    fld DWORD PTR [ebp-018h]
    fcomp DWORD PTR [?g_gameAiForwardDistanceSquaredLimit@@3MB]
    fnstsw ax
    test ah, 5
    jp short approachMiss
    mov ecx, DWORD PTR [ebx+714h]
    cmp ecx, 0ah
    jg short chooseStrongPush
    fld DWORD PTR [ebp-0ch]
    fcomp DWORD PTR [?g_gameAiPushDistanceThreshold@@3MB]
    fnstsw ax
    test ah, 041h
    je short chooseStrongPush
    cmp DWORD PTR [ebx+724h], 0
    jne short chooseStrongPush
    or DWORD PTR [ebp-8], 010h
    jmp short finishPushChoice

chooseStrongPush:
    or DWORD PTR [ebp-8], 020h

finishPushChoice:
    cmp BYTE PTR [ebp+0bh], 0
    je short advanceApproach
    and DWORD PTR [ebp-8], 0fffffffbh

advanceApproach:
    add ecx, 8
    mov DWORD PTR [ebx+714h], ecx
    jmp short applyRoundOverrides

approachMiss:
    lea eax, [ebx+714h]
    dec DWORD PTR [eax]
    jns short applyRoundOverrides
    and DWORD PTR [eax], 0

applyRoundOverrides:
    mov ecx, DWORD PTR [?g_levelLoadState@@3PAHA+010h]
    test ecx, ecx
    mov eax, DWORD PTR [?g_screenTintLevel@@3HA]
    jne short alternateLayoutOverride
    cmp eax, DWORD PTR [ebx+718h]
    jg short forceTimedInput
    mov ebx, DWORD PTR [ebx+71ch]
    cmp eax, ebx
    jle short aiReturn
    add ebx, 8
    cmp eax, ebx
    jge short aiReturn

forceTimedInput:
    mov DWORD PTR [ebp-8], 8

alternateLayoutOverride:
    cmp ecx, 2
    jne short aiReturn
    cmp DWORD PTR [?g_gameMenuAlternateLayout@@3HA], 0
    je short periodicWalkOverride
    and DWORD PTR [ebp-8], 0fffffffbh
    jmp short aiReturn

periodicWalkOverride:
    cdq
    mov ecx, 190h
    idiv ecx
    cmp edx, 0c8h
    jle short aiReturn
    or DWORD PTR [ebp-8], edi

aiReturn:
    mov eax, DWORD PTR [ebp-8]
    pop edi
    pop esi

aiReturnEbx:
    pop ebx
    leave
    ret 4
?ChooseAiInput@GameMan@@QAEIPAU1@@Z ENDP

END
