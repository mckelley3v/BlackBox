#ifndef M1_NUMERIC_CLAMP_HPP
#define M1_NUMERIC_CLAMP_HPP

#include <cassert>

namespace m1
{
    // =================================================================================================================

    constexpr int clamp(int value,
                        int min_value,
                        int max_value) noexcept;

    constexpr float clamp(float value,
                          float min_value,
                          float max_value) noexcept;

    constexpr double clamp(double value,
                           double min_value,
                           double max_value) noexcept;

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

constexpr int m1::clamp(int const value,
                        int const min_value,
                        int const max_value) noexcept
{
    return assert(min_value <= max_value),
           (value < min_value) ? min_value :
           (value > max_value) ? max_value : value;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr float m1::clamp(float const value,
                          float const min_value,
                          float const max_value) noexcept
{
    return assert(min_value <= max_value),
           (value < min_value) ? min_value :
           (value > max_value) ? max_value : value;
}

// ---------------------------------------------------------------------------------------------------------------------

constexpr double m1::clamp(double const value,
                           double const min_value,
                           double const max_value) noexcept
{
    return assert(min_value <= max_value),
           (value < min_value) ? min_value :
           (value > max_value) ? max_value : value;
}

// =====================================================================================================================

#endif // M1_NUMERIC_CLAMP_HPP
