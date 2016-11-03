#ifndef VKU_DEVICE_HPP
#define VKU_DEVICE_HPP

#include "vku_extension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <functional>

// ====================================================================================================================

#define VKU_DEVICE_PROC_MEMBER(func_name) vku::DeviceProc<PFN_vk ## func_name> func_name {*this, "vk" ## #func_name}

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    std::vector<VkPhysicalDevice> EnumeratePhysicalDevices(VkInstance instance);

    // ================================================================================================================

    std::vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice);

    // ================================================================================================================

    std::vector<LayerExtensionProperties> EnumeratePhysicalDeviceLayersExtensionProperties(VkPhysicalDevice physicalDevice);

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

    struct LogicalDeviceCreateInfo
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

    LogicalDeviceCreateInfo CreateLogicalDeviceCreateInfo(VkInstance instance,
                                                          std::vector<PhysicalDeviceRequestedQueueProperties> const &requestedQueues,
                                                          std::vector<std::string> const &requiredLayers,
                                                          std::vector<std::string> const &allowedLayers,
                                                          std::vector<std::string> const &requiredExtensions,
                                                          std::vector<std::string> const &allowedExtensions);

    // ================================================================================================================

    class LogicalDevice
    {
    public:
        LogicalDevice() = default;
        explicit LogicalDevice(VkDevice device);
        LogicalDevice(LogicalDevice &&rhs);
        LogicalDevice& operator = (LogicalDevice &&rhs);
        ~LogicalDevice();

        explicit operator bool() const;
        operator VkDevice() const;

    private:
        LogicalDevice(LogicalDevice const &rhs) = delete;
        LogicalDevice& operator = (LogicalDevice const &rhs) = delete;

        void Reset();

        // members:
        VkDevice m_VkDevice = VK_NULL_HANDLE;
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkDevice CreateLogicalDevice(LogicalDeviceCreateInfo const &createInfo);

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

    class DeviceProcBase
    {
    public:
        DeviceProcBase() = default;
        explicit DeviceProcBase(VkDevice device,
                                char const *func_name);

    protected:
        // members:
        PFN_vkVoidFunction m_FuncPtr = nullptr;
    };

    // ================================================================================================================

    template <typename F>
    struct DeviceProc;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R, typename ...Args>
    class DeviceProc<R (VKAPI_PTR*)(Args...)> : public DeviceProcBase
    {
    public:
        using DeviceProcBase::DeviceProcBase;
        using proc_type = R (VKAPI_PTR*)(Args...);

        proc_type get() const;
        R operator () (Args...) const;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

template <typename R, typename ...Args>
typename vku::DeviceProc<R (VKAPI_PTR*)(Args...)>::proc_type vku::DeviceProc<R (VKAPI_PTR*)(Args...)>::get() const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R, typename ...Args>
R vku::DeviceProc<R (VKAPI_PTR*)(Args...)>::operator () (Args... args) const
{
    return get()(args...);
}

// ====================================================================================================================

#endif // VKU_DEVICE_HPP
