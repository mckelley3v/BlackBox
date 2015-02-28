#include "m1/numeric/mix.hpp"
#include "m1/numeric/lerp.hpp"
#include "m1/numeric/saturate.hpp"

// =====================================================================================================================

float m1::mix(float const x0,
              float const x1,
              float const t)
{
    return lerp(x0, x1, saturate(t));
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::mix(double const x0,
               double const x1,
               double const t)
{
    return lerp(x0, x1, saturate(t));
}

// =====================================================================================================================
