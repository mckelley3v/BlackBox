#include "m1/numeric/mod.hpp"
#include <cassert>

bool test_mod()
{
    using m1::mod;

    assert(mod(-9, 5) == 1);
    assert(mod(-8, 5) == 2);
    assert(mod(-7, 5) == 3);
    assert(mod(-6, 5) == 4);
    assert(mod(-5, 5) == 0);
    assert(mod(-4, 5) == 1);
    assert(mod(-3, 5) == 2);
    assert(mod(-2, 5) == 3);
    assert(mod(-1, 5) == 4);
    assert(mod( 0, 5) == 0);
    assert(mod( 1, 5) == 1);
    assert(mod( 2, 5) == 2);
    assert(mod( 3, 5) == 3);
    assert(mod( 4, 5) == 4);
    assert(mod( 5, 5) == 0);
    assert(mod( 6, 5) == 1);
    assert(mod( 7, 5) == 2);
    assert(mod( 8, 5) == 3);
    assert(mod( 9, 5) == 4);

    return true;
}
