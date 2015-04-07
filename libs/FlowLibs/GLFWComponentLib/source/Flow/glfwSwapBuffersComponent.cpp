#include "Flow/glfwSwapBuffersComponent.hpp"
#include "GLFW/glfw3.h"

// =====================================================================================================================

/*static*/ Flow::ComponentDefinition Flow::glfwSwapBuffersComponent::GetDefinition()
{
    return
    {
        // Name
        "glfwSwapBuffersComponent",
        // InputPorts
        {
            {
                "WindowPtr",    // PortName
                "GLFWwindow*",  // TypeName
            }
        },
        // OutputPorts
        {
            {
                "WindowPtr",    // PortName
                "GLFWwindow*",  // TypeName
            },
        },
        // Annotations
        {
            ComponentProcessAnnotation::Always, // Process
        },
    };
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ Flow::TypeManagerComponentTypeEntry Flow::glfwSwapBuffersComponent::GetComponentTypeEntry()
{
    return {GetDefinition(), MakeSystemComponent<glfwSwapBuffersComponent>};
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::glfwSwapBuffersComponent::glfwSwapBuffersComponent(TypeManager const &type_manager,
                                                         std::string instance_name,
                                                         ComponentInputConnectionPtrsDict input_connection_ptrs_dict)
    : Component(type_manager,
                GetDefinition(),
                ComponentInstance{std::move(instance_name),
                                  std::move(input_connection_ptrs_dict),
                                  {{"WindowPtr", &m_WindowPtr}}})
    , m_WindowPtr(GetInputConnectionRef<GLFWwindow*>(GetInputPortDict(), "WindowPtr"))
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ void Flow::glfwSwapBuffersComponent::Process() /*override*/
{
    if(m_WindowPtr != nullptr)
    {
        glfwSwapBuffers(m_WindowPtr);
    }
}

// =====================================================================================================================
