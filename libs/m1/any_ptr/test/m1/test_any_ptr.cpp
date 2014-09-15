#include "m1/any_ptr.hpp"
#include <cassert>

bool test_any_ptr()
{
    m1::any_ptr p;
    assert(!p);
    int i = 0;
    p = &i;
    assert(m1::static_pointer_cast<float>(p) == nullptr);
    assert(m1::static_pointer_cast<int>(p) == &i);
    assert(m1::reinterpret_pointer_cast<int>(p) == &i);
    assert(m1::dynamic_pointer_cast<int>(p) == &i);
    return true;
}

bool test_const_any_ptr()
{
    m1::const_any_ptr p;
    assert(!p);
    int const i = 0;
    p = &i;
    assert(m1::static_pointer_cast<float>(p) == nullptr);
    assert(m1::static_pointer_cast<int>(p) == &i);
    assert(m1::reinterpret_pointer_cast<int>(p) == &i);
    assert(m1::dynamic_pointer_cast<int>(p) == &i);

    int j = 1;
    m1::any_ptr q = &j;
    m1::const_any_ptr cq1 = &j;
    m1::const_any_ptr cq2 = q;

    assert(m1::static_pointer_cast<int>(cq1) == &j);
    assert(m1::static_pointer_cast<int>(cq2) == &j);
    return true;
}
