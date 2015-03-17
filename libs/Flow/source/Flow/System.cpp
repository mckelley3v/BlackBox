#include "Flow/System.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/Verify.hpp"
#include <cassert>

// =====================================================================================================================

static std::vector<Flow::Component*> FilterActiveComponents(std::vector<std::unique_ptr<Flow::Component>> const &component_ptrs);

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
    , m_ProcessCount(0)
    , m_ActiveComponentPtrs(FilterActiveComponents(GetComponentPtrs()))
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ void Flow::System::Process() /*override*/
{
    for(Component * const component_ptr : m_ActiveComponentPtrs)
    {
        component_ptr->Process();
    }

    if(m_ProcessCount == 0)
    {
        // remove any components designated to run only once
        m_ActiveComponentPtrs.erase(std::remove_if(m_ActiveComponentPtrs.begin(),
                                                   m_ActiveComponentPtrs.end(),
                                                   [](Component const * const p)
                                                   {
                                                       return p->GetAnnotations().Process == ComponentProcessAnnotation::Once;
                                                   }),
                                    m_ActiveComponentPtrs.end());
    }

    ++m_ProcessCount;
}

// =====================================================================================================================

/*static*/ std::vector<Flow::Component*> FilterActiveComponents(std::vector<std::unique_ptr<Flow::Component>> const &component_ptrs)
{
    using namespace Flow;

    std::vector<Component*> result;

    result.reserve(component_ptrs.size());
    for(std::unique_ptr<Component> const &component_ptr : component_ptrs)
    {
        if(component_ptr->GetAnnotations().Process != ComponentProcessAnnotation::Never)
        {
            result.push_back(component_ptr.get());
        }
    }

    return result;
}

// =====================================================================================================================
