#ifndef M1_VECTOR_NUMERIC_IS_NAN_HPP
#define M1_VECTOR_NUMERIC_IS_NAN_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/is_nan.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T> impl::vector_bool_type<T> is_nan(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T> m1::impl::vector_bool_type<T> m1::is_nan(vector<T> const &v) noexcept
{
    return impl::generate_vector_bool<T>([&](auto index) { using m1::is_nan; return is_nan(v[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_IS_NAN_HPP
