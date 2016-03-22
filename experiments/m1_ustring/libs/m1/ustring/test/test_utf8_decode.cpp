#include "m1/utf8_decode.hpp"
#include "m1/pragma_message.hpp"
#include "utf8_test_data.hpp"
#include "catch.hpp"
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

TEST_CASE("Test m1::utf8_decode", "[m1]")
{
    SECTION("utf8_decode_each -- test::utf8_test_data")
    {
        #pragma M1_MESSAGE("change to char32_t and u32string, this is a workaround for VS 2015 linker error")
        std::wstring_convert<std::codecvt_utf8<std::uint32_t>, std::uint32_t> utf32conv;
        std::basic_string<std::uint32_t> const utf32_test_data = utf32conv.from_bytes(reinterpret_cast<char const*>(test::utf8_test_data.begin()),
                                                                                      reinterpret_cast<char const*>(test::utf8_test_data.end()));

        std::vector<m1::code_point> utf32_decode;
        m1::utf8_decode_copy(test::utf8_test_data.begin(),
                             test::utf8_test_data.end(),
                             std::back_inserter(utf32_decode));

        CHECK(std::equal(utf32_decode.begin(), utf32_decode.end(),
                         utf32_test_data.begin(), utf32_test_data.end()));
    }
}
