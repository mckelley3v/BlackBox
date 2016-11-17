#include "vku_CommandBuffers.hpp"
#include <cassert>

// ====================================================================================================================

/*explicit*/ vku::CommandBuffers::CommandBuffers(VkDevice const device,
                                                 VkCommandPool const commandPool,
                                                 VkCommandBuffer * const commandBufferPtr,
                                                 uint32_t const commandBufferCount)
    : m_VkDevice(device)
    , m_VkCommandPool(commandPool)
    , m_CommandBufferCount(commandBufferCount)
    , m_VkCommandBufferPtr(commandBufferPtr)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::CommandBuffers::CommandBuffers(CommandBuffers &&rhs)
    : m_VkDevice(rhs.m_VkDevice)
    , m_VkCommandPool(rhs.m_VkCommandPool)
    , m_CommandBufferCount(rhs.m_CommandBufferCount)
    , m_VkCommandBufferPtr(rhs.m_VkCommandBufferPtr)
{
    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkCommandPool = VK_NULL_HANDLE;
    rhs.m_CommandBufferCount = 0;
    rhs.m_VkCommandBufferPtr = nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

vku::CommandBuffers& vku::CommandBuffers::operator = (CommandBuffers &&rhs)
{
    Reset();

    m_VkDevice = rhs.m_VkDevice;
    m_VkCommandPool = rhs.m_VkCommandPool;
    m_CommandBufferCount = rhs.m_CommandBufferCount;
    m_VkCommandBufferPtr = rhs.m_VkCommandBufferPtr;

    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkCommandPool = VK_NULL_HANDLE;
    rhs.m_CommandBufferCount = 0;
    rhs.m_VkCommandBufferPtr = nullptr;

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::CommandBuffers::~CommandBuffers()
{
    Reset();
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::CommandBuffers::empty() const
{
    return m_CommandBufferCount > 0;
}

// --------------------------------------------------------------------------------------------------------------------

uint32_t vku::CommandBuffers::size() const
{
    return m_CommandBufferCount;
}

// --------------------------------------------------------------------------------------------------------------------

VkCommandBuffer vku::CommandBuffers::operator [] (uint32_t const index) const
{
    assert(index < m_CommandBufferCount);
    return m_VkCommandBufferPtr[index];
}

// --------------------------------------------------------------------------------------------------------------------

VkCommandBuffer* vku::CommandBuffers::begin()
{
    return m_VkCommandBufferPtr;
}

// --------------------------------------------------------------------------------------------------------------------

VkCommandBuffer* vku::CommandBuffers::end()
{
    return m_VkCommandBufferPtr + m_CommandBufferCount;
}

// --------------------------------------------------------------------------------------------------------------------

VkCommandBuffer const* vku::CommandBuffers::begin() const
{
    return m_VkCommandBufferPtr;
}

// --------------------------------------------------------------------------------------------------------------------

VkCommandBuffer const* vku::CommandBuffers::end() const
{
    return m_VkCommandBufferPtr + m_CommandBufferCount;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::CommandBuffers::Reset()
{
    if((m_VkDevice != VK_NULL_HANDLE) &&
       (m_VkCommandPool != VK_NULL_HANDLE) &&
       (m_CommandBufferCount != 0) &&
       (m_VkCommandBufferPtr != nullptr))
    {
        vkFreeCommandBuffers(m_VkDevice,
                             m_VkCommandPool,
                             m_CommandBufferCount,
                             m_VkCommandBufferPtr);

        m_VkDevice = VK_NULL_HANDLE;
        m_VkCommandPool = VK_NULL_HANDLE;
        m_CommandBufferCount = 0;
        m_VkCommandBufferPtr = nullptr;
    }
}

// ====================================================================================================================
