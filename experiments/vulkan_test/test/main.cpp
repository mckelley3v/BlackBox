#include "m1/game_platform.hpp"
#include "vku.hpp"
#include "vku_surface_m1.hpp"
#include <vector>
#include <iostream>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class ApplicationInstance
        : public Instance
    {
    public:
        using Instance::Instance;
        explicit ApplicationInstance(VkInstance instance,
                                     VkSurfaceKHR surface);

        // procs:
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceSupportKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceCapabilitiesKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceFormatsKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfacePresentModesKHR);

        // properties:
        VkSurfaceKHR GetSurfaceKHR() const;

    private:
        ApplicationInstance(Instance const &rhs) = delete;
        ApplicationInstance& operator = (Instance const &rhs) = delete;

        // members:
        VkSurfaceKHR m_SurfaceKHR = VK_NULL_HANDLE;
    };

    // ----------------------------------------------------------------------------------------------------------------

    ApplicationInstance CreateApplicationInstance(m1::game_platform const &gamePlatform);

    // ================================================================================================================

    class ApplicationDevice
        : public LogicalDevice
    {
    public:
        using LogicalDevice::LogicalDevice;
        explicit ApplicationDevice(VkDevice device,
                                   VkQueue graphicsQueue);

        // procs:
        VKU_DEVICE_PROC_MEMBER(CreateSwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(DestroySwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(GetSwapchainImagesKHR);
        VKU_DEVICE_PROC_MEMBER(AcquireNextImageKHR);
        VKU_DEVICE_PROC_MEMBER(QueuePresentKHR);

        // properties:
        VkQueue GetGraphicsQueue() const;

    private:
        ApplicationDevice(LogicalDevice const &rhs) = delete;
        ApplicationDevice& operator = (LogicalDevice const &rhs) = delete;

        // members:
        VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
    };

    // ----------------------------------------------------------------------------------------------------------------

    ApplicationDevice CreateApplicationDevice(ApplicationInstance const &instance);

    // ================================================================================================================
}

// ====================================================================================================================

int main()
{
    try
    {
        m1::game_platform game_platform("vulkan_test");

        vku::ApplicationInstance const vk_inst = vku::CreateApplicationInstance(game_platform);
        vku::ApplicationDevice const vk_device = vku::CreateApplicationDevice(vk_inst);

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

vku::ApplicationInstance::ApplicationInstance(VkInstance const instance,
                                              VkSurfaceKHR const surface)
    : Instance(instance)
    , m_SurfaceKHR(surface)
{
}

// --------------------------------------------------------------------------------------------------------------------

VkSurfaceKHR vku::ApplicationInstance::GetSurfaceKHR() const
{
    return m_SurfaceKHR;
}

// ====================================================================================================================

vku::ApplicationDevice::ApplicationDevice(VkDevice const device,
                                          VkQueue const graphicsQueue)
    : LogicalDevice(device)
    , m_GraphicsQueue(graphicsQueue)
{
}

// ====================================================================================================================

vku::ApplicationInstance vku::CreateApplicationInstance(m1::game_platform const &gamePlatform)
{
    vku::InstanceCreateInfo const instance_create_info = vku::CreateInstanceCreateInfo(// applicationInfo
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

    VkInstance instance = CreateInstance(instance_create_info);
    VkSurfaceKHR surface = CreateSurfaceKHR(instance, gamePlatform);

    return ApplicationInstance(instance,
                               surface);
}

// ====================================================================================================================

vku::ApplicationDevice vku::CreateApplicationDevice(ApplicationInstance const &instance)
{
    std::vector<VkPhysicalDevice> const physical_devices = EnumeratePhysicalDevices(instance);

    LogicalDeviceCreateInfo const device_create_info = CreateLogicalDeviceCreateInfo(physical_devices,
                                                                                     // requestedQueues
                                                                                     {
                                                                                         {
                                                                                             VK_QUEUE_GRAPHICS_BIT, // requiredQueueFlags
                                                                                             0xFFFFFFFF, // allowedQueueFlags
                                                                                             PhysicalDeviceSurfaceSupportKHR(instance.GetPhysicalDeviceSurfaceSupportKHR.get(),
                                                                                                                             instance.GetSurfaceKHR()), // filterQueuePredicate
                                                                                             1, // requiredEnableCount
                                                                                             1, // allowedEnableCount
                                                                                             1.0f, // defaultPriority
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

    VkDevice device = CreateLogicalDevice(device_create_info);
    VkQueue graphics_queue = VK_NULL_HANDLE;
    vkGetDeviceQueue(device,
                     device_create_info.queueFamilies[0].familyIndex,
                     0,
                     &graphics_queue);

    return ApplicationDevice(device,
                             graphics_queue);
}

// ====================================================================================================================
