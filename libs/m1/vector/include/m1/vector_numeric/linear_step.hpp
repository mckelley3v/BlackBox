#ifndef M1_VECTOR_NUMERIC_LINEAR_STEP_HPP
#define M1_VECTOR_NUMERIC_LINEAR_STEP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/linear_step.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T0, typename T1, typename T>
    constexpr impl::vector_copy_type<T0, T1> linear_step(vector<T0> const &edge0,
                                                         vector<T1> const &edge1,
                                                         T const &x) noexcept;

    template <typename T0, typename T1, typename T>
    constexpr impl::vector_copy_type<T0, T1, T> linear_step(vector<T0> const &edge0,
                                                            vector<T1> const &edge1,
                                                            vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T0, typename T1, typename T>
constexpr m1::impl::vector_copy_type<T0, T1> m1::linear_step(vector<T0> const &edge0,
                                                             vector<T1> const &edge1,
                                                             T const &x) noexcept
{
    return impl::generate_vector_copy<T0, T1>([&](auto index)
                                              {
                                                  using m1::linear_step;
                                                  return linear_step(edge0[index],
                                                                     edge1[index],
                                                                     x);
                                              });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T0, typename T1, typename T>
constexpr m1::impl::vector_copy_type<T0, T1, T> m1::linear_step(vector<T0> const &edge0,
                                                                vector<T1> const &edge1,
                                                                vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T0, T1, T>([&](auto index)
                                                 {
                                                     using m1::linear_step;
                                                     return linear_step(edge0[index],
                                                                        edge1[index],
                                                                        v[index]);
                                                 });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_LINEAR_STEP_HPP
