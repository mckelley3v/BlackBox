#include "m1/game_platform.hpp"
#include "vku.hpp"
#include "vku_iostream.hpp"
#include <vector>
#include <iostream>

// ====================================================================================================================

namespace vku
{
    class ApplicationInstance
        : public Instance
    {
    public:
        using Instance::Instance;
        ApplicationInstance(Instance &&rhs);
        ApplicationInstance& operator = (Instance &&rhs);

        // members:
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceSupportKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceCapabilitiesKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfaceFormatsKHR);
        VKU_INSTANCE_PROC_MEMBER(GetPhysicalDeviceSurfacePresentModesKHR);
        VKU_INSTANCE_PROC_MEMBER(GetSwapchainImagesKHR);

    private:
        ApplicationInstance(Instance const &rhs) = delete;
        ApplicationInstance& operator = (Instance const &rhs) = delete;
    };

    class ApplicationDevice
        : public Device
    {
    public:
        using Device::Device;
        ApplicationDevice(Device &&rhs);
        ApplicationDevice& operator = (Device &&rhs);

        // members:
        VKU_DEVICE_PROC_MEMBER(CreateSwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(DestroySwapchainKHR);
        VKU_DEVICE_PROC_MEMBER(GetSwapchainImagesKHR);
        VKU_DEVICE_PROC_MEMBER(AcquireNextImageKHR);
        VKU_DEVICE_PROC_MEMBER(QueuePresentKHR);

    private:
        ApplicationDevice(Device const &rhs) = delete;
        ApplicationDevice& operator = (Device const &rhs) = delete;
    };
}

// ====================================================================================================================

vku::Instance make_vk_instance(m1::game_platform const &game_platform);
vku::Device make_vk_device(VkInstance instance);

// ====================================================================================================================

int main()
{
    try
    {
        m1::game_platform g("vulkan_test");

        vku::ApplicationInstance const vk_inst = make_vk_instance(g);
        std::vector<VkPhysicalDevice> const gpu_list = vku::EnumeratePhysicalDevices(vk_inst);

        using namespace vku::iostream;
        std::cout << "physicalDevices:" << gpu_list << "\n";

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

vku::ApplicationDevice::ApplicationDevice(Device &&rhs)
    : Device(std::move(rhs))
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::ApplicationDevice& vku::ApplicationDevice::operator = (Device &&rhs)
{
    Device::operator = (std::move(rhs));
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
                                              // requiredLayers
                                              {},
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

vku::Device make_vk_device(VkInstance const instance)
{
    VkDevice device = vku::CreateDevice(instance,
                                        VK_QUEUE_GRAPHICS_BIT,
                                        {}, // requiredLayers
                                        {VK_KHR_SWAPCHAIN_EXTENSION_NAME}, // requiredExtensions
                                        {}); // allowedExtensions}
    return vku::Device(device);
}

// ====================================================================================================================
