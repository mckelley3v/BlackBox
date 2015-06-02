#ifndef M1_GRAPHICS_TEXTURE_DEPTH_TARGET_IMPL_HPP
#define M1_GRAPHICS_TEXTURE_DEPTH_TARGET_IMPL_HPP

#include "m1/impl/graphics_texture_source_impl.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_texture_depth_target_impl
        : public graphics_texture_source_impl
    {
    public:
        graphics_texture_depth_target_impl() = default;
        virtual ~graphics_texture_depth_target_impl() = default;

    private:
        graphics_texture_depth_target_impl(graphics_texture_depth_target_impl &&rhs) = delete;
        graphics_texture_depth_target_impl(graphics_texture_depth_target_impl const &rhs) = delete;
        graphics_texture_depth_target_impl& operator = (graphics_texture_depth_target_impl &&rhs) = delete;
        graphics_texture_depth_target_impl& operator = (graphics_texture_depth_target_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_TEXTURE_DEPTH_TARGET_IMPL_HPP
