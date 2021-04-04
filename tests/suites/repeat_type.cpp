#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <meta/repeat_type.hpp>

#include <limits>
#include <type_traits>  // is_same_v


namespace
{
    constexpr auto large_i = std::numeric_limits< unsigned long long >::max();
    
    struct foo final {};
}


TEST_CASE( "repeat_type always T (" JM_META_TEST_CPP_VERSION_STRING ")" )
{
    using JadeMatrix::meta::repeat_type;
    REQUIRE( std::is_same_v< repeat_type< foo,       0 >, foo > );
    REQUIRE( std::is_same_v< repeat_type< foo,       1 >, foo > );
    REQUIRE( std::is_same_v< repeat_type< foo, 9999999 >, foo > );
    REQUIRE( std::is_same_v< repeat_type< foo, large_i >, foo > );
}

TEST_CASE( "repeat_type with references (" JM_META_TEST_CPP_VERSION_STRING ")" )
{
    using JadeMatrix::meta::repeat_type;
    REQUIRE( std::is_same_v< repeat_type< foo        &, 0 >, foo        & > );
    REQUIRE( std::is_same_v< repeat_type< foo const  &, 0 >, foo const  & > );
    REQUIRE( std::is_same_v< repeat_type< foo       &&, 0 >, foo       && > );
    REQUIRE( std::is_same_v< repeat_type< foo const &&, 0 >, foo const && > );
}
