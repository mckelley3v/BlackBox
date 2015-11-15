#ifndef M1_VECTOR_NUMERIC_EXP10_HPP
#define M1_VECTOR_NUMERIC_EXP10_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/exp10.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    impl::vector_copy_type<T> exp10(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
m1::impl::vector_copy_type<T> m1::exp10(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::exp10;
                                             return exp10(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_EXP10_HPP
