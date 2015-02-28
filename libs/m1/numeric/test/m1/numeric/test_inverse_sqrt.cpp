#include "m1/numeric/inverse_sqrt.hpp"
#include "m1/numeric/is_close.hpp"
#include "m1/numeric/sqrt.hpp"
#include <cassert>

bool test_inverse_sqrt()
{
    using m1::inverse_sqrt;
    using m1::sqrt;
    using m1::is_close;

    assert(is_close(inverse_sqrt(  1.0f), 1.0f / sqrt(  1.0f)));
    assert(is_close(inverse_sqrt(  4.0f), 1.0f / sqrt(  4.0f)));
    assert(is_close(inverse_sqrt(  9.0f), 1.0f / sqrt(  9.0f)));
    assert(is_close(inverse_sqrt( 16.0f), 1.0f / sqrt( 16.0f)));
    assert(is_close(inverse_sqrt( 25.0f), 1.0f / sqrt( 25.0f)));
    assert(is_close(inverse_sqrt( 36.0f), 1.0f / sqrt( 36.0f)));
    assert(is_close(inverse_sqrt( 49.0f), 1.0f / sqrt( 49.0f)));
    assert(is_close(inverse_sqrt( 64.0f), 1.0f / sqrt( 64.0f)));
    assert(is_close(inverse_sqrt( 81.0f), 1.0f / sqrt( 81.0f)));
    assert(is_close(inverse_sqrt(100.0f), 1.0f / sqrt(100.0f)));

    assert(is_close(inverse_sqrt(  1.0), 1.0 / sqrt(  1.0)));
    assert(is_close(inverse_sqrt(  4.0), 1.0 / sqrt(  4.0)));
    assert(is_close(inverse_sqrt(  9.0), 1.0 / sqrt(  9.0)));
    assert(is_close(inverse_sqrt( 16.0), 1.0 / sqrt( 16.0)));
    assert(is_close(inverse_sqrt( 25.0), 1.0 / sqrt( 25.0)));
    assert(is_close(inverse_sqrt( 36.0), 1.0 / sqrt( 36.0)));
    assert(is_close(inverse_sqrt( 49.0), 1.0 / sqrt( 49.0)));
    assert(is_close(inverse_sqrt( 64.0), 1.0 / sqrt( 64.0)));
    assert(is_close(inverse_sqrt( 81.0), 1.0 / sqrt( 81.0)));
    assert(is_close(inverse_sqrt(100.0), 1.0 / sqrt(100.0)));

    return true;
}
