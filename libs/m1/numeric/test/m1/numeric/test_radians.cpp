#include "m1/numeric/radians.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_radians()
{
    using m1::radians;
    using m1::is_close;
    float const two_pi = 6.283185307179586476925286766559f;

    assert(is_close(radians(   0.0f),  two_pi * 0.0f / 24.0f));
    assert(is_close(radians( +15.0f),  two_pi * 1.0f / 24.0f));
    assert(is_close(radians( +30.0f),  two_pi * 2.0f / 24.0f));
    assert(is_close(radians( +45.0f),  two_pi * 3.0f / 24.0f));
    assert(is_close(radians( +60.0f),  two_pi * 4.0f / 24.0f));
    assert(is_close(radians( +75.0f),  two_pi * 5.0f / 24.0f));
    assert(is_close(radians( +90.0f),  two_pi * 6.0f / 24.0f));
    assert(is_close(radians(+105.0f),  two_pi * 7.0f / 24.0f));
    assert(is_close(radians(+120.0f),  two_pi * 8.0f / 24.0f));
    assert(is_close(radians(+135.0f),  two_pi * 9.0f / 24.0f));
    assert(is_close(radians(+150.0f), two_pi * 10.0f / 24.0f));
    assert(is_close(radians(+165.0f), two_pi * 11.0f / 24.0f));
    assert(is_close(radians(+180.0f), two_pi * 12.0f / 24.0f));
    assert(is_close(radians(+195.0f), two_pi * 13.0f / 24.0f));
    assert(is_close(radians(+210.0f), two_pi * 14.0f / 24.0f));
    assert(is_close(radians(+225.0f), two_pi * 15.0f / 24.0f));
    assert(is_close(radians(+240.0f), two_pi * 16.0f / 24.0f));
    assert(is_close(radians(+255.0f), two_pi * 17.0f / 24.0f));
    assert(is_close(radians(+270.0f), two_pi * 18.0f / 24.0f));
    assert(is_close(radians(+285.0f), two_pi * 19.0f / 24.0f));
    assert(is_close(radians(+300.0f), two_pi * 20.0f / 24.0f));
    assert(is_close(radians(+315.0f), two_pi * 21.0f / 24.0f));
    assert(is_close(radians(+330.0f), two_pi * 22.0f / 24.0f));
    assert(is_close(radians(+345.0f), two_pi * 23.0f / 24.0f));
    assert(is_close(radians(+360.0f), two_pi * 24.0f / 24.0f));

    return true;
}
