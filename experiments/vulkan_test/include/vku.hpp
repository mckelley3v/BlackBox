#ifndef VKU_HPP
#define VKU_HPP

#include "vkuCommandBuffers.hpp"
#include "vkuCore.hpp"
#include "vkuDevice.hpp"
#include "vkuExtension.hpp"
#include "vkuFramebuffer.hpp"
#include "vkuImage.hpp"
#include "vkuInstance.hpp"
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
