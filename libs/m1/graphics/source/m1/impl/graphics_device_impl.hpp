#ifndef M1_GRAPHICS_DEVICE_IMPL_HPP
#define M1_GRAPHICS_DEVICE_IMPL_HPP

#include "m1/graphics_device.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_command_queue_impl;
    class graphics_draw_target_impl;
    class graphics_geometry_index_buffer_impl;
    class graphics_geometry_vertex_buffer_impl;
    class graphics_memory_buffer_impl;
    class graphics_shader_const_buffer_impl;
    class graphics_shader_mutable_buffer_impl;
    class graphics_shader_instance_buffer_impl;
    class graphics_texture_1D_impl;
    class graphics_texture_2D_impl;
    class graphics_texture_3D_impl;
    class graphics_texture_cube_impl;

    struct graphics_draw_target_definition;
    struct graphics_geometry_index_buffer_definition;
    struct graphics_geometry_vertex_buffer_definition;
    struct graphics_memory_buffer_definition;
    struct graphics_shader_const_buffer_definition;
    struct graphics_shader_mutable_buffer_definition;
    struct graphics_shader_instance_buffer_definition;
    struct graphics_texture_1D_definition;
    struct graphics_texture_2D_definition;
    struct graphics_texture_3D_definition;
    struct graphics_texture_cube_definition;

    // ==================================================================================================

    class graphics_device_impl
    {
    public:
        graphics_device_impl() = default;
        virtual ~graphics_device_impl() = default;

        // properties:
        virtual graphics_api get_api() const = 0;

        // factory:
        virtual std::shared_ptr<graphics_command_queue_impl> make_command_queue_impl() = 0;
        virtual std::shared_ptr<graphics_draw_target_impl> make_draw_target(graphics_draw_target_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_memory_buffer_impl> make_memory_buffer(graphics_memory_buffer_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_geometry_index_buffer_impl> make_geometry_index_buffer(graphics_geometry_index_buffer_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_geometry_vertex_buffer_impl> make_geometry_vertex_buffer(graphics_geometry_vertex_buffer_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_shader_const_buffer_impl> make_shader_const_buffer(graphics_shader_const_buffer_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_shader_mutable_buffer_impl> make_shader_mutable_buffer(graphics_shader_mutable_buffer_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_shader_instance_buffer_impl> make_shader_instance_buffer(graphics_shader_instance_buffer_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_texture_1D_impl> make_texture(graphics_texture_1D_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_texture_2D_impl> make_texture(graphics_texture_2D_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_texture_3D_impl> make_texture(graphics_texture_3D_definition const &definition) = 0;
        virtual std::shared_ptr<graphics_texture_cube_impl> make_texture(graphics_texture_cube_definition const &definition) = 0;

        // device:
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
