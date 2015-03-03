#include "m1/numeric/smooth_step.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::smooth_step", "[m1][m1::numeric]")
{
    using m1::smooth_step;

    CHECK(smooth_step(-1.5f, +2.5f, -2.0f) == Approx(0.0f));
    CHECK(smooth_step(-1.5f, +2.5f, -1.5f) == Approx(0.0f));
    CHECK(smooth_step(-1.5f, +2.5f, -1.0f) == Approx(0.04296875f));
    CHECK(smooth_step(-1.5f, +2.5f, -0.5f) == Approx(0.15625f));
    CHECK(smooth_step(-1.5f, +2.5f,  0.0f) == Approx(0.31640625f));
    CHECK(smooth_step(-1.5f, +2.5f, +0.5f) == Approx(0.5f));
    CHECK(smooth_step(-1.5f, +2.5f, +1.0f) == Approx(0.68359375f));
    CHECK(smooth_step(-1.5f, +2.5f, +1.5f) == Approx(0.84375f));
    CHECK(smooth_step(-1.5f, +2.5f, +2.0f) == Approx(0.95703125f));
    CHECK(smooth_step(-1.5f, +2.5f, +2.5f) == Approx(1.0f));
    CHECK(smooth_step(-1.5f, +2.5f, +3.0f) == Approx(1.0f));

    CHECK(smooth_step(-1.5, +2.5, -2.0) == Approx(0.0));
    CHECK(smooth_step(-1.5, +2.5, -1.5) == Approx(0.0));
    CHECK(smooth_step(-1.5, +2.5, -1.0) == Approx(0.04296875));
    CHECK(smooth_step(-1.5, +2.5, -0.5) == Approx(0.15625));
    CHECK(smooth_step(-1.5, +2.5,  0.0) == Approx(0.31640625));
    CHECK(smooth_step(-1.5, +2.5, +0.5) == Approx(0.5));
    CHECK(smooth_step(-1.5, +2.5, +1.0) == Approx(0.68359375));
    CHECK(smooth_step(-1.5, +2.5, +1.5) == Approx(0.84375));
    CHECK(smooth_step(-1.5, +2.5, +2.0) == Approx(0.95703125));
    CHECK(smooth_step(-1.5, +2.5, +2.5) == Approx(1.0));
    CHECK(smooth_step(-1.5, +2.5, +3.0) == Approx(1.0));
}
