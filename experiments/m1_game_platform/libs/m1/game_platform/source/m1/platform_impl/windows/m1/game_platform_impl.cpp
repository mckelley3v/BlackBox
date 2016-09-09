#include "m1/game_platform.hpp"
#include "m1/platform_impl/windows/m1/game_platform_impl.hpp"

// ====================================================================================================================

static const WCHAR* GetWNDCLASS(HINSTANCE hInstance);
static HWND CreateWND(HINSTANCE hInstance,
                      std::string const &window_name);

// ====================================================================================================================

/*explicit*/ m1::game_platform::game_platform(std::string const &name)
    : m_Name(name)
    , m_ImplPtr(new impl)
{
    m_ImplPtr->program_handle = GetModuleHandleW(nullptr);
    m_ImplPtr->window_handle = CreateWND(m_ImplPtr->program_handle, m_Name);
    SetWindowLongPtrW(m_ImplPtr->window_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

// --------------------------------------------------------------------------------------------------------------------

m1::game_platform::game_platform(game_platform &&rhs)// = default;
    : m_ImplPtr(std::move(rhs.m_ImplPtr))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::game_platform& m1::game_platform::operator = (game_platform &&rhs)// = default;
{
    m_ImplPtr = std::move(rhs.m_ImplPtr);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::game_platform::~game_platform()
{
    DestroyWindow(m_ImplPtr->window_handle);
}

// --------------------------------------------------------------------------------------------------------------------

m1::game_platform::impl& m1::game_platform::platform_impl()
{
    return *m_ImplPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::game_platform::impl const& m1::game_platform::get_platform_impl() const
{
    return *m_ImplPtr;
}

// --------------------------------------------------------------------------------------------------------------------

int m1::game_platform::run()
{
    m1::signal<void()>::connection const exit_connection = event_destroy.connect([&] { exit(0); });
    ShowWindow(m_ImplPtr->window_handle, SW_SHOW);

    while(do_events())
    {
        on_idle();

        WaitMessage();
    }

    return m_ImplPtr->exit_code;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::game_platform::exit(int code /*= 0*/)
{
    PostQuitMessage(code);
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::game_platform::do_events()
{
    if(!m_ImplPtr->is_exiting)
    {
        MSG msg = {};
        while(PeekMessage(&msg,       // lpMsg
                          nullptr,    // hWnd
                          0,          // wMsgFilterMin
                          0,          // wMsgFilterMax
                          PM_REMOVE)) // wRemoveMsg
        {
            if(msg.message == WM_QUIT)
            {
                m_ImplPtr->is_exiting = true;
                m_ImplPtr->exit_code = static_cast<int>(msg.wParam);

                on_exit();
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return !m_ImplPtr->is_exiting;
}

// ====================================================================================================================

/*static*/ LRESULT CALLBACK m1::game_platform::impl::WndProc(HWND const hWnd,
                                                             UINT const message,
                                                             WPARAM const wParam,
                                                             LPARAM const lParam)
{
    LONG_PTR const wnd_user_data = GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if(wnd_user_data)
    {
        m1::game_platform * const game_platform_ptr = reinterpret_cast<m1::game_platform*>(wnd_user_data);

        switch(message)
        {
            case WM_PAINT:
                game_platform_ptr->on_display();
                break;

            case WM_CLOSE:
                game_platform_ptr->on_close();
                break;

            case WM_DESTROY:
                game_platform_ptr->on_destroy();
                break;

            case WM_SETFOCUS:
                game_platform_ptr->on_focus_won();
                break;

            case WM_KILLFOCUS:
                game_platform_ptr->on_focus_lost();
                break;

            case WM_SIZE:
                game_platform_ptr->on_resize(GET_X_LPARAM(lParam),  // width
                                             GET_Y_LPARAM(lParam)); // height
                break;

            default:
                break;
        }
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}

// ====================================================================================================================

/*static*/ const WCHAR* GetWNDCLASS(HINSTANCE const hInstance)
{
    static WNDCLASSW const wc =
    {
        CS_OWNDC,                           // style
        m1::game_platform::impl::WndProc,   // lpfnWndProc
        0,                                  // cbClsExtra
        0,                                  // cbWndExtra
        hInstance,                          // hInstance
        LoadIcon(nullptr, IDI_APPLICATION), // hIcon
        LoadCursor(nullptr, IDC_ARROW),     // hCursor
        GetSysColorBrush(COLOR_WINDOW),     // hbrBackground
        nullptr,                            // lpszMenuName
        L"M1_GAME_WNDCLASS",                // lpszClassName
    };

    assert(wc.hInstance == hInstance);

    static WCHAR const *result = MAKEINTRESOURCEW(RegisterClassW(&wc));
    return result;
}

// ====================================================================================================================

static HWND CreateWND(HINSTANCE const hInstance,
                      std::string const &window_name)
{
    std::wstring const window_wname(window_name.begin(), window_name.end());

    HWND const wnd = CreateWindowExW(0,                      // dwExStyle
                                     GetWNDCLASS(hInstance), // lpClassName
                                     window_wname.c_str(),   // lpWindowName
                                     WS_OVERLAPPEDWINDOW,    // dwStyle
                                     CW_USEDEFAULT,          // X
                                     CW_USEDEFAULT,          // Y
                                     CW_USEDEFAULT,          // nWidth
                                     CW_USEDEFAULT,          // nHeight
                                     HWND_DESKTOP,           // hWndParent
                                     nullptr,                // hMenu
                                     hInstance,              // hInstance
                                     nullptr);               // lpParam
    return wnd;
}

// ====================================================================================================================
