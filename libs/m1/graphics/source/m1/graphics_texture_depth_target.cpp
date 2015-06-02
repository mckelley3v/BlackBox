#include "m1/graphics_texture_depth_target.hpp"
#include "m1/impl/graphics_texture_depth_target_impl.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_texture_depth_target::graphics_texture_depth_target(std::shared_ptr<graphics_texture_depth_target_impl> const &impl_ptr)
    : graphics_texture_source(impl_ptr)
{
}

// ======================================================================================================
