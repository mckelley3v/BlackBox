#include "m1/numeric/pow.hpp"
#include "m1/numeric/floor.hpp"
#include "m1/numeric/is_small.hpp"
#include <cmath>
#include <cassert>

// =====================================================================================================================

float m1::pow(float const base, int const exp)
{
    // more restrictive than std::pow
    // but asserts on implementation defined behavior
    // TODO - consider allowing negative base if exp is odd
    assert(base >= 0.0f);
    assert(!is_small(base) || (exp > 0));
    return std::pow(base, exp);
}

// ---------------------------------------------------------------------------------------------------------------------

float m1::pow(float const base, float const exp)
{
    // more restrictive than std::pow
    // but asserts on implementation defined behavior
    assert(base >= 0.0f);
    assert(!is_small(base) || (exp > 0.0f));
    return std::pow(base, exp);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::pow(const double base, int const exp)
{
    // TODO - consider allowing negative base if exp is odd
    assert(base >= 0.0);
    assert(!is_small(base) || (exp > 0));
    return std::pow(base, exp);
}

// ---------------------------------------------------------------------------------------------------------------------

double m1::pow(const double base, const double exp)
{
    // more restrictive than std::pow
    // but asserts on implementation defined behavior
    assert(base >= 0.0);
    assert(!is_small(base) || (exp > 0.0));
    return std::pow(base, exp);
}

// =====================================================================================================================
