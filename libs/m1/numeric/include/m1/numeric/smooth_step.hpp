#ifndef M1_NUMERIC_SMOOTH_STEP_HPP
#define M1_NUMERIC_SMOOTH_STEP_HPP

#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/saturate.hpp"

namespace m1
{
    // =================================================================================================================

    constexpr float smooth_step(float x) noexcept;
    constexpr double smooth_step(double x) noexcept;

    constexpr float smooth_step(float edge0,
                                float edge1,
                                float x) noexcept;

    constexpr double smooth_step(double edge0,
                                 double edge1,
                                 double x) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    constexpr float smooth_step_curve(float const t) noexcept
    {
        return t * t * (3.0f - 2.0f * t);
    }

    // ---------------------------------------------------------------------------------------------------------------------

    constexpr double smooth_step_curve(double const t) noexcept
    {
        return t * t * (3.0 - 2.0 * t);
    }

    // ================================================================================================================
} // namespace impl
} // namespace m1

// =====================================================================================================================

constexpr float m1::smooth_step(float const x) noexcept
{
    return impl::smooth_step_curve(saturate(x));
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::smooth_step(double const x) noexcept
{
    return impl::smooth_step_curve(saturate(x));
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr float m1::smooth_step(float const edge0,
                                float const edge1,
                                float const x) noexcept
{
    return smooth_step(inverse_lerp(edge0, edge1, x));
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::smooth_step(double const edge0,
                                 double const edge1,
                                 double const x) noexcept
{
    return smooth_step(inverse_lerp(edge0, edge1, x));
}

// =====================================================================================================================

#endif // M1_NUMERIC_SMOOTH_STEP_HPP
