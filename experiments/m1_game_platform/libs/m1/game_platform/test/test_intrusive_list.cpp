#include "m1/intrusive_list.hpp"
#include "catch.hpp"

template <typename T>
struct list_node
    : m1::intrusive_list_node
{
    list_node() = default;
    list_node(T &&val)
        : value(std::move(val))
    {
    }

    list_node(T const &val)
        : value(val)
    {
    }

    T value = 0;
};

template <typename T>
bool operator == (list_node<T> const &lhs, list_node<T> const &rhs)
{
    return lhs.value == rhs.value;
}

template <typename T>
bool operator < (list_node<T> const &lhs, list_node<T> const &rhs)
{
    return lhs.value < rhs.value;
}

typedef list_node<int> X;
template class m1::intrusive_list<X>;
template class m1::intrusive_list_iterator<X>;
template class m1::intrusive_list_const_iterator<X>;

TEST_CASE("Test m1::intrusive_list", "[m1]")
{
    static_assert(m1::impl::is_input_iterator<m1::intrusive_list<X>::iterator, X>::value, "expected is_input_iterator");

    X x0{0};
    X x1{1};
    X x2{2};
    X x3{3};
    X x4{4};

    m1::intrusive_list<X> l;
    CHECK(l.empty());

    l.push_back(x0);
    CHECK(!l.empty());
    CHECK(std::distance(l.begin(), l.end()) == 1);

    l.push_back(x1);
    CHECK(std::distance(l.begin(), l.end()) == 2);

    l.push_back(x2);
    CHECK(std::distance(l.begin(), l.end()) == 2);

    l.push_back(x3);
    CHECK(std::distance(l.begin(), l.end()) == 4);

    l.push_back(x4);
    CHECK(std::distance(l.begin(), l.end()) == 5);



    m1::intrusive_list<X> m;
    swap(l, m);
}
