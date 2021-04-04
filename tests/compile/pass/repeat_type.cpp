#include "../repeat_type_test_utils.hpp"


namespace
{
    constexpr foo cxf;
}


foo make_foo() { return {}; }


int main( int, char*[] )
{
    bar_4 b;
    b.function( foo(), foo(), foo(), foo() );
    b.function( {}, cxf, make_foo(), type_convertible_to_foo{} );
    return 0;
}
