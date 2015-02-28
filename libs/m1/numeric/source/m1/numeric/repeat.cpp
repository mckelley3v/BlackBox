#include "m1/numeric/repeat.hpp"
#include "m1/numeric/fract.hpp"
#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/lerp.hpp"
#include <cassert>

// =====================================================================================================================

float m1::repeat(float const value, float const min_value, float const max_value)
{
    assert(min_value < max_value);
    float const t = inverse_lerp(min_value, max_value, value);
    float const s = fract(t);
    return lerp(min_value, max_value, s);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::repeat(double const value, double const min_value, double const max_value)
{
    assert(min_value < max_value);
    double const t = inverse_lerp(min_value, max_value, value);
    double const s = fract(t);
    return lerp(min_value, max_value, s);
}

// =====================================================================================================================
