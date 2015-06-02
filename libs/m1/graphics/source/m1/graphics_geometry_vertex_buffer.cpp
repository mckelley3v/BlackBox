#include "m1/graphics_geometry_vertex_buffer.hpp"
#include "m1/impl/graphics_geometry_vertex_buffer_impl.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_geometry_vertex_buffer::graphics_geometry_vertex_buffer(std::shared_ptr<graphics_geometry_vertex_buffer_impl> const &impl_ptr)
    : graphics_memory_buffer(impl_ptr)
{
}

// ======================================================================================================
