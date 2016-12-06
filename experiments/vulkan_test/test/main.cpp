#include "m1/game_platform.hpp"
#include "vku.hpp"
#include "vkuSurface_m1.hpp"
#include <vector>
#include <iostream>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class ApplicationInstance
        : public WsiInstance
    {
    public:
        using WsiInstance::WsiInstance;
        explicit ApplicationInstance(WsiInstance &&instance,
                                     VkSurfaceKHR surface);

        // properties:
        VkSurfaceKHR GetSurfaceKHR() const;

    private:
        // prevent slicing:
        ApplicationInstance(WsiInstance const &rhs) = delete;
        ApplicationInstance& operator = (WsiInstance const &rhs) = delete;

        // members:
        SurfaceKHR m_SurfaceKHR;
    };

    // ----------------------------------------------------------------------------------------------------------------

    ApplicationInstance CreateApplicationInstance(m1::game_platform const &gamePlatform);

    // ================================================================================================================

    class ApplicationDevice
        : public WsiDevice
    {
    public:
        using WsiDevice::WsiDevice;
        explicit ApplicationDevice(WsiDevice &&device,
                                   VkQueue graphicsQueue);

        // properties:
        VkQueue GetGraphicsQueue() const;

        void SetSwapchain(Swapchain &&swapchain);
        Swapchain const& GetSwapchain() const;

    private:
        // prevent slicing:
        ApplicationDevice(WsiDevice const &rhs) = delete;
        ApplicationDevice& operator = (WsiDevice const &rhs) = delete;

        // members:
        VkQueue   m_GraphicsQueue = VK_NULL_HANDLE;
        Swapchain m_Swapchain;
    };

    // ----------------------------------------------------------------------------------------------------------------

    ApplicationDevice CreateApplicationDevice(m1::game_platform const &gamePlatform,
                                              ApplicationInstance const &instance);

    // ================================================================================================================
}

// ====================================================================================================================

int main()
{
    try
    {
        m1::game_platform game_platform("vulkan_test");

        vku::ApplicationInstance const vk_inst = vku::CreateApplicationInstance(game_platform);
        vku::ApplicationDevice const vk_device = vku::CreateApplicationDevice(game_platform, vk_inst);

        return game_platform.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred";
    }

    return 0;
}

// ====================================================================================================================

vku::ApplicationInstance::ApplicationInstance(WsiInstance &&instance,
                                              VkSurfaceKHR const surface)
    : WsiInstance(std::move(instance))
    , m_SurfaceKHR(*this, surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

VkSurfaceKHR vku::ApplicationInstance::GetSurfaceKHR() const
{
    return m_SurfaceKHR;
}

// ====================================================================================================================

vku::ApplicationDevice::ApplicationDevice(WsiDevice &&device,
                                          VkQueue const graphicsQueue)
    : WsiDevice(std::move(device))
    , m_GraphicsQueue(graphicsQueue)
{
}

// --------------------------------------------------------------------------------------------------------------------

VkQueue vku::ApplicationDevice::GetGraphicsQueue() const
{
    return m_GraphicsQueue;
}

// --------------------------------------------------------------------------------------------------------------------

void vku::ApplicationDevice::SetSwapchain(Swapchain &&swapchain)
{
    m_Swapchain = std::move(swapchain);
}

// --------------------------------------------------------------------------------------------------------------------

vku::Swapchain const& vku::ApplicationDevice::GetSwapchain() const
{
    return m_Swapchain;
}

// ====================================================================================================================

vku::ApplicationInstance vku::CreateApplicationInstance(m1::game_platform const &gamePlatform)
{
    vku::InstanceCreateInfo const instance_create_info =
        vku::CreateInstanceCreateInfo(// applicationInfo
                                      {
                                          gamePlatform.get_name().c_str(), // pApplicationName
                                          VK_MAKE_VERSION(0, 0, 0),        // applicationVersion
                                          "m1",                            // pEngineName
                                          VK_MAKE_VERSION(0, 0, 0),        // engineVersion
                                          VK_MAKE_VERSION(0, 0, 0),        // apiVersion
                                      },
                                      // requiredLayers
                                      {},
                                      // allowedLayers
                                      {"VK_LAYER_LUNARG_standard_validation"},
                                      // requiredExtensions
                                      {
                                          VK_KHR_SURFACE_EXTENSION_NAME,
                                          GetSurfaceExtensionName(gamePlatform),
                                      },
                                      // allowedExtensions
                                      {});

    WsiInstance instance(CreateInstance(instance_create_info));
    VkSurfaceKHR const surface = CreateSurfaceKHR(instance, gamePlatform);

    return ApplicationInstance(std::move(instance),
                               surface);
}

// ====================================================================================================================

vku::ApplicationDevice vku::CreateApplicationDevice(m1::game_platform const &gamePlatform,
                                                    ApplicationInstance const &instance)
{
    // consider how to support something like:
    // 1) 1 queue with (VK_QUEUE_GRAPHICS_BIT && SurfaceSupport),
    //      else: 1 queue with VK_QUEUE_GRAPHICS_BIT, 1 queue with SurfaceSupport
    // 2) 1 queue with ((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT) && SurfaceSupport)
    //      else if: 1 queue with (VK_QUEUE_GRAPHICS_BIT && SurfaceSupport), 1 queue with VK_QUEUE_COMPUTE_BIT
    //      else if: 1 queue with (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT), 1 queue with SurfaceSupport
    //      else if: 1 queue with (VK_QUEUE_COMPUTE_BIT && SurfaceSupport), 1 queue with VK_QUEUE_GRAPHICS_BIT
    //      else: 1 queue with VK_QUEUE_GRAPHICS_BIT, 1 queue with VK_QUEUE_COMPUTE_BIT, 1 queue with SurfaceSupport
    // perhaps have std::vector<std::vector<PhysicalDeviceRequestedQueueProperties>> requestedQueues, and a multi-pass queue algorithm to find
    // best group of queues (for each requestedQueues group, ...), so we'll prefer the first group over the second

    // **don't forget to update the swapchain's queue family index and image sharing mode if the graphics queue and present queues are different**

    DeviceCreateInfo const device_create_info =
        CreateDeviceCreateInfo(instance,
                               // requestedQueues
                               {
                                   {
                                       // selectQueueFamilyFunc
                                       SelectQueueFamilyWithFlagsAndSurfaceSupport(instance,
                                                                                   instance.GetSurfaceKHR(),
                                                                                   VK_QUEUE_GRAPHICS_BIT),
                                       1.0f, // defaultPriority
                                       1u, // requiredEnableCount
                                       1u, // allowedEnableCount
                                   },
                               },
                               // requiredLayers
                               {},
                               // allowedLayers
                               {},
                               // requiredExtensions
                               {VK_KHR_SWAPCHAIN_EXTENSION_NAME},
                               // allowedExtensions
                               {});

    WsiDevice device(instance,
                     CreateDevice(instance, device_create_info));

    VkQueue graphics_queue = VK_NULL_HANDLE;
    device.vkGetDeviceQueue(device,
                            device_create_info.queueFamilies[0].familyIndex,
                            0,
                            &graphics_queue);

    ApplicationDevice application_device(std::move(device),
                                         graphics_queue);

    vku::SwapchainCreateInfo const swapchain_create_info = vku::CreateSwapchainCreateInfo(instance,
                                                                                          device_create_info.physicalDevice,
                                                                                          instance.GetSurfaceKHR(),
                                                                                          2, // requestedImageCount,
                                                                                          VkExtent2D{static_cast<uint32_t>(gamePlatform.get_surface_width()),
                                                                                                     static_cast<uint32_t>(gamePlatform.get_surface_height())}, // defaultImageExtent
                                                                                          {/*preferred*/ VK_PRESENT_MODE_MAILBOX_KHR, /*backup*/ VK_PRESENT_MODE_IMMEDIATE_KHR}, // preferredPresentModes
                                                                                          VK_NULL_HANDLE);
    vku::Swapchain application_swapchain(instance,
                                         application_device,
                                         swapchain_create_info);

    application_device.SetSwapchain(std::move(application_swapchain));

    return application_device;
}

// ====================================================================================================================
