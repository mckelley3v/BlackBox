#ifndef VKU_HPP
#define VKU_HPP

#include "vulkan/vulkan.h"
#include <vector>
#include <utility>
#include <iosfwd>

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

namespace vku
{
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
                              std::initializer_list<char const * const> const &requiredLayers,
                              std::initializer_list<char const * const> const &allowedLayers,
                              std::initializer_list<char const * const> const &requiredExtensions,
                              std::initializer_list<char const * const> const &allowedExtensions);

    // ================================================================================================================

    std::vector<VkPhysicalDevice> EnumeratePhysicalDevices(VkInstance instance);

    // --------------------------------------------------------------------------------------------------------------------

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
                          PhysicalDeviceQueueFamily physicalDeviceQueueFamily);

    // ================================================================================================================

    namespace iostream
    {
        std::ostream& operator << (std::ostream &out, VkPhysicalDeviceProperties const &value);
        std::ostream& operator << (std::ostream &out, VkPhysicalDeviceType const &value);
        std::ostream& operator << (std::ostream &out, VkPhysicalDeviceLimits const &value);
        std::ostream& operator << (std::ostream &out, VkPhysicalDeviceSparseProperties const &value);
        std::ostream& operator << (std::ostream &out, VkQueueFamilyProperties const &value);
        std::ostream& operator << (std::ostream &out, VkExtent3D const &value);
    }

    // ================================================================================================================
}

#endif // VKU_HPP
