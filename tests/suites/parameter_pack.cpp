#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <meta/parameter_pack.hpp>

#include <cstddef>      // size_t
#include <string>       // basic_string, char_traits<char>, allocator<char>
#include <tuple>
#include <type_traits>  // is_same_v
#include <utility>      // index_sequence, make_index_sequence
#include <variant>
#include <vector>


namespace
{
    struct foo final {};
    
    using custom_type_param_pack = JadeMatrix::meta::type_parameter_pack<
        int,
        foo,
        std::vector< bool >
    >;
    
    using std_string_param_pack = JadeMatrix::meta::type_parameter_pack<
        char,
        std::char_traits< char >,
        std::allocator< char >
    >;
}


TEST_CASE( "type_parameter_pack::size (" JM_META_TEST_CPP_VERSION_STRING ")" )
{
    REQUIRE( custom_type_param_pack::size == 3 );
}

TEST_CASE(
    "type_parameter_pack::wrapped_in< std::tuple > ("
    JM_META_TEST_CPP_VERSION_STRING
    ")"
)
{
    REQUIRE( std::is_same_v<
        custom_type_param_pack::wrapped_in< std::tuple >,
        std::tuple< int, foo, std::vector< bool > >
    > );
}

TEST_CASE(
    "type_parameter_pack::wrapped_in< std::variant > ("
    JM_META_TEST_CPP_VERSION_STRING
    ")"
)
{
    REQUIRE( std::is_same_v<
        custom_type_param_pack::wrapped_in< std::variant >,
        std::variant< int, foo, std::vector< bool > >
    > );
}

TEST_CASE(
    "type_parameter_pack::wrapped_in non-variadic ("
    JM_META_TEST_CPP_VERSION_STRING
    ")"
)
{
    REQUIRE( std::is_same_v<
        std_string_param_pack::wrapped_in< std::basic_string >,
        std::string
    > );
}

TEST_CASE( "value_parameter_pack::size (" JM_META_TEST_CPP_VERSION_STRING ")" )
{
    using values = JadeMatrix::meta::value_parameter_pack< 542, -1, 99999, -1 >;
    REQUIRE( values::size == 4 );
}

TEST_CASE(
    "value_parameter_pack::wrapped_in< std::index_sequence > ("
    JM_META_TEST_CPP_VERSION_STRING
    ")"
)
{
    using values = JadeMatrix::meta::value_parameter_pack<
        static_cast< std::size_t >( 0 ),
        static_cast< std::size_t >( 1 ),
        static_cast< std::size_t >( 2 )
    >;
    REQUIRE( std::is_same_v<
        values::wrapped_in< std::index_sequence >,
        std::make_index_sequence< 3 >
    > );
}
