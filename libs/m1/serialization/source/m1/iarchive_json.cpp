#include "m1/iarchive_json.hpp"
#include "m1/parse_json.hpp"
#include "m1/eval_json.hpp"
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
    , m_State()
    , m_Begin(buffer_begin)
    , m_End(buffer_end)
    , m_Current(m_Begin)
{
    assert(m_Begin != nullptr);
    assert(m_End != nullptr);
    assert(m_Begin <= m_End);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::log& m1::iarchive_json::logger()
{
    return *m_LoggerPtr;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_state m1::iarchive_json::get_state() const
{
    return m_State;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::set_error_state()
{
    set_state(iarchive_state::error);
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
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_property(logger(), token, id))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_property(std::string &name)
{
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_property(logger(), token, name))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(bool &value)
{
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_value(logger(), token, value))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(int &value)
{
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_value(logger(), token, value))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(float &value)
{
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_value(logger(), token, value))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(crc32 &value)
{
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_value(logger(), token, value))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::read_value(std::string &value)
{
    if(sentry const s{*this})
    {
        json_token const token = parse_json_token(m_Current, m_End);
        if(eval_json_value(logger(), token, value))
        {
            return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::iarchive_json::skip_value()
{
    if(sentry const s{*this})
    {
        char const * const prev = m_Current;
        json_token const token = parse_json_token(m_Current, m_End);
        switch(token.id)
        {
            case json_token_id::object_begin:
            {
                // backup for property iterator
                m_Current = prev;

                bool result = true;
                for(m1::property_id const &id : get_property_ids())
                {
                    result &= skip_value();
                }
                return result;
            }

            case json_token_id::array_begin:
            {
                // backup for array iterator
                m_Current = prev;

                bool result = true;
                for(int const array_index : get_array_indices())
                {
                    result &= skip_value();
                }
                return result;
            }

            default:
            {
                if(is_json_value(logger(), token))
                {
                    return true;
                }

                return false;
            }
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::iarchive_json::set_state(iarchive_state state)
{
    m_State = state;
}

// =====================================================================================================================

bool m1::read_property(iarchive_json &in, property_id &id)
{
    return in.read_property(id);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::read_property(iarchive_json &in, std::string &name)
{
    return in.read_property(name);
}

// =====================================================================================================================

bool m1::read_value(iarchive_json &in, bool &value)
{
    return in.read_value(value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, int &value)
{
    return in.read_value(value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, float &value)
{
    return in.read_value(value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::read_value(iarchive_json &in, crc32 &value)
{
    return in.read_value(value);
}

// ---------------------------------------------------------------------------------------------------------------------

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

/*explicit*/ m1::iarchive_json::sentry::sentry(iarchive_json &in)
    : m_ArchivePtr(&in)
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::iarchive_json::sentry::operator bool() const
{
    if(m_ArchivePtr->get_state() != iarchive_state::valid)
    {
        m_ArchivePtr->set_state(iarchive_state::error);
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::iarchive_json::sentry::~sentry()
{
    if(m_ArchivePtr->get_state() != iarchive_state::error)
    {
        if(m_ArchivePtr->m_Current == m_ArchivePtr->m_End)
        {
            m_ArchivePtr->set_state(iarchive_state::end);
        }
    }
}

// =====================================================================================================================

