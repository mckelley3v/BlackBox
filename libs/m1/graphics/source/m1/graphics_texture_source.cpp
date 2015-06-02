#include "m1/graphics_texture_source.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_texture_source::graphics_texture_source(std::shared_ptr<graphics_texture_source_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
    assert(m_ImplPtr && "Invalid graphics_texture_source");
}

// ======================================================================================================
