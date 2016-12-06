#ifndef VKU_CORE_HPP
#define VKU_CORE_HPP

#include <vulkan/vulkan.h>
#include <cstddef>

// ====================================================================================================================

#define VKU_DECLARE_CORE_PROC(func_name) extern vku::VkProc<PFN_ ## func_name> const func_name
#define VKU_CORE_PROC(func_name)               vku::VkProc<PFN_ ## func_name> const func_name {vku::GetCoreProcAddr(#func_name)}

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    PFN_vkVoidFunction GetCoreProcAddr(char const *func_name);

    // ================================================================================================================

    class VkProcBase
    {
    public:
        VkProcBase() = default;
        explicit VkProcBase(PFN_vkVoidFunction func_ptr);
        VkProcBase(VkProcBase &&rhs);
        VkProcBase(VkProcBase const &rhs) = default;
        VkProcBase& operator = (VkProcBase &&rhs);
        VkProcBase& operator = (VkProcBase const &rhs) = default;
        VkProcBase& operator = (std::nullptr_t);
        ~VkProcBase() = default;

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
        typedef R (VKAPI_PTR *proc_type)(Args...);

        using VkProcBase::VkProcBase;
        using VkProcBase::operator = ;

        proc_type get() const;
        R operator () (Args... args) const;
    };

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

extern "C" VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance,
                                                                          const char *pName);

VKU_DECLARE_CORE_PROC(vkCreateInstance);
VKU_DECLARE_CORE_PROC(vkEnumerateInstanceExtensionProperties);
VKU_DECLARE_CORE_PROC(vkEnumerateInstanceLayerProperties);

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
