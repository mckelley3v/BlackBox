#include "m1/numeric/smooth_step.hpp"
#include "m1/numeric/is_close.hpp"
#include <cassert>

bool test_smooth_step()
{
    using m1::smooth_step;
    using m1::is_close;

    assert(is_close(smooth_step(-1.5f, +2.5f, -2.0f), 0.0f));
    assert(is_close(smooth_step(-1.5f, +2.5f, -1.5f), 0.0f));
    assert(is_close(smooth_step(-1.5f, +2.5f, -1.0f), 0.04296875f));
    assert(is_close(smooth_step(-1.5f, +2.5f, -0.5f), 0.15625f));
    assert(is_close(smooth_step(-1.5f, +2.5f,  0.0f), 0.31640625f));
    assert(is_close(smooth_step(-1.5f, +2.5f, +0.5f), 0.5f));
    assert(is_close(smooth_step(-1.5f, +2.5f, +1.0f), 0.68359375f));
    assert(is_close(smooth_step(-1.5f, +2.5f, +1.5f), 0.84375f));
    assert(is_close(smooth_step(-1.5f, +2.5f, +2.0f), 0.95703125f));
    assert(is_close(smooth_step(-1.5f, +2.5f, +2.5f), 1.0f));
    assert(is_close(smooth_step(-1.5f, +2.5f, +3.0f), 1.0f));

    assert(is_close(smooth_step(-1.5, +2.5, -2.0), 0.0));
    assert(is_close(smooth_step(-1.5, +2.5, -1.5), 0.0));
    assert(is_close(smooth_step(-1.5, +2.5, -1.0), 0.04296875));
    assert(is_close(smooth_step(-1.5, +2.5, -0.5), 0.15625));
    assert(is_close(smooth_step(-1.5, +2.5,  0.0), 0.31640625));
    assert(is_close(smooth_step(-1.5, +2.5, +0.5), 0.5));
    assert(is_close(smooth_step(-1.5, +2.5, +1.0), 0.68359375));
    assert(is_close(smooth_step(-1.5, +2.5, +1.5), 0.84375));
    assert(is_close(smooth_step(-1.5, +2.5, +2.0), 0.95703125));
    assert(is_close(smooth_step(-1.5, +2.5, +2.5), 1.0));
    assert(is_close(smooth_step(-1.5, +2.5, +3.0), 1.0));

    return true;
}
