#include "m1/range_view.hpp"
#include "catch.hpp"
#include <vector>

// ====================================================================================================================

template class m1::range_view<std::vector<char>::const_iterator>;
template class m1::range_view<std::vector<signed char>::const_iterator>;
template class m1::range_view<std::vector<unsigned char>::const_iterator>;
template class m1::range_view<std::vector<short>::const_iterator>;
template class m1::range_view<std::vector<unsigned short>::const_iterator>;
template class m1::range_view<std::vector<int>::const_iterator>;
template class m1::range_view<std::vector<unsigned int>::const_iterator>;
template class m1::range_view<std::vector<long>::const_iterator>;
template class m1::range_view<std::vector<unsigned long>::const_iterator>;
template class m1::range_view<std::vector<long long>::const_iterator>;
template class m1::range_view<std::vector<unsigned long long>::const_iterator>;
template class m1::range_view<std::vector<float>::const_iterator>;
template class m1::range_view<std::vector<double>::const_iterator>;
template class m1::range_view<std::vector<long double>::const_iterator>;

// ====================================================================================================================

TEST_CASE("Test m1::range_view", "[m1]")
{
    static_assert(m1::is_const_iterator<int const*>::value, "m1::is_const_iterator");
    static_assert(m1::is_const_iterator<std::vector<int>::const_iterator>::value, "m1::is_const_iterator");
}
