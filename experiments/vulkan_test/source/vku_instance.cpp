#include "vku_instance.hpp"
#include "vku_utility.hpp"
#include <vector>
#include <utility>

// ====================================================================================================================

static std::vector<VkLayerProperties> enumerate_instance_layer_properties();
static std::vector<VkExtensionProperties> enumerate_instance_layer_extension_properties(VkLayerProperties const &layer);
static std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> enumerate_instance_all_layers_extension_properties();

// ====================================================================================================================
// Implementation
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
                               std::initializer_list<char const * const> const &requiredLayers,
                               std::initializer_list<char const * const> const &requiredExtensions,
                               std::initializer_list<char const * const> const &allowedExtensions)
{
    std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> const all_layers_extensions = enumerate_instance_all_layers_extension_properties();

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
            throw std::runtime_error(make_string({"vku::CreateInstance missing required layer (\"", required_layer, "\")"}));
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
            throw std::runtime_error(make_string({"vku::CreateInstance missing required extension (\"", required_extension, "\")"}));
        }
    }

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
        throw std::runtime_error(make_string({"error: vkGetInstanceProcAddr(\"", func_name, "\") returned nullptr"}));
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

/*static*/ std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> enumerate_instance_all_layers_extension_properties()
{
    std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> instance_layer_extensions;

    std::vector<VkLayerProperties> const layers = enumerate_instance_layer_properties();
    for(VkLayerProperties const &layer : layers)
    {
        instance_layer_extensions.push_back(std::make_pair(layer, enumerate_instance_layer_extension_properties(layer)));
    }

    return instance_layer_extensions;
}

// ====================================================================================================================
