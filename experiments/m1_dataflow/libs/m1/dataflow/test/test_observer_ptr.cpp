#include "m1/observer_ptr.hpp"
#include "catch.hpp"

template class m1::observer_ptr<int>;

TEST_CASE("Test m1::observer_ptr", "[m1]")
{
    m1::observer_ptr<int> p;
    m1::observer_ptr<int> q;

    CHECK(p == nullptr);
    CHECK(nullptr == q);
    CHECK(p == q);
    CHECK(!(p != nullptr));
    CHECK(!(nullptr != q));
    CHECK(!(p != q));
    CHECK(p <= q);
    CHECK(!(p < q));
    CHECK(p >= q);
    CHECK(!(p > q));

    swap(p, q);

    int x = 0;
    p = m1::make_observer(&x);
    CHECK(p.get() == &x);
    CHECK(hash(p) != 0);

    swap(p, q);
    CHECK(q.get() == &x);
}
