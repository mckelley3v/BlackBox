#ifndef M1_TEST_ARRAY_SIZE_HPP
#define M1_TEST_ARRAY_SIZE_HPP

#include <type_traits>

namespace m1
{
    // ================================================================================================================

    template <typename T,
              std::size_t N = 0>
    constexpr std::size_t array_size(T const &/*array*/,
                                     std::integral_constant<std::size_t, N> /*dimension*/ = std::integral_constant<std::size_t, N>())
    {
        return std::extent<T, N>::value;
    }

    // ================================================================================================================
} // namespace m1

#endif // M1_TEST_ARRAY_SIZE_HPP
