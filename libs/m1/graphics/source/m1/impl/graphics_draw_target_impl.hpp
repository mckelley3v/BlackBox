#ifndef M1_GRAPHICS_DRAW_TARGET_IMPL_HPP
#define M1_GRAPHICS_DRAW_TARGET_IMPL_HPP

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_draw_target_impl
    {
    public:
        graphics_draw_target_impl() = default;
        virtual ~graphics_draw_target_impl() = default;

    private:
        graphics_draw_target_impl(graphics_draw_target_impl &&rhs) = delete;
        graphics_draw_target_impl(graphics_draw_target_impl const &rhs) = delete;
        graphics_draw_target_impl& operator = (graphics_draw_target_impl &&rhs) = delete;
        graphics_draw_target_impl& operator = (graphics_draw_target_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_DRAW_TARGET_IMPL_HPP
