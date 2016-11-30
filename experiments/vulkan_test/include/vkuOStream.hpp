#ifndef VKU_OSTREAM_HPP
#define VKU_OSTREAM_HPP

#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <iosfwd>

// ====================================================================================================================

namespace vku
{
    struct LayerExtensionProperties;
}

// ====================================================================================================================

namespace vku
{
namespace iostream
{
    // ================================================================================================================

    constexpr char const indent_chars[] = "    ";

    int& indent_level();
    std::ostream& indent_push(std::ostream &out);
    std::ostream& indent_pop(std::ostream &out);
    std::ostream& indent(std::ostream &out);

    // ================================================================================================================

    std::string uuid_to_string(uint8_t const (&value)[VK_UUID_SIZE]);
    std::string queue_flags_to_string(VkQueueFlags const &value);

    // ================================================================================================================

    template <typename T>
    std::ostream& operator << (std::ostream &out, std::vector<T> const &values);
    std::ostream& operator << (std::ostream &out, VkPhysicalDevice const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceProperties const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceType const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceLimits const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceSparseProperties const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceFeatures const &value);
    std::ostream& operator << (std::ostream &out, LayerExtensionProperties const &value);
    std::ostream& operator << (std::ostream &out, VkLayerProperties const &value);
    std::ostream& operator << (std::ostream &out, VkExtensionProperties const &value);
    std::ostream& operator << (std::ostream &out, VkQueueFamilyProperties const &value);
    std::ostream& operator << (std::ostream &out, VkExtent3D const &value);

    // ================================================================================================================
} // namespace iostream
} // namespace vku

// ====================================================================================================================

template <typename T>
std::ostream& vku::iostream::operator << (std::ostream &out, std::vector<T> const &values)
{
    out << "\n";
    out << indent_push;
    for(T const &value : values)
    {
        out << indent << "-" << indent_chars << value << "\n";
    }
    out << indent_pop;

    return out;
}

// ====================================================================================================================

#endif // VKU_OSTREAM_HPP
