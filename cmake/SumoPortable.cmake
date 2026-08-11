include_guard(GLOBAL)

set(SUMO_SDL_VERSION "3" CACHE STRING "SDL major version for the build")
set_property(CACHE SUMO_SDL_VERSION PROPERTY STRINGS 2 3)

if(NOT SUMO_SDL_VERSION MATCHES "^[23]$")
  message(FATAL_ERROR
    "SUMO_SDL_VERSION must be 2 or 3, got '${SUMO_SDL_VERSION}'")
endif()

set(SUMO_AUDIO_BACKEND "sdl" CACHE STRING
  "Default audio device backend at runtime")
set_property(CACHE SUMO_AUDIO_BACKEND PROPERTY STRINGS sdl miniaudio)

if(NOT SUMO_AUDIO_BACKEND MATCHES "^(sdl|miniaudio)$")
  message(FATAL_ERROR
    "SUMO_AUDIO_BACKEND must be sdl or miniaudio, got '${SUMO_AUDIO_BACKEND}'")
endif()
if(SUMO_AUDIO_BACKEND STREQUAL "miniaudio")
  set(SUMO_AUDIO_DEFAULT_BACKEND 1)
else()
  set(SUMO_AUDIO_DEFAULT_BACKEND 0)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sumo_portable_options INTERFACE)
add_library(Sumo::PortableOptions ALIAS sumo_portable_options)
target_compile_features(sumo_portable_options INTERFACE c_std_17 cxx_std_17)

option(SUMO_WARNINGS_AS_ERRORS
  "Treat warnings in first-party portable sources as errors" ON)
if(MSVC)
  target_compile_options(sumo_portable_options INTERFACE /W4)
  if(SUMO_WARNINGS_AS_ERRORS)
    target_compile_options(sumo_portable_options INTERFACE /WX)
  endif()
else()
  target_compile_options(sumo_portable_options INTERFACE
    -Wall
    -Wextra
    -Wpedantic
  )
  if(SUMO_WARNINGS_AS_ERRORS)
    target_compile_options(sumo_portable_options INTERFACE -Werror)
  endif()
endif()

if(MSVC)
  set(SUMO_STRICT_FP_COMPILE_OPTIONS /fp:strict)
else()
  set(SUMO_STRICT_FP_COMPILE_OPTIONS
    -fno-fast-math
    -ffp-contract=off
    -frounding-math
  )
endif()
target_compile_options(sumo_portable_options INTERFACE
  ${SUMO_STRICT_FP_COMPILE_OPTIONS})

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoPortableDependencies.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoPortableGuard.cmake")
include(GNUInstallDirs)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoSources.cmake")

add_library(sumo_decomp OBJECT ${SUMO_SOURCES})
target_include_directories(sumo_decomp PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
)
target_compile_options(sumo_decomp PRIVATE ${SUMO_STRICT_FP_COMPILE_OPTIONS})
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-ffp-eval-method=double" SUMO_HAS_FP_EVAL_METHOD)
if(SUMO_HAS_FP_EVAL_METHOD)
  target_compile_options(sumo_decomp PRIVATE -ffp-eval-method=double)
else()
  message(STATUS
    "sumotori: -ffp-eval-method=double unsupported by this compiler; relying "
    "on the source-level wide-intermediate vector kernel in src/core.cpp")
endif()
option(SUMO_DECOMP_WARNINGS
  "Enable warnings" OFF)
if(SUMO_DECOMP_WARNINGS AND NOT MSVC)
  target_compile_options(sumo_decomp PRIVATE -Wall -Wextra)
elseif(SUMO_DECOMP_WARNINGS AND MSVC)
  target_compile_options(sumo_decomp PRIVATE /W4)
endif()

if(MSVC)
  target_compile_options(sumo_decomp PRIVATE /wd4068)
else()
  target_compile_options(sumo_decomp PRIVATE
    -fno-strict-aliasing
    -fno-delete-null-pointer-checks
    -Wno-unknown-pragmas
    -Wno-write-strings
  )
  if(NOT WIN32)
    target_compile_options(sumo_decomp PRIVATE
      "-D__forceinline=inline"
      "-D__cdecl="
      "-D__stdcall="
      "-D__fastcall="
      "-D__declspec(x)="
    )
  endif()
endif()

set(SUMO_EMBEDDED_ASSETS
  fonts/LiberationSerif-Regular.ttf
  fonts/DejaVuSansMono.ttf
  audio/music/sumotori.xm
  levels/editor_default.smo
  sumo.ico
)
foreach(index RANGE 5)
  list(APPEND SUMO_EMBEDDED_ASSETS "audio/sfx/source${index}.wav")
endforeach()
foreach(index RANGE 22)
  set(padded "0000${index}")
  string(LENGTH "${padded}" padded_length)
  math(EXPR padded_start "${padded_length} - 5")
  string(SUBSTRING "${padded}" ${padded_start} 5 padded)
  list(APPEND SUMO_EMBEDDED_ASSETS "textures/tex${padded}.tga")
endforeach()

set(SUMO_EMBED_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/cmake/embed_assets.py")
set(SUMO_EMBED_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

execute_process(
  COMMAND "${Python_EXECUTABLE}" "${SUMO_EMBED_SCRIPT}"
    --root "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    --output-dir "${SUMO_EMBED_OUTPUT_DIR}"
    --list ${SUMO_EMBEDDED_ASSETS}
  OUTPUT_VARIABLE SUMO_EMBED_OUTPUTS
  RESULT_VARIABLE SUMO_EMBED_LIST_RESULT
  ERROR_VARIABLE SUMO_EMBED_LIST_ERROR
)
if(NOT SUMO_EMBED_LIST_RESULT EQUAL 0)
  message(FATAL_ERROR
    "cmake/embed_assets.py --list failed:\n${SUMO_EMBED_LIST_ERROR}")
endif()
string(REGEX REPLACE "\r?\n" ";" SUMO_EMBED_OUTPUTS "${SUMO_EMBED_OUTPUTS}")
list(REMOVE_ITEM SUMO_EMBED_OUTPUTS "")

set(SUMO_EMBED_INPUTS "")
foreach(asset IN LISTS SUMO_EMBEDDED_ASSETS)
  list(APPEND SUMO_EMBED_INPUTS "${CMAKE_CURRENT_SOURCE_DIR}/assets/${asset}")
endforeach()

add_custom_command(
  OUTPUT ${SUMO_EMBED_OUTPUTS}
  COMMAND "${Python_EXECUTABLE}" "${SUMO_EMBED_SCRIPT}"
    --root "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    --output-dir "${SUMO_EMBED_OUTPUT_DIR}"
    ${SUMO_EMBEDDED_ASSETS}
  DEPENDS "${SUMO_EMBED_SCRIPT}" ${SUMO_EMBED_INPUTS}
  COMMENT "Embedding runtime assets into the binary"
  VERBATIM
)

add_library(sumo_assets STATIC ${SUMO_EMBED_OUTPUTS})
target_include_directories(sumo_assets PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
)
set_target_properties(sumo_assets PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

if(SUMO_SDL_VERSION STREQUAL "3")
  set(SUMO_APP_SDL_SOURCES src/app/platform_sdl3.cpp)
else()
  set(SUMO_APP_SDL_SOURCES src/app/platform_sdl2.cpp)
endif()

list(APPEND SUMO_APP_SDL_SOURCES
  src/app/audio_sdl${SUMO_SDL_VERSION}.cpp
  src/app/audio_miniaudio.cpp
)

set(SUMO_APP_CORE_SOURCES
  src/app/platform.cpp
  src/app/input.cpp
  src/app/assets.cpp
  src/app/icon.cpp
  src/app/audio.cpp
  src/app/renderer.cpp
  src/app/ui.cpp
  src/app/mod_picker.cpp
  src/app/extra_levels.cpp
  ${SUMO_APP_SDL_SOURCES}
)

if(WIN32)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/sumo.ico"
    "${CMAKE_CURRENT_BINARY_DIR}/sumo.ico"
    COPYONLY
  )
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/app/sumotori.rc"
    "${CMAKE_CURRENT_BINARY_DIR}/sumotori.rc"
    COPYONLY
  )
  list(APPEND SUMO_APP_CORE_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/sumotori.rc")
endif()

add_executable(sumotori WIN32
  src/app/main.cpp
  ${SUMO_APP_CORE_SOURCES}
)
target_include_directories(sumotori PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/app"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb"
  "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/miniaudio"
)
target_link_libraries(sumotori PRIVATE
  sumo_decomp
  sumo_assets
  Sumo::PortableOptions
  Sumo::SDL
  Sumo::ImGui
  Sumo::GLAD
  Sumo::XM
)
if(UNIX)
  find_package(Threads REQUIRED)
  target_link_libraries(sumotori PRIVATE m Threads::Threads ${CMAKE_DL_LIBS})
endif()
target_compile_definitions(sumotori PRIVATE
  SUMO_SDL_VERSION=${SUMO_SDL_VERSION}
  SUMO_AUDIO_DEFAULT_BACKEND=${SUMO_AUDIO_DEFAULT_BACKEND}
)

if(WIN32)
  if(MSVC)
    target_link_options(sumotori PRIVATE /ENTRY:mainCRTStartup)
  else()
    target_link_options(sumotori PRIVATE -static)
  endif()
endif()

sumo_verify_portable_target_sources(sumotori)

install(TARGETS sumotori
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
