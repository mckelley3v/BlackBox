#ifndef M1_VECTOR_NUMERIC_ATAN_HPP
#define M1_VECTOR_NUMERIC_ATAN_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/atan.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    impl::vector_copy_type<T> atan(vector<T> const &v) noexcept;

    template <typename Y, typename X>
    impl::vector_copy_type<Y, X> atan2(vector<Y> const &y,
                                       vector<X> const &x) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
m1::impl::vector_copy_type<T> m1::atan(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::atan;
                                             return atan(v[index]);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Y, typename X>
m1::impl::vector_copy_type<Y, X> m1::atan2(vector<Y> const &y,
                                           vector<X> const &x) noexcept
{
    return impl::generate_vector_copy<Y, X>([&](auto index)
                                            {
                                                using m1::atan2;
                                                return atan2(y[index],
                                                             x[index]);
                                            });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_ATAN_HPP
