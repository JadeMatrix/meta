#include "../repeat_type_test_utils.hpp"


int main( int, char*[] )
{
    bar_4 b;
    b.function( int, foo(), foo(), foo() );
    return 0;
}
