#include "m1/utf32_decode.hpp"
#include "array_size.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::utf32_decode", "[m1]")
{
    SECTION("consume_utf32_byte_order_mark")
    {
        char const utf32be_bytes[] = "\x00\x00\xFE\xFF";
        char const utf32le_bytes[] = "\xFF\xFE\x00\x00";
        static_assert(m1::array_size(utf32be_bytes) == 5, "Expected char[5]");
        static_assert(m1::array_size(utf32le_bytes) == 5, "Expected char[5]");

        char32_t const * const utf32be_str = reinterpret_cast<char32_t const*>(utf32be_bytes);
        char32_t const * const utf32le_str = reinterpret_cast<char32_t const*>(utf32le_bytes);

        char32_t const *utf32be_ptr = utf32be_str;
        char32_t const *utf32le_ptr = utf32le_str;

        CHECK(m1::consume_utf32_byte_order_mark(utf32be_ptr, utf32be_str + m1::array_size(utf32be_bytes) / sizeof(char32_t)) == m1::byte_order::big_endian);
        CHECK(m1::consume_utf32_byte_order_mark(utf32le_ptr, utf32le_str + m1::array_size(utf32le_bytes) / sizeof(char32_t)) == m1::byte_order::little_endian);

        CHECK(utf32be_ptr == utf32be_str + 1);
        CHECK(utf32le_ptr == utf32le_str + 1);
    }
}
