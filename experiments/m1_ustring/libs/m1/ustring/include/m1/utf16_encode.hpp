#ifndef M1_UTF16_ENCODE_HPP
#define M1_UTF16_ENCODE_HPP

#include <cstdint>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    // ================================================================================================================

    std::size_t utf16_encode_size(code_point ch);

    // ================================================================================================================

    template <typename OutputItr>
    void utf16_encode_next(OutputItr &&out,
                           code_point ch,
                           std::uint16_t error_unit = 0) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

template <typename OutputItr>
void m1::utf16_encode_next(OutputItr &&out,
                           code_point const ch,
                           std::uint16_t const error_unit /*= 0*/) noexcept
{
    if(ch < 0x10000) // 00000 zzzzzyyy yxxxxxxx
    {
        *out++ = static_cast<std::uint16_t>(ch);
    }
    else if(ch < 0x110000) // uuuuu zzzzzyyy yxxxxxxx
    {
        std::uint16_t const uuuu = 0b0000000000011111 & (ch >> 16);
        std::uint16_t const wwww = (uuuu - 1) << 6;
        std::uint16_t const hi_header = 0xD800;// 0xb1101100000000000;
        std::uint16_t const lo_header = 0xDC00; // 0xb1101110000000000;
        *out++ = static_cast<std::uint16_t>(hi_header | ((ch >> 10) & 0b0000000000111111) | wwww); // 110110wwwwzzzzzy (wwww = uuuuu-1)
        *out++ = static_cast<std::uint16_t>(lo_header | ((ch >>  0) & 0b0000001111111111));        // 110111yyyxxxxxxx
    }
    else
    {
        *out++ = error_unit;
    }
}

// ====================================================================================================================

#endif // M1_UTF16_ENCODE_HPP
