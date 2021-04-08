#pragma once

// Explicit conversions from stdlib and user-defined types to representative
// fundamental types, typically for passing to low-level APIs


#include <chrono>
#include <complex>
#include <tuple>        // tuple, tuple_cat
#include <type_traits>  // enable_if_t, is_fundamental_v, void_t, true_type,
                        //      false_type, declval, is_same_v, decay_t
#include <utility>      // declval


#ifdef __cpp_concepts // Concepts-based implementation /////////////////////////
namespace JadeMatrix::meta
{
    // This should really be in the standard library
    template< typename T > concept fundamental = std::is_fundamental_v< T >;
    
    template< typename T > concept fundamental_arithmetic = (
        std::is_fundamental_v< T >
        && !std::is_same_v< T, bool >
    );
    
    template< fundamental T > constexpr auto fundamental_cast( T v )
    {
        return std::tuple< T >{ v };
    }
}
#else // Non-concepts implementation ///////////////////////////////////////////
namespace JadeMatrix::meta
{
    template< typename T > constexpr auto fundamental_cast( T v ) ->
        std::enable_if_t< std::is_fundamental_v< T >, std::tuple< T > >
    {
        return { v };
    }
}
#endif


namespace JadeMatrix::meta // std::chrono::duration overload ///////////////////
{
    template<
        typename Rep,
        typename Period
    > constexpr auto fundamental_cast( std::chrono::duration< Rep, Period > v )
    {
        return fundamental_cast( v.count() );
    }
}


namespace JadeMatrix::meta // std::complex overload ////////////////////////////
{
    template<
        typename T
    > constexpr auto fundamental_cast( std::complex< T > const & v )
    {
        return std::tuple_cat(
            fundamental_cast( v.real() ),
            fundamental_cast( v.imag() )
        );
    }
}


namespace JadeMatrix::meta // Castability detection ////////////////////////////
{
    // This comes last so it picks up the overloads for types not in the
    // `JadeMatrix::meta` namespace
    
    template<
        typename T,
        typename = void
    > struct has_fundamental_cast : std::false_type {};
    
    template<
        typename T
    > constexpr auto has_fundamental_cast_v = has_fundamental_cast< T >::value;
    
    template< typename T > struct has_fundamental_cast<
        T,
        std::void_t< decltype( fundamental_cast( std::declval< T >() ) ) >
    > : std::true_type {};
    
    #ifdef __cpp_concepts
    template<
        typename T
    > concept fundamental_castable = has_fundamental_cast_v< T >;
    #endif
}
