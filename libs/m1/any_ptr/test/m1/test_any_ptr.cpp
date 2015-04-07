#include "m1/any_ptr.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::any_ptr", "[m1][m1::any_ptr]")
{
    m1::any_ptr p;
    CHECK(!p);
    int i = 0;
    p = &i;
    CHECK(m1::static_pointer_cast<float>(p) == nullptr);
    CHECK(m1::static_pointer_cast<int>(p) == &i);
    CHECK(m1::reinterpret_pointer_cast<int>(p) == &i);
    CHECK(m1::dynamic_pointer_cast<int>(p) == &i);

    // verify incomplete types work
    struct T;
    T *t = nullptr;
    p = t;
}

TEST_CASE("Test m1::const_any_ptr", "[m1][m1::any_ptr]")
{
    m1::const_any_ptr p;
    CHECK(!p);
    int const i = 0;
    p = &i;
    CHECK(m1::static_pointer_cast<float>(p) == nullptr);
    CHECK(m1::static_pointer_cast<int>(p) == &i);
    CHECK(m1::reinterpret_pointer_cast<int>(p) == &i);
    CHECK(m1::dynamic_pointer_cast<int>(p) == &i);

    int j = 1;
    m1::any_ptr q = &j;
    m1::const_any_ptr cq1 = &j;
    m1::const_any_ptr cq2 = q;

    CHECK(m1::static_pointer_cast<int>(cq1) == &j);
    CHECK(m1::static_pointer_cast<int>(cq2) == &j);

    // verify incomplete types work
    struct T;
    T *t = nullptr;
    p = t;
}
