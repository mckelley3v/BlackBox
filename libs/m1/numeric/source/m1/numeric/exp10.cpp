#include "m1/numeric/exp10.hpp"
#include <cmath>

// =====================================================================================================================

float m1::exp10(float const x)
{
    return std::pow(10.0f, x);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::exp10(double const x)
{
    return std::pow(10.0, x);
}

// =====================================================================================================================
