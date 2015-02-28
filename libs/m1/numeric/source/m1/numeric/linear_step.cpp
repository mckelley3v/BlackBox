#include "m1/numeric/linear_step.hpp"
#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/saturate.hpp"

// =====================================================================================================================

// ---------------------------------------------------------------------------------------------------------------------

float m1::linear_step(float const edge0,
                      float const edge1,
                      float const x)
{
    return saturate(inverse_lerp(edge0, edge1, x));
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::linear_step(double const edge0,
                       double const edge1,
                       double const x)
{
    return saturate(inverse_lerp(edge0, edge1, x));
}

// =====================================================================================================================
