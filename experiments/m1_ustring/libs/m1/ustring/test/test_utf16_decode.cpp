#include "m1/utf16_decode.hpp"
#include "m1/pragma_message.hpp"
#include "utf8_test_data.hpp"
#include "array_size.hpp"
#include "catch.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

bool test_utf16(std::initializer_list<char16_t> const &code_units,
                std::initializer_list<char32_t> const &code_points)
{
    std::vector<char32_t> result;
    m1::utf16_decode_copy(code_units.begin(),
                          code_units.end(),
                          std::back_inserter(result));

    return std::equal(result.begin(), result.end(),
                      code_points.begin(), code_points.end());
}

TEST_CASE("Test m1::utf16_decode", "[m1]")
{
    SECTION("consume_utf16_byte_order_mark")
    {
        char const utf16be_bytes[] = "\xFE\xFF";
        char const utf16le_bytes[] = "\xFF\xFE";
        static_assert(m1::array_size(utf16be_bytes) == 3, "Expected char[3]");
        static_assert(m1::array_size(utf16le_bytes) == 3, "Expected char[3]");

        char16_t const * const utf16be_str = reinterpret_cast<char16_t const*>(utf16be_bytes);
        char16_t const * const utf16le_str = reinterpret_cast<char16_t const*>(utf16le_bytes);

        char16_t const *utf16be_ptr = utf16be_str;
        char16_t const *utf16le_ptr = utf16le_str;

        CHECK(m1::consume_utf16_byte_order_mark(utf16be_ptr, utf16be_str + m1::array_size(utf16be_bytes) / sizeof(char16_t)) == m1::byte_order::big_endian);
        CHECK(m1::consume_utf16_byte_order_mark(utf16le_ptr, utf16le_str + m1::array_size(utf16le_bytes) / sizeof(char16_t)) == m1::byte_order::little_endian);

        CHECK(utf16be_ptr == utf16be_str + 1);
        CHECK(utf16le_ptr == utf16le_str + 1);
    }

    SECTION("utf16_decode_each")
    {
        constexpr char32_t const replacement_char = U'\xFFFD';

        CHECK(test_utf16(// code_units
                         {u'\x007A',
                          u'\x6C34',
                          u'\xD834', u'\xDD0B'},
                         // code_points
                         {U'\x007A',     // latin small letter 'z'
                          U'\x6C34',     // CJK ideograph "water"
                          U'\x1D10B'})); // musical sign segno

        CHECK(test_utf16(// code_units
                         {u'\xDC00',
                          u'\x20AC',
                          u'\xD841', u'\x0061',
                          u'\x0061',
                          u'\xD841', u'\xDC02',
                          u'\xD842', u'\xDC06',
                          u'\x0000',
                          u'\xD842', u'\xD7FF',
                          u'\xD7FF',
                          u'\xDC41',
                          u'\xE000',
                          u'\xD800'},
                         // code_points
                         {replacement_char,
                          U'\x020AC',
                          replacement_char,
                          U'\x00061',
                          U'\x20402',
                          U'\x20806',
                          U'\x00000',
                          replacement_char,
                          U'\x0D7FF',
                          replacement_char,
                          U'\x0E000',
                          replacement_char}));
    }

    SECTION("utf16_decode_each -- test::utf8_test_data")
    {
        #pragma M1_MESSAGE("change to char16_t/char32_t and u16string/u32string, this is a workaround for VS 2015 linker error")
        std::wstring_convert<std::codecvt_utf8_utf16<std::uint16_t>, std::uint16_t> utf16conv;
        std::basic_string<std::uint16_t> const utf16_test_data = utf16conv.from_bytes(reinterpret_cast<char const*>(test::utf8_test_data.begin()),
                                                                                      reinterpret_cast<char const*>(test::utf8_test_data.end()));

        std::wstring_convert<std::codecvt_utf8<std::uint32_t>, std::uint32_t> utf32conv;
        std::basic_string<std::uint32_t> const utf32_test_data = utf32conv.from_bytes(reinterpret_cast<char const*>(test::utf8_test_data.begin()),
                                                                                      reinterpret_cast<char const*>(test::utf8_test_data.end()));

        std::vector<m1::code_point> utf16_decode;
        m1::utf16_decode_copy(utf16_test_data.begin(),
                              utf16_test_data.end(),
                              std::back_inserter(utf16_decode));

        CHECK(std::equal(utf16_decode.begin(), utf16_decode.end(),
                         utf32_test_data.begin(), utf32_test_data.end()));
    }
}
