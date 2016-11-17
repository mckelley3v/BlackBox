#include "vku_surface.hpp"
#include "vku_utility.hpp"
#include "vku.hpp"
#include <algorithm>
#include <stdexcept>
#include <cassert>

// ====================================================================================================================

vku::PhysicalDeviceSurfaceSupportKHR::PhysicalDeviceSurfaceSupportKHR(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                                      VkSurfaceKHR const surface)
    : m_pfnGetPhysicalDeviceSurfaceSupportKHR(pfnGetPhysicalDeviceSurfaceSupportKHR)
    , m_SurfaceKHR(surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

bool vku::PhysicalDeviceSurfaceSupportKHR::operator () (VkPhysicalDevice const physicalDevice,
                                                        uint32_t const queueFamilyIndex,
                                                        VkQueueFamilyProperties const &/*queueFamilyProperties*/) const
{
    assert(m_pfnGetPhysicalDeviceSurfaceSupportKHR != nullptr);
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(m_SurfaceKHR != VK_NULL_HANDLE);

    VkBool32 surface_support = VK_FALSE;
    switch(m_pfnGetPhysicalDeviceSurfaceSupportKHR(physicalDevice,
                                                   queueFamilyIndex,
                                                   m_SurfaceKHR,
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

vku::SelectQueueFamilyWithFlagsAndSurfaceSupport::SelectQueueFamilyWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                                                              VkSurfaceKHR const surface,
                                                                                              VkQueueFlags const requiredQueueFlags)
    : PhysicalDeviceSurfaceSupportKHR(pfnGetPhysicalDeviceSurfaceSupportKHR,
                                      surface)
    , SelectQueueFamilyWithFlags(requiredQueueFlags)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::SelectQueueFamilyWithFlagsAndSurfaceSupport::SelectQueueFamilyWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR const pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                                                              VkSurfaceKHR const surface,
                                                                                              VkQueueFlags const requiredQueueFlags,
                                                                                              VkQueueFlags const allowedQueueFlags)
    : PhysicalDeviceSurfaceSupportKHR(pfnGetPhysicalDeviceSurfaceSupportKHR,
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

std::vector<VkSurfaceFormatKHR> vku::GetPhysicalDeviceSurfaceFormatsKHR(PFN_vkGetPhysicalDeviceSurfaceFormatsKHR const pfnGetPhysicalDeviceSurfaceFormatsKHR,
                                                                        VkPhysicalDevice const physicalDevice,
                                                                        VkSurfaceKHR const surface)
{
    assert(pfnGetPhysicalDeviceSurfaceFormatsKHR != nullptr);
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(surface != VK_NULL_HANDLE);

    uint32_t surface_format_count = 0u;
    switch(pfnGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
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
    switch(pfnGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
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

std::vector<VkPresentModeKHR> vku::GetPhysicalDeviceSurfacePresentModesKHR(PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfnGetPhysicalDeviceSurfacePresentModesKHR,
                                                                           VkPhysicalDevice physicalDevice,
                                                                           VkSurfaceKHR surface)
{
    assert(pfnGetPhysicalDeviceSurfacePresentModesKHR != nullptr);
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(surface != VK_NULL_HANDLE);

    uint32_t present_mode_count = 0u;
    switch(pfnGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
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
    switch(pfnGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
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

vku::SwapchainCreateInfo vku::CreateSwapchainCreateInfo(PFN_vkGetPhysicalDeviceSurfaceFormatsKHR const pfnGetPhysicalDeviceSurfaceFormatsKHR,
                                                        PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR const pfnGetPhysicalDeviceSurfaceCapabilitiesKHR,
                                                        PFN_vkGetPhysicalDeviceSurfacePresentModesKHR const pfnGetPhysicalDeviceSurfacePresentModesKHR,
                                                        PFN_vkCreateSwapchainKHR const pfnCreateSwapchainKHR,
                                                        VkDevice const device,
                                                        VkPhysicalDevice const physicalDevice,
                                                        VkSurfaceKHR const surface,
                                                        uint32_t const requestedImageCount,
                                                        VkExtent2D const defaultImageExtent,
                                                        std::vector<VkPresentModeKHR> const &preferredPresentModes,
                                                        VkSwapchainKHR oldSwapchain)
{
    assert(pfnGetPhysicalDeviceSurfaceFormatsKHR != nullptr);
    assert(pfnGetPhysicalDeviceSurfaceCapabilitiesKHR != nullptr);
    assert(pfnGetPhysicalDeviceSurfacePresentModesKHR != nullptr);
    assert(pfnCreateSwapchainKHR != nullptr);
    assert(physicalDevice != VK_NULL_HANDLE);
    assert(surface != VK_NULL_HANDLE);

    std::vector<VkSurfaceFormatKHR> const surface_formats = GetPhysicalDeviceSurfaceFormatsKHR(pfnGetPhysicalDeviceSurfaceFormatsKHR,
                                                                                               physicalDevice,
                                                                                               surface);

    VkSurfaceCapabilitiesKHR surface_capabilities = {};
    switch(pfnGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,
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

    std::vector<VkPresentModeKHR> const swapchain_present_modes = GetPhysicalDeviceSurfacePresentModesKHR(pfnGetPhysicalDeviceSurfacePresentModesKHR,
                                                                                                          physicalDevice,
                                                                                                          surface);
    VkPresentModeKHR const swapchain_present_mode = SelectPresentMode(swapchain_present_modes,
                                                                      preferredPresentModes);

    SwapchainCreateInfo const swapchain_create_info =
    {
        pfnCreateSwapchainKHR,                       // pfnCreateSwapchainKHR
        device,                                      // device
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

/*explicit*/ vku::Swapchain::Swapchain(PFN_vkGetSwapchainImagesKHR const pfnGetSwapchainImagesKHR,
                                       PFN_vkDestroySwapchainKHR const pfnDestroySwapchainKHR,
                                       SwapchainCreateInfo const &createInfo)
    : m_pfnDestroySwapchainKHR(pfnDestroySwapchainKHR)
    , m_VkDevice(createInfo.device)
    , m_VkSwapchainKHR(CreateSwapchain(createInfo))
{
    std::vector<VkImage> const swapchainImages = GetSwapchainImages(pfnGetSwapchainImagesKHR,
                                                                    m_VkDevice,
                                                                    m_VkSwapchainKHR);
    m_Images.reserve(swapchainImages.size());
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
        switch(vkCreateImageView(m_VkDevice,
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

        m_Images.push_back(ImageEntry{image,
                                      ImageView(m_VkDevice, image_view)});
    }
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain::Swapchain(Swapchain &&rhs)
    : m_pfnDestroySwapchainKHR(rhs.m_pfnDestroySwapchainKHR)
    , m_VkDevice(rhs.m_VkDevice)
    , m_VkSwapchainKHR(rhs.m_VkSwapchainKHR)
{
    rhs.m_pfnDestroySwapchainKHR = nullptr;
    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkSwapchainKHR = VK_NULL_HANDLE;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain& vku::Swapchain::operator = (Swapchain &&rhs)
{
    Reset();

    m_pfnDestroySwapchainKHR = rhs.m_pfnDestroySwapchainKHR;
    m_VkDevice = rhs.m_VkDevice;
    m_VkSwapchainKHR = rhs.m_VkSwapchainKHR;

    rhs.m_pfnDestroySwapchainKHR = nullptr;
    rhs.m_VkDevice = VK_NULL_HANDLE;
    rhs.m_VkSwapchainKHR = VK_NULL_HANDLE;

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain::~Swapchain()
{
    Reset();
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

void vku::Swapchain::Reset()
{
    if((m_pfnDestroySwapchainKHR != nullptr) &&
       (m_VkDevice != VK_NULL_HANDLE) &&
       (m_VkSwapchainKHR != VK_NULL_HANDLE))
    {
        m_pfnDestroySwapchainKHR(m_VkDevice,
                                 m_VkSwapchainKHR,
                                 nullptr); // pAllocator

        m_pfnDestroySwapchainKHR = VK_NULL_HANDLE;
        m_VkDevice = VK_NULL_HANDLE;
        m_VkSwapchainKHR = VK_NULL_HANDLE;
    }
}

// ====================================================================================================================

VkSwapchainKHR vku::CreateSwapchain(SwapchainCreateInfo const &createInfo)
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
    switch(createInfo.pfnCreateSwapchainKHR(createInfo.device,
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

std::vector<VkImage> vku::GetSwapchainImages(PFN_vkGetSwapchainImagesKHR const pfnGetSwapchainImagesKHR,
                                             VkDevice const device,
                                             VkSwapchainKHR const swapchain)
{
    assert(pfnGetSwapchainImagesKHR != nullptr);
    assert(device != VK_NULL_HANDLE);
    assert(swapchain != VK_NULL_HANDLE);

    uint32_t swapchainImageCount = 0;
    switch(pfnGetSwapchainImagesKHR(device,
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
    switch(pfnGetSwapchainImagesKHR(device,
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
