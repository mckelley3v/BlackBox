#include "m1/graphics_draw_target.hpp"
#include "m1/impl/graphics_draw_target_impl.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_draw_target::graphics_draw_target(std::shared_ptr<graphics_draw_target_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
    assert(m_ImplPtr && "Invalid graphics_draw_target");
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_draw_target_state& m1::graphics_draw_target::state()
{
    return m_ImplPtr->state();
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_draw_target_state const& m1::graphics_draw_target::get_state() const
{
    return m_ImplPtr->get_state();
}

// ======================================================================================================
