#ifndef VKU_HPP
#define VKU_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include "vku_instance.hpp"
#include "vku_device.hpp"

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
}

#endif // VKU_HPP
