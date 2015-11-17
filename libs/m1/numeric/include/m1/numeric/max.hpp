#ifndef M1_NUMERIC_MAX_HPP
#define M1_NUMERIC_MAX_HPP

namespace m1
{
    // =================================================================================================================

    constexpr int max(int lhs, int rhs) noexcept;
    constexpr float max(float lhs, float rhs) noexcept;
    constexpr double max(double lhs, double rhs) noexcept;
    template <typename... Ts> constexpr int max(int arg0, int arg1, Ts ...argN) noexcept;
    template <typename... Ts> constexpr float max(float arg0, float arg1, Ts ...argN) noexcept;
    template <typename... Ts> constexpr double max(double arg0, double arg1, Ts ...argN) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr int m1::max(int const lhs, int const rhs) noexcept
{
    return (lhs < rhs) ? rhs : lhs;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr float m1::max(float const lhs, float const rhs) noexcept
{
    return (lhs < rhs) ? rhs : lhs;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::max(double const lhs, double const rhs) noexcept
{
    return (lhs < rhs) ? rhs : lhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr int m1::max(int const arg0, int const arg1, Ts ...argN) noexcept
{
    return max(arg0, max(arg1, argN...));
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr float m1::max(float const arg0, float const arg1, Ts ...argN) noexcept
{
    return max(arg0, max(arg1, argN...));
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr double m1::max(double const arg0, double const arg1, Ts ...argN) noexcept
{
    return max(arg0, max(arg1, argN...));
}

// =====================================================================================================================

#endif // M1_NUMERIC_MAX_HPP
