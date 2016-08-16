#ifndef M1_UTF8_DECODE_HPP
#define M1_UTF8_DECODE_HPP

#include <cassert>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    void consume_utf8_byte_order_mark(InputItr &code_unit_itr,
                                      InputEnd code_unit_end) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    code_point utf8_decode_next(InputItr &code_unit_itr,
                                InputEnd code_unit_end,
                                code_point error_character = 0xFFFD) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename CodePointFunc>
    void utf8_decode_each(InputItr code_unit_itr,
                          InputEnd code_unit_end,
                          CodePointFunc code_point_func) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename CodePointFunc>
    void utf8_decode_each_n(InputItr code_unit_itr,
                            InputEnd code_unit_end,
                            std::size_t str_length,
                            CodePointFunc code_point_func) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename OutputItr>
    void utf8_decode_copy(InputItr code_unit_itr,
                          InputEnd code_unit_end,
                          OutputItr out_itr) noexcept;

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd,
              typename OutputItr>
    void utf8_decode_copy_n(InputItr code_unit_itr,
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

    constexpr bool in_range(code_point value,
                            code_point begin_value,
                            code_point end_value) noexcept;

    // ================================================================================================================

    constexpr bool utf8_continuation(unsigned char value) noexcept;

    // ================================================================================================================

    constexpr code_point utf8_code_point(unsigned char code_unit0) noexcept;

    constexpr code_point utf8_code_point(unsigned char code_unit0,
                                         unsigned char code_unit1) noexcept;

    constexpr code_point utf8_code_point(unsigned char code_unit0,
                                         unsigned char code_unit1,
                                         unsigned char code_unit2) noexcept;

    constexpr code_point utf8_code_point(unsigned char code_unit0,
                                         unsigned char code_unit1,
                                         unsigned char code_unit2,
                                         unsigned char code_unit3) noexcept;

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
void m1::consume_utf8_byte_order_mark(InputItr &code_unit_itr,
                                      InputEnd code_unit_end) noexcept
{
    for(unsigned char bom : {'\xEF', '\xBB', '\xBF'})
    {
        if(code_unit_itr == code_unit_end) return;
        if(*code_unit_itr != bom) return;
        ++code_unit_itr;
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
m1::code_point m1::utf8_decode_next(InputItr &code_unit_itr,
                                    InputEnd code_unit_end,
                                    code_point const error_character /*= 0xFFFD*/) noexcept
{
    assert(code_unit_itr != code_unit_end);

    unsigned char const code_unit0 = *code_unit_itr;
    ++code_unit_itr;

    if(code_unit0 < 0b10000000)
    {
        // 0xxxxxxx: 1 octet -- resulting code_point range is [0x0, 0x80)
        code_point const c = impl::utf8_code_point(code_unit0);

        // no way to have an invalid code_point here
        return c;
    }
    else if(code_unit0 < 0b11000000)
    {
        // 10xxxxxx: error -- this pattern is reserved for continuations
    }
    else if(code_unit0 < 0b11100000)
    {
        // 110xxxxx: 2 octets -- resulting code_point range is [0x80, 0x800)

        // get other code_unit (safely)
        if(code_unit_itr != code_unit_end)
        {
            unsigned char const code_unit1 = *code_unit_itr;
            ++code_unit_itr;

            // verify continuation and convert to code_point
            if(impl::utf8_continuation(code_unit1))
            {
                code_point const c = impl::utf8_code_point(code_unit0,
                                                           code_unit1);

                // explicitly verify code_point value to prevent overlong encodings
                if(impl::in_range(c, 0x80, 0x800))
                {
                    return c;
                }
            }
        }
    }
    else if(code_unit0 < 0b11110000)
    {
        // 1110xxxx: 3 octets -- resulting code_point range is [0x800, 0x10000) excluding [0xD800, 0xE000)

        // get other code_units (safely)
        if(code_unit_itr != code_unit_end)
        {
            unsigned char const code_unit1 = *code_unit_itr;
            ++code_unit_itr;

            if(code_unit_itr != code_unit_end)
            {
                unsigned char const code_unit2 = *code_unit_itr;
                ++code_unit_itr;

                // verify continuation and convert to code_point
                if(impl::utf8_continuation(code_unit1) &&
                   impl::utf8_continuation(code_unit2))
                {
                    code_point const c = impl::utf8_code_point(code_unit0,
                                                               code_unit1,
                                                               code_unit2);

                    // explicitly verify code_point value to prevent overlong encodings
                    // also protect against invalid encoding of utf-16 surrogate values
                    if( impl::in_range(c, 0x800, 0x10000) &&
                       !impl::in_range(c, 0xD800, 0xE000))
                    {
                        return c;
                    }
                }
            }
        }
    }
    else if(code_unit0 < 0b11111000)
    {
        // 11110xxx: 4 octets -- resulting code_point range is [0x10000, 0x110000)

        // get other code_units (safely)
        if(code_unit_itr != code_unit_end)
        {
            unsigned char const code_unit1 = *code_unit_itr;
            ++code_unit_itr;

            if(code_unit_itr != code_unit_end)
            {
                unsigned char const code_unit2 = *code_unit_itr;
                ++code_unit_itr;

                if(code_unit_itr != code_unit_end)
                {
                    unsigned char const code_unit3 = *code_unit_itr;
                    ++code_unit_itr;

                    // verify continuation and convert to code_point
                    if(impl::utf8_continuation(code_unit1) &&
                       impl::utf8_continuation(code_unit2) &&
                       impl::utf8_continuation(code_unit3))
                    {
                        code_point const c = impl::utf8_code_point(code_unit0,
                                                                   code_unit1,
                                                                   code_unit2,
                                                                   code_unit3);

                        // explicitly verify code_point value to prevent overlong encodings
                        if(impl::in_range(c, 0x10000, 0x110000))
                        {
                            return c;
                        }
                    }
                }
            }
        }
    }

    return error_character;
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename CodePointFunc>
void m1::utf8_decode_each(InputItr code_unit_itr,
                          InputEnd code_unit_end,
                          CodePointFunc code_point_func) noexcept
{
    while(code_unit_itr != code_unit_end)
    {
        code_point const c = utf8_decode_next(/*ref*/ code_unit_itr,
                                              code_unit_end);
        code_point_func(c);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename CodePointFunc>
void m1::utf8_decode_each_n(InputItr code_unit_itr,
                            InputEnd const code_unit_end,
                            std::size_t str_length,
                            CodePointFunc code_point_func) noexcept
{
    while((code_unit_itr != code_unit_end) && (str_length-- > 0))
    {
        code_point const c = utf8_decode_next(/*ref*/ code_unit_itr,
                                              code_unit_end);
        code_point_func(c);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename OutputItr>
void m1::utf8_decode_copy(InputItr code_unit_itr,
                          InputEnd code_unit_end,
                          OutputItr out_itr) noexcept
{
    while(code_unit_itr != code_unit_end)
    {
        code_point const c = utf8_decode_next(/*ref*/ code_unit_itr,
                                              code_unit_end);
        *out_itr = c;
        ++out_itr;
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd,
          typename OutputItr>
void m1::utf8_decode_copy_n(InputItr code_unit_itr,
                            InputEnd const code_unit_end,
                            std::size_t str_length,
                            OutputItr out_itr) noexcept
{
    while((code_unit_itr != code_unit_end) && (str_length-- > 0))
    {
        code_point const c = utf8_decode_next(/*ref*/ code_unit_itr,
                                              code_unit_end);
        *out_itr = c;
        ++out_itr;
    }
}

// ================================================================================================================

constexpr bool m1::impl::in_range(code_point value,
                                  code_point begin_value,
                                  code_point end_value) noexcept
{
    return ((begin_value <= value) && (value < end_value));
}

// ====================================================================================================================

constexpr bool m1::impl::utf8_continuation(unsigned char const value) noexcept
{
    // match pattern:  10xxxxxx:
    // constexpr unsigned char const value_bits    = 0b00111111;
    // constexpr unsigned char const required_bits = 0b10000000;
    return (value & 0b11000000) == 0b10000000;
}

// ====================================================================================================================

constexpr m1::code_point m1::impl::utf8_code_point(unsigned char const code_unit0) noexcept
{
    return static_cast<code_point>(code_unit0);
}

// --------------------------------------------------------------------------------------------------------------------

constexpr m1::code_point m1::impl::utf8_code_point(unsigned char const code_unit0,
                                                   unsigned char const code_unit1) noexcept
{
    return (static_cast<code_point>(code_unit0 & 0b00011111) << 6) |
           (static_cast<code_point>(code_unit1 & 0b00111111));
}

// --------------------------------------------------------------------------------------------------------------------

constexpr m1::code_point m1::impl::utf8_code_point(unsigned char const code_unit0,
                                                   unsigned char const code_unit1,
                                                   unsigned char const code_unit2) noexcept
{
    return (static_cast<code_point>(code_unit0 & 0b00001111) << 12) |
           (static_cast<code_point>(code_unit1 & 0b00111111) << 6) |
           (static_cast<code_point>(code_unit2 & 0b00111111));
}

// --------------------------------------------------------------------------------------------------------------------

constexpr m1::code_point m1::impl::utf8_code_point(unsigned char const code_unit0,
                                                   unsigned char const code_unit1,
                                                   unsigned char const code_unit2,
                                                   unsigned char const code_unit3) noexcept
{
    return (static_cast<code_point>(code_unit0 & 0b00000111) << 18) |
           (static_cast<code_point>(code_unit1 & 0b00111111) << 12) |
           (static_cast<code_point>(code_unit2 & 0b00111111) << 6) |
           (static_cast<code_point>(code_unit3 & 0b00111111));
}

// ====================================================================================================================

#endif // M1_UTF8_DECODE_HPP
