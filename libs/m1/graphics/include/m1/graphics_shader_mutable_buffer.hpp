#ifndef M1_GRAPHICS_SHADER_MUTABLE_BUFFER_HPP
#define M1_GRAPHICS_SHADER_MUTABLE_BUFFER_HPP

#include "m1/graphics_memory_buffer.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_shader_mutable_buffer_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_shader_mutable_buffer
        : public graphics_memory_buffer
    {
    friend class graphics_device;
    public:
        graphics_shader_mutable_buffer(graphics_shader_mutable_buffer &&rhs) = default;
        graphics_shader_mutable_buffer(graphics_shader_mutable_buffer const &rhs) = default;
        graphics_shader_mutable_buffer& operator = (graphics_shader_mutable_buffer &&rhs) = default;
        graphics_shader_mutable_buffer& operator = (graphics_shader_mutable_buffer const &rhs) = default;
        virtual ~graphics_shader_mutable_buffer() override = default;

    private:
        graphics_shader_mutable_buffer() = delete;
        explicit graphics_shader_mutable_buffer(std::shared_ptr<graphics_shader_mutable_buffer_impl> const &impl_ptr);

        graphics_shader_mutable_buffer_impl* impl_ptr();
        graphics_shader_mutable_buffer_impl const* get_impl_ptr() const;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_SHADER_MUTABLE_BUFFER_HPP
