#include "m1/json_input_archive.hpp"
#include "m1/string_builder_base.hpp"
#include "m1/string_builder.hpp"
#include "m1/ustring_builder.hpp"
#include "m1/crc32_builder.hpp"
#include "m1/verify.hpp"
#include "m1/pragma_message.hpp"
#include <exception>
#include <cctype>

// ====================================================================================================================

namespace
{
    // ================================================================================================================

    enum class sign_state
    {
        positive,
        negative,
    };

    // ================================================================================================================
} // namespace

// ====================================================================================================================

static int eval_sign(int x, sign_state sign);
static float eval_sign(float x, sign_state sign);

static float exp10(int x);

static void combine_int_digit(int &value, m1::code_point digit);
static void combine_int_xdigit(int &value, m1::code_point xdigit);

// ====================================================================================================================

m1::serialization::json_input_archive::json_input_archive(std::streambuf *buffer_ptr)
    : m_Buffer(buffer_ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::json_input_archive::operator >> (bool &value)
{
    return read_bool(/*ref*/ value);
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::json_input_archive::operator >> (int &value)
{
    return read_int(/*ref*/ value);
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::json_input_archive::operator >> (float &value)
{
    return read_float(/*ref*/ value);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::serialization::json_input_archive::skip_space()
{
    while(std::isspace(peek_char()))
    {
        read_char();
    }
}

// --------------------------------------------------------------------------------------------------------------------

char32_t m1::serialization::json_input_archive::read_char()
{
    char32_t const ch = m_Buffer.sbumpc();

    if(ch == '\n')
    {
        ++m_Location.row;
        m_Location.col = 0;
    }
    else
    {
        ++m_Location.col;
    }

    return ch;
}

// --------------------------------------------------------------------------------------------------------------------

char32_t m1::serialization::json_input_archive::peek_char()
{
    return m_Buffer.sgetc();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::json_input_archive::read_bool(bool &value)
{
    bool result = false;
    switch(read_char())
    {
        case 't':
            value = true;
            result = (read_char() == 'r') &&
                     (read_char() == 'u') &&
                     (read_char() == 'e');
            break;

        case 'f':
            value = false;
            result = (read_char() == 'a') &&
                     (read_char() == 'l') &&
                     (read_char() == 's') &&
                     (read_char() == 'e');
            break;
    }

    return M1_VERIFY(result,
                     throw make_json_syntax_error("Invalid bool: expected \"true\" or \"false\""));
}

// --------------------------------------------------------------------------------------------------------------------

#pragma M1_MESSAGE("implement int overflow detection")
bool m1::serialization::json_input_archive::read_int(int &value)
{
    enum class parse_state
    {
        int_sign,    // -
        int_digit0,  // 0 or [1-9]
        int_digits,  // [0-9]
        int_end,
    };

    value = 0;
    sign_state sign = sign_state::positive;
    parse_state state = parse_state::int_sign;

    while(state != parse_state::int_end)
    {
        // delay read_char until ch is known good
        code_point const ch = peek_char();

        switch(state)
        {
            case parse_state::int_sign:
                if(ch == '-')
                {
                    sign = sign_state::negative;
                    state = parse_state::int_digit0;
                    break;
                }
                // fallthrough

            case parse_state::int_digit0:
                if(ch == '0')
                {
                    // no octal support, a number with a leading 0 is considered complete
                    value = 0;
                    state = parse_state::int_end;
                    break;
                }

                if(std::isdigit(ch))
                {
                    combine_int_digit(/*ref*/ value, ch);
                    state = parse_state::int_digits;
                    break;
                }

                // no digits
                return M1_ERROR(throw make_json_syntax_error("Invalid int: no digits"));

            case parse_state::int_digits:
                if(std::isdigit(ch))
                {
                    combine_int_digit(/*ref*/ value, ch);
                    break;
                }

                state = parse_state::int_end;
                // skip read_char, may need ch for next parse
                continue;
        }

        // consume ch
        read_char();
    }

    if(state == parse_state::int_end)
    {
        value = eval_sign(value, sign);
        return true;
    }

    return M1_ERROR(throw make_json_syntax_error("Invalid int"));
}

// --------------------------------------------------------------------------------------------------------------------

#pragma M1_MESSAGE("implement float overflow detection")
bool m1::serialization::json_input_archive::read_float(float &value)
{
    enum class parse_state
    {
        int_sign,    // -
        int_digit0,  // 0 or [1-9]
        int_digits,  // [0-9]
        int_end,     // . or e,E
        frac_digit0, // [0-9]
        frac_digits, // [0-9] or e,E
        exp_sign,    // -,+
        exp_digits,  // [0-9]
        float_end,
    };

    value = 0.0f;
    int exp = 0;
    int ipart = 0;
    int fpart = 0;
    int fpart_exp = 0;
    sign_state sign = sign_state::positive;
    sign_state exp_sign = sign_state::positive;
    parse_state state = parse_state::int_sign;

    while(state != parse_state::float_end)
    {
        // delay read_char until ch is known good
        code_point const ch = peek_char();

        switch(state)
        {
            case parse_state::int_sign:
                if(ch == '-')
                {
                    sign = sign_state::negative;
                    state = parse_state::int_digit0;
                    break;
                }
                // fallthrough

            case parse_state::int_digit0:
                if(ch == '0')
                {
                    ipart = 0;
                    state = parse_state::int_end;
                    break;
                }

                if(std::isdigit(ch))
                {
                    combine_int_digit(ipart, ch);
                    state = parse_state::int_digits;
                    break;
                }

                // no digits
                return M1_ERROR(throw make_json_syntax_error("Invalid float: no digits"));

            case parse_state::int_digits:
                if(std::isdigit(ch))
                {
                    combine_int_digit(ipart, ch);
                }
                // fallthrough

            case parse_state::int_end:
                if((ch == 'e') || (ch == 'E'))
                {
                    state = parse_state::exp_sign;
                    break;
                }

                if(ch == '.')
                {
                    state = parse_state::frac_digit0;
                    break;
                }

                state = parse_state::float_end;
                // skip read_char, may need ch for next parse
                continue;

            case parse_state::frac_digit0:
                if(std::isdigit(ch))
                {
                    --fpart_exp;
                    combine_int_digit(fpart, ch);
                    state = parse_state::frac_digits;
                    break;
                }

                return M1_ERROR(throw make_json_syntax_error("Invalid float: expected float digit"));

            case parse_state::frac_digits:
                if((ch == 'e') || (ch == 'E'))
                {
                    state = parse_state::exp_sign;
                    break;
                }

                if(std::isdigit(ch))
                {
                    --fpart_exp;
                    combine_int_digit(fpart, ch);
                    break;
                }

                state = parse_state::float_end;
                // skip read_char, may need ch for next parse
                continue;

            case parse_state::exp_sign:
                if(ch == '+')
                {
                    exp_sign = sign_state::positive;
                    state = parse_state::exp_digits;
                    break;
                }

                if(ch == '-')
                {
                    exp_sign = sign_state::negative;
                    state = parse_state::exp_digits;
                    break;
                }
                // fallthrough

            case parse_state::exp_digits:
                if(std::isdigit(ch))
                {
                    combine_int_digit(exp, ch);
                    break;
                }

                state = parse_state::float_end;
                // skip read_char, may need ch for next parse
                continue;
        }

        // consume ch
        read_char();
    }

    if(state == parse_state::float_end)
    {
        if(fpart != 0) value = static_cast<float>(fpart) * exp10(fpart_exp);
        if(ipart != 0) value += static_cast<float>(ipart);
        if(exp != 0) value *= exp10(eval_sign(exp, exp_sign));
        value = eval_sign(value, sign);
        return true;
    }

    return M1_ERROR(throw make_json_syntax_error("Invalid float"));
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::json_input_archive::read_string(string_builder_base &value)
{
    enum class parse_state
    {
        begin_quote,
        any_char,
        escaped_char,
        xdigit0,
        xdigit1,
        xdigit2,
        xdigit3,
        end_quote,
    };

    int xdigit = 0u;
    parse_state state = parse_state::begin_quote;
    while(state != parse_state::end_quote)
    {
        code_point const ch = read_char();

        switch(state)
        {
            case parse_state::begin_quote:
                switch(ch)
                {
                    case '\"':
                        state = parse_state::any_char;
                        break;

                    default:
                        // no begin quote
                        return M1_ERROR(throw make_json_syntax_error("Invalid string: expected leading \""));
                }

            case parse_state::any_char:
                switch(ch)
                {
                    case '\\':
                    {
                        state = parse_state::escaped_char;
                        break;
                    }

                    case '\"':
                    {
                        // end quote, string is complete
                        state = parse_state::end_quote;
                        break;
                    }

                    default:
                        value.append(ch);
                        break;
                }

            case parse_state::escaped_char:
                switch(ch)
                {
                    case '\"':
                    case '\\':
                    case '/':
                        value.append(ch);
                        state = parse_state::any_char;
                        break;

                    case 'b':
                        value.append('\b');
                        state = parse_state::any_char;
                        break;

                    case 'f':
                        value.append('\f');
                        state = parse_state::any_char;
                        break;

                    case 'n':
                        value.append('\n');
                        state = parse_state::any_char;
                        break;

                    case 't':
                        value.append('\t');
                        state = parse_state::any_char;
                        break;

                    case 'u':
                        xdigit = 0u;
                        state = parse_state::xdigit3;
                        break;

                    default:
                        // invalid escaped char
                        return M1_ERROR(throw make_json_syntax_error("Invalid string: invalid escaped char"));
                }

            case parse_state::xdigit0:
            case parse_state::xdigit1:
            case parse_state::xdigit2:
            case parse_state::xdigit3:
                if(std::isxdigit(ch))
                {
                    combine_int_xdigit(xdigit, ch);
                    switch(state)
                    {
                        case parse_state::xdigit0:
                            value.append(static_cast<code_point>(xdigit));
                            state = parse_state::any_char;
                            break;

                        case parse_state::xdigit1:
                            state = parse_state::xdigit0;
                            break;

                        case parse_state::xdigit2:
                            state = parse_state::xdigit1;
                            break;

                        case parse_state::xdigit3:
                            state = parse_state::xdigit2;
                            break;
                    }
                }

                // expected hex digit
                return M1_ERROR(throw make_json_syntax_error("Invalid string: expected hex digit for \u escape sequence"));
        }
    }

    if(state == parse_state::end_quote)
    {
        return true;
    }

    return M1_ERROR(throw make_json_syntax_error("Invalid string"));
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::json_input_archive::read_property_id(property_id &id)
{
    crc32_builder builder;
    if(read_string(/*ref*/ builder))
    {
        skip_space();
        if(read_char() == ':')
        {
            id = property_id(std::move(builder).crc());
            return true;
        }
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------

m1::serialization::json_input_error m1::serialization::json_input_archive::make_json_input_error(char const *message) const
{
    return json_input_error(m_Location.row,
                            m_Location.col,
                            message);
}

// --------------------------------------------------------------------------------------------------------------------

m1::serialization::json_syntax_error m1::serialization::json_input_archive::make_json_syntax_error(char const *message) const
{
    return json_syntax_error(m_Location.row,
                             m_Location.col,
                             message);
}

// ====================================================================================================================

bool m1::serialization::operator >> (json_input_archive &in, crc32 &value)
{
    crc32_builder builder;
    if(in >> builder)
    {
        value = std::move(builder).crc();
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::operator >> (json_input_archive &in, std::string &value)
{
    u8string_builder builder;
    if(in >> builder)
    {
        value = std::move(builder).str();
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::operator >> (json_input_archive &in, std::wstring &value)
{
    wstring_builder builder;
    if(in >> builder)
    {
        value = std::move(builder).str();
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::operator >> (json_input_archive &in, std::u16string &value)
{
    u16string_builder builder;
    if(in >> builder)
    {
        value = std::move(builder).str();
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::operator >> (json_input_archive &in, std::u32string &value)
{
    u32string_builder builder;
    if(in >> builder)
    {
        value = std::move(builder).str();
        return true;
    }

    return false;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::serialization::operator >> (json_input_archive &in, ustring &value)
{
    ustring_builder builder;
    if(in >> builder)
    {
        value = std::move(builder).str();
        return true;
    }

    return false;
}

// ====================================================================================================================

/*static*/ int eval_sign(int const x, sign_state const sign)
{
    return (sign == sign_state::negative) ? -x : x;
}

// --------------------------------------------------------------------------------------------------------------------

/*static*/ float eval_sign(float const x, sign_state const sign)
{
    return (sign == sign_state::negative) ? -x : x;
}

// ====================================================================================================================

/*static*/ float exp10(int const x)
{
    float const log10 = 2.30258509299f;
    return std::exp(static_cast<float>(x) * log10);
}

// ====================================================================================================================

/*static*/ void combine_int_digit(int &value, m1::code_point const digit)
{
    assert(std::isdigit(digit));

    value *= 10;
    switch(digit)
    {
        case '0': break;
        case '1': value += 1; break;
        case '2': value += 2; break;
        case '3': value += 3; break;
        case '4': value += 4; break;
        case '5': value += 5; break;
        case '6': value += 6; break;
        case '7': value += 7; break;
        case '8': value += 8; break;
        case '9': value += 9; break;
    }
}

// ====================================================================================================================

/*static*/ void combine_int_xdigit(int &value, m1::code_point const xdigit)
{
    assert(std::isxdigit(xdigit));

    value <<= 4;
    switch(xdigit)
    {
        case '0': break;
        case '1': value += 0x1; break;
        case '2': value += 0x2; break;
        case '3': value += 0x3; break;
        case '4': value += 0x4; break;
        case '5': value += 0x5; break;
        case '6': value += 0x6; break;
        case '7': value += 0x7; break;
        case '8': value += 0x8; break;
        case '9': value += 0x9; break;
        case 'a': case 'A': value += 0xA; break;
        case 'b': case 'B': value += 0xB; break;
        case 'c': case 'C': value += 0xC; break;
        case 'd': case 'D': value += 0xD; break;
        case 'e': case 'E': value += 0xE; break;
        case 'f': case 'F': value += 0xF; break;
    }
}

// ====================================================================================================================
