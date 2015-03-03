#include "m1/numeric/repeat.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::repeat", "[m1][m1::numeric]")
{
    using m1::repeat;

    CHECK(repeat(-2.0f, -1.5f, +2.5f) == Approx(+2.0f));
    CHECK(repeat(-1.5f, -1.5f, +2.5f) == Approx(-1.5f));
    CHECK(repeat(-1.0f, -1.5f, +2.5f) == Approx(-1.0f));
    CHECK(repeat(-0.5f, -1.5f, +2.5f) == Approx(-0.5f));
    CHECK(repeat( 0.0f, -1.5f, +2.5f) == Approx( 0.0f));
    CHECK(repeat(+0.5f, -1.5f, +2.5f) == Approx(+0.5f));
    CHECK(repeat(+1.0f, -1.5f, +2.5f) == Approx(+1.0f));
    CHECK(repeat(+1.5f, -1.5f, +2.5f) == Approx(+1.5f));
    CHECK(repeat(+2.0f, -1.5f, +2.5f) == Approx(+2.0f));
    CHECK(repeat(+2.5f, -1.5f, +2.5f) == Approx(-1.5f));
    CHECK(repeat(+3.0f, -1.5f, +2.5f) == Approx(-1.0f));
    CHECK(repeat(+3.5f, -1.5f, +2.5f) == Approx(-0.5f));

    CHECK(repeat(-2.0, -1.5, +2.5) == Approx(+2.0));
    CHECK(repeat(-1.5, -1.5, +2.5) == Approx(-1.5));
    CHECK(repeat(-1.0, -1.5, +2.5) == Approx(-1.0));
    CHECK(repeat(-0.5, -1.5, +2.5) == Approx(-0.5));
    CHECK(repeat( 0.0, -1.5, +2.5) == Approx( 0.0));
    CHECK(repeat(+0.5, -1.5, +2.5) == Approx(+0.5));
    CHECK(repeat(+1.0, -1.5, +2.5) == Approx(+1.0));
    CHECK(repeat(+1.5, -1.5, +2.5) == Approx(+1.5));
    CHECK(repeat(+2.0, -1.5, +2.5) == Approx(+2.0));
    CHECK(repeat(+2.5, -1.5, +2.5) == Approx(-1.5));
    CHECK(repeat(+3.0, -1.5, +2.5) == Approx(-1.0));
    CHECK(repeat(+3.5, -1.5, +2.5) == Approx(-0.5));
}
