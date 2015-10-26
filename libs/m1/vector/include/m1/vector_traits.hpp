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

    // ================================================================================================================

    template <std::size_t I>
    using index_constant = std::integral_constant<std::size_t, I>;

    template <typename T>
    struct vector_data_traits;

    // ================================================================================================================

    template <typename T>
    struct vector_data_traits<T const>
    {
        typedef T copy_type;
        typedef typename vector_data_traits<T>::value_type value_type;
        typedef typename vector_data_traits<T>::const_reference reference;
        typedef typename vector_data_traits<T>::const_reference const_reference;

        constexpr static std::size_t const static_size = vector_data_traits<T>::static_size;

        static reference ref(T const &data, std::size_t index);
        template <std::size_t I> static reference ref(T const &data, index_constant<I> index);

        constexpr static const_reference get(T const &data, std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const &data, index_constant<I> index);
    };

    // ================================================================================================================

    template <typename T>
    struct vector_data_traits<T&>
    {
        typedef T copy_type;
        typedef typename vector_data_traits<T>::reference value_type;
        typedef typename vector_data_traits<T>::reference reference;
        typedef typename vector_data_traits<T>::const_reference const_reference;

        constexpr static std::size_t const static_size = vector_data_traits<T>::static_size;

        static reference ref(T &data, std::size_t index);
        template <std::size_t I> static reference ref(T &data, index_constant<I> index);

        constexpr static const_reference get(T const &data, std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const &data, index_constant<I> index);
    };

    // ================================================================================================================

    template <typename T>
    struct vector_data_traits<T const&>
    {
        typedef T copy_type;
        typedef typename vector_data_traits<T>::const_reference value_type;
        typedef typename vector_data_traits<T>::const_reference reference;
        typedef typename vector_data_traits<T>::const_reference const_reference;

        constexpr static std::size_t const static_size = vector_data_traits<T>::static_size;

        static reference ref(T const &data, std::size_t index);
        template <std::size_t I> static reference ref(T const &data, index_constant<I> index);

        constexpr static const_reference get(T const &data, std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const &data, index_constant<I> index);
    };

    // ================================================================================================================

    template <typename T, std::size_t N>
    struct vector_data_traits<T[N]>
    {
        typedef T copy_type[N];
        typedef T value_type;
        typedef T& reference;
        typedef T const& const_reference;

        constexpr static std::size_t const static_size = N;

        static reference ref(T(&data)[N], std::size_t index);
        template <std::size_t I> static reference ref(T(&data)[N], index_constant<I> index);

        constexpr static const_reference get(T const (&data)[N], std::size_t index);
        template <std::size_t I> constexpr static const_reference get(T const (&data)[N], index_constant<I> index);
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    using std::index_sequence;
    using std::make_index_sequence;

    // ================================================================================================================

    template <typename... Ts>
    struct vector_data_copy_type;

    template <typename... Ts>
    using vector_data_copy_type_t = typename vector_data_copy_type<Ts...>::type;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    struct vector_data_copy_type<T>
    {
        typedef typename vector_data_traits<T>::copy_type type;
    };

    template <typename T1, typename T2>
    struct vector_data_copy_type<T1, T2>
    {
        static_assert(std::is_same<vector_data_copy_type_t<T1>, vector_data_copy_type_t<T2>>::value, "Mismatched data types");
        typedef typename vector_data_traits<T1>::copy_type type;
    };

    template <typename T1, typename T2, typename... Ts>
    struct vector_data_copy_type<T1, T2, Ts...>
    {
        typedef vector_data_copy_type_t<vector_data_copy_type_t<T1, T2>, Ts...> type;
    };

    // ================================================================================================================

    template <typename... Ts>
    struct vector_data_size;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    struct vector_data_size<T>
    {
        constexpr static std::size_t const value = vector_data_traits<T>::static_size;
    };

    template <typename T, typename... Ts>
    struct vector_data_size<T, Ts...>
    {
        constexpr static std::size_t const value = vector_data_traits<T>::static_size;
        static_assert(value == vector_data_size<Ts...>::value, "Mismatched size");
    };

    // ================================================================================================================

    template <typename... Ts>
    using vector_value_type = std::common_type_t<typename vector_data_traits<Ts>::value_type...>;

    // ================================================================================================================

    // to abstract reference/const vectors
    template <typename... Ts>
    using vector_copy_type = vector<vector_data_copy_type_t<Ts...>>;

    // ================================================================================================================

    // for boolean expressions:
    template <typename... Ts>
    using vector_bool_type = vector<bool[vector_data_size<Ts...>::value]>;

    // ================================================================================================================

    // generic construction from function of index_constant
    template <typename R,
              std::size_t... Indices,
              typename F>
    constexpr R generate_value(index_sequence<Indices...> const /*indices*/, F const &f) noexcept
    {
        return R { f(index_constant<Indices>())... };
    }

    // ================================================================================================================

    // helper function for generic component wise construction
    template <typename... Ts,
              typename F>
    constexpr vector_copy_type<Ts...> generate_vector_copy(F const &f) noexcept
    {
        return generate_value<vector_copy_type<Ts...>>(make_index_sequence<vector_data_size<Ts...>::value>(), f);
    }

    // ================================================================================================================

    // helper function for generic component wise construction
    template <typename... Ts,
              typename F>
    constexpr vector_bool_type<Ts...> generate_vector_bool(F const &f) noexcept
    {
        return generate_value<vector_bool_type<Ts...>>(make_index_sequence<vector_data_size<Ts...>::value>(), f);
    }

    // ================================================================================================================

    // By Sean Parent
    // https://isocpp.org/blog/2015/01/for-each-argument-sean-parent
    template <typename F,
              typename... Args>
    void for_each_arg(F const &f, Args &&...args)
    {
        [](...) {}((f(std::forward<Args>(args)), 0)...);
    }

    // ================================================================================================================

    // generic construction from function of index_constant
    template <std::size_t... Indices,
              typename F>
    void for_each_index(index_sequence<Indices...> const /*indices*/, F const &f)
    {
        for_each_arg(f, index_constant<Indices>()...);
    }

    // ================================================================================================================

    // helper function for generic component wise construction
    template <std::size_t N,
              typename F>
    void for_each_index(F const &f)
    {
        return for_each_index(make_index_sequence<N>(), f);
    }

    // ================================================================================================================
} // namespace impl
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
