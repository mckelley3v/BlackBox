#include "Flow/SystemGraph.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/Verify.hpp"

// =====================================================================================================================

// initial construction of SystemNodes, does not determine input/output edges
static std::vector<Flow::SystemNode> MakeSystemNodes(Flow::SystemDefinition const &system_definition);

// create map from component instance name to corresponding SystemNode
static m1::c_str_dictionary<Flow::SystemNode*> MakeSystemNodePtrDict(std::vector<Flow::SystemNode> &system_nodes);

// determine input/output edges, update SystemNodes and return edges
static std::vector<Flow::SystemEdge> MakeSystemEdges(Flow::SystemDefinition const &system_definition,
                                                     m1::c_str_dictionary<Flow::SystemNode*> const &system_node_ptr_dict);

// helper function for topological sort, recursively visits output nodes and adds them to sorted_nodes_ptr
// returns false if graph is not DAG
static bool const SortSystemGraphVisitNode(std::vector<Flow::SystemNode const*> &sorted_nodes_ptr,
                                           Flow::SystemNode const &node);

// =====================================================================================================================

Flow::SystemGraph Flow::MakeSystemGraph(SystemDefinition const &system_definition,
                                        ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict)
{
    std::vector<SystemNode> system_nodes = MakeSystemNodes(system_definition);

    m1::c_str_dictionary<SystemNode*> const system_node_ptr_dict = MakeSystemNodePtrDict(/*ref*/ system_nodes);

    std::vector<SystemEdge> system_edges = MakeSystemEdges(system_definition, system_node_ptr_dict);

    SystemGraph result = {std::move(system_nodes),
                          std::move(system_edges)};

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

std::vector<Flow::SystemNode const*> Flow::SortSystemGraph(SystemGraph const &system_graph)
{
    std::vector<SystemNode const*> result;
    result.reserve(system_graph.Nodes.size());

    for(SystemNode const &system_node : system_graph.Nodes)
    {
        if(system_node.VisitState == SystemGraphVisitState::Unvisited)
        {
            bool const is_valid = SortSystemGraphVisitNode(/*ref*/ result, system_node);
            if(!is_valid)
            {
                throw std::runtime_error("Not a DAG");
            }
        }
    }

    assert(result.size() == system_graph.Nodes.size());
    std::reverse(result.begin(), result.end());
    return result;
}

// =====================================================================================================================

/*static*/ std::vector<Flow::SystemNode> MakeSystemNodes(Flow::SystemDefinition const &system_definition)
{
    using namespace Flow;

    std::vector<SystemNode> result;
    result.reserve(system_definition.ComponentInstances.size());

    for(SystemComponentInstance const &component_instance_initializer : system_definition.ComponentInstances)
    {
        SystemNode node = {&component_instance_initializer, // InstancePtr
                           {}, // InputEdgePtrs
                           {}, // OutputEdgePtrs
                           SystemGraphVisitState::Unvisited};

        result.push_back(std::move(node));
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ m1::c_str_dictionary<Flow::SystemNode*> MakeSystemNodePtrDict(std::vector<Flow::SystemNode> &system_nodes)
{
    using namespace Flow;

    m1::c_str_dictionary<SystemNode*> result;
    //result.reserve(system_nodes.size());

    for(SystemNode &system_node : system_nodes)
    {
        result[system_node.InstancePtr->InstanceName] = &system_node;
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ std::vector<Flow::SystemEdge> MakeSystemEdges(Flow::SystemDefinition const &system_definition,
                                                         m1::c_str_dictionary<Flow::SystemNode*> const &system_node_ptr_dict)
{
    using namespace Flow;

    std::vector<SystemEdge> result;
    result.reserve(system_definition.Connections.size());

    for(SystemConnection const &connection_initializer : system_definition.Connections)
    {
        // ignore inputs from System::In and outputs to System::Out
        if(std::strcmp(connection_initializer.SourcePort.ComponentInstanceName, System::In) == 0) continue;
        if(std::strcmp(connection_initializer.TargetPort.ComponentInstanceName, System::Out) == 0) continue;

        SystemNode * const source_node_ptr = system_node_ptr_dict.at(connection_initializer.SourcePort.ComponentInstanceName);
        SystemNode * const target_node_ptr = system_node_ptr_dict.at(connection_initializer.TargetPort.ComponentInstanceName);

        SystemEdge edge = {&connection_initializer,
                           source_node_ptr,
                           target_node_ptr,
                           SystemGraphVisitState::Unvisited};

        result.push_back(std::move(edge));

        SystemEdge const &new_edge = result.back();
        source_node_ptr->OutputEdgePtrs.push_back(&new_edge);
        target_node_ptr->InputEdgePtrs.push_back(&new_edge);
    }

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ bool const SortSystemGraphVisitNode(std::vector<Flow::SystemNode const*> &sorted_nodes_ptr,
                                               Flow::SystemNode const &node)
{
    using namespace Flow;

    // recursively visit all dependent nodes
    // if a node is encountered that's in the visiting state
    switch(node.VisitState)
    {
        case SystemGraphVisitState::Unvisited:
            node.VisitState = SystemGraphVisitState::Visiting;
            for(SystemEdge const * const edge_ptr : node.OutputEdgePtrs)
            {
                assert(edge_ptr);
                assert(edge_ptr->TargetNodePtr);

                if(!SortSystemGraphVisitNode(sorted_nodes_ptr, *edge_ptr->TargetNodePtr))
                {
                    return false;
                }
            }
            sorted_nodes_ptr.push_back(&node);
            node.VisitState = SystemGraphVisitState::Visited;
            return true;

        case SystemGraphVisitState::Visiting:
            return false;

        case SystemGraphVisitState::Visited:
        default:
            return true;
    }
}

// =====================================================================================================================
