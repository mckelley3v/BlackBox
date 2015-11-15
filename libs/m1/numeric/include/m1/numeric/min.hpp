#ifndef M1_NUMERIC_MIN_HPP
#define M1_NUMERIC_MIN_HPP

namespace m1
{
    // =================================================================================================================

    constexpr int min(int lhs, int rhs) noexcept;
    constexpr float min(float lhs, float rhs) noexcept;
    constexpr double min(double lhs, double rhs) noexcept;
    template <typename... Ts> constexpr int min(int arg0, int arg1, Ts ...argN) noexcept;
    template <typename... Ts> constexpr float min(float arg0, float arg1, Ts ...argN) noexcept;
    template <typename... Ts> constexpr double min(double arg0, double arg1, Ts ...argN) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr int m1::min(int const lhs, int const rhs) noexcept
{
    return (lhs < rhs) ? lhs : rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr float m1::min(float const lhs, float const rhs) noexcept
{
    return (lhs < rhs) ? lhs : rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::min(double const lhs, double const rhs) noexcept
{
    return (lhs < rhs) ? lhs : rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr int m1::min(int const arg0, int const arg1, Ts const ...argN) noexcept
{
    return min(arg0, min(arg1, argN...));
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr float m1::min(float const arg0, float const arg1, Ts const ...argN) noexcept
{
    return min(arg0, min(arg1, argN...));
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr double m1::min(double const arg0, double const arg1, Ts const ...argN) noexcept
{
    return min(arg0, min(arg1, argN...));
}

// =====================================================================================================================

#endif // M1_NUMERIC_MIN_HPP
