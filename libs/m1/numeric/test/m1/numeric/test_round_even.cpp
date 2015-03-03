#include "m1/numeric/round_even.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::round_even", "[m1][m1::numeric]")
{
    using m1::round_even;

    CHECK(round_even(-6.8f) == Approx(-7.0f));
    CHECK(round_even(-6.5f) == Approx(-6.0f));
    CHECK(round_even(-6.2f) == Approx(-6.0f));
    CHECK(round_even(-6.0f) == Approx(-6.0f));
    CHECK(round_even(-5.8f) == Approx(-6.0f));
    CHECK(round_even(-5.5f) == Approx(-6.0f));
    CHECK(round_even(-5.2f) == Approx(-5.0f));
    CHECK(round_even(-5.0f) == Approx(-5.0f));
    CHECK(round_even(-4.8f) == Approx(-5.0f));
    CHECK(round_even(-4.5f) == Approx(-4.0f));
    CHECK(round_even(-4.2f) == Approx(-4.0f));
    CHECK(round_even(-4.0f) == Approx(-4.0f));
    CHECK(round_even(-3.8f) == Approx(-4.0f));
    CHECK(round_even(-3.5f) == Approx(-4.0f));
    CHECK(round_even(-3.2f) == Approx(-3.0f));
    CHECK(round_even(-3.0f) == Approx(-3.0f));
    CHECK(round_even(-2.8f) == Approx(-3.0f));
    CHECK(round_even(-2.5f) == Approx(-2.0f));
    CHECK(round_even(-2.2f) == Approx(-2.0f));
    CHECK(round_even(-2.0f) == Approx(-2.0f));
    CHECK(round_even(-1.8f) == Approx(-2.0f));
    CHECK(round_even(-1.5f) == Approx(-2.0f));
    CHECK(round_even(-1.2f) == Approx(-1.0f));
    CHECK(round_even(-1.0f) == Approx(-1.0f));
    CHECK(round_even(-0.8f) == Approx(-1.0f));
    CHECK(round_even(-0.5f) == Approx( 0.0f));
    CHECK(round_even(-0.2f) == Approx( 0.0f));
    CHECK(round_even( 0.0f) == Approx( 0.0f));
    CHECK(round_even(+0.2f) == Approx( 0.0f));
    CHECK(round_even(+0.5f) == Approx( 0.0f));
    CHECK(round_even(+0.8f) == Approx(+1.0f));
    CHECK(round_even(+1.0f) == Approx(+1.0f));
    CHECK(round_even(+1.2f) == Approx(+1.0f));
    CHECK(round_even(+1.5f) == Approx(+2.0f));
    CHECK(round_even(+1.8f) == Approx(+2.0f));
    CHECK(round_even(+2.0f) == Approx(+2.0f));
    CHECK(round_even(+2.2f) == Approx(+2.0f));
    CHECK(round_even(+2.5f) == Approx(+2.0f));
    CHECK(round_even(+2.8f) == Approx(+3.0f));
    CHECK(round_even(+3.0f) == Approx(+3.0f));
    CHECK(round_even(+3.2f) == Approx(+3.0f));
    CHECK(round_even(+3.5f) == Approx(+4.0f));
    CHECK(round_even(+3.8f) == Approx(+4.0f));
    CHECK(round_even(+4.0f) == Approx(+4.0f));
    CHECK(round_even(+4.2f) == Approx(+4.0f));
    CHECK(round_even(+4.5f) == Approx(+4.0f));
    CHECK(round_even(+4.8f) == Approx(+5.0f));
    CHECK(round_even(+5.0f) == Approx(+5.0f));
    CHECK(round_even(+5.2f) == Approx(+5.0f));
    CHECK(round_even(+5.5f) == Approx(+6.0f));
    CHECK(round_even(+5.8f) == Approx(+6.0f));
    CHECK(round_even(+6.0f) == Approx(+6.0f));
    CHECK(round_even(+6.2f) == Approx(+6.0f));
    CHECK(round_even(+6.5f) == Approx(+6.0f));
    CHECK(round_even(+6.8f) == Approx(+7.0f));
}
