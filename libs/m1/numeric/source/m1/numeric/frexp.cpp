#include "m1/numeric/frexp.hpp"
#include <cmath>
#include <cassert>

// =====================================================================================================================

float m1::frexp(float const x,
                int * const exp) noexcept
{
    assert(exp != nullptr);
    return std::frexp(x, exp);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::frexp(double const x,
                 int * const exp) noexcept
{
    assert(exp != nullptr);
    return std::frexp(x, exp);
}

// =====================================================================================================================
