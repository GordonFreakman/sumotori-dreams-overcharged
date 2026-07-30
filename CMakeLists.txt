cmake_minimum_required(VERSION 3.25...3.26 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0141 NEW)

project(SUMO LANGUAGES C CXX ASM_MASM)

option(SUMO_REGISTERED_BUILD "Build the registered version" ON)

if(NOT WIN32 OR NOT MSVC)
  message(FATAL_ERROR "SUMO must be built as a x86 Windows target")
endif()

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "13.10.3077")
  message(FATAL_ERROR
    "Expected Microsoft C/C++ 13.10.3077, got ${CMAKE_CXX_COMPILER_VERSION}")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(FATAL_ERROR "SUMO requires a x86 compiler")
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/reccmp.cmake")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoCompiler.cmake")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoDependencies.cmake")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoSources.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/EditorSources.cmake")
add_executable(SUMO WIN32 ${SUMO_SOURCES})

set_source_files_properties(SUMO/core/big_integer_arithmetic.cpp PROPERTIES
  COMPILE_FLAGS "/GX"
)
set_source_files_properties(
  SUMO/core/assert.cpp
  SUMO/core/big_integer_divide.cpp
  SUMO/core/big_integer_log.cpp
  SUMO/core/big_integer_modular_power.cpp
  SUMO/core/big_integer_power.cpp
  SUMO/core/big_integer_string.cpp
  SUMO/game/game_settings_transform.cpp
  SUMO/game/game_settings_load.cpp
  EDITOR/game/game_settings_load.cpp
  PROPERTIES COMPILE_FLAGS "/GX"
)
set_source_files_properties(SUMO/parser/expression_parser.cpp PROPERTIES
  COMPILE_FLAGS "/GX"
)

add_dependencies(SUMO d3d9-import)
target_include_directories(SUMO PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/audio"
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/core"
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/game"
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/parser"
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/physics"
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/platform"
  "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/render"
  "${CMAKE_CURRENT_BINARY_DIR}"
  "${DXSDK_ROOT}/Include"
)
target_link_libraries(SUMO PRIVATE ${SUMO_WINDOWS_LIBRARIES})
target_compile_definitions(SUMO PRIVATE
  SUMO_REGISTERED_BUILD=$<BOOL:${SUMO_REGISTERED_BUILD}>)
sumo_configure_msvc_target(SUMO)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoLinkerSymbols.cmake")
sumo_apply_linker_symbols(SUMO)

set_property(TARGET SUMO PROPERTY OUTPUT_NAME "sumofull")
set_property(TARGET SUMO PROPERTY PREFIX "")
set_property(TARGET SUMO PROPERTY SUFFIX ".exe")
reccmp_add_target(SUMO ID SUMO)

if(EDITOR_SOURCE_SET_COMPLETE)
  add_executable(EDITOR WIN32 ${EDITOR_SOURCES})
  add_dependencies(EDITOR d3d9-import)
  target_include_directories(EDITOR PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/EDITOR"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/audio"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/game"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/parser"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/physics"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/platform"
    "${CMAKE_CURRENT_SOURCE_DIR}/SUMO/render"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${DXSDK_ROOT}/Include"
  )
  target_link_libraries(EDITOR PRIVATE ${SUMO_WINDOWS_LIBRARIES})
  target_compile_definitions(EDITOR PRIVATE
    SUMO_REGISTERED_BUILD=$<BOOL:${SUMO_REGISTERED_BUILD}>)
  sumo_configure_msvc_target(EDITOR)
  sumo_apply_linker_symbols(EDITOR)
  set_property(TARGET EDITOR PROPERTY OUTPUT_NAME "sumoeditor")
  set_property(TARGET EDITOR PROPERTY PREFIX "")
  set_property(TARGET EDITOR PROPERTY SUFFIX ".exe")
  reccmp_add_target(EDITOR ID EDITOR)
endif()

reccmp_configure()
