#ifndef VKU_SURFACE_HPP
#define VKU_SURFACE_HPP

#include <vulkan/vulkan.h>
#include "vkuInstance.hpp"
#include "vkuDevice.hpp"
#include "vkuImage.hpp"

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class WsiInstance
        : public Instance
    {
    public:
        using Instance::Instance;

        // procs:
        VKU_INSTANCE_PROC_MEMBER(vkGetPhysicalDeviceSurfaceSupportKHR);
        VKU_INSTANCE_PROC_MEMBER(vkGetPhysicalDeviceSurfaceFormatsKHR);
        VKU_INSTANCE_PROC_MEMBER(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
        VKU_INSTANCE_PROC_MEMBER(vkGetPhysicalDeviceSurfacePresentModesKHR);
        VKU_INSTANCE_PROC_MEMBER(vkDestroySurfaceKHR);

    private:
        // prevent slicing:
        WsiInstance(Instance const &rhs) = delete;
        WsiInstance& operator = (Instance const &rhs) = delete;
    };

    // ================================================================================================================

    class WsiDevice
        : public Device
    {
    public:
        using Device::Device;

        // procs:
        VKU_DEVICE_PROC_MEMBER(vkCreateSwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(vkDestroySwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(vkGetSwapchainImagesKHR);
        VKU_DEVICE_PROC_MEMBER(vkAcquireNextImageKHR);
        VKU_DEVICE_PROC_MEMBER(vkQueuePresentKHR);

    private:
        // prevent slicing:
        WsiDevice(Device const &rhs) = delete;
        WsiDevice& operator = (Device const &rhs) = delete;
    };

    // ================================================================================================================

    class SurfaceKHR
    {
    public:
        SurfaceKHR() = default;
        explicit SurfaceKHR(WsiInstance const &instance,
                            VkSurfaceKHR surface);
        SurfaceKHR(SurfaceKHR &&rhs);
        SurfaceKHR& operator = (SurfaceKHR &&rhs);
        ~SurfaceKHR();

        explicit operator bool() const;
        operator VkSurfaceKHR() const;

    private:
        SurfaceKHR(SurfaceKHR const &rhs) = delete;
        SurfaceKHR& operator = (SurfaceKHR const &rhs) = delete;

        void Release();
        void Reset();

        // members:
        PFN_vkDestroySurfaceKHR m_pfnDestroySurfaceKHR = nullptr;
        VkInstance              m_VkInstance           = VK_NULL_HANDLE;
        VkSurfaceKHR            m_VkSurfaceKHR         = VK_NULL_HANDLE;
    };

    // ================================================================================================================

    class PhysicalDeviceSurfaceSupportKHR
    {
    public:
        PhysicalDeviceSurfaceSupportKHR(WsiInstance const &instance,
                                        VkSurfaceKHR surface);

        bool operator () (VkPhysicalDevice physicalDevice,
                          uint32_t queueFamilyIndex,
                          VkQueueFamilyProperties const &queueFamilyProperties) const;

    private:
        // members:
        WsiInstance const *m_InstancePtr  = nullptr;
        VkSurfaceKHR       m_VkSurfaceKHR = VK_NULL_HANDLE;
    };

    // ================================================================================================================

    class SelectQueueFamilyWithFlagsAndSurfaceSupport
        : private PhysicalDeviceSurfaceSupportKHR
        , private SelectQueueFamilyWithFlags
    {
    public:
        SelectQueueFamilyWithFlagsAndSurfaceSupport(WsiInstance const &instance,
                                                    VkSurfaceKHR surface,
                                                    VkQueueFlags requiredQueueFlags);
        SelectQueueFamilyWithFlagsAndSurfaceSupport(WsiInstance const &instance,
                                                    VkSurfaceKHR surface,
                                                    VkQueueFlags requiredQueueFlags,
                                                    VkQueueFlags allowedQueueFlags);

        bool operator () (VkPhysicalDevice physicalDevice,
                          uint32_t queueFamilyIndex,
                          VkQueueFamilyProperties const &queueFamilyProperties) const;
    };

    // ================================================================================================================

    std::vector<VkSurfaceFormatKHR> GetPhysicalDeviceSurfaceFormatsKHR(WsiInstance const &instance,
                                                                       VkPhysicalDevice physicalDevice,
                                                                       VkSurfaceKHR surface);

    // ----------------------------------------------------------------------------------------------------------------

    VkSurfaceFormatKHR SelectSurfaceFormat(std::vector<VkSurfaceFormatKHR> const &surfaceFormats,
                                           VkFormat preferredFormat = VK_FORMAT_B8G8R8A8_SRGB);

    // ================================================================================================================

    std::vector<VkPresentModeKHR> GetPhysicalDeviceSurfacePresentModesKHR(WsiInstance const &instance,
                                                                          VkPhysicalDevice physicalDevice,
                                                                          VkSurfaceKHR surface);

    // ----------------------------------------------------------------------------------------------------------------

    VkPresentModeKHR SelectPresentMode(std::vector<VkPresentModeKHR> const &presentModes,
                                       std::vector<VkPresentModeKHR> const &preferredModes);

    // ================================================================================================================

    struct SwapchainCreateInfo
    {
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

    SwapchainCreateInfo CreateSwapchainCreateInfo(WsiInstance const &instance,
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
        explicit Swapchain(WsiInstance const &instance,
                           WsiDevice const &device,
                           SwapchainCreateInfo const &createInfo);
        Swapchain(Swapchain &&rhs);
        Swapchain& operator = (Swapchain &&rhs);
        ~Swapchain();

        explicit operator bool() const;
        operator VkSwapchainKHR() const;

    private:
        Swapchain(Swapchain const &rhs) = delete;
        Swapchain& operator = (Swapchain const &rhs) = delete;

        void Release();
        void Reset();

        // types:
        struct ImageEntry
        {
            VkImage     image;
            ImageView   imageView;
        };

        static std::vector<ImageEntry> CreateSwapchainImageEntries(WsiInstance const &instance,
                                                                   WsiDevice const &device,
                                                                   VkSwapchainKHR const swapchain,
                                                                   SwapchainCreateInfo const &createInfo);

        // members:
        PFN_vkDestroySwapchainKHR m_pfnDestroySwapchainKHR = nullptr;
        VkDevice                  m_VkDevice               = VK_NULL_HANDLE;
        VkSwapchainKHR            m_VkSwapchainKHR         = VK_NULL_HANDLE;
        std::vector<ImageEntry>   m_Images                 = {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    VkSwapchainKHR CreateSwapchain(WsiDevice const &device,
                                   SwapchainCreateInfo const &createInfo);

    // ================================================================================================================

    std::vector<VkImage> GetSwapchainImages(WsiDevice const &device,
                                            VkSwapchainKHR swapchain);

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

#endif // VKU_SURFACE_HPP
