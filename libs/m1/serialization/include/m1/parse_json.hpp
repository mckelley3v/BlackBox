#ifndef M1_PARSE_JSON_HPP
#define M1_PARSE_JSON_HPP

namespace m1
{
    // =================================================================================================================

    // return true if [begin, end) is valid utf8 json text
//    bool parse_json(char const *begin,
//                    char const *end);

    // -----------------------------------------------------------------------------------------------------------------

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

    // return true if id is one of json_token_id::value_*
    bool is_json_value(json_token_id id);

    // -----------------------------------------------------------------------------------------------------------------

    struct json_token
    {
        json_token_id id;
        char const *begin;
        char const *end;
    };

    // -----------------------------------------------------------------------------------------------------------------

    // extract the next json token from [curr, end) and advance curr to the end of the token returned
    json_token parse_json_token(char const *&curr,
                                char const *end);

    // =================================================================================================================
} // namespace m1

#endif // M1_PARSE_JSON_HPP
