#ifndef M1_NUMERIC_MIX_HPP
#define M1_NUMERIC_MIX_HPP

#include "m1/numeric/lerp.hpp"
#include "m1/numeric/saturate.hpp"

namespace m1
{
    // =================================================================================================================

    constexpr float mix(float x0,
                        float x1,
                        float t) noexcept;

    constexpr double mix(double x0,
                         double x1,
                         double t) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr float m1::mix(float const x0,
                        float const x1,
                        float const t) noexcept
{
    return lerp(x0, x1, saturate(t));
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::mix(double const x0,
                         double const x1,
                         double const t) noexcept
{
    return lerp(x0, x1, saturate(t));
}

// =====================================================================================================================

#endif // M1_NUMERIC_MIX_HPP
