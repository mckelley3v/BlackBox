#include "m1/graphics_geometry_index_buffer.hpp"
#include "m1/impl/graphics_geometry_index_buffer_impl.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_geometry_index_buffer::graphics_geometry_index_buffer(std::shared_ptr<graphics_geometry_index_buffer_impl> const &impl_ptr)
    : graphics_memory_buffer(impl_ptr)
{
}

// ======================================================================================================
