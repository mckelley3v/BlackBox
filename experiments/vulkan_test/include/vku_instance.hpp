#ifndef VKU_INSTANCE_HPP
#define VKU_INSTANCE_HPP

#include "vku_extension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

// ====================================================================================================================

#ifdef VK_USE_PLATFORM_ANDROID_KHR
#define VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
#define VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_MIR_SURFACE_EXTENSION_NAME
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
#define VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
#define VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
#define VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_XLIB_SURFACE_EXTENSION_NAME
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
#define VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_XCB_SURFACE_EXTENSION_NAME
#endif

// ====================================================================================================================

#define VKU_INSTANCE_PROC_MEMBER(func_name) vku::InstanceProc<PFN_vk ## func_name> func_name {*this, "vk" ## #func_name}

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    std::vector<LayerExtensionProperties> EnumerateInstanceLayersExtensionProperties();

    // ================================================================================================================

    struct ApplicationInfo
    {
        const char* pApplicationName;
        uint32_t    applicationVersion;
        const char* pEngineName;
        uint32_t    engineVersion;
        uint32_t    apiVersion;
    };

    // ================================================================================================================

    class Instance
    {
    public:
        Instance() = default;
        explicit Instance(VkInstance instance);
        Instance(Instance &&rhs);
        Instance& operator = (Instance &&rhs);
        ~Instance();

        explicit operator bool() const;
        operator VkInstance() const;

    private:
        Instance(Instance const &rhs) = delete;
        Instance& operator = (Instance const &rhs) = delete;

        // members:
        VkInstance m_VkInstance = VK_NULL_HANDLE;
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkInstance CreateInstance(ApplicationInfo const &appInfo,
                              std::vector<std::string> const &requiredLayers,
                              std::vector<std::string> const &allowedLayers,
                              std::vector<std::string> const &requiredExtensions,
                              std::vector<std::string> const &allowedExtensions);

    // ================================================================================================================

    class InstanceProcBase
    {
    public:
        InstanceProcBase() = default;
        explicit InstanceProcBase(VkInstance instance,
                                  char const *func_name);

    protected:
        // members:
        PFN_vkVoidFunction m_FuncPtr = nullptr;
    };

    // ================================================================================================================

    template <typename F>
    struct InstanceProc;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R, typename ...Args>
    class InstanceProc<R (VKAPI_PTR*)(Args...)> : public InstanceProcBase
    {
    public:
        using InstanceProcBase::InstanceProcBase;

        R operator () (Args... args) const;
    };

    // ================================================================================================================
}

// ====================================================================================================================

template <typename R, typename ...Args>
R vku::InstanceProc<R (VKAPI_PTR*)(Args...)>::operator () (Args... args) const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr)(args...);
}

// ====================================================================================================================

#endif // VKU_INSTANCE_HPP
