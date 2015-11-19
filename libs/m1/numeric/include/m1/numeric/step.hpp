#ifndef M1_NUMERIC_STEP_HPP
#define M1_NUMERIC_STEP_HPP

namespace m1
{
    // =================================================================================================================

    constexpr float step(float edge, float x) noexcept;
    constexpr double step(double edge, double x) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr float m1::step(float const edge, float const x) noexcept
{
    return (x < edge) ? 0.0f : 1.0f;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::step(double const edge, double const x) noexcept
{
    return (x < edge) ? 0.0 : 1.0;
}

// =====================================================================================================================

#endif // M1_NUMERIC_STEP_HPP
