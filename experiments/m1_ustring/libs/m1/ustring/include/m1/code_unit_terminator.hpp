#ifndef M1_CODE_UNIT_TERMINATOR_HPP
#define M1_CODE_UNIT_TERMINATOR_HPP

namespace m1
{
    // ================================================================================================================

    class code_unit_terminator_null {};

    // ----------------------------------------------------------------------------------------------------------------

    template <typename Itr> constexpr bool operator == (code_unit_terminator_null const &lhs, Itr const &rhs) noexcept;
    template <typename Itr> constexpr bool operator == (Itr const &lhs, code_unit_terminator_null const &rhs) noexcept;

    template <typename Itr> constexpr bool operator != (code_unit_terminator_null const &lhs, Itr const &rhs) noexcept;
    template <typename Itr> constexpr bool operator != (Itr const &lhs, code_unit_terminator_null const &rhs) noexcept;

    // ================================================================================================================

    class code_unit_terminator_never {};

    // ----------------------------------------------------------------------------------------------------------------

    template <typename Itr> constexpr bool operator == (code_unit_terminator_never const &lhs, Itr const &rhs) noexcept;
    template <typename Itr> constexpr bool operator == (Itr const &lhs, code_unit_terminator_never const &rhs) noexcept;

    template <typename Itr> constexpr bool operator != (code_unit_terminator_never const &lhs, Itr const &rhs) noexcept;
    template <typename Itr> constexpr bool operator != (Itr const &lhs, code_unit_terminator_never const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

template <typename Itr> constexpr bool m1::operator == (code_unit_terminator_null const &/*lhs*/, Itr const &rhs) noexcept
{
    return 0 == *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr> constexpr bool m1::operator == (Itr const &lhs, code_unit_terminator_null const &/*rhs*/) noexcept
{
    return *lhs == 0;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr> constexpr bool m1::operator != (code_unit_terminator_null const &/*lhs*/, Itr const &rhs) noexcept
{
    return 0 != *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr> constexpr bool m1::operator != (Itr const &lhs, code_unit_terminator_null const &/*rhs*/) noexcept
{
    return *lhs != 0;
}

// ====================================================================================================================

template <typename Itr> constexpr bool m1::operator == (code_unit_terminator_never const &/*lhs*/, Itr const &/*rhs*/) noexcept
{
    return false;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr> constexpr bool m1::operator == (Itr const &/*lhs*/, code_unit_terminator_never const &/*rhs*/) noexcept
{
    return false;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr> constexpr bool m1::operator != (code_unit_terminator_never const &/*lhs*/, Itr const &/*rhs*/) noexcept
{
    return true;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr> constexpr bool m1::operator != (Itr const &/*lhs*/, code_unit_terminator_never const &/*rhs*/) noexcept
{
    return true;
}

// ====================================================================================================================

#endif // M1_CODE_UNIT_TERMINATOR_HPP
