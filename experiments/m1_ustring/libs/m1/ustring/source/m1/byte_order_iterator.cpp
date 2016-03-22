#include "m1/byte_order_iterator.hpp"

template m1::swap_byte_order_iterator<char16_t*>;
template m1::swap_byte_order_iterator<char16_t const*>;
template m1::swap_byte_order_iterator<char32_t*>;
template m1::swap_byte_order_iterator<char32_t const*>;
template m1::swap_byte_order_iterator<std::uint16_t*>;
template m1::swap_byte_order_iterator<std::uint16_t const*>;
template m1::swap_byte_order_iterator<std::uint32_t*>;
template m1::swap_byte_order_iterator<std::uint32_t const*>;
