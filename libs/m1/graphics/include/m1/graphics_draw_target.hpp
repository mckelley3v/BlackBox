#ifndef M1_GRAPHICS_DRAW_TARGET_HPP
#define M1_GRAPHICS_DRAW_TARGET_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_command_queue;
    class graphics_draw_target_state;
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

        graphics_draw_target_state& state();
        graphics_draw_target_state const& get_state() const;

        //std::future<graphics_texture_source> resolve_color_texture_source(graphics_command_queue &queue, int draw_target_index = 0);
        //std::future<graphics_texture_source> resolve_depth_texture_source(graphics_command_queue &queue);

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
