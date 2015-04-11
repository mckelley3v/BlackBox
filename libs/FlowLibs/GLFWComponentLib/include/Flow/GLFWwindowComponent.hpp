#ifndef FLOW_GLFWWINDOWCOMPONENT_HPP
#define FLOW_GLFWWINDOWCOMPONENT_HPP

#include "Flow/Component.hpp"
#include "Flow/TypeManager.hpp"

// =====================================================================================================================

struct GLFWwindow;

// ---------------------------------------------------------------------------------------------------------------------

enum class GLFWwindowMode
{
    Windowed,
    Fullscreen,
};

// ---------------------------------------------------------------------------------------------------------------------

enum class GLFWgraphicsApi
{
    GL_2_1,
    GL_3_3,
    GL_3_3_Core,
    GLES_2_0,
    GLES_3_0,
    GLES_3_1,
};

// ---------------------------------------------------------------------------------------------------------------------

enum class GLFWgraphicsColorFormat
{
    R8G8B8A8,
};

// ---------------------------------------------------------------------------------------------------------------------

enum class GLFWgraphicsDepthFormat
{
    Depth24_Stencil8,
    Depth32,
};

// ---------------------------------------------------------------------------------------------------------------------

enum class GLFWgraphicsMultisample
{
    x1,
    x2,
    x4,
    x8,
    x16,
    x32,
};

// ---------------------------------------------------------------------------------------------------------------------

enum class GLFWgraphicsBuffering
{
    Double,
    Single,
};

// ---------------------------------------------------------------------------------------------------------------------

struct GLFWwindowDescription
{
    int Width;
    int Height;
    std::string Title;
    GLFWwindowMode Mode;
    GLFWgraphicsApi Api;
    GLFWgraphicsColorFormat ColorFormat;
    GLFWgraphicsDepthFormat DepthFormat;
    GLFWgraphicsMultisample Multisample;
    GLFWgraphicsBuffering Buffering;
};

// ---------------------------------------------------------------------------------------------------------------------

using glfwDestroyWindowFunc = void (*)(GLFWwindow*);
using GLFWwindowUPtr = std::unique_ptr<GLFWwindow, glfwDestroyWindowFunc>;

// ---------------------------------------------------------------------------------------------------------------------

GLFWwindowUPtr glfwCreateWindowUPtr(GLFWwindowDescription const &description);

// =====================================================================================================================

namespace Flow
{
    // =================================================================================================================

    class GLFWwindowComponent
        : public Component
    {
    public:
        class InstanceData;

        static ComponentDefinition GetDefinition();
        static TypeManagerComponentTypeEntry GetComponentTypeEntry();
        static std::unique_ptr<Component> MakeInstance(TypeManager const &type_manager,
                                                       std::string instance_name,
                                                       ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                       Component::InstanceData *instance_data_ptr);

        GLFWwindowComponent(TypeManager const &type_manager,
                            std::string instance_name,
                            ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                            InstanceData const &instance_data);
        GLFWwindowComponent(GLFWwindowComponent &&rhs) = default;
        GLFWwindowComponent& operator = (GLFWwindowComponent &&rhs) = default;
        virtual ~GLFWwindowComponent() override = default;

        GLFWwindow* WindowPtr();
        GLFWwindow const* GetWindowPtr() const;
        bool ShouldClose() const;

        virtual void Process() override;

    private:
        GLFWwindowComponent() = delete;
        GLFWwindowComponent(GLFWwindowComponent const &rhs) = delete;
        GLFWwindowComponent& operator = (GLFWwindowComponent const &rhs) = delete;

        // members:
        bool const &m_IsValid;
        GLFWwindowUPtr m_WindowUPtr;
        GLFWwindow *m_WindowPtr;
        bool m_ShouldClose;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class GLFWwindowComponent::InstanceData
        : public Component::InstanceData
    {
    public:
        InstanceData() = default;
        InstanceData(InstanceData &&rhs) = default;
        InstanceData& operator = (InstanceData &&rhs) = default;
        virtual ~InstanceData() = default;

        GLFWwindowDescription& WindowDescription();
        GLFWwindowDescription const& GetWindowDescription() const;

    private:
        InstanceData(InstanceData const &rhs) = delete;
        InstanceData& operator = (InstanceData const &rhs) = delete;

        virtual bool ReadArchive(m1::iarchive_json &in);
        virtual bool ReadArchive(m1::iarchive_ubjson &in);

        // members:
        GLFWwindowDescription m_WindowDescription = {};
    };

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_GLFWWINDOWCOMPONENT_HPP
