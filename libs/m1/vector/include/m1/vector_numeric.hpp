#ifndef M1_VECTOR_NUMERIC_HPP
#define M1_VECTOR_NUMERIC_HPP

#include "m1/vector_type.hpp"

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    // logical functions:
    // template <typename T> constexpr bool all_of(vector<T> const &v) noexcept;
    // template <typename T> constexpr bool any_of(vector<T> const &v) noexcept;
    // template <typename T> constexpr bool none_of(vector<T> const &v) noexcept;
    // template <typename L, typename R> constexpr vector_bool_type<T> is_close(vector<L> const &lhs, vector<R> const &rhs);
    // template <typename L, typename R, typename T> constexpr vector_bool_type<T> is_close(vector<L> const &lhs,
    //                                                                                      vector<R> const &rhs,
    //                                                                                      T const &relative_tolerance,
    //                                                                                      T const &absolute_tolerance);
    // is_finite
    // is_inf
    // is_nan
    // is_pow2
    // is_small

    // componentwise functions:
    // abs
    // acos
    // asin
    // atan
    // ceil
    // clamp
    // cos
    // cosh
    // degrees
    // exp
    // exp10
    // exp2
    // floor
    // fract
    // frexp
    // inverse_lerp
    // inverse_sqrt
    // ldexp
    // lerp
    // linear_step
    // log
    // log10
    // log2
    // max
    // min
    // mirror
    // mix
    // mod
    // modf
    // pow
    // radians
    // repeat
    // round
    // round_even
    // saturate
    // sign
    // sin
    // sinh
    // smooth_step
    // sqrt
    // step
    // tan
    // tanh
    // trunc
    // multiply
    // divide

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_VECTOR_NUMERIC_HPP
