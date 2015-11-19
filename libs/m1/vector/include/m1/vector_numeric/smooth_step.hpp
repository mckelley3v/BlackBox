#ifndef M1_VECTOR_NUMERIC_SMOOTH_STEP_HPP
#define M1_VECTOR_NUMERIC_SMOOTH_STEP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/smooth_step.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename E0, typename E1, typename T>
    constexpr impl::vector_copy_type<T> smooth_step(E0 const &edge0,
                                                    E1 const &edge1,
                                                    vector<T> const &v) noexcept;

    template <typename E0, typename E1, typename T>
    constexpr impl::vector_copy_type<E0, E1, T> smooth_step(vector<E0> const &edge0,
                                                            vector<E1> const &edge1,
                                                            vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename E0, typename E1, typename T>
constexpr m1::impl::vector_copy_type<T> m1::smooth_step(E0 const &edge0,
                                                        E1 const &edge1,
                                                        vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::smooth_step;
                                             return smooth_step(edge0,
                                                                edge1,
                                                                v[index]);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename E0, typename E1, typename T>
constexpr m1::impl::vector_copy_type<E0, E1, T> m1::smooth_step(vector<E0> const &edge0,
                                                                vector<E1> const &edge1,
                                                                vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<E0, E1, T>([&](auto index)
                                                 {
                                                     using m1::smooth_step;
                                                     return smooth_step(edge0[index],
                                                                        edge1[index],
                                                                        v[index]);
                                                 });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_SMOOTH_STEP_HPP
