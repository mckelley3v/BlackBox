#ifndef VKU_COMMANDBUFFERS_HPP
#define VKU_COMMANDBUFFERS_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class Instance;

    // ================================================================================================================

    class CommandBuffers
    {
    public:
        CommandBuffers() = default;
        explicit CommandBuffers(Instance const &instance,
                                VkDevice device,
                                VkCommandPool commandPool,
                                VkCommandBuffer *commandBufferPtr,
                                uint32_t commandBufferCount);
        CommandBuffers(CommandBuffers &&rhs);
        CommandBuffers& operator = (CommandBuffers &&rhs);
        ~CommandBuffers();

        bool empty() const;
        uint32_t size() const;
        VkCommandBuffer operator [] (uint32_t index) const;

        VkCommandBuffer* begin();
        VkCommandBuffer* end();

        VkCommandBuffer const* begin() const;
        VkCommandBuffer const* end() const;

    private:
        CommandBuffers(CommandBuffers const &rhs) = delete;
        CommandBuffers& operator = (CommandBuffers const &rhs) = delete;

        void Release();
        void Reset();

        // members:
        PFN_vkFreeCommandBuffers m_pfnFreeCommandBuffers = nullptr;
        VkDevice                 m_VkDevice              = VK_NULL_HANDLE;
        VkCommandPool            m_VkCommandPool         = VK_NULL_HANDLE;
        uint32_t                 m_CommandBufferCount    = 0;
        VkCommandBuffer         *m_VkCommandBufferPtr    = nullptr;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_COMMANDBUFFERS_HPP
