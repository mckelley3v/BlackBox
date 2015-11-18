#ifndef M1_VECTOR_NUMERIC_ROUND_HPP
#define M1_VECTOR_NUMERIC_ROUND_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/round.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    constexpr impl::vector_copy_type<T> round(vector<T> const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
constexpr m1::impl::vector_copy_type<T> m1::round(vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index)
                                         {
                                             using m1::round;
                                             return round(v[index]);
                                         });
}

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_ROUND_HPP
