#include "m1/numeric/max.hpp"

// =====================================================================================================================

int m1::max(int const lhs, int const rhs)
{
    return (lhs < rhs) ? rhs : lhs;
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::max(float const lhs, float const rhs)
{
    return (lhs < rhs) ? rhs : lhs;
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::max(double const lhs, double const rhs)
{
    return (lhs < rhs) ? rhs : lhs;
}

// =====================================================================================================================
