#include "m1/numeric/lerp.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::lerp", "[m1][m1::numeric]")
{
    using m1::lerp;

    CHECK(lerp(0.0f, 1.0f, -0.1f) == Approx(-0.1f));
    CHECK(lerp(0.0f, 1.0f,  0.0f) == Approx( 0.0f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
    CHECK(lerp(0.0f, 1.0f, +0.1f) == Approx(+0.1f));
}
