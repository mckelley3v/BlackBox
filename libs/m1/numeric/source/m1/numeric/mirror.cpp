#include "m1/numeric/mirror.hpp"
#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/lerp.hpp"
#include <cmath>
#include <cassert>

// =====================================================================================================================

float m1::mirror(float const x)
{
    return std::abs(2.0f * (0.5f * x - std::floor(0.5f * x + 0.5f)));
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::mirror(double const x)
{
    return std::abs(2.0 * (0.5 * x - std::floor(0.5 * x + 0.5)));
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::mirror(float const value,
                 float const min_value,
                 float const max_value)
{
    assert(min_value < max_value);
    float const t = inverse_lerp(min_value, max_value, value);
    float const s = mirror(t);
    return lerp(min_value, max_value, s);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::mirror(const double value, const double min_value, const double max_value)
{
    assert(min_value < max_value);
    const double t = inverse_lerp(min_value, max_value, value);
    const double s = mirror(t);
    return lerp(min_value, max_value, s);
}

// =====================================================================================================================
