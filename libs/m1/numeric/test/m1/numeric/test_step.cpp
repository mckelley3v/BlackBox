#include "m1/numeric/step.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_step()
{
    using m1::step;
    using m1::is_close;

    assert(is_close(step(0.5f, -2.0f), 0.0f));
    assert(is_close(step(0.5f, -1.5f), 0.0f));
    assert(is_close(step(0.5f, -1.0f), 0.0f));
    assert(is_close(step(0.5f, -0.5f), 0.0f));
    assert(is_close(step(0.5f,  0.0f), 0.0f));
    assert(is_close(step(0.5f, +0.5f), 1.0f));
    assert(is_close(step(0.5f, +1.0f), 1.0f));
    assert(is_close(step(0.5f, +1.5f), 1.0f));
    assert(is_close(step(0.5f, +2.0f), 1.0f));
    assert(is_close(step(0.5f, +2.5f), 1.0f));
    assert(is_close(step(0.5f, +3.0f), 1.0f));

    assert(is_close(step(0.5, -2.0), 0.0));
    assert(is_close(step(0.5, -1.5), 0.0));
    assert(is_close(step(0.5, -1.0), 0.0));
    assert(is_close(step(0.5, -0.5), 0.0));
    assert(is_close(step(0.5,  0.0), 0.0));
    assert(is_close(step(0.5, +0.5), 1.0));
    assert(is_close(step(0.5, +1.0), 1.0));
    assert(is_close(step(0.5, +1.5), 1.0));
    assert(is_close(step(0.5, +2.0), 1.0));
    assert(is_close(step(0.5, +2.5), 1.0));
    assert(is_close(step(0.5, +3.0), 1.0));

    return true;
}
