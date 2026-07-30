.586
.model flat
option casemap:none
ASSUME FS:NOTHING

EXTERN __EH_prolog:PROC
EXTERN ___CxxFrameHandler:PROC
EXTERN ??0BigInteger@@QAE@H@Z:PROC
EXTERN ??0BigInteger@@QAE@AAV0@@Z:PROC
EXTERN ??1BigInteger@@QAE@XZ:PROC
EXTERN ??4BigInteger@@QAEAAV0@AAV0@@Z:PROC
EXTERN ??DBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??HBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??KBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??LBigInteger@@QAE?AV0@AAV0@@Z:PROC
EXTERN ??YBigInteger@@QAEXAAV0@@Z:PROC
EXTERN ?Log@BigInteger@@QAEHAAV1@@Z:PROC
EXTERN ?TestBit@U32Vector@@QAEHH@Z:PROC
EXTERN _free:PROC

.data
ALIGN 4
PUBLIC settingsTransformEhDescriptor
settingsTransformEhDescriptor DWORD 019930520h, 0, 0, 0, 0, 0, 0, 0

.code

settingsTransformCleanupBound:
    lea ecx, [ebp+20h]
    jmp ??1BigInteger@@QAE@XZ

settingsTransformCleanupInput:
    lea ecx, [ebp+0ch]
    jmp ??1BigInteger@@QAE@XZ

settingsTransformCleanupModulus:
    lea ecx, [ebp-5ch]
    jmp ??1BigInteger@@QAE@XZ

settingsTransformCleanupResidue:
    lea ecx, [ebp-9ch]
    jmp ??1BigInteger@@QAE@XZ

settingsTransformCleanupCandidate:
    lea ecx, [ebp-4ch]
    jmp ??1BigInteger@@QAE@XZ

settingsTransformCleanupPlace:
    lea ecx, [ebp-8ch]
    jmp ??1BigInteger@@QAE@XZ

settingsTransformCleanupTemporary:
    lea ecx, [ebp-6ch]
    jmp ??1BigInteger@@QAE@XZ

PUBLIC settingsTransformEhHandler
settingsTransformEhHandler:
    mov eax, OFFSET settingsTransformEhDescriptor
    jmp ___CxxFrameHandler

; FUNCTION: SUMO 0x00404008
; FUNCTION: EDITOR 0x00404008
PUBLIC ?TransformEncodedGameSettings@@YA?AVBigInteger@@V1@H0@Z
?TransformEncodedGameSettings@@YA?AVBigInteger@@V1@H0@Z PROC
    mov eax, OFFSET settingsTransformEhHandler
    call __EH_prolog
    sub esp, 90h
    push ebx
    xor ebx, ebx
    push esi
    mov dword ptr [ebp-18h], ebx
    push dword ptr [ebp+1ch]
    lea ecx, [ebp-5ch]
    mov dword ptr [ebp-4], 1
    call ??0BigInteger@@QAE@H@Z
    lea eax, [ebp-5ch]
    push eax
    lea eax, [ebp-9ch]
    push eax
    lea ecx, [ebp+0ch]
    mov byte ptr [ebp-4], 2
    call ??LBigInteger@@QAE?AV0@AAV0@@Z
    push 2
    lea ecx, [ebp-28h]
    mov byte ptr [ebp-4], 3
    mov dword ptr [ebp-2ch], 666h
    call ??0BigInteger@@QAE@H@Z
    lea eax, [ebp-28h]
    push eax
    lea ecx, [ebp-5ch]
    mov byte ptr [ebp-4], 4
    call ?Log@BigInteger@@QAEHAAV1@@Z
    mov esi, eax
    inc esi
    cmp dword ptr [ebp-28h], ebx
    mov byte ptr [ebp-4], 3
    jz settingsTransformFirstBaseDestroyed
    push dword ptr [ebp-28h]
    call _free
    pop ecx

settingsTransformFirstBaseDestroyed:
    push edi
    push 10000h
    lea ecx, [ebp-28h]
    call ??0BigInteger@@QAE@H@Z
    lea eax, [ebp-28h]
    push eax
    lea ecx, [ebp+20h]
    mov byte ptr [ebp-4], 5
    call ?Log@BigInteger@@QAEHAAV1@@Z
    mov edi, eax
    inc edi
    cmp dword ptr [ebp-28h], ebx
    mov byte ptr [ebp-4], 3
    jz settingsTransformSecondBaseDestroyed
    push dword ptr [ebp-28h]
    call _free
    pop ecx

settingsTransformSecondBaseDestroyed:
    push ebx
    lea ecx, [ebp-4ch]
    call ??0BigInteger@@QAE@H@Z
    or dword ptr [ebp-14h], 0ffffffffh
    cmp esi, 0ffffffffh
    mov byte ptr [ebp-4], 6
    jle settingsTransformReduceBound

settingsTransformNextBit:
    cmp dword ptr [ebp-14h], 0ffffffffh
    jnz settingsTransformTestResidueBit
    mov byte ptr [ebp-0dh], 1
    jmp settingsTransformBuildPlace

settingsTransformTestResidueBit:
    push dword ptr [ebp-14h]
    lea ecx, [ebp-9ch]
    call ?TestBit@U32Vector@@QAEHH@Z
    test eax, eax
    setnz byte ptr [ebp-0dh]

settingsTransformBuildPlace:
    push 1
    lea ecx, [ebp-8ch]
    call ??0BigInteger@@QAE@H@Z
    cmp edi, ebx
    mov byte ptr [ebp-4], 7
    jle settingsTransformDestroyPlace
    mov dword ptr [ebp-18h], edi

settingsTransformNextWord:
    mov eax, dword ptr [ebp-2ch]
    imul eax, 343fdh
    add eax, 269ec3h
    mov dword ptr [ebp-2ch], eax
    sar eax, 10h
    and eax, 7fffh
    cmp byte ptr [ebp-0dh], bl
    jz settingsTransformAdvanceWord
    push eax
    lea ecx, [ebp-6ch]
    call ??0BigInteger@@QAE@H@Z
    push eax
    lea eax, [ebp-7ch]
    push eax
    lea ecx, [ebp-8ch]
    mov byte ptr [ebp-4], 8
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-4ch]
    mov byte ptr [ebp-4], 9
    call ??YBigInteger@@QAEXAAV0@@Z
    cmp dword ptr [ebp-7ch], ebx
    jz settingsTransformRandomProductDestroyed
    push dword ptr [ebp-7ch]
    call _free
    pop ecx
    mov dword ptr [ebp-7ch], ebx

settingsTransformRandomProductDestroyed:
    cmp dword ptr [ebp-6ch], ebx
    mov byte ptr [ebp-4], 7
    jz settingsTransformAdvancePlace
    push dword ptr [ebp-6ch]
    call _free
    pop ecx
    mov dword ptr [ebp-6ch], ebx

settingsTransformAdvancePlace:
    push 10000h
    lea ecx, [ebp-28h]
    call ??0BigInteger@@QAE@H@Z
    lea eax, [ebp-28h]
    push eax
    lea eax, [ebp-3ch]
    push eax
    lea ecx, [ebp-8ch]
    mov byte ptr [ebp-4], 0ah
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-8ch]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-3ch], ebx
    jz settingsTransformPlaceProductDestroyed
    push dword ptr [ebp-3ch]
    call _free
    pop ecx
    mov dword ptr [ebp-3ch], ebx

settingsTransformPlaceProductDestroyed:
    cmp dword ptr [ebp-28h], ebx
    mov byte ptr [ebp-4], 7
    jz settingsTransformAdvanceWord
    push dword ptr [ebp-28h]
    call _free
    pop ecx
    mov dword ptr [ebp-28h], ebx

settingsTransformAdvanceWord:
    dec dword ptr [ebp-18h]
    jnz settingsTransformNextWord

settingsTransformDestroyPlace:
    cmp dword ptr [ebp-8ch], ebx
    mov byte ptr [ebp-4], 6
    jz settingsTransformAdvanceBit
    push dword ptr [ebp-8ch]
    call _free
    pop ecx
    mov dword ptr [ebp-8ch], ebx

settingsTransformAdvanceBit:
    inc dword ptr [ebp-14h]
    cmp dword ptr [ebp-14h], esi
    jl settingsTransformNextBit

settingsTransformReduceBound:
    lea eax, [ebp+20h]
    push eax
    lea eax, [ebp-3ch]
    push eax
    lea ecx, [ebp-4ch]
    call ??LBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-4ch]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-3ch], ebx
    pop edi
    jz settingsTransformSnapResidue
    push dword ptr [ebp-3ch]
    call _free
    pop ecx

settingsTransformSnapResidue:
    lea eax, [ebp-5ch]
    push eax
    lea eax, [ebp-7ch]
    push eax
    lea ecx, [ebp-4ch]
    call ??KBigInteger@@QAE?AV0@AAV0@@Z
    lea ecx, [ebp-5ch]
    push ecx
    lea ecx, [ebp-6ch]
    push ecx
    mov ecx, eax
    mov byte ptr [ebp-4], 0bh
    call ??DBigInteger@@QAE?AV0@AAV0@@Z
    lea ecx, [ebp-9ch]
    push ecx
    lea ecx, [ebp-3ch]
    push ecx
    mov ecx, eax
    mov byte ptr [ebp-4], 0ch
    call ??HBigInteger@@QAE?AV0@AAV0@@Z
    push eax
    lea ecx, [ebp-4ch]
    call ??4BigInteger@@QAEAAV0@AAV0@@Z
    cmp dword ptr [ebp-3ch], ebx
    jz settingsTransformSumDestroyed
    push dword ptr [ebp-3ch]
    call _free
    pop ecx
    mov dword ptr [ebp-3ch], ebx

settingsTransformSumDestroyed:
    cmp dword ptr [ebp-6ch], ebx
    jz settingsTransformProductDestroyed
    push dword ptr [ebp-6ch]
    call _free
    pop ecx
    mov dword ptr [ebp-6ch], ebx

settingsTransformProductDestroyed:
    cmp dword ptr [ebp-7ch], ebx
    mov byte ptr [ebp-4], 6
    jz settingsTransformCopyReturn
    push dword ptr [ebp-7ch]
    call _free
    pop ecx

settingsTransformCopyReturn:
    mov ecx, dword ptr [ebp+8]
    lea eax, [ebp-4ch]
    push eax
    call ??0BigInteger@@QAE@AAV0@@Z
    cmp dword ptr [ebp-4ch], ebx
    jz settingsTransformDestroyResidue
    push dword ptr [ebp-4ch]
    call _free
    pop ecx
    mov dword ptr [ebp-4ch], ebx

settingsTransformDestroyResidue:
    cmp dword ptr [ebp-9ch], ebx
    jz settingsTransformDestroyModulus
    push dword ptr [ebp-9ch]
    call _free
    pop ecx
    mov dword ptr [ebp-9ch], ebx

settingsTransformDestroyModulus:
    cmp dword ptr [ebp-5ch], ebx
    jz settingsTransformDestroyInput
    push dword ptr [ebp-5ch]
    call _free
    pop ecx
    mov dword ptr [ebp-5ch], ebx

settingsTransformDestroyInput:
    cmp dword ptr [ebp+0ch], ebx
    jz settingsTransformDestroyBound
    push dword ptr [ebp+0ch]
    call _free
    pop ecx
    mov dword ptr [ebp+0ch], ebx

settingsTransformDestroyBound:
    cmp dword ptr [ebp+20h], ebx
    pop esi
    pop ebx
    jz settingsTransformReturn
    push dword ptr [ebp+20h]
    call _free
    pop ecx

settingsTransformReturn:
    mov ecx, dword ptr [ebp-0ch]
    mov eax, dword ptr [ebp+8]
    mov dword ptr fs:[0], ecx
    leave
    ret
?TransformEncodedGameSettings@@YA?AVBigInteger@@V1@H0@Z ENDP

END
