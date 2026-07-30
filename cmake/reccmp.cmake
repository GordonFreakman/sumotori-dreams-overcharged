# Find reccmp-ghidra-import for optional Ghidra import build targets.
find_program(RECCMP_GHIDRA_IMPORT_BIN
  NAMES reccmp-ghidra-import
  DOC "Path of reccmp-ghidra-import"
)

if(EXISTS "${RECCMP_GHIDRA_IMPORT_BIN}")
  set_property(GLOBAL APPEND PROPERTY JOB_POOLS "reccmp_import_ghidra_job_pool=1")
  add_custom_target(reccmp-import-ghidra)
endif()

function(reccmp_find_project result)
  set(curdir "${CMAKE_CURRENT_SOURCE_DIR}")
  while(1)
    if(EXISTS "${curdir}/reccmp-project.yml")
      break()
    endif()
    get_filename_component(nextdir "${curdir}" DIRECTORY)
    if(nextdir STREQUAL curdir)
      set(curdir "${result}-NOTFOUND")
      break()
    endif()
    set(curdir "${nextdir}")
  endwhile()
  set("${result}" "${curdir}" PARENT_SCOPE)
endfunction()
function(reccmp_add_target target)
  cmake_parse_arguments(args "" "ID" "" ${ARGN})
  if(NOT args_ID)
    message(FATAL_ERROR "Missing ID argument")
  endif()

  set_property(TARGET ${target} PROPERTY INTERFACE_RECCMP_ID "${args_ID}")
  set_property(GLOBAL APPEND PROPERTY RECCMP_TARGETS ${target})

  if(EXISTS "${RECCMP_GHIDRA_IMPORT_BIN}")
    set(RECCMP_${args_ID}_GHIDRA_LOCAL_PROJECT_PATH "" CACHE FILEPATH
      "Path of the Ghidra ${args_ID} project")
    set(RECCMP_${args_ID}_GHIDRA_FILE "" CACHE STRING
      "Name of the file inside the Ghidra project")
    if(EXISTS "${RECCMP_${args_ID}_GHIDRA_LOCAL_PROJECT_PATH}"
       AND NOT "${RECCMP_${args_ID}_GHIDRA_FILE}" STREQUAL "")
      get_filename_component(ghidra_project_dir
        "${RECCMP_${args_ID}_GHIDRA_LOCAL_PROJECT_PATH}" DIRECTORY)
      get_filename_component(ghidra_project_name
        "${RECCMP_${args_ID}_GHIDRA_LOCAL_PROJECT_PATH}" NAME_WE)
      add_custom_target(reccmp-import-ghidra-${args_ID}
        COMMAND "${RECCMP_GHIDRA_IMPORT_BIN}"
          --target "${args_ID}"
          --local-project-dir "${ghidra_project_dir}"
          --local-project-name "${ghidra_project_name}"
          --file "${RECCMP_${args_ID}_GHIDRA_FILE}"
        JOB_POOL "reccmp_import_ghidra_job_pool"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
      )
      add_dependencies(reccmp-import-ghidra reccmp-import-ghidra-${args_ID})
    endif()
  endif()
endfunction()

function(reccmp_configure)
  reccmp_find_project(reccmp_project_dir)
  if(NOT reccmp_project_dir)
    message(FATAL_ERROR "Cannot find reccmp-project.yml")
  endif()

  # Relative paths keep this file usable by host Python even though CMake and
  # MSVC run through Wine and otherwise report Z:/... Windows paths.
  file(RELATIVE_PATH reccmp_project_relative
    "${CMAKE_BINARY_DIR}" "${reccmp_project_dir}")
  file(TO_CMAKE_PATH "${reccmp_project_relative}" reccmp_project_relative)

  set(build_yml "project: '${reccmp_project_relative}'\ntargets:\n")
  get_property(reccmp_targets GLOBAL PROPERTY RECCMP_TARGETS)
  foreach(target ${reccmp_targets})
    get_property(id TARGET "${target}" PROPERTY INTERFACE_RECCMP_ID)
    string(APPEND build_yml "  ${id}:\n")
    string(APPEND build_yml "    path: '$<TARGET_FILE_NAME:${target}>'\n")
    string(APPEND build_yml "    pdb: '$<TARGET_PDB_FILE_NAME:${target}>'\n")
  endforeach()

  file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/reccmp-build.yml" CONTENT "${build_yml}")
endfunction()
