#ifndef M1_NUMERIC_IS_POW2_HPP
#define M1_NUMERIC_IS_POW2_HPP

namespace m1
{
    // =================================================================================================================

    constexpr bool is_pow2(int value) noexcept;

    // =================================================================================================================
} // namespace m1

// http://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
// =====================================================================================================================

constexpr bool m1::is_pow2(int const value) noexcept
{
    return value && !(value & (value - 1));
}

// =====================================================================================================================

#endif // M1_NUMERIC_IS_POW2_HPP
