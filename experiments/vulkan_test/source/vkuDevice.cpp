#include "vkuDevice.hpp"
#include "vkuInstance.hpp"
#include "vkuUtility.hpp"
#include <utility>
#include <cassert>

// ====================================================================================================================

static std::vector<VkLayerProperties> enumerate_device_layer_properties(vku::Instance const &instance,
                                                                        VkPhysicalDevice physical_device);

static std::vector<VkExtensionProperties> enumerate_device_layer_extension_properties(vku::Instance const &instance,
                                                                                      VkPhysicalDevice physical_device,
                                                                                      VkLayerProperties const &layer);

static std::vector<vku::PhysicalDeviceQueueFamilyCreateInfo> enumerate_selected_queue_families(vku::Instance const &instance,
                                                                                               VkPhysicalDevice physicalDevice,
                                                                                               std::vector<vku::PhysicalDeviceRequestedQueueProperties> const &requestedQueues);

// ====================================================================================================================

std::vector<VkPhysicalDevice> vku::EnumeratePhysicalDevices(Instance const &instance)
{
    uint32_t device_count = 0;
    switch(instance.vkEnumeratePhysicalDevices(instance,
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

    std::vector<VkPhysicalDevice> devices(device_count, VK_NULL_HANDLE);
    switch(instance.vkEnumeratePhysicalDevices(instance,
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

std::vector<VkQueueFamilyProperties> vku::GetPhysicalDeviceQueueFamilyProperties(Instance const &instance,
                                                                                 VkPhysicalDevice const physicalDevice)
{
    uint32_t family_property_count = 0;
    instance.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,
                                                      &family_property_count,
                                                      nullptr);

    std::vector<VkQueueFamilyProperties> family_properties(family_property_count);
    instance.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,
                                                      &family_property_count,
                                                      family_properties.data());

    return family_properties;
}

// ====================================================================================================================

std::vector<vku::LayerExtensionProperties> vku::EnumeratePhysicalDeviceLayersExtensionProperties(Instance const &instance,
                                                                                                 VkPhysicalDevice const physicalDevice)
{
    std::vector<LayerExtensionProperties> device_layer_extensions;
    std::vector<VkLayerProperties> const layers = enumerate_device_layer_properties(instance,
                                                                                    physicalDevice);
    device_layer_extensions.reserve(layers.size());

    for(VkLayerProperties const &layer : layers)
    {
        device_layer_extensions.push_back(LayerExtensionProperties{layer,
                                                                   enumerate_device_layer_extension_properties(instance,
                                                                                                               physicalDevice,
                                                                                                               layer)});
    }

    return device_layer_extensions;
};

// ====================================================================================================================

vku::SelectQueueFamilyWithFlags::SelectQueueFamilyWithFlags(VkQueueFlags const requiredQueueFlags)
    : m_RequiredQueueFlags(requiredQueueFlags)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::SelectQueueFamilyWithFlags::SelectQueueFamilyWithFlags(VkQueueFlags const requiredQueueFlags,
                                                            VkQueueFlags const allowedQueueFlags)
    : m_RequiredQueueFlags(requiredQueueFlags)
    , m_AllowedQueueFlags(allowedQueueFlags)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::SelectQueueFamilyWithFlags::operator () (VkPhysicalDevice const /*physicalDevice*/,
                                                   uint32_t const /*queueFamilyIndex*/,
                                                   VkQueueFamilyProperties const &queueFamilyProperties) const
{
    bool const has_required_queue_flags = (queueFamilyProperties.queueFlags & m_RequiredQueueFlags) ? true : false;
    bool const has_forbidden_queue_flags = (queueFamilyProperties.queueFlags & ~(m_AllowedQueueFlags | m_RequiredQueueFlags)) ? true : false;
    return has_required_queue_flags && !has_forbidden_queue_flags;
}

// ====================================================================================================================

vku::DeviceCreateInfo vku::CreateDeviceCreateInfo(Instance const &instance,
                                                  std::vector<PhysicalDeviceRequestedQueueProperties> const &requestedQueues,
                                                  std::vector<std::string> const &requiredLayers,
                                                  std::vector<std::string> const &allowedLayers,
                                                  std::vector<std::string> const &requiredExtensions,
                                                  std::vector<std::string> const &allowedExtensions)
{
    assert(!requestedQueues.empty());

    std::vector<VkPhysicalDevice> const physical_devices = EnumeratePhysicalDevices(instance);
    for(VkPhysicalDevice const &physical_device : physical_devices)
    {
        std::vector<LayerExtensionProperties> layer_extension_properties = EnumeratePhysicalDeviceLayersExtensionProperties(instance,
                                                                                                                            physical_device);
        if(HasRequiredLayersExtension(layer_extension_properties,
                                      requiredLayers,
                                      requiredExtensions))
        {
            std::vector<PhysicalDeviceQueueFamilyCreateInfo> selected_queue_families = enumerate_selected_queue_families(instance,
                                                                                                                         physical_device,
                                                                                                                         requestedQueues);
            if(!selected_queue_families.empty())
            {
                std::vector<char const*> layer_names;
                std::vector<char const*> extension_names;

                AccumulateAllowedLayersExtensionsNames(layer_names, // ref
                                                       extension_names, // ref
                                                       layer_extension_properties,
                                                       requiredLayers,
                                                       allowedLayers,
                                                       requiredExtensions,
                                                       allowedExtensions);

                return DeviceCreateInfo{physical_device,
                                        std::move(selected_queue_families),
                                        std::move(layer_extension_properties),
                                        std::move(layer_names),
                                        std::move(extension_names)};
            }
        }
    }

    throw std::runtime_error("error: vku::CreateDeviceCreateInfo unable to find physical device matching requirements");
}

// ====================================================================================================================

/*explicit*/ vku::Device::Device(Instance const &instance,
                                         VkDevice const device)
    : m_pfnDestroyDevice(instance.vkDestroyDevice.get())
    , m_pfnGetDeviceProcAddr(instance.vkGetDeviceProcAddr.get())
    , m_VkDevice(device)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::Device(Device &&rhs)
    : m_pfnDestroyDevice(rhs.m_pfnDestroyDevice)
    , m_pfnGetDeviceProcAddr(rhs.m_pfnGetDeviceProcAddr)
    , m_VkDevice(rhs.m_VkDevice)
{
    rhs.Reset();
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device& vku::Device::operator = (Device &&rhs)
{
    Release();

    m_pfnDestroyDevice = rhs.m_pfnDestroyDevice;
    m_pfnGetDeviceProcAddr = rhs.m_pfnGetDeviceProcAddr;
    m_VkDevice = rhs.m_VkDevice;

    rhs.Reset();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Device::~Device()
{
    Release();
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

// --------------------------------------------------------------------------------------------------------------------

PFN_vkVoidFunction vku::Device::GetDeviceProcAddr(char const *func_name) const
{
    if (m_pfnGetDeviceProcAddr != nullptr)
    {
        PFN_vkVoidFunction const func_ptr = m_pfnGetDeviceProcAddr(m_VkDevice, func_name);
        if(func_ptr == nullptr)
        {
            throw std::runtime_error(make_string("error: vkGetDeviceProcAddr(\"", func_name, "\") returned nullptr"));
        }

        return func_ptr;
    }

    return nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::Device::Release()
{
    if((m_pfnDestroyDevice != nullptr) &&
       (m_VkDevice != VK_NULL_HANDLE))
    {
        m_pfnDestroyDevice(m_VkDevice, // pDevice
                           nullptr); // pAllocator

        Reset();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void vku::Device::Reset()
{
    m_pfnDestroyDevice = nullptr;
    m_pfnGetDeviceProcAddr = nullptr;
    m_VkDevice = VK_NULL_HANDLE;
}

// ====================================================================================================================

VkDevice vku::CreateDevice(Instance const &instance,
                           DeviceCreateInfo const &createInfo)
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
    switch(instance.vkCreateDevice(createInfo.physicalDevice, // physicalDevice
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

/*static*/ std::vector<VkLayerProperties> enumerate_device_layer_properties(vku::Instance const &instance,
                                                                            VkPhysicalDevice const physical_device)
{
    uint32_t layer_count = 0;
    switch(instance.vkEnumerateDeviceLayerProperties(physical_device,
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
    switch(instance.vkEnumerateDeviceLayerProperties(physical_device,
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

/*static*/ std::vector<VkExtensionProperties> enumerate_device_layer_extension_properties(vku::Instance const &instance,
                                                                                          VkPhysicalDevice const physical_device,
                                                                                          VkLayerProperties const &layer)
{
    char const * const layerName = (layer.layerName[0] != '\0') ? layer.layerName : nullptr;

    uint32_t extension_count = 0;
    switch(instance.vkEnumerateDeviceExtensionProperties(physical_device,
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
    switch(instance.vkEnumerateDeviceExtensionProperties(physical_device,
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

/*static*/ std::vector<vku::PhysicalDeviceQueueFamilyCreateInfo> enumerate_selected_queue_families(vku::Instance const &instance,
                                                                                                   VkPhysicalDevice const physicalDevice,
                                                                                                   std::vector<vku::PhysicalDeviceRequestedQueueProperties> const &requestedQueues)
{
    std::vector<vku::PhysicalDeviceQueueFamilyCreateInfo> selected_queue_families;

    std::vector<VkQueueFamilyProperties> const queue_families_properties = vku::GetPhysicalDeviceQueueFamilyProperties(instance, physicalDevice);
    uint32_t const queue_family_count = static_cast<uint32_t>(queue_families_properties.size());

    for(vku::PhysicalDeviceRequestedQueueProperties const &requested_queue : requestedQueues)
    {
        bool const is_required_queue = (requested_queue.requiredEnableCount > 0);

        bool found_requested_queue = false;
        for(uint32_t family_index = 0; family_index < queue_family_count; ++family_index)
        {
            VkQueueFamilyProperties const &family_properties = queue_families_properties[family_index];
            bool const has_enough_queues = family_properties.queueCount >= requested_queue.requiredEnableCount;
            if(has_enough_queues)
            {
                if(requested_queue.selectQueueFamilyFunc(physicalDevice, family_index, family_properties))
                {
                    uint32_t const selected_queue_count = std::min(family_properties.queueCount, requested_queue.allowedEnableCount);

                    found_requested_queue = true;
                    selected_queue_families.push_back(vku::PhysicalDeviceQueueFamilyCreateInfo{family_properties,
                                                                                               family_index,
                                                                                               std::vector<float>(selected_queue_count, requested_queue.defaultPriority)});
                    break;
                }
            }
        }

        if(is_required_queue && !found_requested_queue)
        {
            return std::vector<vku::PhysicalDeviceQueueFamilyCreateInfo>();
        }
    }

    return selected_queue_families;
}

// ====================================================================================================================
