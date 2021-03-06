#include "m1/numeric/ldexp.hpp"
#include <cmath>

// =====================================================================================================================

float m1::ldexp(float const x, int const exp) noexcept
{
    return std::ldexp(x, exp);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::ldexp(double const x, int const exp) noexcept
{
    return std::ldexp(x, exp);
}

// =====================================================================================================================
