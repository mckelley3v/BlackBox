#ifndef M1_NUMERIC_IS_SMALL_HPP
#define M1_NUMERIC_IS_SMALL_HPP

#include "m1/numeric/abs.hpp"
#include "m1/numeric/epsilon.hpp"

namespace m1
{
    // =================================================================================================================

    constexpr bool is_small(float x) noexcept;
    constexpr bool is_small(double x) noexcept;

    constexpr bool is_small(float x,
                            float epsilon) noexcept;

    constexpr bool is_small(double x,
                            double epsilon) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr bool m1::is_small(float const x) noexcept
{
    return abs(x) <= absolute_epsilon<float>();
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr bool m1::is_small(double const x) noexcept
{
    return abs(x) <= absolute_epsilon<double>();
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr bool m1::is_small(float const x,
                            float const epsilon) noexcept
{
    return abs(x) <= epsilon;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr bool m1::is_small(double const x,
                            double const epsilon) noexcept
{
    return abs(x) <= epsilon;
}

// =====================================================================================================================

#endif // M1_NUMERIC_IS_SMALL_HPP
