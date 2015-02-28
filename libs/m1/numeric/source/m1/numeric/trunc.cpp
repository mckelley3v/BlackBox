#include "m1/numeric/trunc.hpp"
#include <limits>
#include <cassert>

// =====================================================================================================================

float m1::trunc(float const x)
{
    assert(static_cast<float>(std::numeric_limits<int>::min()) <= x);
    assert(x <= static_cast<float>(std::numeric_limits<int>::max()));
    return static_cast<float>(static_cast<int>(x));
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::trunc(double const x)
{
    assert(static_cast<double>(std::numeric_limits<int>::min()) <= x);
    assert(x <= static_cast<double>(std::numeric_limits<int>::max()));
    return static_cast<double>(static_cast<int>(x));
}

// =====================================================================================================================
