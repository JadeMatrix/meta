CMAKE_MINIMUM_REQUIRED( VERSION 3.11 FATAL_ERROR #[[
    Requiring 3.11+:
        ADD_*( foo ) ... TARGET_SOURCES( foo ... )
    Requiring 3.10+:
        INCLUDE( doctest )
]] )

FIND_PACKAGE( doctest 2.3.3 REQUIRED COMPONENTS doctest )
INCLUDE( doctest )


# Regular runnable unit tests
ADD_CUSTOM_TARGET( tests ALL )

FOREACH( CPP_VERSION IN ITEMS "17" "20" )
    FOREACH( SUITE IN ITEMS
        "fundamental"
        "is_constant_evaluated"
        "parameter_pack"
        "repeat_type"
    )
        ADD_EXECUTABLE( ${SUITE}_tests_${CPP_VERSION} )
        TARGET_SOURCES( ${SUITE}_tests_${CPP_VERSION} PRIVATE "${SUITE}.cpp" )
        TARGET_LINK_LIBRARIES( ${SUITE}_tests_${CPP_VERSION}
            PRIVATE
                meta
                doctest::doctest
        )
        TARGET_COMPILE_OPTIONS( ${SUITE}_tests_${CPP_VERSION}
            PRIVATE
                ${META_COMPILE_OPTIONS}
                ${META_COMPILE_OPTIONS_CONVERSION}
        )
        TARGET_COMPILE_DEFINITIONS( ${SUITE}_tests_${CPP_VERSION}
            PRIVATE
                "JM_META_TEST_CPP_VERSION_STRING=\"C++${CPP_VERSION}\""
        )
        SET_TARGET_PROPERTIES( ${SUITE}_tests_${CPP_VERSION}
            PROPERTIES
                CXX_STANDARD          ${CPP_VERSION}
                CXX_STANDARD_REQUIRED ON
                # Consider also ON/OFF for this
                CXX_EXTENSIONS        OFF
        )
        
        ADD_DEPENDENCIES( tests ${SUITE}_tests_${CPP_VERSION} )
        DOCTEST_DISCOVER_TESTS( ${SUITE}_tests_${CPP_VERSION} )
    ENDFOREACH()
ENDFOREACH()
