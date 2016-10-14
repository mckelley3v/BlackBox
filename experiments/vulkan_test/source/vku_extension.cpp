#include "vku_extension.hpp"
#include "vku_utility.hpp"
#include <cstring>

// ====================================================================================================================

namespace
{
    // ================================================================================================================

    struct c_str_compare_sort
    {
        bool operator () (char const * const lhs, char const * const rhs) const
        {
            return std::strcmp(lhs, rhs) < 0;
        }
    };

    // ================================================================================================================

    struct c_str_compare_equal
    {
        bool operator () (char const * const lhs, char const * const rhs) const
        {
            return std::strcmp(lhs, rhs) == 0;
        }
    };

    // ================================================================================================================
}

template <typename Container,
          typename CompareSort,
          typename CompareEqual>
static void sort_unique_erase(Container &c,
                              CompareSort compSort,
                              CompareEqual compEqual)
{
    using std::begin;
    using std::end;
    using std::sort;
    using std::unique;

    sort(begin(c),
         end(c),
         compSort);

    c.erase(unique(begin(c),
                   end(c),
                   compEqual),
            end(c));
}

// ====================================================================================================================

bool vku::HasRequiredLayersExtension(std::vector<LayerExtensionProperties> const &layerExtensionProperties,
                                     std::vector<std::string> const &requiredLayers,
                                     std::vector<std::string> const &requiredExtensions)
{
    for(std::string const &required_layer_name : requiredLayers)
    {
        if(!contains_if(layerExtensionProperties.begin(),
                        layerExtensionProperties.end(),
                        [&](LayerExtensionProperties const &layer_extension)
                        {
                            return layer_extension.layerProperties.layerName == required_layer_name;
                        }))
        {
            return false;
        }
    }

    for(std::string const &required_extension_name : requiredExtensions)
    {
        if(!contains_if(layerExtensionProperties.begin(),
                        layerExtensionProperties.end(),
                        [&](LayerExtensionProperties const &layer_extension)
                        {
                            return contains_if(layer_extension.extensionProperties.begin(),
                                               layer_extension.extensionProperties.end(),
                                               [&](VkExtensionProperties const &extension)
                                               {
                                                   return extension.extensionName == required_extension_name;
                                               });
                        }))
        {
            return false;
        }
    }

    return true;
}

// ====================================================================================================================

void vku::AccumulateAllowedLayersExtensionsNames(std::vector<char const*> &resultLayerNames,
                                                 std::vector<char const*> &resultExtensionNames,
                                                 std::vector<LayerExtensionProperties> const &layerExtensionProperties,
                                                 std::vector<std::string> const &requiredLayers,
                                                 std::vector<std::string> const &allowedLayers,
                                                 std::vector<std::string> const &requiredExtensions,
                                                 std::vector<std::string> const &allowedExtensions)
{
    bool const allLayersAllowed = (allowedLayers.size() == 1) && (allowedLayers.front() == "*");
    bool const allExtensionsAllowed = (allowedExtensions.size() == 1) && (allowedExtensions.front() == "*");

    for(LayerExtensionProperties const &layer_extensions_entry : layerExtensionProperties)
    {
        VkLayerProperties const &layer = layer_extensions_entry.layerProperties;
        std::vector<VkExtensionProperties> const &layer_extensions = layer_extensions_entry.extensionProperties;

        bool use_layer = allLayersAllowed ||
                         contains(requiredLayers.begin(),
                                  requiredLayers.end(),
                                  layer.layerName) ||
                         contains(allowedLayers.begin(),
                                  allowedLayers.end(),
                                  layer.layerName);

        for(VkExtensionProperties const &extension : layer_extensions)
        {
            bool const allow_extension = allExtensionsAllowed ||
                                         contains(requiredExtensions.begin(),
                                                  requiredExtensions.end(),
                                                  extension.extensionName) ||
                                         contains(allowedExtensions.begin(),
                                                  allowedExtensions.end(),
                                                  extension.extensionName);
            if(allow_extension)
            {
                use_layer = true;
                resultExtensionNames.push_back(extension.extensionName);
            }
        }

        if(use_layer && (layer.layerName[0] != '\0'))
        {
            resultLayerNames.push_back(layer.layerName);
        }
    }

    sort_unique_erase(resultLayerNames,
                      c_str_compare_sort(),
                      c_str_compare_equal());

    sort_unique_erase(resultExtensionNames,
                      c_str_compare_sort(),
                      c_str_compare_equal());
}

// ====================================================================================================================
