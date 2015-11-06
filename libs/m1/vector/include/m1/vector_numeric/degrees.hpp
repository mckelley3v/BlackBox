#ifndef M1_VECTOR_NUMERIC_DEGREES_HPP
#define M1_VECTOR_NUMERIC_DEGREES_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/degrees.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T> constexpr impl::vector_copy_type<T> degrees(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

  // ====================================================================================================================

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::degrees(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { using m1::degrees; return degrees(v[index]); });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_DEGREES_HPP
