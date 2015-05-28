#ifndef M1_GRAPHICS_COMMAND_QUEUE_NONE_HPP
#define M1_GRAPHICS_COMMAND_QUEUE_NONE_HPP

#include "m1/graphics_command_queue_impl.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_command_queue_none
        : public graphics_command_queue_impl
    {
    public:
        graphics_command_queue_none() = default;
        virtual ~graphics_command_queue_none() override = default;

    private:
        graphics_command_queue_none(graphics_command_queue_none &&rhs) = delete;
        graphics_command_queue_none(graphics_command_queue_none const &rhs) = delete;
        graphics_command_queue_none& operator = (graphics_command_queue_none &&rhs) = delete;
        graphics_command_queue_none& operator = (graphics_command_queue_none const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_COMMAND_QUEUE_NONE_HPP
