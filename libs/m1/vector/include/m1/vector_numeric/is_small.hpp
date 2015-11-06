#ifndef M1_VECTOR_NUMERIC_IS_SMALL_HPP
#define M1_VECTOR_NUMERIC_IS_SMALL_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/is_small.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T> impl::vector_bool_type<T> is_small(vector<T> const &v) noexcept;

    template <typename T, typename X> impl::vector_bool_type<T> is_small(vector<T> const &v,
                                                                         X const &tolerance) noexcept;

    template <typename T, typename X> impl::vector_bool_type<T, X> is_small(vector<T> const &v,
                                                                            vector<X> const &tolerance) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T> m1::impl::vector_bool_type<T> m1::is_small(vector<T> const &v) noexcept
{
    return impl::generate_vector_bool<T>([&](auto index) { using m1::is_small; return is_small(v[index]); });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, typename X> m1::impl::vector_bool_type<T> m1::is_small(vector<T> const &v,
                                                                             X const &tolerance) noexcept
{
    return impl::generate_vector_bool<T>([&](auto index) { using m1::is_small; return is_small(v[index], tolerance); });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, typename X> m1::impl::vector_bool_type<T, X> m1::is_small(vector<T> const &v,
                                                                                vector<X> const &tolerance) noexcept
{
    return impl::generate_vector_bool<T, X>([&](auto index) { using m1::is_small; return is_small(v[index], tolerance[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_IS_SMALL_HPP
