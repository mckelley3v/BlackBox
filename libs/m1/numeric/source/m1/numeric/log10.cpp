#include "m1/numeric/log10.hpp"
#include <cmath>
#include <cassert>

// =====================================================================================================================

float m1::log10(float const x)
{
    assert(x > 0.0f);
    return std::log10(x);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::log10(double const x)
{
    assert(x > 0.0);
    return std::log10(x);
}

// =====================================================================================================================
