#include "m1/numeric/degrees.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::degrees", "[m1][m1::numeric]")
{
    using m1::degrees;
    float const two_pi = 6.283185307179586476925286766559f;

    CHECK(degrees(two_pi *  0.0f / 24.0f) == Approx(   0.0f));
    CHECK(degrees(two_pi *  1.0f / 24.0f) == Approx( 15.0f));
    CHECK(degrees(two_pi *  2.0f / 24.0f) == Approx( 30.0f));
    CHECK(degrees(two_pi *  3.0f / 24.0f) == Approx( 45.0f));
    CHECK(degrees(two_pi *  4.0f / 24.0f) == Approx( 60.0f));
    CHECK(degrees(two_pi *  5.0f / 24.0f) == Approx( 75.0f));
    CHECK(degrees(two_pi *  6.0f / 24.0f) == Approx( 90.0f));
    CHECK(degrees(two_pi *  7.0f / 24.0f) == Approx(105.0f));
    CHECK(degrees(two_pi *  8.0f / 24.0f) == Approx(120.0f));
    CHECK(degrees(two_pi *  9.0f / 24.0f) == Approx(135.0f));
    CHECK(degrees(two_pi * 10.0f / 24.0f) == Approx(150.0f));
    CHECK(degrees(two_pi * 11.0f / 24.0f) == Approx(165.0f));
    CHECK(degrees(two_pi * 12.0f / 24.0f) == Approx(180.0f));
    CHECK(degrees(two_pi * 13.0f / 24.0f) == Approx(195.0f));
    CHECK(degrees(two_pi * 14.0f / 24.0f) == Approx(210.0f));
    CHECK(degrees(two_pi * 15.0f / 24.0f) == Approx(225.0f));
    CHECK(degrees(two_pi * 16.0f / 24.0f) == Approx(240.0f));
    CHECK(degrees(two_pi * 17.0f / 24.0f) == Approx(255.0f));
    CHECK(degrees(two_pi * 18.0f / 24.0f) == Approx(270.0f));
    CHECK(degrees(two_pi * 19.0f / 24.0f) == Approx(285.0f));
    CHECK(degrees(two_pi * 20.0f / 24.0f) == Approx(300.0f));
    CHECK(degrees(two_pi * 21.0f / 24.0f) == Approx(315.0f));
    CHECK(degrees(two_pi * 22.0f / 24.0f) == Approx(330.0f));
    CHECK(degrees(two_pi * 23.0f / 24.0f) == Approx(345.0f));
    CHECK(degrees(two_pi * 24.0f / 24.0f) == Approx(360.0f));
}
