#include "m1/game_platform.hpp"
#include "vulkan/vulkan.h"
#include <vector>
#include <iostream>


class VkScopedInstance
{
public:
    VkScopedInstance() = default;
    explicit VkScopedInstance(VkInstance inst);
    ~VkScopedInstance();

    explicit operator VkInstance() const;

private:
    VkScopedInstance(VkScopedInstance &&rhs) = delete;
    VkScopedInstance(VkScopedInstance const &rhs) = delete;
    VkScopedInstance& operator = (VkScopedInstance &&rhs) = delete;
    VkScopedInstance& operator = (VkScopedInstance const &rhs) = delete;

    // members:
    VkInstance m_VkInstance = nullptr;
};

namespace vk
{
   std::vector<VkLayerProperties> EnumerateInstanceLayerProperties();
   std::vector<VkExtensionProperties> EnumerateInstanceExtensionProperties(char const *layer_name);
}

VkInstance make_vk_instance(m1::game_platform const &game_platform);

int main()
{
    try
    {
        m1::game_platform g;

        VkScopedInstance const inst(make_vk_instance(g));
        return g.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred";
    }

    return 0;
}

#ifdef M1_GAME_PLATFORM_WINDOWS
#include "m1/platform_impl/windows/m1/game_platform_impl.hpp"
#endif

#include <stdexcept>

VkScopedInstance::VkScopedInstance(VkInstance inst)
    : m_VkInstance(inst)
{
}

VkScopedInstance::~VkScopedInstance()
{
    if(m_VkInstance != nullptr)
    {
        vkDestroyInstance(m_VkInstance, // pInstance
                          nullptr); // pAllocator
    }
}

/*explicit*/ VkScopedInstance::operator VkInstance() const
{
    return m_VkInstance;
}

std::vector<VkLayerProperties> vk::EnumerateInstanceLayerProperties()
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

    std::vector<VkLayerProperties> layer_properties(layer_count);
    switch(vkEnumerateInstanceLayerProperties(&layer_count,
                                              layer_properties.data()))
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

    return layer_properties;
}

std::vector<VkExtensionProperties> vk::EnumerateInstanceExtensionProperties(char const *layer_name)
{
    uint32_t extension_count = 0;
    switch (vkEnumerateInstanceExtensionProperties(layer_name,
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

    std::vector<VkExtensionProperties> extension_properties(extension_count);
    switch (vkEnumerateInstanceExtensionProperties(layer_name,
                                                   &extension_count,
                                                   extension_properties.data()))
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

    return extension_properties;
}

VkInstance make_vk_instance(m1::game_platform const &/*game_platform*/)
{
    VkApplicationInfo const app_info =
    {
        VK_STRUCTURE_TYPE_APPLICATION_INFO, // sType
        nullptr,                            // pNext
        "vulkan_test",                      // pApplicationName
        VK_MAKE_VERSION(0, 0, 0),           // applicationVersion
        "m1",                               // pEngineName
        VK_MAKE_VERSION(0, 0, 0),           // engineVersion
        VK_MAKE_VERSION(0, 0, 0),           // apiVersion
    };

    // extensions:
    std::initializer_list<char const * const> const extension_filter =
    {
        VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef VK_USE_PLATFORM_ANDROID_KHR
        VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#endif
#ifdef VK_USE_PLATFORM_MIR_KHR
        VK_KHR_MIR_SURFACE_EXTENSION_NAME,
#endif
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
        VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#endif
#ifdef VK_USE_PLATFORM_WIN32_KHR
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif
#ifdef VK_USE_PLATFORM_XLIB_KHR
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
#endif
#ifdef VK_USE_PLATFORM_XCB_KHR
        VK_KHR_XCB_SURFACE_EXTENSION_NAME,
#endif
    };

    std::vector<char const*> extension_names;
    {
       std::vector<VkExtensionProperties> const extension_properties = vk::EnumerateInstanceExtensionProperties(nullptr);
       for(VkExtensionProperties const &extension_property : extension_properties)
       {
          bool const use_extension = std::find_if(extension_filter.begin(),
                                                  extension_filter.end(),
                                                  [&](char const * const filter_entry)
                                                  {
                                                      return std::strcmp(filter_entry, extension_property.extensionName) == 0;
                                                  }) != extension_filter.end();
          if(use_extension)
          {
              extension_names.push_back(extension_property.extensionName);
          }
       }
    }

    // layers:
    std::vector<VkLayerProperties> const layer_properties = vk::EnumerateInstanceLayerProperties();
    std::vector<char const*> layer_names;
    layer_names.reserve(layer_properties.size());
    for(VkLayerProperties const &layer_property : layer_properties)
    {
       bool use_layer = false;

       std::vector<VkExtensionProperties> const extension_properties = vk::EnumerateInstanceExtensionProperties(layer_property.layerName);
       for(VkExtensionProperties const &extension_property : extension_properties)
       {
          bool const use_extension = std::find_if(extension_filter.begin(),
                                                  extension_filter.end(),
                                                  [&](char const * const filter_entry)
                                                  {
                                                      return std::strcmp(filter_entry, extension_property.extensionName) == 0;
                                                  }) != extension_filter.end();
          if(use_extension)
          {
              use_layer = true;
              extension_names.push_back(extension_property.extensionName);
          }
       }

       if(use_layer && (layer_property.layerName != nullptr))
       {
         layer_names.push_back(layer_property.layerName);
       }
    }

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

    //HWND const hwnd = g.get_platform_impl().window_handle;
    VkInstance inst = nullptr;
    switch(vkCreateInstance(&inst_create_info, // pCreateInfo
                            nullptr, // pAllocator
                            &inst)) // pInstance
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

    return inst;
}

