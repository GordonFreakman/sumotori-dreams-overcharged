.686
.model flat
option casemap:none

EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD
EXTERN ?g_gameContactObjects@@3PAEA:BYTE
EXTERN ?g_gameContactObjectsEnd@@3PAEA:DWORD
EXTERN ?g_gameContactLinks@@3PAEA:BYTE
EXTERN ?g_gameContactLinksEnd@@3PAEA:DWORD

.code

; FUNCTION: SUMO 0x00408c14
; FUNCTION: EDITOR 0x00408c36
PUBLIC ?ResetGameContactLists@@YAXXZ
?ResetGameContactLists@@YAXXZ PROC
    mov ecx, dword ptr [?g_gameBoxesEnd@@3PAUGameBox@@A]
    mov eax, OFFSET ?g_gameBoxes@@3PAUGameBox@@A
    cmp ecx, eax
    jbe boxesReady
clearBoxLists:
    and dword ptr [eax + 0e8h], 0
    add eax, 0fch
    cmp eax, ecx
    jb clearBoxLists
boxesReady:
    cmp dword ptr [?g_gameContactObjectsEnd@@3PAEA], OFFSET ?g_gameContactObjects@@3PAEA
    mov dword ptr [?g_gameContactLinksEnd@@3PAEA], OFFSET ?g_gameContactLinks@@3PAEA
    jbe contactResetDone
    push ebx
    push esi
    push edi
    mov eax, OFFSET ?g_gameContactObjects@@3PAEA + 068h
    mov edi, 0e8h
clearContactOwner:
    and dword ptr [eax + 088h], 0
    fldz
    fstp dword ptr [eax - 00ch]
    mov edx, dword ptr [?g_gameContactLinksEnd@@3PAEA]
    fldz
    fstp dword ptr [eax + 080h]
    fldz
    fstp dword ptr [eax + 084h]
    fldz
    fstp dword ptr [eax + 004h]
    fldz
    fstp dword ptr [eax]
    fldz
    fstp dword ptr [eax - 004h]
    fldz
    fstp dword ptr [eax + 064h]
    fldz
    fstp dword ptr [eax + 060h]
    fldz
    fstp dword ptr [eax + 05ch]
    fldz
    fstp dword ptr [eax + 058h]
    fldz
    fstp dword ptr [eax + 054h]
    fldz
    fstp dword ptr [eax + 050h]
    mov ecx, dword ptr [eax - 064h]
    mov dword ptr [edx + 008h], ecx
    mov edx, dword ptr [?g_gameContactLinksEnd@@3PAEA]
    lea ecx, [eax - 068h]
    mov dword ptr [edx + 004h], ecx
    mov edx, dword ptr [ecx]
    mov esi, dword ptr [?g_gameContactLinksEnd@@3PAEA]
    add edx, edi
    mov ebx, dword ptr [edx]
    mov dword ptr [esi], ebx
    mov dword ptr [edx], esi
    add dword ptr [?g_gameContactLinksEnd@@3PAEA], 00ch
    mov edx, dword ptr [ecx]
    mov esi, dword ptr [?g_gameContactLinksEnd@@3PAEA]
    mov dword ptr [esi + 008h], edx
    mov edx, dword ptr [?g_gameContactLinksEnd@@3PAEA]
    mov dword ptr [edx + 004h], ecx
    mov ecx, dword ptr [eax - 064h]
    mov edx, dword ptr [?g_gameContactLinksEnd@@3PAEA]
    add ecx, edi
    mov esi, dword ptr [ecx]
    mov dword ptr [edx], esi
    mov dword ptr [ecx], edx
    add dword ptr [?g_gameContactLinksEnd@@3PAEA], 00ch
    add eax, 0f4h
    lea ecx, [eax - 068h]
    cmp ecx, dword ptr [?g_gameContactObjectsEnd@@3PAEA]
    jb clearContactOwner
    pop edi
    pop esi
    pop ebx
contactResetDone:
    ret
?ResetGameContactLists@@YAXXZ ENDP

END
