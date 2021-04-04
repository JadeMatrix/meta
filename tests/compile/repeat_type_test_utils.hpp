#include <meta/repeat_type.hpp>

#include <utility>  // make_index_sequence

namespace
{
    struct type_convertible_to_foo final {};
    
    struct foo final
    {
        constexpr foo() = default;
        constexpr foo( type_convertible_to_foo const & ) {}
    };
    
    template< typename Sequence > struct bar;
    template< std::size_t... Is > struct bar< std::index_sequence< Is... > >
    {
        constexpr void function(
            JadeMatrix::meta::repeat_type< foo, Is > const &...
        )
        {}
    };
    
    using bar_4 = bar< std::make_index_sequence< 4 > >;
}
