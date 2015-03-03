#include "m1/numeric/mod.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::mod", "[m1][m1::numeric]")
{
    using m1::mod;

    CHECK(mod(-9, 5) == 1);
    CHECK(mod(-8, 5) == 2);
    CHECK(mod(-7, 5) == 3);
    CHECK(mod(-6, 5) == 4);
    CHECK(mod(-5, 5) == 0);
    CHECK(mod(-4, 5) == 1);
    CHECK(mod(-3, 5) == 2);
    CHECK(mod(-2, 5) == 3);
    CHECK(mod(-1, 5) == 4);
    CHECK(mod( 0, 5) == 0);
    CHECK(mod( 1, 5) == 1);
    CHECK(mod( 2, 5) == 2);
    CHECK(mod( 3, 5) == 3);
    CHECK(mod( 4, 5) == 4);
    CHECK(mod( 5, 5) == 0);
    CHECK(mod( 6, 5) == 1);
    CHECK(mod( 7, 5) == 2);
    CHECK(mod( 8, 5) == 3);
    CHECK(mod( 9, 5) == 4);
}
