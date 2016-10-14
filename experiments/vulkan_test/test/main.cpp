#include "m1/game_platform.hpp"
#include "vku.hpp"
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
        ApplicationInstance(Instance &&rhs);
        ApplicationInstance& operator = (Instance &&rhs);

        // procs:
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceSupportKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceCapabilitiesKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceFormatsKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfacePresentModesKHR);

    private:
        ApplicationInstance(Instance const &rhs) = delete;
        ApplicationInstance& operator = (Instance const &rhs) = delete;
    };

    // ================================================================================================================

    class ApplicationDevice
        : public LogicalDevice
    {
    public:
        using LogicalDevice::LogicalDevice;
        ApplicationDevice(LogicalDevice &&rhs);
        ApplicationDevice& operator = (LogicalDevice &&rhs);

        // procs:
        VKU_DEVICE_PROC_MEMBER(CreateSwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(DestroySwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(GetSwapchainImagesKHR);
        VKU_DEVICE_PROC_MEMBER(AcquireNextImageKHR);
        VKU_DEVICE_PROC_MEMBER(QueuePresentKHR);

    private:
        ApplicationDevice(LogicalDevice const &rhs) = delete;
        ApplicationDevice& operator = (LogicalDevice const &rhs) = delete;
    };

    // ================================================================================================================
}

// ====================================================================================================================

vku::Instance make_vk_instance(m1::game_platform const &game_platform);
vku::LogicalDevice make_vk_device(VkInstance instance);

// ====================================================================================================================

int main()
{
    try
    {
        m1::game_platform g("vulkan_test");

        vku::ApplicationInstance const vk_inst = make_vk_instance(g);
        vku::ApplicationDevice const vk_device = make_vk_device(vk_inst);

        return g.run();
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

vku::ApplicationInstance::ApplicationInstance(Instance &&rhs)
    : Instance(std::move(rhs))
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::ApplicationInstance& vku::ApplicationInstance::operator = (Instance &&rhs)
{
    Instance::operator = (std::move(rhs));
    return *this;
}

// ====================================================================================================================

vku::ApplicationDevice::ApplicationDevice(LogicalDevice &&rhs)
    : LogicalDevice(std::move(rhs))
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::ApplicationDevice& vku::ApplicationDevice::operator = (LogicalDevice &&rhs)
{
    LogicalDevice::operator = (std::move(rhs));
    return *this;
}

// ====================================================================================================================

vku::Instance make_vk_instance(m1::game_platform const &game_platform)
{
    vku::ApplicationInfo const app_info =
    {
        game_platform.get_name().c_str(), // pApplicationName
        VK_MAKE_VERSION(0, 0, 0),         // applicationVersion
        "m1",                             // pEngineName
        VK_MAKE_VERSION(0, 0, 0),         // engineVersion
        VK_MAKE_VERSION(0, 0, 0),         // apiVersion
    };

    VkInstance instance = vku::CreateInstance(app_info,
                                              {}, // requiredLayers
                                              {"VK_LAYER_LUNARG_standard_validation"}, // allowedLayers
                                              // requiredExtensions
                                              {
                                                  VK_KHR_SURFACE_EXTENSION_NAME,
                                                  VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME,
                                              },
                                              // allowedExtensions
                                              {});
    return vku::Instance(instance);
}

// ====================================================================================================================

vku::LogicalDevice make_vk_device(VkInstance const instance)
{
    VkDevice device = vku::CreateLogicalDevice(instance,
                                               // requestedQueues
                                               {
                                                   {
                                                       VK_QUEUE_GRAPHICS_BIT, // requiredQueueFlags
                                                       0xFFFFFFFF, // allowedQueueFlags
                                                       1, // requiredEnableCount
                                                       1, // allowedEnableCount
                                                       1.0f, // defaultPriority
                                                   },
                                               },
                                               {}, // requiredLayers
                                               {}, // allowedLayers
                                               {VK_KHR_SWAPCHAIN_EXTENSION_NAME}, // requiredExtensions
                                               {}); // allowedExtensions
    return vku::LogicalDevice(device);
}

// ====================================================================================================================
