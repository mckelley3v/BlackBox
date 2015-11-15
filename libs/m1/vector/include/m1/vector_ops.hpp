#ifndef M1_VECTOR_OPS_HPP
#define M1_VECTOR_OPS_HPP

#include "m1/vector_type.hpp"
#include "m1/vector_impl.hpp"
#include "m1/numeric/all_of.hpp"
#include "m1/numeric/any_of.hpp"
#include "m1/numeric/none_of.hpp"
#include "m1/numeric/inverse_sqrt.hpp"
#include "m1/numeric/sqrt.hpp"
#include "m1/numeric/sum.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    // aritmetic operators:
    template <typename L, typename R> vector<L>& operator += (vector<L> &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> vector<L>& operator -= (vector<L> &lhs, vector<R> const &rhs) noexcept;
    template <typename T> vector<T>& operator *= (vector<T> &lhs, typename vector<T>::const_reference rhs) noexcept;
    template <typename T> vector<T>& operator /= (vector<T> &lhs, typename vector<T>::const_reference rhs) noexcept;
    template <typename T> constexpr impl::vector_copy_type<T> operator + (vector<T> const &v) noexcept;
    template <typename T> constexpr impl::vector_copy_type<T> operator - (vector<T> const &v) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> operator + (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> operator - (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename T> constexpr impl::vector_copy_type<T> operator * (typename vector<T>::const_reference lhs, vector<T> const &rhs) noexcept;
    template <typename T> constexpr impl::vector_copy_type<T> operator * (vector<T> const &lhs, typename vector<T>::const_reference rhs) noexcept;
    template <typename T> constexpr impl::vector_copy_type<T> operator / (vector<T> const &lhs, typename vector<T>::const_reference rhs) noexcept;

    // logical operators:
    template <typename T> constexpr impl::vector_bool_type<T> operator ! (vector<T> const &v) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator && (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator || (vector<L> const &lhs, vector<R> const &rhs) noexcept;

    // relational operators:
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator == (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator != (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator <  (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator <= (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator >  (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_bool_type<L, R> operator >= (vector<L> const &lhs, vector<R> const &rhs) noexcept;

    // logical functions:
    template <typename B> constexpr bool all_of(vector<B> const &v) noexcept;
    template <typename B> constexpr bool any_of(vector<B> const &v) noexcept;
    template <typename B> constexpr bool none_of(vector<B> const &v) noexcept;
    template <typename B, typename L, typename R> constexpr impl::vector_copy_type<L, R> select(vector<B> const &condition, vector<L> const &lhs, vector<R> const &rhs) noexcept;

    // bitwise operators:
    template <typename L, typename R> vector<L>& operator &= (vector<L> &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> vector<L>& operator |= (vector<L> &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> vector<L>& operator ^= (vector<L> &lhs, vector<R> const &rhs) noexcept;
    template <typename T> constexpr impl::vector_copy_type<T> operator ~ (vector<T> const &v) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> operator & (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> operator | (vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> operator ^ (vector<L> const &lhs, vector<R> const &rhs) noexcept;

    // vector functions:
    template <typename T> constexpr impl::vector_copy_type<T> normalize(vector<T> const &v) noexcept;
    template <typename T> constexpr impl::vector_value_type<T> length(vector<T> const &v) noexcept;
    template <typename T> constexpr impl::vector_value_type<T> squared_length(vector<T> const &v) noexcept;
    template <typename T> constexpr impl::vector_value_type<T> inverse_length(vector<T> const &v) noexcept;
    template <typename L, typename R> constexpr impl::vector_value_type<L, R> dot(vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_value_type<L, R> distance(vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_value_type<L, R> squared_distance(vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_value_type<L, R> inverse_distance(vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> cross(vector<L> const &lhs, vector<R> const &rhs) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> reflect(vector<L> const &v, vector<R> const &normal) noexcept;
    template <typename L, typename R> constexpr impl::vector_copy_type<L, R> project(vector<L> const &v, vector<R> const &onto_u) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    template <typename L,
              typename R,
              std::size_t... Indices>
    constexpr vector_value_type<L, R> dot(vector<L> const &lhs,
                                          vector<R> const &rhs,
                                          index_sequence<Indices...> const /*indices*/) noexcept
    {
        return sum((lhs[(index_constant<Indices>())] * rhs[(index_constant<Indices>())])...);
    }

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================

template <typename L, typename R> m1::vector<L>& m1::operator += (vector<L> &lhs, vector<R> const &rhs) noexcept
{
    impl::for_each_vector_index<L, R>([&](auto index) { lhs[index] += rhs[index]; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> m1::vector<L>& m1::operator -= (vector<L> &lhs, vector<R> const &rhs) noexcept
{
    impl::for_each_vector_index<L, R>([&](auto index) { lhs[index] -= rhs[index]; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> m1::vector<T>& m1::operator *= (vector<T> &lhs, typename vector<T>::const_reference rhs) noexcept
{
    impl::for_each_vector_index<T>([&](auto index) { lhs[index] *= rhs; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> m1::vector<T>& m1::operator /= (vector<T> &lhs, typename vector<T>::const_reference rhs) noexcept
{
    impl::for_each_vector_index<T>([&](auto index) { lhs[index] /= rhs; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::operator + (vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { return +v[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::operator - (vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { return -v[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::operator + (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_copy<L, R>([&](auto index) { return lhs[index] + rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::operator - (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_copy<L, R>([&](auto index) { return lhs[index] - rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::operator * (typename vector<T>::const_reference lhs, vector<T> const &rhs) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { return lhs * rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::operator * (vector<T> const &lhs, typename vector<T>::const_reference rhs) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { return lhs[index] * rhs; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::operator / (vector<T> const &lhs, typename vector<T>::const_reference rhs) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { return lhs[index] / rhs; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_bool_type<T> m1::operator ! (vector<T> const &v) noexcept
{
    return impl::generate_vector_bool<T>([&](auto index) { return !v[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator && (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] && rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator || (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] || rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator == (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] == rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator != (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] != rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator <  (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] < rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator <= (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] <= rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator >  (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] > rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_bool_type<L, R> m1::operator >= (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_bool<L, R>([&](auto index) { return lhs[index] >= rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename B> constexpr bool m1::all_of(vector<B> const &v) noexcept
{
    return impl::accumulate_vector_values(M1_LAMBDA_FORWARD(all_of), v);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename B> constexpr bool m1::any_of(vector<B> const &v) noexcept
{
    return impl::accumulate_vector_values(M1_LAMBDA_FORWARD(any_of), v);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename B> constexpr bool m1::none_of(vector<B> const &v) noexcept
{
    return impl::accumulate_vector_values(M1_LAMBDA_FORWARD(none_of), v);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename B, typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::select(vector<B> const &condition, vector<L> const &lhs, vector<R> const &rhs) noexcept
{
   return impl::generate_vector_copy<L, R>([&](auto index) { return condition[index] ? lhs[index] : rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> m1::vector<L>& m1::operator &= (vector<L> &lhs, vector<R> const &rhs) noexcept
{
    impl::for_each_vector_index<L, R>([&](auto index) { lhs[index] &= rhs[index]; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> m1::vector<L>& m1::operator |= (vector<L> &lhs, vector<R> const &rhs) noexcept
{
    impl::for_each_vector_index<L, R>([&](auto index) { lhs[index] |= rhs[index]; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> m1::vector<L>& m1::operator ^= (vector<L> &lhs, vector<R> const &rhs) noexcept
{
    impl::for_each_vector_index<L, R>([&](auto index) { lhs[index] ^= rhs[index]; });
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::operator ~ (vector<T> const &v) noexcept
{
    return impl::generate_vector_copy<T>([&](auto index) { return ~v[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::operator & (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_copy<L, R>([&](auto index) { return lhs[index] & rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::operator | (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_copy<L, R>([&](auto index) { return lhs[index] | rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::operator ^ (vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::generate_vector_copy<L, R>([&](auto index) { return lhs[index] ^ rhs[index]; });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_copy_type<T> m1::normalize(vector<T> const &v) noexcept
{
    return v * inverse_length(v);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_value_type<T> m1::length(vector<T> const &v) noexcept
{
    using m1::sqrt;
    return sqrt(squared_length(v));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_value_type<T> m1::squared_length(vector<T> const &v) noexcept
{
    return dot(v, v);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T> constexpr m1::impl::vector_value_type<T> m1::inverse_length(vector<T> const &v) noexcept
{
    using m1::inverse_sqrt;
    return inverse_sqrt(squared_length(v));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_value_type<L, R> m1::dot(vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return impl::dot(lhs, rhs, impl::make_index_sequence<impl::vector_data_size<L, R>::value>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_value_type<L, R> m1::distance(vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return length(rhs - lhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_value_type<L, R> m1::squared_distance(vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return squared_length(rhs - lhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_value_type<L, R> m1::inverse_distance(vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    return inverse_length(rhs - lhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::cross(vector<L> const &lhs, vector<R> const &rhs) noexcept
{
    static_assert(vector<L>::static_size == 3, "cross product only defined for 3 dimensional vectors");
    static_assert(vector<R>::static_size == 3, "cross product only defined for 3 dimensional vectors");

    return impl::vector_copy_type<L, R> { lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                                          lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                                          lhs.x() * rhs.y() - lhs.y() * rhs.x() };
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::reflect(vector<L> const &v, vector<R> const &normal) noexcept
{
    return v - 2 * dot(v, normal) * normal;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename L, typename R> constexpr m1::impl::vector_copy_type<L, R> m1::project(vector<L> const &v, vector<R> const &onto_u) noexcept
{
    return (dot(v, onto_u) / squared_length(onto_u)) * onto_u;
}

// ====================================================================================================================

#endif // M1_VECTOR_OPS_HPP
