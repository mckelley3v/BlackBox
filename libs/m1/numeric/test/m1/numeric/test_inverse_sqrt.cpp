#include "m1/numeric/inverse_sqrt.hpp"
#include "m1/numeric/sqrt.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::inverse_sqrt", "[m1][m1::numeric]")
{
    using m1::inverse_sqrt;

    CHECK(inverse_sqrt(  1.0f) == Approx(1.0f / sqrt(  1.0f)));
    CHECK(inverse_sqrt(  4.0f) == Approx(1.0f / sqrt(  4.0f)));
    CHECK(inverse_sqrt(  9.0f) == Approx(1.0f / sqrt(  9.0f)));
    CHECK(inverse_sqrt( 16.0f) == Approx(1.0f / sqrt( 16.0f)));
    CHECK(inverse_sqrt( 25.0f) == Approx(1.0f / sqrt( 25.0f)));
    CHECK(inverse_sqrt( 36.0f) == Approx(1.0f / sqrt( 36.0f)));
    CHECK(inverse_sqrt( 49.0f) == Approx(1.0f / sqrt( 49.0f)));
    CHECK(inverse_sqrt( 64.0f) == Approx(1.0f / sqrt( 64.0f)));
    CHECK(inverse_sqrt( 81.0f) == Approx(1.0f / sqrt( 81.0f)));
    CHECK(inverse_sqrt(100.0f) == Approx(1.0f / sqrt(100.0f)));

    CHECK(inverse_sqrt(  1.0) == Approx(1.0 / sqrt(  1.0)));
    CHECK(inverse_sqrt(  4.0) == Approx(1.0 / sqrt(  4.0)));
    CHECK(inverse_sqrt(  9.0) == Approx(1.0 / sqrt(  9.0)));
    CHECK(inverse_sqrt( 16.0) == Approx(1.0 / sqrt( 16.0)));
    CHECK(inverse_sqrt( 25.0) == Approx(1.0 / sqrt( 25.0)));
    CHECK(inverse_sqrt( 36.0) == Approx(1.0 / sqrt( 36.0)));
    CHECK(inverse_sqrt( 49.0) == Approx(1.0 / sqrt( 49.0)));
    CHECK(inverse_sqrt( 64.0) == Approx(1.0 / sqrt( 64.0)));
    CHECK(inverse_sqrt( 81.0) == Approx(1.0 / sqrt( 81.0)));
    CHECK(inverse_sqrt(100.0) == Approx(1.0 / sqrt(100.0)));
}
