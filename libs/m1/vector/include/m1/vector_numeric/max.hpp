#ifndef M1_VECTOR_NUMERIC_MAX_HPP
#define M1_VECTOR_NUMERIC_MAX_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/max.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    constexpr impl::vector_value_type<T> max(vector<T> const &v) noexcept;

    template <typename T0, typename T1, typename...Ts>
    impl::vector_copy_type<T0, T1, Ts...> max(vector<T0> const &v0,
                                              vector<T1> const &v1,
                                              vector<Ts> const &...vN) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
constexpr m1::impl::vector_value_type<T> m1::max(vector<T> const &v) noexcept
{
    return impl::accumulate_vector_values(M1_LAMBDA_FORWARD(max), v);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T0, typename T1, typename...Ts>
m1::impl::vector_copy_type<T0, T1, Ts...> m1::max(vector<T0> const &v0,
                                                  vector<T1> const &v1,
                                                  vector<Ts> const &...vN) noexcept
{
    return impl::generate_vector_copy<T0, T1, Ts...>([&](auto index)
                                                     {
                                                         using m1::max;
                                                         return max(v0[index],
                                                                    v1[index],
                                                                    vN[index]...);
                                                     });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_MAX_HPP
