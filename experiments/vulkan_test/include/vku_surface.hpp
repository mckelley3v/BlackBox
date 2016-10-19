#ifndef VKU_SURFACE_HPP
#define VKU_SURFACE_HPP

#include <vulkan/vulkan.h>
#include "vku_device.hpp"

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class PhysicalDeviceSurfaceSupportKHR
    {
    public:
        PhysicalDeviceSurfaceSupportKHR(PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfnGetPhysicalDeviceSurfaceSupportKHR,
                                        VkSurfaceKHR surface);

        bool operator () (VkPhysicalDevice physicalDevice,
                          uint32_t queueFamilyIndex,
                          VkQueueFamilyProperties const &queueFamilyProperties) const;

    private:
        // members:
        PFN_vkGetPhysicalDeviceSurfaceSupportKHR m_pfnGetPhysicalDeviceSurfaceSupportKHR = nullptr;
        VkSurfaceKHR m_SurfaceKHR = VK_NULL_HANDLE;
    };

    // ----------------------------------------------------------------------------------------------------------------

    class SelectQueueWithFlagsAndSurfaceSupport
        : private PhysicalDeviceSurfaceSupportKHR
        , private SelectQueueWithFlags
    {
    public:
        SelectQueueWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfnGetPhysicalDeviceSurfaceSupportKHR,
                                              VkSurfaceKHR surface,
                                              VkQueueFlags requiredQueueFlags);
        SelectQueueWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfnGetPhysicalDeviceSurfaceSupportKHR,
                                              VkSurfaceKHR surface,
                                              VkQueueFlags requiredQueueFlags,
                                              VkQueueFlags allowedQueueFlags,
                                              uint32_t requiredEnableCount,
                                              uint32_t allowedEnableCount);

        uint32_t operator () (VkPhysicalDevice physicalDevice,
                              uint32_t queueFamilyIndex,
                              VkQueueFamilyProperties const &queueFamilyProperties) const;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_SURFACE_HPP
