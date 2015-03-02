#include "m1/numeric/inverse_lerp.hpp"
#include <cassert>

// =====================================================================================================================

float m1::inverse_lerp(float const x0,
                       float const x1,
                       float const x)
{
    assert(x0 < x1);
    return (x - x0) / (x1 - x0);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::inverse_lerp(double const x0,
                        double const x1,
                        double const x)
{
    assert(x0 < x1);
    return (x - x0) / (x1 - x0);
}

// =====================================================================================================================