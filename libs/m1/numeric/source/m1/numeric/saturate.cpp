#include "m1/numeric/saturate.hpp"

// =====================================================================================================================

float m1::saturate(float const value)
{
    return (value < 0.0f) ? 0.0f :
           (value > 1.0f) ? 1.0f : value;
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::saturate(double const value)
{
    return (value < 0.0) ? 0.0 :
           (value > 1.0) ? 1.0 : value;
}

// =====================================================================================================================