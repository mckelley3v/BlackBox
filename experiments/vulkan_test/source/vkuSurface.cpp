#include "vkuSurface.hpp"
#include "vkuUtility.hpp"
#include "vku.hpp"
#include <algorithm>
#include <stdexcept>
#include <cassert>

// ====================================================================================================================

/*explicit*/ vku::SurfaceKHR::SurfaceKHR(WsiInstance const &instance,
                                         VkSurfaceKHR const surface)
    : m_pfnDestroySurfaceKHR(instance.vkDestroySurfaceKHR.get())
    , m_VkInstance(instance)
    , m_VkSurfaceKHR(surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::SurfaceKHR::SurfaceKHR(SurfaceKHR &&rhs)
    : m_pfnDestroySurfaceKHR(rhs.m_pfnDestroySurfaceKHR)
    , m_VkInstance(rhs.m_VkInstance)
    , m_VkSurfaceKHR(rhs.m_VkSurfaceKHR)
{
    rhs.Reset();
}

// --------------------------------------------------------------------------------------------------------------------

vku::SurfaceKHR& vku::SurfaceKHR::operator = (SurfaceKHR &&rhs)
{
    Release();

    m_pfnDestroySurfaceKHR = rhs.m_pfnDestroySurfaceKHR;
    m_VkInstance = rhs.m_VkInstance;
    m_VkSurfaceKHR = rhs.m_VkSurfaceKHR;

    rhs.Reset();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::SurfaceKHR::~SurfaceKHR()
{
    Release();
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::SurfaceKHR::operator bool() const
{
    return m_VkSurfaceKHR != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::SurfaceKHR::operator VkSurfaceKHR() const
{
    return m_VkSurfaceKHR;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::SurfaceKHR::Release()
{
    if((m_pfnDestroySurfaceKHR != nullptr) &&
       (m_VkInstance != VK_NULL_HANDLE) &&
       (m_VkSurfaceKHR != VK_NULL_HANDLE))
    {
        m_pfnDestroySurfaceKHR(m_VkInstance,
                               m_VkSurfaceKHR,
                               nullptr); // pAllocator

        Reset();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void vku::SurfaceKHR::Reset()
{
    m_pfnDestroySurfaceKHR = nullptr;
    m_VkInstance = VK_NULL_HANDLE;
    m_VkSurfaceKHR = VK_NULL_HANDLE;
}

// ====================================================================================================================

vku::PhysicalDeviceSurfaceSupportKHR::PhysicalDeviceSurfaceSupportKHR(WsiInstance const &instance,
                                                                      VkSurfaceKHR const surface)
    : m_InstancePtr(&instance)
    , m_VkSurfaceKHR(surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::PhysicalDeviceSurfaceSupportKHR::operator () (VkPhysicalDevice const physicalDevice,
                                                        uint32_t const queueFamilyIndex,
                                                        VkQueueFamilyProperties const &/*queueFamilyProperties*/) const
{
    assert(m_InstancePtr != nullptr);
    assert(m_VkSurfaceKHR != VK_NULL_HANDLE);
    assert(physicalDevice != VK_NULL_HANDLE);

    VkBool32 surface_support = VK_FALSE;
    switch(m_InstancePtr->vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,
                                                               queueFamilyIndex,
                                                               m_VkSurfaceKHR,
                                                               &surface_support))
    {
        case VK_SUCCESS:
            return (surface_support == VK_FALSE) ? false : true;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceSupportKHR returned unknown error");
    }
}

// ====================================================================================================================

vku::SelectQueueFamilyWithFlagsAndSurfaceSupport::SelectQueueFamilyWithFlagsAndSurfaceSupport(WsiInstance const &instance,
                                                                                              VkSurfaceKHR const surface,
                                                                                              VkQueueFlags const requiredQueueFlags)
    : PhysicalDeviceSurfaceSupportKHR(instance,
                                      surface)
    , SelectQueueFamilyWithFlags(requiredQueueFlags)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::SelectQueueFamilyWithFlagsAndSurfaceSupport::SelectQueueFamilyWithFlagsAndSurfaceSupport(WsiInstance const &instance,
                                                                                              VkSurfaceKHR const surface,
                                                                                              VkQueueFlags const requiredQueueFlags,
                                                                                              VkQueueFlags const allowedQueueFlags)
    : PhysicalDeviceSurfaceSupportKHR(instance,
                                      surface)
    , SelectQueueFamilyWithFlags(requiredQueueFlags,
                                 allowedQueueFlags)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::SelectQueueFamilyWithFlagsAndSurfaceSupport::operator () (VkPhysicalDevice const physicalDevice,
                                                                  uint32_t const queueFamilyIndex,
                                                                  VkQueueFamilyProperties const &queueFamilyProperties) const
{
    return PhysicalDeviceSurfaceSupportKHR::operator()(physicalDevice, queueFamilyIndex, queueFamilyProperties) &&
           SelectQueueFamilyWithFlags::operator()(physicalDevice, queueFamilyIndex, queueFamilyProperties);
}

// ====================================================================================================================

std::vector<VkSurfaceFormatKHR> vku::GetPhysicalDeviceSurfaceFormatsKHR(WsiInstance const &instance,
                                                                        VkPhysicalDevice const physicalDevice,
                                                                        VkSurfaceKHR const surface)
{
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(surface != VK_NULL_HANDLE);

    uint32_t surface_format_count = 0u;
    switch(instance.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
                                                         surface,
                                                         &surface_format_count,
                                                         nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned unknown error");
    }

    std::vector<VkSurfaceFormatKHR> surface_formats(surface_format_count, VkSurfaceFormatKHR());
    switch(instance.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
                                                         surface,
                                                         &surface_format_count,
                                                         surface_formats.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfaceFormatsKHR returned unknown error");
    }

    return surface_formats;
}

// ====================================================================================================================

VkSurfaceFormatKHR vku::SelectSurfaceFormat(std::vector<VkSurfaceFormatKHR> const &surfaceFormats,
                                            VkFormat const preferredFormat /*= VK_FORMAT_B8G8R8A8_UNORM*/)
{
    if(surfaceFormats.empty())
    {
        return VkSurfaceFormatKHR{VK_FORMAT_UNDEFINED, VK_COLOR_SPACE_BEGIN_RANGE_KHR};
    }
    else if((surfaceFormats.size() == 1) && (surfaceFormats.front().format == VK_FORMAT_UNDEFINED))
    {
        return VkSurfaceFormatKHR{preferredFormat, surfaceFormats.front().colorSpace};
    }
    else
    {
        std::vector<VkSurfaceFormatKHR>::const_iterator const preferred_itr = std::find_if(surfaceFormats.begin(),
                                                                                           surfaceFormats.end(),
                                                                                           [&](VkSurfaceFormatKHR const &surfaceFormat)
                                                                                           {
                                                                                               return surfaceFormat.format == preferredFormat;
                                                                                           });
        if(preferred_itr != surfaceFormats.end())
        {
            return *preferred_itr;
        }

        return surfaceFormats.front();
    }
}

// ====================================================================================================================

std::vector<VkPresentModeKHR> vku::GetPhysicalDeviceSurfacePresentModesKHR(WsiInstance const &instance,
                                                                           VkPhysicalDevice physicalDevice,
                                                                           VkSurfaceKHR surface)
{
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(surface != VK_NULL_HANDLE);

    uint32_t present_mode_count = 0u;
    switch(instance.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
                                                              surface,
                                                              &present_mode_count,
                                                              nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned unknown error");
    }

    std::vector<VkPresentModeKHR> present_modes(present_mode_count, VkPresentModeKHR());
    switch(instance.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
                                                              surface,
                                                              &present_mode_count,
                                                              present_modes.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_INCOMPLETE");

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: vkGetPhysicalDeviceSurfacePresentModesKHR returned unknown error");
    }

    return present_modes;
}

// ====================================================================================================================

VkPresentModeKHR vku::SelectPresentMode(std::vector<VkPresentModeKHR> const &presentModes,
                                        std::vector<VkPresentModeKHR> const &preferredModes)
{
    for(VkPresentModeKHR const preferredMode : preferredModes)
    {
        if(contains(presentModes.begin(),
                    presentModes.end(),
                    preferredMode))
        {
            return preferredMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

// ====================================================================================================================

vku::SwapchainCreateInfo vku::CreateSwapchainCreateInfo(WsiInstance const &instance,
                                                        VkPhysicalDevice const physicalDevice,
                                                        VkSurfaceKHR const surface,
                                                        uint32_t const requestedImageCount,
                                                        VkExtent2D const defaultImageExtent,
                                                        std::vector<VkPresentModeKHR> const &preferredPresentModes,
                                                        VkSwapchainKHR oldSwapchain)
{
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(surface != VK_NULL_HANDLE);

    std::vector<VkSurfaceFormatKHR> const surface_formats = GetPhysicalDeviceSurfaceFormatsKHR(instance,
                                                                                               physicalDevice,
                                                                                               surface);

    VkSurfaceCapabilitiesKHR surface_capabilities = {};
    switch(instance.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,
                                                              surface,
                                                              &surface_capabilities))
    {
        case VK_SUCCESS:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: VKGetPhysicalDeviceSurfaceCapabilitiesKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: VKGetPhysicalDeviceSurfaceCapabilitiesKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: VKGetPhysicalDeviceSurfaceCapabilitiesKHR returned VK_ERROR_SURFACE_LOST_KHR");

        default:
            throw std::runtime_error("error: VKGetPhysicalDeviceSurfaceCapabilitiesKHR returned unknown error");
    }

    VkSurfaceFormatKHR const surface_format = SelectSurfaceFormat(surface_formats);

    uint32_t const swapchain_image_count = std::min(std::max(requestedImageCount, surface_capabilities.minImageCount), surface_capabilities.maxImageCount);

    VkExtent2D const swapchain_image_extent = IsValidExtent(surface_capabilities.currentExtent) ? surface_capabilities.currentExtent
                                                                                                : ClampExtent(defaultImageExtent,
                                                                                                              surface_capabilities.minImageExtent,
                                                                                                              surface_capabilities.maxImageExtent);
    VkSurfaceTransformFlagBitsKHR const swapchain_transform_flag_bits = (surface_capabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) ? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR
                                                                                                                                                           : surface_capabilities.currentTransform;

    std::vector<VkPresentModeKHR> const swapchain_present_modes = GetPhysicalDeviceSurfacePresentModesKHR(instance,
                                                                                                          physicalDevice,
                                                                                                          surface);
    VkPresentModeKHR const swapchain_present_mode = SelectPresentMode(swapchain_present_modes,
                                                                      preferredPresentModes);

    SwapchainCreateInfo const swapchain_create_info =
    {
        surface,                                     // surface
        swapchain_image_count,                       // minImageCount
        surface_format.format,                       // imageFormat
        surface_format.colorSpace,                   // imageColorSpace
        swapchain_image_extent,                      // imageExtent
        1,                                           // imageArrayLayers
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,         // imageUsage
        VK_SHARING_MODE_EXCLUSIVE,                   // imageSharingMode
        0,                                           // queueFamilyIndexCount
        nullptr,                                     // pQueueFamilyIndices
        swapchain_transform_flag_bits,               // preTransform
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,           // compositeAlpha
        swapchain_present_mode,                      // presentMode
        VK_TRUE,                                     // clipped
        oldSwapchain,                                // oldSwapchain
    };

    return swapchain_create_info;
}

// ====================================================================================================================

/*explicit*/ vku::Swapchain::Swapchain(WsiInstance const &instance,
                                       WsiDevice const &device,
                                       SwapchainCreateInfo const &createInfo)
    : m_pfnDestroySwapchainKHR(device.vkDestroySwapchainKHR.get())
    , m_VkDevice(device)
    , m_VkSwapchainKHR(CreateSwapchain(device, createInfo))
    , m_Images(CreateSwapchainImageEntries(instance, device, m_VkSwapchainKHR, createInfo))
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain::Swapchain(Swapchain &&rhs)
    : m_pfnDestroySwapchainKHR(rhs.m_pfnDestroySwapchainKHR)
    , m_VkDevice(rhs.m_VkDevice)
    , m_VkSwapchainKHR(rhs.m_VkSwapchainKHR)
    , m_Images(std::move(rhs.m_Images))
{
    rhs.Reset();
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain& vku::Swapchain::operator = (Swapchain &&rhs)
{
    Release();

    m_pfnDestroySwapchainKHR = rhs.m_pfnDestroySwapchainKHR;
    m_VkDevice = rhs.m_VkDevice;
    m_VkSwapchainKHR = rhs.m_VkSwapchainKHR;
    m_Images = std::move(rhs.m_Images);

    rhs.Reset();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain::~Swapchain()
{
    Release();
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ vku::Swapchain::operator bool() const
{
    return m_VkSwapchainKHR != VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain::operator VkSwapchainKHR() const
{
    return m_VkSwapchainKHR;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::Swapchain::Release()
{
    if((m_pfnDestroySwapchainKHR != nullptr) &&
       (m_VkDevice != nullptr) &&
       (m_VkSwapchainKHR != VK_NULL_HANDLE))
    {
        m_Images.clear();
        m_pfnDestroySwapchainKHR(m_VkDevice,
                                 m_VkSwapchainKHR,
                                 nullptr); // pAllocator

        Reset();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void vku::Swapchain::Reset()
{
    m_pfnDestroySwapchainKHR = nullptr;
    m_VkDevice = VK_NULL_HANDLE;
    m_VkSwapchainKHR = VK_NULL_HANDLE;
    m_Images.clear();
}

// --------------------------------------------------------------------------------------------------------------------

/*static*/ std::vector<vku::Swapchain::ImageEntry> vku::Swapchain::CreateSwapchainImageEntries(WsiInstance const &instance,
                                                                                               WsiDevice const &device,
                                                                                               VkSwapchainKHR const swapchain,
                                                                                               SwapchainCreateInfo const &createInfo)
{
    std::vector<ImageEntry> result;
    std::vector<VkImage> const swapchainImages = GetSwapchainImages(device,
                                                                    swapchain);
    result.reserve(swapchainImages.size());
    for(VkImage const image : swapchainImages)
    {
        VkImageViewCreateInfo const image_view_create_info =
        {
            VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, // sType
            nullptr,                                  // pNext
            0,                                        // flags
            image,                                    // image
            VK_IMAGE_VIEW_TYPE_2D,                    // viewType
            createInfo.imageFormat,                   // format
            // components
            {
                VK_COMPONENT_SWIZZLE_R,
                VK_COMPONENT_SWIZZLE_G,
                VK_COMPONENT_SWIZZLE_B,
                VK_COMPONENT_SWIZZLE_A,
            },
            // subresourceRange
            {
                VK_IMAGE_ASPECT_COLOR_BIT, // aspectMask
                0,                         // baseMipLevel
                1,                         // levelCount
                0,                         // baseArrayLayer
                1,                         // layerCount
            },
        };

        VkImageView image_view = VK_NULL_HANDLE;
        switch(instance.vkCreateImageView(device,
                                          &image_view_create_info,
                                          nullptr, // pAllocator
                                          &image_view))
        {
            case VK_SUCCESS:
                break;

            case VK_ERROR_OUT_OF_HOST_MEMORY:
                throw std::runtime_error("error: vkCreateImageView returned VK_ERROR_OUT_OF_HOST_MEMORY");

            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                throw std::runtime_error("error: vkCreateImageView returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

            default:
                throw std::runtime_error("error: vkCreateImageView returned unknown error");
        }

        result.push_back(ImageEntry{image,
                                      ImageView(instance,
                                                device,
                                                image_view)});
    }

    return result;
}

// ====================================================================================================================

VkSwapchainKHR vku::CreateSwapchain(WsiDevice const &device,
                                    SwapchainCreateInfo const &createInfo)
{

    VkSwapchainCreateInfoKHR const swapchain_create_info =
    {
        VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, // sType
        nullptr,                                     // pNext
        0,                                           // flags
        createInfo.surface,                          // surface
        createInfo.minImageCount,                    // minImageCount
        createInfo.imageFormat,                      // imageFormat
        createInfo.imageColorSpace,                  // imageColorSpace
        createInfo.imageExtent,                      // imageExtent
        createInfo.imageArrayLayers,                 // imageArrayLayers
        createInfo.imageUsage,                       // imageUsage
        createInfo.imageSharingMode,                 // imageSharingMode
        createInfo.queueFamilyIndexCount,            // queueFamilyIndexCount
        createInfo.pQueueFamilyIndices,              // pQueueFamilyIndices
        createInfo.preTransform,                     // preTransform
        createInfo.compositeAlpha,                   // compositeAlpha
        createInfo.presentMode,                      // presentMode
        createInfo.clipped,                          // clipped
        createInfo.oldSwapchain,                     // oldSwapchain
    };

    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    switch(device.vkCreateSwapchainKHR(device,
                                       &swapchain_create_info,
                                       nullptr, // pAllocator
                                       &swapchain))
    {
       case VK_SUCCESS:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkCreateSwapchainKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkCreateSwapchainKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        case VK_ERROR_DEVICE_LOST:
            throw std::runtime_error("error: vkCreateSwapchainKHR returned VK_ERROR_DEVICE_LOST");

        case VK_ERROR_SURFACE_LOST_KHR:
            throw std::runtime_error("error: vkCreateSwapchainKHR returned VK_ERROR_SURFACE_LOST_KHR");

        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            throw std::runtime_error("error: vkCreateSwapchainKHR returned VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");

        default:
            throw std::runtime_error("error: vkCreateSwapchainKHR returned unknown error");
    }

    return swapchain;
}

// ====================================================================================================================

std::vector<VkImage> vku::GetSwapchainImages(WsiDevice const &device,
                                             VkSwapchainKHR const swapchain)
{
    assert(swapchain != VK_NULL_HANDLE);

    uint32_t swapchainImageCount = 0;
    switch(device.vkGetSwapchainImagesKHR(device,
                                          swapchain,
                                          &swapchainImageCount,
                                          nullptr))
    {
        case VK_SUCCESS:
        case VK_INCOMPLETE:
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned unknown error");
    }

    std::vector<VkImage> swapchainImages(swapchainImageCount, VkImage());
    switch(device.vkGetSwapchainImagesKHR(device,
                                          swapchain,
                                          &swapchainImageCount,
                                          swapchainImages.data()))
    {
        case VK_SUCCESS:
            break;

        case VK_INCOMPLETE:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned VK_INCOMPLETE");
            break;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkGetSwapchainImagesKHR returned unknown error");
    }

    return swapchainImages;
}

// ====================================================================================================================
