#include "m1/numeric/is_pow2.hpp"
#include <limits>
#include <cstdlib>
#include "catch.hpp"

TEST_CASE("Test m1::is_pow2", "[m1][m1::numeric]")
{
    using m1::is_pow2;

    // check all powers of two
    CHECK(!is_pow2(0));
    for(int i = 1; i < std::numeric_limits<int>::digits; ++i)
    {
        int const value = 1 << i;
        CHECK(is_pow2(value));
    }

    // check several non-power of two numbers (at least 2 bits set)
    for(int bits = 2; bits < std::numeric_limits<int>::digits; ++bits)
    {
        for(int i = 0; i < 100; ++i)
        {
            int random_value = 0;
            for(int b = 0; b < bits;)
            {
                int const d = std::rand() % std::numeric_limits<int>::digits;
                int const random_bit = (1 << d);
                if(!(random_value & random_bit))
                {
                    random_value |= random_bit;
                    ++b;
                }
            }

            CHECK(!is_pow2(random_value));
        }
    }
}
