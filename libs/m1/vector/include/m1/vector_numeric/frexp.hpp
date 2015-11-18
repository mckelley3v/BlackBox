#ifndef M1_VECTOR_NUMERIC_FREXP_HPP
#define M1_VECTOR_NUMERIC_FREXP_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/frexp.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T, typename I>
    impl::vector_copy_type<T> frexp(vector<T> const &v,
                                    vector<I> *exps) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T, typename I>
m1::impl::vector_copy_type<T>  m1::frexp(vector<T> const &v,
                                         vector<I> *exps) noexcept
{
    assert(exps != nullptr);

    return impl::generate_vector_copy<T>([&](auto index)
                                        {
                                            using m1::frexp;
                                            return frexp(v[index],
                                                         &(*exps)[index]);
                                        });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_FREXP_HPP
