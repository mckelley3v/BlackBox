#ifndef M1_VECTOR_NUMERIC_MIX_HPP
#define M1_VECTOR_NUMERIC_MIX_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/mix.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T0, typename T1, typename T>
    constexpr impl::vector_copy_type<T0, T1> mix(vector<T0> const &v0,
                                                 vector<T1> const &v1,
                                                 T const &t) noexcept;

    template <typename T0, typename T1, typename T>
    constexpr impl::vector_copy_type<T0, T1, T> mix(vector<T0> const &v0,
                                                    vector<T1> const &v1,
                                                    vector<T> const &t) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T0, typename T1, typename T>
constexpr m1::impl::vector_copy_type<T0, T1> m1::mix(vector<T0> const &v0,
                                                     vector<T1> const &v1,
                                                     T const &t) noexcept
{
    return impl::generate_vector_copy<T0, T1>([&](auto index)
                                              {
                                                  using m1::mix;
                                                  return mix(v0[index],
                                                             v1[index],
                                                             t);
                                              });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T0, typename T1, typename T>
constexpr m1::impl::vector_copy_type<T0, T1, T> m1::mix(vector<T0> const &v0,
                                                        vector<T1> const &v1,
                                                        vector<T> const &t) noexcept
{
    return impl::generate_vector_copy<T0, T1, T>([&](auto index)
                                                 {
                                                     using m1::mix;
                                                     return mix(v0[index],
                                                                v1[index],
                                                                t[index]);
                                                 });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_MIX_HPP
