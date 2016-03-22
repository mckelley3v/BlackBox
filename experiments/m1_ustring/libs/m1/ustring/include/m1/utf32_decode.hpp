#ifndef M1_UTF32_DECODE_HPP
#define M1_UTF32_DECODE_HPP

#include "m1/byte_order.hpp"
#include <cassert>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    byte_order consume_utf32_byte_order_mark(InputItr &code_unit_itr,
                                             InputEnd code_unit_end) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    code_point utf32_decode_next(InputItr &code_unit_itr,
                                 InputEnd code_unit_end,
                                 code_point error_character = 0xFFFD) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename CodePointFunc>
    void utf32_decode_each(InputItr code_unit_itr,
                           InputEnd code_unit_end,
                           CodePointFunc code_point_func) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename CodePointFunc>
    void utf32_decode_each_n(InputItr code_unit_itr,
                             InputEnd code_unit_end,
                             std::size_t str_length,
                             CodePointFunc code_point_func) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename OutputItr>
    void utf32_decode_copy(InputItr code_unit_itr,
                           InputEnd code_unit_end,
                           OutputItr out_itr) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename OutputItr>
    void utf32_decode_copy_n(InputItr code_unit_itr,
                             InputEnd code_unit_end,
                             std::size_t str_length,
                             OutputItr out_itr) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
m1::byte_order m1::consume_utf32_byte_order_mark(InputItr &code_unit_itr,
                                                 InputEnd code_unit_end) noexcept
{
    if(code_unit_itr != code_unit_end)
    {
        char32_t const big_endian_mark = *reinterpret_cast<char32_t const*>("\x00\x00\xFE\xFF");
        char32_t const little_endian_mark = *reinterpret_cast<char32_t const*>("\xFF\xFE\x00\x00");

        char32_t const code_unit = *code_unit_itr;
        if(code_unit == big_endian_mark)
        {
            ++code_unit_itr;
            return byte_order::big_endian;
        }
        else if(code_unit == little_endian_mark)
        {
            ++code_unit_itr;
            return byte_order::little_endian;
        }
    }

    // no BOM, assume big endian
    return byte_order::big_endian;
}

// ================================================================================================================

template <typename InputItr,
          typename InputEnd>
m1::code_point m1::utf32_decode_next(InputItr &code_unit_itr,
                                     InputEnd code_unit_end,
                                     code_point const error_character /*= 0xFFFD*/) noexcept
{
    assert(code_unit_itr != code_unit_end);

    char32_t const code_unit = *code_unit_itr;
    ++code_unit_itr;

    if(code_unit < 0x110000)
    {
        code_point const c = static_cast<code_point>(code_unit);
        return c;
    }

    return error_character;
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename CodePointFunc>
void m1::utf32_decode_each(InputItr code_unit_itr,
                           InputEnd const code_unit_end,
                           CodePointFunc code_point_func) noexcept
{
    while(code_unit_itr != code_unit_end)
    {
        code_point const c = utf32_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        code_point_func(c);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename CodePointFunc>
void m1::utf32_decode_each_n(InputItr code_unit_itr,
                             InputEnd const code_unit_end,
                             std::size_t str_length,
                             CodePointFunc code_point_func) noexcept
{
    while((code_unit_itr != code_unit_end) && (str_length-- > 0))
    {
        code_point const c = utf32_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        code_point_func(c);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename OutputItr>
void m1::utf32_decode_copy(InputItr code_unit_itr,
                           InputEnd const code_unit_end,
                           OutputItr out_itr) noexcept
{
    while(code_unit_itr != code_unit_end)
    {
        code_point const c = utf32_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        *out_itr = c;
        ++out_itr;
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename OutputItr>
void m1::utf32_decode_copy_n(InputItr code_unit_itr,
                             InputEnd const code_unit_end,
                             std::size_t str_length,
                             OutputItr out_itr) noexcept
{
    while((code_unit_itr != code_unit_end) && (str_length-- > 0))
    {
        code_point const c = utf32_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        *out_itr = c;
        ++out_itr;
    }
}

// ====================================================================================================================

#endif // M1_UTF32_DECODE_HPP
