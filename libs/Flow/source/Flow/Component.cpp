#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/Verify.hpp"

// =====================================================================================================================

static bool IsInputTypesValid(Flow::TypeManager const &type_manager,
                              Flow::Component::InputPortDict const &input_port_dict);

static bool IsOutputTypesValid(Flow::TypeManager const &type_manager,
                               Flow::Component::OutputPortDict const &output_port_dict);

static Flow::Component::InputPortDict MakeInputPortDict(std::initializer_list<Flow::InputPortDefinition> input_port_definitions,
                                                        Flow::ComponentInputConnectionPtrsDict &&input_ptrs_dict);

static Flow::Component::OutputPortDict MakeOutputPortDict(std::initializer_list<Flow::OutputPortDefinition> output_port_definitions,
                                                          Flow::ComponentOutputConnectionPtrDict &&output_ptr_dict);

// =====================================================================================================================

Flow::Component::Component(TypeManager const &type_manager,
                           ComponentDefinition definition,
                           ComponentInstance instance)
    : m_DefinitionName(definition.Name)
    , m_Annotations(definition.Annotations)
    , m_InstanceName(std::move(instance.Name))
    , m_InputPortDict(MakeInputPortDict(definition.InputPorts,
                                        std::move(instance.InputConnectionPtrsDict)))
    , m_OutputPortDict(MakeOutputPortDict(definition.OutputPorts,
                                          std::move(instance.OutputConnectionPtrDict)))
{
    FLOW_VERIFY(type_manager.FindComponentDefinition(GetDefinitionName()) != nullptr,
                std::runtime_error("Invalid component definition"));

    FLOW_VERIFY(IsInputTypesValid(type_manager, GetInputPortDict()),
                std::runtime_error("Invalid input type found"));

    FLOW_VERIFY(IsOutputTypesValid(type_manager, GetOutputPortDict()),
                std::runtime_error("Invalid output type found"));
}

// ---------------------------------------------------------------------------------------------------------------------

std::string const& Flow::Component::GetDefinitionName() const
{
    return m_DefinitionName;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentAnnotations const& Flow::Component::GetAnnotations() const
{
    return m_Annotations;
}

// ---------------------------------------------------------------------------------------------------------------------

std::string const& Flow::Component::GetInstanceName() const
{
    return m_InstanceName;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::Component::InputPortDict const& Flow::Component::GetInputPortDict() const
{
    return m_InputPortDict;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::Component::OutputPortDict const& Flow::Component::GetOutputPortDict() const
{
    return m_OutputPortDict;
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ void Flow::Component::Process()
{
}

// =====================================================================================================================

/*static*/ bool IsInputTypesValid(Flow::TypeManager const &type_manager,
                                  Flow::Component::InputPortDict const &input_port_dict)
{
    using namespace Flow;

    for(Component::InputPortDict::value_type const &input_port_nvp : input_port_dict)
    {
        InputPort const &input_port = input_port_nvp.second;
        if(!type_manager.IsConnectionValid(input_port.GetTypeName(), input_port.GetTypeName()))
        {
            return false;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ bool IsOutputTypesValid(Flow::TypeManager const &type_manager,
                                   Flow::Component::OutputPortDict const &output_port_dict)
{
    using namespace Flow;

    for(Component::OutputPortDict::value_type const &output_port_nvp : output_port_dict)
    {
        OutputPort const &output_port = output_port_nvp.second;
        if(!type_manager.IsConnectionValid(output_port.GetTypeName(), output_port.GetTypeName()))
        {
            return false;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ Flow::Component::InputPortDict MakeInputPortDict(std::initializer_list<Flow::InputPortDefinition> input_port_definitions,
                                                            Flow::ComponentInputConnectionPtrsDict &&input_ptrs_dict)
{
    using namespace Flow;

    Component::InputPortDict result;

    for(InputPortDefinition const &input_port_definition : input_port_definitions)
    {
        std::string input_port_name = input_port_definition.PortName;
        InputPortInstance input_port_instance = {std::move(input_ptrs_dict.at(input_port_name))};

        FLOW_VERIFY((input_port_definition.IsOptional == InputPortOptional::Yes) || (!input_port_instance.ConnectionPtrs.empty()),
                    std::runtime_error("Only optional ports may have zero connections"));

        FLOW_VERIFY((input_port_definition.IsMultiplex == InputPortMultiplex::No) || (input_port_instance.ConnectionPtrs.size() <= 1),
                    std::runtime_error("Only multiplex ports may have multiple connections"));

        InputPort input_port(input_port_definition,
                             std::move(input_port_instance));
        result.emplace(std::move(input_port_name),
                       std::move(input_port));
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ Flow::Component::OutputPortDict MakeOutputPortDict(std::initializer_list<Flow::OutputPortDefinition> output_port_definitions,
                                                              Flow::ComponentOutputConnectionPtrDict &&output_ptr_dict)
{
    using namespace Flow;

    Component::OutputPortDict result;

    for(OutputPortDefinition const &output_port_definition : output_port_definitions)
    {
        std::string output_port_name = output_port_definition.PortName;
        OutputPortInstance output_port_instance = {std::move(output_ptr_dict.at(output_port_name))};

        FLOW_VERIFY(output_port_instance.ConnectionPtr != nullptr,
                    std::runtime_error("Output ports must have connection"));

        OutputPort output_port(output_port_definition,
                               std::move(output_port_instance));
        result.emplace(std::move(output_port_name),
                       std::move(output_port));
    }

    return result;
}

// =====================================================================================================================
