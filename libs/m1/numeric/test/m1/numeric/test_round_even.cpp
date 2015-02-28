#include "m1/numeric/round_even.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_round_even()
{
    using m1::round_even;
    using m1::is_close;

    assert(is_close(round_even(-6.8f), -7.0f));
    assert(is_close(round_even(-6.5f), -6.0f));
    assert(is_close(round_even(-6.2f), -6.0f));
    assert(is_close(round_even(-6.0f), -6.0f));
    assert(is_close(round_even(-5.8f), -6.0f));
    assert(is_close(round_even(-5.5f), -6.0f));
    assert(is_close(round_even(-5.2f), -5.0f));
    assert(is_close(round_even(-5.0f), -5.0f));
    assert(is_close(round_even(-4.8f), -5.0f));
    assert(is_close(round_even(-4.5f), -4.0f));
    assert(is_close(round_even(-4.2f), -4.0f));
    assert(is_close(round_even(-4.0f), -4.0f));
    assert(is_close(round_even(-3.8f), -4.0f));
    assert(is_close(round_even(-3.5f), -4.0f));
    assert(is_close(round_even(-3.2f), -3.0f));
    assert(is_close(round_even(-3.0f), -3.0f));
    assert(is_close(round_even(-2.8f), -3.0f));
    assert(is_close(round_even(-2.5f), -2.0f));
    assert(is_close(round_even(-2.2f), -2.0f));
    assert(is_close(round_even(-2.0f), -2.0f));
    assert(is_close(round_even(-1.8f), -2.0f));
    assert(is_close(round_even(-1.5f), -2.0f));
    assert(is_close(round_even(-1.2f), -1.0f));
    assert(is_close(round_even(-1.0f), -1.0f));
    assert(is_close(round_even(-0.8f), -1.0f));
    assert(is_close(round_even(-0.5f),  0.0f));
    assert(is_close(round_even(-0.2f),  0.0f));
    assert(is_close(round_even( 0.0f),  0.0f));
    assert(is_close(round_even(+0.2f),  0.0f));
    assert(is_close(round_even(+0.5f),  0.0f));
    assert(is_close(round_even(+0.8f), +1.0f));
    assert(is_close(round_even(+1.0f), +1.0f));
    assert(is_close(round_even(+1.2f), +1.0f));
    assert(is_close(round_even(+1.5f), +2.0f));
    assert(is_close(round_even(+1.8f), +2.0f));
    assert(is_close(round_even(+2.0f), +2.0f));
    assert(is_close(round_even(+2.2f), +2.0f));
    assert(is_close(round_even(+2.5f), +2.0f));
    assert(is_close(round_even(+2.8f), +3.0f));
    assert(is_close(round_even(+3.0f), +3.0f));
    assert(is_close(round_even(+3.2f), +3.0f));
    assert(is_close(round_even(+3.5f), +4.0f));
    assert(is_close(round_even(+3.8f), +4.0f));
    assert(is_close(round_even(+4.0f), +4.0f));
    assert(is_close(round_even(+4.2f), +4.0f));
    assert(is_close(round_even(+4.5f), +4.0f));
    assert(is_close(round_even(+4.8f), +5.0f));
    assert(is_close(round_even(+5.0f), +5.0f));
    assert(is_close(round_even(+5.2f), +5.0f));
    assert(is_close(round_even(+5.5f), +6.0f));
    assert(is_close(round_even(+5.8f), +6.0f));
    assert(is_close(round_even(+6.0f), +6.0f));
    assert(is_close(round_even(+6.2f), +6.0f));
    assert(is_close(round_even(+6.5f), +6.0f));
    assert(is_close(round_even(+6.8f), +7.0f));

    return true;
}
