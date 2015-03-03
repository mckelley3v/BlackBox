#include "m1/numeric/mirror.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::mirror", "[m1][m1::numeric]")
{
    using m1::mirror;

    CHECK(mirror(-2.0f, -1.5f, +2.5f) == Approx(-1.0f));
    CHECK(mirror(-1.5f, -1.5f, +2.5f) == Approx(-1.5f));
    CHECK(mirror(-1.0f, -1.5f, +2.5f) == Approx(-1.0f));
    CHECK(mirror(-0.5f, -1.5f, +2.5f) == Approx(-0.5f));
    CHECK(mirror( 0.0f, -1.5f, +2.5f) == Approx( 0.0f));
    CHECK(mirror(+0.5f, -1.5f, +2.5f) == Approx(+0.5f));
    CHECK(mirror(+1.0f, -1.5f, +2.5f) == Approx(+1.0f));
    CHECK(mirror(+1.5f, -1.5f, +2.5f) == Approx(+1.5f));
    CHECK(mirror(+2.0f, -1.5f, +2.5f) == Approx(+2.0f));
    CHECK(mirror(+2.5f, -1.5f, +2.5f) == Approx(+2.5f));
    CHECK(mirror(+3.0f, -1.5f, +2.5f) == Approx(+2.0f));
    CHECK(mirror(+3.5f, -1.5f, +2.5f) == Approx(+1.5f));

    CHECK(mirror(-2.0, -1.5, +2.5) == Approx(-1.0));
    CHECK(mirror(-1.5, -1.5, +2.5) == Approx(-1.5));
    CHECK(mirror(-1.0, -1.5, +2.5) == Approx(-1.0));
    CHECK(mirror(-0.5, -1.5, +2.5) == Approx(-0.5));
    CHECK(mirror( 0.0, -1.5, +2.5) == Approx( 0.0));
    CHECK(mirror(+0.5, -1.5, +2.5) == Approx(+0.5));
    CHECK(mirror(+1.0, -1.5, +2.5) == Approx(+1.0));
    CHECK(mirror(+1.5, -1.5, +2.5) == Approx(+1.5));
    CHECK(mirror(+2.0, -1.5, +2.5) == Approx(+2.0));
    CHECK(mirror(+2.5, -1.5, +2.5) == Approx(+2.5));
    CHECK(mirror(+3.0, -1.5, +2.5) == Approx(+2.0));
    CHECK(mirror(+3.5, -1.5, +2.5) == Approx(+1.5));
}
