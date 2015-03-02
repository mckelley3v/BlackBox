#include "m1/iarchive_json.hpp"
#include "m1/parse_json.hpp"
#include "m1/eval_json.hpp"
#include <cstring>
#include <cassert>

// =====================================================================================================================

/*explicit*/ m1::iarchive_json::iarchive_json(char const *buffer)
    : iarchive_json(buffer,
                    buffer + std::strlen(buffer))
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::iarchive_json(char const *buffer_begin,
                                 char const *buffer_end)
    : m_Begin(buffer_begin)
    , m_End(buffer_end)
    , m_Current(m_Begin)
{
    assert(m_Begin != nullptr);
    assert(m_End != nullptr);
    assert(m_Begin <= m_End);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::operator ! () const
{
    return m_Current == m_End;
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::iarchive_json::operator bool () const
{
    return !!(*this);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::property_ids m1::iarchive_json::get_property_ids(log &logger)
{
    return property_ids(*this, logger);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices m1::iarchive_json::get_array_indices(log &logger)
{
    return array_indices(*this, logger);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_property(log &logger, property_id &id)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_property(logger, token, id));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_property(log &logger, std::string &name)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_property(logger, token, name));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(log &logger, bool &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_value(logger, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(log &logger, int &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_value(logger, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(log &logger, float &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_value(logger, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(log &logger, crc32 &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_value(logger, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(log &logger, std::string &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(eval_json_value(logger, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::skip_value(log &logger)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return set_error_state(is_json_value(logger, token));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::set_error_state(bool const state)
{
    if(!state)
    {
        set_error_state();
    }

    return state;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::set_error_state()
{
    m_Current = m_End;
}

// =====================================================================================================================

bool m1::read_property(iarchive_json &in, log &logger, property_id &id)
{
    return in.read_property(logger, id);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_property(iarchive_json &in, log &logger, std::string &name)
{
    return in.read_property(logger, name);
}

// =====================================================================================================================

bool m1::read_value(iarchive_json &in, log &logger, bool &value)
{
    return in.read_value(logger, value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, log &logger, int &value)
{
    return in.read_value(logger, value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, log &logger, float &value)
{
    return in.read_value(logger, value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, log &logger, crc32 &value)
{
    return in.read_value(logger, value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, log &logger, std::string &value)
{
    return in.read_value(logger, value);
}

// =====================================================================================================================

bool m1::skip_value(iarchive_json &in, log &logger)
{
    return in.skip_value(logger);
}

// =====================================================================================================================

