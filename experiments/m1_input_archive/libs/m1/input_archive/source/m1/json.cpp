#include "m1/utf8_decode.hpp"
#include "m1/crc32.hpp"
#include "m1/property_id.hpp"
#include "m1/ustring.hpp"
#include <cctype>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    class utf8_input_buffer
    {
    public:
        utf8_input_buffer();
        ~utf8_input_buffer() = default;

        template <typename InputItr,
                  typename InputEnd>
        code_point read(InputItr &itr,
                        InputEnd end);

        template <typename InputItr,
                  typename InputEnd>
        code_point peek(InputItr &itr,
                        InputEnd end);

        template <typename InputItr,
                  typename InputEnd>
        bool const empty(InputItr itr,
                         InputEnd end) const;

    private:
        utf8_input_buffer(utf8_input_buffer &&rhs) = delete;
        utf8_input_buffer(utf8_input_buffer const &rhs) = delete;
        utf8_input_buffer& operator = (utf8_input_buffer &&rhs) = delete;
        utf8_input_buffer& operator = (utf8_input_buffer const &rhs) = delete;

        bool buffer_empty() const;

        template <typename InputItr,
                  typename InputEnd>
        void fill(InputItr &itr,
                  InputEnd end);

        // members:
        typedef std::uint8_t index_t;
        constexpr static std::size_t const k_Capacity = 4;

        code_point m_Data[k_Capacity] = {};
        std::size_t m_Len = 0u;
        index_t m_Pos : 2;
        index_t m_End : 2;
    };

    // ----------------------------------------------------------------------------------------------------------------

    struct json_location
    {
        int row;
        int col;
    };

    // ----------------------------------------------------------------------------------------------------------------

    struct json_context
    {
        utf8_input_buffer input_buffer;
        json_location location;
        char const *error_msg;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename InputItr,
              typename InputEnd>
    bool json_empty(json_context const &context,
                    InputItr itr,
                    InputEnd end);

    // ----------------------------------------------------------------------------------------------------------------

    template <typename InputItr,
              typename InputEnd>
    code_point json_read(json_context &context,
                         InputItr &itr,
                         InputEnd end);

    // ----------------------------------------------------------------------------------------------------------------

    template <typename InputItr,
              typename InputEnd>
    code_point json_peek(json_context &context,
                         InputItr &itr,
                         InputEnd end);

    // ----------------------------------------------------------------------------------------------------------------

    bool json_error(json_context &context,
                    char const *error_msg);

    // ================================================================================================================

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_key_id(serialization::property_id &key,    // result of successful parsing
                           json_context &context,              // tracks parsing state and manages input buffer
                           InputItr &itr,                      // utf8 octet (char8_t) iterator
                           InputEnd end);                      // utf8 octet (char8_t) terminator

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_key_name(ustring &key,                       // result of successful parsing
                             json_context &context,              // tracks parsing state and manages input buffer
                             InputItr &itr,                      // utf8 octet (char8_t) iterator
                             InputEnd end);                      // utf8 octet (char8_t) terminator

    // ================================================================================================================

    // returns one of {json_parse_success, json_parse_failure, code point value immediately following parsed value}

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_bool(bool &value,                      // result of successful parsing
                         json_context &context,            // tracks parsing state and manages input buffer
                         InputItr &itr,                    // utf8 octet (char8_t) iterator
                         InputEnd end);                    // utf8 octet (char8_t) terminator

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_int(int &value,                       // result of successful parsing
                        json_context &context,            // tracks parsing state and manages input buffer
                        InputItr &itr,                    // utf8 octet (char8_t) iterator
                        InputEnd end);                    // utf8 octet (char8_t) terminator

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_float(float &value,                     // result of successful parsing
                          json_context &context,            // tracks parsing state and manages input buffer
                          InputItr &itr,                    // utf8 octet (char8_t) iterator
                          InputEnd end);                    // utf8 octet (char8_t) terminator

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_crc32(crc32 &value,                     // result of successful parsing
                          json_context &context,            // tracks parsing state and manages input buffer
                          InputItr &itr,                    // utf8 octet (char8_t) iterator
                          InputEnd end);                    // utf8 octet (char8_t) terminator

    template <typename InputItr,
              typename InputEnd>
    bool parse_json_ustring(ustring &value,                   // result of successful parsing
                            json_context &context,            // tracks parsing state and manages input buffer
                            InputItr &itr,                    // utf8 octet (char8_t) iterator
                            InputEnd end);                    // utf8 octet (char8_t) terminator

    template <typename OutputItr,
              typename InputItr,
              typename InputEnd>
    bool parse_json_string(OutputItr out,                   // result of successful parsing
                          json_context &context,            // tracks parsing state and manages input buffer
                          InputItr &itr,                    // utf8 octet (char8_t) iterator
                          InputEnd end);                    // utf8 octet (char8_t) terminator

    // ================================================================================================================
} // namespace m1

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

template <typename InputItr,
          typename InputEnd>
static void skip_space(m1::json_context &context,
                       InputItr &itr,
                       InputEnd end);

static int eval_sign(int x, sign_state sign);
static float eval_sign(float x, sign_state sign);

static float exp10(int x);

static void combine_int_digit(int &value, m1::code_point digit);
static void combine_int_xdigit(int &value, m1::code_point xdigit);

// ====================================================================================================================

m1::utf8_input_buffer::utf8_input_buffer()
    : m_Pos()
    , m_End()
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
m1::code_point m1::utf8_input_buffer::read(InputItr &itr,
                                           InputEnd end)
{
    assert(!empty(itr, end));

    if(buffer_empty())
    {
        fill(/*ref*/ itr, end);
    }

    assert(!empty(itr, end));

    --m_Len;
    return m_Data[m_Pos++];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
m1::code_point m1::utf8_input_buffer::peek(InputItr &itr,
                                           InputEnd end)
{
    assert(!empty(itr, end));

    if(buffer_empty())
    {
        fill(/*ref*/ itr, end);
    }

    assert(!empty(itr, end));

    return m_Data[m_Pos];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
bool const m1::utf8_input_buffer::empty(InputItr itr,
                                        InputEnd end) const
{
    return (itr == end) && buffer_empty();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::utf8_input_buffer::buffer_empty() const
{
    return m_Len == 0u;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
void m1::utf8_input_buffer::fill(InputItr &itr,
                                 InputEnd end)
{
    // relying on unsigned overflow to circularly wrap indices
    while((itr != end) && (m_Len < k_Capacity))
    {
        m_Data[m_End] = utf8_decode_next(/*ref*/ itr, end);
        ++m_End;
        ++m_Len;
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
bool m1::json_empty(json_context const &context,
                    InputItr itr,
                    InputEnd end)
{
    return context.input_buffer.empty(itr, end);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
m1::code_point m1::json_read(json_context &context,
                             InputItr &itr,
                             InputEnd end)
{
    m1::code_point const ch = context.input_buffer.read(/*ref*/ itr, end);
    if(ch == '\n')
    {
        ++context.location.row;
        context.location.col = 0;
    }
    else
    {
        ++context.location.col;
    }

    return ch;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
m1::code_point m1::json_peek(json_context &context,
                             InputItr &itr,
                             InputEnd end)
{
    return context.input_buffer.peek(itr, end);
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::json_error(json_context &context,
                    char const *error_msg)
{
    context.error_msg = error_msg;
    return false;
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
bool m1::parse_json_bool(bool &value,
                         json_context &context,
                         InputItr &itr,
                         InputEnd end)
{
    assert(!json_empty(context, itr, end));

    bool result = false;
    switch(json_read(/*ref*/ context, /*ref*/ itr, end))
    {
        case 't':
            value = true;
            result = (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 'r')) &&
                     (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 'u')) &&
                     (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 'e'));
            break;

        case 'f':
            value = false;
            result = (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 'a')) &&
                     (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 'l')) &&
                     (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 's')) &&
                     (!json_empty(context, itr, end) && (json_read(/*ref*/ context, /*ref*/ itr, end) == 'e'));
            break;
    }

    if(result)
    {
        return true;
    }

    return json_error(/*ref*/ context,
                      "Invalid bool: expected \"true\" or \"false\"");
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
bool m1::parse_json_int(int &value,
                        json_context &context,
                        InputItr &itr,
                        InputEnd end)
{
    assert(!json_empty(context, itr, end));

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

    while(!json_empty(context, itr, end) && (state != parse_state::int_end))
    {
        // delay json_read until ch is known good
        code_point const ch = json_peek(/*ref*/ context, /*ref*/ itr, end);

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
                return json_error(/*ref*/ context,
                                  "Invalid int: no digits");

            case parse_state::int_digits:
                if(std::isdigit(ch))
                {
                    combine_int_digit(/*ref*/ value, ch);
                    break;
                }

                state = parse_state::int_end;
                // skip json_read, may need ch for next parse
                continue;
        }

        // consume ch
        json_read(/*ref*/ context, /*ref*/ itr, end);
    }

    if (state == parse_state::int_end)
    {
        value = eval_sign(value, sign);
        return true;
    }

    return json_error(/*ref*/ context,
                      "Invalid int");
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
bool m1::parse_json_float(float &value,
                          json_context &context,
                          InputItr &itr,
                          InputEnd end)
{
    assert(!json_empty(context, itr, end));

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

    while(!json_empty(context, itr, end) && (state != parse_state::float_end))
    {
        // delay json_read until ch is known good
        code_point const ch = json_peek(/*ref*/ context, /*ref*/ itr, end);

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
                return json_error(/*ref*/ context,
                                  "Invalid float: no digits");

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
                // skip json_read, may need ch for next parse
                continue;

            case parse_state::frac_digit0:
                if(std::isdigit(ch))
                {
                    --fpart_exp;
                    combine_int_digit(fpart, ch);
                    state = parse_state::frac_digits;
                    break;
                }

                return json_error(/*ref*/ context,
                                  "Invalid float: expected float digit");

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
                // skip json_read, may need ch for next parse
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
                // skip json_read, may need ch for next parse
                continue;
        }

        // consume ch
        json_read(/*ref*/ context, /*ref*/ itr, end);
    }

    if (state == parse_state::float_end)
    {
        if(fpart != 0) value = static_cast<float>(fpart) * exp10(fpart_exp);
        if(ipart != 0) value += static_cast<float>(ipart);
        if(exp != 0) value *= exp10(eval_sign(exp, exp_sign));
        value = eval_sign(value, sign);
        return true;
    }

    return json_error(/*ref*/ context,
                      "Invalid float");
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
bool m1::parse_json_crc32(crc32 &value,
                          json_context &context,
                          InputItr &itr,
                          InputEnd end)
{
    return parse_json_string(utf8_crc32_iterator(value),
                             /*ref*/ context,
                             /*ref*/ itr,
                             end);
}

// ====================================================================================================================

template <typename OutputItr,
          typename InputItr,
          typename InputEnd>
bool m1::parse_json_string(OutputItr out,
                           json_context &context,
                           InputItr &itr,
                           InputEnd end)
{
    assert(!json_empty(context, itr, end));

    enum class parse_state
    {
        begin_quote,
        any_char,
        escaped_char,
        xdigit0,
        xdigit1,
        xdigit2,
        xdigit3,
    };

    int xdigit = 0u;
    parse_state state = parse_state::begin_quote;
    while(!json_empty(context, itr, end))
    {
        code_point const ch = json_read(/*ref*/ context, /*ref*/ itr, end);

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
                        return json_error(/*ref*/ context,
                                          "Invalid string: expected leading \"");
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
                        return true;
                    }

                    default:
                        *out++ = ch;
                        break;
                }

            case parse_state::escaped_char:
                switch(ch)
                {
                    case '\"':
                    case '\\':
                    case '/':
                        *out++ = ch;
                        state = parse_state::any_char;
                        break;

                    case 'b':
                        *out++ = '\b';
                        state = parse_state::any_char;
                        break;

                    case 'f':
                        *out++ = '\f';
                        state = parse_state::any_char;
                        break;

                    case 'n':
                        *out++ = '\n';
                        state = parse_state::any_char;
                        break;

                    case 't':
                        *out++ = '\t';
                        state = parse_state::any_char;
                        break;

                    case 'u':
                        xdigit = 0u;
                        state = parse_state::xdigit3;
                        break;

                    default:
                        // invalid escaped char
                        return json_error(/*ref*/ context,
                                          "Invalid string: invalid escaped char");
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
                            *out++ = static_cast<code_point>(xdigit);
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
                return json_error(/*ref*/ context,
                                  "Invalid string: expected hex digit for \u escape sequence");
        }
    }

    return json_error(/*ref*/ context,
                      "Invalid string");
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
/*static*/ void skip_space(m1::json_context &context,
                           InputItr &itr,
                           InputEnd end)
{
    while(!json_empty(context, itr, end))
    {
        // delay json_read until ch is known good
        code_point const ch = json_peek(/*ref*/ context, /*ref*/ itr, end);

        if(!std::isspace(ch))
        {
            break;
        }

        json_read(/*ref*/ context, /*ref*/ itr, end);
    }
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
// ====================================================================================================================

void force_compile()
{
    auto const f0 = &m1::parse_json_key_id<char*, char*>;
    auto const f1 = &m1::parse_json_key_name<char*, char*>;
    auto const f2 = &m1::parse_json_bool<char*, char*>;
    auto const f3 = &m1::parse_json_int<char*, char*>;
    auto const f4 = &m1::parse_json_float<char*, char*>;
    auto const f5 = &m1::parse_json_crc32<char*, char*>;
    auto const f6 = &m1::parse_json_ustring<char*, char*>;

    (void)(f0, f1, f2, f3, f4, f5, f6);
}

