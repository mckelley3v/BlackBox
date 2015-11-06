#ifndef M1_VECTOR_NUMERIC_IS_CLOSE_HPP
#define M1_VECTOR_NUMERIC_IS_CLOSE_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/is_close.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename L, typename R> impl::vector_bool_type<L, R> is_close(vector<L> const &lhs,
                                                                            vector<R> const &rhs) noexcept;

    template <typename L, typename R, typename T> impl::vector_bool_type<L, R> is_close(vector<L> const &lhs,
                                                                                        vector<R> const &rhs,
                                                                                        T const &relative_tolerance,
                                                                                        T const &absolute_tolerance) noexcept;

    template <typename L, typename R, typename T0, typename T1> impl::vector_bool_type<L, R, T0, T1> is_close(vector<L> const &lhs,
                                                                                                              vector<R> const &rhs,
                                                                                                              vector<T0> const &relative_tolerance,
                                                                                                              vector<T1> const &absolute_tolerance) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename L, typename R> m1::impl::vector_bool_type<L, R> m1::is_close(vector<L> const &lhs,
                                                                                vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { using m1::is_close; return is_close(lhs[index], rhs[index]); });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R, typename T> m1::impl::vector_bool_type<L, R> m1::is_close(vector<L> const &lhs,
                                                                                            vector<R> const &rhs,
                                                                                            T const &relative_tolerance,
                                                                                            T const &absolute_tolerance) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { using m1::is_close; return is_close(lhs[index], rhs[index], relative_tolerance, absolute_tolerance); });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R, typename T0, typename T1> m1::impl::vector_bool_type<L, R, T0, T1> m1::is_close(vector<L> const &lhs,
                                                                                                                  vector<R> const &rhs,
                                                                                                                  vector<T0> const &relative_tolerance,
                                                                                                                  vector<T1> const &absolute_tolerance) noexcept
{
    return impl::generate_vector_bool<L, R, T0, T1>([&](auto index) { using m1::is_close; return is_close(lhs[index], rhs[index], relative_tolerance[index], absolute_tolerance[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_IS_CLOSE_HPP
