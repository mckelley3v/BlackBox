#ifndef M1_VECTOR_NUMERIC_TRUNC_HPP
#define M1_VECTOR_NUMERIC_TRUNC_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/trunc.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    constexpr impl::vector_copy_type<T> trunc(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
constexpr m1::impl::vector_copy_type<T> m1::trunc(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::trunc;
                                             return trunc(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_TRUNC_HPP
