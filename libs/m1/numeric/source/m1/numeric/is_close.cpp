#include "m1/numeric/is_close.hpp"
#include "m1/numeric/abs.hpp"
#include "m1/numeric/default_tolerance.hpp"

// =====================================================================================================================

bool m1::is_close(float const lhs,
                  float const rhs)
{
    return is_close(lhs,
                    rhs,
                    default_relative_tolerance<float>(),
                    default_absolute_tolerance<float>());
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_close(double const lhs,
                  double const rhs)
{
    return is_close(lhs,
                    rhs,
                    default_relative_tolerance<double>(),
                    default_absolute_tolerance<double>());
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_close(float const lhs,
                  float const rhs,
                  float const relative_tolerance,
                  float const absolute_tolerance)
{
    return abs(rhs - lhs) <= (relative_tolerance * (abs(lhs) + abs(rhs)) + absolute_tolerance);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_close(double const lhs,
                  double const rhs,
                  double const relative_tolerance,
                  double const absolute_tolerance)
{
    return abs(rhs - lhs) <= (relative_tolerance * (abs(lhs) + abs(rhs)) + absolute_tolerance);
}

// =====================================================================================================================
