#include "m1/numeric/log2.hpp"
#include <cmath>
#include <cstdint>
#include <cassert>

// =====================================================================================================================

static std::uint32_t log2_impl(std::uint32_t x) noexcept;

// =====================================================================================================================

int m1::log2(int const x) noexcept
{
    static_assert(sizeof(x) == sizeof(std::uint32_t), "32-bit implementation");
    return static_cast<int>(log2_impl(static_cast<std::uint32_t>(x)));
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::log2(float const x) noexcept
{
    assert(x > 0.0f);
    return std::log2(x);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::log2(double const x) noexcept
{
    assert(x > 0.0);
    return std::log2(x);
}

// =====================================================================================================================

/*static*/ std::uint32_t log2_impl(std::uint32_t x) noexcept
{
    std::uint32_t result = 0;

    if(x & 0xFFFF0000)
    {
        x >>= 16;
        result |= 16;
    }

    if(x & 0x0000FF00)
    {
        x >>= 8;
        result |= 8;
    }

    if(x & 0x000000F0)
    {
        x >>= 4;
        result |= 4;
    }

    if(x & 0x0000000C)
    {
        x >>= 2;
        result |= 2;
    }

    if(x & 0x00000002)
    {
        x >>= 1;
        result |= 1;
    }

    return result;
}

// =====================================================================================================================
