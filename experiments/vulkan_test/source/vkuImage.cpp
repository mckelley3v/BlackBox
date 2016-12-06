#include "vkuImage.hpp"
#include "vkuInstance.hpp"

// ====================================================================================================================

/*explicit*/ vku::ImageView::ImageView(Instance const &instance,
                                       VkDevice const device,
                                       VkImageView const imageView)
    : m_pfnDestroyImageView(instance.vkDestroyImageView.get())
    , m_VkDevice(device)
    , m_VkImageView(imageView)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView::ImageView(ImageView &&rhs)
    : m_pfnDestroyImageView(rhs.m_pfnDestroyImageView)
    , m_VkDevice(rhs.m_VkDevice)
    , m_VkImageView(rhs.m_VkImageView)
{
    rhs.Reset();
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView& vku::ImageView::operator = (ImageView &&rhs)
{
    Release();

    m_pfnDestroyImageView = rhs.m_pfnDestroyImageView;
    m_VkDevice    = rhs.m_VkDevice;
    m_VkImageView = rhs.m_VkImageView;

    rhs.Reset();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::ImageView::~ImageView()
{
    Release();
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

void vku::ImageView::Release()
{
    if ((m_pfnDestroyImageView != nullptr) &&
        (m_VkDevice != VK_NULL_HANDLE) &&
        (m_VkImageView != VK_NULL_HANDLE))
    {
        m_pfnDestroyImageView(m_VkDevice,
                              m_VkImageView,
                              nullptr); // pAllocator

        Reset();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void vku::ImageView::Reset()
{
    m_pfnDestroyImageView = nullptr;
    m_VkDevice = VK_NULL_HANDLE;
    m_VkImageView = VK_NULL_HANDLE;
}

// ====================================================================================================================
