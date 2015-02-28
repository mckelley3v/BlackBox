#include "m1/numeric/degrees.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_degrees()
{
    using m1::degrees;
    using m1::is_close;
    float const two_pi = 6.283185307179586476925286766559f;

    assert(is_close(degrees( two_pi * 0.0f / 24.0f),    0.0f));
    assert(is_close(degrees( two_pi * 1.0f / 24.0f),  +15.0f));
    assert(is_close(degrees( two_pi * 2.0f / 24.0f),  +30.0f));
    assert(is_close(degrees( two_pi * 3.0f / 24.0f),  +45.0f));
    assert(is_close(degrees( two_pi * 4.0f / 24.0f),  +60.0f));
    assert(is_close(degrees( two_pi * 5.0f / 24.0f),  +75.0f));
    assert(is_close(degrees( two_pi * 6.0f / 24.0f),  +90.0f));
    assert(is_close(degrees( two_pi * 7.0f / 24.0f), +105.0f));
    assert(is_close(degrees( two_pi * 8.0f / 24.0f), +120.0f));
    assert(is_close(degrees( two_pi * 9.0f / 24.0f), +135.0f));
    assert(is_close(degrees(two_pi * 10.0f / 24.0f), +150.0f));
    assert(is_close(degrees(two_pi * 11.0f / 24.0f), +165.0f));
    assert(is_close(degrees(two_pi * 12.0f / 24.0f), +180.0f));
    assert(is_close(degrees(two_pi * 13.0f / 24.0f), +195.0f));
    assert(is_close(degrees(two_pi * 14.0f / 24.0f), +210.0f));
    assert(is_close(degrees(two_pi * 15.0f / 24.0f), +225.0f));
    assert(is_close(degrees(two_pi * 16.0f / 24.0f), +240.0f));
    assert(is_close(degrees(two_pi * 17.0f / 24.0f), +255.0f));
    assert(is_close(degrees(two_pi * 18.0f / 24.0f), +270.0f));
    assert(is_close(degrees(two_pi * 19.0f / 24.0f), +285.0f));
    assert(is_close(degrees(two_pi * 20.0f / 24.0f), +300.0f));
    assert(is_close(degrees(two_pi * 21.0f / 24.0f), +315.0f));
    assert(is_close(degrees(two_pi * 22.0f / 24.0f), +330.0f));
    assert(is_close(degrees(two_pi * 23.0f / 24.0f), +345.0f));
    assert(is_close(degrees(two_pi * 24.0f / 24.0f), +360.0f));

    return true;
}
