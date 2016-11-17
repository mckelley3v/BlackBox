#ifndef VKU_SURFACE_HPP
#define VKU_SURFACE_HPP

#include <vulkan/vulkan.h>
#include "vku_device.hpp"
#include "vku_image.hpp"

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class PhysicalDeviceSurfaceSupportKHR
    {
    public:
        PhysicalDeviceSurfaceSupportKHR(PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfnGetPhysicalDeviceSurfaceSupportKHR,
                                        VkSurfaceKHR surface);

        bool operator () (VkPhysicalDevice physicalDevice,
                          uint32_t queueFamilyIndex,
                          VkQueueFamilyProperties const &queueFamilyProperties) const;

    private:
        // members:
        PFN_vkGetPhysicalDeviceSurfaceSupportKHR m_pfnGetPhysicalDeviceSurfaceSupportKHR = nullptr;
        VkSurfaceKHR m_SurfaceKHR = VK_NULL_HANDLE;
    };

    // ================================================================================================================

    class SelectQueueFamilyWithFlagsAndSurfaceSupport
        : private PhysicalDeviceSurfaceSupportKHR
        , private SelectQueueFamilyWithFlags
    {
    public:
        SelectQueueFamilyWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                    VkSurfaceKHR surface,
                                                    VkQueueFlags requiredQueueFlags);
        SelectQueueFamilyWithFlagsAndSurfaceSupport(PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfnGetPhysicalDeviceSurfaceSupportKHR,
                                                    VkSurfaceKHR surface,
                                                    VkQueueFlags requiredQueueFlags,
                                                    VkQueueFlags allowedQueueFlags);

        bool operator () (VkPhysicalDevice physicalDevice,
                          uint32_t queueFamilyIndex,
                          VkQueueFamilyProperties const &queueFamilyProperties) const;
    };

    // ================================================================================================================

    std::vector<VkSurfaceFormatKHR> GetPhysicalDeviceSurfaceFormatsKHR(PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfnGetPhysicalDeviceSurfaceFormatsKHR,
                                                                       VkPhysicalDevice physicalDevice,
                                                                       VkSurfaceKHR surface);

    // ----------------------------------------------------------------------------------------------------------------

    VkSurfaceFormatKHR SelectSurfaceFormat(std::vector<VkSurfaceFormatKHR> const &surfaceFormats,
                                           VkFormat preferredFormat = VK_FORMAT_B8G8R8A8_SRGB);

    // ================================================================================================================

    std::vector<VkPresentModeKHR> GetPhysicalDeviceSurfacePresentModesKHR(PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfnGetPhysicalDeviceSurfacePresentModesKHR,
                                                                          VkPhysicalDevice physicalDevice,
                                                                          VkSurfaceKHR surface);

    // ----------------------------------------------------------------------------------------------------------------

    VkPresentModeKHR SelectPresentMode(std::vector<VkPresentModeKHR> const &presentModes,
                                       std::vector<VkPresentModeKHR> const &preferredModes);

    // ================================================================================================================

    struct SwapchainCreateInfo
    {
        PFN_vkCreateSwapchainKHR      pfnCreateSwapchainKHR;
        VkDevice                      device;
        VkSurfaceKHR                  surface;
        uint32_t                      minImageCount;
        VkFormat                      imageFormat;
        VkColorSpaceKHR               imageColorSpace;
        VkExtent2D                    imageExtent;
        uint32_t                      imageArrayLayers;
        VkImageUsageFlags             imageUsage;
        VkSharingMode                 imageSharingMode;
        uint32_t                      queueFamilyIndexCount;
        const uint32_t*               pQueueFamilyIndices;
        VkSurfaceTransformFlagBitsKHR preTransform;
        VkCompositeAlphaFlagBitsKHR   compositeAlpha;
        VkPresentModeKHR              presentMode;
        VkBool32                      clipped;
        VkSwapchainKHR                oldSwapchain;
    };

    // ----------------------------------------------------------------------------------------------------------------

    SwapchainCreateInfo CreateSwapchainCreateInfo(PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfnGetPhysicalDeviceSurfaceFormatsKHR,
                                                  PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfnGetPhysicalDeviceSurfaceCapabilitiesKHR,
                                                  PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfnGetPhysicalDeviceSurfacePresentModesKHR,
                                                  PFN_vkCreateSwapchainKHR pfnCreateSwapchainKHR,
                                                  VkDevice device,
                                                  VkPhysicalDevice physicalDevice,
                                                  VkSurfaceKHR surface,
                                                  uint32_t requestedImageCount,
                                                  VkExtent2D defaultImageExtent,
                                                  std::vector<VkPresentModeKHR> const &preferredPresentModes,
                                                  VkSwapchainKHR oldSwapchain);

    // ================================================================================================================

    class Swapchain
    {
    public:
        Swapchain() = default;
        explicit Swapchain(PFN_vkGetSwapchainImagesKHR pfnGetSwapchainImagesKHR,
                           PFN_vkDestroySwapchainKHR pfnDestroySwapchainKHR,
                           SwapchainCreateInfo const &createInfo);
        Swapchain(Swapchain &&rhs);
        Swapchain& operator = (Swapchain &&rhs);
        ~Swapchain();

        explicit operator bool() const;
        operator VkSwapchainKHR() const;

    private:
        Swapchain(Swapchain const &rhs) = delete;
        Swapchain& operator = (Swapchain const &rhs) = delete;

        void Reset();

        // types:
        struct ImageEntry
        {
            VkImage     image;
            ImageView   imageView;
        };

        // members:
        PFN_vkDestroySwapchainKHR m_pfnDestroySwapchainKHR = nullptr;
        VkDevice                  m_VkDevice               = VK_NULL_HANDLE;
        VkSwapchainKHR            m_VkSwapchainKHR         = VK_NULL_HANDLE;
        std::vector<ImageEntry>   m_Images                 = {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkSwapchainKHR CreateSwapchain(SwapchainCreateInfo const &createInfo);

    // ================================================================================================================

    std::vector<VkImage> GetSwapchainImages(PFN_vkGetSwapchainImagesKHR pfnGetSwapchainImagesKHR,
                                            VkDevice device,
                                            VkSwapchainKHR swapchain);

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_SURFACE_HPP
