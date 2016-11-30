#ifndef VKU_IMAGE_HPP
#define VKU_IMAGE_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class ImageView
    {
    public:
        ImageView() = default;
        explicit ImageView(VkDevice device,
                           VkImageView imageView);
        ImageView(ImageView &&rhs);
        ImageView& operator = (ImageView &&rhs);
        ~ImageView();

        explicit operator bool() const;
        operator VkImageView() const;

    private:
        ImageView(ImageView const &rhs) = delete;
        ImageView& operator = (ImageView const &rhs) = delete;

        void Reset();

        // members:
        VkDevice    m_VkDevice    = VK_NULL_HANDLE;
        VkImageView m_VkImageView = VK_NULL_HANDLE;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_IMAGE_HPP
