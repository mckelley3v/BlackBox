#include "Flow/System.hpp"
#include "Flow/Verify.hpp"
#include "m1/log.hpp"
#include "m1/iarchive_json.hpp"
#include "m1/iarchive_ubjson.hpp"
#include <cassert>

// =====================================================================================================================

static std::vector<Flow::Component*> FilterActiveComponents(std::vector<std::unique_ptr<Flow::Component>> const &component_ptrs);

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::SystemComponentInstance &value);
template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::SystemConnectionPort &value);
template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::SystemConnection &value);
template <typename IArchive> static bool read_value(IArchive &in, m1::log &logger, Flow::SystemDefinition &value);

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, SystemComponentInstance &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemComponentInstance &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, SystemConnectionPort &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemConnectionPort &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, SystemConnection &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemConnection &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, m1::log &logger, SystemDefinition &value)
{
    return ::read_value<m1::iarchive_json>(in, logger, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemDefinition &value)
{
    return false;
    //return ::read_value<m1::iarchive_ubjson>(in, logger, value);
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

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::SystemComponentInstance &value)
{
    using namespace Flow;
    using Flow::read_value;

    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("DefinitionName"):
                result &= read_value(in, logger, value.DefinitionName);
                break;

            case m1::property_id("InstanceName"):
                result &= read_value(in, logger, value.InstanceName);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                break;
        }
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::SystemConnectionPort &value)
{
    using namespace Flow;
    using Flow::read_value;

    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("ComponentInstanceName"):
                result &= read_value(in, logger, value.ComponentInstanceName);
                break;

            case m1::property_id("PortName"):
                result &= read_value(in, logger, value.PortName);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                break;
        }
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::SystemConnection &value)
{
    using namespace Flow;
    using Flow::read_value;

    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("SourcePort"):
                result &= read_value(in, logger, value.SourcePort);
                break;

            case m1::property_id("TargetPort"):
                result &= read_value(in, logger, value.TargetPort);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                break;
        }
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, m1::log &logger, Flow::SystemDefinition &value)
{
    using namespace Flow;
    using Flow::read_value;

    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("Interface"):
                result &= read_value(in, logger, value.Interface);
                break;

            case m1::property_id("ComponentInstances"):
                result &= read_value(in, logger, value.ComponentInstances);
                break;

            case m1::property_id("Connections"):
                result &= read_value(in, logger, value.Connections);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                break;
        }
    }

    return result;
}

// =====================================================================================================================
