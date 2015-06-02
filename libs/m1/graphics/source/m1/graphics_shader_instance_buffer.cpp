#include "m1/graphics_shader_instance_buffer.hpp"
#include "m1/impl/graphics_shader_instance_buffer_impl.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_shader_instance_buffer::graphics_shader_instance_buffer(std::shared_ptr<graphics_shader_instance_buffer_impl> const &impl_ptr)
    : graphics_memory_buffer(impl_ptr)
{
}

// ======================================================================================================
