#include "vku_surface_m1.hpp"
#include "m1/game_platform.hpp"
#include "m1/game_platform_impl.hpp"
#include <stdexcept>

// ====================================================================================================================

static VkSurfaceKHR create_surface_khr(VkInstance const instance,
                                       m1::game_platform::impl const &gamePlatformImpl);

// ====================================================================================================================

VkSurfaceKHR vku::CreateSurfaceKHR(VkInstance const instance,
                                   m1::game_platform const &gamePlatform)
{
    switch(gamePlatform.get_platform_id())
    {
#ifdef VK_USE_PLATFORM_WIN32_KHR
        case m1::game_platform_id::win32:
            return create_surface_khr(instance, gamePlatform.get_platform_impl());
#endif
        default:
            return VK_NULL_HANDLE;
    }
}

// ====================================================================================================================

/*static*/ VkSurfaceKHR create_surface_khr(VkInstance const instance,
                                           m1::game_platform::impl const &gamePlatformImpl)
{
    VkWin32SurfaceCreateInfoKHR const create_info =
    {
        VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, // sType
        nullptr,                                         // pNext
        0,                                               // flags
        gamePlatformImpl.program_handle,                 // hinstance
        gamePlatformImpl.window_handle,                  // hwnd
    };

    VkSurfaceKHR surface = VK_NULL_HANDLE;
    switch(vkCreateWin32SurfaceKHR(instance,
                                   &create_info,
                                   nullptr,
                                   &surface))
    {
        case VK_SUCCESS:
            return surface;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
            throw std::runtime_error("error: vkCreateWin32SurfaceKHR returned VK_ERROR_OUT_OF_HOST_MEMORY");

        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            throw std::runtime_error("error: vkCreateWin32SurfaceKHR returned VK_ERROR_OUT_OF_DEVICE_MEMORY");

        default:
            throw std::runtime_error("error: vkCreateWin32SurfaceKHR returned unknown error");
    }
}

// ====================================================================================================================
