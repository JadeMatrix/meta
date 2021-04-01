FIND_PACKAGE( JadeMatrix-CMake-Modules 1 REQUIRED )
INCLUDE( JadeMatrix-CMake-Modules/Util/AddCompileTest )

FOREACH( COMPILE IN ITEMS )
    ADD_COMPILE_TEST( ${COMPILE}
        FILE "pass/${COMPILE}.cpp"
        COMPILE_OPTIONS
            ${META_COMPILE_OPTIONS}
            ${META_COMPILE_OPTIONS_CONVERSION}
        LINK_LIBRARIES meta
    )
ENDFOREACH()
