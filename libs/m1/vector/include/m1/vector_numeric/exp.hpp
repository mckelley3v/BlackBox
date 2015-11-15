#ifndef M1_VECTOR_NUMERIC_EXP_HPP
#define M1_VECTOR_NUMERIC_EXP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/exp.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    impl::vector_copy_type<T> exp(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
m1::impl::vector_copy_type<T> m1::exp(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::exp;
                                             return exp(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_EXP_HPP
