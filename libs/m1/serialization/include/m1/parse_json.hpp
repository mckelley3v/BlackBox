#ifndef M1_PARSE_JSON_HPP
#define M1_PARSE_JSON_HPP

namespace m1
{
    // =================================================================================================================

    enum class json_token_id
    {
        invalid,
        object_begin,   // {
        object_end,     // }
        array_begin,    // [
        array_end,      // ]
        separator,      // ,
        property,       // "as\tdf":
        value_null,     // null
        value_true,     // true
        value_false,    // false
        value_int,      // -123
        value_float,    // -12.3, 12e-3
        value_string,   // "as\tdf"
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool is_json_value(json_token_id id);

    // -----------------------------------------------------------------------------------------------------------------

    struct json_token
    {
        json_token_id id;
        char const *begin;
        char const *end;
    };

    // -----------------------------------------------------------------------------------------------------------------

    json_token parse_json_token(char const *&curr,
                                char const *end);

    // =================================================================================================================
} // namespace m1

#endif // M1_PARSE_JSON_HPP
