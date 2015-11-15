#ifndef M1_NUMERIC_NONE_OF_HPP
#define M1_NUMERIC_NONE_OF_HPP

namespace m1
{
    // =================================================================================================================

    constexpr bool none_of(bool lhs, bool rhs) noexcept;
    template <typename... Ts> constexpr bool none_of(bool arg0, bool arg1, Ts ...argN) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr bool m1::none_of(bool const lhs, bool const rhs) noexcept
{
    return !lhs && !rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr bool m1::none_of(bool const arg0, bool const arg1, Ts const ...argN) noexcept
{
    return none_of(arg0, none_of(arg1, argN...));
}

// =====================================================================================================================

#endif // M1_NUMERIC_NONE_OF_HPP
