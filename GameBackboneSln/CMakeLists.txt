# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project("GameBackbone")

# top project folder
set(GAMEBACKBONE_TOP_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

# project wide output directories
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(GB_ROOT ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(GB_BUILD_VARS_FILE "${GAMEBACKBONE_TOP_FOLDER}/GB_BuildVars.txt")
if (EXISTS ${GB_BUILD_VARS_FILE})
    # setup keys
    set(SFML_ROOT_INDEX 4)
    set(TGUI_ROOT_INDEX 6)
    set(BOOST_ROOT_INDEX 8)

    # read file
    file(STRINGS ${GB_BUILD_VARS_FILE} FILE_LINES)

    # search for sfml key
    list(GET FILE_LINES ${SFML_ROOT_INDEX} INPUT_SFML_ROOT)
    if(NOT ${INPUT_SFML_ROOT} STREQUAL "" AND NOT ${INPUT_SFML_ROOT} STREQUAL "<SFML_ROOT_PATH>")
        SET(SFML_ROOT ${INPUT_SFML_ROOT})
        message("SFML_ROOT set to: ${SFML_ROOT} via GB_BuildVars.txt")
    endif()
    # search for tgui key
    list(GET FILE_LINES ${TGUI_ROOT_INDEX} INPUT_TGUI_ROOT)
    if(NOT ${INPUT_TGUI_ROOT} STREQUAL "" AND NOT ${INPUT_TGUI_ROOT} STREQUAL "<TGUI_ROOT_PATH>")
        SET(TGUI_ROOT ${INPUT_TGUI_ROOT})
        message("TGUI_ROOT set to: ${TGUI_ROOT} via GB_BuildVars.txt")
    endif()
    # search for boost key
    list(GET FILE_LINES ${BOOST_ROOT_INDEX} INPUT_BOOST_ROOT)
    if(NOT ${INPUT_BOOST_ROOT} STREQUAL "" AND NOT ${INPUT_BOOST_ROOT} STREQUAL "<BOOST_ROOT_PATH>")
        SET(BOOST_ROOT ${INPUT_TGUI_ROOT})
        message("BOOST_ROOT set to: ${BOOST_ROOT} via GB_BuildVars.txt")
    endif()
endif()

# SFML and TGUI install path from environment
if (NOT $ENV{SFML_ROOT} STREQUAL "" AND NOT ${SFML_ROOT})
    set(SFML_ROOT $ENV{SFML_ROOT})
    message("SFML_ROOT set to: ${SFML_ROOT} via environment variable")
endif()
if (NOT $ENV{TGUI_ROOT} STREQUAL "" AND NOT ${TGUI_ROOT})
    set(TGUI_ROOT $ENV{TGUI_ROOT})
    message("TGUI_ROOT set to: ${TGUI_ROOT} via environment variable")
endif()

# add dependencies to cmake module path adfad
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SFML_ROOT}/cmake/Modules)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${TGUI_ROOT}/cmake/Modules)

# prepend function from https://stackoverflow.com/a/27630120
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

# set posfix
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX -d)
endif()

add_subdirectory("GameBackboneLib")
add_subdirectory("GameBackboneExe")
# add_subdirectory("GameBackboneBoostUnitTest1")