#ifndef M1_VECTOR_TRAITS_HPP
#define M1_VECTOR_TRAITS_HPP

#include <type_traits>
#include <cstddef>
#include <cassert>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    class vector;

    template <typename T>
    struct vector_data_traits;

    template <std::size_t I>
    using index_constant = std::integral_constant<std::size_t, I>;

    // ================================================================================================================

    template <typename T>
    struct vector_data_traits<T const>
    {
        // types:
        typedef T const data_type;
        typedef T copy_type;
        typedef typename vector_data_traits<T>::value_type value_type;
        typedef typename vector_data_traits<T>::const_reference reference;
        typedef typename vector_data_traits<T>::const_reference const_reference;

        // constants:
        constexpr static std::size_t const static_size = vector_data_traits<T>::static_size;

        // element access:
        static reference ref(T const &data, std::size_t index);
        template <std::size_t I> static reference ref(T const &data, index_constant<I> index);

        constexpr static const_reference get(T const &data, std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const &data, index_constant<I> index);
    };

    // ================================================================================================================

    template <typename T>
    struct vector_data_traits<T&>
    {
        // types:
        typedef T& data_type;
        typedef T copy_type;
        typedef typename vector_data_traits<T>::reference value_type;
        typedef typename vector_data_traits<T>::reference reference;
        typedef typename vector_data_traits<T>::const_reference const_reference;

        // constants:
        constexpr static std::size_t const static_size = vector_data_traits<T>::static_size;

        // element access:
        static reference ref(T &data, std::size_t index);
        template <std::size_t I> static reference ref(T &data, index_constant<I> index);

        constexpr static const_reference get(T const &data, std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const &data, index_constant<I> index);
    };

    // ================================================================================================================

    template <typename T>
    struct vector_data_traits<T const&>
    {
        // types:
        typedef T const& data_type;
        typedef T copy_type;
        typedef typename vector_data_traits<T>::const_reference value_type;
        typedef typename vector_data_traits<T>::const_reference reference;
        typedef typename vector_data_traits<T>::const_reference const_reference;

        // constants:
        constexpr static std::size_t const static_size = vector_data_traits<T>::static_size;

        // element access:
        static reference ref(T const &data, std::size_t index);
        template <std::size_t I> static reference ref(T const &data, index_constant<I> index);

        constexpr static const_reference get(T const &data, std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const &data, index_constant<I> index);
    };

    // ================================================================================================================

    template <typename T, std::size_t N>
    struct vector_data_traits<T[N]>
    {
        // types:
        typedef T data_type[N];
        typedef T copy_type[N];
        typedef T value_type;
        typedef T& reference;
        typedef T const& const_reference;

        // constants:
        constexpr static std::size_t const static_size = N;

        // element access:
        static reference ref(T (&data)[N], std::size_t index);
        template <std::size_t I> static reference ref(T (&data)[N], index_constant<I> index);

        constexpr static const_reference get(T const (&data)[N], std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const (&data)[N], index_constant<I> index);
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename T>
/*static*/ typename m1::vector_data_traits<T const>::reference m1::vector_data_traits<T const>::ref(T const &data, std::size_t const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
/*static*/ typename m1::vector_data_traits<T const>::reference m1::vector_data_traits<T const>::ref(T const &data, index_constant<I> const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr /*static*/ typename m1::vector_data_traits<T const>::const_reference m1::vector_data_traits<T const>::get(T const &data, std::size_t const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
constexpr /*static*/ typename m1::vector_data_traits<T const>::const_reference m1::vector_data_traits<T const>::get(T const &data, index_constant<I> const index)
{
    return vector_data_traits<T>::get(data, index);
}

// ====================================================================================================================

template <typename T>
/*static*/ typename m1::vector_data_traits<T&>::reference m1::vector_data_traits<T&>::ref(T &data, std::size_t const index)
{
    return vector_data_traits<T>::ref(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
/*static*/ typename m1::vector_data_traits<T&>::reference m1::vector_data_traits<T&>::ref(T &data, index_constant<I> const index)
{
    return vector_data_traits<T>::ref(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr /*static*/ typename m1::vector_data_traits<T&>::const_reference m1::vector_data_traits<T&>::get(T const &data, std::size_t const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
constexpr /*static*/ typename m1::vector_data_traits<T&>::const_reference m1::vector_data_traits<T&>::get(T const &data, index_constant<I> const index)
{
    return vector_data_traits<T>::get(data, index);
}

// ====================================================================================================================

template <typename T>
/*static*/ typename m1::vector_data_traits<T const&>::reference m1::vector_data_traits<T const&>::ref(T const &data, std::size_t const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
/*static*/ typename m1::vector_data_traits<T const&>::reference m1::vector_data_traits<T const&>::ref(T const &data, index_constant<I> const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr /*static*/ typename m1::vector_data_traits<T const&>::const_reference m1::vector_data_traits<T const&>::get(T const &data, std::size_t const index)
{
    return vector_data_traits<T>::get(data, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <std::size_t I>
constexpr /*static*/ typename m1::vector_data_traits<T const&>::const_reference m1::vector_data_traits<T const&>::get(T const &data, index_constant<I> const index)
{
    return vector_data_traits<T>::get(data, index);
}

// ====================================================================================================================

template <typename T, std::size_t N>
/*static*/ typename m1::vector_data_traits<T[N]>::reference m1::vector_data_traits<T[N]>::ref(T(&data)[N], std::size_t const index)
{
    assert(index < N);
    return data[index];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, std::size_t N>
template <std::size_t I>
/*static*/ typename m1::vector_data_traits<T[N]>::reference m1::vector_data_traits<T[N]>::ref(T(&data)[N], index_constant<I> const /*index*/)
{
    static_assert(I < N, "Invalid index");
    return data[I];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, std::size_t N>
constexpr /*static*/ typename m1::vector_data_traits<T[N]>::const_reference m1::vector_data_traits<T[N]>::get(T const (&data)[N], std::size_t const index)
{
    assert(index < N);
    return data[index];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T, std::size_t N>
template <std::size_t I>
constexpr /*static*/ typename m1::vector_data_traits<T[N]>::const_reference m1::vector_data_traits<T[N]>::get(T const (&data)[N], index_constant<I> const /*index*/)
{
    static_assert(I < N, "Invalid index");
    return data[I];
}

// ====================================================================================================================

#endif // M1_VECTOR_TRAITS_HPP
