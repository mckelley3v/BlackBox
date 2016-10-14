#include "vku_instance.hpp"
#include "vku_utility.hpp"
#include <utility>

// ====================================================================================================================

static std::vector<VkLayerProperties> enumerate_instance_layer_properties();
static std::vector<VkExtensionProperties> enumerate_instance_layer_extension_properties(VkLayerProperties const &layer);

// ====================================================================================================================

std::vector<vku::LayerExtensionProperties> vku::EnumerateInstanceLayersExtensionProperties()
{
    std::vector<LayerExtensionProperties> instance_layer_extensions;
    std::vector<VkLayerProperties> const layers = enumerate_instance_layer_properties();
    instance_layer_extensions.reserve(layers.size());

    for(VkLayerProperties const &layer : layers)
    {
        instance_layer_extensions.push_back(LayerExtensionProperties{layer, enumerate_instance_layer_extension_properties(layer)});
    }

    return instance_layer_extensions;
}

// ====================================================================================================================

vku::Instance::Instance(VkInstance const instance)
    : m_VkInstance(instance)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Instance::Instance(Instance &&rhs)
    : m_VkInstance(rhs.m_VkInstance)
{
    rhs.m_VkInstance = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Instance& vku::Instance::operator = (Instance &&rhs)
{
    m_VkInstance = rhs.m_VkInstance;
    rhs.m_VkInstance = VK_NULL_HANDLE;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Instance::~Instance()
{
    if(m_VkInstance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(m_VkInstance, // pInstance
                          nullptr); // pAllocator
    }
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::Instance::operator bool() const
{
    return m_VkInstance != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Instance::operator VkInstance() const
{
    return m_VkInstance;
}

// ====================================================================================================================

VkInstance vku::CreateInstance(ApplicationInfo const &appInfo,
                               std::vector<std::string> const &requiredLayers,
                               std::vector<std::string> const &allowedLayers,
                               std::vector<std::string> const &requiredExtensions,
                               std::vector<std::string> const &allowedExtensions)
{
    std::vector<LayerExtensionProperties> const layer_extension_properties = EnumerateInstanceLayersExtensionProperties();
    if(!HasRequiredLayersExtension(layer_extension_properties,
                                   requiredLayers,
                                   requiredExtensions))
    {
        throw std::runtime_error("vku::CreateInstance missing required layer/extension");
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

    // create instance:
    VkApplicationInfo const app_info =
    {
        VK_STRUCTURE_TYPE_APPLICATION_INFO, // sType
        nullptr,                            // pNext
        appInfo.pApplicationName,           // pApplicationName
        appInfo.applicationVersion,         // applicationVersion
        appInfo.pEngineName,                // pEngineName
        appInfo.engineVersion,              // engineVersion
        appInfo.apiVersion,                 // apiVersion
    };

    VkInstanceCreateInfo const inst_create_info =
    {
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,        // sType,
        nullptr,                                       // pNext
        0,                                             // flags
        &app_info,                                     // pApplicationInfo
        static_cast<uint32_t>(layer_names.size()),     // enabledLayerCount
        layer_names.data(),                            // ppEnabledLayerNames
        static_cast<uint32_t>(extension_names.size()), // enabledExtensionCount
        extension_names.data(),                        // ppEnabledExtensionNames
    };

    VkInstance instance = VK_NULL_HANDLE;
    switch(vkCreateInstance(&inst_create_info, // pCreateInfo
                            nullptr, // pAllocator
                            &instance)) // pInstance
    {
        case VK_SUCCESS:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkCreateInstance returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkCreateInstance returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_INITIALIZATION_FAILED:
            throw std::runtime_error("error: vkCreateInstance returned VK_ERROR_INITIALIZATION_FAILED");

        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("error: vkCreateInstance returned VK_ERROR_LAYER_NOT_PRESENT");

        case VK_ERROR_EXTENSION_NOT_PRESENT:
            throw std::runtime_error("error: vkCreateInstance returned VK_ERROR_EXTENSION_NOT_PRESENT");

        case VK_ERROR_INCOMPATIBLE_DRIVER:
            throw std::runtime_error("error: vkCreateInstance returned VK_ERROR_INCOMPATIBLE_DRIVER");

        default:
            throw std::runtime_error("error: vkCreateInstance returned unknown error");
    };

    return instance;
}

// ====================================================================================================================

vku::InstanceProcBase::InstanceProcBase(VkInstance const instance,
                                        char const * const func_name)
    : m_FuncPtr(vkGetInstanceProcAddr(instance, func_name))
{
    if(m_FuncPtr == nullptr)
    {
        throw std::runtime_error(make_string("error: vkGetInstanceProcAddr(\"", func_name, "\") returned nullptr"));
    }
}

// ====================================================================================================================

/*static*/ std::vector<VkLayerProperties> enumerate_instance_layer_properties()
{
    uint32_t layer_count = 0;
    switch(vkEnumerateInstanceLayerProperties(&layer_count,
                                              nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned unknown error");
    }

    // add 1 for unnamed implicit layer
    std::vector<VkLayerProperties> layer_properties(layer_count + 1, VkLayerProperties());
    switch(vkEnumerateInstanceLayerProperties(&layer_count,
                                              layer_properties.data() + 1))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkEnumerateInstanceLayerProperties returned unknown error");
    }

    return layer_properties;
}

// ====================================================================================================================

/*static*/ std::vector<VkExtensionProperties> enumerate_instance_layer_extension_properties(VkLayerProperties const &layer)
{
    uint32_t extension_count = 0;
    switch(vkEnumerateInstanceExtensionProperties((layer.layerName[0] != '\0') ? layer.layerName : nullptr,
                                                  &extension_count,
                                                  nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_ERROR_LAYER_NOT_PRESENT");

        default:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned unknown error");
    }

    std::vector<VkExtensionProperties> layer_extension_properties(extension_count, VkExtensionProperties());
    switch(vkEnumerateInstanceExtensionProperties((layer.layerName[0] != '\0') ? layer.layerName : nullptr,
                                                  &extension_count,
                                                  layer_extension_properties.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_LAYER_NOT_PRESENT:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned VK_ERROR_LAYER_NOT_PRESENT");

        default:
            throw std::runtime_error("error: vkEnumerateInstanceExtensionProperties returned unknown error");
    }

    return layer_extension_properties;
}

// ====================================================================================================================
