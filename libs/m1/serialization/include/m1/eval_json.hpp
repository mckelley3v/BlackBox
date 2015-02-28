#ifndef M1_EVAL_JSON_HPP
#define M1_EVAL_JSON_HPP

#include <string>
#include <cstdint>

namespace m1
{
    // =================================================================================================================

    class log;
    class crc32;
    struct json_token;

    // =================================================================================================================

    bool eval_json_property(log &logger, json_token const &token, crc32 &id);
    bool eval_json_property(log &logger, json_token const &token, std::string &name);

    // -----------------------------------------------------------------------------------------------------------------

    bool is_json_value(log &logger, json_token const &token);

    // -----------------------------------------------------------------------------------------------------------------

    bool eval_json_value(log &logger, json_token const &token, bool &value);
    bool eval_json_value(log &logger, json_token const &token, int &value);
    bool eval_json_value(log &logger, json_token const &token, float &value);
    bool eval_json_value(log &logger, json_token const &token, crc32 &value);
    bool eval_json_value(log &logger, json_token const &token, std::string &value);

    // =================================================================================================================
} // namespace m1

#endif // M1_EVAL_JSON_HPP
