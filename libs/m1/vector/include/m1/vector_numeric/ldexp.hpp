#ifndef M1_VECTOR_NUMERIC_LDEXP_HPP
#define M1_VECTOR_NUMERIC_LDEXP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/ldexp.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T, typename E>
    impl::vector_copy_type<T> ldexp(vector<T> const &v,
                                    vector<E> const &exps) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T, typename E>
m1::impl::vector_copy_type<T> m1::ldexp(vector<T> const &v,
                                        vector<E> const &exps) noexcept
{
    // check dimensions explicitly since vector_copy_type<T, E> is invalid for T = floating point and E = integral
    static_assert(vector<T>::static_size == vector<E>::static_size, "Mismatched size");

    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::ldexp;
                                             return ldexp(v[index],
                                                          exps[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_LDEXP_HPP
