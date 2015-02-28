#include "m1/numeric/round.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_round()
{
    using m1::round;
    using m1::is_close;

    assert(is_close(round(-6.8f), -7.0f));
    assert(is_close(round(-6.5f), -6.0f));
    assert(is_close(round(-6.2f), -6.0f));
    assert(is_close(round(-6.0f), -6.0f));
    assert(is_close(round(-5.8f), -6.0f));
    assert(is_close(round(-5.5f), -5.0f));
    assert(is_close(round(-5.2f), -5.0f));
    assert(is_close(round(-5.0f), -5.0f));
    assert(is_close(round(-4.8f), -5.0f));
    assert(is_close(round(-4.5f), -4.0f));
    assert(is_close(round(-4.2f), -4.0f));
    assert(is_close(round(-4.0f), -4.0f));
    assert(is_close(round(-3.8f), -4.0f));
    assert(is_close(round(-3.5f), -3.0f));
    assert(is_close(round(-3.2f), -3.0f));
    assert(is_close(round(-3.0f), -3.0f));
    assert(is_close(round(-2.8f), -3.0f));
    assert(is_close(round(-2.5f), -2.0f));
    assert(is_close(round(-2.2f), -2.0f));
    assert(is_close(round(-2.0f), -2.0f));
    assert(is_close(round(-1.8f), -2.0f));
    assert(is_close(round(-1.5f), -1.0f));
    assert(is_close(round(-1.2f), -1.0f));
    assert(is_close(round(-1.0f), -1.0f));
    assert(is_close(round(-0.8f), -1.0f));
    assert(is_close(round(-0.5f),  0.0f));
    assert(is_close(round(-0.2f),  0.0f));
    assert(is_close(round( 0.0f),  0.0f));
    assert(is_close(round(+0.2f),  0.0f));
    assert(is_close(round(+0.5f), +1.0f));
    assert(is_close(round(+0.8f), +1.0f));
    assert(is_close(round(+1.0f), +1.0f));
    assert(is_close(round(+1.2f), +1.0f));
    assert(is_close(round(+1.5f), +2.0f));
    assert(is_close(round(+1.8f), +2.0f));
    assert(is_close(round(+2.0f), +2.0f));
    assert(is_close(round(+2.2f), +2.0f));
    assert(is_close(round(+2.5f), +3.0f));
    assert(is_close(round(+2.8f), +3.0f));
    assert(is_close(round(+3.0f), +3.0f));
    assert(is_close(round(+3.2f), +3.0f));
    assert(is_close(round(+3.5f), +4.0f));
    assert(is_close(round(+3.8f), +4.0f));
    assert(is_close(round(+4.0f), +4.0f));
    assert(is_close(round(+4.2f), +4.0f));
    assert(is_close(round(+4.5f), +5.0f));
    assert(is_close(round(+4.8f), +5.0f));
    assert(is_close(round(+5.0f), +5.0f));
    assert(is_close(round(+5.2f), +5.0f));
    assert(is_close(round(+5.5f), +6.0f));
    assert(is_close(round(+5.8f), +6.0f));
    assert(is_close(round(+6.0f), +6.0f));
    assert(is_close(round(+6.2f), +6.0f));
    assert(is_close(round(+6.5f), +7.0f));
    assert(is_close(round(+6.8f), +7.0f));

    return true;
}
