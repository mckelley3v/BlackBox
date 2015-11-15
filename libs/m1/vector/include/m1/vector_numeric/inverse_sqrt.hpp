#ifndef M1_VECTOR_NUMERIC_INVERSE_SQRT_HPP
#define M1_VECTOR_NUMERIC_INVERSE_SQRT_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/inverse_sqrt.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    impl::vector_copy_type<T> inverse_sqrt(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
m1::impl::vector_copy_type<T> m1::inverse_sqrt(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::inverse_sqrt;
                                             return inverse_sqrt(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_INVERSE_SQRT_HPP
