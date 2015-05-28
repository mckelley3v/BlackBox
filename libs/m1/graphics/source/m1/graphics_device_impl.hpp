#ifndef M1_GRAPHICS_DEVICE_IMPL_HPP
#define M1_GRAPHICS_DEVICE_IMPL_HPP

#include "m1/graphics_device.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_device_impl
    {
    public:
        graphics_device_impl() = default;
        virtual ~graphics_device_impl() = default;

        virtual graphics_api get_api() const = 0;
        virtual void execute(graphics_command_queue const &queue);

    private:
        graphics_device_impl(graphics_device_impl &&rhs) = delete;
        graphics_device_impl(graphics_device_impl const &rhs) = delete;
        graphics_device_impl& operator = (graphics_device_impl &&rhs) = delete;
        graphics_device_impl& operator = (graphics_device_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_DEVICE_IMPL_HPP
