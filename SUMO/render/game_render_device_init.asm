.686
.model flat
option casemap:none

EXTERN _Direct3DCreate9:PROC
EXTERN __imp__GetDesktopWindow@0:DWORD
EXTERN __imp__GetWindowDC@4:DWORD
EXTERN __imp__GetDeviceCaps@8:DWORD
EXTERN __imp__ReleaseDC@8:DWORD
EXTERN __imp__ShowWindow@8:DWORD

EXTERN ?g_gameD3D@@3PAUIDirect3D9@@A:DWORD
EXTERN ?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A:DWORD
EXTERN ?g_gameDeviceResource@@3PAXA:DWORD
EXTERN ?g_gameDeviceCaps@@3U_D3DCAPS9@@A:BYTE
EXTERN ?g_gameConfiguredWidth@@3HA:DWORD
EXTERN ?g_gameConfiguredHeight@@3HA:DWORD
EXTERN ?g_gameUseDesktopSize@@3EA:BYTE
EXTERN ?g_gameAspectRatio@@3MA:DWORD
EXTERN ?g_gameWindow@@3PAUHWND__@@A:DWORD

.code

; FUNCTION: SUMO 0x00403c36
; FUNCTION: EDITOR 0x00403c36
PUBLIC ?InitializeGameD3DDevice@@YAHXZ
?InitializeGameD3DDevice@@YAHXZ PROC
    push ebp
    mov ebp, esp
    sub esp, 060h
    push ebx
    push esi
    push edi
    push 020h
    call _Direct3DCreate9
    mov dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A], eax
    call dword ptr [__imp__GetDesktopWindow@0]
    mov ebx, eax
    push ebx
    call dword ptr [__imp__GetWindowDC@4]
    mov edi, eax
    mov eax, dword ptr [?g_gameConfiguredHeight@@3HA]
    imul eax, dword ptr [?g_gameConfiguredWidth@@3HA]
    test eax, eax
    jnz dimensionsReady
    mov esi, dword ptr [__imp__GetDeviceCaps@8]
    push 8
    push edi
    call esi
    push 00ah
    push edi
    mov dword ptr [?g_gameConfiguredWidth@@3HA], eax
    call esi
    mov dword ptr [?g_gameConfiguredHeight@@3HA], eax
dimensionsReady:
    fild dword ptr [?g_gameConfiguredWidth@@3HA]
    push edi
    push ebx
    fidiv dword ptr [?g_gameConfiguredHeight@@3HA]
    fstp dword ptr [?g_gameAspectRatio@@3MA]
    call dword ptr [__imp__ReleaseDC@8]
    mov eax, dword ptr [?g_gameConfiguredWidth@@3HA]
    xor ebx, ebx
    mov dword ptr [ebp - 060h], eax
    mov eax, dword ptr [?g_gameConfiguredHeight@@3HA]
    xor esi, esi
    inc esi
    cmp byte ptr [?g_gameUseDesktopSize@@3EA], bl
    mov dword ptr [ebp - 05ch], eax
    mov eax, dword ptr [?g_gameWindow@@3PAUHWND__@@A]
    mov dword ptr [ebp - 058h], 015h
    mov dword ptr [ebp - 054h], esi
    mov dword ptr [ebp - 050h], ebx
    mov dword ptr [ebp - 04ch], ebx
    mov dword ptr [ebp - 048h], esi
    mov dword ptr [ebp - 044h], eax
    mov dword ptr [ebp - 040h], ebx
    mov dword ptr [ebp - 03ch], esi
    mov dword ptr [ebp - 038h], 04bh
    mov dword ptr [ebp - 034h], ebx
    mov dword ptr [ebp - 030h], ebx
    mov dword ptr [ebp - 02ch], esi
    mov dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A], ebx
    mov edi, OFFSET ?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A
    jnz showWindowAndFallback
    mov ecx, dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A]
    mov ecx, dword ptr [ecx]
    push edi
    lea edx, [ebp - 060h]
    push edx
    push 040h
    push eax
    push esi
    push ebx
    push dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A]
    call dword ptr [ecx + 040h]
    cmp dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A], ebx
    jnz deviceReady
    mov eax, dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A]
    mov ecx, dword ptr [eax]
    push edi
    lea edx, [ebp - 060h]
    push edx
    push 020h
    push dword ptr [?g_gameWindow@@3PAUHWND__@@A]
    push esi
    push ebx
    push eax
    call dword ptr [ecx + 040h]
    cmp dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A], ebx
    jnz deviceReady
    mov eax, dword ptr [?g_gameWindow@@3PAUHWND__@@A]
showWindowAndFallback:
    push esi
    push eax
    call dword ptr [__imp__ShowWindow@8]
    mov eax, dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A]
    lea edx, [ebp - 010h]
    push edx
    push ebx
    mov dword ptr [?g_gameAspectRatio@@3MA], 03faaa993h
    mov dword ptr [ebp - 030h], ebx
    mov dword ptr [ebp - 02ch], ebx
    mov dword ptr [ebp - 040h], esi
    mov ecx, dword ptr [eax]
    push eax
    call dword ptr [ecx + 020h]
    cmp dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A], ebx
    mov eax, dword ptr [ebp - 004h]
    mov dword ptr [ebp - 058h], eax
    jnz deviceReady
    mov eax, dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A]
    mov ecx, dword ptr [eax]
    push edi
    lea edx, [ebp - 060h]
    push edx
    push 040h
    push dword ptr [?g_gameWindow@@3PAUHWND__@@A]
    push esi
    push ebx
    push eax
    call dword ptr [ecx + 040h]
    cmp dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A], ebx
    jnz deviceReady
    mov eax, dword ptr [?g_gameD3D@@3PAUIDirect3D9@@A]
    mov ecx, dword ptr [eax]
    push edi
    lea edx, [ebp - 060h]
    push edx
    push 020h
    push dword ptr [?g_gameWindow@@3PAUHWND__@@A]
    push esi
    push ebx
    push eax
    call dword ptr [ecx + 040h]
deviceReady:
    mov eax, dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    mov ecx, dword ptr [eax]
    push OFFSET ?g_gameDeviceResource@@3PAXA
    push ebx
    push ebx
    push ebx
    push eax
    call dword ptr [ecx + 048h]
    fldz
    mov eax, dword ptr [?g_gameConfiguredWidth@@3HA]
    fstp dword ptr [ebp - 018h]
    mov dword ptr [ebp - 020h], eax
    fld1
    mov eax, dword ptr [?g_gameConfiguredHeight@@3HA]
    fstp dword ptr [ebp - 014h]
    mov dword ptr [ebp - 01ch], eax
    mov eax, dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    lea edx, [ebp - 028h]
    push edx
    mov dword ptr [ebp - 028h], ebx
    mov dword ptr [ebp - 024h], ebx
    mov ecx, dword ptr [eax]
    push eax
    call dword ptr [ecx + 0bch]
    mov eax, dword ptr [?g_gameD3DDevice@@3PAUIDirect3DDevice9@@A]
    mov ecx, dword ptr [eax]
    push OFFSET ?g_gameDeviceCaps@@3U_D3DCAPS9@@A
    push eax
    call dword ptr [ecx + 01ch]
    pop edi
    pop esi
    pop ebx
    leave
    ret
?InitializeGameD3DDevice@@YAHXZ ENDP

END
