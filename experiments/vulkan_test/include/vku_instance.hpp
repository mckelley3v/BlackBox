#ifndef VKU_INSTANCE_HPP
#define VKU_INSTANCE_HPP

#include "vku_extension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

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
        const char *pApplicationName;
        uint32_t    applicationVersion;
        const char *pEngineName;
        uint32_t    engineVersion;
        uint32_t    apiVersion;
    };

    // ----------------------------------------------------------------------------------------------------------------

    struct InstanceCreateInfo
    {
        ApplicationInfo                       applicationInfo;
        std::vector<LayerExtensionProperties> layerExtensionProperties;
        std::vector<char const*>              enabledLayerNames;
        std::vector<char const*>              enabledExtensionNames;
    };

    // ----------------------------------------------------------------------------------------------------------------

    InstanceCreateInfo CreateInstanceCreateInfo(ApplicationInfo const &applicationInfo,
                                                std::vector<std::string> const &requiredLayers,
                                                std::vector<std::string> const &allowedLayers,
                                                std::vector<std::string> const &requiredExtensions,
                                                std::vector<std::string> const &allowedExtensions);

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

    VkInstance CreateInstance(InstanceCreateInfo const &createInfo);

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
        using proc_type = R (VKAPI_PTR*)(Args...);

        proc_type get() const;
        R operator () (Args... args) const;
    };

    // ================================================================================================================
}

// ====================================================================================================================

template <typename R, typename ...Args>
typename vku::InstanceProc<R (VKAPI_PTR*)(Args...)>::proc_type vku::InstanceProc<R (VKAPI_PTR*)(Args...)>::get() const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R, typename ...Args>
R vku::InstanceProc<R (VKAPI_PTR*)(Args...)>::operator () (Args... args) const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr)(args...);
}

// ====================================================================================================================

#endif // VKU_INSTANCE_HPP
