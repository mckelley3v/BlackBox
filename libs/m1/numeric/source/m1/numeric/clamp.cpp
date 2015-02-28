#include "m1/numeric/clamp.hpp"
#include <cassert>

// =====================================================================================================================

float m1::clamp(float const value,
                float const min_value,
                float const max_value)
{
    assert(min_value <= max_value);
    return (value < min_value) ? min_value :
           (value > max_value) ? max_value : value;
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::clamp(double const value,
                 double const min_value,
                 double const max_value)
{
    assert(min_value <= max_value);
    return (value < min_value) ? min_value :
           (value > max_value) ? max_value : value;
}

// =====================================================================================================================
