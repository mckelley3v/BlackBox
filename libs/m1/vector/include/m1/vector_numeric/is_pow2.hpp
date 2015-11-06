#ifndef M1_VECTOR_NUMERIC_IS_POW2_HPP
#define M1_VECTOR_NUMERIC_IS_POW2_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/is_pow2.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T> constexpr impl::vector_bool_type<T> is_pow2(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T> constexpr m1::impl::vector_bool_type<T> m1::is_pow2(vector<T> const &v) noexcept
{
    return impl::generate_vector_bool<T>([&](auto index) { using m1::is_pow2; return is_pow2(v[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_IS_POW2_HPP
