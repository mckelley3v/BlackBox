#ifndef M1_VECTOR_NUMERIC_POW_HPP
#define M1_VECTOR_NUMERIC_POW_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/pow.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T, typename E>
    constexpr impl::vector_copy_type<T> pow(vector<T> const &bases,
                                            E const &exp) noexcept;

    template <typename T, typename E>
    constexpr impl::vector_copy_type<T> pow(vector<T> const &bases,
                                            vector<E> const &exps) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T, typename E>
constexpr m1::impl::vector_copy_type<T> m1::pow(vector<T> const &bases,
                                                E const &exp) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::pow;
                                             return pow(bases[index], exp);
                                         });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, typename E>
constexpr m1::impl::vector_copy_type<T> m1::pow(vector<T> const &bases,
                                                vector<E> const &exps) noexcept
{
    // check dimensions explicitly since vector_copy_type<T, X> is invalid for T = floating point and X = integral
    static_assert(vector<T>::static_size == vector<E>::static_size, "Mismatched size");

    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::pow;
                                             return pow(bases[index], exps[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_POW_HPP
