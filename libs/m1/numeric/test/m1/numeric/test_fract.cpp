#include "m1/numeric/fract.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::fract", "[m1][m1::numeric]")
{
    using m1::fract;

    CHECK(fract(-6.8f) == Approx(0.2f));
    CHECK(fract(-6.5f) == Approx(0.5f));
    CHECK(fract(-6.2f) == Approx(0.8f));
    CHECK(fract(-6.0f) == Approx(0.0f));
    CHECK(fract(-5.8f) == Approx(0.2f));
    CHECK(fract(-5.5f) == Approx(0.5f));
    CHECK(fract(-5.2f) == Approx(0.8f));
    CHECK(fract(-5.0f) == Approx(0.0f));
    CHECK(fract(-4.8f) == Approx(0.2f));
    CHECK(fract(-4.5f) == Approx(0.5f));
    CHECK(fract(-4.2f) == Approx(0.8f));
    CHECK(fract(-4.0f) == Approx(0.0f));
    CHECK(fract(-3.8f) == Approx(0.2f));
    CHECK(fract(-3.5f) == Approx(0.5f));
    CHECK(fract(-3.2f) == Approx(0.8f));
    CHECK(fract(-3.0f) == Approx(0.0f));
    CHECK(fract(-2.8f) == Approx(0.2f));
    CHECK(fract(-2.5f) == Approx(0.5f));
    CHECK(fract(-2.2f) == Approx(0.8f));
    CHECK(fract(-2.0f) == Approx(0.0f));
    CHECK(fract(-1.8f) == Approx(0.2f));
    CHECK(fract(-1.5f) == Approx(0.5f));
    CHECK(fract(-1.2f) == Approx(0.8f));
    CHECK(fract(-1.0f) == Approx(0.0f));
    CHECK(fract(-0.8f) == Approx(0.2f));
    CHECK(fract(-0.5f) == Approx(0.5f));
    CHECK(fract(-0.2f) == Approx(0.8f));
    CHECK(fract( 0.0f) == Approx(0.0f));
    CHECK(fract(+0.2f) == Approx(0.2f));
    CHECK(fract(+0.5f) == Approx(0.5f));
    CHECK(fract(+0.8f) == Approx(0.8f));
    CHECK(fract(+1.0f) == Approx(0.0f));
    CHECK(fract(+1.2f) == Approx(0.2f));
    CHECK(fract(+1.5f) == Approx(0.5f));
    CHECK(fract(+1.8f) == Approx(0.8f));
    CHECK(fract(+2.0f) == Approx(0.0f));
    CHECK(fract(+2.2f) == Approx(0.2f));
    CHECK(fract(+2.5f) == Approx(0.5f));
    CHECK(fract(+2.8f) == Approx(0.8f));
    CHECK(fract(+3.0f) == Approx(0.0f));
    CHECK(fract(+3.2f) == Approx(0.2f));
    CHECK(fract(+3.5f) == Approx(0.5f));
    CHECK(fract(+3.8f) == Approx(0.8f));
    CHECK(fract(+4.0f) == Approx(0.0f));
    CHECK(fract(+4.2f) == Approx(0.2f));
    CHECK(fract(+4.5f) == Approx(0.5f));
    CHECK(fract(+4.8f) == Approx(0.8f));
    CHECK(fract(+5.0f) == Approx(0.0f));
    CHECK(fract(+5.2f) == Approx(0.2f));
    CHECK(fract(+5.5f) == Approx(0.5f));
    CHECK(fract(+5.8f) == Approx(0.8f));
    CHECK(fract(+6.0f) == Approx(0.0f));
    CHECK(fract(+6.2f) == Approx(0.2f));
    CHECK(fract(+6.5f) == Approx(0.5f));
    CHECK(fract(+6.8f) == Approx(0.8f));
}
