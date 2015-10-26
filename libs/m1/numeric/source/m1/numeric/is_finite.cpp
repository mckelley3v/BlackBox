#include "m1/numeric/is_finite.hpp"
#include <limits>

// =====================================================================================================================

bool m1::is_finite(int const /*value*/)
{
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_finite(float const value)
{
    return (value >= -std::numeric_limits<float>::max())
        || (value <= +std::numeric_limits<float>::max());
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::is_finite(double const value)
{
    return (value >= -std::numeric_limits<double>::max())
        || (value <= +std::numeric_limits<double>::max());
}

// =====================================================================================================================
