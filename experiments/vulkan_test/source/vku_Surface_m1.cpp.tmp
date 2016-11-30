#include "vku_Surface_m1.hpp"
#include "m1/game_platform.hpp"

// ====================================================================================================================

char const* vku::GetSurfaceExtensionName(m1::game_platform const &gamePlatform)
{
    switch(gamePlatform.get_platform_id())
    {
#ifdef VK_USE_PLATFORM_ANDROID_KHR
        case m1::game_platform_id::android:
            return VK_KHR_ANDROID_SURFACE_EXTENSION_NAME;
#endif

#ifdef VK_USE_PLATFORM_MIR_KHR
        case m1::game_platform_id::mir:
            return VK_KHR_MIR_SURFACE_EXTENSION_NAME;
#endif

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
        case m1::game_platform_id::wayland:
            return VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME;
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
        case m1::game_platform_id::win32:
            return VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
#endif

#ifdef VK_USE_PLATFORM_XCB_KHR
        case m1::game_platform_id::xcb:
            return VK_KHR_XCB_SURFACE_EXTENSION_NAME;
#endif

#ifdef VK_USE_PLATFORM_XLIB_KHR
        case m1::game_platform_id::xlib:
            return VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
#endif

        default:
            return nullptr;
    }
}

// ====================================================================================================================
