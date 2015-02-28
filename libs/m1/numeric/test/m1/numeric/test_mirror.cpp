#include "m1/numeric/mirror.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_mirror()
{
    using m1::mirror;
    using m1::is_close;

    assert(is_close(mirror(-2.0f, -1.5f, +2.5f), -1.0f));
    assert(is_close(mirror(-1.5f, -1.5f, +2.5f), -1.5f));
    assert(is_close(mirror(-1.0f, -1.5f, +2.5f), -1.0f));
    assert(is_close(mirror(-0.5f, -1.5f, +2.5f), -0.5f));
    assert(is_close(mirror( 0.0f, -1.5f, +2.5f),  0.0f));
    assert(is_close(mirror(+0.5f, -1.5f, +2.5f), +0.5f));
    assert(is_close(mirror(+1.0f, -1.5f, +2.5f), +1.0f));
    assert(is_close(mirror(+1.5f, -1.5f, +2.5f), +1.5f));
    assert(is_close(mirror(+2.0f, -1.5f, +2.5f), +2.0f));
    assert(is_close(mirror(+2.5f, -1.5f, +2.5f), +2.5f));
    assert(is_close(mirror(+3.0f, -1.5f, +2.5f), +2.0f));
    assert(is_close(mirror(+3.5f, -1.5f, +2.5f), +1.5f));

    assert(is_close(mirror(-2.0, -1.5, +2.5), -1.0));
    assert(is_close(mirror(-1.5, -1.5, +2.5), -1.5));
    assert(is_close(mirror(-1.0, -1.5, +2.5), -1.0));
    assert(is_close(mirror(-0.5, -1.5, +2.5), -0.5));
    assert(is_close(mirror( 0.0, -1.5, +2.5),  0.0));
    assert(is_close(mirror(+0.5, -1.5, +2.5), +0.5));
    assert(is_close(mirror(+1.0, -1.5, +2.5), +1.0));
    assert(is_close(mirror(+1.5, -1.5, +2.5), +1.5));
    assert(is_close(mirror(+2.0, -1.5, +2.5), +2.0));
    assert(is_close(mirror(+2.5, -1.5, +2.5), +2.5));
    assert(is_close(mirror(+3.0, -1.5, +2.5), +2.0));
    assert(is_close(mirror(+3.5, -1.5, +2.5), +1.5));

    return true;
}
