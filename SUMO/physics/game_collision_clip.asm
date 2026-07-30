.386
.model flat
option casemap:none

EXTERN __alloca_probe:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ?UpdateFacePlane@GameBox@@QAEXAAUGameBoxFace@@@Z:PROC

.code

; FUNCTION: SUMO 0x004092d6
; FUNCTION: EDITOR 0x004092f8
PUBLIC ?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z
?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z PROC
    push ebp
    mov ebp, esp
    mov eax, 305Ch
    call __alloca_probe
    push ebx
    push esi
    push edi
    mov edi, ecx
    mov ecx, [ebp+8]
    mov esi, [ecx]
    mov eax, [ecx+4]
    sub eax, esi
    and eax, 0FFFFFFF0h
    cmp eax, 1000h
    mov [ebp-0Ch], edi
    jg clipGeometryOversize
    mov eax, [ecx+14h]
    sub eax, [ecx+10h]
    push 24h
    cdq
    pop ebx
    idiv ebx
    cmp eax, 100h
    jg clipGeometryOversize
    xor dl, dl
    cmp esi, [ecx+4]
    jae clipGeometryEmpty

    mov ebx, [ebp+0Ch]
clipGeometryClassifyPoint:
    fld DWORD PTR [esi+8]
    mov BYTE PTR [ebp+0Fh], 1
    fmul DWORD PTR [ebx+8]
    fld DWORD PTR [esi+4]
    fmul DWORD PTR [ebx+4]
    faddp st(1), st
    fld DWORD PTR [esi]
    fmul DWORD PTR [ebx]
    faddp st(1), st
    fcomp DWORD PTR [ebp+10h]
    fnstsw ax
    test ah, 41h
    je short clipGeometryClassified
    mov BYTE PTR [ebp+0Fh], 0
clipGeometryClassified:
    mov al, BYTE PTR [ebp+0Fh]
    or WORD PTR [esi+0Eh], 0FFFFh
    mov [esi+0Ch], al
    add esi, 10h
    or dl, al
    cmp esi, [ecx+4]
    jb short clipGeometryClassifyPoint
    test dl, dl
    je clipGeometryEmpty

    mov eax, [edi]
    mov esi, [edi+8]
    and DWORD PTR [ebp-8], 0
    test esi, esi
    mov edx, [edi+10h]
    mov [ebp-4], eax
    lea eax, [ebp-305Ch]
    mov [ebp-30h], eax
    mov [ebp+0Ch], edx
    mov [ebp-18h], esi
    je clipGeometryReturn
    mov edx, [ecx+10h]
    cmp edx, [ecx+14h]
    mov [ebp-14h], edx
    jae clipGeometryNoCap

clipGeometryFaceLoop:
    mov ecx, [edx+10h]
    mov edi, [edx+1Ch]
    and DWORD PTR [ebp-38h], 0
    and DWORD PTR [ebp-34h], 0
    lea edi, [ecx+edi*8-8]
    mov [ebp-20h], edi
    mov edi, [ebp+0Ch]
    mov [edi+10h], esi
    xor edi, edi
    cmp [edx+1Ch], edi
    mov [ebp-24h], ecx
    mov [ebp-10h], edi
    mov [ebp-2Ch], edi
    jle clipGeometryNextFaceKnown

clipGeometryReferenceLoop:
    mov edx, [ecx]
    mov edi, [ebp-20h]
    mov edi, [edi]
    mov dl, [edx+0Ch]
    xor dl, [edi+0Ch]
    je clipGeometryCopyKeptPoint
    mov edi, [ecx+4]
    mov edx, [ebp-20h]
    mov edx, [edx+4]
    shl edi, 10h
    add edi, edx
    mov [ebp-28h], edi
    lea edi, [ebp-305Ch]
    cmp edi, eax
    mov [ebp-1Ch], edi
    jae short clipGeometryEdgeSearchDone
clipGeometryEdgeSearch:
    mov ecx, [ebp-28h]
    cmp ecx, [edi]
    je short clipGeometryEdgeFound
    add edi, 0Ch
    cmp edi, eax
    mov [ebp-1Ch], edi
    jb short clipGeometryEdgeSearch
clipGeometryEdgeFound:
    mov ecx, [ebp-24h]
clipGeometryEdgeSearchDone:
    cmp edi, eax
    jne clipGeometryEdgeReady
    shl edx, 10h
    add edx, [ecx+4]
    and DWORD PTR [eax+8], 0
    mov [eax], edx
    mov edx, [ebp-8]
    mov [eax+4], edx
    add eax, 0Ch
    mov [ebp-30h], eax
    mov eax, [ebp-20h]
    mov esi, [eax]
    fld DWORD PTR [esi+8]
    mov eax, [ecx]
    fmul DWORD PTR [ebx+8]
    lea ecx, [ebp-28h]
    fld DWORD PTR [esi+4]
    push ecx
    fmul DWORD PTR [ebx+4]
    lea ecx, [ebp-44h]
    push ecx
    push eax
    faddp st(1), st
    mov ecx, esi
    fld DWORD PTR [esi]
    fmul DWORD PTR [ebx]
    faddp st(1), st
    fsub DWORD PTR [ebp+10h]
    fld DWORD PTR [esi+8]
    fmul DWORD PTR [ebx+8]
    fld DWORD PTR [esi+4]
    fmul DWORD PTR [ebx+4]
    faddp st(1), st
    fld DWORD PTR [ebx]
    fmul DWORD PTR [esi]
    faddp st(1), st
    fld DWORD PTR [eax+8]
    fmul DWORD PTR [ebx+8]
    fld DWORD PTR [eax+4]
    fmul DWORD PTR [ebx+4]
    faddp st(1), st
    fld DWORD PTR [ebx]
    fmul DWORD PTR [eax]
    lea eax, [ebp-5Ch]
    push eax
    faddp st(1), st
    fsubp st(1), st
    fdivp st(1), st
    fstp DWORD PTR [ebp-28h]
    call ??GVector3@@QAE?AU0@AAU0@@Z
    mov ecx, eax
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    push eax
    lea eax, [ebp-50h]
    push eax
    mov ecx, esi
    call ??GVector3@@QAE?AU0@AAU0@@Z
    mov edi, [ebp-4]
    mov ecx, [ebp-24h]
    mov esi, eax
    mov eax, [ebp-4]
    add DWORD PTR [ebp-4], 10h
    inc DWORD PTR [ebp-8]
    movsd
    movsd
    movsd
    mov esi, [ebp-18h]
    mov edi, [ebp-1Ch]
    mov BYTE PTR [eax+0Dh], 1
    mov eax, [ebp-30h]

clipGeometryEdgeReady:
    mov edx, [ecx]
    cmp BYTE PTR [edx+0Ch], 0
    je short clipGeometryEdgeDiscarded
    mov [ebp-38h], edi
    jmp short clipGeometryEmitIntersection
clipGeometryEdgeDiscarded:
    mov [ebp-34h], edi
clipGeometryEmitIntersection:
    mov edx, [edi+4]
    mov edi, [ebp-0Ch]
    mov [esi+4], edx
    shl edx, 4
    add edx, [edi]
    mov [esi], edx
    add esi, 8
    inc DWORD PTR [ebp-10h]
    mov [ebp-18h], esi

clipGeometryCopyKeptPoint:
    mov edx, [ecx]
    cmp BYTE PTR [edx+0Ch], 0
    je short clipGeometryNextReference
    cmp WORD PTR [edx+0Eh], 0FFFFh
    jne short clipGeometryPointIndexed
    mov edi, [ebp-4]
    add DWORD PTR [ebp-4], 10h
    mov esi, edx
    movsd
    movsd
    movsd
    movsd
    mov si, WORD PTR [ebp-8]
    mov edx, [ecx]
    inc DWORD PTR [ebp-8]
    mov [edx+0Eh], si
    mov esi, [ebp-18h]
clipGeometryPointIndexed:
    mov edx, [ecx]
    movsx edx, WORD PTR [edx+0Eh]
    mov edi, [ebp-0Ch]
    mov [esi+4], edx
    shl edx, 4
    add edx, [edi]
    mov [esi], edx
    add esi, 8
    inc DWORD PTR [ebp-10h]
    mov [ebp-18h], esi

clipGeometryNextReference:
    mov edx, [ebp-14h]
    mov [ebp-20h], ecx
    add ecx, 8
    inc DWORD PTR [ebp-2Ch]
    mov edi, [ebp-2Ch]
    cmp edi, [edx+1Ch]
    mov [ebp-24h], ecx
    jl clipGeometryReferenceLoop

clipGeometryFinishFace:
    mov ecx, [ebp-10h]
    cmp ecx, 3
    jl short clipGeometryNextFace
    mov edi, [ebp+0Ch]
    mov [edi+1Ch], ecx
    mov ecx, edx
    mov edx, [ecx+18h]
    mov [edi+18h], edx
    mov esi, ecx
    movsd
    movsd
    movsd
    mov edx, [ecx+0Ch]
    mov esi, [ebp+0Ch]
    mov [esi+0Ch], edx
    mov ecx, [ecx+14h]
    mov [esi+14h], ecx
    mov ecx, [ebp-38h]
    test ecx, ecx
    je short clipGeometryFaceDone
    mov eax, [ebp-34h]
    mov [ecx+8], eax
    mov ecx, [ebp-0Ch]
    push esi
    call ?UpdateFacePlane@GameBox@@QAEXAAUGameBoxFace@@@Z
    mov eax, [ebp-30h]
clipGeometryFaceDone:
    add esi, 24h
    mov [ebp+0Ch], esi
    mov esi, [ebp-18h]

clipGeometryNextFace:
    mov edx, [ebp-14h]
clipGeometryNextFaceKnown:
    mov ecx, [ebp+8]
    mov edi, [ebp-0Ch]
    add edx, 24h
    cmp edx, [ecx+14h]
    mov [ebp-14h], edx
    jb clipGeometryFaceLoop

    lea ecx, [ebp-305Ch]
    cmp eax, ecx
    je clipGeometryNoCap
    mov ecx, [ebp+0Ch]
    and DWORD PTR [ebp+10h], 0
    lea ebx, [ebp-305Ch]
    mov edx, ebx
    cmp edx, eax
    mov [ecx+10h], esi
    jae short clipGeometryCapReady

clipGeometryCapLinkLoop:
    cmp DWORD PTR [ebx+4], 0FFFFFFFFh
    je short clipGeometryNextCapLink
    mov edx, ebx
clipGeometryCapChainLoop:
    mov ecx, [edx+4]
    mov [esi+4], ecx
    shl ecx, 4
    add ecx, [edi]
    mov [esi], ecx
    or DWORD PTR [edx+4], 0FFFFFFFFh
    mov edx, [edx+8]
    add esi, 8
    inc DWORD PTR [ebp+10h]
    cmp edx, ebx
    je short clipGeometryCapChainClosed
    test edx, edx
    jne short clipGeometryCapChainLoop
clipGeometryCapChainClosed:
    test edx, edx
    je clipGeometryEmpty
    mov ecx, [ebp+0Ch]
clipGeometryNextCapLink:
    add ebx, 0Ch
    cmp ebx, eax
    jb short clipGeometryCapLinkLoop

clipGeometryCapReady:
    mov eax, [ebp+10h]
    mov [ecx+1Ch], eax
    push ecx
    mov ecx, edi
    call ?UpdateFacePlane@GameBox@@QAEXAAUGameBoxFace@@@Z
    mov eax, [ebp+0Ch]
    mov DWORD PTR [eax+14h], 0BF800000h
    add eax, 24h
    jmp short clipGeometryCommitFaces

clipGeometryEmpty:
    mov eax, [edi+10h]
    mov [edi+14h], eax
    jmp short clipGeometryReturn

clipGeometryNoCap:
    mov eax, [ebp+0Ch]
clipGeometryCommitFaces:
    mov [edi+14h], eax
    mov eax, [ebp-4]
    mov [edi+0Ch], esi
    jmp short clipGeometryCommitPoints

clipGeometryOversize:
    mov eax, [edi+10h]
    mov [edi+14h], eax
    mov eax, [edi]
clipGeometryCommitPoints:
    mov [edi+4], eax

clipGeometryReturn:
    pop edi
    pop esi
    pop ebx
    leave
    ret 0Ch
?ClipGeometry@GameBox@@QAEXAAU1@AAUVector3@@M@Z ENDP

END
