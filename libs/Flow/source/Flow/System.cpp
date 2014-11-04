#include "Flow/System.hpp"
#include "Flow/Verify.hpp"
#include "Flow/FlowIO.hpp"
#include <cassert>

// =====================================================================================================================

static std::vector<Flow::Component*> FilterActiveComponents(std::vector<std::unique_ptr<Flow::Component>> const &component_ptrs);

// =====================================================================================================================

Flow::IO::SystemDefinition const* Flow::IO::ParseSystemDefinitionBuffer(void const * const buffer_ptr,
                                                                        std::size_t const buffer_size,
                                                                        VerifyBuffer const verify_buffer /*= VerifyBuffer::Yes*/)
{
    using namespace Flow::IO;

    assert(buffer_ptr != nullptr);
    assert(buffer_size > 0);

    if (verify_buffer == VerifyBuffer::Yes)
    {
        flatbuffers::Verifier verifier(reinterpret_cast<std::uint8_t const*>(buffer_ptr), buffer_size);
        if(!VerifySystemDefinitionBuffer(verifier)) return nullptr;
    }

    return GetSystemDefinition(buffer_ptr);
}

// =====================================================================================================================

Flow::SystemComponentInstance::SystemComponentInstance(SystemComponentInstanceInitializer definition_initializer)
    : DefinitionName(IO::get_c_str(definition_initializer.DefinitionName))
    , InstanceName(IO::get_c_str(definition_initializer.InstanceName))
{
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::SystemComponentInstance::SystemComponentInstance(IO::SystemComponentInstance const * const definition_io_ptr)
    : DefinitionName(FLOWIO_GET_C_STR_MEMBER(definition_io_ptr, DefinitionName()))
    , InstanceName(FLOWIO_GET_C_STR_MEMBER(definition_io_ptr, InstanceName()))
{
}

// =====================================================================================================================

Flow::SystemConnectionPort::SystemConnectionPort(SystemConnectionPortInitializer definition_initializer)
    : ComponentInstanceName(IO::get_c_str(definition_initializer.ComponentInstanceName))
    , PortName(IO::get_c_str(definition_initializer.PortName))
{
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::SystemConnectionPort::SystemConnectionPort(IO::SystemConnectionPort const * const definition_io_ptr)
    : ComponentInstanceName(FLOWIO_GET_C_STR_MEMBER(definition_io_ptr, ComponentInstanceName()))
    , PortName(FLOWIO_GET_C_STR_MEMBER(definition_io_ptr, PortName()))
{
}

// =====================================================================================================================

Flow::SystemConnection::SystemConnection(SystemConnectionInitializer definition_initializer)
    : SourcePort(std::move(definition_initializer.SourcePort))
    , TargetPort(std::move(definition_initializer.TargetPort))
{
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::SystemConnection::SystemConnection(IO::SystemConnection const * const definition_io_ptr)
    : SourcePort(FLOWIO_GET_PTR_MEMBER(definition_io_ptr, SourcePort()))
    , TargetPort(FLOWIO_GET_PTR_MEMBER(definition_io_ptr, TargetPort()))
{
}

// =====================================================================================================================

Flow::SystemDefinition::SystemDefinition(SystemDefinitionInitializer definition_initializer)
    : Interface(std::move(definition_initializer.Interface))
    , ComponentInstances(definition_initializer.ComponentInstances.begin(),
                         definition_initializer.ComponentInstances.end())
    , Connections(definition_initializer.Connections.begin(),
                  definition_initializer.Connections.end())
{
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::SystemDefinition::SystemDefinition(IO::SystemDefinition const * const definition_io_ptr)
    : Interface(FLOWIO_GET_PTR_MEMBER(definition_io_ptr, Interface()))
    , ComponentInstances(IO::get_vector<SystemComponentInstance>(FLOWIO_GET_PTR_MEMBER(definition_io_ptr, ComponentInstances())))
    , Connections(IO::get_vector<SystemConnection>(FLOWIO_GET_PTR_MEMBER(definition_io_ptr, Connections())))
{
}

// =====================================================================================================================

/*static*/ char const * const Flow::System::In = "in:";
/*static*/ char const * const Flow::System::Out = "out:";

// ---------------------------------------------------------------------------------------------------------------------

Flow::System::System(TypeManager const &type_manager,
                     SystemDefinition definition,
                     SystemInstance instance)
    : SystemBase(type_manager,
                 definition,
                 instance.InputConnectionPtrsDict)
    , Component(type_manager,
                std::move(definition.Interface),
                ComponentInstance{std::move(instance.Name),
                                  std::move(instance.InputConnectionPtrsDict),
                                  std::move(SystemBase::OutputConnectionPtrDict())})
    , m_ActiveComponentPtrs(FilterActiveComponents(GetComponentPtrs()))
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ void Flow::System::Process() /*override*/
{
    for(Component *component_ptr : m_ActiveComponentPtrs)
    {
        component_ptr->Process();
    }
}

// =====================================================================================================================

/*static*/ std::vector<Flow::Component*> FilterActiveComponents(std::vector<std::unique_ptr<Flow::Component>> const &component_ptrs)
{
    using namespace Flow;

    std::vector<Component*> result;

    result.reserve(component_ptrs.size());
    for(std::unique_ptr<Component> const &component_ptr : component_ptrs)
    {
        if(component_ptr->GetAnnotations().Process != ComponentProcessAnnotation::Ignore)
        {
            result.push_back(component_ptr.get());
        }
    }

    return result;
}

// =====================================================================================================================
