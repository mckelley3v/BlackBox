#include "m1/game_platform.hpp"

// ====================================================================================================================

std::string const& m1::game_platform::get_name() const
{
    return m_Name;
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_idle()
{
    event_idle.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_display()
{
    event_display.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_close()
{
    event_close.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_destroy()
{
    event_destroy.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_exit()
{
    event_exit.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_focus_won()
{
    event_focus_won.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_focus_lost()
{
    event_focus_lost.emit();
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::game_platform::on_resize(int width, int height)
{
    event_resize.emit(width, height);
}

// ====================================================================================================================
