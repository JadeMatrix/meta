CMAKE_MINIMUM_REQUIRED( VERSION 3.10 FATAL_ERROR #[[
    Requiring 3.10+:
        INCLUDE( doctest )
]] )

IF(
       "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang"
    OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel"
)
    SET( META_COMPILE_OPTIONS
        "-g"
        "-Werror"
        "-Wall"
        "-Wextra"
        "-Wshadow"
        "-Wnon-virtual-dtor"
        "-Wold-style-cast"
        "-Wcast-align"
        "-Wunused"
        "-Woverloaded-virtual"
        "-Wpedantic"
        "-Wnull-dereference"
        "-Wformat=2"
        "-Wconversion"
        "-Wsign-conversion"
        "-Wdouble-promotion"
    )
    
    IF( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
        LIST( APPEND META_COMPILE_OPTIONS
            "-Wduplicated-cond"
            "-Wduplicated-branches"
            "-Wlogical-op"
            "-Wuseless-cast"
        )
    ENDIF()
ELSEIF( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    SET( META_COMPILE_OPTIONS
        "/DEBUG"
        "/WX"
        "/Wall"
    )
ENDIF()


ADD_SUBDIRECTORY( "suites/"  )
ADD_SUBDIRECTORY( "compile/" )
