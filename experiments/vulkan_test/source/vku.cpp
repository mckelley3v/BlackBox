#include "vku.hpp"
#include <string>
#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <cassert>

// ====================================================================================================================

class c_str_compare_to
{
public:
    explicit c_str_compare_to(char const *lhs);

    bool operator() (char const *rhs) const;

private:
    // members:
    char const * const m_Lhs = nullptr;
};

// ====================================================================================================================

class vku_name_compare_to
{
public:
    explicit vku_name_compare_to(char const *lhs);

    bool operator() (char const *rhs) const;

private:
    // members:
    char const * const m_Lhs = nullptr;
};

// ====================================================================================================================

static bool c_str_equal(char const *lhs, char const *rhs);

// ====================================================================================================================

template <typename Itr,
          typename End,
          typename Pred>
static bool contains(Itr itr, End end, Pred pred);

// ====================================================================================================================

static std::vector<VkLayerProperties> enumerate_instance_layer_properties();
// ====================================================================================================================

static std::vector<VkExtensionProperties> enumerate_instance_layer_extension_properties(VkLayerProperties const &layer);
// ====================================================================================================================

static std::vector<std::pair<VkLayerProperties, std::vector<VkExtensionProperties>>> enumerate_instance_all_layers_extension_properties();

// ====================================================================================================================

namespace vku
{
namespace iostream
{
    // ================================================================================================================

    int& indent_level();
    std::ostream& indent_push(std::ostream &out);
    std::ostream& indent_pop(std::ostream &out);
    std::ostream& indent(std::ostream &out);

    // ================================================================================================================

    template <typename T> struct type_tag {};

    // ================================================================================================================

    std::string to_string(type_tag<VkQueueFlagBits>, VkQueueFlags const &value);

    // ================================================================================================================

    template <std::size_t N>
    static std::ostream& operator << (std::ostream &out, uint32_t const (&values)[N]);

    // ================================================================================================================
} // namespace iostream
} // namespace vku

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
                               std::initializer_list<char const * const> const &allowedLayers,
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

        bool const allow_layer = contains(requiredLayers.begin(),
                                          requiredLayers.end(),
                                          c_str_compare_to(layer.layerName)) ||
                                 contains(allowedLayers.begin(),
                                          allowedLayers.end(),
                                          vku_name_compare_to(layer.layerName));
        if(!allow_layer) continue;

        bool use_layer = false;
        for(VkExtensionProperties const &extension : layer_extensions)
        {
            bool const allow_extension = contains(requiredExtensions.begin(),
                                                  requiredExtensions.end(),
                                                  c_str_compare_to(extension.extensionName)) ||
                                         contains(allowedExtensions.begin(),
                                                  allowedExtensions.end(),
                                                  vku_name_compare_to(extension.extensionName));
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
            throw std::runtime_error(std::string("vku::CreateInstance missing required layer: ") + std::string(required_layer));
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
            throw std::runtime_error(std::string("vku::CreateInstance missing required extension: ") + std::string(required_extension));
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

    VkInstance instance = nullptr;
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
// Private Implementation
// ====================================================================================================================

int& vku::iostream::indent_level()
{
   static int s_IndentLevel = 0;
   return s_IndentLevel;
}

// ====================================================================================================================

std::ostream& vku::iostream::indent_push(std::ostream &out)
{
   ++indent_level();
   return out;
};

// ====================================================================================================================

std::ostream& vku::iostream::indent_pop(std::ostream &out)
{
   --indent_level();
   return out;
};

// ====================================================================================================================

std::ostream& vku::iostream::indent(std::ostream &out)
{
   int const n = indent_level();
   for(int i = 0; i < n; ++i)
   {
      out.put('\t');
   }

   return out;
}

// ====================================================================================================================

c_str_compare_to::c_str_compare_to(char const * const lhs)
    : m_Lhs(lhs)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool c_str_compare_to::operator() (char const * const rhs) const
{
    return c_str_equal(m_Lhs, rhs);
}

// ====================================================================================================================

vku_name_compare_to::vku_name_compare_to(char const * const lhs)
    : m_Lhs(lhs)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku_name_compare_to::operator() (char const * const rhs) const
{
    return c_str_equal(m_Lhs, rhs) || c_str_equal("*", m_Lhs) || c_str_equal("*", rhs);
}

// ====================================================================================================================

/*static*/ bool c_str_equal(char const *lhs, char const *rhs)
{
    return std::strcmp(lhs, rhs) == 0;
}

// ====================================================================================================================

template <typename Itr,
          typename End,
          typename Pred>
/*static*/ bool contains(Itr itr, End end, Pred pred)
{
    return std::find_if(itr, end, pred) != end;
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

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceProperties const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "apiVersion:        " << VK_VERSION_MAJOR(value.apiVersion)    << "." << VK_VERSION_MINOR(value.apiVersion)    << "." << VK_VERSION_PATCH(value.apiVersion)    << "\n";
    out << indent << "driverVersion:     " << VK_VERSION_MAJOR(value.driverVersion) << "." << VK_VERSION_MINOR(value.driverVersion) << "." << VK_VERSION_PATCH(value.driverVersion) << "\n";
    out << indent << "vendorID:          " << value.vendorID          << "\n";
    out << indent << "deviceID:          " << value.deviceID          << "\n";
    out << indent << "deviceType:        " << value.deviceType        << "\n";
    out << indent << "deviceName:        " << value.deviceName        << "\n";
    out << indent << "pipelineCacheUUID: " << value.pipelineCacheUUID << "\n";
    out << indent << "limits:            " << value.limits            << "\n";
    out << indent << "sparseProperties:  " << value.sparseProperties  << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceType const &value)
{
    switch(value)
    {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return out << "VK_PHYSICAL_DEVICE_TYPE_OTHER";

        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU";

        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU";

        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU";

        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return out << "VK_PHYSICAL_DEVICE_TYPE_CPU";

        default:
            return out;
    }
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceLimits const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "maxImageDimension1D:                             " << value.maxImageDimension1D << "\n";
    out << indent << "maxImageDimension2D:                             " << value.maxImageDimension2D << "\n";
    out << indent << "maxImageDimension3D:                             " << value.maxImageDimension3D << "\n";
    out << indent << "maxImageDimensionCube:                           " << value.maxImageDimensionCube << "\n";
    out << indent << "maxImageArrayLayers:                             " << value.maxImageArrayLayers << "\n";
    out << indent << "maxTexelBufferElements:                          " << value.maxTexelBufferElements << "\n";
    out << indent << "maxUniformBufferRange:                           " << value.maxUniformBufferRange << "\n";
    out << indent << "maxStorageBufferRange:                           " << value.maxStorageBufferRange << "\n";
    out << indent << "maxPushConstantsSize:                            " << value.maxPushConstantsSize << "\n";
    out << indent << "maxMemoryAllocationCount:                        " << value.maxMemoryAllocationCount << "\n";
    out << indent << "maxSamplerAllocationCount:                       " << value.maxSamplerAllocationCount << "\n";
    out << indent << "bufferImageGranularity:                          " << value.bufferImageGranularity << "\n";
    out << indent << "sparseAddressSpaceSize:                          " << value.sparseAddressSpaceSize << "\n";
    out << indent << "maxBoundDescriptorSets:                          " << value.maxBoundDescriptorSets << "\n";
    out << indent << "maxPerStageDescriptorSamplers:                   " << value.maxPerStageDescriptorSamplers << "\n";
    out << indent << "maxPerStageDescriptorUniformBuffers:             " << value.maxPerStageDescriptorUniformBuffers << "\n";
    out << indent << "maxPerStageDescriptorStorageBuffers:             " << value.maxPerStageDescriptorStorageBuffers << "\n";
    out << indent << "maxPerStageDescriptorSampledImages:              " << value.maxPerStageDescriptorSampledImages << "\n";
    out << indent << "maxPerStageDescriptorStorageImages:              " << value.maxPerStageDescriptorStorageImages << "\n";
    out << indent << "maxPerStageDescriptorInputAttachments:           " << value.maxPerStageDescriptorInputAttachments << "\n";
    out << indent << "maxPerStageResources:                            " << value.maxPerStageResources << "\n";
    out << indent << "maxDescriptorSetSamplers:                        " << value.maxDescriptorSetSamplers << "\n";
    out << indent << "maxDescriptorSetUniformBuffers:                  " << value.maxDescriptorSetUniformBuffers << "\n";
    out << indent << "maxDescriptorSetUniformBuffersDynamic:           " << value.maxDescriptorSetUniformBuffersDynamic << "\n";
    out << indent << "maxDescriptorSetStorageBuffers:                  " << value.maxDescriptorSetStorageBuffers << "\n";
    out << indent << "maxDescriptorSetStorageBuffersDynamic:           " << value.maxDescriptorSetStorageBuffersDynamic << "\n";
    out << indent << "maxDescriptorSetSampledImages:                   " << value.maxDescriptorSetSampledImages << "\n";
    out << indent << "maxDescriptorSetStorageImages:                   " << value.maxDescriptorSetStorageImages << "\n";
    out << indent << "maxDescriptorSetInputAttachments:                " << value.maxDescriptorSetInputAttachments << "\n";
    out << indent << "maxVertexInputAttributes:                        " << value.maxVertexInputAttributes << "\n";
    out << indent << "maxVertexInputBindings:                          " << value.maxVertexInputBindings << "\n";
    out << indent << "maxVertexInputAttributeOffset:                   " << value.maxVertexInputAttributeOffset << "\n";
    out << indent << "maxVertexInputBindingStride:                     " << value.maxVertexInputBindingStride << "\n";
    out << indent << "maxVertexOutputComponents:                       " << value.maxVertexOutputComponents << "\n";
    out << indent << "maxTessellationGenerationLevel:                  " << value.maxTessellationGenerationLevel << "\n";
    out << indent << "maxTessellationPatchSize:                        " << value.maxTessellationPatchSize << "\n";
    out << indent << "maxTessellationControlPerVertexInputComponents:  " << value.maxTessellationControlPerVertexInputComponents << "\n";
    out << indent << "maxTessellationControlPerVertexOutputComponents: " << value.maxTessellationControlPerVertexOutputComponents << "\n";
    out << indent << "maxTessellationControlPerPatchOutputComponents:  " << value.maxTessellationControlPerPatchOutputComponents << "\n";
    out << indent << "maxTessellationControlTotalOutputComponents:     " << value.maxTessellationControlTotalOutputComponents << "\n";
    out << indent << "maxTessellationEvaluationInputComponents:        " << value.maxTessellationEvaluationInputComponents << "\n";
    out << indent << "maxTessellationEvaluationOutputComponents:       " << value.maxTessellationEvaluationOutputComponents << "\n";
    out << indent << "maxGeometryShaderInvocations:                    " << value.maxGeometryShaderInvocations << "\n";
    out << indent << "maxGeometryInputComponents:                      " << value.maxGeometryInputComponents << "\n";
    out << indent << "maxGeometryOutputComponents:                     " << value.maxGeometryOutputComponents << "\n";
    out << indent << "maxGeometryOutputVertices:                       " << value.maxGeometryOutputVertices << "\n";
    out << indent << "maxGeometryTotalOutputComponents:                " << value.maxGeometryTotalOutputComponents << "\n";
    out << indent << "maxFragmentInputComponents:                      " << value.maxFragmentInputComponents << "\n";
    out << indent << "maxFragmentOutputAttachments:                    " << value.maxFragmentOutputAttachments << "\n";
    out << indent << "maxFragmentDualSrcAttachments:                   " << value.maxFragmentDualSrcAttachments << "\n";
    out << indent << "maxFragmentCombinedOutputResources:              " << value.maxFragmentCombinedOutputResources << "\n";
    out << indent << "maxComputeSharedMemorySize:                      " << value.maxComputeSharedMemorySize << "\n";
    out << indent << "maxComputeWorkGroupCount:                        " << value.maxComputeWorkGroupCount << "\n";
    out << indent << "maxComputeWorkGroupInvocations:                  " << value.maxComputeWorkGroupInvocations << "\n";
    out << indent << "maxComputeWorkGroupSize:                         " << value.maxComputeWorkGroupSize << "\n";
    out << indent << "subPixelPrecisionBits:                           " << value.subPixelPrecisionBits << "\n";
    out << indent << "subTexelPrecisionBits:                           " << value.subTexelPrecisionBits << "\n";
    out << indent << "mipmapPrecisionBits:                             " << value.mipmapPrecisionBits << "\n";
    out << indent << "maxDrawIndexedIndexValue:                        " << value.maxDrawIndexedIndexValue << "\n";
    out << indent << "maxDrawIndirectCount:                            " << value.maxDrawIndirectCount << "\n";
    out << indent << "maxSamplerLodBias:                               " << value.maxSamplerLodBias << "\n";
    out << indent << "maxSamplerAnisotropy:                            " << value.maxSamplerAnisotropy << "\n";
    out << indent << "maxViewports:                                    " << value.maxViewports << "\n";
    out << indent << "maxViewportDimensions:                           " << value.maxViewportDimensions << "\n";
    out << indent << "viewportBoundsRange:                             " << value.viewportBoundsRange << "\n";
    out << indent << "viewportSubPixelBits:                            " << value.viewportSubPixelBits << "\n";
    out << indent << "minMemoryMapAlignment:                           " << value.minMemoryMapAlignment << "\n";
    out << indent << "minTexelBufferOffsetAlignment:                   " << value.minTexelBufferOffsetAlignment << "\n";
    out << indent << "minUniformBufferOffsetAlignment:                 " << value.minUniformBufferOffsetAlignment << "\n";
    out << indent << "minStorageBufferOffsetAlignment:                 " << value.minStorageBufferOffsetAlignment << "\n";
    out << indent << "minTexelOffset:                                  " << value.minTexelOffset << "\n";
    out << indent << "maxTexelOffset:                                  " << value.maxTexelOffset << "\n";
    out << indent << "minTexelGatherOffset:                            " << value.minTexelGatherOffset << "\n";
    out << indent << "maxTexelGatherOffset:                            " << value.maxTexelGatherOffset << "\n";
    out << indent << "minInterpolationOffset:                          " << value.minInterpolationOffset << "\n";
    out << indent << "maxInterpolationOffset:                          " << value.maxInterpolationOffset << "\n";
    out << indent << "subPixelInterpolationOffsetBits:                 " << value.subPixelInterpolationOffsetBits << "\n";
    out << indent << "maxFramebufferWidth:                             " << value.maxFramebufferWidth << "\n";
    out << indent << "maxFramebufferHeight:                            " << value.maxFramebufferHeight << "\n";
    out << indent << "maxFramebufferLayers:                            " << value.maxFramebufferLayers << "\n";
    out << indent << "framebufferColorSampleCounts:                    " << value.framebufferColorSampleCounts << "\n";
    out << indent << "framebufferDepthSampleCounts:                    " << value.framebufferDepthSampleCounts << "\n";
    out << indent << "framebufferStencilSampleCounts:                  " << value.framebufferStencilSampleCounts << "\n";
    out << indent << "framebufferNoAttachmentsSampleCounts:            " << value.framebufferNoAttachmentsSampleCounts << "\n";
    out << indent << "maxColorAttachments:                             " << value.maxColorAttachments << "\n";
    out << indent << "sampledImageColorSampleCounts:                   " << value.sampledImageColorSampleCounts << "\n";
    out << indent << "sampledImageIntegerSampleCounts:                 " << value.sampledImageIntegerSampleCounts << "\n";
    out << indent << "sampledImageDepthSampleCounts:                   " << value.sampledImageDepthSampleCounts << "\n";
    out << indent << "sampledImageStencilSampleCounts:                 " << value.sampledImageStencilSampleCounts << "\n";
    out << indent << "storageImageSampleCounts:                        " << value.storageImageSampleCounts << "\n";
    out << indent << "maxSampleMaskWords:                              " << value.maxSampleMaskWords << "\n";
    out << indent << "timestampComputeAndGraphics:                     " << value.timestampComputeAndGraphics << "\n";
    out << indent << "timestampPeriod:                                 " << value.timestampPeriod << "\n";
    out << indent << "maxClipDistances:                                " << value.maxClipDistances << "\n";
    out << indent << "maxCullDistances:                                " << value.maxCullDistances << "\n";
    out << indent << "maxCombinedClipAndCullDistances:                 " << value.maxCombinedClipAndCullDistances << "\n";
    out << indent << "discreteQueuePriorities:                         " << value.discreteQueuePriorities << "\n";
    out << indent << "pointSizeRange:                                  " << value.pointSizeRange << "\n";
    out << indent << "lineWidthRange:                                  " << value.lineWidthRange << "\n";
    out << indent << "pointSizeGranularity:                            " << value.pointSizeGranularity << "\n";
    out << indent << "lineWidthGranularity:                            " << value.lineWidthGranularity << "\n";
    out << indent << "strictLines:                                     " << value.strictLines << "\n";
    out << indent << "standardSampleLocations:                         " << value.standardSampleLocations << "\n";
    out << indent << "optimalBufferCopyOffsetAlignment:                " << value.optimalBufferCopyOffsetAlignment << "\n";
    out << indent << "optimalBufferCopyRowPitchAlignment:              " << value.optimalBufferCopyRowPitchAlignment << "\n";
    out << indent << "nonCoherentAtomSize:                             " << value.nonCoherentAtomSize << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkPhysicalDeviceSparseProperties const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "residencyStandard2DBlockShape:            " << value.residencyStandard2DBlockShape << "\n";
    out << indent << "residencyStandard2DMultisampleBlockShape: " << value.residencyStandard2DMultisampleBlockShape << "\n";
    out << indent << "residencyStandard3DBlockShape:            " << value.residencyStandard3DBlockShape << "\n";
    out << indent << "residencyAlignedMipSize:                  " << value.residencyAlignedMipSize << "\n";
    out << indent << "residencyNonResidentStrict:               " << value.residencyNonResidentStrict << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkQueueFamilyProperties const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "queueFlags:                  " << to_string(type_tag<VkQueueFlagBits>(), value.queueFlags) << "\n";
    out << indent << "queueCount:                  " << value.queueCount << "\n";
    out << indent << "timestampValidBits:          " << value.timestampValidBits << "\n";
    out << indent << "minImageTransferGranularity: " << value.minImageTransferGranularity << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

std::string vku::iostream::to_string(type_tag<VkQueueFlagBits>, VkQueueFlags const &value)
{
   std::string result;

   if(value)
   {
      char const *prefix = "";
      if(value & VK_QUEUE_GRAPHICS_BIT)
      {
         result += prefix;
         result += "VK_QUEUE_GRAPHICS_BIT";
         prefix = " | ";
      }

      if(value & VK_QUEUE_COMPUTE_BIT)
      {
         result += prefix;
         result += "VK_QUEUE_COMPUTE_BIT";
         prefix = " | ";
      }

      if(value & VK_QUEUE_TRANSFER_BIT)
      {
         result += prefix;
         result += "VK_QUEUE_TRANSFER_BIT";
         prefix = " | ";
      }

      if(value & VK_QUEUE_SPARSE_BINDING_BIT)
      {
         result += prefix;
         result += "VK_QUEUE_SPARSE_BINDING_BIT";
         prefix = " | ";
      }
   }
   else
   {
      result = "0";
   }

   return result;
}

// ====================================================================================================================

std::ostream& vku::iostream::operator << (std::ostream &out, VkExtent3D const &value)
{
    out << "\n";
    out << indent_push;
    out << indent << "width:  " << value.width << "\n";
    out << indent << "height: " << value.height << "\n";
    out << indent << "depth:  " << value.depth << "\n";
    out << indent_pop;
    return out;
}

// ====================================================================================================================

template <std::size_t N>
/*static*/ std::ostream& vku::iostream::operator << (std::ostream &out, uint32_t const (&values)[N])
{
    out << "\n";
    out << indent_push;
    for(uint32_t const &value : values)
    {
        out << indent << "-\t" << value << "\n";
    }
    out << indent_pop;

    return out;
}

// ====================================================================================================================
