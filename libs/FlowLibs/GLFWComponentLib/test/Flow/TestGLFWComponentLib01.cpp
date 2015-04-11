#include "Flow/System.hpp"
#include "Flow/TypeManager.hpp"
#include "Flow/glfwSwapBuffersComponent.hpp"
#include "Flow/GLFWlibComponent.hpp"
#include "Flow/GLFWwindowComponent.hpp"
#include "m1/log.hpp"
#include "m1/iarchive_json.hpp"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Test GLFWComponentLib", "[Flow]")
{
    using namespace Flow;

    TypeManager type_manager
    {{
        // ComponentTypes
        {
            glfwSwapBuffersComponent::GetComponentTypeEntry(),
            GLFWlibComponent::GetComponentTypeEntry(),
            GLFWwindowComponent::GetComponentTypeEntry(),
        },
        // ConnectionTypes
        {
            // Name               BaseNames
            {             "bool", {}},
            {              "int", {}},
            {            "float", {}},
            {         "glfwInit", {}},
            {"GLFWwindow const*", {}},
            {      "GLFWwindow*", {"GLFWwindow const*"}},
        },
    }};

    char const * const json =
R"json(
{
    "Interface":
    {
        "Name": "TestGLFWComponentLib",
        "InputPorts": null,
        "OutputPorts":
        [
            {"PortName": "IsDone", "TypeName": "bool"}
        ]
    },
    "ComponentInstances":
    [
        {
            "DefinitionName": "GLFWlib",
            "InstanceName": "GLFW"
        },
        {
            "DefinitionName": "GLFWwindowComponent",
            "InstanceName": "GLFWwindow",
            "InstanceData":
            {
                "Width": 640,
                "Height": 480,
                "Title": "Test GLFW",
                "Api": "GL-2.1"
            }
        },
        {
            "DefinitionName": "glfwSwapBuffersComponent",
            "InstanceName": "glfwSwapBuffers"
        }
    ],
    "Connections":
    [
        {"SourcePort": {"ComponentInstanceName": "GLFW",           "PortName": "IsValid"},
         "TargetPort": {"ComponentInstanceName": "GLFWwindow",     "PortName": "IsValid"}},
        {"SourcePort": {"ComponentInstanceName": "GLFWwindow",     "PortName": "WindowPtr"},
         "TargetPort": {"ComponentInstanceName": "glfwSwapBuffers","PortName": "WindowPtr"}},
        {"SourcePort": {"ComponentInstanceName": "GLFWwindow",     "PortName": "ShouldClose"},
         "TargetPort": {"ComponentInstanceName": "out:",           "PortName": "IsDone"}}
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
    System system(type_manager, std::move(definition), {"TestGLFWComponentLib"});
    bool const * const is_done_ptr = GetOutputConnectionPtr<bool>(system.GetOutputPortDict(), "IsDone");
    REQUIRE(is_done_ptr != nullptr);
    bool const &is_done = *is_done_ptr;

    // run system
    while(!is_done)
    {
        system.Process();
    }

    CHECK(is_done);
}
