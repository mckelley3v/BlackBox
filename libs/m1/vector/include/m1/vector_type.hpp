#ifndef M1_VECTOR_TYPE_HPP
#define M1_VECTOR_TYPE_HPP

#include "m1/vector_traits.hpp"
#include <stdexcept>
#include <utility>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    class vector
    {
    public:
        // types:
        typedef T data_type;
        typedef vector_data_traits<data_type> traits_type;
        typedef typename traits_type::value_type value_type;
        typedef typename traits_type::reference reference;
        typedef typename traits_type::const_reference const_reference;

        // constants:
        constexpr static std::size_t const static_size = traits_type::static_size;

        // construct/copy/move/destroy:
        constexpr vector() noexcept = default;
        template <typename U> constexpr explicit vector(U &&u) noexcept;
        template <typename U0, typename... UN> constexpr vector(U0 &&u0, UN &&...uN) noexcept;
        vector(vector &&rhs) noexcept = default;
        vector(vector const &rhs) noexcept = default;
        vector& operator = (vector &&rhs) noexcept = default;
        vector& operator = (vector const &rhs) noexcept = default;
        ~vector() noexcept = default;

        // element access:
        reference x() noexcept;
        constexpr const_reference x() const noexcept;

        reference y() noexcept;
        constexpr const_reference y() const noexcept;

        reference z() noexcept;
        constexpr const_reference z() const noexcept;

        reference w() noexcept;
        constexpr const_reference w() const noexcept;

        // indexed access:
        reference operator [] (std::size_t index) noexcept;
        constexpr const_reference operator [] (std::size_t index) const noexcept;
        template <std::size_t I> reference operator [] (index_constant<I> index) noexcept;
        template <std::size_t I> constexpr const_reference operator [] (index_constant<I> index) const noexcept;

        // range checked indexed access:
        reference at(std::size_t index);
        constexpr const_reference at(std::size_t index) const;
        template <std::size_t I> reference at(index_constant<I> index);
        template <std::size_t I> constexpr const_reference at(index_constant<I> index) const;

        // size:
        constexpr std::size_t size() const noexcept;

        // members:
        data_type data;
    };

    // ================================================================================================================

    // construction:
    template <typename... Ts>
    constexpr vector<std::common_type_t<Ts...>[sizeof...(Ts)]> make_vector(Ts &&...ts) noexcept;

    template <typename T>
    constexpr vector<T&> make_vector_ref(T &&v) noexcept;

    template <typename T>
    constexpr vector<T const&> make_vector_cref(T const &v) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
template <typename U>
constexpr /*explicit*/ m1::vector<T>::vector(U &&u) noexcept
    : data{std::forward<U>(u)}
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename U0, typename... UN>
constexpr m1::vector<T>::vector(U0 &&u0, UN &&...uN) noexcept
    : data{std::forward<U0>(u0), std::forward<UN>(uN)...}
{
    static_assert(static_size == (sizeof...(UN) +1), "Mismatched size");
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::vector<T>::reference m1::vector<T>::x() noexcept
{
    static_assert(static_size > 0, "x component unavailable");
    return traits_type::ref(data, index_constant<0>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::x() const noexcept
{
    static_assert(static_size > 0, "x component unavailable");
    return traits_type::get(data, index_constant<0>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::vector<T>::reference m1::vector<T>::y() noexcept
{
    static_assert(static_size > 1, "y component unavailable");
    return traits_type::ref(data, index_constant<1>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::y() const noexcept
{
    static_assert(static_size > 1, "y component unavailable");
    return traits_type::get(data, index_constant<1>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::vector<T>::reference m1::vector<T>::z() noexcept
{
    static_assert(static_size > 2, "z component unavailable");
    return traits_type::ref(data, index_constant<2>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::z() const noexcept
{
    static_assert(static_size > 2, "z component unavailable");
    return traits_type::get(data, index_constant<2>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::vector<T>::reference m1::vector<T>::w() noexcept
{
    static_assert(static_size > 3, "w component unavailable");
    return traits_type::ref(data, index_constant<3>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::w() const noexcept
{
    static_assert(static_size > 3, "w component unavailable");
    return traits_type::get(data, index_constant<3>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::vector<T>::reference m1::vector<T>::operator [] (std::size_t const index) noexcept
{
    assert(index < static_size);
    return traits_type::ref(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::operator [] (std::size_t const index) const noexcept
{
    assert(index < static_size);
    return traits_type::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
typename m1::vector<T>::reference m1::vector<T>::operator [] (index_constant<I> const index) noexcept
{
    static_assert(I < static_size, "Invalid index");
    return traits_type::ref(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::operator [] (index_constant<I> const index) const noexcept
{
    static_assert(I < static_size, "Invalid index");
    return traits_type::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::vector<T>::reference m1::vector<T>::at(std::size_t const index)
{
    if (index < static_size)
    {
        return traits_type::ref(data, index);
    }

    throw std::out_of_range("Invalid index");
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::at(std::size_t const index) const
{
    if (index < static_size)
    {
        return traits_type::get(data, index);
    }

    throw std::out_of_range("Invalid index");
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
typename m1::vector<T>::reference m1::vector<T>::at(index_constant<I> const index)
{
    return traits_type::ref(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
constexpr typename m1::vector<T>::const_reference m1::vector<T>::at(index_constant<I> const index) const
{
    return traits_type::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr std::size_t m1::vector<T>::size() const noexcept
{
    return static_size;
}

// ====================================================================================================================

template <typename... Ts>
constexpr m1::vector<std::common_type_t<Ts...>[sizeof...(Ts)]> m1::make_vector(Ts &&...ts) noexcept
{
    return vector<std::common_type_t<Ts...>[sizeof...(Ts)]> { std::forward<Ts>(ts)... };
}

// ====================================================================================================================

template <typename T>
constexpr m1::vector<T&> m1::make_vector_ref(T &&v) noexcept
{
    return vector<T&> { std::forward<T>(v) };
}

// ====================================================================================================================

template <typename T>
constexpr m1::vector<T const&> m1::make_vector_cref(T const &v) noexcept
{
    return vector<T const&> { v };
}

// ====================================================================================================================

#endif //M1_VECTOR_TYPE_HPP
