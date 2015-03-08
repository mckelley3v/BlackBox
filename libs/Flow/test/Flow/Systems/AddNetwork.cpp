#include "Flow/Systems/AddNetwork.hpp"
#include "Flow/Components/Add.hpp"
#include "Flow/Components/Constant.hpp"

// =====================================================================================================================

/*static*/ Flow::SystemDefinition Flow::Systems::AddNetwork::GetDefinition()
{
    return
    {
        // Interface
        {
            // Name
            "AddNetwork",
            // InputPorts
            {
            },
            // OutputPorts
            {
                //   Name   Type
                {"Result", "int"},
            },
            // Annotations
            {
                ComponentProcessAnnotation::Always,
            },
        },
        // ComponentInstances
        {
            //   DefinitionName   InstanceName
            {"Constant<int>{0}", "const_int_0"},
            {"Constant<int>{1}", "const_int_1"},
            {"Constant<int>{2}", "const_int_2"},
            {"Constant<int>{4}", "const_int_4"},
            {        "Add<int>",       "add_0"},
            {        "Add<int>",       "add_1"},
            {        "Add<int>",       "add_2"},
        },
        // Connections
        {
            //                SourcePort                               TargetPort
            // ComponentInstanceName    PortName        ComponentInstanceName    PortName
            {{         "const_int_0",    "Value"}, {                  "add_0",      "Lhs"}},
            {{         "const_int_1",    "Value"}, {                  "add_0",      "Rhs"}},
            {{         "const_int_2",    "Value"}, {                  "add_1",      "Lhs"}},
            {{         "const_int_4",    "Value"}, {                  "add_1",      "Rhs"}},
            {{               "add_0",   "Result"}, {                  "add_2",      "Lhs"}},
            {{               "add_1",   "Result"}, {                  "add_2",      "Rhs"}},
            {{               "add_2",   "Result"}, {              System::Out,   "Result"}},
        },
    };
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::Systems::AddNetwork::AddNetwork(TypeManager const &type_manager,
                                      std::string instance_name,
                                      ComponentInputConnectionPtrsDict input_connection_ptrs_dict)
    : System(type_manager,
             GetDefinition(),
             SystemInstance{std::move(instance_name),
                            std::move(input_connection_ptrs_dict)})
    , m_Result(GetOutputConnectionRef<int>(GetOutputPortDict(), "Result"))
{
}

// ---------------------------------------------------------------------------------------------------------------------

int const& Flow::Systems::AddNetwork::GetResult() const
{
    return m_Result;
}

// =====================================================================================================================
