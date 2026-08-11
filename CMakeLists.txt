cmake_minimum_required(VERSION 3.25...3.26 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0141 NEW)
if(POLICY CMP0219)
  cmake_policy(SET CMP0219 NEW)
endif()

project(SUMO LANGUAGES C CXX)

if(WIN32)
  enable_language(RC)
endif()

foreach(language C CXX)
  if(language STREQUAL "C")
    set(required_feature c_std_17)
  else()
    set(required_feature cxx_std_17)
  endif()
  if(NOT required_feature IN_LIST CMAKE_${language}_COMPILE_FEATURES)
    message(FATAL_ERROR
      "C17/C++17 capable compiler is required!")
  endif()
endforeach()

option(SUMO_BUILD_PORTABLE "Build the portable C/C++ version" ON)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SumoPortable.cmake")
