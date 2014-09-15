#include "Flow/System.hpp"
#include "Flow/Verify.hpp"
#include "System_generated.h"
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
        flatbuffers::Verifier const verifier(reinterpret_cast<std::uint8_t const*>(buffer_ptr), buffer_size);
        if(!VerifySystemDefinitionBuffer(verifier)) return nullptr;
    }

    return GetSystemDefinition(buffer_ptr);
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

//Flow::System::System(TypeManager const &type_manager,
//                     IO::SystemDefinition const * const definition_ptr,
//                     SystemInstance instance)
//    : SystemBase(type_manager,
//                 definition_ptr,
//                 instance.InputConnectionPtrsDict)
//    , Component(type_manager,
//                definition_ptr ? definition_ptr->Interface() : nullptr,
//                ComponentInstance{std::move(instance.Name),
//                                  std::move(instance.InputConnectionPtrsDict),
//                                  std::move(SystemBase::OutputConnectionPtrDict())})
//    , m_ActiveComponentPtrs(FilterActiveComponents(GetComponentPtrs()))
//{
//}

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
