set(CMAKE_C_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)
foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
  set(CMAKE_C_FLAGS_${config} "" CACHE STRING "" FORCE)
  set(CMAKE_CXX_FLAGS_${config} "" CACHE STRING "" FORCE)
endforeach()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

set(SUMO_COMPILE_OPTIONS
  /nologo
  /W3
  /O1
  /GS
  /Gy
  /GF
  /Gd
  /Zp8
)

set(SUMO_CXX_COMPILE_OPTIONS
  /GR-
  /GX-
)

set(SUMO_LINK_OPTIONS
  /NOLOGO
  /SUBSYSTEM:WINDOWS
  /MACHINE:X86
  /DEBUG
  /INCREMENTAL:NO
  /OPT:REF
  /OPT:ICF
  /FILEALIGN:4096
)

function(sumo_configure_msvc_target target)
  target_compile_options(${target} PRIVATE
    $<$<COMPILE_LANGUAGE:C,CXX>:${SUMO_COMPILE_OPTIONS}>
  )
  target_compile_options(${target} PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${SUMO_CXX_COMPILE_OPTIONS}>
  )
  target_compile_definitions(${target} PRIVATE WIN32 _WINDOWS NDEBUG)
  target_link_options(${target} PRIVATE ${SUMO_LINK_OPTIONS})
  set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
  set_property(TARGET ${target} PROPERTY MSVC_DEBUG_INFORMATION_FORMAT "ProgramDatabase")
endfunction()
