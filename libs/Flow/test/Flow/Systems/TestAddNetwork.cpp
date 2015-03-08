#include "Flow/Systems/AddNetwork.hpp"
#include "Flow/Components/Add.hpp"
#include "Flow/Components/Constant.hpp"
#include "Flow/TypeManager.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::Systems::AddNetwork", "[Flow]")
{
    using namespace Flow;
    using namespace Flow::Components;
    using namespace Flow::Systems;

    ComponentDefinition const constant_int_definition = Constant<int>::GetDefinition();
    ComponentDefinition const c0_definition
    {
        // Name
        "Constant<int>{0}",
        constant_int_definition.InputPorts,
        constant_int_definition.OutputPorts,
        constant_int_definition.Annotations,
    };

    ComponentDefinition const c1_definition
    {
        // Name
        "Constant<int>{1}",
        constant_int_definition.InputPorts,
        constant_int_definition.OutputPorts,
        constant_int_definition.Annotations,
    };

    ComponentDefinition const c2_definition
    {
        // Name
        "Constant<int>{2}",
        constant_int_definition.InputPorts,
        constant_int_definition.OutputPorts,
        constant_int_definition.Annotations,
    };

    ComponentDefinition const c4_definition
    {
        // Name
        "Constant<int>{4}",
        constant_int_definition.InputPorts,
        constant_int_definition.OutputPorts,
        constant_int_definition.Annotations,
    };

    TypeManager const type_manager
    {{
        // ComponentTypes
        {
            //                             Definition                 MakeInstanceFunc
            {          Constant<int>::GetDefinition(),                         nullptr},
            {                           c0_definition,  [](TypeManager const &type_manager, std::string instance_name, ComponentInputConnectionPtrsDict input_connection_ptrs_dict) { return MakeConstantInstance(type_manager, std::move(instance_name), std::move(input_connection_ptrs_dict), 0); }}, // TODO - handle parameters
            {                           c1_definition,  [](TypeManager const &type_manager, std::string instance_name, ComponentInputConnectionPtrsDict input_connection_ptrs_dict) { return MakeConstantInstance(type_manager, std::move(instance_name), std::move(input_connection_ptrs_dict), 1); }},
            {                           c2_definition,  [](TypeManager const &type_manager, std::string instance_name, ComponentInputConnectionPtrsDict input_connection_ptrs_dict) { return MakeConstantInstance(type_manager, std::move(instance_name), std::move(input_connection_ptrs_dict), 2); }},
            {                           c4_definition,  [](TypeManager const &type_manager, std::string instance_name, ComponentInputConnectionPtrsDict input_connection_ptrs_dict) { return MakeConstantInstance(type_manager, std::move(instance_name), std::move(input_connection_ptrs_dict), 4); }},
            {               Add<int>::GetDefinition(),   MakeSystemComponent<Add<int>>},
            {   AddNetwork::GetDefinition().Interface, MakeSystemComponent<AddNetwork>},
        },
        // ConnectionTypes
        {
            // Name    BaseNames
            {  "bool",        {}},
            {   "int",        {}},
            { "float",        {}},
        },
    }};

    Systems::AddNetwork add_network(type_manager, "add_network", {});
    add_network.Process();
    CHECK(add_network.GetResult() == 7);
}
