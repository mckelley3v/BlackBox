#ifndef VKU_IMAGE_HPP
#define VKU_IMAGE_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class Instance;

    // ================================================================================================================

    class ImageView
    {
    public:
        ImageView() = default;
        explicit ImageView(Instance const &instance,
                           VkDevice device,
                           VkImageView imageView);
        ImageView(ImageView &&rhs);
        ImageView& operator = (ImageView &&rhs);
        ~ImageView();

        explicit operator bool() const;
        operator VkImageView() const;

    private:
        ImageView(ImageView const &rhs) = delete;
        ImageView& operator = (ImageView const &rhs) = delete;

        void Release();
        void Reset();

        // members:
        PFN_vkDestroyImageView m_pfnDestroyImageView = nullptr;
        VkDevice               m_VkDevice            = VK_NULL_HANDLE;
        VkImageView            m_VkImageView         = VK_NULL_HANDLE;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_IMAGE_HPP
