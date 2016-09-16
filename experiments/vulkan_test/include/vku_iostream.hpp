#ifndef VKU_IOSTREAM_HPP
#define VKU_IOSTREAM_HPP

#include <vulkan/vulkan.h>
#include <string>
#include <iosfwd>

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

    std::string uuid_to_string(uint8_t const (&value)[VK_UUID_SIZE]);
    std::string queue_flags_to_string(VkQueueFlags const &value);

    // ================================================================================================================

    template <std::size_t N>
    std::ostream& operator << (std::ostream &out, uint32_t const (&values)[N]);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceProperties const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceType const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceLimits const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceSparseProperties const &value);
    std::ostream& operator << (std::ostream &out, VkPhysicalDeviceFeatures const &value);
    std::ostream& operator << (std::ostream &out, VkQueueFamilyProperties const &value);
    std::ostream& operator << (std::ostream &out, VkExtent3D const &value);

    // ================================================================================================================
} // namespace iostream
} // namespace vku

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

#endif // VKU_IOSTREAM_HPP
