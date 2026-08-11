include_guard(GLOBAL)

function(_sumo_verify_portable_target_node target)
  if(NOT TARGET "${target}")
    message(FATAL_ERROR "Cannot verify unknown portable target '${target}'")
  endif()

  get_target_property(aliased_target "${target}" ALIASED_TARGET)
  if(aliased_target)
    set(target "${aliased_target}")
  endif()

  get_property(visited GLOBAL PROPERTY SUMO_PORTABLE_GUARD_VISITED)
  if(target IN_LIST visited)
    return()
  endif()
  list(APPEND visited "${target}")
  set_property(GLOBAL PROPERTY SUMO_PORTABLE_GUARD_VISITED "${visited}")

  get_target_property(target_imported "${target}" IMPORTED)
  if(target_imported)
    return()
  endif()
  get_target_property(target_source_dir "${target}" SOURCE_DIR)
  get_target_property(target_binary_dir "${target}" BINARY_DIR)
  file(RELATIVE_PATH target_source_relative
    "${CMAKE_SOURCE_DIR}" "${target_source_dir}")
  file(RELATIVE_PATH target_binary_relative
    "${CMAKE_BINARY_DIR}" "${target_binary_dir}")
  if(target_source_relative MATCHES "^\\.\\." OR
     NOT target_source_relative STREQUAL target_binary_relative)
    return()
  endif()

  get_target_property(target_sources "${target}" SOURCES)

  foreach(source IN LISTS target_sources)
    if(source MATCHES "^\\$<")
      message(FATAL_ERROR
        "Portable target '${target}' has an unverifiable generated source: ${source}")
    endif()

    get_filename_component(source_extension "${source}" LAST_EXT)
    string(TOLOWER "${source_extension}" source_extension)
    get_source_file_property(source_language "${source}" LANGUAGE)
    if(source_extension STREQUAL ".asm" OR
       source_language MATCHES "^ASM($|_)")
      message(FATAL_ERROR
        "Portable target '${target}' contains assembly source: ${source}")
    endif()

    if(IS_ABSOLUTE "${source}")
      set(source_path "${source}")
    else()
      get_filename_component(source_path "${source}" ABSOLUTE
        BASE_DIR "${target_source_dir}")
    endif()

    if(EXISTS "${source_path}" AND NOT IS_DIRECTORY "${source_path}")
      file(READ "${source_path}" source_contents)
      if(source_contents MATCHES
         "(^|[^A-Za-z0-9_])__asm(__)?([^A-Za-z0-9_]|$)")
        message(FATAL_ERROR
          "Portable target '${target}' contains inline assembly: ${source}")
      endif()
      if(source_contents MATCHES
         "(^|[^A-Za-z0-9_])naked([^A-Za-z0-9_]|$)")
        message(FATAL_ERROR
          "Portable target '${target}' contains a naked declaration: ${source}")
      endif()
    endif()
  endforeach()

  foreach(link_property LINK_LIBRARIES INTERFACE_LINK_LIBRARIES)
    get_target_property(linked_targets "${target}" "${link_property}")
    foreach(linked_target IN LISTS linked_targets)
      set(link_candidate "${linked_target}")
      while("${link_candidate}" MATCHES
            "^\\$<(BUILD_INTERFACE|LINK_ONLY|TARGET_NAME_IF_EXISTS):(.+)>$")
        set(link_candidate "${CMAKE_MATCH_2}")
      endwhile()
      if(link_candidate MATCHES "\\$<")
        message(FATAL_ERROR
          "Portable target '${target}' has an unverifiable linked target expression: ${linked_target}")
      endif()
      if(TARGET "${link_candidate}")
        _sumo_verify_portable_target_node("${link_candidate}")
      endif()
    endforeach()
  endforeach()
endfunction()

function(sumo_verify_portable_target_sources target)
  set_property(GLOBAL PROPERTY SUMO_PORTABLE_GUARD_VISITED "")
  _sumo_verify_portable_target_node("${target}")
endfunction()
