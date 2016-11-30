#include "vkuImage.hpp"

// ====================================================================================================================

/*explicit*/ vku::ImageView::ImageView(VkDevice const device,
                                       VkImageView const imageView)
    : m_VkDevice(device)
    , m_VkImageView(imageView)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView::ImageView(ImageView &&rhs)
    : m_VkDevice(rhs.m_VkDevice)
    , m_VkImageView(rhs.m_VkImageView)
{
    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkImageView = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView& vku::ImageView::operator = (ImageView &&rhs)
{
    Reset();

    m_VkDevice    = rhs.m_VkDevice;
    m_VkImageView = rhs.m_VkImageView;

    rhs.m_VkDevice    = VK_NULL_HANDLE;
    rhs.m_VkImageView = VK_NULL_HANDLE;

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView::~ImageView()
{
    Reset();
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::ImageView::operator bool() const
{
    return m_VkImageView != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView::operator VkImageView() const
{
    return m_VkImageView;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::ImageView::Reset()
{
    if ((m_VkDevice != VK_NULL_HANDLE) &&
        (m_VkImageView != VK_NULL_HANDLE))
    {
        vkDestroyImageView(m_VkDevice,
                           m_VkImageView,
                           nullptr); // pAllocator

        m_VkDevice = VK_NULL_HANDLE;
        m_VkImageView = VK_NULL_HANDLE;
    }
}

// ====================================================================================================================
