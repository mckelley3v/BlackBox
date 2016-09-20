#ifndef VKU_DEVICE_HPP
#define VKU_DEVICE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <initializer_list>

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

    struct PhysicalDeviceQueueFamily
    {
       VkPhysicalDevice        physicalDevice;
       uint32_t                familyIndex;
       VkQueueFamilyProperties familyProperties;
    };

    // ----------------------------------------------------------------------------------------------------------------

    PhysicalDeviceQueueFamily FindPhysicalDeviceQueueFamily(std::vector<VkPhysicalDevice> const &physicalDevices,
                                                            VkQueueFlags requiredFlags);

    // ================================================================================================================

    class Device
    {
    public:
       Device() = default;
       explicit Device(VkDevice device);
       Device(Device &&rhs);
       Device& operator = (Device &&rhs);
       ~Device();

       explicit operator bool() const;
       operator VkDevice() const;

    private:
       Device(Device const &rhs) = delete;
       Device& operator = (Device const &rhs) = delete;

       // members:
       VkDevice m_VkDevice = VK_NULL_HANDLE;
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkDevice CreateDevice(VkInstance instance,
                          VkQueueFlags requiredFlags,
                          std::initializer_list<char const * const> const &requiredLayers,
                          std::initializer_list<char const * const> const &requiredExtensions,
                          std::initializer_list<char const * const> const &allowedExtensions);

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

        R operator () (Args...) const;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

template <typename R, typename ...Args>
R vku::DeviceProc<R (VKAPI_PTR*)(Args...)>::operator () (Args... args) const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr)(args...);
}

// ====================================================================================================================

#endif // VKU_DEVICE_HPP
