#ifndef FLOW_SYSTEMGRAPH_HPP
#define FLOW_SYSTEMGRAPH_HPP

// =====================================================================================================================
// Flow::SystemGraph
// - Implementation detail for Flow::SystemBase to help sort the components topographically
// =====================================================================================================================
#include "Flow/System.hpp"
#include <vector>

namespace Flow
{
    // =================================================================================================================

    class SystemNode;
    class SystemEdge;

    // -----------------------------------------------------------------------------------------------------------------

    enum class SystemGraphVisitState
    {
        Unvisited,
        Visiting,
        Visited,
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemNode
    {
    public:
        SystemComponentInstance const *InstancePtr;
        std::vector<SystemEdge const*> InputEdgePtrs;
        std::vector<SystemEdge const*> OutputEdgePtrs;
        mutable SystemGraphVisitState VisitState;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemEdge
    {
    public:
        SystemConnection const *ConnectionPtr;
        SystemNode const *SourceNodePtr;
        SystemNode const *TargetNodePtr;
        mutable SystemGraphVisitState VisitState;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemGraph
    {
    public:
        std::vector<SystemNode> Nodes;
        std::vector<SystemEdge> Edges;
    };

    // =================================================================================================================

    SystemGraph MakeSystemGraph(SystemDefinition const &system_definition,
                                ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict);

    // -----------------------------------------------------------------------------------------------------------------

    std::vector<SystemNode const*> SortSystemGraph(SystemGraph const &system_graph);

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_SYSTEMGRAPH_HPP
