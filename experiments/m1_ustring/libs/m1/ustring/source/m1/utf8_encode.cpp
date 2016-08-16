#include "m1/utf8_encode.hpp"

// ====================================================================================================================

std::size_t m1::utf8_encode_size(code_point const ch)
{
    if(ch < 0x80) // 00000 00000000 0xxxxxxx
    {
        return 1;
    }
    else if(ch < 0x800) // 00000 00000yyy yxxxxxxx
    {
        return 2;
    }
    else if(ch < 0x10000) // 00000 zzzzzyyy yxxxxxxx
    {
        return 3;
    }
    else if(ch < 0x110000) // uuuuu zzzzzyyy yxxxxxxx
    {
        return 4;
    }
    else
    {
        // invalid: utf8_encode_next will append error_unit
        return 1;
    }
}

// ====================================================================================================================
