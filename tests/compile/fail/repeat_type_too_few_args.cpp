#include "../repeat_type_test_utils.hpp"


int main( int, char*[] )
{
    bar_4 b;
    b.function( foo(), foo(), foo() );
    return 0;
}
