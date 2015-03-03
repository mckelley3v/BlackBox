#include "m1/numeric/step.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::step", "[m1][m1::numeric]")
{
    using m1::step;

    CHECK(step(0.5f, -2.0f) == Approx(0.0f));
    CHECK(step(0.5f, -1.5f) == Approx(0.0f));
    CHECK(step(0.5f, -1.0f) == Approx(0.0f));
    CHECK(step(0.5f, -0.5f) == Approx(0.0f));
    CHECK(step(0.5f,  0.0f) == Approx(0.0f));
    CHECK(step(0.5f, +0.5f) == Approx(1.0f));
    CHECK(step(0.5f, +1.0f) == Approx(1.0f));
    CHECK(step(0.5f, +1.5f) == Approx(1.0f));
    CHECK(step(0.5f, +2.0f) == Approx(1.0f));
    CHECK(step(0.5f, +2.5f) == Approx(1.0f));
    CHECK(step(0.5f, +3.0f) == Approx(1.0f));

    CHECK(step(0.5, -2.0) == Approx(0.0));
    CHECK(step(0.5, -1.5) == Approx(0.0));
    CHECK(step(0.5, -1.0) == Approx(0.0));
    CHECK(step(0.5, -0.5) == Approx(0.0));
    CHECK(step(0.5,  0.0) == Approx(0.0));
    CHECK(step(0.5, +0.5) == Approx(1.0));
    CHECK(step(0.5, +1.0) == Approx(1.0));
    CHECK(step(0.5, +1.5) == Approx(1.0));
    CHECK(step(0.5, +2.0) == Approx(1.0));
    CHECK(step(0.5, +2.5) == Approx(1.0));
    CHECK(step(0.5, +3.0) == Approx(1.0));
}
