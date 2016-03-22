#ifndef M1_UTF16_DECODE_HPP
#define M1_UTF16_DECODE_HPP

#include "m1/byte_order.hpp"
#include <cassert>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    byte_order consume_utf16_byte_order_mark(InputItr &code_unit_itr,
                                             InputEnd code_unit_end) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    code_point utf16_decode_next(InputItr &code_unit_itr,
                                 InputEnd code_unit_end,
                                 code_point error_character = 0xFFFD) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename CodePointFunc>
    void utf16_decode_each(InputItr code_unit_itr,
                           InputEnd code_unit_end,
                           CodePointFunc code_point_func) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename CodePointFunc>
    void utf16_decode_each_n(InputItr code_unit_itr,
                             InputEnd code_unit_end,
                             std::size_t str_length,
                             CodePointFunc code_point_func) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename OutputItr>
    void utf16_decode_copy(InputItr code_unit_itr,
                           InputEnd code_unit_end,
                           OutputItr out_itr) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename OutputItr>
    void utf16_decode_copy_n(InputItr code_unit_itr,
                             InputEnd code_unit_end,
                             std::size_t str_length,
                             OutputItr out_itr) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    constexpr bool utf16_surrogate_head(char16_t value) noexcept;
    constexpr bool utf16_surrogate_tail(char16_t value) noexcept;

    // ================================================================================================================

    constexpr code_point utf16_code_point(char16_t code_unit0) noexcept;

    constexpr code_point utf16_code_point(char16_t code_unit0,
                                          char16_t code_unit1) noexcept;

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
m1::byte_order m1::consume_utf16_byte_order_mark(InputItr &code_unit_itr,
                                                 InputEnd code_unit_end) noexcept
{
    if(code_unit_itr != code_unit_end)
    {
        char16_t const big_endian_mark = *reinterpret_cast<char16_t const*>("\xFE\xFF");
        char16_t const little_endian_mark = *reinterpret_cast<char16_t const*>("\xFF\xFE");

        char16_t const code_unit = *code_unit_itr;
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
m1::code_point m1::utf16_decode_next(InputItr &code_unit_itr,
                                     InputEnd code_unit_end,
                                     code_point const error_character /*= 0xFFFD*/) noexcept
{
    assert(code_unit_itr != code_unit_end);

    char16_t const code_unit0 = *code_unit_itr;
    ++code_unit_itr;

    if(impl::utf16_surrogate_head(code_unit0))
    {
        // protect against input overrun
        if(code_unit_itr != code_unit_end)
        {
            char16_t const code_unit1 = *code_unit_itr;
            ++code_unit_itr;

            if(impl::utf16_surrogate_tail(code_unit1))
            {
                code_point const c = impl::utf16_code_point(code_unit0, code_unit1);
                return c;
            }
        }
    }
    else if(!impl::utf16_surrogate_tail(code_unit0))
    {
        code_point const c = impl::utf16_code_point(code_unit0);
        return c;
    }

    // error
    return error_character;
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename CodePointFunc>
void m1::utf16_decode_each(InputItr code_unit_itr,
                           InputEnd const code_unit_end,
                           CodePointFunc code_point_func) noexcept
{
    while(code_unit_itr != code_unit_end)
    {
        code_point const c = utf16_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        code_point_func(c);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename CodePointFunc>
void m1::utf16_decode_each_n(InputItr code_unit_itr,
                             InputEnd const code_unit_end,
                             std::size_t str_length,
                             CodePointFunc code_point_func) noexcept
{
    while((code_unit_itr != code_unit_end) && (str_length-- > 0))
    {
        code_point const c = utf16_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        code_point_func(c);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename OutputItr>
void m1::utf16_decode_copy(InputItr code_unit_itr,
                           InputEnd const code_unit_end,
                           OutputItr out_itr) noexcept
{
    while(code_unit_itr != code_unit_end)
    {
        code_point const c = utf16_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        *out_itr = c;
        ++out_itr;
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename OutputItr>
void m1::utf16_decode_copy_n(InputItr code_unit_itr,
                             InputEnd const code_unit_end,
                             std::size_t str_length,
                             OutputItr out_itr) noexcept
{
    while((code_unit_itr != code_unit_end) && (str_length-- > 0))
    {
        code_point const c = utf16_decode_next(/*ref*/ code_unit_itr,
                                               code_unit_end);
        *out_itr = c;
        ++out_itr;
    }
}

// ====================================================================================================================

constexpr bool m1::impl::utf16_surrogate_head(char16_t value) noexcept
{
    // match pattern:  110110xxxxxxxxxx:
    // constexpr char16_t const value_bits    = 0b0000001111111111;
    // constexpr char16_t const required_bits = 0b1101100000000000;
    // return (value & ~value_bits) == required_bits;

    return (value & 0b1111110000000000) == 0b1101100000000000;
}

// ====================================================================================================================

constexpr bool m1::impl::utf16_surrogate_tail(char16_t value) noexcept
{
    // match pattern:  110111xxxxxxxxxx:
    // constexpr char16_t const value_bits    = 0b0000001111111111;
    // constexpr char16_t const required_bits = 0b1101110000000000;
    // return (value & ~value_bits) == required_bits;

    return (value & 0b1111110000000000) == 0b1101110000000000;
}

// ====================================================================================================================

constexpr m1::code_point m1::impl::utf16_code_point(char16_t const code_unit0) noexcept
{
    // trivial
    return static_cast<code_point>(code_unit0);
}

// --------------------------------------------------------------------------------------------------------------------

constexpr m1::code_point m1::impl::utf16_code_point(char16_t const code_unit0,
                                                    char16_t const code_unit1) noexcept
{
    // mask lower 10-bits of each
    // combine code_unit0 as high bits, code_unit1 as low bits
    // add 0x10000
    return ((static_cast<code_point>(code_unit0 & 0b0000001111111111)) << 10) +
           ((static_cast<code_point>(code_unit1 & 0b0000001111111111))) +
           0x10000;
}

// ====================================================================================================================

#endif // M1_UTF16_DECODE_HPP
