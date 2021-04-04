#pragma once


#include <type_traits>  // __cpp_lib_is_constant_evaluated,
                        //      is_constant_evaluated


// Attempt to use or emulate `std::is_constant_evaluated()` in as many compile
// configurations as possible
#if defined( __cpp_lib_is_constant_evaluated )
    #define JM_META_IF_CONSTANT_EVALUATED() if( std::is_constant_evaluated() )
#elif defined( __GNUG__ ) && __has_builtin( __builtin_is_constant_evaluated )
    // `__has_builtin()` is a GCC/Clang feature (`__GNUG__` works for both GCC &
    // Clang)
    #define JM_META_IF_CONSTANT_EVALUATED() \
        if( __builtin_is_constant_evaluated() )
#else // TODO: There may be more fallbacks we can use on other compilers
    #define JM_META_IF_CONSTANT_EVALUATED() if constexpr( true )
#endif
