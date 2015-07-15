#ifndef M1_GRAPHICS_TEXTURE_DEPTH_TARGET_HPP
#define M1_GRAPHICS_TEXTURE_DEPTH_TARGET_HPP

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_texture_depth_target_2D
    {
    public:
        graphics_texture_depth_target_2D(graphics_texture_depth_target_2D &&rhs) = default;
        graphics_texture_depth_target_2D& operator = (graphics_texture_depth_target_2D &&rhs) = default;
        virtual ~graphics_texture_depth_target_2D() = default;

    private:
        graphics_texture_depth_target_2D() = delete;
        graphics_texture_depth_target_2D(graphics_texture_depth_target_2D const &rhs) = delete;
        graphics_texture_depth_target_2D& operator = (graphics_texture_depth_target_2D const &rhs) = delete;

        // members:
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_TEXTURE_DEPTH_TARGET_HPP
