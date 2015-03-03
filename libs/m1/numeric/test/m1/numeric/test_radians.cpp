#include "m1/numeric/radians.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::radians", "[m1][m1::numeric]")
{
    using m1::radians;
    float const two_pi = 6.283185307179586476925286766559f;

    CHECK(radians(   0.0f) == Approx(two_pi *  0.0f / 24.0f));
    CHECK(radians( +15.0f) == Approx(two_pi *  1.0f / 24.0f));
    CHECK(radians( +30.0f) == Approx(two_pi *  2.0f / 24.0f));
    CHECK(radians( +45.0f) == Approx(two_pi *  3.0f / 24.0f));
    CHECK(radians( +60.0f) == Approx(two_pi *  4.0f / 24.0f));
    CHECK(radians( +75.0f) == Approx(two_pi *  5.0f / 24.0f));
    CHECK(radians( +90.0f) == Approx(two_pi *  6.0f / 24.0f));
    CHECK(radians(+105.0f) == Approx(two_pi *  7.0f / 24.0f));
    CHECK(radians(+120.0f) == Approx(two_pi *  8.0f / 24.0f));
    CHECK(radians(+135.0f) == Approx(two_pi *  9.0f / 24.0f));
    CHECK(radians(+150.0f) == Approx(two_pi * 10.0f / 24.0f));
    CHECK(radians(+165.0f) == Approx(two_pi * 11.0f / 24.0f));
    CHECK(radians(+180.0f) == Approx(two_pi * 12.0f / 24.0f));
    CHECK(radians(+195.0f) == Approx(two_pi * 13.0f / 24.0f));
    CHECK(radians(+210.0f) == Approx(two_pi * 14.0f / 24.0f));
    CHECK(radians(+225.0f) == Approx(two_pi * 15.0f / 24.0f));
    CHECK(radians(+240.0f) == Approx(two_pi * 16.0f / 24.0f));
    CHECK(radians(+255.0f) == Approx(two_pi * 17.0f / 24.0f));
    CHECK(radians(+270.0f) == Approx(two_pi * 18.0f / 24.0f));
    CHECK(radians(+285.0f) == Approx(two_pi * 19.0f / 24.0f));
    CHECK(radians(+300.0f) == Approx(two_pi * 20.0f / 24.0f));
    CHECK(radians(+315.0f) == Approx(two_pi * 21.0f / 24.0f));
    CHECK(radians(+330.0f) == Approx(two_pi * 22.0f / 24.0f));
    CHECK(radians(+345.0f) == Approx(two_pi * 23.0f / 24.0f));
    CHECK(radians(+360.0f) == Approx(two_pi * 24.0f / 24.0f));
}
