#include "m1/numeric/clamp.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::clamp", "[m1][m1::numeric]")
{
    using m1::clamp;

    CHECK(clamp(-2.0f, -1.5f, +2.5f) == Approx(-1.5f));
    CHECK(clamp(-1.5f, -1.5f, +2.5f) == Approx(-1.5f));
    CHECK(clamp(-1.0f, -1.5f, +2.5f) == Approx(-1.0f));
    CHECK(clamp(-0.5f, -1.5f, +2.5f) == Approx(-0.5f));
    CHECK(clamp( 0.0f, -1.5f, +2.5f) == Approx( 0.0f));
    CHECK(clamp(+0.5f, -1.5f, +2.5f) == Approx(+0.5f));
    CHECK(clamp(+1.0f, -1.5f, +2.5f) == Approx(+1.0f));
    CHECK(clamp(+1.5f, -1.5f, +2.5f) == Approx(+1.5f));
    CHECK(clamp(+2.0f, -1.5f, +2.5f) == Approx(+2.0f));
    CHECK(clamp(+2.5f, -1.5f, +2.5f) == Approx(+2.5f));
    CHECK(clamp(+3.0f, -1.5f, +2.5f) == Approx(+2.5f));
    CHECK(clamp(+3.5f, -1.5f, +2.5f) == Approx(+2.5f));

    CHECK(clamp(-2.0, -1.5, +2.5) == Approx(-1.5));
    CHECK(clamp(-1.5, -1.5, +2.5) == Approx(-1.5));
    CHECK(clamp(-1.0, -1.5, +2.5) == Approx(-1.0));
    CHECK(clamp(-0.5, -1.5, +2.5) == Approx(-0.5));
    CHECK(clamp( 0.0, -1.5, +2.5) == Approx( 0.0));
    CHECK(clamp(+0.5, -1.5, +2.5) == Approx(+0.5));
    CHECK(clamp(+1.0, -1.5, +2.5) == Approx(+1.0));
    CHECK(clamp(+1.5, -1.5, +2.5) == Approx(+1.5));
    CHECK(clamp(+2.0, -1.5, +2.5) == Approx(+2.0));
    CHECK(clamp(+2.5, -1.5, +2.5) == Approx(+2.5));
    CHECK(clamp(+3.0, -1.5, +2.5) == Approx(+2.5));
    CHECK(clamp(+3.5, -1.5, +2.5) == Approx(+2.5));
}
