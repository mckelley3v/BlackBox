#include "m1/c_str_hash.hpp"
#include "m1/murmur3_32.hpp"
#include <cstring>
#include <cwchar>

// =====================================================================================================================
// m1::c_str_hash
// =====================================================================================================================

std::size_t m1::c_str_hash::operator () (char const * const c_str) const
{
    return static_cast<std::size_t>(murmur3_32(static_cast<void const*>(c_str),
                                               static_cast<std::uint32_t>(std::strlen(c_str) * sizeof(c_str[0])),
                                               murmur3_32_seed()));
}

// ---------------------------------------------------------------------------------------------------------------------

std::size_t m1::c_str_hash::operator () (char const * const c_str, std::size_t const c_str_length) const
{
    return static_cast<std::size_t>(murmur3_32(static_cast<void const*>(c_str),
                                               static_cast<std::uint32_t>(c_str_length * sizeof(c_str[0])),
                                               murmur3_32_seed()));
}

// ---------------------------------------------------------------------------------------------------------------------

std::size_t m1::c_str_hash::operator () (wchar_t const * const c_str) const
{
    return static_cast<std::size_t>(murmur3_32(static_cast<void const*>(c_str),
                                               static_cast<std::uint32_t>(std::wcslen(c_str) * sizeof(c_str[0])),
                                               murmur3_32_seed()));
}

// ---------------------------------------------------------------------------------------------------------------------

std::size_t m1::c_str_hash::operator () (wchar_t const * const c_str, std::size_t const c_str_length) const
{
    return static_cast<std::size_t>(murmur3_32(static_cast<void const*>(c_str),
                                               static_cast<std::uint32_t>(c_str_length * sizeof(c_str[0])),
                                               murmur3_32_seed()));
}
