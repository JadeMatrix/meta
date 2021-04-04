FIND_PACKAGE( JadeMatrix-CMake-Modules 1 REQUIRED )
INCLUDE( JadeMatrix-CMake-Modules/Util/AddCompileTest )


# Compilation pass tests
FOREACH( CPP_VERSION IN ITEMS "17" "20" )
    FOREACH( COMPILE IN ITEMS
        "repeat_type"
    )
        ADD_COMPILE_TEST( ${COMPILE}_${CPP_VERSION}
            FILE "pass/${COMPILE}.cpp"
            COMPILE_OPTIONS
                ${META_COMPILE_OPTIONS}
                ${META_COMPILE_OPTIONS_CONVERSION}
            LINK_LIBRARIES meta
        )
        SET_TARGET_PROPERTIES( ${COMPILE}_${CPP_VERSION}_compiles
            PROPERTIES
                CXX_STANDARD          ${CPP_VERSION}
                CXX_STANDARD_REQUIRED ON
                # Consider also ON/OFF for this
                CXX_EXTENSIONS        OFF
        )
    ENDFOREACH()
ENDFOREACH()


# Compilation failure tests
FOREACH( CPP_VERSION IN ITEMS "17" "20" )
    FOREACH( COMPILE IN ITEMS
        "repeat_type_too_few_args"
        "repeat_type_too_many_args"
        "repeat_type_wrong_type_args"
        "type_printer"
    )
        ADD_COMPILE_TEST( ${COMPILE}_${CPP_VERSION}
            FILE "fail/${COMPILE}.cpp"
            COMPILE_OPTIONS
                ${META_COMPILE_OPTIONS}
                ${META_COMPILE_OPTIONS_CONVERSION}
            LINK_LIBRARIES meta
            WILL_FAIL
        )
        SET_TARGET_PROPERTIES( ${COMPILE}_${CPP_VERSION}_compiles
            PROPERTIES
                CXX_STANDARD          ${CPP_VERSION}
                CXX_STANDARD_REQUIRED ON
                # Consider also ON/OFF for this
                CXX_EXTENSIONS        OFF
        )
    ENDFOREACH()
ENDFOREACH()


# Test compiler output of `meta::type_printer`
FOREACH( CPP_VERSION IN ITEMS "17" "20" )
    ADD_COMPILE_TEST( type_printer_output_${CPP_VERSION}
        FILE "fail/type_printer.cpp"
        COMPILE_OPTIONS
            ${META_COMPILE_OPTIONS}
            ${META_COMPILE_OPTIONS_CONVERSION}
        LINK_LIBRARIES meta
    )
    SET_TARGET_PROPERTIES( type_printer_output_${CPP_VERSION}_compiles
        PROPERTIES
            CXX_STANDARD          ${CPP_VERSION}
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS        OFF
    )
    SET_TESTS_PROPERTIES( type_printer_output_${CPP_VERSION}
        PROPERTIES
            PASS_REGULAR_EXPRESSION
                "[^a-zA-Z0-9_]type_to_test_type_printer[^a-zA-Z0-9_]"
    )
ENDFOREACH()
