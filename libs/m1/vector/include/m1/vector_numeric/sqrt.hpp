#ifndef M1_VECTOR_NUMERIC_SQRT_HPP
#define M1_VECTOR_NUMERIC_SQRT_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/sqrt.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    constexpr impl::vector_copy_type<T> sqrt(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
constexpr m1::impl::vector_copy_type<T> m1::sqrt(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::sqrt;
                                             return sqrt(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_SQRT_HPP
