#ifndef VKU_M1_HPP
#define VKU_M1_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    class game_platform;

    // ================================================================================================================
}

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    char const* GetSurfaceExtensionName(m1::game_platform const &gamePlatform);

    // --------------------------------------------------------------------------------------------------------------------

    VkSurfaceKHR CreateSurfaceKHR(VkInstance instance,
                                  m1::game_platform const &gamePlatform);

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_M1_HPP
