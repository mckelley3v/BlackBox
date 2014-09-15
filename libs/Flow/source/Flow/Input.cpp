#include "Flow/Input.hpp"
#include <utility>
#include <cassert>

// =====================================================================================================================

static bool is_input_connection_ptrs_valid(std::vector<m1::const_any_ptr> const &connection_ptrs);

// =====================================================================================================================

Flow::InputPort::InputPort(InputPortDefinition definition,
                           InputPortInstance instance)
    : m_PortName(definition.PortName)
    , m_TypeName(definition.TypeName)
    , m_IsOptional(definition.IsOptional == InputPortOptional::Yes)
    , m_IsMultiplex(definition.IsMultiplex == InputPortMultiplex::Yes)
    , m_ConnectionPtrs(std::move(instance.ConnectionPtrs))
{
    assert(m_IsOptional || !m_ConnectionPtrs.empty());
    assert(m_IsMultiplex || (m_ConnectionPtrs.size() <= 1));
    assert(is_input_connection_ptrs_valid(m_ConnectionPtrs));
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
