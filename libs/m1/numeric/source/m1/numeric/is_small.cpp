#include "m1/numeric/is_small.hpp"
#include "m1/numeric/abs.hpp"
#include "m1/numeric/default_tolerance.hpp"

// =====================================================================================================================

bool m1::is_small(float const x)
{
    return is_small(x, default_absolute_tolerance<float>());
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_small(double const x)
{
    return is_small(x, default_absolute_tolerance<double>());
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_small(float const x,
                  float const tolerance)
{
    return abs(x) <= tolerance;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_small(double const x,
                  double const tolerance)
{
    return abs(x) <= tolerance;
}

// =====================================================================================================================
