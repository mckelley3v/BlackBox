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
}

// ====================================================================================================================

vku::Instance make_vk_instance(m1::game_platform const &game_platform);

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

        vku::PhysicalDeviceQueueFamily const selected_device_queue_family = vku::FindPhysicalDeviceQueueFamily(gpu_list,
                                                                                                               VK_QUEUE_GRAPHICS_BIT);

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
                                              // allowedLayers
                                              {"*"},
                                              // requiredExtensions
                                              {},
                                              // allowedExtensions
                                              {
                                                  VK_KHR_SURFACE_EXTENSION_NAME,
                                                  VKU_KHR_PLATFORM_SURFACE_EXTENSION_NAME,
                                              });
    return vku::Instance(instance);
}

// ====================================================================================================================
