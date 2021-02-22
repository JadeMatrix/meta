#pragma once


namespace JadeMatrix::meta
{
    // Alias of a type T for use with non-type parameter packs deduced from
    // std::integer_sequence.
    template< typename T, auto > using repeat_type = T;
}
