#ifndef M1_NUMERIC_DEFAULT_TOLERANCE_HPP
#define M1_NUMERIC_DEFAULT_TOLERANCE_HPP

namespace m1
{
    // =================================================================================================================

    template <typename T> constexpr T default_relative_tolerance();

    // =================================================================================================================

    template <typename T> constexpr T default_absolute_tolerance();

    // =================================================================================================================
} // namespace m1

// =================================================================================================================

template <typename T> constexpr T m1::default_relative_tolerance()
{
    return static_cast<T>(1e-5);
}

// =================================================================================================================

template <typename T> constexpr T m1::default_absolute_tolerance()
{
    return static_cast<T>(1e-6);
}

// =================================================================================================================

#endif // M1_NUMERIC_DEFAULT_TOLERANCE_HPP
