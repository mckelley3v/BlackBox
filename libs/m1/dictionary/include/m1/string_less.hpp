#ifndef M1_STRING_LESS_HPP
#define M1_STRING_LESS_HPP

#include "m1/c_str_less.hpp"
#include <string>
#include <cstring>

namespace m1
{
    // =================================================================================================================

    struct string_less
        : c_str_less
    {
        using c_str_less::is_transparent;
        using c_str_less::operator ();

        template <typename Ch,
                  typename Tr,
                  typename A1>
        std::size_t operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                 char const * const rhs) const;

        template <typename Ch,
                  typename Tr,
                  typename A1>
        std::size_t operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                 char const * const rhs, std::size_t const rhs_length) const;

        template <typename Ch,
                  typename Tr,
                  typename A2>
        std::size_t operator () (char const * const lhs,
                                 std::basic_string<Ch, Tr, A2> const &rhs) const;

        template <typename Ch,
                  typename Tr,
                  typename A2>
        std::size_t operator () (char const * const lhs, std::size_t const lhs_length,
                                 std::basic_string<Ch, Tr, A2> const &rhs) const;

        template <typename Ch,
                  typename Tr,
                  typename A1,
                  typename A2>
        std::size_t operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                 std::basic_string<Ch, Tr, A2> const &rhs) const;
    };

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================
// m1::string_less
// =====================================================================================================================

template <typename Ch,
          typename Tr,
          typename A1>
std::size_t m1::string_less::operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                          char const * const rhs) const
{
    return c_str_less::operator () (lhs.c_str(), lhs.size(),
                                    rhs);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A1>
std::size_t m1::string_less::operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                          char const * const rhs, std::size_t const rhs_length) const
{
    return c_str_less::operator () (lhs.c_str(), lhs.size(),
                                    rhs, rhs_length);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A2>
std::size_t m1::string_less::operator () (char const * const lhs,
                                          std::basic_string<Ch, Tr, A2> const &rhs) const
{
    return c_str_less::operator () (lhs,
                                    rhs.c_str(), rhs.size());
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A2>
std::size_t m1::string_less::operator () (char const * const lhs, std::size_t const lhs_length,
                                          std::basic_string<Ch, Tr, A2> const &rhs) const
{
    return c_str_less::operator () (lhs, lhs_length,
                                    rhs.c_str(), rhs.size());
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A1,
          typename A2>
std::size_t m1::string_less::operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                          std::basic_string<Ch, Tr, A2> const &rhs) const
{
    return c_str_less::operator () (lhs.c_str(), lhs.size(),
                                    rhs.c_str(), rhs.size());
}

#endif // M1_STRING_LESS_HPP
