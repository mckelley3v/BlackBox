#include "m1/c_str_less.hpp"
#include <cstring>
#include <cwchar>

// =====================================================================================================================
// m1::c_str_less
// =====================================================================================================================

bool m1::c_str_less::operator () (char const * const lhs,
                                  char const * const rhs) const
{
    return std::strcmp(lhs, rhs) < 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (char const * const lhs,
                                  char const * const rhs, std::size_t const rhs_length) const
{
    return std::strncmp(lhs, rhs, rhs_length) < 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (char const * const lhs, std::size_t const lhs_length,
                                  char const * const rhs) const
{
    return std::strncmp(lhs, rhs, lhs_length) < 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (char const * const lhs, std::size_t const lhs_length,
                                  char const * const rhs, std::size_t const rhs_length) const
{
    std::size_t min_length = (lhs_length < rhs_length) ? lhs_length : rhs_length;
    int const cmp = std::strncmp(lhs, rhs, min_length);
    return (cmp == 0) ? (lhs_length < rhs_length) : (cmp < 0);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (wchar_t const * const lhs,
                                  wchar_t const * const rhs) const
{
    return std::wcscmp(lhs, rhs) < 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (wchar_t const * const lhs,
                                  wchar_t const * const rhs, std::size_t const rhs_length) const
{
    return std::wcsncmp(lhs, rhs, rhs_length) < 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (wchar_t const * const lhs, std::size_t const lhs_length,
                                  wchar_t const * const rhs) const
{
    return std::wcsncmp(lhs, rhs, lhs_length) <= 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::c_str_less::operator () (wchar_t const * const lhs, std::size_t const lhs_length,
                                  wchar_t const * const rhs, std::size_t const rhs_length) const
{
    std::size_t min_length = (lhs_length < rhs_length) ? lhs_length : rhs_length;
    int const cmp = std::wcsncmp(lhs, rhs, min_length);
    return (cmp == 0) ? (lhs_length < rhs_length) : (cmp < 0);
}
