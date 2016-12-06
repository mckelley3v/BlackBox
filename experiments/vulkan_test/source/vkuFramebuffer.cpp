#include "vkuFramebuffer.hpp"
#include "vkuInstance.hpp"

// ====================================================================================================================

/*explicit*/ vku::Framebuffer::Framebuffer(Instance const &instance,
                                           VkDevice const device,
                                           VkFramebuffer const framebuffer)
    : m_pfnDestroyFramebuffer(instance.vkDestroyFramebuffer.get())
    , m_VkDevice(device)
    , m_VkFramebuffer(framebuffer)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer::Framebuffer(Framebuffer &&rhs)
    : m_pfnDestroyFramebuffer(rhs.m_pfnDestroyFramebuffer)
    , m_VkDevice(rhs.m_VkDevice)
    , m_VkFramebuffer(rhs.m_VkFramebuffer)
{
    rhs.Reset();
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer& vku::Framebuffer::operator = (Framebuffer &&rhs)
{
    Release();

    m_pfnDestroyFramebuffer = rhs.m_pfnDestroyFramebuffer;
    m_VkDevice = rhs.m_VkDevice;
    m_VkFramebuffer = rhs.m_VkFramebuffer;

    rhs.Reset();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Framebuffer::~Framebuffer()
{
    Release();
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

void vku::Framebuffer::Release()
{
    if((m_pfnDestroyFramebuffer != nullptr) &&
       (m_VkDevice != VK_NULL_HANDLE) &&
       (m_VkFramebuffer != VK_NULL_HANDLE))
    {
        m_pfnDestroyFramebuffer(m_VkDevice,
                                m_VkFramebuffer,
                                nullptr); // pAllocator

        Reset();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void vku::Framebuffer::Reset()
{
    m_pfnDestroyFramebuffer = nullptr;
    m_VkDevice = VK_NULL_HANDLE;
    m_VkFramebuffer = VK_NULL_HANDLE;
}

// ====================================================================================================================
