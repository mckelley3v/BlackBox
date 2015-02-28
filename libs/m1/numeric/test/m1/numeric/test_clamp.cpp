#include "m1/numeric/clamp.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_clamp()
{
    using m1::clamp;
    using m1::is_close;

    assert(is_close(clamp(-2.0f, -1.5f, +2.5f), -1.5f));
    assert(is_close(clamp(-1.5f, -1.5f, +2.5f), -1.5f));
    assert(is_close(clamp(-1.0f, -1.5f, +2.5f), -1.0f));
    assert(is_close(clamp(-0.5f, -1.5f, +2.5f), -0.5f));
    assert(is_close(clamp( 0.0f, -1.5f, +2.5f),  0.0f));
    assert(is_close(clamp(+0.5f, -1.5f, +2.5f), +0.5f));
    assert(is_close(clamp(+1.0f, -1.5f, +2.5f), +1.0f));
    assert(is_close(clamp(+1.5f, -1.5f, +2.5f), +1.5f));
    assert(is_close(clamp(+2.0f, -1.5f, +2.5f), +2.0f));
    assert(is_close(clamp(+2.5f, -1.5f, +2.5f), +2.5f));
    assert(is_close(clamp(+3.0f, -1.5f, +2.5f), +2.5f));
    assert(is_close(clamp(+3.5f, -1.5f, +2.5f), +2.5f));

    assert(is_close(clamp(-2.0, -1.5, +2.5), -1.5));
    assert(is_close(clamp(-1.5, -1.5, +2.5), -1.5));
    assert(is_close(clamp(-1.0, -1.5, +2.5), -1.0));
    assert(is_close(clamp(-0.5, -1.5, +2.5), -0.5));
    assert(is_close(clamp( 0.0, -1.5, +2.5),  0.0));
    assert(is_close(clamp(+0.5, -1.5, +2.5), +0.5));
    assert(is_close(clamp(+1.0, -1.5, +2.5), +1.0));
    assert(is_close(clamp(+1.5, -1.5, +2.5), +1.5));
    assert(is_close(clamp(+2.0, -1.5, +2.5), +2.0));
    assert(is_close(clamp(+2.5, -1.5, +2.5), +2.5));
    assert(is_close(clamp(+3.0, -1.5, +2.5), +2.5));
    assert(is_close(clamp(+3.5, -1.5, +2.5), +2.5));

    return true;
}
