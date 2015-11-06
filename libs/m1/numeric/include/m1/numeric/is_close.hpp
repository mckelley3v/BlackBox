#ifndef M1_NUMERIC_IS_CLOSE_HPP
#define M1_NUMERIC_IS_CLOSE_HPP

#include "m1/numeric/abs.hpp"
#include "m1/numeric/epsilon.hpp"

namespace m1
{
    // =================================================================================================================

    constexpr bool is_close(float lhs,
                            float rhs) noexcept;

    constexpr bool is_close(double lhs,
                            double rhs) noexcept;

    constexpr bool is_close(float lhs,
                            float rhs,
                            float relative_tolerance,
                            float absolute_tolerance) noexcept;

    constexpr bool is_close(double lhs,
                            double rhs,
                            double relative_tolerance,
                            double absolute_tolerance) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr bool m1::is_close(float const lhs,
                            float const rhs) noexcept
{
    return abs(rhs - lhs) <= (relative_epsilon<float>() * (abs(lhs) + abs(rhs)) + absolute_epsilon<float>());
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr bool m1::is_close(double const lhs,
                            double const rhs) noexcept
{
    return abs(rhs - lhs) <= (relative_epsilon<double>() * (abs(lhs) + abs(rhs)) + absolute_epsilon<double>());
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr bool m1::is_close(float const lhs,
                            float const rhs,
                            float const relative_tolerance,
                            float const absolute_tolerance) noexcept
{
    return abs(rhs - lhs) <= (relative_tolerance * (abs(lhs) + abs(rhs)) + absolute_tolerance);
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr bool m1::is_close(double const lhs,
                            double const rhs,
                            double const relative_tolerance,
                            double const absolute_tolerance) noexcept
{
    return abs(rhs - lhs) <= (relative_tolerance * (abs(lhs) + abs(rhs)) + absolute_tolerance);
}

// =====================================================================================================================

#endif // M1_NUMERIC_IS_CLOSE_HPP
