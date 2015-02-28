#include "m1/numeric/trunc.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_trunc()
{
    using m1::trunc;
    using m1::is_close;

    assert(is_close(trunc(-6.8f), -6.0f));
    assert(is_close(trunc(-6.5f), -6.0f));
    assert(is_close(trunc(-6.2f), -6.0f));
    assert(is_close(trunc(-6.0f), -6.0f));
    assert(is_close(trunc(-5.8f), -5.0f));
    assert(is_close(trunc(-5.5f), -5.0f));
    assert(is_close(trunc(-5.2f), -5.0f));
    assert(is_close(trunc(-5.0f), -5.0f));
    assert(is_close(trunc(-4.8f), -4.0f));
    assert(is_close(trunc(-4.5f), -4.0f));
    assert(is_close(trunc(-4.2f), -4.0f));
    assert(is_close(trunc(-4.0f), -4.0f));
    assert(is_close(trunc(-3.8f), -3.0f));
    assert(is_close(trunc(-3.5f), -3.0f));
    assert(is_close(trunc(-3.2f), -3.0f));
    assert(is_close(trunc(-3.0f), -3.0f));
    assert(is_close(trunc(-2.8f), -2.0f));
    assert(is_close(trunc(-2.5f), -2.0f));
    assert(is_close(trunc(-2.2f), -2.0f));
    assert(is_close(trunc(-2.0f), -2.0f));
    assert(is_close(trunc(-1.8f), -1.0f));
    assert(is_close(trunc(-1.5f), -1.0f));
    assert(is_close(trunc(-1.2f), -1.0f));
    assert(is_close(trunc(-1.0f), -1.0f));
    assert(is_close(trunc(-0.8f),  0.0f));
    assert(is_close(trunc(-0.5f),  0.0f));
    assert(is_close(trunc(-0.2f),  0.0f));
    assert(is_close(trunc( 0.0f),  0.0f));
    assert(is_close(trunc(+0.2f),  0.0f));
    assert(is_close(trunc(+0.5f),  0.0f));
    assert(is_close(trunc(+0.8f),  0.0f));
    assert(is_close(trunc(+1.0f), +1.0f));
    assert(is_close(trunc(+1.2f), +1.0f));
    assert(is_close(trunc(+1.5f), +1.0f));
    assert(is_close(trunc(+1.8f), +1.0f));
    assert(is_close(trunc(+2.0f), +2.0f));
    assert(is_close(trunc(+2.2f), +2.0f));
    assert(is_close(trunc(+2.5f), +2.0f));
    assert(is_close(trunc(+2.8f), +2.0f));
    assert(is_close(trunc(+3.0f), +3.0f));
    assert(is_close(trunc(+3.2f), +3.0f));
    assert(is_close(trunc(+3.5f), +3.0f));
    assert(is_close(trunc(+3.8f), +3.0f));
    assert(is_close(trunc(+4.0f), +4.0f));
    assert(is_close(trunc(+4.2f), +4.0f));
    assert(is_close(trunc(+4.5f), +4.0f));
    assert(is_close(trunc(+4.8f), +4.0f));
    assert(is_close(trunc(+5.0f), +5.0f));
    assert(is_close(trunc(+5.2f), +5.0f));
    assert(is_close(trunc(+5.5f), +5.0f));
    assert(is_close(trunc(+5.8f), +5.0f));
    assert(is_close(trunc(+6.0f), +6.0f));
    assert(is_close(trunc(+6.2f), +6.0f));
    assert(is_close(trunc(+6.5f), +6.0f));
    assert(is_close(trunc(+6.8f), +6.0f));

    assert(is_close(trunc(-6.8), -6.0));
    assert(is_close(trunc(-6.5), -6.0));
    assert(is_close(trunc(-6.2), -6.0));
    assert(is_close(trunc(-6.0), -6.0));
    assert(is_close(trunc(-5.8), -5.0));
    assert(is_close(trunc(-5.5), -5.0));
    assert(is_close(trunc(-5.2), -5.0));
    assert(is_close(trunc(-5.0), -5.0));
    assert(is_close(trunc(-4.8), -4.0));
    assert(is_close(trunc(-4.5), -4.0));
    assert(is_close(trunc(-4.2), -4.0));
    assert(is_close(trunc(-4.0), -4.0));
    assert(is_close(trunc(-3.8), -3.0));
    assert(is_close(trunc(-3.5), -3.0));
    assert(is_close(trunc(-3.2), -3.0));
    assert(is_close(trunc(-3.0), -3.0));
    assert(is_close(trunc(-2.8), -2.0));
    assert(is_close(trunc(-2.5), -2.0));
    assert(is_close(trunc(-2.2), -2.0));
    assert(is_close(trunc(-2.0), -2.0));
    assert(is_close(trunc(-1.8), -1.0));
    assert(is_close(trunc(-1.5), -1.0));
    assert(is_close(trunc(-1.2), -1.0));
    assert(is_close(trunc(-1.0), -1.0));
    assert(is_close(trunc(-0.8),  0.0));
    assert(is_close(trunc(-0.5),  0.0));
    assert(is_close(trunc(-0.2),  0.0));
    assert(is_close(trunc( 0.0),  0.0));
    assert(is_close(trunc(+0.2),  0.0));
    assert(is_close(trunc(+0.5),  0.0));
    assert(is_close(trunc(+0.8),  0.0));
    assert(is_close(trunc(+1.0), +1.0));
    assert(is_close(trunc(+1.2), +1.0));
    assert(is_close(trunc(+1.5), +1.0));
    assert(is_close(trunc(+1.8), +1.0));
    assert(is_close(trunc(+2.0), +2.0));
    assert(is_close(trunc(+2.2), +2.0));
    assert(is_close(trunc(+2.5), +2.0));
    assert(is_close(trunc(+2.8), +2.0));
    assert(is_close(trunc(+3.0), +3.0));
    assert(is_close(trunc(+3.2), +3.0));
    assert(is_close(trunc(+3.5), +3.0));
    assert(is_close(trunc(+3.8), +3.0));
    assert(is_close(trunc(+4.0), +4.0));
    assert(is_close(trunc(+4.2), +4.0));
    assert(is_close(trunc(+4.5), +4.0));
    assert(is_close(trunc(+4.8), +4.0));
    assert(is_close(trunc(+5.0), +5.0));
    assert(is_close(trunc(+5.2), +5.0));
    assert(is_close(trunc(+5.5), +5.0));
    assert(is_close(trunc(+5.8), +5.0));
    assert(is_close(trunc(+6.0), +6.0));
    assert(is_close(trunc(+6.2), +6.0));
    assert(is_close(trunc(+6.5), +6.0));
    assert(is_close(trunc(+6.8), +6.0));

    return true;
}
