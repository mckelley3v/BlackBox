#ifndef M1_GRAPHICS_SHADER_INSTANCE_BUFFER_HPP
#define M1_GRAPHICS_SHADER_INSTANCE_BUFFER_HPP

#include "m1/graphics_memory_buffer.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_shader_instance_buffer_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_shader_instance_buffer
        : public graphics_memory_buffer
    {
    friend class graphics_device;
    public:
        graphics_shader_instance_buffer(graphics_shader_instance_buffer &&rhs) = default;
        graphics_shader_instance_buffer(graphics_shader_instance_buffer const &rhs) = default;
        graphics_shader_instance_buffer& operator = (graphics_shader_instance_buffer &&rhs) = default;
        graphics_shader_instance_buffer& operator = (graphics_shader_instance_buffer const &rhs) = default;
        virtual ~graphics_shader_instance_buffer() override = default;

    private:
        graphics_shader_instance_buffer() = delete;
        explicit graphics_shader_instance_buffer(std::shared_ptr<graphics_shader_instance_buffer_impl> const &impl_ptr);

        graphics_shader_instance_buffer_impl* impl_ptr();
        graphics_shader_instance_buffer_impl const* get_impl_ptr() const;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_SHADER_INSTANCE_BUFFER_HPP
