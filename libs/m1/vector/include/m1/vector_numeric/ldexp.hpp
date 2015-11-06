#ifndef M1_VECTOR_NUMERIC_LDEXP_HPP
#define M1_VECTOR_NUMERIC_LDEXP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/ldexp.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T, typename X> impl::vector_copy_type<T> ldexp(vector<T> const &v,
                                                                      vector<X> const &exps) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T, typename X> m1::impl::vector_copy_type<T> m1::ldexp(vector<T> const &v,
                                                                          vector<X> const &exps) noexcept
{
    // check dimensions explicitly since vector_copy_type<T, X> is invalid for T = floating point and X = integral
    static_assert(vector<T>::static_size == vector<X>::static_size, "Mismatched size");

    return impl::generate_vector_copy<T>([&](auto index) { using m1::ldexp; return ldexp(v[index], exps[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_LDEXP_HPP
