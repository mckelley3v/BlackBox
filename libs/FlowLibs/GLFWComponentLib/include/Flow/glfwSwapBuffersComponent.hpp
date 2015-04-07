#ifndef FLOW_GLFWSWAPBUFFERSCOMPONENT_HPP
#define FLOW_GLFWSWAPBUFFERSCOMPONENT_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"

// =====================================================================================================================

struct GLFWwindow;

// =====================================================================================================================

namespace Flow
{
    // =================================================================================================================

    class glfwSwapBuffersComponent
        : public Component
    {
    public:
        static ComponentDefinition GetDefinition();
        static TypeManagerComponentTypeEntry GetComponentTypeEntry();

        glfwSwapBuffersComponent(TypeManager const &type_manager,
                                 std::string instance_name,
                                 ComponentInputConnectionPtrsDict input_connection_ptrs_dict);
        glfwSwapBuffersComponent(glfwSwapBuffersComponent &&rhs) = default;
        glfwSwapBuffersComponent& operator = (glfwSwapBuffersComponent &&rhs) = default;
        virtual ~glfwSwapBuffersComponent() override = default;

        virtual void Process() override;

    private:
        glfwSwapBuffersComponent() = delete;
        glfwSwapBuffersComponent(glfwSwapBuffersComponent const &rhs) = delete;
        glfwSwapBuffersComponent& operator = (glfwSwapBuffersComponent const &rhs) = delete;

        // members:
        GLFWwindow *m_WindowPtr;
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

#endif // FLOW_GLFWSWAPBUFFERSCOMPONENT_HPP
