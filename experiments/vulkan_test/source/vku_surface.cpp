#include "vku_surface.hpp"
#include <stdexcept>
#include <cassert>

// ====================================================================================================================

vku::PhysicalDeviceSurfaceSupportKHR::PhysicalDeviceSurfaceSupportKHR(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const procGetPhysicalDeviceSurfaceSupportKHR,
                                                                      VkSurfaceKHR const surface)
    : m_ProcGetPhysicalDeviceSurfaceSupportKHR(procGetPhysicalDeviceSurfaceSupportKHR)
    , m_SurfaceKHR(surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::PhysicalDeviceSurfaceSupportKHR::operator () (VkPhysicalDevice const physicalDevice,
                                                        uint32_t const queueFamilyIndex,
                                                        VkQueueFamilyProperties const &/*queueFamilyProperties*/) const
{
    assert(m_ProcGetPhysicalDeviceSurfaceSupportKHR != nullptr);
    assert(m_SurfaceKHR != VK_NULL_HANDLE);

    VkBool32 surface_support = VK_FALSE;
    switch(m_ProcGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,
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
