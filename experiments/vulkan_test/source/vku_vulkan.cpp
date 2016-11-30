#include "vku_vulkan.hpp"
#include "vku_Utility.hpp"
#include <stdexcept>

// ====================================================================================================================

VKU_DEFINE_VK_PROC(vkCreateInstance);
VKU_DEFINE_VK_PROC(vkEnumerateInstanceExtensionProperties);
VKU_DEFINE_VK_PROC(vkEnumerateInstanceLayerProperties);

// ====================================================================================================================

vku::VkProcBase::VkProcBase(char const * const func_name)
    : m_FuncPtr(vkGetInstanceProcAddr(VK_NULL_HANDLE, func_name))
{
    if(m_FuncPtr == nullptr)
    {
        throw std::runtime_error(make_string("error: vkGetInstanceProcAddr(\"", func_name, "\") returned nullptr"));
    }
}

// ====================================================================================================================
