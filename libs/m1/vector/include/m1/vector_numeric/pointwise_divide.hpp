#ifndef M1_VECTOR_NUMERIC_POINTWISE_DIVIDE_HPP
#define M1_VECTOR_NUMERIC_POINTWISE_DIVIDE_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename L, typename R>
    constexpr impl::vector_copy_type<L, R> pointwise_divide(vector<L> const &lhs,
                                                              vector<R> const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename L, typename R>
constexpr m1::impl::vector_copy_type<L, R> m1::pointwise_divide(vector<L> const &lhs,
                                                                  vector<R> const &rhs) noexcept
{
    return impl::generate_vector_copy<L, R>([&](auto index)
                                            {
                                                return lhs[index] / rhs[index];
                                            });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_POINTWISE_DIVIDE_HPP
