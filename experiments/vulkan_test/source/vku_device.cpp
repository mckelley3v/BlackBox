#include "vku_device.hpp"
#include "vku_utility.hpp"
#include "vku_iostream.hpp"
#include <utility>
#include <cassert>

// ====================================================================================================================

static std::vector<VkLayerProperties> enumerate_device_layer_properties(VkPhysicalDevice physical_device);

static std::vector<VkExtensionProperties> enumerate_device_layer_extension_properties(VkPhysicalDevice physical_device,
                                                                                      VkLayerProperties const &layer);

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

std::vector<vku::LayerExtensionProperties> vku::EnumeratePhysicalDeviceLayersExtensionProperties(VkPhysicalDevice const physicalDevice)
{
    std::vector<LayerExtensionProperties> device_layer_extensions;
    std::vector<VkLayerProperties> const layers = enumerate_device_layer_properties(physicalDevice);
    device_layer_extensions.reserve(layers.size());

    for(VkLayerProperties const &layer : layers)
    {
        device_layer_extensions.push_back(LayerExtensionProperties{layer, enumerate_device_layer_extension_properties(physicalDevice, layer)});
    }

    return device_layer_extensions;
};

// ====================================================================================================================

vku::LogicalDeviceCreateInfo vku::CreateLogicalDeviceCreateInfo(std::vector<VkPhysicalDevice> const &physicalDevices,
                                                                std::vector<PhysicalDeviceRequestedQueueProperties> const &requestedQueues,
                                                                std::vector<std::string> const &requiredLayers,
                                                                std::vector<std::string> const &allowedLayers,
                                                                std::vector<std::string> const &requiredExtensions,
                                                                std::vector<std::string> const &allowedExtensions)
{
    for(VkPhysicalDevice const &physicalDevice : physicalDevices)
    {
        std::vector<LayerExtensionProperties> layer_extension_properties = EnumeratePhysicalDeviceLayersExtensionProperties(physicalDevice);
        if(HasRequiredLayersExtension(layer_extension_properties,
                                      requiredLayers,
                                      requiredExtensions))
        {
            std::vector<VkQueueFamilyProperties> const queue_families_properties = GetPhysicalDeviceQueueFamilyProperties(physicalDevice);
            std::size_t const queue_family_count = queue_families_properties.size();

            std::vector<PhysicalDeviceQueueFamilyCreateInfo> selected_queue_families;
            for(PhysicalDeviceRequestedQueueProperties const &requested_queue : requestedQueues)
            {
                bool found_requested_queue = false;

                for(std::size_t family_index = 0; family_index < queue_family_count; ++family_index)
                {
                    VkQueueFamilyProperties const &family_properties = queue_families_properties[family_index];

                    bool const has_required_queue_flags = (family_properties.queueFlags & requested_queue.requiredQueueFlags) ? true : false;
                    bool const has_forbidden_queue_flags = (family_properties.queueFlags & ~(requested_queue.allowedQueueFlags | requested_queue.requiredQueueFlags)) ? true : false;
                    bool const has_enough_queues = family_properties.queueCount >= requested_queue.requiredEnableCount;
                    if(has_required_queue_flags && !has_forbidden_queue_flags && has_enough_queues)
                    {
                        found_requested_queue = true;
                        uint32_t const requested_queue_count = std::min(family_properties.queueCount, requested_queue.allowedEnableCount);
                        selected_queue_families.push_back(PhysicalDeviceQueueFamilyCreateInfo{family_properties,
                                                                                              static_cast<uint32_t>(family_index),
                                                                                              std::vector<float>(requested_queue_count, requested_queue.defaultPriority)});
                    }
                }

                if(!found_requested_queue)
                {
                    throw std::runtime_error("error: vku::CreateLogicalDeviceCreateInfo unable to find requested queue");
                }
            }

            std::vector<char const*> layer_names;
            std::vector<char const*> extension_names;

            AccumulateAllowedLayersExtensionsNames(layer_names, // ref
                                                   extension_names, // ref
                                                   layer_extension_properties,
                                                   requiredLayers,
                                                   allowedLayers,
                                                   requiredExtensions,
                                                   allowedExtensions);

            return LogicalDeviceCreateInfo{physicalDevice,
                                           std::move(selected_queue_families),
                                           std::move(layer_extension_properties),
                                           std::move(layer_names),
                                           std::move(extension_names)};
        }
    }

    throw std::runtime_error("error: vku::CreateLogicalDeviceCreateInfo unable to find physical device matching requirements");
}

// ====================================================================================================================

/*explicit*/ vku::LogicalDevice::LogicalDevice(VkDevice const device)
    : m_VkDevice(device)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::LogicalDevice::LogicalDevice(LogicalDevice &&rhs)
    : m_VkDevice(rhs.m_VkDevice)
{
    rhs.m_VkDevice = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::LogicalDevice& vku::LogicalDevice::operator = (LogicalDevice &&rhs)
{
    m_VkDevice = rhs.m_VkDevice;
    rhs.m_VkDevice = VK_NULL_HANDLE;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::LogicalDevice::~LogicalDevice()
{
    if(m_VkDevice != VK_NULL_HANDLE)
    {
        vkDestroyDevice(m_VkDevice, // pDevice
                        nullptr); // pAllocator
    }
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::LogicalDevice::operator bool() const
{
    return m_VkDevice != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::LogicalDevice::operator VkDevice() const
{
    return m_VkDevice;
}

// ====================================================================================================================

VkDevice vku::CreateLogicalDevice(VkInstance instance,
                                  std::vector<PhysicalDeviceRequestedQueueProperties> const &requestedQueues,
                                  std::vector<std::string> const &requiredLayers,
                                  std::vector<std::string> const &allowedLayers,
                                  std::vector<std::string> const &requiredExtensions,
                                  std::vector<std::string> const &allowedExtensions)
{
    std::vector<VkPhysicalDevice> const physical_devices = EnumeratePhysicalDevices(instance);
    return CreateLogicalDevice(CreateLogicalDeviceCreateInfo(physical_devices,
                                                             requestedQueues,
                                                             requiredLayers,
                                                             allowedLayers,
                                                             requiredExtensions,
                                                             allowedExtensions));
}

// --------------------------------------------------------------------------------------------------------------------

VkDevice vku::CreateLogicalDevice(LogicalDeviceCreateInfo const &createInfo)
{
    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    queue_create_infos.reserve(createInfo.queueFamilies.size());

    for (PhysicalDeviceQueueFamilyCreateInfo const &queueFamily : createInfo.queueFamilies)
    {
        queue_create_infos.push_back(VkDeviceQueueCreateInfo{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,                 // sType
                                                             nullptr,                                                    // pNext
                                                             0,                                                          // flags
                                                             queueFamily.familyIndex,                                    // queueFamilyIndex
                                                             static_cast<uint32_t>(queueFamily.queuePriorities.size()),  // queueCount
                                                             queueFamily.queuePriorities.data()});                       // pQueuePriorities
    }

    VkDeviceCreateInfo const device_create_info =
    {
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,                           // sType
        nullptr,                                                        // pNext
        0,                                                              // flags
        static_cast<uint32_t>(queue_create_infos.size()),               // queueCreateInfoCount
        queue_create_infos.data(),                                      // pQueueCreateInfos
        static_cast<uint32_t>(createInfo.enabledLayerNames.size()),     // enabledLayerCount
        createInfo.enabledLayerNames.data(),                            // ppEnabledLayerNames
        static_cast<uint32_t>(createInfo.enabledExtensionNames.size()), // enabledExtensionCount
        createInfo.enabledExtensionNames.data(),                        // ppEnabledExtensionNames
        &createInfo.enabledFeatures,                                    // pEnabledFeatures
    };

    VkDevice device = VK_NULL_HANDLE;
    switch(vkCreateDevice(createInfo.physicalDevice, // physicalDevice
                          &device_create_info, // pCreateInfo
                          nullptr, // pAllocator
                          &device))
    {
        case VK_SUCCESS:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_INITIALIZATION_FAILED:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_INITIALIZATION_FAILED");

        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_LAYER_NOT_PRESENT");

        case VK_ERROR_EXTENSION_NOT_PRESENT:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_EXTENSION_NOT_PRESENT");

        case VK_ERROR_FEATURE_NOT_PRESENT:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_FEATURE_NOT_PRESENT");

        case VK_ERROR_TOO_MANY_OBJECTS:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_TOO_MANY_OBJECTS");

        case VK_ERROR_INCOMPATIBLE_DRIVER:
            throw std::runtime_error("error: vkCreateDevice returned VK_ERROR_INCOMPATIBLE_DRIVER");

        default:
            throw std::runtime_error("error: vkCreateDevice returned unknown error");
    };

    return device;
}

// ====================================================================================================================

vku::DeviceProcBase::DeviceProcBase(VkDevice const device,
                                    char const * const func_name)
    : m_FuncPtr(vkGetDeviceProcAddr(device, func_name))
{
    if(m_FuncPtr == nullptr)
    {
        throw std::runtime_error(make_string("error: vkGetDeviceProcAddr(\"", func_name, "\") returned nullptr"));
    }
}

// ====================================================================================================================

std::vector<VkSurfaceFormatKHR> vku::GetPhysicalDeviceSurfaceFormatsKHR(PFN_vkGetPhysicalDeviceSurfaceFormatsKHR const pfnGetPhysicalDeviceSurfaceFormatsKHR,
                                                                        VkPhysicalDevice physicalDevice,
                                                                        VkSurfaceKHR surface)
{
    assert(pfnGetPhysicalDeviceSurfaceFormatsKHR != nullptr);

    uint32_t surface_format_count = 0;
    switch(pfnGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
                                                 surface,
                                                 &surface_format_count,
                                                 nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned unknown error");
    }

    std::vector<VkSurfaceFormatKHR> surface_formats(surface_format_count, VkSurfaceFormatKHR());
    switch(pfnGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
                                                 surface,
                                                 &surface_format_count,
                                                 surface_formats.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned unknown error");
    }

    return surface_formats;
}

// ====================================================================================================================

/*static*/ std::vector<VkLayerProperties> enumerate_device_layer_properties(VkPhysicalDevice const physical_device)
{
    uint32_t layer_count = 0;
    switch(vkEnumerateDeviceLayerProperties(physical_device,
                                            &layer_count,
                                            nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned unknown error");
    }

    // add 1 for unnamed implicit layer
    std::vector<VkLayerProperties> layer_properties(layer_count + 1, VkLayerProperties());
    switch(vkEnumerateDeviceLayerProperties(physical_device,
                                            &layer_count,
                                            layer_properties.data() + 1))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkEnumerateDeviceLayerProperties returned unknown error");
    }

    return layer_properties;
}

// ====================================================================================================================

/*static*/ std::vector<VkExtensionProperties> enumerate_device_layer_extension_properties(VkPhysicalDevice const physical_device,
                                                                                          VkLayerProperties const &layer)
{
    char const * const layerName = (layer.layerName[0] != '\0') ? layer.layerName : nullptr;

    uint32_t extension_count = 0;
    switch(vkEnumerateDeviceExtensionProperties(physical_device,
                                                layerName,
                                                &extension_count,
                                                nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_ERROR_LAYER_NOT_PRESENT");

        default:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned unknown error");
    }

    std::vector<VkExtensionProperties> layer_extension_properties(extension_count, VkExtensionProperties());
    switch(vkEnumerateDeviceExtensionProperties(physical_device,
                                                layerName,
                                                &extension_count,
                                                layer_extension_properties.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned VK_ERROR_LAYER_NOT_PRESENT");

        default:
            throw std::runtime_error("error: vkEnumerateDeviceExtensionProperties returned unknown error");
    }

    return layer_extension_properties;
}

// ====================================================================================================================
