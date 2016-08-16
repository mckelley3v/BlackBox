#include "m1/crc32.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::crc32", "[m1][m1::serialization]" )
{
    using m1::crc32;

    bool is_crc32_constexpr = false;
    switch(crc32("hello"))
    {
        case crc32("hello"):
            is_crc32_constexpr = true;
            break;

        case crc32("world"):
        default:
            is_crc32_constexpr = false;
            break;
    }

    static_assert(crc32("caracoles") == 0xF59A8C00, "CRC32 error");
    CHECK(is_crc32_constexpr);
}
