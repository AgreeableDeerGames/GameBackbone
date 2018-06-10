
set(FIND_GB_PATHS
	${GB_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)


find_library(GB_LIBRARY_STATIC_RELEASE
             NAMES GameBackbone
             PATH_SUFFIXES lib64 lib lib/GB build/lib build/lib/Release
             PATHS ${FIND_GB_PATHS})


set(GB_LIBRARY_RELEASE ${GB_LIBRARY_STATIC_RELEASE})


if (GB_LIBRARY_RELEASE)
    # library found
    set(GB_FOUND TRUE)


    set(GB_LIBRARY       ${GB_LIBRARY_RELEASE})

endif()


mark_as_advanced(GB_LIBRARY)


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
