#ifndef M1_VECTOR_NUMERIC_LINEAR_STEP_HPP
#define M1_VECTOR_NUMERIC_LINEAR_STEP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/linear_step.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename E0, typename E1, typename T>
    constexpr impl::vector_copy_type<T> linear_step(E0 const &edge0,
                                                    E1 const &edge1,
                                                    vector<T> const &v) noexcept;

    template <typename E0, typename E1, typename T>
    constexpr impl::vector_copy_type<E0, E1, T> linear_step(vector<E0> const &edge0,
                                                            vector<E1> const &edge1,
                                                            vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename E0, typename E1, typename T>
constexpr m1::impl::vector_copy_type<T> m1::linear_step(E0 const &edge0,
                                                        E1 const &edge1,
                                                        vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::linear_step;
                                             return linear_step(edge0,
                                                                edge1,
                                                                v[index]);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename E0, typename E1, typename T>
constexpr m1::impl::vector_copy_type<E0, E1, T> m1::linear_step(vector<E0> const &edge0,
                                                                vector<E1> const &edge1,
                                                                vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<E0, E1, T>([&](auto index)
                                                 {
                                                     using m1::linear_step;
                                                     return linear_step(edge0[index],
                                                                        edge1[index],
                                                                        v[index]);
                                                 });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_LINEAR_STEP_HPP
