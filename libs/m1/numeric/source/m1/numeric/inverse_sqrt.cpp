#include "m1/numeric/inverse_sqrt.hpp"
#include <limits>
#include <cassert>

// references:
// http://www.beyond3d.com/content/articles/8/
// http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf

// =====================================================================================================================

float m1::inverse_sqrt(float const x) noexcept
{
    assert(static_cast<float>(std::numeric_limits<int>::min()) <= x);
    assert(x <= static_cast<float>(std::numeric_limits<int>::max()));

    int const i = reinterpret_cast<int const&>(x);
    int const j = 0x5f375a86 - (i >> 1);
    float const hx = 0.5f * x;
    float const y0 = reinterpret_cast<float const&>(j);
    float const y1 = y0 * (1.5f - hx * y0 * y0);
    float const y2 = y1 * (1.5f - hx * y1 * y1);
    return y2;
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::inverse_sqrt(double const x) noexcept
{
    assert(static_cast<double>(std::numeric_limits<long long>::min()) <= x);
    assert(x <= static_cast<double>(std::numeric_limits<long long>::max()));

    long long const i = reinterpret_cast<long long const&>(x);
    long long const j = 0x5fe6ec85e7de30da - (i >> 1l);
    double const hx = 0.5 * x;
    double const y0 = reinterpret_cast<double const&>(j);
    double const y1 = y0 * (1.5 - hx * y0 * y0);
    double const y2 = y1 * (1.5 - hx * y1 * y1);
    return y2;
}

// =====================================================================================================================
