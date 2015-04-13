#ifndef FLOW_DRAWTESTTRIANGLECOMPONENT_HPP
#define FLOW_DRAWTESTTRIANGLECOMPONENT_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"

// =====================================================================================================================

struct GLFWwindow;

// =====================================================================================================================

namespace Flow
{
    // =================================================================================================================

    class DrawTestTriangleComponent
        : public Component
    {
    public:
        static ComponentDefinition GetDefinition();
        static TypeManagerComponentTypeEntry GetComponentTypeEntry();

        DrawTestTriangleComponent(TypeManager const &type_manager,
                                  std::string instance_name,
                                  ComponentInputConnectionPtrsDict input_connection_ptrs_dict);
        DrawTestTriangleComponent(DrawTestTriangleComponent &&rhs) = default;
        DrawTestTriangleComponent& operator = (DrawTestTriangleComponent &&rhs) = default;
        virtual ~DrawTestTriangleComponent() override = default;

        virtual void Process() override;

    private:
        DrawTestTriangleComponent() = delete;
        DrawTestTriangleComponent(DrawTestTriangleComponent const &rhs) = delete;
        DrawTestTriangleComponent& operator = (DrawTestTriangleComponent const &rhs) = delete;

        // members:
        GLFWwindow *m_WindowPtr;
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

#endif // FLOW_DRAWTESTTRIANGLECOMPONENT_HPP
