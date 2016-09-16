#include "vku.hpp"
#include <string>
#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <cassert>

// ====================================================================================================================

std::vector<VkPhysicalDevice> vku::EnumeratePhysicalDevices(VkInstance const instance)
{
    uint32_t device_count = 0;
    switch(vkEnumeratePhysicalDevices(instance,
                                      &device_count,
                                      nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_INITIALIZATION_FAILED:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_ERROR_INITIALIZATION_FAILED");

        default:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned unknown error");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    switch(vkEnumeratePhysicalDevices(instance,
                                      &device_count,
                                      devices.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_INITIALIZATION_FAILED:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned VK_ERROR_INITIALIZATION_FAILED");

        default:
            throw std::runtime_error("error: vkEnumeratePhysicalDevices returned unknown error");
    }

    return devices;
}

// ====================================================================================================================

std::vector<VkQueueFamilyProperties> vku::GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice const physicalDevice)
{
   uint32_t family_property_count = 0;
   vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,
                                            &family_property_count,
                                            nullptr);

   std::vector<VkQueueFamilyProperties> family_properties(family_property_count);
   vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,
                                            &family_property_count,
                                            family_properties.data());

   return family_properties;
}

// ====================================================================================================================

vku::PhysicalDeviceQueueFamily vku::FindPhysicalDeviceQueueFamily(std::vector<VkPhysicalDevice> const &physicalDevices,
                                                                  VkQueueFlags requiredFlags)
{
    for(VkPhysicalDevice const &gpu : physicalDevices)
    {
        std::vector<VkQueueFamilyProperties> const queue_families_properties = vku::GetPhysicalDeviceQueueFamilyProperties(gpu);
        std::size_t const family_count = queue_families_properties.size();
        for(std::size_t family_index = 0; family_index < family_count; ++family_index)
        {
            VkQueueFamilyProperties const &family_properties = queue_families_properties[family_index];
            if(family_properties.queueFlags & requiredFlags)
            {
                return PhysicalDeviceQueueFamily {gpu,
                                                  static_cast<uint32_t>(family_index),
                                                  family_properties};
            }
        }
    }

    throw std::runtime_error("error: vku::FindPhysicalDeviceQueueFamily unable to find queue family");
}

// ====================================================================================================================
// Private Implementation
// ====================================================================================================================
