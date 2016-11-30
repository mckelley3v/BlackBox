#include "vku_Framebuffer.hpp"

// ====================================================================================================================

/*explicit*/ vku::Framebuffer::Framebuffer(VkDevice const device,
                                           VkFramebuffer const framebuffer)
    : m_VkDevice(device)
    , m_VkFramebuffer(framebuffer)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer::Framebuffer(Framebuffer &&rhs)
    : m_VkDevice(rhs.m_VkDevice)
    , m_VkFramebuffer(rhs.m_VkFramebuffer)
{
    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkFramebuffer = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer& vku::Framebuffer::operator = (Framebuffer &&rhs)
{
    Reset();

    m_VkDevice = rhs.m_VkDevice;
    m_VkFramebuffer = rhs.m_VkFramebuffer;

    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkFramebuffer = VK_NULL_HANDLE;

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer::~Framebuffer()
{
    Reset();
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::Framebuffer::operator bool() const
{
    return m_VkFramebuffer != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer::operator VkFramebuffer() const
{
    return m_VkFramebuffer;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::Framebuffer::Reset()
{
    if((m_VkDevice != VK_NULL_HANDLE) &&
       (m_VkFramebuffer != VK_NULL_HANDLE))
    {
        vkDestroyFramebuffer(m_VkDevice,
                             m_VkFramebuffer,
                             nullptr); // pAllocator

        m_VkDevice = VK_NULL_HANDLE;
        m_VkFramebuffer = VK_NULL_HANDLE;
    }
}

// ====================================================================================================================
