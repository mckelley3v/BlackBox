#include "m1/numeric/frexp.hpp"
#include <cmath>
#include <cassert>

// =====================================================================================================================

void m1::frexp(float * const scale,
               int * const exp,
               float const x)
{
    assert(scale != nullptr);
    assert(exp != nullptr);
    *scale = std::frexp(x, exp);
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::frexp(double * const scale,
               int * const exp,
               double const x)
{
    assert(scale != nullptr);
    assert(exp != nullptr);
    *scale = std::frexp(x, exp);
}

// =====================================================================================================================
