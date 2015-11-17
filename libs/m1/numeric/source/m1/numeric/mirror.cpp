#include "m1/numeric/mirror.hpp"
#include "m1/numeric/abs.hpp"
#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/lerp.hpp"
#include "m1/numeric/floor.hpp"
#include <cassert>

// =====================================================================================================================

float m1::mirror(float const x) noexcept
{
    return abs(2.0f * (0.5f * x - floor(0.5f * x + 0.5f)));
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::mirror(double const x) noexcept
{
    return abs(2.0 * (0.5 * x - floor(0.5 * x + 0.5)));
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::mirror(float const value,
                 float const min_value,
                 float const max_value) noexcept
{
    assert(min_value < max_value);
    float const t = inverse_lerp(min_value, max_value, value);
    float const s = mirror(t);
    return lerp(min_value, max_value, s);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::mirror(double const value,
                  double const min_value,
                  double const max_value) noexcept
{
    assert(min_value < max_value);
    double const t = inverse_lerp(min_value, max_value, value);
    double const s = mirror(t);
    return lerp(min_value, max_value, s);
}

// =====================================================================================================================
