#ifndef M1_NUMERIC_SIGN_HPP
#define M1_NUMERIC_SIGN_HPP

namespace m1
{
    // =================================================================================================================

    constexpr int sign(int x) noexcept;
    constexpr float sign(float x) noexcept;
    constexpr double sign(double x) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr int m1::sign(int const x) noexcept
{
    return (x == 0) ?  0 :
           (x < 0)  ? -1 : +1;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr float m1::sign(float const x) noexcept
{
    return (x == 0.0f) ?  0.0f :
           (x < 0.0f)  ? -1.0f : +1.0f;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::sign(double const x) noexcept
{
    return (x == 0.0) ?  0.0 :
           (x < 0.0)  ? -1.0 : +1.0;
}

// =====================================================================================================================

#endif // M1_NUMERIC_SIGN_HPP
