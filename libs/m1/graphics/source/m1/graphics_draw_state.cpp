#include "m1/graphics_draw_state.hpp"

// =====================================================================================================================

/*explicit*/ m1::graphics_draw_state::graphics_draw_state(graphics_raster_state const &state)
    : graphics_draw_state()
{
    set_state(state);
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::graphics_draw_state::graphics_draw_state(graphics_color_target_state const &state)
    : graphics_draw_state()
{
    set_state(state);
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::graphics_draw_state::graphics_draw_state(graphics_depth_target_state const &state)
    : graphics_draw_state()
{
    set_state(state);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::graphics_draw_state::is_raster_state_default() const
{
    return (m_StateMask & state_bits::raster_bit) ? true : false;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_raster_state& m1::graphics_draw_state::raster_state()
{
    m_StateMask |= state_bits::raster_bit;
    return m_Raster;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_raster_state const& m1::graphics_draw_state::get_raster_state() const
{
    return m_Raster;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::graphics_draw_state::is_color_target_state_default() const
{
    return (m_StateMask & state_bits::color_target_bit) ? true : false;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_color_target_state& m1::graphics_draw_state::color_target_state()
{
    m_StateMask |= state_bits::color_target_bit;
    return m_ColorTarget;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_color_target_state const& m1::graphics_draw_state::get_color_target_state() const
{
    return m_ColorTarget;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::graphics_draw_state::is_depth_target_state_default() const
{
    return (m_StateMask & state_bits::depth_target_bit) ? true : false;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_depth_target_state& m1::graphics_draw_state::depth_target_state()
{
    m_StateMask |= state_bits::depth_target_bit;
    return m_DepthTarget;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_depth_target_state const& m1::graphics_draw_state::get_depth_target_state() const
{
    return m_DepthTarget;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::graphics_draw_state::set_state(graphics_raster_state const &state)
{
    raster_state() = state;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::graphics_draw_state::set_state(graphics_color_target_state const &state)
{
    color_target_state() = state;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::graphics_draw_state::set_state(graphics_depth_target_state const &state)
{
    depth_target_state() = state;
}

// =====================================================================================================================

m1::graphics_draw_state m1::merge_graphics_state(graphics_draw_state const &original,
                                                 graphics_draw_state const &override)
{
    graphics_draw_state result = original;

    if(!override.is_raster_state_default())
    {
        result.raster_state() = override.get_raster_state();
    }

    if(!override.is_color_target_state_default())
    {
        result.color_target_state() = override.get_color_target_state();
    }

    if(!override.is_depth_target_state_default())
    {
        result.depth_target_state() = override.get_depth_target_state();
    }

    return result;
}

// =====================================================================================================================
