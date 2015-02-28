#include "m1/numeric/repeat.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_repeat()
{
    using m1::repeat;
    using m1::is_close;

    assert(is_close(repeat(-2.0f, -1.5f, +2.5f), +2.0f));
    assert(is_close(repeat(-1.5f, -1.5f, +2.5f), -1.5f));
    assert(is_close(repeat(-1.0f, -1.5f, +2.5f), -1.0f));
    assert(is_close(repeat(-0.5f, -1.5f, +2.5f), -0.5f));
    assert(is_close(repeat( 0.0f, -1.5f, +2.5f),  0.0f));
    assert(is_close(repeat(+0.5f, -1.5f, +2.5f), +0.5f));
    assert(is_close(repeat(+1.0f, -1.5f, +2.5f), +1.0f));
    assert(is_close(repeat(+1.5f, -1.5f, +2.5f), +1.5f));
    assert(is_close(repeat(+2.0f, -1.5f, +2.5f), +2.0f));
    assert(is_close(repeat(+2.5f, -1.5f, +2.5f), -1.5f));
    assert(is_close(repeat(+3.0f, -1.5f, +2.5f), -1.0f));
    assert(is_close(repeat(+3.5f, -1.5f, +2.5f), -0.5f));

    assert(is_close(repeat(-2.0, -1.5, +2.5), +2.0));
    assert(is_close(repeat(-1.5, -1.5, +2.5), -1.5));
    assert(is_close(repeat(-1.0, -1.5, +2.5), -1.0));
    assert(is_close(repeat(-0.5, -1.5, +2.5), -0.5));
    assert(is_close(repeat( 0.0, -1.5, +2.5),  0.0));
    assert(is_close(repeat(+0.5, -1.5, +2.5), +0.5));
    assert(is_close(repeat(+1.0, -1.5, +2.5), +1.0));
    assert(is_close(repeat(+1.5, -1.5, +2.5), +1.5));
    assert(is_close(repeat(+2.0, -1.5, +2.5), +2.0));
    assert(is_close(repeat(+2.5, -1.5, +2.5), -1.5));
    assert(is_close(repeat(+3.0, -1.5, +2.5), -1.0));
    assert(is_close(repeat(+3.5, -1.5, +2.5), -0.5));

    return true;
}
