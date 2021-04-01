CMAKE_MINIMUM_REQUIRED( VERSION 3.1 FATAL_ERROR #[[
    Requiring 3.1+:
        WRITE_BASIC_PACKAGE_VERSION_FILE( ... )
]] )

PROJECT(
    "JadeMatrix-meta"
    VERSION 0.1
    LANGUAGES CXX
)

INCLUDE( CTest )
INCLUDE( GNUInstallDirs )

IF( EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake" )
    INCLUDE( "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake" )
    CONAN_SET_FIND_PATHS()
ENDIF()


ADD_LIBRARY( meta INTERFACE )
TARGET_INCLUDE_DIRECTORIES(
    meta
    INTERFACE
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)


INSTALL(
    TARGETS meta
    EXPORT "jadematrix-meta-config"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT core
)
INSTALL(
    DIRECTORY "include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT core
)

INCLUDE( CMakePackageConfigHelpers )
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${PROJECT_BINARY_DIR}/jadematrix-meta-config-version.cmake"
    COMPATIBILITY SameMajorVersion
)
INSTALL(
    FILES "${PROJECT_BINARY_DIR}/jadematrix-meta-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/JadeMatrix-meta/"
    COMPONENT cmake
)

INSTALL(
    EXPORT "jadematrix-meta-config"
    NAMESPACE "JadeMatrix::"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/JadeMatrix-meta/"
    COMPONENT cmake
)

EXPORT( EXPORT "jadematrix-meta-config" FILE "jadematrix-meta-config.cmake" )


IF( BUILD_TESTING )
    ADD_SUBDIRECTORY( "tests/" )
ENDIF()
