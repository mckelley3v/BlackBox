#ifndef VKU_HPP
#define VKU_HPP

#include "vkuInstance.hpp"
#include "vkuDevice.hpp"
#include "vkuSurface.hpp"

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    bool IsValidExtent(VkExtent2D const &extent2D);

    // ----------------------------------------------------------------------------------------------------------------

    VkExtent2D ClampExtent(VkExtent2D const &extent2D,
                           VkExtent2D const &minExtent2D,
                           VkExtent2D const &maxExtent2D);

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_HPP
