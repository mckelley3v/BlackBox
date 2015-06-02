#ifndef M1_GRAPHICS_COMMAND_QUEUE_IMPL_HPP
#define M1_GRAPHICS_COMMAND_QUEUE_IMPL_HPP

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_command_queue_impl
    {
    public:
        graphics_command_queue_impl() = default;
        virtual ~graphics_command_queue_impl() = default;

    private:
        graphics_command_queue_impl(graphics_command_queue_impl &&rhs) = delete;
        graphics_command_queue_impl(graphics_command_queue_impl const &rhs) = delete;
        graphics_command_queue_impl& operator = (graphics_command_queue_impl &&rhs) = delete;
        graphics_command_queue_impl& operator = (graphics_command_queue_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_COMMAND_QUEUE_IMPL_HPP
