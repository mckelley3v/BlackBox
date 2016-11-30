#ifndef VKU_CORE_HPP
#define VKU_CORE_HPP

#include <vulkan/vulkan.h>

// ====================================================================================================================

#define VKU_DECLARE_VK_PROC(func_name) extern vku::VkProc<PFN_ ## func_name> const func_name
#define VKU_DEFINE_VK_PROC(func_name) vku::VkProc<PFN_ ## func_name> const func_name {#func_name}

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class VkProcBase
    {
    public:
        VkProcBase() = default;
        explicit VkProcBase(char const *func_name);

    protected:
        // members:
        PFN_vkVoidFunction m_FuncPtr = nullptr;
    };

    // ================================================================================================================

    template <typename F>
    struct VkProc;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename R, typename ...Args>
    class VkProc<R (VKAPI_PTR*)(Args...)> : public VkProcBase
    {
    public:
        using VkProcBase::VkProcBase;
        using proc_type = R (VKAPI_PTR*)(Args...);

        proc_type get() const;
        R operator () (Args... args) const;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

extern PFN_vkGetInstanceProcAddr const vkGetInstanceProcAddr;
VKU_DECLARE_VK_PROC(vkCreateInstance);
VKU_DECLARE_VK_PROC(vkEnumerateInstanceExtensionProperties);
VKU_DECLARE_VK_PROC(vkEnumerateInstanceLayerProperties);

// ====================================================================================================================

template <typename R, typename ...Args>
typename vku::VkProc<R (VKAPI_PTR*)(Args...)>::proc_type vku::VkProc<R (VKAPI_PTR*)(Args...)>::get() const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename R, typename ...Args>
R vku::VkProc<R (VKAPI_PTR*)(Args...)>::operator () (Args... args) const
{
    return reinterpret_cast<R (VKAPI_PTR*)(Args...)>(m_FuncPtr)(args...);
}

// ====================================================================================================================

#endif // VKU_CORE_HPP
