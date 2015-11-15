#ifndef M1_VECTOR_IMPL_HPP
#define M1_VECTOR_IMPL_HPP

#include <utility>
#include <type_traits>
#include <cstddef>

// ====================================================================================================================

#define M1_LAMBDA_FORWARD(F) ([] (auto &&...args) { return F(std::forward<decltype(args)>(args)...);})

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

    template <typename F,
              std::size_t... Indices>
    constexpr auto apply_each_vector_index(F &&f, index_sequence<Indices...> const /*indices*/) noexcept
    {
        return f(index_constant<Indices>()...);
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename... Ts,
              typename F>
    constexpr auto apply_each_vector_index(F &&f) noexcept
    {
        return apply_each_vector_index(std::forward<F>(f), make_index_sequence<vector_data_size<Ts...>::value>());
    }

    // ================================================================================================================

    template <typename F,
              typename V,
              std::size_t... Indices>
    constexpr auto accumulate_vector_values(F &&f, V &&v, index_sequence<Indices...> const /*indices*/) noexcept
    {
        return f(v[(index_constant<Indices>())]...);
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename F,
              typename V>
    constexpr auto accumulate_vector_values(F &&f, V &&v) noexcept
    {
        using vector_type = std::decay_t<V>;
        return accumulate_vector_values(std::forward<F>(f), std::forward<V>(v), make_index_sequence<vector_type::static_size>());
    }

    // ================================================================================================================

    // generic construction from function of index_constant
    template <typename V,
              typename F,
              std::size_t... Indices>
    constexpr auto generate_vector(F &&f, index_sequence<Indices...> const /*indices*/) noexcept
    {
        return V { f(index_constant<Indices>())... };
    }

    // ================================================================================================================

    // helper function for generic component wise construction
    template <typename... Ts,
              typename F>
    constexpr auto generate_vector_copy(F &&f) noexcept
    {
        return generate_vector<vector_copy_type<Ts...>>(std::forward<F>(f), make_index_sequence<vector_data_size<Ts...>::value>());
    }

    // ================================================================================================================

    // helper function for generic component wise construction
    template <typename... Ts,
              typename F>
    constexpr auto generate_vector_bool(F &&f) noexcept
    {
        return generate_vector<vector_bool_type<Ts...>>(std::forward<F>(f), make_index_sequence<vector_data_size<Ts...>::value>());
    }

    // ================================================================================================================

    // By Sean Parent
    // https://isocpp.org/blog/2015/01/for-each-argument-sean-parent
    template <typename F,
              typename... Args>
    void for_each_arg(F &&f, Args &&...args)
    {
        [](...) {}((f(std::forward<Args>(args)), 0)...);
    }

    // ================================================================================================================

    // generic construction from function of index_constant
    template <typename F,
              std::size_t... Indices>
    void for_each_index(F &&f, index_sequence<Indices...> const /*indices*/)
    {
        for_each_arg(f, index_constant<Indices>()...);
    }

    // ================================================================================================================

    // helper function for generic component wise construction
    template <typename... Ts,
              typename F>
    void for_each_vector_index(F &&f)
    {
        return for_each_index(f, make_index_sequence<vector_data_size<Ts...>::value>());
    }

    // ================================================================================================================
} // namespace impl
} // namespace m1

#endif // M1_VECTOR_IMPL_HPP
