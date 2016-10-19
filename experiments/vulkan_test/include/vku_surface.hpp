#ifndef VKU_SURFACE_HPP
#define VKU_SURFACE_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class PhysicalDeviceSurfaceSupportKHR
    {
    public:
        PhysicalDeviceSurfaceSupportKHR(PFN_vkGetPhysicalDeviceSurfaceSupportKHR procGetPhysicalDeviceSurfaceSupportKHR,
                                        VkSurfaceKHR surface);

        bool operator () (VkPhysicalDevice physicalDevice,
                           uint32_t queueFamilyIndex,
                           VkQueueFamilyProperties const &queueFamilyProperties) const;

    private:
        // members:
        PFN_vkGetPhysicalDeviceSurfaceSupportKHR m_ProcGetPhysicalDeviceSurfaceSupportKHR = nullptr;
        VkSurfaceKHR m_SurfaceKHR = VK_NULL_HANDLE;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_SURFACE_HPP
