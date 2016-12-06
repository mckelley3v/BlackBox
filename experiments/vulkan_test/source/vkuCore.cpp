#include "vkuCore.hpp"
#include "vkuUtility.hpp"
#include <stdexcept>

// ====================================================================================================================

VKU_CORE_PROC(vkCreateInstance);
VKU_CORE_PROC(vkEnumerateInstanceExtensionProperties);
VKU_CORE_PROC(vkEnumerateInstanceLayerProperties);

// ====================================================================================================================

PFN_vkVoidFunction vku::GetCoreProcAddr(char const * const func_name)
{
    PFN_vkVoidFunction const func_ptr = vkGetInstanceProcAddr(VK_NULL_HANDLE, func_name);

    if(func_ptr == nullptr)
    {
        throw std::runtime_error(make_string("error: vkGetInstanceProcAddr(\"", func_name, "\") returned nullptr"));
    }

    return func_ptr;
}

// ====================================================================================================================

vku::VkProcBase::VkProcBase(PFN_vkVoidFunction const func_ptr)
    : m_FuncPtr(func_ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

vku::VkProcBase::VkProcBase(VkProcBase &&rhs)
    : m_FuncPtr(rhs.m_FuncPtr)
{
    rhs.m_FuncPtr = nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

vku::VkProcBase& vku::VkProcBase::operator = (VkProcBase &&rhs)
{
    m_FuncPtr = rhs.m_FuncPtr;
    rhs.m_FuncPtr = nullptr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

vku::VkProcBase& vku::VkProcBase::operator = (std::nullptr_t)
{
    m_FuncPtr = nullptr;
    return *this;
}

// ====================================================================================================================
