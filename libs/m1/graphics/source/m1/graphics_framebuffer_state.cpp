#include "m1/graphics_framebuffer_state.hpp"

// =====================================================================================================================

/*explicit*/ m1::graphics_framebuffer_state::graphics_framebuffer_state(int const width,
                                                                        int const height,
                                                                        graphics_multisampling_count const multisampling_count)
    : graphics_framebuffer_state()
{
    graphics_viewport_state const viewport = {0, // x
                                              0, // y
                                              width,
                                              height};
    viewport_state() = viewport;

    if(multisampling_count != get_multisampling_state().count)
    {
        graphics_multisampling_state const multisampling = {multisampling_count,
                                                            graphics_multisampling_bits::all};
        multisampling_state() = multisampling;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::graphics_framebuffer_state::graphics_framebuffer_state(graphics_viewport_state const &state)
    : graphics_framebuffer_state()
{
    set_state(state);
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::graphics_framebuffer_state::graphics_framebuffer_state(graphics_scissor_state const &state)
    : graphics_framebuffer_state()
{
    set_state(state);
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::graphics_framebuffer_state::graphics_framebuffer_state(graphics_multisampling_state const &state)
    : graphics_framebuffer_state()
{
    set_state(state);
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::graphics_framebuffer_state::is_viewport_state_default() const
{
    return (m_StateMask & state_bits::viewport_bit) ? true : false;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_viewport_state& m1::graphics_framebuffer_state::viewport_state()
{
    m_StateMask |= state_bits::viewport_bit;
    return m_Viewport;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_viewport_state const& m1::graphics_framebuffer_state::get_viewport_state() const
{
    return m_Viewport;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::graphics_framebuffer_state::is_scissor_state_default() const
{
    return (m_StateMask & state_bits::scissor_bit) ? true : false;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_scissor_state& m1::graphics_framebuffer_state::scissor_state()
{
    m_StateMask |= state_bits::scissor_bit;
    return m_Scissor;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_scissor_state const& m1::graphics_framebuffer_state::get_scissor_state() const
{
    return m_Scissor;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::graphics_framebuffer_state::is_multisampling_state_default() const
{
    return (m_StateMask & state_bits::multisampling_bit) ? true : false;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_multisampling_state& m1::graphics_framebuffer_state::multisampling_state()
{
    m_StateMask |= state_bits::multisampling_bit;
    return m_Multisampling;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::graphics_multisampling_state const& m1::graphics_framebuffer_state::get_multisampling_state() const
{
    return m_Multisampling;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::graphics_framebuffer_state::set_state(graphics_viewport_state const &state)
{
    viewport_state() = state;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::graphics_framebuffer_state::set_state(graphics_scissor_state const &state)
{
    scissor_state() = state;
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::graphics_framebuffer_state::set_state(graphics_multisampling_state const &state)
{
    multisampling_state() = state;
}

// =====================================================================================================================

m1::graphics_framebuffer_state m1::merge_graphics_state(graphics_framebuffer_state const &original,
                                                        graphics_framebuffer_state const &override)
{
    graphics_framebuffer_state result = original;

    if(override.is_viewport_state_default())
    {
        result.viewport_state() = override.get_viewport_state();
    }

    if(override.is_scissor_state_default())
    {
        result.scissor_state() = override.get_scissor_state();
    }

    if(override.is_multisampling_state_default())
    {
        result.multisampling_state() = override.get_multisampling_state();
    }

    return result;
}

// =====================================================================================================================
