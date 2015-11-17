#include "m1/numeric/mod.hpp"
#include "m1/numeric/is_small.hpp"
#include <cmath>
#include <cassert>

// =====================================================================================================================

int m1::mod(int const numer,
            int const denom) noexcept
{
    assert(denom > 0);
    return
          (numer > 0)
        ? (numer % denom)
        : ((denom - (-numer % denom)) % denom);
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::mod(float const numer,
              float const denom) noexcept
{
    assert(!is_small(denom));
    return std::fmod(numer, denom);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::mod(double const numer,
               double const denom) noexcept
{
    assert(!is_small(denom));
    return std::fmod(numer, denom);
}

// =====================================================================================================================
