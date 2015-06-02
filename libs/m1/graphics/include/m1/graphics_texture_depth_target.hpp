#ifndef M1_GRAPHICS_TEXTURE_DEPTH_TARGET_HPP
#define M1_GRAPHICS_TEXTURE_DEPTH_TARGET_HPP

#include "m1/graphics_texture_source.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_texture_depth_target_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_texture_depth_target
        : public graphics_texture_source
    {
    friend class graphics_device;
    public:
        graphics_texture_depth_target(graphics_texture_depth_target &&rhs) = default;
        graphics_texture_depth_target(graphics_texture_depth_target const &rhs) = default;
        graphics_texture_depth_target& operator = (graphics_texture_depth_target &&rhs) = default;
        graphics_texture_depth_target& operator = (graphics_texture_depth_target const &rhs) = default;
        virtual ~graphics_texture_depth_target() override = default;

    private:
        graphics_texture_depth_target() = delete;
        explicit graphics_texture_depth_target(std::shared_ptr<graphics_texture_depth_target_impl> const &impl_ptr);

        graphics_texture_depth_target_impl* impl_ptr();
        graphics_texture_depth_target_impl const* get_impl_ptr() const;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_TEXTURE_DEPTH_TARGET_HPP
