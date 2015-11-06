#ifndef M1_NUMERIC_EPSILON_HPP
#define M1_NUMERIC_EPSILON_HPP

namespace m1
{
    // =================================================================================================================

    template <typename T> constexpr T relative_epsilon() noexcept;

    // =================================================================================================================

    template <typename T> constexpr T absolute_epsilon() noexcept;

    // =================================================================================================================
} // namespace m1

// =================================================================================================================

template <typename T> constexpr T m1::relative_epsilon() noexcept
{
    return static_cast<T>(1e-5);
}

// =================================================================================================================

template <typename T> constexpr T m1::absolute_epsilon() noexcept
{
    return static_cast<T>(1e-6);
}

// =================================================================================================================

#endif // M1_NUMERIC_EPSILON_HPP
