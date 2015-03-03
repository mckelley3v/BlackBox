#include "m1/numeric/round.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::round", "[m1][m1::numeric]")
{
    using m1::round;

    CHECK(round(-6.8f) == Approx(-7.0f));
    CHECK(round(-6.5f) == Approx(-6.0f));
    CHECK(round(-6.2f) == Approx(-6.0f));
    CHECK(round(-6.0f) == Approx(-6.0f));
    CHECK(round(-5.8f) == Approx(-6.0f));
    CHECK(round(-5.5f) == Approx(-5.0f));
    CHECK(round(-5.2f) == Approx(-5.0f));
    CHECK(round(-5.0f) == Approx(-5.0f));
    CHECK(round(-4.8f) == Approx(-5.0f));
    CHECK(round(-4.5f) == Approx(-4.0f));
    CHECK(round(-4.2f) == Approx(-4.0f));
    CHECK(round(-4.0f) == Approx(-4.0f));
    CHECK(round(-3.8f) == Approx(-4.0f));
    CHECK(round(-3.5f) == Approx(-3.0f));
    CHECK(round(-3.2f) == Approx(-3.0f));
    CHECK(round(-3.0f) == Approx(-3.0f));
    CHECK(round(-2.8f) == Approx(-3.0f));
    CHECK(round(-2.5f) == Approx(-2.0f));
    CHECK(round(-2.2f) == Approx(-2.0f));
    CHECK(round(-2.0f) == Approx(-2.0f));
    CHECK(round(-1.8f) == Approx(-2.0f));
    CHECK(round(-1.5f) == Approx(-1.0f));
    CHECK(round(-1.2f) == Approx(-1.0f));
    CHECK(round(-1.0f) == Approx(-1.0f));
    CHECK(round(-0.8f) == Approx(-1.0f));
    CHECK(round(-0.5f) == Approx( 0.0f));
    CHECK(round(-0.2f) == Approx( 0.0f));
    CHECK(round( 0.0f) == Approx( 0.0f));
    CHECK(round(+0.2f) == Approx( 0.0f));
    CHECK(round(+0.5f) == Approx(+1.0f));
    CHECK(round(+0.8f) == Approx(+1.0f));
    CHECK(round(+1.0f) == Approx(+1.0f));
    CHECK(round(+1.2f) == Approx(+1.0f));
    CHECK(round(+1.5f) == Approx(+2.0f));
    CHECK(round(+1.8f) == Approx(+2.0f));
    CHECK(round(+2.0f) == Approx(+2.0f));
    CHECK(round(+2.2f) == Approx(+2.0f));
    CHECK(round(+2.5f) == Approx(+3.0f));
    CHECK(round(+2.8f) == Approx(+3.0f));
    CHECK(round(+3.0f) == Approx(+3.0f));
    CHECK(round(+3.2f) == Approx(+3.0f));
    CHECK(round(+3.5f) == Approx(+4.0f));
    CHECK(round(+3.8f) == Approx(+4.0f));
    CHECK(round(+4.0f) == Approx(+4.0f));
    CHECK(round(+4.2f) == Approx(+4.0f));
    CHECK(round(+4.5f) == Approx(+5.0f));
    CHECK(round(+4.8f) == Approx(+5.0f));
    CHECK(round(+5.0f) == Approx(+5.0f));
    CHECK(round(+5.2f) == Approx(+5.0f));
    CHECK(round(+5.5f) == Approx(+6.0f));
    CHECK(round(+5.8f) == Approx(+6.0f));
    CHECK(round(+6.0f) == Approx(+6.0f));
    CHECK(round(+6.2f) == Approx(+6.0f));
    CHECK(round(+6.5f) == Approx(+7.0f));
    CHECK(round(+6.8f) == Approx(+7.0f));
}
