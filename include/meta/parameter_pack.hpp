#pragma once

// Utilities for capturing & re-using parameter packs
// TODO: reverse, split, join, shuffle, etc.


namespace JadeMatrix::meta
{
    template< typename... Ts > struct type_parameter_pack
    {
        constexpr static auto size = sizeof...( Ts );
        template<
            template< typename... > typename Wrapper
        > using wrapped_in = Wrapper< Ts... >;
    };
    
    template< auto... Vs > struct value_parameter_pack
    {
        constexpr static auto size = sizeof...( Vs );
        template<
            template< auto... > typename Wrapper
        > using wrapped_in = Wrapper< Vs... >;
    };
}
