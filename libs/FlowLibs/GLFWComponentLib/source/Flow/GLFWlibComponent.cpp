#include "Flow/GLFWlibComponent.hpp"
#include "GLFW/glfw3.h"

// =====================================================================================================================

/*static*/ Flow::ComponentDefinition Flow::GLFWlibComponent::GetDefinition()
{
    return
    {
        // Name
        "GLFWlib",
        // InputPorts
        {},
        // OutputPorts
        {
            {
                "IsValid",  // PortName
                "glfwInit", // TypeName
            },
        },
        // Annotations
        {
            ComponentProcessAnnotation::Never, // Process
        },
    };
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ Flow::TypeManagerComponentTypeEntry Flow::GLFWlibComponent::GetComponentTypeEntry()
{
    return {GetDefinition(), MakeSystemComponent<GLFWlibComponent>};
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::GLFWlibComponent::GLFWlibComponent(TypeManager const &type_manager,
                                         std::string instance_name,
                                         ComponentInputConnectionPtrsDict input_connection_ptrs_dict)
    : Component(type_manager,
                GetDefinition(),
                ComponentInstance{std::move(instance_name),
                                  std::move(input_connection_ptrs_dict),
                                  {{"IsValid", &m_IsValid}}})
    , m_IsValid(glfwInit())
{
    // TODO - consider throwing exception if !m_IsValid
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ Flow::GLFWlibComponent::~GLFWlibComponent()
{
    if(m_IsValid)
    {
        glfwTerminate();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::GLFWlibComponent::IsValid() const
{
    return m_IsValid;
}

// =====================================================================================================================
