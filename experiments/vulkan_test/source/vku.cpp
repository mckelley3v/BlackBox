#include "vku.hpp"
#include <algorithm>

// ====================================================================================================================

bool vku::IsValidExtent(VkExtent2D const &extent2D)
{
    uint32_t const invalidSize = 0xFFFFFFFFu;
    return (extent2D.width != invalidSize) && (extent2D.height != invalidSize);
}

// ====================================================================================================================

VkExtent2D vku::ClampExtent(VkExtent2D const &extent2D,
                            VkExtent2D const &minExtent2D,
                            VkExtent2D const &maxExtent2D)
{
    uint32_t const w = std::min(std::max(extent2D.width, minExtent2D.width), maxExtent2D.width);
    uint32_t const h = std::min(std::max(extent2D.width, minExtent2D.width), maxExtent2D.width);
    return VkExtent2D {w, h};
}

// ====================================================================================================================
