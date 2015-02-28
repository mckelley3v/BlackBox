#include "m1/iarchive_json.hpp"
#include "m1/parse_json.hpp"
#include "m1/eval_json.hpp"
#include "m1/log.hpp"
#include <ostream>
#include <cstring>
#include <cassert>

// =====================================================================================================================

/*explicit*/ m1::iarchive_json::iarchive_json(log &logger,
                                              char const *buffer)
    : iarchive_json(logger,
                    buffer,
                    buffer + std::strlen(buffer))
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::iarchive_json(log &logger,
                                 char const *buffer_begin,
                                 char const *buffer_end)
    : m_LoggerPtr(&logger)
    , m_Begin(buffer_begin)
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

m1::iarchive_json::property_ids m1::iarchive_json::get_property_ids()
{
    return property_ids(*this);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::array_indices m1::iarchive_json::get_array_indices()
{
    return array_indices(*this);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_property(property_id &id)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_property(*m_LoggerPtr, token, id));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_property(std::string &name)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_property(*m_LoggerPtr, token, name));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(bool &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_value(*m_LoggerPtr, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(int &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_value(*m_LoggerPtr, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(float &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_value(*m_LoggerPtr, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(crc32 &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_value(*m_LoggerPtr, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(std::string &value)
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(eval_json_value(*m_LoggerPtr, token, value));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::skip_value()
{
    json_token const token = parse_json_token(m_Current, m_End);
    return record_eval_state(is_json_value(*m_LoggerPtr, token));
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::record_eval_state(bool const state)
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

bool m1::read_property(iarchive_json &in, property_id &id)
{
    return in.read_property(id);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_property(iarchive_json &in, std::string &name)
{
    return in.read_property(name);
}

// =====================================================================================================================

bool m1::read_value(iarchive_json &in, bool &value)
{
    return in.read_value(value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, int &value)
{
    return in.read_value(value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, float &value)
{
    return in.read_value(value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, crc32 &value)
{
    return in.read_value(value);
}

// -----------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, std::string &value)
{
    return in.read_value(value);
}

// =====================================================================================================================

bool m1::skip_value(iarchive_json &in)
{
    return in.skip_value();
}

// =====================================================================================================================

