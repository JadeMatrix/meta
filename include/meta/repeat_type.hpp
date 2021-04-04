#pragma once


#include "parameter_pack.hpp"   // type_parameter_pack

#include <utility>  // integer_sequence


namespace JadeMatrix::meta
{
    // Alias of a type T for use with non-type parameter packs deduced from
    // std::integer_sequence.
    template< typename T, auto > using repeat_type = T;
    
    // A parameter pack of some number of Ts
    template< typename T, typename Sequence > struct repeat_type_pack;
    template<
        typename T,
        typename IdT,
        IdT... I
    > struct repeat_type_pack<
        T,
        std::integer_sequence< IdT, I... >
    > : type_parameter_pack< repeat_type< T, I >... > {};
    
    // Create a parameter pack of N Ts
    template<
        typename T,
        std::size_t N
    > using make_repeat_type_pack = repeat_type_pack<
        T,
        std::make_index_sequence< N >
    >;
}
