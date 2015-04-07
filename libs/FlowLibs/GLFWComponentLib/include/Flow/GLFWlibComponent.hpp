#ifndef FLOW_GLFWLIBCOMPONENT_HPP
#define FLOW_GLFWLIBCOMPONENT_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"

// =====================================================================================================================

namespace Flow
{
    // =================================================================================================================

    class GLFWlibComponent
        : public Component
    {
    public:
        static ComponentDefinition GetDefinition();
        static TypeManagerComponentTypeEntry GetComponentTypeEntry();

        GLFWlibComponent(TypeManager const &type_manager,
                         std::string instance_name,
                         ComponentInputConnectionPtrsDict input_connection_ptrs_dict);
        GLFWlibComponent(GLFWlibComponent &&rhs) = default;
        GLFWlibComponent& operator = (GLFWlibComponent &&rhs) = default;
        virtual ~GLFWlibComponent() override;

        bool IsValid() const;

    private:
        GLFWlibComponent() = delete;
        GLFWlibComponent(GLFWlibComponent const &rhs) = delete;
        GLFWlibComponent& operator = (GLFWlibComponent const &rhs) = delete;

        // members:
        bool m_IsValid;
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

#endif // FLOW_GLFWLIBCOMPONENT_HPP
