#ifndef M1_GAME_PLATFORM_IMPL_WINDOWS_HPP
#define M1_GAME_PLATFORM_IMPL_WINDOWS_HPP

#ifndef M1_GAME_PLATFORM_HPP
#error include "m1/game_platform.hpp" before including "m1/game_platform_impl.hpp"
#endif

#ifndef M1_GAME_PLATFORM_WINDOWS
#error incorrect platform for this header file
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <windowsx.h>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    struct game_platform::impl
    {
        static LRESULT CALLBACK WndProc(HWND hWnd,
                                        UINT message,
                                        WPARAM wParam,
                                        LPARAM lParam);

        // members:
        bool      is_exiting     = false;
        int       exit_code      = 0;
        HINSTANCE program_handle = 0;
        HWND      window_handle  = 0;
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_GAME_PLATFORM_IMPL_WINDOWS_HPP
