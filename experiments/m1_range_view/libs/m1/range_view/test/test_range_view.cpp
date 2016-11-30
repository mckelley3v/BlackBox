#include "m1/range_view.hpp"
#include "catch.hpp"
#include <vector>

// ====================================================================================================================

template class m1::forward_range_view<std::vector<char>::const_iterator>;
template class m1::forward_range_view<std::vector<signed char>::const_iterator>;
template class m1::forward_range_view<std::vector<unsigned char>::const_iterator>;
template class m1::forward_range_view<std::vector<short>::const_iterator>;
template class m1::forward_range_view<std::vector<unsigned short>::const_iterator>;
template class m1::forward_range_view<std::vector<int>::const_iterator>;
template class m1::forward_range_view<std::vector<unsigned int>::const_iterator>;
template class m1::forward_range_view<std::vector<long>::const_iterator>;
template class m1::forward_range_view<std::vector<unsigned long>::const_iterator>;
template class m1::forward_range_view<std::vector<long long>::const_iterator>;
template class m1::forward_range_view<std::vector<unsigned long long>::const_iterator>;
template class m1::forward_range_view<std::vector<float>::const_iterator>;
template class m1::forward_range_view<std::vector<double>::const_iterator>;
template class m1::forward_range_view<std::vector<long double>::const_iterator>;

template class m1::bidirectional_range_view<std::vector<char>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<signed char>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<unsigned char>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<short>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<unsigned short>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<int>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<unsigned int>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<long>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<unsigned long>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<long long>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<unsigned long long>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<float>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<double>::const_iterator>;
template class m1::bidirectional_range_view<std::vector<long double>::const_iterator>;

template class m1::random_access_range_view<std::vector<char>::const_iterator>;
template class m1::random_access_range_view<std::vector<signed char>::const_iterator>;
template class m1::random_access_range_view<std::vector<unsigned char>::const_iterator>;
template class m1::random_access_range_view<std::vector<short>::const_iterator>;
template class m1::random_access_range_view<std::vector<unsigned short>::const_iterator>;
template class m1::random_access_range_view<std::vector<int>::const_iterator>;
template class m1::random_access_range_view<std::vector<unsigned int>::const_iterator>;
template class m1::random_access_range_view<std::vector<long>::const_iterator>;
template class m1::random_access_range_view<std::vector<unsigned long>::const_iterator>;
template class m1::random_access_range_view<std::vector<long long>::const_iterator>;
template class m1::random_access_range_view<std::vector<unsigned long long>::const_iterator>;
template class m1::random_access_range_view<std::vector<float>::const_iterator>;
template class m1::random_access_range_view<std::vector<double>::const_iterator>;
template class m1::random_access_range_view<std::vector<long double>::const_iterator>;

// ====================================================================================================================

namespace m1
{
    template <typename T>
    using vector_view = random_access_range_view<typename std::vector<T>::const_iterator>;
}

// ====================================================================================================================

TEST_CASE("Test m1::range_view", "[m1]")
{
    static_assert(m1::is_const_iterator<int const*>::value, "m1::is_const_iterator");
    static_assert(m1::is_const_iterator<std::vector<int>::const_iterator>::value, "m1::is_const_iterator");

    std::vector<int> const v {1, 2, 3};

    m1::vector_view<int> const cv0 = m1::make_range_view(v);
    CHECK(!cv0.empty());
    CHECK(cv0.size() == v.size());
    CHECK(cv0[0] == 1);
    CHECK(cv0.at(1) == 2);

    m1::vector_view<int> const cv1 = m1::make_range_view(v.cbegin(),
                                                         v.cend());
    CHECK(cv0 == cv1);

    m1::array_view<int> const cv2 = m1::make_array_view(v.data(), v.size());
}

// ====================================================================================================================
