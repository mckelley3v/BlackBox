#include "m1/ustring.hpp"
#include "m1/pragma_message.hpp"
#include "utf8_test_data.hpp"
#include "catch.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

bool compare_code_points(m1::ustring const &str,
                         std::initializer_list<m1::code_point> const &code_points)
{
    return std::equal(str.begin(), str.end(),
                      code_points.begin(), code_points.end());
}

template <std::size_t N>
bool compare_code_points(m1::ustring const &str,
                         m1::code_point const (&code_points)[N])
{
    return std::equal(str.begin(), str.end(),
                      std::begin(code_points), std::end(code_points) - 1);
}

TEST_CASE("Test m1::ustring", "[m1]")
{
    SECTION("literals")
    {
        using namespace m1::literals;

        CHECK(compare_code_points("asdf"_us, U"asdf"));

        char const c_str[] = "qwerty";
        CHECK(m1::make_ustring_view(c_str).data() == c_str);
        CHECK(compare_code_points(m1::make_ustring_view(c_str), U"qwerty"));

        wchar_t const w_str[] = L"qwerty";
        CHECK(m1::make_ustring_view(w_str).data() == w_str);
        CHECK(compare_code_points(m1::make_ustring_view(w_str), U"qwerty"));

        char32_t const u32_str[] = U"qwerty";
        CHECK(m1::make_ustring_view(u32_str).data() == u32_str);
        CHECK(compare_code_points(m1::make_ustring_view(u32_str), U"qwerty"));
    }

    m1::ustring const s0(m1::ascii_encoding_default, "The quick brown fox jumped over the lazy dog");
    CHECK(compare_code_points(s0, U"The quick brown fox jumped over the lazy dog"));

    SECTION("test::utf8_test_data")
    {
        m1::ustring const ustr(m1::utf8_encoding_default,
                               test::utf8_test_data.begin(),
                               test::utf8_test_data.end());

        #pragma M1_MESSAGE("change to char32_t and u32string, this is a workaround for VS 2015 linker error")
        std::wstring_convert<std::codecvt_utf8<std::uint32_t>, std::uint32_t> utf32conv;
        std::basic_string<std::uint32_t> const utf32_test_data = utf32conv.from_bytes(reinterpret_cast<char const*>(test::utf8_test_data.begin()),
                                                                                      reinterpret_cast<char const*>(test::utf8_test_data.end()));

        CHECK(std::equal(ustr.begin(), ustr.end(),
                         utf32_test_data.begin(), utf32_test_data.end()));
    }
}
