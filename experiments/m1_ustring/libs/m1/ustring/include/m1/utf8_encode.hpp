#ifndef M1_UTF8_ENCODE_HPP
#define M1_UTF8_ENCODE_HPP

#include <cstdint>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    // ================================================================================================================

    std::size_t utf8_encode_size(code_point ch);

    // ================================================================================================================

    template <typename OutputItr>
    void utf8_encode_next(OutputItr &&out,
                          code_point ch,
                          std::uint8_t error_unit = 0) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

template <typename OutputItr>
void m1::utf8_encode_next(OutputItr &&out,
                          code_point const ch,
                          std::uint8_t const error_unit /*= 0*/) noexcept
{
    if(ch < 0x80) // 00000 00000000 0xxxxxxx
    {
        *out++ = static_cast<std::uint8_t>(ch);
    }
    else if(ch < 0x800) // 00000 00000yyy yxxxxxxx
    {
        *out++ = static_cast<std::uint8_t>(0xb11000000 | ((ch >> 6) & 0b00011111)); // 110yyyyx
        *out++ = static_cast<std::uint8_t>(0xb10000000 | ((ch >> 0) & 0b00111111)); // 10xxxxxx
    }
    else if(ch < 0x10000) // 00000 zzzzzyyy yxxxxxxx
    {
        *out++ = static_cast<std::uint8_t>(0xb11100000 | ((ch >> 12) & 0b00001111)); // 1110zzzz
        *out++ = static_cast<std::uint8_t>(0xb10000000 | ((ch >>  6) & 0b00111111)); // 10zyyyyx
        *out++ = static_cast<std::uint8_t>(0xb10000000 | ((ch >>  0) & 0b00111111)); // 10xxxxxx
    }
    else if(ch < 0x110000) // uuuuu zzzzzyyy yxxxxxxx
    {
        *out++ = static_cast<std::uint8_t>(0xb11110000 | ((ch >> 18) & 0b00000111)); // 11110uuu
        *out++ = static_cast<std::uint8_t>(0xb10000000 | ((ch >> 12) & 0b00111111)); // 10uuzzzz
        *out++ = static_cast<std::uint8_t>(0xb10000000 | ((ch >>  6) & 0b00111111)); // 10zyyyyx
        *out++ = static_cast<std::uint8_t>(0xb10000000 | ((ch >>  0) & 0b00111111)); // 10xxxxxx
    }
    else
    {
        *out++ = error_unit;
    }
}

// ====================================================================================================================

#endif // M1_UTF8_ENCODE_HPP
