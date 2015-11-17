#ifndef M1_VECTOR_NUMERIC_MIRROR_HPP
#define M1_VECTOR_NUMERIC_MIRROR_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/mirror.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    impl::vector_copy_type<T> mirror(vector<T> const &v) noexcept;

    template <typename T, typename L, typename R>
    impl::vector_copy_type<T> mirror(vector<T> const &values,
                                     L const &min_value,
                                     R const &max_value) noexcept;

    template <typename T, typename L, typename R>
    impl::vector_copy_type<T, L, R> mirror(vector<T> const &values,
                                           vector<L> const &min_values,
                                           vector<R> const &max_values) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
m1::impl::vector_copy_type<T> m1::mirror(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::mirror;
                                             return mirror(v[index]);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, typename L, typename R>
m1::impl::vector_copy_type<T> m1::mirror(vector<T> const &values,
                                         L const &min_value,
                                         R const &max_value) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::mirror;
                                             return mirror(values[index],
                                                           min_value,
                                                           max_value);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, typename L, typename R>
m1::impl::vector_copy_type<T, L, R> m1::mirror(vector<T> const &values,
                                               vector<L> const &min_values,
                                               vector<R> const &max_values) noexcept
{
    return impl::generate_vector_copy<T, L, R>([&](auto index)
                                               {
                                                   using m1::mirror;
                                                   return mirror(values[index],
                                                                 min_values[index],
                                                                 max_values[index]);
                                               });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_MIRROR_HPP
