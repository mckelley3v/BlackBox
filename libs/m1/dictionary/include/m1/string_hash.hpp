#ifndef M1_STRING_HASH_HPP
#define M1_STRING_HASH_HPP

#include "m1/c_str_hash.hpp"
#include <string>

namespace m1
{
    // =================================================================================================================

    struct string_hash
        : c_str_hash
    {
        using c_str_hash::is_transparent;
        using c_str_hash::operator ();

        template <typename Ch,
                  typename Tr,
                  typename A>
        std::size_t operator () (std::basic_string<Ch, Tr, A> const &str) const;
    };

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================
// m1::string_hash
// =====================================================================================================================

template <typename Ch,
          typename Tr,
          typename A>
std::size_t m1::string_hash::operator () (std::basic_string<Ch, Tr, A> const &str) const
{
    return c_str_hash::operator () (str.c_str(), str.size());
}

#endif // M1_STRING_HASH_HPP
