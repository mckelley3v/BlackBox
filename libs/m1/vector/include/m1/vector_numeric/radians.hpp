#ifndef M1_VECTOR_NUMERIC_RADIANS_HPP
#define M1_VECTOR_NUMERIC_RADIANS_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/radians.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    constexpr impl::vector_copy_type<T> radians(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
constexpr m1::impl::vector_copy_type<T> m1::radians(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::radians;
                                             return radians(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_RADIANS_HPP
