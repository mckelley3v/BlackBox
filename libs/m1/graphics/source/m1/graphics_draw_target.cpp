#include "m1/graphics_draw_target.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_draw_target::graphics_draw_target(std::shared_ptr<graphics_draw_target_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
    assert(m_ImplPtr && "Invalid graphics_draw_target");
}

// ======================================================================================================
