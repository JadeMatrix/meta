#pragma once


namespace JadeMatrix::meta
{
    // Undefined template struct used for producing compile-time errors that
    // report the parameter type
    template< typename > struct type_printer;
}
