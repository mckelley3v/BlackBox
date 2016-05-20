#include "m1/intrusive_list.hpp"
#include "catch.hpp"

struct X
    : m1::intrusive_list_node
{
    int value = 0;
};

TEST_CASE("Test m1::intrusive_list", "[m1]")
{
    static_assert(m1::is_forward_iterator<m1::intrusive_list<X>::iterator, X>::value, "expected is_forward_iterator");

    m1::intrusive_list<X> l;
    CHECK(l.empty());
}
