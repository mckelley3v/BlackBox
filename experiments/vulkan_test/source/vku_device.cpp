#include "vku_device.hpp"
#include "vku_utility.hpp"
#include <utility>

// ====================================================================================================================

static std::vector<VkLayerProperties> enumerate_device_layer_properties(VkPhysicalDevice physical_device);
static std::vector<VkExtensionProperties> enumerate_device_layer_extension_properties(VkPhysicalDevice physical_device,
                                                                                      VkLayerProperties const &layer);
static std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> enumerate_device_all_layers_extension_properties(VkPhysicalDevice physical_device);

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
        std::vector<VkQueueFamilyProperties> const queue_families_properties = GetPhysicalDeviceQueueFamilyProperties(gpu);
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

/*explicit*/ vku::Device::Device(VkDevice const device)
   : m_VkDevice(device)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::Device(Device &&rhs)
   : m_VkDevice(rhs.m_VkDevice)
{
   rhs.m_VkDevice = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device& vku::Device::operator = (Device &&rhs)
{
   m_VkDevice = rhs.m_VkDevice;
   rhs.m_VkDevice = VK_NULL_HANDLE;
   return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::~Device()
{
   if(m_VkDevice != VK_NULL_HANDLE)
   {
      vkDestroyDevice(m_VkDevice, // pDevice
                      nullptr); // pAllocator
   }
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::Device::operator bool() const
{
   return m_VkDevice != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::operator VkDevice() const
{
   return m_VkDevice;
}

// ====================================================================================================================

VkDevice vku::CreateDevice(VkInstance instance,
                           VkQueueFlags requiredFlags,
                           std::initializer_list<char const * const> const &requiredLayers,
                           std::initializer_list<char const * const> const &requiredExtensions,
                           std::initializer_list<char const * const> const &allowedExtensions)
{
    std::vector<VkPhysicalDevice> const physical_devices = EnumeratePhysicalDevices(instance);
    PhysicalDeviceQueueFamily const selected_device_queue_family = FindPhysicalDeviceQueueFamily(physical_devices,
                                                                                                 requiredFlags);

    std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> const all_layers_extensions = enumerate_device_all_layers_extension_properties(selected_device_queue_family.physicalDevice);

    // gather layer/extension names, filter to required/allowed lists
    std::vector<char const*> layer_names;
    std::vector<char const*> extension_names;
    for(auto const &layer_extensions_entry : all_layers_extensions)
    {
        VkLayerProperties const &layer = layer_extensions_entry.first;
        std::vector<VkExtensionProperties> const &layer_extensions = layer_extensions_entry.second;

        bool use_layer = contains(requiredLayers.begin(),
                                  requiredLayers.end(),
                                  c_str_compare_to(layer.layerName));

        for(VkExtensionProperties const &extension : layer_extensions)
        {
            bool const allow_extension = contains(requiredExtensions.begin(),
                                                  requiredExtensions.end(),
                                                  c_str_compare_to(extension.extensionName)) ||
                                         contains(allowedExtensions.begin(),
                                                  allowedExtensions.end(),
                                                  name_compare_to(extension.extensionName));
            if(allow_extension)
            {
                use_layer = true;
                extension_names.push_back(extension.extensionName);
            }
        }

        if(use_layer && (layer.layerName[0] != '\0'))
        {
            layer_names.push_back(layer.layerName);
        }
    }

    // enforce required layers
    for(char const * const required_layer : requiredLayers)
    {
        bool const has_layer = contains(layer_names.begin(),
                                        layer_names.end(),
                                        c_str_compare_to(required_layer));
        if(!has_layer)
        {
            throw std::runtime_error(make_string({"vku::CreateDevice missing required layer (\"", required_layer, "\")"}));
        }
    }

    // enforce required extensions
    for(char const * const required_extension : requiredExtensions)
    {
        bool const has_extension = contains(extension_names.begin(),
                                            extension_names.end(),
                                            c_str_compare_to(required_extension));
        if(!has_extension)
        {
            throw std::runtime_error(make_string({"vku::CreateDevice missing required extension (\"", required_extension, "\")"}));
        }
    }

    float const queue_priorities[] = {1.0f};
    VkDeviceQueueCreateInfo const queue_create_infos[] =
    {
        {
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, // sType
            nullptr,                                    // pNext
            0,                                          // flags
            selected_device_queue_family.familyIndex,   // queueFamilyIndex
            1,                                          // queueCount
            queue_priorities,                           // pQueuePriorities
        },
    };

    VkDeviceCreateInfo const device_create_info =
    {
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,             // sType
        nullptr,                                          // pNext
        0,                                                // flags
        std::extent<decltype(queue_create_infos)>::value, // queueCreateInfoCount
        queue_create_infos,                               // pQueueCreateInfos
        static_cast<uint32_t>(layer_names.size()),        // enabledLayerCount
        layer_names.data(),                               // ppEnabledLayerNames
        static_cast<uint32_t>(extension_names.size()),    // enabledExtensionCount
        extension_names.data(),                           // ppEnabledExtensionNames
        nullptr,                                          // pEnabledFeatures
    };

    VkDevice device = VK_NULL_HANDLE;
    switch(vkCreateDevice(selected_device_queue_family.physicalDevice, // physicalDevice
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
        throw std::runtime_error(make_string({"error: vkGetDeviceProcAddr(\"", func_name, "\") returned nullptr"}));
    }
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
    uint32_t extension_count = 0;
    switch(vkEnumerateDeviceExtensionProperties(physical_device,
                                                (layer.layerName[0] != '\0') ? layer.layerName : nullptr,
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
                                                (layer.layerName[0] != '\0') ? layer.layerName : nullptr,
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

/*static*/ std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> enumerate_device_all_layers_extension_properties(VkPhysicalDevice const physical_device)
{
    std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> device_layer_extensions;

    std::vector<VkLayerProperties> const layers = enumerate_device_layer_properties(physical_device);
    for(VkLayerProperties const &layer : layers)
    {
        device_layer_extensions.push_back(std::make_pair(layer, enumerate_device_layer_extension_properties(physical_device, layer)));
    }

    return device_layer_extensions;
}

// ====================================================================================================================
