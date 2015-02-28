#include "m1/parse_json.hpp"
#include "utf8.h"
#include <cctype>
#include <cassert>

// =====================================================================================================================

using m1::json_token;
using m1::json_token_id;
namespace u8 = utf8::unchecked;

// =====================================================================================================================

static char const*& u8_advance(char const * &curr);

// =====================================================================================================================

static bool skip_space(char const * &curr,
                       char const * const end);

// =====================================================================================================================

static bool expect_char(char const * &curr,
                        char const * const end,
                        utf8::uint32_t const ch);

// =====================================================================================================================

static bool expect_xdigit(char const * &curr,
                          char const * const end);

// =====================================================================================================================

static bool is_end_of_number(utf8::uint32_t const ch);

// =====================================================================================================================

static json_token parse_json_token_string(char const * &curr,
                                          char const * const end);

// =====================================================================================================================

static json_token parse_json_token_null(char const * &curr,
                                        char const * const end);

// =====================================================================================================================

static json_token parse_json_token_true(char const * &curr,
                                        char const * const end);

// =====================================================================================================================

static json_token parse_json_token_false(char const * &curr,
                                         char const * const end);

// =====================================================================================================================

static json_token parse_json_token_number(char const * &curr,
                                          char const * const end);

// =====================================================================================================================

/*static*/ char const*& u8_advance(char const * &curr)
{
    u8::next(curr);
    return curr;
}

// =====================================================================================================================

/*static*/ bool skip_space(char const * &curr,
                           char const * const end)
{
    assert(curr != nullptr);
    assert(end != nullptr);

    for(char const *itr = curr; itr != end;)
    {
        utf8::uint32_t const ch = u8::next(itr);
        if(!std::isspace(ch))
        {
            break;
        }

        curr = itr;
    }

    return curr != end;
}

// =====================================================================================================================

/*static*/ bool expect_char(char const * &curr,
                            char const * const end,
                            utf8::uint32_t const ch)
{
    return (curr != end) && (u8::next(curr) == ch);
}

// =====================================================================================================================

/*static*/ bool expect_xdigit(char const * &curr,
                              char const * const end)
{
    return (curr != end) && std::isxdigit(u8::next(curr));
}

// =====================================================================================================================

/*static*/ bool is_end_of_number(utf8::uint32_t const ch)
{
    return std::ispunct(ch) || std::isspace(ch);
}

// =====================================================================================================================

bool m1::is_json_value(json_token_id const id)
{
    switch(id)
    {
        case json_token_id::value_null:
        case json_token_id::value_true:
        case json_token_id::value_false:
        case json_token_id::value_int:
        case json_token_id::value_float:
        case json_token_id::value_string:
            return true;

        default:
            return false;
    }
}

// =====================================================================================================================

json_token m1::parse_json_token(char const * &curr,
                                char const * const end)
{
    if(skip_space(curr, end))
    {
        char const * const begin = curr;
        utf8::uint32_t const ch = u8::peek_next(curr);

        switch(ch)
        {
            case '{':  return { json_token_id::object_begin, begin, u8_advance(curr) };
            case '}':  return { json_token_id::object_end,   begin, u8_advance(curr) };
            case '[':  return { json_token_id::array_begin,  begin, u8_advance(curr) };
            case ']':  return { json_token_id::array_end,    begin, u8_advance(curr) };
            case ',':  return { json_token_id::separator,    begin, u8_advance(curr) };
            case 'n':  return parse_json_token_null(curr, end);
            case 't':  return parse_json_token_true(curr, end);
            case 'f':  return parse_json_token_false(curr, end);
            case '"':
            {
                json_token const string_token = parse_json_token_string(curr, end);
                if((string_token.id == json_token_id::value_string) &&
                    skip_space(curr, end) &&
                    (u8::peek_next(curr) == ':'))
                {
                    u8::next(curr);
                    return { json_token_id::property, string_token.begin, string_token.end };
                }

                return string_token;
            }

            default:
                return parse_json_token_number(curr, end);
        }
    }

    return { json_token_id::invalid, curr, end };
}

// =====================================================================================================================

/*static*/ json_token parse_json_token_string(char const * &curr,
                                              char const * const end)
{
    assert(curr != end);
    assert(!std::isspace(u8::peek_next(curr)));
    assert(u8::peek_next(curr) == '"');

    enum class parse_state
    {
        expect_begin_quote,
        expect_first_char,
        expect_any_char,
        expect_escaped_char,
        expect_xdigit0,
        expect_xdigit1,
        expect_xdigit2,
        expect_xdigit3,
        end_of_string,
    };

    char const * const begin = curr;
    char const * str_begin = nullptr;
    char const * str_end = nullptr;

    parse_state state = parse_state::expect_begin_quote;
    while((curr != end) && (state != parse_state::end_of_string))
    {
        char const * const prev = curr;
        utf8::uint32_t const ch = u8::next(curr);

        switch(state)
        {
            case parse_state::expect_begin_quote:
                switch(ch)
                {
                    case '\"':
                        state = parse_state::expect_first_char;
                        break;

                    default:
                        // invalid char
                        return { json_token_id::invalid, begin, curr };
                }
                break;

            case parse_state::expect_first_char:
                str_begin = prev;
                state = parse_state::expect_any_char;
                // fallthrough

            case parse_state::expect_any_char:
                switch(ch)
                {
                    case '\\':
                        state = parse_state::expect_escaped_char;
                        break;

                    case '\"':
                        str_end = prev;
                        state = parse_state::end_of_string;
                        break;

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
                    case 'b':
                    case 'f':
                    case 'n':
                    case 't':
                        state = parse_state::expect_any_char;
                        break;

                    case 'u':
                        state = parse_state::expect_xdigit3;
                        break;

                    default:
                        // invalid char
                        return { json_token_id::invalid, begin, curr };
                }
                break;

            case parse_state::expect_xdigit0:
            case parse_state::expect_xdigit1:
            case parse_state::expect_xdigit2:
            case parse_state::expect_xdigit3:
                if(std::isxdigit(ch))
                {
                    switch(state)
                    {
                        case parse_state::expect_xdigit0:
                            state = parse_state::expect_any_char;
                            break;

                        case parse_state::expect_xdigit1:
                            state = parse_state::expect_xdigit0;
                            break;

                        case parse_state::expect_xdigit2:
                            state = parse_state::expect_xdigit1;
                            break;

                        case parse_state::expect_xdigit3:
                            state = parse_state::expect_xdigit2;
                            break;

                        default:
                            assert(false && "unexpected parse_state");
                            state = parse_state::expect_any_char;
                            break;
                    }
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            default:
                assert(false && "unexpected parse_state");
                return { json_token_id::invalid, begin, curr };
        }
    }

    if(state == parse_state::end_of_string)
    {
        assert(str_begin != nullptr);
        assert(str_end != nullptr);
        return { json_token_id::value_string, str_begin, str_end };
    }

    return { json_token_id::invalid, begin, curr };
}

// =====================================================================================================================

/*static*/ json_token parse_json_token_null(char const * &curr,
                                            char const * const end)
{
    assert(curr != end);
    assert(!std::isspace(u8::peek_next(curr)));

    char const * const begin = curr;

    if(expect_char(curr, end, 'n') &&
       expect_char(curr, end, 'u') &&
       expect_char(curr, end, 'l') &&
       expect_char(curr, end, 'l'))
    {
        return { json_token_id::value_null, begin, curr };
    }

    return { json_token_id::invalid, begin, curr };
}

// =====================================================================================================================

/*static*/ json_token parse_json_token_true(char const * &curr,
                                            char const * const end)
{
    assert(curr != end);
    assert(!std::isspace(u8::peek_next(curr)));

    char const * const begin = curr;

    if(expect_char(curr, end, 't') &&
       expect_char(curr, end, 'r') &&
       expect_char(curr, end, 'u') &&
       expect_char(curr, end, 'e'))
    {
        return { json_token_id::value_true, begin, curr };
    }

    return { json_token_id::invalid, begin, curr };
}

// =====================================================================================================================

/*static*/ json_token parse_json_token_false(char const * &curr,
                                             char const * const end)
{
    assert(curr != end);
    assert(!std::isspace(u8::peek_next(curr)));

    char const * const begin = curr;

    if(expect_char(curr, end, 'f') &&
       expect_char(curr, end, 'a') &&
       expect_char(curr, end, 'l') &&
       expect_char(curr, end, 's') &&
       expect_char(curr, end, 'e'))
    {
        return { json_token_id::value_false, begin, curr };
    }

    return { json_token_id::invalid, begin, curr };
}

// =====================================================================================================================

/*static*/ json_token parse_json_token_number(char const * &curr,
                                              char const * const end)
{
    assert(curr != end);
    assert(!std::isspace(u8::peek_next(curr)));
    assert((u8::peek_next(curr) == '-') || std::isdigit(u8::peek_next(curr)));

    enum class parse_state
    {
        int_begin,
        int_digit,
        int_digits,
        int_end,
        frac_begin,
        frac_digits,
        exp_begin,
        exp_digit,
        exp_digits,
        end_of_number,
    };

    json_token_id type = json_token_id::value_int;
    char const * const begin = curr;

    parse_state state = parse_state::int_begin;
    while((curr != end) && (state != parse_state::end_of_number))
    {
        char const * const prev = curr;
        utf8::uint32_t const ch = u8::next(curr);

        switch(state)
        {
            case parse_state::int_begin:
                if(ch == '-')
                {
                    state = parse_state::int_digit;
                    break;
                }
                // fallthrough

            case parse_state::int_digit:
                if(ch == '0')
                {
                    state = parse_state::int_end;
                    break;
                }

                if(std::isdigit(ch))
                {
                    state = parse_state::int_digits;
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            case parse_state::int_digits:
                if(std::isdigit(ch))
                {
                    break;
                }
                // fallthrough

            case parse_state::int_end:
                if((ch == 'e') || (ch == 'E'))
                {
                    type = json_token_id::value_float;
                    state = parse_state::exp_begin;
                    break;
                }

                if(ch == '.')
                {
                    type = json_token_id::value_float;
                    state = parse_state::frac_begin;
                    break;
                }

                if(is_end_of_number(ch))
                {
                    curr = prev;
                    state = parse_state::end_of_number;
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            case parse_state::frac_begin:
                if(std::isdigit(ch))
                {
                    state = parse_state::frac_digits;
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            case parse_state::frac_digits:
                if((ch == 'e') || (ch == 'E'))
                {
                    state = parse_state::exp_begin;
                    break;
                }

                if(std::isdigit(ch))
                {
                    break;
                }

                if(is_end_of_number(ch))
                {
                    curr = prev;
                    state = parse_state::end_of_number;
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            case parse_state::exp_begin:
                if((ch == '+') || (ch == '-'))
                {
                    state = parse_state::exp_digit;
                    break;
                }
                // fallthrough

            case parse_state::exp_digit:
                if(std::isdigit(ch))
                {
                    state = parse_state::exp_digits;
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            case parse_state::exp_digits:
                if(std::isdigit(ch))
                {
                    break;
                }

                if(is_end_of_number(ch))
                {
                    curr = prev;
                    state = parse_state::end_of_number;
                    break;
                }

                // invalid char
                return { json_token_id::invalid, begin, curr };

            default:
                assert(false && "unexpected parse_state");
                return { json_token_id::invalid, begin, curr };
        }
    }

    if(state == parse_state::end_of_number)
    {
        return { type, begin, curr };
    }

    return { json_token_id::invalid, begin, curr };
}

// =====================================================================================================================
