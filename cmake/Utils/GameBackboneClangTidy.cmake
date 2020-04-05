include("${PROJECT_SOURCE_DIR}/cmake/Utils/GameBackboneMessage.cmake")

find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
  )
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*, -google-build-using-namespace, -fuchsia-default-arguments, -fuchsia-overloaded-operator, -fuchsia-default-arguments-calls, -modernize-use-trailing-return-type")
endif()

function(gamebackbone_target_enable_clang_tidy ANALYSIS_TARGET)
    if(CLANG_TIDY_EXE)
        gamebackbone_message("Clang-Tidy enabled. Clang-Tidy will be run on build.")
        set_target_properties (
            ${ANALYSIS_TARGET} PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
        # Clang Tidy on, but not found
    else()
        gamebackbone_fatal_error("Clang Tidy enabled but not found!")
    endif()   
endfunction()
