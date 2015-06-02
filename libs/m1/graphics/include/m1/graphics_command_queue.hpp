#ifndef M1_GRAPHICS_COMMAND_QUEUE_HPP
#define M1_GRAPHICS_COMMAND_QUEUE_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_device;
    class graphics_command_queue_impl;

    // ==================================================================================================

    class graphics_command_queue
    {
    friend class graphics_device;
    public:
        graphics_command_queue(graphics_command_queue &&rhs) = default;
        graphics_command_queue& operator = (graphics_command_queue &&rhs) = default;
        ~graphics_command_queue() = default;

        // possible methods:

        //void draw(graphics_framebuffer &framebuffer,
        //          graphics_mesh const &mesh,
        //          graphics_draw_state const &draw_state,
        //          graphics_instance_data const &instance_data);

    private:
        graphics_command_queue() = delete;
        graphics_command_queue(graphics_command_queue const &rhs) = delete;
        graphics_command_queue& operator = (graphics_command_queue const &rhs) = delete;
        explicit graphics_command_queue(std::shared_ptr<graphics_command_queue_impl> const &impl_ptr);

        // members:
        std::shared_ptr<graphics_command_queue_impl> m_ImplPtr;
    };
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_COMMAND_QUEUE_HPP
