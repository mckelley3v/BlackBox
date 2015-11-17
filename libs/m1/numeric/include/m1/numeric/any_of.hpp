#ifndef M1_NUMERIC_ANY_OF_HPP
#define M1_NUMERIC_ANY_OF_HPP

namespace m1
{
    // =================================================================================================================

    constexpr bool any_of(bool lhs, bool rhs) noexcept;
    template <typename... Ts> constexpr bool any_of(bool arg0, bool arg1, Ts ...argN) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr bool m1::any_of(bool const lhs, bool const rhs) noexcept
{
    return lhs || rhs;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename... Ts> constexpr bool m1::any_of(bool const arg0, bool const arg1, Ts ...argN) noexcept
{
    return any_of(arg0, any_of(arg1, argN...));
}

// =====================================================================================================================

#endif // M1_NUMERIC_ANY_OF_HPP
