set(DXSDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/dxsdk")
set(D3D9_DEF "${CMAKE_CURRENT_SOURCE_DIR}/cmake/d3d9.def")
set(D3D9_IMPORT_LIBRARY "${CMAKE_CURRENT_BINARY_DIR}/d3d9.lib")
set(SUMO_AUDIO_DATA_ASM
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/audio/game_audio_data.asm")
set(SUMO_AUDIO_XM_PARSER
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/audio/game_audio_xm_parser.asm")

add_custom_command(
  OUTPUT "${D3D9_IMPORT_LIBRARY}"
  COMMAND "${CMAKE_AR}" /NOLOGO /MACHINE:X86 /DEF:"${D3D9_DEF}"
          /OUT:"${D3D9_IMPORT_LIBRARY}"
  DEPENDS "${D3D9_DEF}"
  COMMENT "Generating VC7.1-compatible d3d9.lib"
  VERBATIM
)
add_custom_target(d3d9-import DEPENDS "${D3D9_IMPORT_LIBRARY}")

set(SUMO_WINDOWS_LIBRARIES
  "${D3D9_IMPORT_LIBRARY}"
  dsound
  winmm
  msacm32
  user32
  gdi32
  comdlg32
  advapi32
  kernel32
)
