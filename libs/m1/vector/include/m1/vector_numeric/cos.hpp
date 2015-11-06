#ifndef M1_VECTOR_NUMERIC_COS_HPP
#define M1_VECTOR_NUMERIC_COS_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/cos.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T> impl::vector_copy_type<T> cos(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

  // ====================================================================================================================

template <typename T> m1::impl::vector_copy_type<T> m1::cos(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { using m1::cos; return cos(v[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_COS_HPP
