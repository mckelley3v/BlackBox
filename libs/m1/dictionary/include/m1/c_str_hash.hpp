#ifndef M1_C_STR_HASH_HPP
#define M1_C_STR_HASH_HPP

#include <cstddef>

namespace m1
{
    // =================================================================================================================

    struct c_str_hash
    {
        typedef void is_transparent;

        std::size_t operator () (char const * const c_str) const;
        std::size_t operator () (char const * const c_str, std::size_t const c_str_length) const;
        std::size_t operator () (wchar_t const * const c_str) const;
        std::size_t operator () (wchar_t const * const c_str, std::size_t const c_str_length) const;
    };

    // =================================================================================================================
} // namespace m1

#endif // M1_C_STR_HASH_HPP
