#include "m1/game_platform.hpp"
#include "vku.hpp"
#include <iostream>

// ====================================================================================================================

vku::Instance make_vk_instance(m1::game_platform const &game_platform);

int main()
{
    try
    {
        m1::game_platform g("vulkan_test");

        vku::Instance const vk_inst = make_vk_instance(g);
        std::vector<VkPhysicalDevice> const gpu_list = vku::EnumeratePhysicalDevices(vk_inst);

        std::cout << "VkPhysicalDevice[]:\n";
        for(VkPhysicalDevice const &gpu : gpu_list)
        {
            using namespace vku::iostream;

            VkPhysicalDeviceProperties gpu_properties = {};
            vkGetPhysicalDeviceProperties(gpu, &gpu_properties);

            std::cout << "-\n" << gpu_properties << "\n";

            std::cout << "PhysicalDeviceQueueFamilyProperties: \n";
            std::vector<VkQueueFamilyProperties> const gpu_queue_families_properties = vku::GetPhysicalDeviceQueueFamilyProperties(gpu);
            for(VkQueueFamilyProperties const &queue_family_properties : gpu_queue_families_properties)
            {
               std::cout << "-\n" << queue_family_properties << "\n";
            }
        }

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
