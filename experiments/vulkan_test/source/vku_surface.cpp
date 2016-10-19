#include "vku_surface.hpp"
#include <stdexcept>
#include <cassert>

// ====================================================================================================================

vku::PhysicalDeviceSurfaceSupportKHR::PhysicalDeviceSurfaceSupportKHR(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                                      VkSurfaceKHR const surface)
    : m_pfnGetPhysicalDeviceSurfaceSupportKHR(pfnGetPhysicalDeviceSurfaceSupportKHR)
    , m_SurfaceKHR(surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::PhysicalDeviceSurfaceSupportKHR::operator () (VkPhysicalDevice const physicalDevice,
                                                        uint32_t const queueFamilyIndex,
                                                        VkQueueFamilyProperties const &/*queueFamilyProperties*/) const
{
    assert(m_pfnGetPhysicalDeviceSurfaceSupportKHR != nullptr);
    assert(m_SurfaceKHR != VK_NULL_HANDLE);

    VkBool32 surface_support = VK_FALSE;
    switch(m_pfnGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,
                                                   queueFamilyIndex,
                                                   m_SurfaceKHR,
                                                   &surface_support))
    {
        case VK_SUCCESS:
            return (surface_support == VK_FALSE) ? false : true;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned unknown error");
    }
}

// ====================================================================================================================

vku::SelectQueueWithFlagsAndSurfaceSupport::SelectQueueWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                                                  VkSurfaceKHR const surface,
                                                                                  VkQueueFlags const requiredQueueFlags)
    : PhysicalDeviceSurfaceSupportKHR(pfnGetPhysicalDeviceSurfaceSupportKHR,
                                      surface)
    , SelectQueueWithFlags(requiredQueueFlags)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::SelectQueueWithFlagsAndSurfaceSupport::SelectQueueWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                                                  VkSurfaceKHR const surface,
                                                                                  VkQueueFlags const requiredQueueFlags,
                                                                                  VkQueueFlags const allowedQueueFlags,
                                                                                  uint32_t const requiredEnableCount,
                                                                                  uint32_t const allowedEnableCount)
    : PhysicalDeviceSurfaceSupportKHR(pfnGetPhysicalDeviceSurfaceSupportKHR,
                                      surface)
    , SelectQueueWithFlags(requiredQueueFlags,
                           allowedQueueFlags,
                           requiredEnableCount,
                           allowedEnableCount)
{
}

// --------------------------------------------------------------------------------------------------------------------

uint32_t vku::SelectQueueWithFlagsAndSurfaceSupport::operator () (VkPhysicalDevice const physicalDevice,
                                                                  uint32_t const queueFamilyIndex,
                                                                  VkQueueFamilyProperties const &queueFamilyProperties) const
{
    if(PhysicalDeviceSurfaceSupportKHR::operator()(physicalDevice,
                                                   queueFamilyIndex,
                                                   queueFamilyProperties))
    {
        return SelectQueueWithFlags::operator()(physicalDevice,
                                                queueFamilyIndex,
                                                queueFamilyProperties);
    }

    return 0u;
}

// ====================================================================================================================
