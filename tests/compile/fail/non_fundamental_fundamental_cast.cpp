#include <meta/fundamental.hpp>

#include <complex>


namespace
{
    struct foo final {};
    
    auto get_fund()
    {
        std::complex< foo > c;
        using JadeMatrix::meta::fundamental_cast;
        return fundamental_cast( c );
    }
}


int main( int, char*[] )
{
    auto f = get_fund();
    ( void )f;
    return 0;
}
