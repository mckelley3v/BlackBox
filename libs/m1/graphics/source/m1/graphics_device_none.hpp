#ifndef M1_GRAPHICS_DEVICE_NONE_HPP
#define M1_GRAPHICS_DEVICE_NONE_HPP

#include "m1/graphics_device_impl.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_device_none
        : public graphics_device_impl
    {
    public:
        graphics_device_none() = default;
        virtual ~graphics_device_none() = default;

        virtual graphics_api get_api() const override;
        virtual void execute(graphics_command_queue const &queue) override;

    private:
        graphics_device_none(graphics_device_none &&rhs) = delete;
        graphics_device_none(graphics_device_none const &rhs) = delete;
        graphics_device_none& operator = (graphics_device_none &&rhs) = delete;
        graphics_device_none& operator = (graphics_device_none const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_DEVICE_NONE_HPP
