#include "vkuCommandBuffers.hpp"
#include "vkuInstance.hpp"
#include <cassert>

// ====================================================================================================================

/*explicit*/ vku::CommandBuffers::CommandBuffers(Instance const &instance,
                                                 VkDevice const device,
                                                 VkCommandPool const commandPool,
                                                 VkCommandBuffer * const commandBufferPtr,
                                                 uint32_t const commandBufferCount)
    : m_pfnFreeCommandBuffers(instance.vkFreeCommandBuffers.get())
    , m_VkDevice(device)
    , m_VkCommandPool(commandPool)
    , m_CommandBufferCount(commandBufferCount)
    , m_VkCommandBufferPtr(commandBufferPtr)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::CommandBuffers::CommandBuffers(CommandBuffers &&rhs)
    : m_pfnFreeCommandBuffers(rhs.m_pfnFreeCommandBuffers)
    , m_VkDevice(rhs.m_VkDevice)
    , m_VkCommandPool(rhs.m_VkCommandPool)
    , m_CommandBufferCount(rhs.m_CommandBufferCount)
    , m_VkCommandBufferPtr(rhs.m_VkCommandBufferPtr)
{
    rhs.Reset();
}

// --------------------------------------------------------------------------------------------------------------------

vku::CommandBuffers& vku::CommandBuffers::operator = (CommandBuffers &&rhs)
{
    Release();

    m_pfnFreeCommandBuffers = rhs.m_pfnFreeCommandBuffers;
    m_VkDevice = rhs.m_VkDevice;
    m_VkCommandPool = rhs.m_VkCommandPool;
    m_CommandBufferCount = rhs.m_CommandBufferCount;
    m_VkCommandBufferPtr = rhs.m_VkCommandBufferPtr;

    rhs.Reset();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::CommandBuffers::~CommandBuffers()
{
    Release();
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

void vku::CommandBuffers::Release()
{
    if((m_pfnFreeCommandBuffers != nullptr) &&
       (m_VkDevice != VK_NULL_HANDLE) &&
       (m_VkCommandPool != VK_NULL_HANDLE) &&
       (m_CommandBufferCount != 0) &&
       (m_VkCommandBufferPtr != nullptr))
    {
        m_pfnFreeCommandBuffers(m_VkDevice,
                                m_VkCommandPool,
                                m_CommandBufferCount,
                                m_VkCommandBufferPtr);

        Reset();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void vku::CommandBuffers::Reset()
{
    m_pfnFreeCommandBuffers = nullptr;
    m_VkDevice = VK_NULL_HANDLE;
    m_VkCommandPool = VK_NULL_HANDLE;
    m_CommandBufferCount = 0;
    m_VkCommandBufferPtr = nullptr;
}

// ====================================================================================================================
