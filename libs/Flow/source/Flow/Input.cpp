#include "Flow/Input.hpp"
#include "Flow/Verify.hpp"
#include "m1/log.hpp"
#include "m1/iarchive_json.hpp"
#include "m1/iarchive_ubjson.hpp"
#include <utility>
#include <stdexcept>
#include <cassert>

// =====================================================================================================================

static bool is_input_connection_ptrs_valid(std::vector<m1::const_any_ptr> const &connection_ptrs);

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::InputPortOptional &value);
template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::InputPortMultiplex &value);
template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::InputPortDefinition &value);

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, InputPortOptional &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, InputPortOptional &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, InputPortMultiplex &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, InputPortMultiplex &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, InputPortDefinition &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, InputPortDefinition &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

Flow::InputPort::InputPort(InputPortDefinition definition,
                           InputPortInstance instance)
    : m_PortName(std::move(definition.PortName))
    , m_TypeName(std::move(definition.TypeName))
    , m_IsOptional(definition.IsOptional == InputPortOptional::Yes)
    , m_IsMultiplex(definition.IsMultiplex == InputPortMultiplex::Yes)
    , m_ConnectionPtrs(std::move(instance.ConnectionPtrs))
{
    FLOW_VERIFY(m_IsOptional || !m_ConnectionPtrs.empty(),
                std::runtime_error("InputPort is empty but non-optional"));
    FLOW_VERIFY(m_IsMultiplex || (m_ConnectionPtrs.size() <= 1),
                std::runtime_error("InputPort has multiple connection but non-multiplex"));
    FLOW_VERIFY(is_input_connection_ptrs_valid(m_ConnectionPtrs),
                std::runtime_error("InputPort has invalid connections"));
}

// ---------------------------------------------------------------------------------------------------------------------

std::string const& Flow::InputPort::GetPortName() const
{
    return m_PortName;
}

// ---------------------------------------------------------------------------------------------------------------------

std::string const& Flow::InputPort::GetTypeName() const
{
    return m_TypeName;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::InputPort::IsOptional() const
{
    return m_IsOptional;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::InputPort::IsMultiplex() const
{
    return m_IsMultiplex;
}

// ---------------------------------------------------------------------------------------------------------------------

std::vector<m1::const_any_ptr> const& Flow::InputPort::GetConnectionPtrs() const
{
    return m_ConnectionPtrs;
}

// =====================================================================================================================

/*static*/ bool is_input_connection_ptrs_valid(std::vector<m1::const_any_ptr> const &connection_ptrs)
{
    for(m1::const_any_ptr const &connection_ptr : connection_ptrs)
    {
        if(!connection_ptr)
        {
            return false;
        }
    }

    return true;
}

// =====================================================================================================================

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::InputPortOptional &value)
{
    using namespace Flow;

    bool bool_value = false;
    if(read_value(in, logger, bool_value))
    {
        value = bool_value ? InputPortOptional::Yes : InputPortOptional::No;
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::InputPortMultiplex &value)
{
    using namespace Flow;

    bool bool_value = false;
    if(read_value(in, logger, bool_value))
    {
        value = bool_value ? InputPortMultiplex::Yes : InputPortMultiplex::No;
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::InputPortDefinition &value)
{
    using namespace Flow;

    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("PortName"):
                result &= read_value(in, logger, value.PortName);
                break;

            case m1::property_id("TypeName"):
                result &= read_value(in, logger, value.TypeName);
                break;

            case m1::property_id("IsOptional"):
                result &= read_value(in, logger, value.IsOptional);
                break;

            case m1::property_id("IsMultiplex"):
                result &= read_value(in, logger, value.IsMultiplex);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                break;
        }
    }

    return result;
}

// =====================================================================================================================
