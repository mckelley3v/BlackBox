#include "m1/crc32.hpp"

bool test_crc32()
{
    using m1::crc32;
    using m1::calc_crc32;

    bool result = false;
    switch(crc32("hello"))
    {
        case crc32("hello"):
            result = true;
            break;

        case crc32("world"):
        default:
            result = false;
            break;
    }

    static_assert(crc32("caracoles") == 0xF59A8C00, "CRC32 error");
    static_assert(calc_crc32("caracoles") == 0xF59A8C00, "CRC32 error");

    return result;
}
