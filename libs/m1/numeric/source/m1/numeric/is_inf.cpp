#include "m1/numeric/is_inf.hpp"
#include <limits>

// =====================================================================================================================

bool is_inf(int const /*value*/)
{
    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool is_inf(float const value)
{
    return (value < -std::numeric_limits<float>::max())
        || (value > +std::numeric_limits<float>::max());
}

// ---------------------------------------------------------------------------------------------------------------------

bool is_inf(double const value)
{
    return (value < -std::numeric_limits<double>::max())
        || (value > +std::numeric_limits<double>::max());
}

// =====================================================================================================================
