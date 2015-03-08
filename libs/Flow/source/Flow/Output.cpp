#include "Flow/Output.hpp"
#include "Flow/Verify.hpp"
#include "m1/log.hpp"
#include "m1/iarchive_json.hpp"
#include "m1/iarchive_ubjson.hpp"
#include <utility>
#include <stdexcept>
#include <cassert>

// =====================================================================================================================

template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::OutputPortDefinition &value);

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, OutputPortDefinition &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, OutputPortDefinition &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

Flow::OutputPort::OutputPort(OutputPortDefinition definition,
                             OutputPortInstance instance)
    : m_PortName(std::move(definition.PortName))
    , m_TypeName(std::move(definition.TypeName))
    , m_ConnectionPtr(std::move(instance.ConnectionPtr))
{
    FLOW_VERIFY(m_ConnectionPtr,
                std::runtime_error("Invalid connection"));
}

// ---------------------------------------------------------------------------------------------------------------------

std::string const& Flow::OutputPort::GetPortName() const
{
    return m_PortName;
}

// ---------------------------------------------------------------------------------------------------------------------

std::string const& Flow::OutputPort::GetTypeName() const
{
    return m_TypeName;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::any_ptr const& Flow::OutputPort::GetConnectionPtr() const
{
    return m_ConnectionPtr;
}

// =====================================================================================================================

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::OutputPortDefinition &value)
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

            default:
                M1_WARN(logger, "Unknown property");
                break;
        }
    }

    return result;
}

// =====================================================================================================================
