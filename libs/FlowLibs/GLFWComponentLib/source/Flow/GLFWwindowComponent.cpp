#include "Flow/GLFWwindowComponent.hpp"
#include "m1/iarchive_json.hpp"
#include "m1/iarchive_ubjson.hpp"
#include "GLFW/glfw3.h"

// =====================================================================================================================

static void glfwWindowHint(GLFWwindowMode mode);
static void glfwWindowHint(GLFWgraphicsApi api);
static void glfwWindowHint(GLFWgraphicsColorFormat color_format);
static void glfwWindowHint(GLFWgraphicsDepthFormat depth_format);
static void glfwWindowHint(GLFWgraphicsMultisample multisample);
static void glfwWindowHint(GLFWgraphicsBuffering buffering);
static void glfwWindowHint(GLFWwindowDescription const &description);

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> static bool read_value(IArchive &in, GLFWwindowMode &value);
template <typename IArchive> static bool read_value(IArchive &in, GLFWgraphicsApi &value);
template <typename IArchive> static bool read_value(IArchive &in, GLFWgraphicsColorFormat &value);
template <typename IArchive> static bool read_value(IArchive &in, GLFWgraphicsDepthFormat &value);
template <typename IArchive> static bool read_value(IArchive &in, GLFWgraphicsMultisample &value);
template <typename IArchive> static bool read_value(IArchive &in, GLFWgraphicsBuffering &value);
template <typename IArchive> static bool read_value(IArchive &in, GLFWwindowDescription &value);

// =====================================================================================================================

GLFWwindowUPtr glfwCreateWindowUPtr(GLFWwindowDescription const &description)
{
    glfwWindowHint(description);
    return GLFWwindowUPtr(glfwCreateWindow(description.Width,
                                           description.Height,
                                           description.Title.c_str(),
                                           (description.Mode == GLFWwindowMode::Windowed) ? nullptr
                                                                                          : glfwGetPrimaryMonitor(),
                                           nullptr),
                          glfwDestroyWindow);
}

// =====================================================================================================================

/*static*/ Flow::ComponentDefinition Flow::GLFWwindowComponent::GetDefinition()
{
    return
    {
        // Name
        "GLFWwindowComponent",
        // InputPorts
        {
            {
                "IsValid",  // PortName
                "glfwInit", // TypeName
            }
        },
        // OutputPorts
        {
            {
                "WindowPtr",    // PortName
                "GLFWwindow*",  // TypeName
            },
            {
                "ShouldClose",  // PortName
                "bool",         // TypeName
            },
        },
        // Annotations
        {
            ComponentProcessAnnotation::Always, // Process
        },
    };
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ Flow::TypeManagerComponentTypeEntry Flow::GLFWwindowComponent::GetComponentTypeEntry()
{
    return {GetDefinition(), MakeInstance, std::make_shared<InstanceData>};
}

// ---------------------------------------------------------------------------------------------------------------------

std::unique_ptr<Flow::Component> Flow::GLFWwindowComponent::MakeInstance(TypeManager const &type_manager,
                                                                         std::string instance_name,
                                                                         ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                                                         Component::InstanceData *instance_data_ptr)
{
    assert(dynamic_cast<InstanceData*>(instance_data_ptr) != nullptr);

    return std::make_unique<GLFWwindowComponent>(type_manager,
                                                 std::move(instance_name),
                                                 std::move(input_connection_ptrs_dict),
                                                 *static_cast<InstanceData*>(instance_data_ptr));
}

// ---------------------------------------------------------------------------------------------------------------------

Flow::GLFWwindowComponent::GLFWwindowComponent(TypeManager const &type_manager,
                                               std::string instance_name,
                                               ComponentInputConnectionPtrsDict input_connection_ptrs_dict,
                                               InstanceData const &instance_data)
    : Component(type_manager,
                GetDefinition(),
                ComponentInstance{std::move(instance_name),
                                  std::move(input_connection_ptrs_dict),
                                  {{"WindowPtr", &m_WindowPtr},
                                   {"ShouldClose", &m_ShouldClose}}})
    , m_IsValid(GetInputConnectionRef<bool>(GetInputPortDict(), "IsValid"))
    , m_WindowUPtr(m_IsValid ? glfwCreateWindowUPtr(instance_data.GetWindowDescription())
                             : GLFWwindowUPtr(nullptr, glfwDestroyWindow))
    , m_WindowPtr(m_WindowUPtr.get())
    , m_ShouldClose(false)
{
}

// ---------------------------------------------------------------------------------------------------------------------

GLFWwindow* Flow::GLFWwindowComponent::WindowPtr()
{
    return m_WindowPtr;
}

// ---------------------------------------------------------------------------------------------------------------------

GLFWwindow const* Flow::GLFWwindowComponent::GetWindowPtr() const
{
    return m_WindowPtr;
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::GLFWwindowComponent::ShouldClose() const
{
    return m_ShouldClose;
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ void Flow::GLFWwindowComponent::Process() /*override*/
{
    glfwPollEvents();
    m_ShouldClose = glfwWindowShouldClose(m_WindowPtr);
}

// =====================================================================================================================

GLFWwindowDescription& Flow::GLFWwindowComponent::InstanceData::WindowDescription()
{
    return m_WindowDescription;
}

// ---------------------------------------------------------------------------------------------------------------------

GLFWwindowDescription const& Flow::GLFWwindowComponent::InstanceData::GetWindowDescription() const
{
    return m_WindowDescription;
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ bool Flow::GLFWwindowComponent::InstanceData::ReadArchive(m1::iarchive_json &in)
{
    return read_value(in, m_WindowDescription);
}

// ---------------------------------------------------------------------------------------------------------------------

/*virtual*/ bool Flow::GLFWwindowComponent::InstanceData::ReadArchive(m1::iarchive_ubjson &in)
{
    return false;
    //return read_value(in, m_WindowDescription);
}

// =====================================================================================================================

/*static*/ void glfwWindowHint(GLFWgraphicsApi const api)
{
    switch(api)
    {
        case GLFWgraphicsApi::OpenGL_2_1:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            break;

        case GLFWgraphicsApi::OpenGL_3_3_Legacy:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            break;

        case GLFWgraphicsApi::OpenGL_3_3_Core:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
            break;

        case GLFWgraphicsApi::OpenGLES_2_0:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            break;

        case GLFWgraphicsApi::OpenGLES_3_0:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            break;

        case GLFWgraphicsApi::OpenGLES_3_1:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ void glfwWindowHint(GLFWgraphicsColorFormat const color_format)
{
    switch(color_format)
    {
        case GLFWgraphicsColorFormat::R8G8B8A8:
            glfwWindowHint(GLFW_RED_BITS, 8);
            glfwWindowHint(GLFW_GREEN_BITS, 8);
            glfwWindowHint(GLFW_BLUE_BITS, 8);
            glfwWindowHint(GLFW_ALPHA_BITS, 8);
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ void glfwWindowHint(GLFWgraphicsDepthFormat const depth_format)
{
    switch(depth_format)
    {
        case GLFWgraphicsDepthFormat::Depth32:
            glfwWindowHint(GLFW_DEPTH_BITS, 32);
            glfwWindowHint(GLFW_STENCIL_BITS, 0);
            break;

        case GLFWgraphicsDepthFormat::Depth24_Stencil8:
            glfwWindowHint(GLFW_DEPTH_BITS, 24);
            glfwWindowHint(GLFW_STENCIL_BITS, 8);
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ void glfwWindowHint(GLFWgraphicsMultisample const multisample)
{
    switch(multisample)
    {
        case GLFWgraphicsMultisample::x1:
            glfwWindowHint(GLFW_SAMPLES, 0);
            break;

        case GLFWgraphicsMultisample::x2:
            glfwWindowHint(GLFW_SAMPLES, 2);
            break;

        case GLFWgraphicsMultisample::x4:
            glfwWindowHint(GLFW_SAMPLES, 4);
            break;

        case GLFWgraphicsMultisample::x8:
            glfwWindowHint(GLFW_SAMPLES, 8);
            break;

        case GLFWgraphicsMultisample::x16:
            glfwWindowHint(GLFW_SAMPLES, 16);
            break;

        case GLFWgraphicsMultisample::x32:
            glfwWindowHint(GLFW_SAMPLES, 32);
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ void glfwWindowHint(GLFWgraphicsBuffering const buffering)
{
    switch(buffering)
    {
        case GLFWgraphicsBuffering::Double:
            glfwWindowHint(GLFW_DOUBLEBUFFER, true);
            break;

        case GLFWgraphicsBuffering::Single:
            glfwWindowHint(GLFW_DOUBLEBUFFER, false);
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ void glfwWindowHint(GLFWwindowDescription const &description)
{
    glfwDefaultWindowHints();
    glfwWindowHint(description.Api);
    glfwWindowHint(description.ColorFormat);
    glfwWindowHint(description.DepthFormat);
    glfwWindowHint(description.Multisample);
    glfwWindowHint(description.Buffering);
}

// =====================================================================================================================

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWwindowMode &value)
{
    m1::crc32 crc;
    if(read_value(in, crc))
    {
        switch(crc)
        {
            case m1::crc32("Windowed"):
                value = GLFWwindowMode::Windowed;
                return true;

            case m1::crc32("Fullscreen"):
                value = GLFWwindowMode::Fullscreen;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid GLFWwindowMode");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWgraphicsApi &value)
{
    m1::crc32 crc;
    if(read_value(in, crc))
    {
        switch(crc)
        {
            case m1::crc32("OpenGL_2_1"):
                value = GLFWgraphicsApi::OpenGL_2_1;
                return true;

            case m1::crc32("OpenGL_3_3_Legacy"):
                value = GLFWgraphicsApi::OpenGL_3_3_Legacy;
                return true;

            case m1::crc32("OpenGL_3_3_Core"):
                value = GLFWgraphicsApi::OpenGL_3_3_Core;
                return true;

            case m1::crc32("OpenGLES_2_0"):
                value = GLFWgraphicsApi::OpenGLES_2_0;
                return true;

            case m1::crc32("OpenGLES_3_0"):
                value = GLFWgraphicsApi::OpenGLES_3_0;
                return true;

            case m1::crc32("OpenGLES_3_1"):
                value = GLFWgraphicsApi::OpenGLES_3_1;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid GLFWgraphicsApi");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWgraphicsColorFormat &value)
{
    m1::crc32 crc;
    if(read_value(in, crc))
    {
        switch(crc)
        {
            case m1::crc32("Default"):
                value = GLFWgraphicsColorFormat::R8G8B8A8;
                return true;

            case m1::crc32("RGBA8"):
                value = GLFWgraphicsColorFormat::R8G8B8A8;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid GLFWgraphicsColorFormat");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWgraphicsDepthFormat &value)
{
    m1::crc32 crc;
    if(read_value(in, crc))
    {
        switch(crc)
        {
            case m1::crc32("Default"):
                value = GLFWgraphicsDepthFormat::Depth24_Stencil8;
                return true;

            case m1::crc32("Depth24_Stencil8"):
                value = GLFWgraphicsDepthFormat::Depth24_Stencil8;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid GLFWgraphicsDepthFormat");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWgraphicsMultisample &value)
{
    int multisample = 0;
    if(read_value(in, multisample))
    {
        switch(multisample)
        {
            case 1:
                value = GLFWgraphicsMultisample::x1;
                return true;

            case 2:
                value = GLFWgraphicsMultisample::x2;
                return true;

            case 4:
                value = GLFWgraphicsMultisample::x4;
                return true;

            case 8:
                value = GLFWgraphicsMultisample::x8;
                return true;

            case 16:
                value = GLFWgraphicsMultisample::x16;
                return true;

            case 32:
                value = GLFWgraphicsMultisample::x32;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid GLFWgraphicsMultisample");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWgraphicsBuffering &value)
{
    m1::crc32 crc;
    if(read_value(in, crc))
    {
        switch(crc)
        {
            case m1::crc32("Double"):
                value = GLFWgraphicsBuffering::Double;
                return true;

            case m1::crc32("Single"):
                value = GLFWgraphicsBuffering::Single;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid GLFWgraphicsBuffering");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool read_value(IArchive &in, GLFWwindowDescription &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("Width"):
                result &= read_value(in, value.Width);
                break;

            case m1::property_id("Height"):
                result &= read_value(in, value.Height);
                break;

            case m1::property_id("Title"):
                result &= read_value(in, value.Title);
                break;

            case m1::property_id("Mode"):
                result &= read_value(in, value.Mode);
                break;

            case m1::property_id("Api"):
                result &= read_value(in, value.Api);
                break;

            case m1::property_id("ColorFormat"):
                result &= read_value(in, value.ColorFormat);
                break;

            case m1::property_id("DepthFormat"):
                result &= read_value(in, value.DepthFormat);
                break;

            case m1::property_id("Multisample"):
                result &= read_value(in, value.Multisample);
                break;

            case m1::property_id("Buffering"):
                result &= read_value(in, value.Buffering);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================
