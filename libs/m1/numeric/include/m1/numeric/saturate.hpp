#ifndef M1_NUMERIC_SATURATE_HPP
#define M1_NUMERIC_SATURATE_HPP

namespace m1
{
    // =================================================================================================================

    constexpr float saturate(float value) noexcept;
    constexpr double saturate(double value) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr float m1::saturate(float const value) noexcept
{
    return (value < 0.0f) ? 0.0f :
           (value > 1.0f) ? 1.0f : value;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::saturate(double const value) noexcept
{
    return (value < 0.0) ? 0.0 :
           (value > 1.0) ? 1.0 : value;
}

// =====================================================================================================================

#endif // M1_NUMERIC_SATURATE_HPP
