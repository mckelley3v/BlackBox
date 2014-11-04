#include "Flow/System.hpp"
#include "Flow/SystemGraph.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/Verify.hpp"
#include "m1/dictionary.hpp"
#include <stdexcept>
#include <cassert>

// =====================================================================================================================

namespace
{
    using ComponentPtrs = std::vector<std::unique_ptr<Flow::Component>>;
    using ComponentDefinitionPtrDict = m1::dictionary<Flow::ComponentDefinition const*>;
} // namespace

// =====================================================================================================================

// construct components in topological order, gathering inputs from dependencies
static ComponentPtrs MakeSystemComponents(Flow::TypeManager const &type_manager,
                                          Flow::SystemDefinition const &definition,
                                          Flow::ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict);

// ---------------------------------------------------------------------------------------------------------------------

// create a dictionary from each component's instance name to the component's definition
// note: includes an entry for System::In and System::Out
static ComponentDefinitionPtrDict MakeComponentInstanceDefinitionPtrDict(Flow::TypeManager const &type_manager,
                                                                         Flow::SystemDefinition const &definition);

// ---------------------------------------------------------------------------------------------------------------------

// gather all the inputs for node from available_inputs into a single dictionary
// to be passed to the node's MakeInstanceFunc
static Flow::ComponentInputConnectionPtrsDict ResolveNodeInputs(Flow::TypeManager const &type_manager,
                                                                Flow::SystemNode const &node,
                                                                ComponentDefinitionPtrDict const &component_instance_definition_ptr_dict,
                                                                m1::dictionary<Flow::ComponentInputConnectionPtrsDict> const &available_inputs_dict);

// ---------------------------------------------------------------------------------------------------------------------

// search a component's definition for an input port with the given name, return that port's type name
static char const* FindInputPortTypeName(Flow::ComponentDefinition const * const node_definition_ptr,
                                         std::string const &port_name);

// ---------------------------------------------------------------------------------------------------------------------

// search a component's definition for an output port with the given name, return that port's type name
static char const* FindOutputPortTypeName(Flow::ComponentDefinition const * const node_definition_ptr,
                                          std::string const &port_name);

// ---------------------------------------------------------------------------------------------------------------------

// construct corresponding inputs for each output so component's outputs can be easily found and connected
static Flow::ComponentInputConnectionPtrsDict MirrorComponentOutputs(Flow::Component::OutputPortDict const &output_port_dict);

// ---------------------------------------------------------------------------------------------------------------------

// construct dictionary of system outputs to initialize System's base Component with
static Flow::ComponentOutputConnectionPtrDict MakeSystemOutputDict(Flow::SystemDefinition const &definition,
                                                                   ComponentPtrs const &component_ptrs);

// =====================================================================================================================

Flow::SystemBase::SystemBase(TypeManager const &type_manager,
                             SystemDefinition const &definition,
                             ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict)
    : m_ComponentPtrs(MakeSystemComponents(type_manager, definition, input_connection_ptrs_dict))
    , m_OutputConnectionPtrDict(MakeSystemOutputDict(definition, m_ComponentPtrs))
{
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::SystemBase::ComponentPtrs const& Flow::SystemBase::GetComponentPtrs() const
{
    return m_ComponentPtrs;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentOutputConnectionPtrDict& Flow::SystemBase::OutputConnectionPtrDict()
{
    return m_OutputConnectionPtrDict;
}

// =====================================================================================================================

ComponentPtrs MakeSystemComponents(Flow::TypeManager const &type_manager,
                                   Flow::SystemDefinition const &definition,
                                   Flow::ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict)
{
    using namespace Flow;

    std::vector<std::unique_ptr<Component>> result;
    result.reserve(definition.ComponentInstances.size());

    // create graph of node definitions and connections between them
    SystemGraph const system_graph = MakeSystemGraph(definition,
                                                     input_connection_ptrs_dict);

    // topographically sort nodes
    std::vector<SystemNode const*> const sorted_node_ptrs = SortSystemGraph(system_graph);
    assert(sorted_node_ptrs.size() == definition.ComponentInstances.size());

    // dictionary from component instance name to input connection dictionary created from the component's outputs
    // note: adds a special entry for System::In
    m1::dictionary<ComponentInputConnectionPtrsDict> available_inputs_dict;
    //available_inputs_dict.reserve(sorted_node_ptrs.size() + 1);
    available_inputs_dict[System::In] = input_connection_ptrs_dict;

    // dictionary from component instance name to definition ptr
    // used to validate connection type safety
    ComponentDefinitionPtrDict const component_instance_definition_ptr_dict = MakeComponentInstanceDefinitionPtrDict(type_manager, definition);

    // construct components in topological order
    // gather available inputs/outputs as new components are added
    for(SystemNode const *node_ptr : sorted_node_ptrs)
    {
        assert(node_ptr != nullptr);
        assert(node_ptr->InstancePtr != nullptr);
        assert(!node_ptr->InstancePtr->InstanceName.empty());
        FLOW_VERIFY(node_ptr->InstancePtr->InstanceName != System::In,
                    std::runtime_error("Component name must not be a reserved name"));
        FLOW_VERIFY(node_ptr->InstancePtr->InstanceName != System::Out,
                    std::runtime_error("Component name must not be a reserved name"));

        SystemNode const &node = *node_ptr;
        std::string const &node_instance_name = node.InstancePtr->InstanceName;

        FLOW_VERIFY(available_inputs_dict.find(node_instance_name) == available_inputs_dict.end(),
                    std::runtime_error("Duplicate component name detected"));

        // gather inputs to create component for this node (topological sort should insure they are available)
        ComponentInputConnectionPtrsDict node_input_connection_ptrs_dict = ResolveNodeInputs(type_manager,
                                                                                             node,
                                                                                             component_instance_definition_ptr_dict,
                                                                                             available_inputs_dict);

        // create node
        std::string const &node_definition_name = node.InstancePtr->DefinitionName;
        std::unique_ptr<Component> node_component_ptr = type_manager.MakeSystemComponent(node_definition_name,
                                                                                         node_instance_name,
                                                                                         std::move(node_input_connection_ptrs_dict));
        FLOW_VERIFY(node_component_ptr != nullptr,
                    std::runtime_error("Unable to create component"));

        // for each output port, add to available_inputs_dict
        available_inputs_dict.emplace(std::piecewise_construct,
                                      std::forward_as_tuple(node_instance_name),
                                      std::forward_as_tuple(MirrorComponentOutputs(node_component_ptr->GetOutputPortDict())));

        result.push_back(std::move(node_component_ptr));
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

ComponentDefinitionPtrDict MakeComponentInstanceDefinitionPtrDict(Flow::TypeManager const &type_manager,
                                                                  Flow::SystemDefinition const &definition)
{
    using namespace Flow;

    ComponentDefinitionPtrDict result;
    //result.reserve(definition.ComponentInstances.size() + 2);

    ComponentDefinition const * const system_definition_ptr = type_manager.FindComponentDefinition(definition.Interface.Name);
    result[System::In] = system_definition_ptr;
    result[System::Out] = system_definition_ptr;

    for(SystemComponentInstance const &component_instance : definition.ComponentInstances)
    {
        assert(!component_instance.DefinitionName.empty());
        assert(!component_instance.InstanceName.empty());
        result[component_instance.InstanceName] = type_manager.FindComponentDefinition(component_instance.DefinitionName);
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentInputConnectionPtrsDict ResolveNodeInputs(Flow::TypeManager const &type_manager,
                                                         Flow::SystemNode const &node,
                                                         ComponentDefinitionPtrDict const &component_instance_definition_ptr_dict,
                                                         m1::dictionary<Flow::ComponentInputConnectionPtrsDict> const &available_inputs_dict)
{
    using namespace Flow;

    std::string const &node_instance_name = node.InstancePtr->InstanceName;
    ComponentDefinition const * const node_definition_ptr = component_instance_definition_ptr_dict.at(node_instance_name);
    FLOW_VERIFY(node_definition_ptr != nullptr,
                std::runtime_error("Invalid definition name for component"));

    ComponentInputConnectionPtrsDict result;
    //result.reserve(node.InputEdgePtrs.size());

    // for each node source edge
    //   look up source component/port in available_inputs
    //   append to result at connected slot name
    for(SystemEdge const * const input_edge_ptr : node.InputEdgePtrs)
    {
        assert(input_edge_ptr != nullptr);
        SystemEdge const &input_edge = *input_edge_ptr;

        // get port name input is connected to
        assert(input_edge.ConnectionPtr != nullptr);
        assert(input_edge.ConnectionPtr->TargetPort.ComponentInstanceName == node_instance_name);
        std::string const &target_component_port_name = input_edge.ConnectionPtr->TargetPort.PortName;
        char const * const target_component_port_type_name = FindInputPortTypeName(node_definition_ptr, target_component_port_name);
        assert(target_component_port_type_name != nullptr);

        // get component and port name input is connected from
        assert(node.InstancePtr != nullptr);
        std::string const &source_component_instance_name = input_edge.ConnectionPtr->SourcePort.ComponentInstanceName;
        std::string const &source_component_port_name = input_edge.ConnectionPtr->SourcePort.PortName;

        ComponentDefinition const * const source_component_definition_ptr = component_instance_definition_ptr_dict.at(source_component_instance_name);
        char const * const source_component_port_type_name = FindOutputPortTypeName(source_component_definition_ptr, source_component_port_name);
        assert(source_component_port_type_name != nullptr);

        // verify that connection is between valid types
        FLOW_VERIFY(type_manager.IsConnectionValid(source_component_port_type_name, target_component_port_type_name),
                    std::runtime_error("Invalid connection specified for port input/output types"));

        // find port dictionary for input component (must exist)
        ComponentInputConnectionPtrsDict const &input_component_dict = available_inputs_dict.at(source_component_instance_name);

        // find port (must exist)
        std::vector<m1::const_any_ptr> const &input_port_ptrs = input_component_dict.at(source_component_port_name);

        // copy port's connection ptrs
        std::vector<m1::const_any_ptr> &result_port_ptrs = result[target_component_port_name];
        result_port_ptrs.insert(result_port_ptrs.end(),
                                input_port_ptrs.begin(),
                                input_port_ptrs.end());
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

char const* FindInputPortTypeName(Flow::ComponentDefinition const * const node_definition_ptr,
                                  std::string const &port_name)
{
    using namespace Flow;

    for(InputPortDefinition const &input_port : node_definition_ptr->InputPorts)
    {
        if(input_port.PortName == port_name)
        {
            return input_port.TypeName.c_str();
        }
    }

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

char const* FindOutputPortTypeName(Flow::ComponentDefinition const * const node_definition_ptr,
                                   std::string const &port_name)
{
    using namespace Flow;

    for(OutputPortDefinition const &output_port : node_definition_ptr->OutputPorts)
    {
        if(output_port.PortName == port_name)
        {
            return output_port.TypeName.c_str();
        }
    }

    return nullptr;
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::ComponentInputConnectionPtrsDict MirrorComponentOutputs(Flow::Component::OutputPortDict const &output_port_dict)
{
    using namespace Flow;

    // for each output, copy connection as input
    ComponentInputConnectionPtrsDict result;
    //result.reserve(output_port_dict.size());
    for(Component::OutputPortDict::value_type const &output_port_nvp : output_port_dict)
    {
        OutputPort const &node_component_output_port = output_port_nvp.second;

        FLOW_VERIFY(result.find(node_component_output_port.GetPortName()) == result.end(),
                    std::runtime_error("Duplicate component output port detected"));
        result[node_component_output_port.GetPortName()].push_back(node_component_output_port.GetConnectionPtr());
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ Flow::ComponentOutputConnectionPtrDict MakeSystemOutputDict(Flow::SystemDefinition const &definition,
                                                                       ComponentPtrs const &component_ptrs)
{
    using namespace Flow;

    // first index all the nodes by name so this isn't a O(N^2) algorithm
    // TODO - consider if this can this be constructed in MakeSystemComponents
    m1::dictionary<Component const*> component_ptr_dict;
    //component_ptr_dict.reserve(component_ptrs.size());
    for(std::unique_ptr<Component> const &component_ptr : component_ptrs)
    {
        assert(component_ptr != nullptr);
        component_ptr_dict[component_ptr->GetInstanceName()] = component_ptr.get();
    }

    ComponentOutputConnectionPtrDict result;
    //result.reserve(definition.Interface.OutputPorts.size());

    // for each connection to System::Out
    //   copy the pointer that is assigned to connect to it
    for(SystemConnection const &connection : definition.Connections)
    {
        std::string const &target_component_instance_name = connection.TargetPort.ComponentInstanceName;
        assert(!target_component_instance_name.empty());
        if(target_component_instance_name == System::Out)
        {
            std::string const &target_component_port_name = connection.TargetPort.PortName;
            assert(!target_component_port_name.empty());

            std::string const &source_component_instance_name = connection.SourcePort.ComponentInstanceName;
            assert(!source_component_instance_name.empty());

            std::string const &source_component_port_name = connection.SourcePort.PortName;
            assert(!source_component_port_name.empty());

            Component const *source_component_ptr = component_ptr_dict.at(source_component_instance_name);
            assert(source_component_ptr != nullptr);

            OutputPort const &system_output_port = source_component_ptr->GetOutputPortDict().at(source_component_port_name);
            result[target_component_port_name] = system_output_port.GetConnectionPtr();
        }
    }

    return result;
}

// =====================================================================================================================
