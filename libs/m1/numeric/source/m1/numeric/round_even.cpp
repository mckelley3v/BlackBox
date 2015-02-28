#include "m1/numeric/round_even.hpp"
#include "m1/numeric/is_close.hpp"
#include "m1/numeric/ceil.hpp"
#include "m1/numeric/floor.hpp"
#include <limits>
#include <cassert>

// =====================================================================================================================

float m1::round_even(float const x)
{
    assert(static_cast<float>(std::numeric_limits<int>::min()) <= x);
    assert(x <= static_cast<float>(std::numeric_limits<int>::max()));

    if(is_close(ceil(x + 0.5f), floor(x + 0.5f)))
    {
        int const a = static_cast<int>(ceil(x));
        if(a % 2 == 0)
        {
            return ceil(x);
        }
        else
        {
            return floor(x);
        }
    }
    else
    {
        return floor(x + 0.5f);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::round_even(double const x)
{
    assert(static_cast<double>(std::numeric_limits<int>::min()) <= x);
    assert(x <= static_cast<double>(std::numeric_limits<int>::max()));

    if(is_close(ceil(x + 0.5), floor(x + 0.5)))
    {
        int const a = static_cast<int>(ceil(x));
        if(a % 2 == 0)
        {
            return ceil(x);
        }
        else
        {
            return floor(x);
        }
    }
    else
    {
        return floor(x + 0.5);
    }
}

// =====================================================================================================================
