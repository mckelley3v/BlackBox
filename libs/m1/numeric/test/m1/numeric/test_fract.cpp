#include "m1/numeric/fract.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_fract()
{
    using m1::fract;
    using m1::is_close;

    assert(is_close(fract(-6.8f), +0.2f));
    assert(is_close(fract(-6.5f), +0.5f));
    assert(is_close(fract(-6.2f), +0.8f));
    assert(is_close(fract(-6.0f),  0.0f));
    assert(is_close(fract(-5.8f), +0.2f));
    assert(is_close(fract(-5.5f), +0.5f));
    assert(is_close(fract(-5.2f), +0.8f));
    assert(is_close(fract(-5.0f),  0.0f));
    assert(is_close(fract(-4.8f), +0.2f));
    assert(is_close(fract(-4.5f), +0.5f));
    assert(is_close(fract(-4.2f), +0.8f));
    assert(is_close(fract(-4.0f),  0.0f));
    assert(is_close(fract(-3.8f), +0.2f));
    assert(is_close(fract(-3.5f), +0.5f));
    assert(is_close(fract(-3.2f), +0.8f));
    assert(is_close(fract(-3.0f),  0.0f));
    assert(is_close(fract(-2.8f), +0.2f));
    assert(is_close(fract(-2.5f), +0.5f));
    assert(is_close(fract(-2.2f), +0.8f));
    assert(is_close(fract(-2.0f),  0.0f));
    assert(is_close(fract(-1.8f), +0.2f));
    assert(is_close(fract(-1.5f), +0.5f));
    assert(is_close(fract(-1.2f), +0.8f));
    assert(is_close(fract(-1.0f),  0.0f));
    assert(is_close(fract(-0.8f), +0.2f));
    assert(is_close(fract(-0.5f), +0.5f));
    assert(is_close(fract(-0.2f), +0.8f));
    assert(is_close(fract( 0.0f),  0.0f));
    assert(is_close(fract(+0.2f), +0.2f));
    assert(is_close(fract(+0.5f), +0.5f));
    assert(is_close(fract(+0.8f), +0.8f));
    assert(is_close(fract(+1.0f),  0.0f));
    assert(is_close(fract(+1.2f), +0.2f));
    assert(is_close(fract(+1.5f), +0.5f));
    assert(is_close(fract(+1.8f), +0.8f));
    assert(is_close(fract(+2.0f),  0.0f));
    assert(is_close(fract(+2.2f), +0.2f));
    assert(is_close(fract(+2.5f), +0.5f));
    assert(is_close(fract(+2.8f), +0.8f));
    assert(is_close(fract(+3.0f),  0.0f));
    assert(is_close(fract(+3.2f), +0.2f));
    assert(is_close(fract(+3.5f), +0.5f));
    assert(is_close(fract(+3.8f), +0.8f));
    assert(is_close(fract(+4.0f),  0.0f));
    assert(is_close(fract(+4.2f), +0.2f));
    assert(is_close(fract(+4.5f), +0.5f));
    assert(is_close(fract(+4.8f), +0.8f));
    assert(is_close(fract(+5.0f),  0.0f));
    assert(is_close(fract(+5.2f), +0.2f));
    assert(is_close(fract(+5.5f), +0.5f));
    assert(is_close(fract(+5.8f), +0.8f));
    assert(is_close(fract(+6.0f),  0.0f));
    assert(is_close(fract(+6.2f), +0.2f));
    assert(is_close(fract(+6.5f), +0.5f));
    assert(is_close(fract(+6.8f), +0.8f));

    return true;
}
