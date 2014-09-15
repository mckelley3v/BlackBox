#ifndef M1_STRING_EQUAL_TO_HPP
#define M1_STRING_EQUAL_TO_HPP

#include "m1/c_str_equal_to.hpp"
#include <string>
#include <cstring>

namespace m1
{
    // =================================================================================================================

    struct string_equal_to
        : c_str_equal_to
    {
        using c_str_equal_to::is_transparent;
        using c_str_equal_to::operator ();

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
// m1::string_equal_to
// =====================================================================================================================

template <typename Ch,
          typename Tr,
          typename A1>
std::size_t m1::string_equal_to::operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                              char const * const rhs) const
{
    return c_str_equal_to::operator () (lhs.c_str(), lhs.size(),
                                        rhs);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A1>
std::size_t m1::string_equal_to::operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                              char const * const rhs, std::size_t const rhs_length) const
{
    return c_str_equal_to::operator () (lhs.c_str(), lhs.size(),
                                        rhs, rhs_length);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A2>
std::size_t m1::string_equal_to::operator () (char const * const lhs,
                                              std::basic_string<Ch, Tr, A2> const &rhs) const
{
    return c_str_equal_to::operator () (lhs,
                                        rhs.c_str(), rhs.size());
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A2>
std::size_t m1::string_equal_to::operator () (char const * const lhs, std::size_t const lhs_length,
                                              std::basic_string<Ch, Tr, A2> const &rhs) const
{
    return c_str_equal_to::operator () (lhs, lhs_length,
                                        rhs.c_str(), rhs.size());
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Ch,
          typename Tr,
          typename A1,
          typename A2>
std::size_t m1::string_equal_to::operator () (std::basic_string<Ch, Tr, A1> const &lhs,
                                              std::basic_string<Ch, Tr, A2> const &rhs) const
{
    return c_str_equal_to::operator () (lhs.c_str(), lhs.size(),
                                        rhs.c_str(), rhs.size());
}

#endif // M1_STRING_EQUAL_TO_HPP
