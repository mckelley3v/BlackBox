#include "vku_utility.hpp"
#include <cstring>

// ====================================================================================================================
// Implementation
// ====================================================================================================================

vku::c_str_compare_to::c_str_compare_to(char const * const lhs)
    : m_Lhs(lhs)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::c_str_compare_to::operator() (char const * const rhs) const
{
    return c_str_equal(m_Lhs, rhs);
}

// ====================================================================================================================

vku::name_compare_to::name_compare_to(char const * const lhs)
    : m_Lhs(lhs)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::name_compare_to::operator() (char const * const rhs) const
{
    return c_str_equal(m_Lhs, rhs) || c_str_equal("*", m_Lhs) || c_str_equal("*", rhs);
}

// ====================================================================================================================

/*static*/ bool vku::c_str_equal(char const *lhs, char const *rhs)
{
    return std::strcmp(lhs, rhs) == 0;
}

// ====================================================================================================================

std::string vku::make_string(std::initializer_list<char const*> c_strs)
{
    std::size_t length = 0;
    for(char const * const c_str : c_strs)
    {
        length += std::strlen(c_str);
    }

    std::string result;
    result.reserve(length);

    for(char const * const c_str : c_strs)
    {
        result.append(c_str);
    }

    return result;
}

// ====================================================================================================================
