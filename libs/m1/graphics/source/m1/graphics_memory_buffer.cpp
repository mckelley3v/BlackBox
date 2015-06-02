#include "m1/graphics_memory_buffer.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_memory_buffer::graphics_memory_buffer(std::shared_ptr<graphics_memory_buffer_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
    assert(m_ImplPtr && "Invalid graphics_memory_buffer");
}

// ======================================================================================================
