#ifndef VKU_INSTANCE_HPP
#define VKU_INSTANCE_HPP

#include "vkuCore.hpp"
#include "vkuExtension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

// ====================================================================================================================

#define VKU_INSTANCE_PROC_MEMBER(func_name)    vku::VkProc<PFN_ ## func_name> func_name {GetInstanceProcAddr(#func_name)}

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
        explicit Instance(VkInstance instance);
        Instance(Instance &&rhs);
        Instance& operator = (Instance &&rhs);
        ~Instance();

        explicit operator bool() const;
        operator VkInstance() const;

        PFN_vkVoidFunction GetInstanceProcAddr(char const *func_name) const;

    private:
        Instance(Instance const &rhs) = delete;
        Instance& operator = (Instance const &rhs) = delete;

        void Release();
        void Reset();

        // members:
        VkInstance m_VkInstance = VK_NULL_HANDLE;

    public:
        // core procs:
        VKU_INSTANCE_PROC_MEMBER(vkDestroyInstance);
        VKU_INSTANCE_PROC_MEMBER(vkEnumeratePhysicalDevices);
        VKU_INSTANCE_PROC_MEMBER(vkGetPhysicalDeviceQueueFamilyProperties);
        VKU_INSTANCE_PROC_MEMBER(vkEnumerateDeviceLayerProperties);
        VKU_INSTANCE_PROC_MEMBER(vkEnumerateDeviceExtensionProperties);
        VKU_INSTANCE_PROC_MEMBER(vkCreateDevice);
        VKU_INSTANCE_PROC_MEMBER(vkDestroyDevice);
        VKU_INSTANCE_PROC_MEMBER(vkGetDeviceProcAddr);
        VKU_INSTANCE_PROC_MEMBER(vkFreeCommandBuffers);
        VKU_INSTANCE_PROC_MEMBER(vkDestroyFramebuffer);
        VKU_INSTANCE_PROC_MEMBER(vkCreateImageView);
        VKU_INSTANCE_PROC_MEMBER(vkDestroyImageView);
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkInstance CreateInstance(InstanceCreateInfo const &createInfo);

    // ================================================================================================================
}

// ====================================================================================================================

#endif // VKU_INSTANCE_HPP
