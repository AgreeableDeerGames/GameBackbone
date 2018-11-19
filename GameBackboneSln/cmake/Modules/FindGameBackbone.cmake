
set(FIND_GB_PATHS
    ${GB_ROOT}
    ${GB_ROOT}/GameBackboneLib
    $ENV{GB_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)

# find the GB include directory
find_path(GB_INCLUDE_DIR Backbone/GameRegion.h
        PATH_SUFFIXES header
        PATHS ${FIND_GB_PATHS})

find_library(GB_LIBRARY_DYNAMIC_RELEASE
             NAMES GameBackbone
             PATH_SUFFIXES lib64 lib lib/GB build/lib build/lib/Release
             PATHS ${FIND_GB_PATHS})

find_library(GB_LIBRARY_DYNAMIC_DEBUG
            NAMES GameBackbone-d
            PATH_SUFFIXES lib64 lib lib/GB build/lib build/lib/Debug
            PATHS ${FIND_GB_PATHS})


set(GB_LIBRARY_RELEASE ${GB_LIBRARY_DYNAMIC_RELEASE})
set(GB_LIBRARY_DEBUG ${GB_LIBRARY_DYNAMIC_DEBUG})


if (GB_LIBRARY_RELEASE OR GB_LIBRARY_DEBUG)
    # library found
    set(GB_FOUND TRUE)

    # if both are found, set TGUI_LIBRARY to contain both
    if (GB_LIBRARY_DEBUG AND GB_LIBRARY_RELEASE)
        set(GB_LIBRARY 
            debug ${GB_LIBRARY_DEBUG} 
            optimized ${GB_LIBRARY_RELEASE})
    endif()

    # if only one debug/release variant is found, set the other to be equal to the found one
    if (GB_LIBRARY_RELEASE AND NOT GB_LIBRARY_DEBUG)
        set(GB_LIBRARY_DEBUG ${GB_LIBRARY_RELEASE})
        set(GB_LIBRARY       ${GB_LIBRARY_RELEASE})
    endif()
    if (GB_LIBRARY_DEBUG AND NOT GB_LIBRARY_RELEASE)
        set(GB_LIBRARY_RELEASE ${GB_LIBRARY_DEBUG})
        set(GB_LIBRARY         ${GB_LIBRARY_DEBUG})
    endif()
endif()


mark_as_advanced(GB_LIBRARY
                GB_LIBRARY_DEBUG
                GB_LIBRARY_RELEASE
                GB_LIBRARY_DYNAMIC_DEBUG
                GB_LIBRARY_DYNAMIC_RELEASE)

# error handling
if(NOT GB_FOUND)
    # include directory or library not found
    set(FIND_GB_ERROR "Could NOT find GB")
endif()
if (NOT GB_FOUND)
    if(GB_FIND_REQUIRED)
        # fatal error
        message(FATAL_ERROR ${FIND_GB_ERROR})
    elseif(NOT GB_FIND_QUIETLY)
        # error but continue
        message("${FIND_GB_ERROR}")
    endif()
endif()

# handle success
if(GB_FOUND AND NOT GB_FIND_QUIETLY)
    message(STATUS "Found GB ${GB_VERSION_MAJOR}.${GB_VERSION_MINOR}.${GB_VERSION_PATCH} in ${GB_INCLUDE_DIR}")
endif()
