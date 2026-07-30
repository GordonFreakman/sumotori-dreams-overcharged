.686
.model flat
option casemap:none

EXTERN ___security_cookie:DWORD
EXTERN __ftol2:PROC
EXTERN _exp:PROC
EXTERN _fclose:PROC
EXTERN _fopen:PROC
EXTERN _fprintf:PROC
EXTERN _log:PROC
EXTERN ??GVector3@@QAE?AU0@AAU0@@Z:PROC
EXTERN ?g_freeCameraAimScale@@3MB:DWORD
EXTERN ?g_freeCameraAngleRecordScale@@3MB:DWORD
EXTERN ?g_freeCameraFileInitialized@@3HA:DWORD
EXTERN ?g_freeCameraPitchVelocity@@3MA:DWORD
EXTERN ?g_freeCameraPositionRecordScale@@3MB:DWORD
EXTERN ?g_freeCameraRecordTicks@@3HA:DWORD
EXTERN ?g_freeCameraRollVelocity@@3MA:DWORD
EXTERN ?g_freeCameraRotationAcceleration@@3MA:DWORD
EXTERN ?g_freeCameraRotationDamping@@3MA:DWORD
EXTERN ?g_freeCameraScanCodes@@3PACA:DWORD
EXTERN ?g_freeCameraTarget@@3UVector3@@A:DWORD
EXTERN ?g_freeCameraTranslationAcceleration@@3MA:DWORD
EXTERN ?g_freeCameraTranslationDamping@@3MA:DWORD
EXTERN ?g_freeCameraVelocity@@3UVector3@@A:DWORD
EXTERN ?g_freeCameraYawVelocity@@3MA:DWORD
EXTERN ?g_gameCameraWorldPosition@@3UVector3@@A:DWORD
EXTERN ?g_gameInverseViewMatrix@@3UMatrix3@@A:DWORD
EXTERN ?g_gameKeyDown@@3PAEA:DWORD
EXTERN ?g_inertiaRadiusScale@@3MB:DWORD
EXTERN ?g_parserMinimumBreakability@@3MB:DWORD
EXTERN ?g_sceneAngle@@3MA:DWORD
EXTERN ?g_sceneOrientation@@3UMatrix3@@A:DWORD
EXTERN ?g_scenePhaseA@@3MA:DWORD
EXTERN ?g_scenePhaseB@@3MA:DWORD
EXTERN ?g_scenePosition@@3UVector3@@A:DWORD
EXTERN ?RotateRows01@Matrix3@@QAEXM@Z:PROC
EXTERN ?RotateRows02@Matrix3@@QAEXM@Z:PROC
EXTERN ?RotateRows12@Matrix3@@QAEXM@Z:PROC
EXTERN ?SetIdentity@Matrix3@@QAEXXZ:PROC
EXTERN ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z:PROC
EXTERN @__security_check_cookie@4:PROC
EXTERN ??_C@_01MCMALHOG@a?$AA@:BYTE
EXTERN ??_C@_01NOFIACDB@w?$AA@:BYTE

.const
PUBLIC cameraFileName
cameraFileName DB "camera.dat", 0
; STRING: SUMO 0x0042b25c
; STRING: EDITOR 0x0042b25c
PUBLIC cameraRecordFormat
cameraRecordFormat DB "{%d,%d,%d,%d,%d,%d,%d},", 0ah, 0

.code

; FUNCTION: SUMO 0x00402846
; FUNCTION: EDITOR 0x00402846
PUBLIC ?UpdateFreeGameCamera@@YAXH@Z
?UpdateFreeGameCamera@@YAXH@Z PROC
    DB 055h, 08bh, 0ech, 083h, 0ech, 048h, 0a1h
    DD ___security_cookie
    DB 053h, 033h, 0dbh, 039h, 01dh
    DD ?g_freeCameraFileInitialized@@3HA
    DB 089h, 045h, 0fch, 056h, 075h, 022h, 068h
    DD ??_C@_01NOFIACDB@w?$AA@
    DB 068h
    DD cameraFileName
    call _fopen
    DB 050h
    call _fclose
    DB 083h, 0c4h, 00ch, 0c7h, 005h
    DD ?g_freeCameraFileInitialized@@3HA
    DB 001h, 000h, 000h, 000h, 0dbh, 045h, 008h, 051h, 051h, 0d9h, 05dh, 0d8h, 0d9h, 005h
    DD ?g_freeCameraRotationDamping@@3MA
    DB 0ddh, 01ch, 024h
    call _log
    DB 0d8h, 04dh, 0d8h, 0ddh, 01ch, 024h
    call _exp
    DB 0d9h, 05dh, 0d0h, 0d9h, 005h
    DD ?g_freeCameraTranslationDamping@@3MA
    DB 0ddh, 01ch, 024h
    call _log
    DB 0d8h, 04dh, 0d8h, 0ddh, 01ch, 024h
    call _exp
    DB 0d9h, 05dh, 0d4h, 0d9h, 045h, 0d8h, 059h, 0d8h, 00dh
    DD ?g_freeCameraRotationAcceleration@@3MA
    DB 059h, 0d9h, 045h, 0d8h, 033h, 0c0h, 0d8h, 00dh
    DD ?g_freeCameraTranslationAcceleration@@3MA
    DB 0d9h, 05dh, 008h, 00fh, 0beh, 088h
    DD ?g_freeCameraScanCodes@@3PACA
    DB 038h, 099h
    DD ?g_gameKeyDown@@3PAEA
    DB 00fh, 095h, 0c1h, 088h, 04ch, 005h, 0dch, 040h, 083h, 0f8h, 013h, 072h, 0e6h, 038h, 05dh, 0eeh
    DB 074h, 00ch, 0d9h, 045h, 008h, 0d8h, 00dh
    DD ?g_parserMinimumBreakability@@3MB
    DB 0d9h, 05dh, 008h, 038h, 05dh, 0dch, 074h, 00eh, 0d9h, 005h
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 0d8h, 0c1h, 0d9h, 01dh
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 038h, 05dh, 0ddh, 074h, 00eh, 0d9h, 005h
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 0d8h, 0e1h, 0d9h, 01dh
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 038h, 05dh, 0e0h, 074h, 00eh, 0d9h, 005h
    DD ?g_freeCameraRollVelocity@@3MA
    DB 0d8h, 0e1h, 0d9h, 01dh
    DD ?g_freeCameraRollVelocity@@3MA
    DB 038h, 05dh, 0e1h, 074h, 00eh, 0d9h, 005h
    DD ?g_freeCameraRollVelocity@@3MA
    DB 0d8h, 0c1h, 0d9h, 01dh
    DD ?g_freeCameraRollVelocity@@3MA
    DB 038h, 05dh, 0dfh, 074h, 00eh, 0d9h, 005h
    DD ?g_freeCameraYawVelocity@@3MA
    DB 0d8h, 0e1h, 0d9h, 01dh
    DD ?g_freeCameraYawVelocity@@3MA
    DB 038h, 05dh, 0deh, 074h, 00eh, 0d9h, 005h
    DD ?g_freeCameraYawVelocity@@3MA
    DB 0d8h, 0c1h, 0d9h, 01dh
    DD ?g_freeCameraYawVelocity@@3MA
    DB 057h, 0ddh, 0d8h, 0beh
    DD ?g_freeCameraTarget@@3UVector3@@A
    DB 08dh, 07dh, 0c4h, 0a5h, 0a5h, 068h
    DD ?g_scenePosition@@3UVector3@@A
    DB 08dh, 045h, 0b8h, 050h, 08dh, 04dh, 0c4h, 0a5h
    call ??GVector3@@QAE?AU0@AAU0@@Z
    DB 050h, 08dh, 045h, 0c4h, 0beh
    DD ?g_sceneOrientation@@3UMatrix3@@A
    DB 050h, 08bh, 0ceh
    call ?Transform@Matrix3@@QAE?AUVector3@@AAU2@@Z
    DB 0d9h, 005h
    DD ?g_freeCameraRollVelocity@@3MA
    DB 08bh, 0ceh, 0d8h, 04dh, 0d0h, 0d9h, 01dh
    DD ?g_freeCameraRollVelocity@@3MA
    DB 0d9h, 0e8h, 0d8h, 075h, 0cch, 0d9h, 045h, 0c8h, 0d8h, 0c9h, 0d8h, 00dh
    DD ?g_freeCameraAimScale@@3MB
    DB 0d8h, 025h
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d8h, 005h
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 0d8h, 04dh, 0d0h, 0d9h, 01dh
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 0d8h, 04dh, 0c4h, 0d8h, 00dh
    DD ?g_freeCameraAimScale@@3MB
    DB 0d8h, 025h
    DD ?g_freeCameraYawVelocity@@3MA
    DB 0d8h, 00dh
    DD ?g_inertiaRadiusScale@@3MB
    DB 0d8h, 005h
    DD ?g_freeCameraYawVelocity@@3MA
    DB 0d8h, 04dh, 0d0h, 0d9h, 01dh
    DD ?g_freeCameraYawVelocity@@3MA
    DB 0d9h, 045h, 0d8h, 0d8h, 00dh
    DD ?g_freeCameraRollVelocity@@3MA
    DB 0d8h, 02dh
    DD ?g_scenePhaseA@@3MA
    DB 0d9h, 01dh
    DD ?g_scenePhaseA@@3MA
    DB 0d9h, 045h, 0d8h, 0d8h, 00dh
    DD ?g_freeCameraPitchVelocity@@3MA
    DB 0d8h, 005h
    DD ?g_scenePhaseB@@3MA
    DB 0d9h, 01dh
    DD ?g_scenePhaseB@@3MA
    DB 0d9h, 045h, 0d8h, 0d8h, 00dh
    DD ?g_freeCameraYawVelocity@@3MA
    DB 0d8h, 02dh
    DD ?g_sceneAngle@@3MA
    DB 0d9h, 01dh
    DD ?g_sceneAngle@@3MA
    call ?SetIdentity@Matrix3@@QAEXXZ
    DB 0d9h, 005h
    DD ?g_sceneAngle@@3MA
    DB 051h, 08bh, 0ceh, 0d9h, 01ch, 024h
    call ?RotateRows02@Matrix3@@QAEXM@Z
    DB 0d9h, 005h
    DD ?g_scenePhaseB@@3MA
    DB 051h, 08bh, 0ceh, 0d9h, 01ch, 024h
    call ?RotateRows12@Matrix3@@QAEXM@Z
    DB 0d9h, 005h
    DD ?g_scenePhaseA@@3MA
    DB 051h, 08bh, 0ceh, 0d9h, 01ch, 024h
    call ?RotateRows01@Matrix3@@QAEXM@Z
    DB 038h, 05dh, 0e2h, 074h, 03bh, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A
    DB 0d8h, 04dh, 008h, 0d8h, 02dh
    DD ?g_freeCameraVelocity@@3UVector3@@A
    DB 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 04h
    DB 0d8h, 04dh, 008h, 0d8h, 02dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 04h
    DB 0d9h, 01dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 04h
    DB 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 08h
    DB 0d8h, 04dh, 008h, 0d8h, 02dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0d9h, 01dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0ebh, 006h, 0d9h, 005h
    DD ?g_freeCameraVelocity@@3UVector3@@A
    DB 038h, 05dh, 0e3h, 074h, 031h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A
    DB 0d8h, 04dh, 008h, 0deh, 0c1h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 04h
    DB 0d8h, 04dh, 008h, 0d8h, 005h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 04h
    DB 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 08h
    DB 0d8h, 04dh, 008h, 0d8h, 005h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0d9h, 015h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0ebh, 00ch, 0d9h, 005h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 04h
    DB 0d9h, 005h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 038h, 05dh, 0e4h, 0d9h, 045h, 008h, 074h, 026h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 018h
    DB 0d8h, 0c9h, 0deh, 0c4h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 01ch
    DB 0d8h, 0c9h, 0deh, 0c3h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 020h
    DB 0d8h, 0c9h, 0d8h, 0c2h, 0d9h, 015h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0ddh, 0dah, 038h, 05dh, 0e5h, 074h, 026h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 018h
    DB 0d8h, 0c9h, 0deh, 0ech, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 01ch
    DB 0d8h, 0c9h, 0deh, 0ebh, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 020h
    DB 0d8h, 0c9h, 0d8h, 0eah, 0d9h, 015h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0ddh, 0dah, 038h, 05dh, 0e7h, 074h, 026h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 0ch
    DB 0d8h, 0c9h, 0deh, 0ech, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 010h
    DB 0d8h, 0c9h, 0deh, 0ebh, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 014h
    DB 0d8h, 0c9h, 0d8h, 0eah, 0d9h, 015h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0ddh, 0dah, 038h, 05dh, 0e6h, 074h, 024h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 0ch
    DB 0d8h, 0c9h, 0deh, 0c4h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 010h
    DB 0d8h, 0c9h, 0deh, 0c3h, 0d9h, 005h
    DD ?g_sceneOrientation@@3UMatrix3@@A + 014h
    DB 0d8h, 0c9h, 0d8h, 0c2h, 0d9h, 01dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0ddh, 0d8h, 0ffh, 005h
    DD ?g_freeCameraRecordTicks@@3HA
    DB 038h, 01dh
    DD ?g_gameKeyDown@@3PAEA + 039h
    DB 0ddh, 0d8h, 0d9h, 0c1h, 06ah, 009h, 0d8h, 04dh, 0d4h, 059h, 0beh
    DD ?g_sceneOrientation@@3UMatrix3@@A
    DB 0bfh
    DD ?g_gameInverseViewMatrix@@3UMatrix3@@A
    DB 0d9h, 01dh
    DD ?g_freeCameraVelocity@@3UVector3@@A
    DB 0f3h, 0a5h, 0d8h, 04dh, 0d4h, 0d9h, 01dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 04h
    DB 0d9h, 005h
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0d8h, 04dh, 0d4h, 0d9h, 01dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0beh
    DD ?g_scenePosition@@3UVector3@@A
    DB 0ddh, 0d8h, 0bfh
    DD ?g_gameCameraWorldPosition@@3UVector3@@A
    DB 0d9h, 045h, 0d8h, 0d8h, 00dh
    DD ?g_freeCameraVelocity@@3UVector3@@A
    DB 0d8h, 005h
    DD ?g_scenePosition@@3UVector3@@A
    DB 0d9h, 01dh
    DD ?g_scenePosition@@3UVector3@@A
    DB 0d9h, 045h, 0d8h, 0d8h, 00dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 04h
    DB 0d8h, 005h
    DD ?g_scenePosition@@3UVector3@@A + 04h
    DB 0d9h, 01dh
    DD ?g_scenePosition@@3UVector3@@A + 04h
    DB 0d9h, 045h, 0d8h, 0d8h, 00dh
    DD ?g_freeCameraVelocity@@3UVector3@@A + 08h
    DB 0d8h, 005h
    DD ?g_scenePosition@@3UVector3@@A + 08h
    DB 0d9h, 01dh
    DD ?g_scenePosition@@3UVector3@@A + 08h
    DB 0a5h, 0a5h, 0a5h, 05fh, 075h, 013h, 0a1h
    DD ?g_freeCameraRecordTicks@@3HA
    DB 06ah, 032h, 099h, 059h, 0f7h, 0f9h, 085h, 0d2h, 00fh, 085h, 09bh, 000h, 000h, 000h, 068h
    DD ??_C@_01MCMALHOG@a?$AA@
    DB 068h
    DD cameraFileName
    DB 088h, 01dh
    DD ?g_gameKeyDown@@3PAEA + 039h
    call _fopen
    DB 0d9h, 005h
    DD ?g_freeCameraPositionRecordScale@@3MB
    DB 0d9h, 005h
    DD ?g_scenePosition@@3UVector3@@A + 08h
    DB 0ffh, 035h
    DD ?g_freeCameraRecordTicks@@3HA
    DB 0d8h, 0c9h, 08bh, 0f0h
    call __ftol2
    DB 0d9h, 005h
    DD ?g_scenePosition@@3UVector3@@A + 04h
    DB 0d8h, 0c9h, 050h
    call __ftol2
    DB 0d9h, 005h
    DD ?g_scenePosition@@3UVector3@@A
    DB 0d8h, 0c9h, 050h
    call __ftol2
    DB 0ddh, 0d8h, 0d9h, 005h
    DD ?g_freeCameraAngleRecordScale@@3MB
    DB 050h, 0d9h, 005h
    DD ?g_sceneAngle@@3MA
    DB 0d8h, 0c9h
    call __ftol2
    DB 0d9h, 005h
    DD ?g_scenePhaseB@@3MA
    DB 0d8h, 0c9h, 050h
    call __ftol2
    DB 0d9h, 005h
    DD ?g_scenePhaseA@@3MA
    DB 0d8h, 0c9h, 050h
    call __ftol2
    DB 0ddh, 0d8h, 050h, 068h
    DD cameraRecordFormat
    DB 056h
    call _fprintf
    DB 056h
    call _fclose
    DB 083h, 0c4h, 030h, 089h, 01dh
    DD ?g_freeCameraRecordTicks@@3HA
    DB 08bh, 04dh, 0fch, 05eh, 05bh
    call @__security_check_cookie@4
    DB 0c9h, 0c3h
?UpdateFreeGameCamera@@YAXH@Z ENDP

END
