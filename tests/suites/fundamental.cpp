#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <meta/fundamental.hpp>

#include <cmath>        // nextafter
#include <chrono>       // duration
#include <limits>
#include <random>       // uniform_real_distribution, random_device, minstd_rand
#include <tuple>
#include <type_traits>  // is_same_v
#include <utility>      // declval


namespace meta = ::JadeMatrix::meta;


namespace
{
    std::minstd_rand gen( std::random_device{}() );
    
    template< typename T > auto random()
    {
        std::uniform_real_distribution<> dist(
            static_cast< double >( std::numeric_limits< T >::min() ),
            // Yeah this will never generate the max value, but it's good enough
            // for testing purposes
            static_cast< double >( std::numeric_limits< T >::max() )
        );
        return static_cast< T >( dist( gen ) );
    }
    template<> auto random< bool >()
    {
        std::uniform_int_distribution<> dist( 0, 1 );
        return static_cast< bool >( dist( gen ) );
    }
}


#define EMIT_FUND_FUNDCAST_TEST( TYPE ) \
    TEST_CASE( \
        "fundamental_cast for " #TYPE " (" JM_META_TEST_CPP_VERSION_STRING ")" \
    ) \
    { \
        using meta::fundamental_cast; /* ADL */ \
        auto value = random< TYPE >(); \
        CAPTURE( value ); \
        REQUIRE( std::is_same_v< \
            std::tuple< TYPE >, \
            decltype( fundamental_cast( value ) ) \
        > ); \
        REQUIRE( std::get< 0 >( fundamental_cast( value ) ) == value ); \
    }
EMIT_FUND_FUNDCAST_TEST( bool               )
EMIT_FUND_FUNDCAST_TEST( char               )
EMIT_FUND_FUNDCAST_TEST( short              )
EMIT_FUND_FUNDCAST_TEST( int                )
EMIT_FUND_FUNDCAST_TEST( long               )
EMIT_FUND_FUNDCAST_TEST( long long          )
EMIT_FUND_FUNDCAST_TEST( unsigned char      )
EMIT_FUND_FUNDCAST_TEST( unsigned short     )
EMIT_FUND_FUNDCAST_TEST( unsigned int       )
EMIT_FUND_FUNDCAST_TEST( unsigned long      )
EMIT_FUND_FUNDCAST_TEST( unsigned long long )
EMIT_FUND_FUNDCAST_TEST( float              )
EMIT_FUND_FUNDCAST_TEST( double             )
EMIT_FUND_FUNDCAST_TEST( long double        )
#undef EMIT_FUND_FUNDCAST_TEST


#define EMIT_CHRONO_FUNDCAST_TEST( TYPE ) \
    TEST_CASE( \
        "fundamental_cast for std::chrono::duration< " \
        #TYPE \
        ", ... > (" \
        JM_META_TEST_CPP_VERSION_STRING \
        ")" \
    ) \
    { \
        using meta::fundamental_cast; /* ADL */ \
        auto value = random< TYPE >(); \
        CAPTURE( value ); \
        std::chrono::duration< TYPE, std::ratio< 3600 > > hours( value ); \
        std::chrono::duration< TYPE, std::micro         > usecs( value ); \
        REQUIRE_FALSE( hours == usecs ); \
        REQUIRE( std::is_same_v< \
            std::tuple< TYPE >, \
            decltype( fundamental_cast( hours ) ) \
        > ); \
        REQUIRE( std::is_same_v< \
            decltype( fundamental_cast( hours ) ), \
            decltype( fundamental_cast( usecs ) ) \
        > ); \
        REQUIRE( fundamental_cast( hours ) == fundamental_cast( usecs ) ); \
    }
EMIT_CHRONO_FUNDCAST_TEST( bool               )
EMIT_CHRONO_FUNDCAST_TEST( char               )
EMIT_CHRONO_FUNDCAST_TEST( short              )
EMIT_CHRONO_FUNDCAST_TEST( int                )
EMIT_CHRONO_FUNDCAST_TEST( long               )
EMIT_CHRONO_FUNDCAST_TEST( long long          )
EMIT_CHRONO_FUNDCAST_TEST( unsigned char      )
EMIT_CHRONO_FUNDCAST_TEST( unsigned short     )
EMIT_CHRONO_FUNDCAST_TEST( unsigned int       )
EMIT_CHRONO_FUNDCAST_TEST( unsigned long      )
EMIT_CHRONO_FUNDCAST_TEST( unsigned long long )
EMIT_CHRONO_FUNDCAST_TEST( float              )
EMIT_CHRONO_FUNDCAST_TEST( double             )
EMIT_CHRONO_FUNDCAST_TEST( long double        )
#undef EMIT_CHRONO_FUNDCAST_TEST


#define EMIT_COMPLEX_FUNDCAST_TEST( TYPE ) \
    TEST_CASE( \
        "fundamental_cast for std::complex< " \
        #TYPE \
        " > (" \
        JM_META_TEST_CPP_VERSION_STRING \
        ")" \
    ) \
    { \
        using meta::fundamental_cast; /* ADL */ \
        auto real = random< TYPE >(); \
        auto imag = random< TYPE >(); \
        CAPTURE( real ); \
        CAPTURE( imag ); \
        std::complex< TYPE > c( real, imag ); \
        REQUIRE( std::is_same_v< \
            std::tuple< TYPE, TYPE >, \
            decltype( fundamental_cast( c ) ) \
        > ); \
        REQUIRE( fundamental_cast( c ) == std::tuple( real, imag ) ); \
    }
EMIT_COMPLEX_FUNDCAST_TEST( bool               )
EMIT_COMPLEX_FUNDCAST_TEST( char               )
EMIT_COMPLEX_FUNDCAST_TEST( short              )
EMIT_COMPLEX_FUNDCAST_TEST( int                )
EMIT_COMPLEX_FUNDCAST_TEST( long               )
EMIT_COMPLEX_FUNDCAST_TEST( long long          )
EMIT_COMPLEX_FUNDCAST_TEST( unsigned char      )
EMIT_COMPLEX_FUNDCAST_TEST( unsigned short     )
EMIT_COMPLEX_FUNDCAST_TEST( unsigned int       )
EMIT_COMPLEX_FUNDCAST_TEST( unsigned long      )
EMIT_COMPLEX_FUNDCAST_TEST( unsigned long long )
EMIT_COMPLEX_FUNDCAST_TEST( float              )
EMIT_COMPLEX_FUNDCAST_TEST( double             )
EMIT_COMPLEX_FUNDCAST_TEST( long double        )
#undef EMIT_COMPLEX_FUNDCAST_TEST
