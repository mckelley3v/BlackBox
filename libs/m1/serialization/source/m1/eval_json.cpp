#include "m1/eval_json.hpp"
#include "m1/parse_json.hpp"
#include "m1/crc32.hpp"
#include "m1/log.hpp"
#include "utf8.h"
#include <ostream>
#include <iterator>
#include <cmath>
#include <cctype>
#include <cassert>

// =====================================================================================================================

namespace u8 = utf8::unchecked;

// =====================================================================================================================
namespace
{
    // =================================================================================================================

    enum class sign_state
    {
        positive,
        negative,
    };

    // =================================================================================================================
} // namespace

// =====================================================================================================================

static int eval_sign(int x, sign_state sign);
static float eval_sign(float x, sign_state sign);

// ---------------------------------------------------------------------------------------------------------------------

static float exp10(int x);

// ---------------------------------------------------------------------------------------------------------------------

static void combine_int_digit(int &value, utf8::uint32_t digit);

// ---------------------------------------------------------------------------------------------------------------------

static void combine_int_xdigit(int &value, utf8::uint32_t xdigit);

// ---------------------------------------------------------------------------------------------------------------------

static bool eval_property(m1::log &logger, m1::json_token const &token, m1::crc32 &id);
static bool eval_property(m1::log &logger, m1::json_token const &token, std::string &name);

// ---------------------------------------------------------------------------------------------------------------------

static bool eval_int(m1::log &logger, m1::json_token const &token, int &value);

// ---------------------------------------------------------------------------------------------------------------------

static bool eval_float(m1::log &logger, m1::json_token const &token, float &value);

// ---------------------------------------------------------------------------------------------------------------------

static bool eval_string(m1::log &logger, m1::json_token const &token, m1::crc32 &value);
static bool eval_string(m1::log &logger, m1::json_token const &token, std::string &value);

// ---------------------------------------------------------------------------------------------------------------------

template <typename OutputIterator>
static bool eval_string_impl(m1::log &logger, m1::json_token const &token, OutputIterator out);

// =====================================================================================================================

bool m1::eval_json_property(log &logger, json_token const &token, crc32 &id)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected property name");
            return false;

        case json_token_id::property:
            return eval_property(logger, token, id);

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected property name");
            return false;

        case json_token_id::value_true:
        case json_token_id::value_false:
            M1_ERROR(logger, "Unexpected bool, expected property name");
            return false;

        case json_token_id::value_int:
        case json_token_id::value_float:
            M1_ERROR(logger, "Unexpected number, expected property name");
            return false;

        case json_token_id::value_string:
            M1_ERROR(logger, "Unexpected string, expected property name -- missing ':'");
            return false;

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::eval_json_property(log &logger, json_token const &token, std::string &name)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected property name");
            return false;

        case json_token_id::property:
            return eval_property(logger, token, name);

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected property name");
            return false;

        case json_token_id::value_true:
        case json_token_id::value_false:
            M1_ERROR(logger, "Unexpected bool, expected property name");
            return false;

        case json_token_id::value_int:
        case json_token_id::value_float:
            M1_ERROR(logger, "Unexpected number, expected property name");
            return false;

        case json_token_id::value_string:
            M1_ERROR(logger, "Unexpected string, expected property name -- missing ':'");
            return false;

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// =====================================================================================================================

bool m1::is_json_value(log &logger, json_token const &token)
{
    if(!is_json_value(token.id))
    {
        M1_ERROR(logger, "Unexpected token, expected value");
        return false;
    }

    return true;
}

// =====================================================================================================================

bool m1::eval_json_value(log &logger, json_token const &token, bool &value)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected bool");
            return false;

        case json_token_id::property:
            M1_ERROR(logger, "Unexpected property name, expected bool");
            return false;

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected bool");
            return false;

        case json_token_id::value_true:
            value = true;
            return true;

        case json_token_id::value_false:
            value = false;
            return true;

        case json_token_id::value_int:
        case json_token_id::value_float:
            M1_ERROR(logger, "Unexpected number, expected bool");
            return false;

        case json_token_id::value_string:
            M1_ERROR(logger, "Unexpected string, expected bool");
            return false;

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::eval_json_value(log &logger, json_token const &token, int &value)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected int");
            return false;

        case json_token_id::property:
            M1_ERROR(logger, "Unexpected property name, expected int");
            return false;

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected int");
            return false;

        case json_token_id::value_true:
        case json_token_id::value_false:
            M1_ERROR(logger, "Unexpected bool, expected int");
            return false;

        case json_token_id::value_int:
            return eval_int(logger, token, value);

        case json_token_id::value_float:
            M1_ERROR(logger, "Unexpected float, expected int");
            return false;

        case json_token_id::value_string:
            M1_ERROR(logger, "Unexpected string, expected int");
            return false;

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::eval_json_value(log &logger, json_token const &token, float &value)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected float");
            return false;

        case json_token_id::property:
            M1_ERROR(logger, "Unexpected property name, expected float");
            return false;

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected float");
            return false;

        case json_token_id::value_true:
        case json_token_id::value_false:
            M1_ERROR(logger, "Unexpected bool, expected float");
            return false;

        case json_token_id::value_int:
            {
                int value_int = 0;
                if (eval_int(logger, token, value_int))
                {
                    value = static_cast<float>(value_int);
                    return true;
                }
                return false;
            }

        case json_token_id::value_float:
            return eval_float(logger, token, value);

        case json_token_id::value_string:
            M1_ERROR(logger, "Unexpected string, expected float");
            return false;

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::eval_json_value(log &logger, json_token const &token, crc32 &crc)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected int");
            return false;

        case json_token_id::property:
            M1_ERROR(logger, "Unexpected property name, expected float");
            return false;

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected float");
            return false;

        case json_token_id::value_true:
        case json_token_id::value_false:
            M1_ERROR(logger, "Unexpected bool, expected float");
            return false;

        case json_token_id::value_int:
        case json_token_id::value_float:
            M1_ERROR(logger, "Unexpected number, expected float");
            return false;

        case json_token_id::value_string:
            return eval_string(logger, token, crc);

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::eval_json_value(log &logger, json_token const &token, std::string &value)
{
    switch(token.id)
    {
        case json_token_id::invalid:
            M1_ERROR(logger, "Invalid json\n");
            return false;

        case json_token_id::object_begin:
        case json_token_id::object_end:
        case json_token_id::array_begin:
        case json_token_id::array_end:
        case json_token_id::separator:
            M1_ERROR(logger, "Unexpected token, expected int");
            return false;

        case json_token_id::property:
            M1_ERROR(logger, "Unexpected property name, expected float");
            return false;

        case json_token_id::value_null:
            M1_ERROR(logger, "Unexpected null, expected float");
            return false;

        case json_token_id::value_true:
        case json_token_id::value_false:
            M1_ERROR(logger, "Unexpected bool, expected float");
            return false;

        case json_token_id::value_int:
        case json_token_id::value_float:
            M1_ERROR(logger, "Unexpected number, expected float");
            return false;

        case json_token_id::value_string:
            return eval_string(logger, token, value);

        default:
            assert(false && "Invalid token");
            return false;
    }
}

// =====================================================================================================================

/*static*/ int eval_sign(int x, sign_state sign)
{
    return (sign == sign_state::negative) ? -x : x;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ float eval_sign(float x, sign_state sign)
{
    return (sign == sign_state::negative) ? -x : x;
}

// =====================================================================================================================

/*static*/ float exp10(int const x)
{
    float const log10 = 2.30258509299f;
    return std::exp(static_cast<float>(x) * log10);
}

// =====================================================================================================================

/*static*/ void combine_int_digit(int &value, utf8::uint32_t const digit)
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

// =====================================================================================================================

/*static*/ void combine_int_xdigit(int &value, utf8::uint32_t const xdigit)
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

// =====================================================================================================================

/*static*/ bool eval_property(m1::log &logger, m1::json_token const &token, m1::crc32 &id)
{
    assert(token.id == m1::json_token_id::property);

    return eval_string_impl(logger, token, m1::crc32_combine_iterator(id));
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ bool eval_property(m1::log &logger, m1::json_token const &token, std::string &name)
{
    assert(token.id == m1::json_token_id::property);

    name.clear();
    name.reserve(token.end - token.begin);
    return eval_string_impl(logger, token, std::back_inserter(name));
}

// =====================================================================================================================

/*static*/ bool eval_int(m1::log &logger, m1::json_token const &token, int &value)
{
    assert(token.id == m1::json_token_id::value_int);

    enum class parse_state
    {
        int_begin,
        int_digit,
        int_digits,
        int_end,
    };

    value = 0;
    sign_state sign = sign_state::positive;
    parse_state state = parse_state::int_begin;

    char const *curr = token.begin;
    while(curr != token.end)
    {
        utf8::uint32_t const ch = u8::next(curr);

        switch(state)
        {
            case parse_state::int_begin:
                if(ch == '-')
                {
                    sign = sign_state::negative;
                    state = parse_state::int_digit;
                    break;
                }
                // fallthrough

            case parse_state::int_digit:
                if(ch == '0')
                {
                    combine_int_digit(value, ch);
                    state = parse_state::int_end;
                    break;
                }

                if(std::isdigit(ch))
                {
                    combine_int_digit(value, ch);
                    state = parse_state::int_digits;
                    break;
                }

                M1_ERROR(logger, "Error parsing int token\n");
                return false;

            case parse_state::int_digits:
                if(std::isdigit(ch))
                {
                    combine_int_digit(value, ch);
                    break;
                }
                // fallthrough

            case parse_state::int_end:
                M1_ERROR(logger, "Error parsing int token\n");
                return false;

            default:
                assert(false && "unexpected parse_state");
                return false;
        }
    }

    if(curr != token.end)
    {
        M1_ERROR(logger, "Error parsing int token\n");
        return false;
    }

    value = eval_sign(value, sign);
    return true;
}

// =====================================================================================================================

/*static*/ bool eval_float(m1::log &logger, m1::json_token const &token, float &value)
{
    assert(token.id == m1::json_token_id::value_float);

    enum class parse_state
    {
        int_begin,
        int_digit,
        int_digits,
        int_end,
        frac_begin,
        frac_digits,
        exp_begin,
        exp_digits,
    };

    value = 0.0f;
    int exp = 0;
    int ipart = 0;
    int fpart = 0;
    int fpart_exp = 0;
    sign_state sign = sign_state::positive;
    sign_state exp_sign = sign_state::positive;
    parse_state state = parse_state::int_begin;

    char const *curr = token.begin;
    while(curr != token.end)
    {
        utf8::uint32_t const ch = u8::next(curr);

        switch(state)
        {
            case parse_state::int_begin:
                if(ch == '-')
                {
                    sign = sign_state::negative;
                    state = parse_state::int_digit;
                    break;
                }
                // fallthrough

            case parse_state::int_digit:
                if(ch == '0')
                {
                    combine_int_digit(ipart, ch);
                    state = parse_state::int_end;
                    break;
                }

                if(std::isdigit(ch))
                {
                    combine_int_digit(ipart, ch);
                    state = parse_state::int_digits;
                    break;
                }

                M1_ERROR(logger, "Error parsing float token\n");
                return false;

            case parse_state::int_digits:
                if(std::isdigit(ch))
                {
                    combine_int_digit(ipart, ch);
                    break;
                }
                // fallthrough

            case parse_state::int_end:
                if((ch == 'e') || (ch == 'E'))
                {
                    state = parse_state::exp_begin;
                    break;
                }

                if(ch == '.')
                {
                    state = parse_state::frac_begin;
                    break;
                }

                M1_ERROR(logger, "Error parsing float token\n");
                return false;

            case parse_state::frac_begin:
                if(std::isdigit(ch))
                {
                    --fpart_exp;
                    combine_int_digit(fpart, ch);
                    state = parse_state::frac_digits;
                    break;
                }

                M1_ERROR(logger, "Error parsing float token\n");
                return false;

            case parse_state::frac_digits:
                if((ch == 'e') || (ch == 'E'))
                {
                    state = parse_state::exp_begin;
                    break;
                }

                if(std::isdigit(ch))
                {
                    --fpart_exp;
                    combine_int_digit(fpart, ch);
                    break;
                }

                M1_ERROR(logger, "Error parsing float token\n");
                return false;

            case parse_state::exp_begin:
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

                M1_ERROR(logger, "Error parsing float token\n");
                return false;

            default:
                assert(false && "unexpected parse_state");
                return false;
        }
    }

    if(curr != token.end)
    {
        M1_ERROR(logger, "Error parsing float token\n");
        return false;
    }

    if(fpart != 0) value = static_cast<float>(fpart) * exp10(fpart_exp);
    if(ipart != 0) value += static_cast<float>(ipart);
    if(exp != 0) value *= exp10(eval_sign(exp, exp_sign));
    value = eval_sign(value, sign);
    return true;
}

// =====================================================================================================================

/*static*/ bool eval_string(m1::log &logger, m1::json_token const &token, m1::crc32 &crc)
{
    assert(token.id == m1::json_token_id::value_string);

    return eval_string_impl(logger, token, m1::crc32_combine_iterator(crc));
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ bool eval_string(m1::log &logger, m1::json_token const &token, std::string &value)
{
    assert(token.id == m1::json_token_id::value_string);

    value.clear();
    value.reserve(token.end - token.begin);
    return eval_string_impl(logger, token, std::back_inserter(value));
}

// =====================================================================================================================

template <typename OutputIterator>
/*static*/ bool eval_string_impl(m1::log &logger, m1::json_token const &token, OutputIterator out)
{
    assert((token.id == m1::json_token_id::property) ||
           (token.id == m1::json_token_id::value_string));

    enum class parse_state
    {
        expect_any_char,
        expect_escaped_char,
        expect_xdigit0,
        expect_xdigit1,
        expect_xdigit2,
        expect_xdigit3,
    };

    parse_state state = parse_state::expect_any_char;
    int xdigit = 0u;

    char const *curr = token.begin;
    while(curr != token.end)
    {
        utf8::uint32_t ch = u8::next(curr);

        switch(state)
        {
            case parse_state::expect_any_char:
                switch(ch)
                {
                    case '\\':
                        state = parse_state::expect_escaped_char;
                        continue;

                    default:
                        break;
                }
                break;

            case parse_state::expect_escaped_char:
                switch(ch)
                {
                    case '\"':
                    case '\\':
                    case '/':
                        state = parse_state::expect_any_char;
                        break;

                    case 'b':
                        ch = '\b';
                        state = parse_state::expect_any_char;
                        break;

                    case 'f':
                        ch = '\f';
                        state = parse_state::expect_any_char;
                        break;

                    case 'n':
                        ch = '\n';
                        state = parse_state::expect_any_char;
                        break;

                    case 't':
                        ch = '\t';
                        state = parse_state::expect_any_char;
                        break;

                    case 'u':
                        xdigit = 0u;
                        state = parse_state::expect_xdigit3;
                        continue;

                    default:
                        M1_ERROR(logger, "Invalid escaped character\n");
                        return false;
                }
                break;

            case parse_state::expect_xdigit0:
            case parse_state::expect_xdigit1:
            case parse_state::expect_xdigit2:
            case parse_state::expect_xdigit3:
                if(std::isxdigit(ch))
                {
                    combine_int_xdigit(xdigit, ch);
                    switch(state)
                    {
                        case parse_state::expect_xdigit0:
                            ch = static_cast<utf8::uint32_t>(xdigit);
                            state = parse_state::expect_any_char;
                            break;

                        case parse_state::expect_xdigit1:
                            state = parse_state::expect_xdigit0;
                            continue;

                        case parse_state::expect_xdigit2:
                            state = parse_state::expect_xdigit1;
                            continue;

                        case parse_state::expect_xdigit3:
                            state = parse_state::expect_xdigit2;
                            continue;

                        default:
                            assert(false && "unexpected parse_state");
                            return false;
                    }
                    break;
                }

                // invalid char
                M1_ERROR(logger, "Invalid escaped character\n");
                return false;
        }

        u8::append(ch, out);
    }

    if(curr != token.end)
    {
        M1_ERROR(logger, "Error parsing string token\n");
        return false;
    }

    return true;
}
