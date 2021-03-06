#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/Verify.hpp"

// =====================================================================================================================

static bool IsInputTypesValid(Flow::TypeManager const &type_manager,
                              Flow::ComponentInputPortDict const &input_port_dict);

// ---------------------------------------------------------------------------------------------------------------------

static bool IsOutputTypesValid(Flow::TypeManager const &type_manager,
                               Flow::ComponentOutputPortDict const &output_port_dict);

// ---------------------------------------------------------------------------------------------------------------------

template <typename InputPortDefinitionIterator>
static Flow::ComponentInputPortDict MakeInputPortDict(InputPortDefinitionIterator const input_port_definitions_begin,
                                                        InputPortDefinitionIterator const input_port_definitions_end,
                                                        Flow::ComponentInputConnectionPtrsDict &&input_ptrs_dict);

// ---------------------------------------------------------------------------------------------------------------------

template <typename OutputPortDefinitionIterator>
static Flow::ComponentOutputPortDict MakeOutputPortDict(OutputPortDefinitionIterator const output_port_definitions_begin,
                                                          OutputPortDefinitionIterator const output_port_definitions_end,
                                                          Flow::ComponentOutputConnectionPtrDict &&output_ptr_dict);

// =====================================================================================================================

Flow::Component::Component(TypeManager const &type_manager,
                           ComponentDefinition definition,
                           ComponentInstance instance)
    : m_DefinitionName(std::move(definition.Name))
    , m_Annotations(definition.Annotations)
    , m_InstanceName(std::move(instance.Name))
    , m_InputPortDict(MakeInputPortDict(definition.InputPorts.begin(),
                                        definition.InputPorts.end(),
                                        std::move(instance.InputConnectionPtrsDict)))
    , m_OutputPortDict(MakeOutputPortDict(definition.OutputPorts.begin(),
                                          definition.OutputPorts.end(),
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

Flow::ComponentInputPortDict& Flow::Component::InputPortDict()
{
    return m_InputPortDict;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentInputPortDict const& Flow::Component::GetInputPortDict() const
{
    return m_InputPortDict;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentOutputPortDict& Flow::Component::OutputPortDict()
{

    return m_OutputPortDict;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentOutputPortDict const& Flow::Component::GetOutputPortDict() const
{
    return m_OutputPortDict;
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ void Flow::Component::Process()
{
}

// =====================================================================================================================

/*static*/ bool IsInputTypesValid(Flow::TypeManager const &type_manager,
                                  Flow::ComponentInputPortDict const &input_port_dict)
{
    using namespace Flow;

    for(ComponentInputPortDict::value_type const &input_port_nvp : input_port_dict)
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
                                   Flow::ComponentOutputPortDict const &output_port_dict)
{
    using namespace Flow;

    for(ComponentOutputPortDict::value_type const &output_port_nvp : output_port_dict)
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

template <typename InputPortDefinitionIterator>
/*static*/ Flow::ComponentInputPortDict MakeInputPortDict(InputPortDefinitionIterator const input_port_definitions_begin,
                                                          InputPortDefinitionIterator const input_port_definitions_end,
                                                          Flow::ComponentInputConnectionPtrsDict &&input_ptrs_dict)
{
    using namespace Flow;

    ComponentInputPortDict result;

    for(InputPortDefinitionIterator input_port_definition_itr = input_port_definitions_begin;
                                    input_port_definition_itr != input_port_definitions_end;
                                  ++input_port_definition_itr)
    {
        auto &input_port_definition = *input_port_definition_itr;

        // copy name -- will be moved into result as key
        std::string input_port_name = input_port_definition.PortName;

        InputPortInstance input_port_instance = {std::move(input_ptrs_dict.at(input_port_name))};

        InputPort input_port(std::move(input_port_definition),
                             std::move(input_port_instance));

        result.emplace(std::move(input_port_name),
                       std::move(input_port));
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename OutputPortDefinitionIterator>
/*static*/ Flow::ComponentOutputPortDict MakeOutputPortDict(OutputPortDefinitionIterator const output_port_definitions_begin,
                                                            OutputPortDefinitionIterator const output_port_definitions_end,
                                                            Flow::ComponentOutputConnectionPtrDict &&output_ptr_dict)
{
    using namespace Flow;

    ComponentOutputPortDict result;

    for(OutputPortDefinitionIterator output_port_definition_itr = output_port_definitions_begin;
                                     output_port_definition_itr != output_port_definitions_end;
                                   ++output_port_definition_itr)
    {
        auto &output_port_definition = *output_port_definition_itr;

        // copy name -- will be moved into result as key
        std::string output_port_name = output_port_definition.PortName;

        OutputPortInstance output_port_instance = {std::move(output_ptr_dict.at(output_port_name))};

        OutputPort output_port(std::move(output_port_definition),
                               std::move(output_port_instance));

        result.emplace(std::move(output_port_name),
                       std::move(output_port));
    }

    return result;
}

// =====================================================================================================================
