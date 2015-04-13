#include "Flow/DrawTestTriangleComponent.hpp"
#include "GL/gl.h"

// =====================================================================================================================

/*static*/ Flow::ComponentDefinition Flow::DrawTestTriangleComponent::GetDefinition()
{
    return
    {
        // Name
        "DrawTestTriangleComponent",
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

/*static*/ Flow::TypeManagerComponentTypeEntry Flow::DrawTestTriangleComponent::GetComponentTypeEntry()
{
    return {GetDefinition(), MakeSystemComponent<DrawTestTriangleComponent>};
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::DrawTestTriangleComponent::DrawTestTriangleComponent(TypeManager const &type_manager,
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

/*virtual*/ void Flow::DrawTestTriangleComponent::Process() /*override*/
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(  0.0f,  1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( -1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(  1.0f, -1.0f, 0.0f);
    glEnd();
}

// =====================================================================================================================
