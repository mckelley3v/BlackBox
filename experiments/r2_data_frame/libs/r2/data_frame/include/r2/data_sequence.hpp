#ifndef T2_DATA_SEQUENCE_HPP
#define T2_DATA_SEQUENCE_HPP

#include "r2/data_source.hpp"
#include <memory>
#include <cassert>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    // generic data sequence class providing useful operations on any given underlying data
    template <typename T>
    class data_sequence
    {
    public:
        // types:
        typedef T value_type;

        // construct/move/destroy:
        data_sequence() = default;
        explicit data_sequence(std::shared_ptr<data_source<T>> &&source_ptr);
        data_sequence(data_sequence &&rhs) = default;
        data_sequence& operator = (data_sequence &&rhs) = default;
        ~data_sequence() = default;

        // properties:
        std::size_t size() const;
        value_type const& operator [] (std::size_t index) const;

        source_ptr_type const& get_source_ptr() const;

    private:
        // copy (deleted):
        data_sequence(data_sequence const &rhs) = delete;
        data_sequence& operator = (data_sequence const &rhs) = delete;

        // types:
        typedef std::shared_ptr<data_source<T>> source_ptr_type;

        // members:
        source_ptr_type m_SourcePtr {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    // non-member functions:
    //  arithmetic operators:
    template <typename T> data_sequence<T>& operator += (data_sequence<T> &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T>& operator -= (data_sequence<T> &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T>& operator *= (data_sequence<T> &lhs, typename data_sequence<T>::value_type const &rhs);
    template <typename T> data_sequence<T>& operator /= (data_sequence<T> &lhs, typename data_sequence<T>::value_type const &rhs);
    template <typename T> data_sequence<T> operator + (data_sequence<T> const &v);
    template <typename T> data_sequence<T> operator - (data_sequence<T> const &v);
    template <typename T> data_sequence<T> operator + (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> operator - (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> operator * (typename data_sequence<T>::value_type const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> operator * (data_sequence<T> const &lhs, typename data_sequence<T>::value_type const &rhs);
    template <typename T> data_sequence<T> operator / (data_sequence<T> const &lhs, typename data_sequence<T>::value_type const &rhs);

    //  bitwise operators:
    template <typename T> data_sequence<T>& operator &= (data_sequence<T> &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T>& operator |= (data_sequence<T> &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T>& operator ^= (data_sequence<T> &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> operator ~ (data_sequence<T> const &v);
    template <typename T> data_sequence<T> operator & (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> operator | (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> operator ^ (data_sequence<T> const &lhs, data_sequence<T> const &rhs);

    //  logical operators:
    template <typename T> data_sequence<bool> operator ! (data_sequence<T> const &v);
    template <typename T> data_sequence<bool> operator && (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> operator || (data_sequence<T> const &lhs, data_sequence<T> const &rhs);

    //  relational operators:
    template <typename T> data_sequence<bool> operator == (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> operator != (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> operator <  (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> operator <= (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> operator >  (data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> operator >= (data_sequence<T> const &lhs, data_sequence<T> const &rhs);

    //  logical functions:
    bool all_of(data_sequence<bool> const &v);
    bool any_of(data_sequence<bool> const &v);
    bool none_of(data_sequence<bool> const &v);
    template <typename T> data_sequence<T> select(data_sequence<bool> const &condition, data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> is_close(data_sequence<T> &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<bool> is_close(data_sequence<T> &lhs, data_sequence<T> const &rhs, T const &relative_tolerance, T const &absolute_tolerance);
    template <typename T> data_sequence<bool> is_finite(data_sequence<T> const &v);
    template <typename T> data_sequence<bool> is_inf(data_sequence<T> const &v);
    template <typename T> data_sequence<bool> is_nan(data_sequence<T> const &v);
    template <typename T> data_sequence<bool> is_pow2(data_sequence<T> const &v);
    template <typename T> data_sequence<bool> is_small(data_sequence<T> const &v);
    template <typename T> data_sequence<bool> is_small(data_sequence<T> const &v, T const &tolerance);

    //  pointwise functions:
    template <typename T> data_sequence<T> abs(data_sequence<T> const &v);
    template <typename T> data_sequence<T> acos(data_sequence<T> const &v);
    template <typename T> data_sequence<T> asin(data_sequence<T> const &v);
    template <typename T> data_sequence<T> atan(data_sequence<T> const &v);
    template <typename T> data_sequence<T> atan2(data_sequence<T> const &y, data_sequence<T> const &x);
    template <typename T> data_sequence<T> ceil(data_sequence<T> const &v);
    template <typename T> data_sequence<T> clamp(data_sequence<T> const &v, T const &min_value, T const &max_value);
    template <typename T> data_sequence<T> clamp(data_sequence<T> const &v, data_sequence<T> const &min_values, data_sequence<T> const &max_values);
    template <typename T> data_sequence<T> cos(data_sequence<T> const &v);
    template <typename T> data_sequence<T> cosh(data_sequence<T> const &v);
    template <typename T> data_sequence<T> degrees(data_sequence<T> const &v);
    template <typename T> data_sequence<T> divide(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> exp(data_sequence<T> const &v);
    template <typename T> data_sequence<T> exp10(data_sequence<T> const &v);
    template <typename T> data_sequence<T> exp2(data_sequence<T> const &v);
    template <typename T> data_sequence<T> floor(data_sequence<T> const &v);
    template <typename T> data_sequence<T> fract(data_sequence<T> const &v);
    template <typename T> data_sequence<T> frexp(data_sequence<T> const &v);
    template <typename T> data_sequence<T> inverse_lerp(T const &x0, T const &x1, data_sequence<T> const &v);
    template <typename T> data_sequence<T> inverse_lerp(data_sequence<T> const &x0, data_sequence<T> const &x1, data_sequence<T> const &v);
    template <typename T> data_sequence<T> inverse_sqrt(data_sequence<T> const &v);
    template <typename T> data_sequence<T> ldexp(data_sequence<T> const &v, data_sequence<int> const &exps);
    template <typename T> data_sequence<T> lerp(data_sequence<T> const &v0, data_sequence<T> const &v1, T const &t);
    template <typename T> data_sequence<T> lerp(data_sequence<T> const &v0, data_sequence<T> const &v1, data_sequence<T> const &t);
    template <typename T> data_sequence<T> linear_step(T const &edge0, T const &edge1, data_sequence<T> const &v);
    template <typename T> data_sequence<T> linear_step(data_sequence<T> const &edge0, data_sequence<T> const &edge1, data_sequence<T> const &v);
    template <typename T> data_sequence<T> log(data_sequence<T> const &v);
    template <typename T> data_sequence<T> log10(data_sequence<T> const &v);
    template <typename T> data_sequence<T> log2(data_sequence<T> const &v);
    template <typename T> data_sequence<T> max(data_sequence<T> const &v);
    template <typename T> data_sequence<T> max(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T, typename ...TN> data_sequence<T> max(data_sequence<T> const &v0, data_sequence<T> const &v1, data_sequence<TN> const &...vN);
    template <typename T> data_sequence<T> min(data_sequence<T> const &v);
    template <typename T> data_sequence<T> min(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T, typename ...TN> data_sequence<T> min(data_sequence<T> const &v0, data_sequence<T> const &v1, data_sequence<TN> const &...vN);
    template <typename T> data_sequence<T> mirror(data_sequence<T> const &v, T const &min_value, T const &max_value);
    template <typename T> data_sequence<T> mirror(data_sequence<T> const &v, data_sequence<T> const &min_value, data_sequence<T> const &max_value);
    template <typename T> data_sequence<T> mix(data_sequence<T> const &v0, data_sequence<T> const &v1, T const &t);
    template <typename T> data_sequence<T> mix(data_sequence<T> const &v0, data_sequence<T> const &v1, data_sequence<T> const &t);
    template <typename T> data_sequence<T> mod(data_sequence<T> const &numer, T const &denom);
    template <typename T> data_sequence<T> mod(T const &numer, data_sequence<T> const &denom);
    template <typename T> data_sequence<T> mod(data_sequence<T> const &numer, data_sequence<T> const &denom);
    template <typename T> data_sequence<T> modf(data_sequence<T> const &v, data_sequence<T> *int_parts);
    template <typename T> data_sequence<T> multiply(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> data_sequence<T> pow(data_sequence<T> const &v, T const &exp);
    template <typename T> data_sequence<T> pow(data_sequence<T> const &v, data_sequence<T> const &exps);
    template <typename T> data_sequence<T> radians(data_sequence<T> const &v);
    template <typename T> data_sequence<T> repeat(data_sequence<T> const &v, T const &min_value, T const &max_value);
    template <typename T> data_sequence<T> repeat(data_sequence<T> const &v, data_sequence<T> const &min_value, data_sequence<T> const &max_value);
    template <typename T> data_sequence<T> round(data_sequence<T> const &v);
    template <typename T> data_sequence<T> round_even(data_sequence<T> const &v);
    template <typename T> data_sequence<T> saturate(data_sequence<T> const &v);
    template <typename T> data_sequence<T> sign(data_sequence<T> const &v);
    template <typename T> data_sequence<T> sin(data_sequence<T> const &v);
    template <typename T> data_sequence<T> sinh(data_sequence<T> const &v);
    template <typename T> data_sequence<T> smooth_step(T const &edge0, T const &edge1, data_sequence<T> const &v);
    template <typename T> data_sequence<T> smooth_step(data_sequence<T> const &edge0, data_sequence<T> const &edge1, data_sequence<T> const &v);
    template <typename T> data_sequence<T> sqrt(data_sequence<T> const &v);
    template <typename T> data_sequence<T> step(T const &edge, data_sequence<T> const &v);
    template <typename T> data_sequence<T> step(data_sequence<T> const &edge, data_sequence<T> const &v);
    template <typename T> data_sequence<T> tan(data_sequence<T> const &v);
    template <typename T> data_sequence<T> tanh(data_sequence<T> const &v);
    template <typename T> data_sequence<T> trunc(data_sequence<T> const &v);

    //  vector functions:
    template <typename T> data_sequence<T> normalize(data_sequence<T> const &v);
    template <typename T> T length(data_sequence<T> const &v);
    template <typename T> T squared_length(data_sequence<T> const &v);
    template <typename T> T inverse_length(data_sequence<T> const &v);
    template <typename T> T dot(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> T distance(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> T squared_distance(data_sequence<T> const &lhs, data_sequence<T> const &rhs);
    template <typename T> T inverse_distance(data_sequence<T> const &lhs, data_sequence<T> const &rhs);

    // ================================================================================================================
} // namespace r2

// ====================================================================================================================
// r2::data_sequence<T>
// ====================================================================================================================

template <typename T>
/*explicit*/ r2::data_sequence<T>::data_sequence(std::shared_ptr<data_source<T>> &&source_ptr)
    : m_SourcePtr(std::move(source_ptr))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
std::size_t r2::data_sequence<T>::size() const
{
    return m_SourcePtr ? m_SourcePtr->size() : 0;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename r2::data_sequence<T>::value_type const& r2::data_sequence<T>::operator [] (std::size_t const index) const
{
    assert(index < size());
    return (*m_SourcePtr)[index];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename r2::data_sequence<T>::source_ptr_type const& r2::data_sequence<T>::get_source_ptr() const
{
    return m_SourcePtr;
}

// ====================================================================================================================

#endif // T2_DATA_SEQUENCE_HPP
