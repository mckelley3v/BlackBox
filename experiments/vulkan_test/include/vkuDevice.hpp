#ifndef VKU_DEVICE_HPP
#define VKU_DEVICE_HPP

#include "vkuCore.hpp"
#include "vkuExtension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <functional>

// ====================================================================================================================

#define VKU_DEVICE_PROC_MEMBER(func_name)  vku::VkProc<PFN_ ## func_name> func_name {GetDeviceProcAddr(#func_name)}

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class Instance;

    // ================================================================================================================

    std::vector<VkPhysicalDevice> EnumeratePhysicalDevices(Instance const &instance);

    // ================================================================================================================

    std::vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(Instance const &instance,
                                                                                VkPhysicalDevice physicalDevice);

    // ================================================================================================================

    std::vector<LayerExtensionProperties> EnumeratePhysicalDeviceLayersExtensionProperties(Instance const &instance,
                                                                                           VkPhysicalDevice physicalDevice);

    // ================================================================================================================

    // find queue families that:
    //  -   have required graphics/compute flag
    //  -   have required layers/extensions
    // this implies physical device(s)
    //  -   using multiple devices not supported by vulkan yet
    //  -   for now just allow multiple queue families if they're part of the same physical device
    // generate enabled layers/extensions
    // choose queue counts
    // build logical device

    struct PhysicalDeviceQueueFamilyCreateInfo
    {
        VkQueueFamilyProperties familyProperties;
        uint32_t                familyIndex;
        std::vector<float>      queuePriorities;
    };

    // ----------------------------------------------------------------------------------------------------------------

    struct DeviceCreateInfo
    {
        VkPhysicalDevice                                  physicalDevice;
        std::vector<PhysicalDeviceQueueFamilyCreateInfo>  queueFamilies;
        std::vector<LayerExtensionProperties>             layerExtensionProperties;
        std::vector<char const*>                          enabledLayerNames;
        std::vector<char const*>                          enabledExtensionNames;
        VkPhysicalDeviceFeatures                          enabledFeatures;
    };

    // ----------------------------------------------------------------------------------------------------------------

    class SelectQueueFamilyWithFlags
    {
    public:
        SelectQueueFamilyWithFlags(VkQueueFlags requiredQueueFlags);
        SelectQueueFamilyWithFlags(VkQueueFlags requiredQueueFlags,
                                   VkQueueFlags allowedQueueFlags);

        bool operator () (VkPhysicalDevice physicalDevice,
                          uint32_t queueFamilyIndex,
                          VkQueueFamilyProperties const &queueFamilyProperties) const;

    private:
        // members:
        VkQueueFlags m_RequiredQueueFlags = 0u;
        VkQueueFlags m_AllowedQueueFlags  = ~0u;
    };

    // ----------------------------------------------------------------------------------------------------------------

    typedef std::function<bool(VkPhysicalDevice physicalDevice,
                               uint32_t queueFamilyIndex,
                               VkQueueFamilyProperties const &queueFamilyProperties)> SelectQueueFamilyFunc;

    // ----------------------------------------------------------------------------------------------------------------

    struct PhysicalDeviceRequestedQueueProperties
    {
        SelectQueueFamilyFunc selectQueueFamilyFunc;
        float                 defaultPriority;
        uint32_t              requiredEnableCount;
        uint32_t              allowedEnableCount;
    };

    // ----------------------------------------------------------------------------------------------------------------

    DeviceCreateInfo CreateDeviceCreateInfo(Instance const &instance,
                                            std::vector<PhysicalDeviceRequestedQueueProperties> const &requestedQueues,
                                            std::vector<std::string> const &requiredLayers,
                                            std::vector<std::string> const &allowedLayers,
                                            std::vector<std::string> const &requiredExtensions,
                                            std::vector<std::string> const &allowedExtensions);

    // ================================================================================================================

    class Device
    {
    public:
        explicit Device(Instance const &instance,
                        VkDevice device);
        Device(Device &&rhs);
        Device& operator = (Device &&rhs);
        ~Device();

        explicit operator bool() const;
        operator VkDevice() const;

        PFN_vkVoidFunction GetDeviceProcAddr(char const *func_name) const;

    private:
        Device(Device const &rhs) = delete;
        Device& operator = (Device const &rhs) = delete;

        void Release();
        void Reset();

        // members:
        PFN_vkDestroyDevice     m_pfnDestroyDevice     = nullptr;
        PFN_vkGetDeviceProcAddr m_pfnGetDeviceProcAddr = nullptr;
        VkDevice                m_VkDevice             = VK_NULL_HANDLE;

    public:
        // core procs:
        VKU_DEVICE_PROC_MEMBER(vkDeviceWaitIdle);
        VKU_DEVICE_PROC_MEMBER(vkGetDeviceQueue);
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkDevice CreateDevice(Instance const &instance,
                          DeviceCreateInfo const &createInfo);

    // ================================================================================================================

    class Queue
    {
    public:
        Queue() = default;
        explicit Queue(VkQueue queue, uint32_t familyIndex, uint32_t queueIndex);
        Queue(Queue &&rhs);
        Queue& operator = (Queue &&rhs);
        ~Queue();

        explicit operator bool() const;
        operator VkQueue() const;

        uint32_t GetFamilyIndex() const;
        uint32_t GetQueueIndex() const;

    private:
        Queue(Queue const &rhs) = delete;
        Queue& operator = (Queue const &rhs) = delete;

        // members:
        VkQueue  m_VkQueue = VK_NULL_HANDLE;
        uint32_t m_FamilyIndex = 0u;
        uint32_t m_QueueIndex = 0u;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_DEVICE_HPP
