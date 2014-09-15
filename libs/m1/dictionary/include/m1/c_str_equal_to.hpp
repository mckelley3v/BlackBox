#ifndef M1_C_STR_EQUAL_TO_HPP
#define M1_C_STR_EQUAL_TO_HPP

#include <cstddef>

namespace m1
{
    // =================================================================================================================

    struct c_str_equal_to
    {
        typedef void is_transparent;

        bool operator () (char const * const lhs,
                          char const * const rhs) const;

        bool operator () (char const * const lhs,
                          char const * const rhs, std::size_t const rhs_length) const;

        bool operator () (char const * const lhs, std::size_t const lhs_length,
                          char const * const rhs) const;

        bool operator () (char const * const lhs, std::size_t const lhs_length,
                          char const * const rhs, std::size_t const rhs_length) const;

        bool operator () (wchar_t const * const lhs,
                          wchar_t const * const rhs) const;

        bool operator () (wchar_t const * const lhs,
                          wchar_t const * const rhs, std::size_t const rhs_length) const;

        bool operator () (wchar_t const * const lhs, std::size_t const lhs_length,
                          wchar_t const * const rhs) const;

        bool operator () (wchar_t const * const lhs, std::size_t const lhs_length,
                          wchar_t const * const rhs, std::size_t const rhs_length) const;
    };

    // =================================================================================================================
} // namespace m1

#endif // M1_C_STR_EQUAL_TO_HPP
