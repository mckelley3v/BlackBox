#ifndef M1_VECTOR_NUMERIC_STEP_HPP
#define M1_VECTOR_NUMERIC_STEP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/step.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename E, typename T>
    constexpr impl::vector_copy_type<T> step(E const &edge,
                                             vector<T> const &v) noexcept;

    template <typename E, typename T>
    constexpr impl::vector_copy_type<E, T> step(vector<E> const &edge,
                                                vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename E, typename T>
constexpr m1::impl::vector_copy_type<T> m1::step(E const &edge,
                                                 vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::step;
                                             return step(edge,
                                                         v[index]);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename E, typename T>
constexpr m1::impl::vector_copy_type<E, T> m1::step(vector<E> const &edge,
                                                    vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<E, T>([&](auto index)
                                            {
                                                using m1::step;
                                                return step(edge[index],
                                                            v[index]);
                                            });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_STEP_HPP
