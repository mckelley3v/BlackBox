#include "m1/c_str_equal_to.hpp"
#include <cstring>
#include <cwchar>

// =====================================================================================================================

template <typename Char>
static bool c_str_equal_to_n(Char const *lhs,
                             Char const *rhs, std::size_t rhs_length);

// =====================================================================================================================
// m1::c_str_equal_to
// =====================================================================================================================

bool m1::c_str_equal_to::operator () (char const * const lhs,
                                      char const * const rhs) const
{
    return std::strcmp(lhs, rhs) == 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (char const * const lhs,
                                      char const * const rhs, std::size_t const rhs_length) const
{
    return c_str_equal_to_n(lhs, rhs, rhs_length);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (char const * const lhs, std::size_t const lhs_length,
                                      char const * const rhs) const
{
    return c_str_equal_to_n(rhs, lhs, lhs_length);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (char const * const lhs, std::size_t const lhs_length,
                                      char const * const rhs, std::size_t const rhs_length) const
{
    return (lhs_length == rhs_length) ? std::strncmp(lhs, rhs, lhs_length) == 0 : false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (wchar_t const * const lhs,
                                      wchar_t const * const rhs) const
{
    return std::wcscmp(lhs, rhs) == 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (wchar_t const * const lhs,
                                      wchar_t const * const rhs, std::size_t const rhs_length) const
{
    return c_str_equal_to_n(lhs, rhs, rhs_length);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (wchar_t const * const lhs, std::size_t const lhs_length,
                                      wchar_t const * const rhs) const
{
    return c_str_equal_to_n(rhs, lhs, lhs_length);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_equal_to::operator () (wchar_t const * const lhs, std::size_t const lhs_length,
                                      wchar_t const * const rhs, std::size_t const rhs_length) const
{
    return (lhs_length == rhs_length) ? std::wcsncmp(lhs, rhs, lhs_length) == 0 : false;
}

// =====================================================================================================================

template <typename Char>
static bool c_str_equal_to_n(Char const *lhs,
                             Char const *rhs, std::size_t rhs_length)
{
    // iterate over lhs until null char is reached
    // iterate over rhs until rhs_length reaches 0
    while(*lhs && rhs_length)
    {
        if (*lhs != *rhs) return false;
        ++lhs;
        ++rhs;
        --rhs_length;
    }

    // lhs is equal to rhs if all chars are compared equal
    return !*lhs && (rhs_length == 0);
}
