#ifndef M1_VECTOR_NUMERIC_FREXP_HPP
#define M1_VECTOR_NUMERIC_FREXP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/frexp.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename S, typename E, typename T> void frexp(vector<S> *scales,
                                                             vector<E> *exps,
                                                             vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

  // ====================================================================================================================

template <typename S, typename E, typename T> void m1::frexp(vector<S> * const scales,
                                                             vector<E> * const exps,
                                                             vector<T> const &v) noexcept
{
    assert(scales != nullptr);
    assert(exps != nullptr);
    impl::for_each_vector_index<S, E, T>([&](auto index) { using m1::frexp; frexp(&((*scales)[index]), &((*exps)[index]), v[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_FREXP_HPP
