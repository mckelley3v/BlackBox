#include "Flow/Components/Add.hpp"
#include "Flow/Components/Constant.hpp"
#include "Flow/System.hpp"
#include "Flow/TypeManager.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Test Flow JSON", "[Flow]")
{
    using namespace Flow;
    using namespace Flow::Components;

    TypeManager type_manager
    {{
        // ComponentTypes
        {
            //                             Definition                 MakeInstanceFunc                           MakeInstanceDataFunc
            {          Constant<int>::GetDefinition(),       MakeConstantInstance<int>, std::make_shared<Constant<int>::InstanceData>},
            {               Add<int>::GetDefinition(),   MakeSystemComponent<Add<int>>},
        },
        // ConnectionTypes
        {
            // Name    BaseNames
            {  "bool",        {}},
            {   "int",        {}},
            { "float",        {}},
        },
    }};

    char const * const json =
R"json(
{
    "Interface":
    {
        "Name": "AddNetwork",
        "InputPorts": null,
        "OutputPorts":
        [
            {"PortName": "Result", "TypeName": "int"}
        ],
        "Annotations":
        {
            "Process": "Always"
        }
    },
    "ComponentInstances":
    [
        {"DefinitionName": "Constant<int>", "InstanceName": "const_int_0", "InstanceData": 0},
        {"DefinitionName": "Constant<int>", "InstanceName": "const_int_1", "InstanceData": 1},
        {"DefinitionName": "Constant<int>", "InstanceName": "const_int_2", "InstanceData": 2},
        {"DefinitionName": "Constant<int>", "InstanceName": "const_int_4", "InstanceData": 4},
        {"DefinitionName":      "Add<int>", "InstanceName":       "add_0"},
        {"DefinitionName":      "Add<int>", "InstanceName":       "add_1"},
        {"DefinitionName":      "Add<int>", "InstanceName":       "add_2"}
    ],
    "Connections":
    [
        {"SourcePort": {"ComponentInstanceName": "const_int_0", "PortName": "Value"},
         "TargetPort": {"ComponentInstanceName": "add_0",       "PortName": "Lhs"}},
        {"SourcePort": {"ComponentInstanceName": "const_int_1", "PortName": "Value"},
         "TargetPort": {"ComponentInstanceName": "add_0",       "PortName": "Rhs"}},
        {"SourcePort": {"ComponentInstanceName": "const_int_2", "PortName": "Value"},
         "TargetPort": {"ComponentInstanceName": "add_1",       "PortName": "Lhs"}},
        {"SourcePort": {"ComponentInstanceName": "const_int_4", "PortName": "Value"},
         "TargetPort": {"ComponentInstanceName": "add_1",       "PortName": "Rhs"}},
        {"SourcePort": {"ComponentInstanceName": "add_0",       "PortName": "Result"},
         "TargetPort": {"ComponentInstanceName": "add_2",       "PortName": "Lhs"}},
        {"SourcePort": {"ComponentInstanceName": "add_1",       "PortName": "Result"},
         "TargetPort": {"ComponentInstanceName": "add_2",       "PortName": "Rhs"}},
        {"SourcePort": {"ComponentInstanceName": "add_2",       "PortName": "Result"},
         "TargetPort": {"ComponentInstanceName": "out:",        "PortName": "Result"}}
    ]
}
)json";

    m1::log logger(std::cout,
                   std::clog,
                   std::cerr);

    m1::iarchive_json in(logger, json);

    // read definition from JSON
    SystemDefinition definition{};
    REQUIRE(read_value(in, type_manager, definition));
    type_manager.AddSystemDefinition(definition);

    // create system
    System system(type_manager, std::move(definition), {"TestSerialization"});
    int const &result = GetOutputConnectionRef<int>(system.GetOutputPortDict(), "Result");

    // run system once
    system.Process();

    CHECK(result == 7);
}
