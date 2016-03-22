#include "m1/byte_order.hpp"
#include "m1/byte_order_iterator.hpp"
#include "array_size.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::byte_order", "[m1]")
{
    static_assert(m1::native_byte_order() == m1::byte_order::little_endian, "little_endian");
    static_assert(m1::swap_byte_order(char16_t('AB')) == 'BA', "swap_byte_order");
    static_assert(m1::swap_byte_order(char32_t('ABCD')) == 'DCBA', "swap_byte_order");
    static_assert(m1::swap_byte_order(std::uint16_t('AB')) == 'BA', "swap_byte_order");
    static_assert(m1::swap_byte_order(std::uint32_t('ABCD')) == 'DCBA', "swap_byte_order");

    char16_t const utf16le[] = {0x007a,          // latin small letter 'z' U+007a
                                0x6c34,          // CJK ideograph "water"  U+6c34
                                0xd834, 0xdd0b}; // musical sign segno U+1d10b
    {
        char16_t const *p = utf16le;
        for(auto itr = m1::make_little_endian_iterator(utf16le + 0),
                 end = m1::make_little_endian_iterator(utf16le + m1::array_size(utf16le));
            itr != end;
            ++itr)
        {
            CHECK(*itr == m1::little_endian(*p++));
        }
    }

    {
        char16_t const *p = utf16le;
        for(auto itr = m1::make_big_endian_iterator(utf16le + 0),
                 end = m1::make_big_endian_iterator(utf16le + m1::array_size(utf16le));
            itr != end;
            ++itr)
        {
            CHECK(*itr == m1::big_endian(*p++));
        }
    }
}
