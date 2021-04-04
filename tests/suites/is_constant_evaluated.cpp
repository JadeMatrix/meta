#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <meta/is_constant_evaluated.hpp>


namespace
{
    enum class is_constexpr { no, yes };
    
    constexpr auto check_constexpr()
    {
        JM_META_IF_CONSTANT_EVALUATED()
        {
            return is_constexpr::yes;
        }
        else
        {
            return is_constexpr::no;
        }
    }
}


// Needs to be a potentially visible symbol
auto force_non_constexpr()
{
    return check_constexpr();
}


TEST_CASE(
    "JM_META_IF_CONSTANT_EVALUATED constexpr branch ("
    JM_META_TEST_CPP_VERSION_STRING
    ")"
)
{
    constexpr auto value = check_constexpr();
    REQUIRE( value == is_constexpr::yes );
}

TEST_CASE(
    "JM_META_IF_CONSTANT_EVALUATED non-constexpr branch ("
    JM_META_TEST_CPP_VERSION_STRING
    ")"
)
{
    const auto value = force_non_constexpr();
    // This feature may not be available on all compilers; since it's just an
    // optimization, don't fail this test
    WARN( value == is_constexpr::no );
}
