#ifndef M1_NUMERIC_SUM_HPP
#define M1_NUMERIC_SUM_HPP

namespace m1
{
    // =================================================================================================================

    constexpr int sum(int lhs, int rhs) noexcept;
    constexpr float sum(float lhs, float rhs) noexcept;
    constexpr double sum(double lhs, double rhs) noexcept;
    template <typename... Ts> constexpr int sum(int arg0, int arg1, Ts ...argN) noexcept;
    template <typename... Ts> constexpr float sum(float arg0, float arg1, Ts ...argN) noexcept;
    template <typename... Ts> constexpr double sum(double arg0, double arg1, Ts ...argN) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr int m1::sum(int const lhs, int const rhs) noexcept
{
    return lhs + rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr float m1::sum(float const lhs, float const rhs) noexcept
{
    return lhs + rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::sum(double const lhs, double const rhs) noexcept
{
    return lhs + rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr int m1::sum(int const arg0, int const arg1, Ts ...argN) noexcept
{
    return sum(arg0, sum(arg1, argN...));
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr float m1::sum(float const arg0, float const arg1, Ts ...argN) noexcept
{
    return sum(arg0, sum(arg1, argN...));
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr double m1::sum(double const arg0, double const arg1, Ts ...argN) noexcept
{
    return sum(arg0, sum(arg1, argN...));
}

// =====================================================================================================================

#endif // M1_NUMERIC_SUM_HPP
