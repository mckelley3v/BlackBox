#ifndef M1_NUMERIC_ALL_OF_HPP
#define M1_NUMERIC_ALL_OF_HPP

namespace m1
{
    // =================================================================================================================

    constexpr bool all_of(bool lhs, bool rhs) noexcept;
    template <typename... Ts> constexpr bool all_of(bool arg0, bool arg1, Ts ...argN) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr bool m1::all_of(bool const lhs, bool const rhs) noexcept
{
    return lhs && rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr bool m1::all_of(bool const arg0, bool const arg1, Ts const ...argN) noexcept
{
    return all_of(arg0, all_of(arg1, argN...));
}

// =====================================================================================================================

#endif // M1_NUMERIC_ALL_OF_HPP
