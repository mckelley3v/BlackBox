#include "m1/numeric/is_pow2.hpp"

// http://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
// =====================================================================================================================

bool m1::is_pow2(int const value)
{
    return value && !(value & (value - 1));
}

// =====================================================================================================================
