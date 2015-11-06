#ifndef M1_VECTOR_NUMERIC_INVERSE_LERP_HPP
#define M1_VECTOR_NUMERIC_INVERSE_LERP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/inverse_lerp.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T0, typename T1, typename T> constexpr impl::vector_copy_type<T0, T1, T> inverse_lerp(vector<T0> const &v0,
                                                                                                             vector<T1> const &v1,
                                                                                                             vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

  // ====================================================================================================================

template <typename T0, typename T1, typename T> constexpr m1::impl::vector_copy_type<T0, T1, T> m1::inverse_lerp(vector<T0> const &v0,
                                                                                                                 vector<T1> const &v1,
                                                                                                                 vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T0, T1, T>([&](auto index) { using m1::inverse_lerp; return inverse_lerp(v0[index], v1[index], v[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_INVERSE_LERP_HPP
