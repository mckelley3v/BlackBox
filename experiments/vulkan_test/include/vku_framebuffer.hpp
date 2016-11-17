#ifndef VKU_FRAMEBUFFER_HPP
#define VKU_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class Framebuffer
    {
    public:
        Framebuffer() = default;
        explicit Framebuffer(VkDevice device,
                             VkFramebuffer framebuffer);
        Framebuffer(Framebuffer &&rhs);
        Framebuffer& operator = (Framebuffer &&rhs);
        ~Framebuffer();

        explicit operator bool() const;
        operator VkFramebuffer() const;

    private:
        Framebuffer(Framebuffer const &rhs) = delete;
        Framebuffer& operator = (Framebuffer const &rhs) = delete;

        void Reset();

        // members:
        VkDevice      m_VkDevice      = VK_NULL_HANDLE;
        VkFramebuffer m_VkFramebuffer = VK_NULL_HANDLE;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_FRAMEBUFFER_HPP
