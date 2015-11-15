#ifndef M1_VECTOR_NUMERIC_LOG2_HPP
#define M1_VECTOR_NUMERIC_LOG2_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/log2.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    impl::vector_copy_type<T> log2(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
m1::impl::vector_copy_type<T> m1::log2(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::log2;
                                             return log2(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_LOG2_HPP
