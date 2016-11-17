#ifndef VKU_EXTENSION_HPP
#define VKU_EXTENSION_HPP

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    struct LayerExtensionProperties
    {
        VkLayerProperties                  layerProperties;
        std::vector<VkExtensionProperties> extensionProperties;
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool HasRequiredLayersExtension(std::vector<LayerExtensionProperties> const &layerExtensionProperties,
                                    std::vector<std::string> const &requiredLayers,
                                    std::vector<std::string> const &requiredExtensions);

    // ----------------------------------------------------------------------------------------------------------------

    void AccumulateAllowedLayersExtensionsNames(std::vector<char const*> &resultLayerNames,
                                                std::vector<char const*> &resultExtensionNames,
                                                std::vector<LayerExtensionProperties> const &layerExtensionProperties,
                                                std::vector<std::string> const &requiredLayers,
                                                std::vector<std::string> const &allowedLayers,
                                                std::vector<std::string> const &requiredExtensions,
                                                std::vector<std::string> const &allowedExtensions);

    // ================================================================================================================
} // namespace vku

#endif // VKU_EXTENSION_HPP

