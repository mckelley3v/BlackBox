#include "m1/numeric/smooth_step.hpp"
#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/saturate.hpp"

// =====================================================================================================================

float m1::smooth_step(float const x)
{
    float const t = saturate(x);
    return t * t * (3.0f - 2.0f * t);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::smooth_step(double const x)
{
    double const t = saturate(x);
    return t * t * (3.0 - 2.0 * t);
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::smooth_step(float const edge0,
                      float const edge1,
                      float const x)
{
    float const t = inverse_lerp(edge0, edge1, x);
    return smooth_step(t);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::smooth_step(double const edge0,
                       double const edge1,
                       double const x)
{
    double const t = inverse_lerp(edge0, edge1, x);
    return smooth_step(t);
}

// =====================================================================================================================
