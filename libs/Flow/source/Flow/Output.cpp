#include "Flow/Output.hpp"
#include <utility>
#include <cassert>

// =====================================================================================================================

Flow::OutputPort::OutputPort(OutputPortDefinition definition,
                             OutputPortInstance instance)
    : m_PortName(definition.PortName)
    , m_TypeName(definition.TypeName)
    , m_ConnectionPtr(std::move(instance.ConnectionPtr))
{
    assert(m_ConnectionPtr);
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
