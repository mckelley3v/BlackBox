#ifndef M1_NUMERIC_LERP_HPP
#define M1_NUMERIC_LERP_HPP

#include <cassert>

namespace m1
{
    // =================================================================================================================

    constexpr float lerp(float x0,
                         float x1,
                         float t) noexcept;

    constexpr double lerp(double x0,
                          double x1,
                          double t) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr float m1::lerp(float const x0,
                         float const x1,
                         float const t) noexcept
{
    return assert(x0 < x1), x0 + t * (x1 - x0);
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::lerp(double const x0,
                          double const x1,
                          double const t) noexcept
{
    return assert(x0 < x1), x0 + t * (x1 - x0);
}

// =====================================================================================================================

#endif // M1_NUMERIC_LERP_HPP
