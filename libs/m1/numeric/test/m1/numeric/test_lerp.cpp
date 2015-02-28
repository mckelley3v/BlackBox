#include "m1/numeric/lerp.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_lerp()
{
    using m1::lerp;
    using m1::is_close;

    assert(is_close(lerp(0.0f, 1.0f, -0.1f), -0.1f));
    assert(is_close(lerp(0.0f, 1.0f,  0.0f),  0.0f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));
    assert(is_close(lerp(0.0f, 1.0f, +0.1f), +0.1f));

    return true;
}
