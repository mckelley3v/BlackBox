#include "Flow/Input.hpp"
#include "Flow/FlowIO.hpp"
#include "Flow/Verify.hpp"
#include <utility>
#include <stdexcept>
#include <cassert>

// =====================================================================================================================

static bool is_input_connection_ptrs_valid(std::vector<m1::const_any_ptr> const &connection_ptrs);

// =====================================================================================================================

/*explicit*/ Flow::InputPortDefinition::InputPortDefinition(InputPortDefinitionInitializer definition_initializer)
    : PortName(IO::get_c_str(definition_initializer.PortName))
    , TypeName(IO::get_c_str(definition_initializer.TypeName))
    , IsOptional(definition_initializer.IsOptional)
    , IsMultiplex(definition_initializer.IsMultiplex)
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ Flow::InputPortDefinition::InputPortDefinition(IO::InputPortDefinition const * const definition_io_ptr)
    : PortName(FLOWIO_GET_STR_MEMBER(definition_io_ptr, PortName()))
    , TypeName(FLOWIO_GET_STR_MEMBER(definition_io_ptr, TypeName()))
    , IsOptional(FLOWIO_GET_BOOL_MEMBER(definition_io_ptr, IsOptional()) ? InputPortOptional::Yes : InputPortOptional::No)
    , IsMultiplex(FLOWIO_GET_BOOL_MEMBER(definition_io_ptr, IsMultiplex()) ? InputPortMultiplex::Yes : InputPortMultiplex::No)
{
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
