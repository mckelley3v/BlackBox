#ifndef M1_NUMERIC_LINEAR_STEP_HPP
#define M1_NUMERIC_LINEAR_STEP_HPP

#include "m1/numeric/inverse_lerp.hpp"
#include "m1/numeric/saturate.hpp"

namespace m1
{
    // =================================================================================================================

    constexpr float linear_step(float edge0,
                                float edge1,
                                float x) noexcept;

    constexpr double linear_step(double edge0,
                                 double edge1,
                                 double x) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr float m1::linear_step(float const edge0,
                                float const edge1,
                                float const x) noexcept
{
    return saturate(inverse_lerp(edge0, edge1, x));
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::linear_step(double const edge0,
                                 double const edge1,
                                 double const x) noexcept
{
    return saturate(inverse_lerp(edge0, edge1, x));
}

// =====================================================================================================================

#endif // M1_NUMERIC_LINEAR_STEP_HPP
