#ifndef M1_GAME_PLATFORM_HPP
#define M1_GAME_PLATFORM_HPP

#include "m1/signal.hpp"
#include <memory>

// ====================================================================================================================

namespace m1
{
namespace input
{
    // ================================================================================================================

    enum class keyboard_button
    {
        unknown,

//A	A key
//Add	Add key
//Apps	Applications key
//Attn	Attn key
//B	B key
//Back	BACKSPACE key
//BrowserBack	Windows 2000/XP: Browser Back key
//BrowserFavorites	Windows 2000/XP: Browser Favorites key
//BrowserForward	Windows 2000/XP: Browser Forward key
//BrowserHome	Windows 2000/XP: Browser Start and Home key
//BrowserRefresh	Windows 2000/XP: Browser Refresh key
//BrowserSearch	Windows 2000/XP: Browser Search key
//BrowserStop	Windows 2000/XP: Browser Stop key
//C	C key
//CapsLock	CAPS LOCK key
//ChatPadGreen	Green ChatPad key
//ChatPadOrange	Orange ChatPad key
//Crsel	CrSel key
//D	D key
//D0	Used for miscellaneous characters; it can vary by keyboard.
//D1	Used for miscellaneous characters; it can vary by keyboard.
//D2	Used for miscellaneous characters; it can vary by keyboard.
//D3	Used for miscellaneous characters; it can vary by keyboard.
//D4	Used for miscellaneous characters; it can vary by keyboard.
//D5	Used for miscellaneous characters; it can vary by keyboard.
//D6	Used for miscellaneous characters; it can vary by keyboard.
//D7	Used for miscellaneous characters; it can vary by keyboard.
//D8	Used for miscellaneous characters; it can vary by keyboard.
//D9	Used for miscellaneous characters; it can vary by keyboard.
//Decimal	Decimal key
//Delete	DEL key
//Divide	Divide key
//Down	DOWN ARROW key
//E	E key
//End	END key
//Enter	ENTER key
//EraseEof	Erase EOF key
//Escape	ESC key
//Execute	EXECUTE key
//Exsel	ExSel key
//F	F key
//F1	F1 key
//F10	F10 key
//F11	F11 key
//F12	F12 key
//F13	F13 key
//F14	F14 key
//F15	F15 key
//F16	F16 key
//F17	F17 key
//F18	F18 key
//F19	F19 key
//F2	F2 key
//F20	F20 key
//F21	F21 key
//F22	F22 key
//F23	F23 key
//F24	F24 key
//F3	F3 key
//F4	F4 key
//F5	F5 key
//F6	F6 key
//F7	F7 key
//F8	F8 key
//F9	F9 key
//G	G key
//H	H key
//Help	HELP key
//Home	HOME key
//I	I key
//ImeConvert	IME Convert key
//ImeNoConvert	IME NoConvert key
//Insert	INS key
//J	J key
//K	K key
//Kana	Kana key on Japanese keyboards
//Kanji	Kanji key on Japanese keyboards
//L	L key
//LaunchApplication1	Windows 2000/XP: Start Application 1 key
//LaunchApplication2	Windows 2000/XP: Start Application 2 key
//LaunchMail	Windows 2000/XP: Start Mail key
//Left	LEFT ARROW key
//LeftAlt	Left ALT key
//LeftControl	Left CONTROL key
//LeftShift	Left SHIFT key
//LeftWindows	Left Windows key
//M	M key
//MediaNextTrack	Windows 2000/XP: Next Track key
//MediaPlayPause	Windows 2000/XP: Play/Pause Media key
//MediaPreviousTrack	Windows 2000/XP: Previous Track key
//MediaStop	Windows 2000/XP: Stop Media key
//Multiply	Multiply key
//N	N key
//None	Reserved
//NumLock	NUM LOCK key
//NumPad0	Numeric keypad 0 key
//NumPad1	Numeric keypad 1 key
//NumPad2	Numeric keypad 2 key
//NumPad3	Numeric keypad 3 key
//NumPad4	Numeric keypad 4 key
//NumPad5	Numeric keypad 5 key
//NumPad6	Numeric keypad 6 key
//NumPad7	Numeric keypad 7 key
//NumPad8	Numeric keypad 8 key
//NumPad9	Numeric keypad 9 key
//O	O key
//Oem8	Used for miscellaneous characters; it can vary by keyboard.
//OemAuto	OEM Auto key
//OemBackslash	Windows 2000/XP: The OEM angle bracket or backslash key on the RT 102 key keyboard
//OemClear	CLEAR key
//OemCloseBrackets	Windows 2000/XP: The OEM close bracket key on a US standard keyboard
//OemComma	Windows 2000/XP: For any country/region, the ',' key
//OemCopy	OEM Copy key
//OemEnlW	OEM Enlarge Window key
//OemMinus	Windows 2000/XP: For any country/region, the '-' key
//OemOpenBrackets	Windows 2000/XP: The OEM open bracket key on a US standard keyboard
//OemPeriod	Windows 2000/XP: For any country/region, the '.' key
//OemPipe	Windows 2000/XP: The OEM pipe key on a US standard keyboard
//OemPlus	Windows 2000/XP: For any country/region, the '+' key
//OemQuestion	Windows 2000/XP: The OEM question mark key on a US standard keyboard
//OemQuotes	Windows 2000/XP: The OEM singled/double quote key on a US standard keyboard
//OemSemicolon	Windows 2000/XP: The OEM Semicolon key on a US standard keyboard
//OemTilde	Windows 2000/XP: The OEM tilde key on a US standard keyboard
//P	P key
//Pa1	PA1 key
//PageDown	PAGE DOWN key
//PageUp	PAGE UP key
//Pause	PAUSE key
//Play	Play key
//Print	PRINT key
//PrintScreen	PRINT SCREEN key
//ProcessKey	Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key
//Q	Q key
//R	R key
//Right	RIGHT ARROW key
//RightAlt	Right ALT key
//RightControl	Right CONTROL key
//RightShift	Right SHIFT key
//RightWindows	Right Windows key
//S	S key
//Scroll	SCROLL LOCK key
//Select	SELECT key
//SelectMedia	Windows 2000/XP: Select Media key
//Separator	Separator key
//Sleep	Computer Sleep key
//Space	SPACEBAR
//Subtract	Subtract key
//T	T key
//Tab	TAB key
//U	U key
//Up	UP ARROW key
//V	V key
//VolumeDown	Windows 2000/XP: Volume Down key
//VolumeMute	Windows 2000/XP: Volume Mute key
//VolumeUp	Windows 2000/XP: Volume Up key
//W	W key
//X	X key
//Y	Y key
//Z	Z key
//Zoom	Zoom key
    };

    // ================================================================================================================

    enum class mouse_button
    {
        left,
        middle,
        right,
        x1,
        x2,
    };

    // ================================================================================================================
} // namespace input
} // namespace m1

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    class game_platform
    {
    public:
        // types:
        struct impl;

        // construct/move/destroy:
        game_platform();
        game_platform(game_platform &&rhs);
        game_platform& operator = (game_platform &&rhs);
        ~game_platform();

        // impl:
        impl& platform_impl();
        impl const& get_platform_impl() const;

        // methods:
        int run();
        void exit(int code = 0);

        // system events:
        m1::signal<void()> event_idle;
        m1::signal<void()> event_display;
        m1::signal<void()> event_close;
        m1::signal<void()> event_destroy;
        m1::signal<void()> event_exit;
        m1::signal<void()> event_focus_won;
        m1::signal<void()> event_focus_lost;
        m1::signal<void(int width, int height)> event_resize;

        // keyboard events:
        m1::signal<void(input::keyboard_button button)> event_keyboard_button_click;
        m1::signal<void(input::keyboard_button button)> event_keyboard_button_press;
        m1::signal<void(input::keyboard_button button)> event_keyboard_button_release;

        // mouse events:
        // (x, y) is in NDC coordinates: [-1, +1] X [-1, +1]
        // where (-1, -1) is lower-left of screen and (+1, +1) is upper-right of screen
        m1::signal<void(float x, float y)> event_mouse_moved;
        m1::signal<void(int wheel, float x, float y)> event_mouse_wheel_change;
        m1::signal<void(input::mouse_button button, float x, float y)> event_mouse_button_click;
        m1::signal<void(input::mouse_button button, float x, float y)> event_mouse_button_double_click;
        m1::signal<void(input::mouse_button button, float x, float y)> event_mouse_button_press;
        m1::signal<void(input::mouse_button button, float x, float y)> event_mouse_button_drag;
        m1::signal<void(input::mouse_button button, float x, float y)> event_mouse_button_release;

        // gamepad events:

        // joystick events:

        // touch events:

    private:
        bool do_events();
        virtual void on_idle();
        virtual void on_display();
        virtual void on_close();
        virtual void on_destroy();
        virtual void on_exit();
        virtual void on_focus_won();
        virtual void on_focus_lost();
        virtual void on_resize(int width, int height);

        game_platform(game_platform const &rhs) = delete;
        game_platform& operator = (game_platform const &rhs) = delete;

        // members:
        std::unique_ptr<impl> m_ImplPtr;
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_GAME_PLATFORM_HPP
