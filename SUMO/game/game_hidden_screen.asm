.386
.model flat
option casemap:none

EXTERN ?g_gameProjectileCooldown@@3HA:DWORD
EXTERN ?g_gameMouseX@@3HA:DWORD
EXTERN ?g_gameCameraWorldPosition@@3UVector3@@A:DWORD
EXTERN ?g_gameInverseViewMatrix@@3UMatrix3@@A:DWORD
EXTERN ?g_gameProjectionMinimum@@3MB:DWORD
EXTERN ?g_gameCameraInputOffsetScale@@3MB:DWORD
EXTERN ?g_screenTintLevel@@3HA:DWORD
EXTERN ?g_gameBoxes@@3PAUGameBox@@A:BYTE
EXTERN ?g_gameBoxesEnd@@3PAUGameBox@@A:DWORD

EXTERN ?GetGameMouseRayDirection@@YA?AUVector3@@XZ:PROC
EXTERN ?Scale@Vector3@@QAE?AU1@AAM@Z:PROC
EXTERN ??HVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z:PROC
EXTERN ?LaunchGameBoxProjectile@@YAXUVector3@@0MH@Z:PROC
EXTERN ?DrawGameText@@YAPADMMPADH@Z:PROC
EXTERN ?InitializeGameRuntimeState@@YAHXZ:PROC

EXTERN __real@41f00000:DWORD
EXTERN __real@be4ccccd:DWORD
EXTERN __real@3e4ccccd:DWORD
EXTERN ??_C@_0M@KDNOOHLB@Hidden?5Part?$AA@:BYTE
EXTERN ??_C@_0EN@GNHHLKJI@Controls?3?6Home?1PageUp?5?$DN?5Move?5Cam@:BYTE

.code

; FUNCTION: SUMO 0x004077f6
; FUNCTION: EDITOR 0x00407818
PUBLIC ?UpdateHiddenGameScreen@@YAHXZ
?UpdateHiddenGameScreen@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 28h
    dec dword ptr [?g_gameProjectileCooldown@@3HA]
    cmp dword ptr [?g_gameMouseX@@3HA], -1
    push ebx
    push esi
    push edi
    je mouseComplete

    cmp dword ptr [?g_gameProjectileCooldown@@3HA], 0
    jg clearMouse
    lea eax, [ebp - 28h]
    push eax
    mov dword ptr [?g_gameProjectileCooldown@@3HA], 3ch
    call ?GetGameMouseRayDirection@@YA?AUVector3@@XZ
    mov esi, eax
    lea edi, [ebp - 10h]
    movsd
    pop ecx
    lea eax, [ebp - 4]
    movsd
    push eax
    lea eax, [ebp - 1ch]
    push eax
    lea ecx, [ebp - 10h]
    movsd
    mov dword ptr [ebp - 4], 42480000h
    call ?Scale@Vector3@@QAE?AU1@AAM@Z
    push eax
    lea eax, [ebp - 28h]
    mov ebx, OFFSET ?g_gameCameraWorldPosition@@3UVector3@@A
    push eax
    mov ecx, ebx
    call ??HVector3@@QAE?AU0@AAU0@@Z

    mov dword ptr [ebp - 10h], 40a00000h
    fldz
    fstp dword ptr [ebp - 0ch]
    mov dword ptr [ebp - 8], 40800000h
    lea esi, [ebp - 10h]
    lea edi, [ebp - 1ch]
    movsd
    movsd
    push OFFSET ?g_gameInverseViewMatrix@@3UMatrix3@@A
    lea eax, [ebp - 10h]
    push eax
    lea ecx, [ebp - 1ch]
    movsd
    call ?Transform@Vector3@@QAE?AU1@AAUMatrix3@@@Z
    push eax
    lea eax, [ebp - 1ch]
    push eax
    mov ecx, ebx
    call ??HVector3@@QAE?AU0@AAU0@@Z

    fld dword ptr [__real@41f00000]
    push 2
    sub esp, 10h
    fstp dword ptr [esp + 0ch]
    mov edi, esp
    lea esi, [ebp - 28h]
    movsd
    movsd
    movsd
    sub esp, 0ch
    lea esi, [ebp - 1ch]
    mov edi, esp
    movsd
    movsd
    movsd
    call ?LaunchGameBoxProjectile@@YAXUVector3@@0MH@Z
    add esp, 20h

clearMouse:
    or dword ptr [?g_gameMouseX@@3HA], -1

mouseComplete:
    fld dword ptr [?g_gameProjectionMinimum@@3MB]
    push 0b08f8fffh
    push OFFSET ??_C@_0M@KDNOOHLB@Hidden?5Part?$AA@
    push ecx
    push ecx
    fstp dword ptr [esp + 4]
    fld dword ptr [__real@be4ccccd]
    fstp dword ptr [esp]
    call ?DrawGameText@@YAPADMMPADH@Z
    add esp, 10h

    cmp dword ptr [?g_screenTintLevel@@3HA], 3e8h
    jge short checkBoxLimit
    fld dword ptr [?g_gameCameraInputOffsetScale@@3MB]
    push 0b0ffffffh
    push OFFSET ??_C@_0EN@GNHHLKJI@Controls?3?6Home?1PageUp?5?$DN?5Move?5Cam@
    push ecx
    push ecx
    fstp dword ptr [esp + 4]
    fld dword ptr [__real@3e4ccccd]
    fstp dword ptr [esp]
    call ?DrawGameText@@YAPADMMPADH@Z
    add esp, 10h

checkBoxLimit:
    cmp dword ptr [?g_gameBoxesEnd@@3PAUGameBox@@A], OFFSET ?g_gameBoxes@@3PAUGameBox@@A + 189c0h
    jbe short updateComplete
    call ?InitializeGameRuntimeState@@YAHXZ

updateComplete:
    pop edi
    pop esi
    pop ebx
    leave
    ret
?UpdateHiddenGameScreen@@YAHXZ ENDP

END
