#ifndef M1_GRAPHICS_DRAW_TARGET_HPP
#define M1_GRAPHICS_DRAW_TARGET_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_draw_target_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_draw_target
    {
    friend class graphics_device;
    public:
        graphics_draw_target(graphics_draw_target &&rhs) = default;
        graphics_draw_target(graphics_draw_target const &rhs) = default;
        graphics_draw_target& operator = (graphics_draw_target &&rhs) = default;
        graphics_draw_target& operator = (graphics_draw_target const &rhs) = default;
        virtual ~graphics_draw_target() = default;

    private:
        graphics_draw_target() = delete;
        explicit graphics_draw_target(std::shared_ptr<graphics_draw_target_impl> const &impl_ptr);

        // members:
        std::shared_ptr<graphics_draw_target_impl> m_ImplPtr;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_DRAW_TARGET_HPP
