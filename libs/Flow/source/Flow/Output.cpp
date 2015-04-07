#include "Flow/Output.hpp"
#include "Flow/Verify.hpp"
#include <utility>
#include <stdexcept>
#include <cassert>

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

m1::any_ptr& Flow::OutputPort::ConnectionPtr()
{
    return m_ConnectionPtr;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::any_ptr const& Flow::OutputPort::GetConnectionPtr() const
{
    return m_ConnectionPtr;
}

// =====================================================================================================================
