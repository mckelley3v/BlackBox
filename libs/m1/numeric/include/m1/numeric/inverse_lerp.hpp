#ifndef M1_NUMERIC_INVERSE_LERP_HPP
#define M1_NUMERIC_INVERSE_LERP_HPP

#include <cassert>

namespace m1
{
    // =================================================================================================================

    constexpr float inverse_lerp(float x0,
                                 float x1,
                                 float x) noexcept;

    constexpr double inverse_lerp(double x0,
                                  double x1,
                                  double x) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr float m1::inverse_lerp(float const x0,
                                 float const x1,
                                 float const x) noexcept
{
    return assert(x0 < x1), (x - x0) / (x1 - x0);
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::inverse_lerp(double const x0,
                                  double const x1,
                                  double const x) noexcept
{
    return assert(x0 < x1), (x - x0) / (x1 - x0);
}

// =====================================================================================================================

#endif // M1_NUMERIC_INVERSE_LERP_HPP
