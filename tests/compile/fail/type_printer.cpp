#include <meta/type_printer.hpp>


namespace
{
    struct type_to_test_type_printer final {};
}


int main( int, char*[] )
{
    JadeMatrix::meta::type_printer< type_to_test_type_printer > tp;
    ( void )tp;
    return 0;
}
