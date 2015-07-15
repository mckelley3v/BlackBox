#ifndef M1_GRAPHICS_DEVICE_HPP
#define M1_GRAPHICS_DEVICE_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    enum class graphics_api
    {
        none,
        d3d_11,
        d3d_12,
        gl_2,
        gl_3,
        gl_4,
        gles_2,
        gles_3,
        vk_1,
    };

    // --------------------------------------------------------------------------------------------------

    class graphics_command_queue;
    class graphics_draw_target;
    class graphics_geometry_index_buffer;
    class graphics_geometry_vertex_buffer;
    class graphics_memory_buffer;
    class graphics_shader_const_buffer;
    class graphics_shader_mutable_buffer;
    class graphics_shader_instance_buffer;
    class graphics_texture_1D;
    class graphics_texture_2D;
    class graphics_texture_3D;
    class graphics_texture_cube;

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

    // --------------------------------------------------------------------------------------------------

    class graphics_device_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_device
    {
    public:
        explicit graphics_device(graphics_api api);
        graphics_device(graphics_device &&rhs) = default;
        graphics_device& operator = (graphics_device &&rhs) = default;
        ~graphics_device() = default;

        // properties:
        graphics_api get_api() const;
        graphics_draw_target& main_draw_target();
        graphics_draw_target const& get_main_draw_target() const;

        // factory:
        graphics_command_queue make_command_queue();
        graphics_draw_target make_draw_target(graphics_draw_target_definition const &definition);
        graphics_geometry_index_buffer make_geometry_index_buffer(graphics_geometry_index_buffer_definition const &definition);
        graphics_geometry_vertex_buffer make_geometry_vertex_buffer(graphics_geometry_vertex_buffer_definition const &definition);
        graphics_memory_buffer make_memory_buffer(graphics_memory_buffer_definition const &definition);
        graphics_shader_const_buffer make_shader_const_buffer(graphics_shader_const_buffer_definition const &definition);
        graphics_shader_mutable_buffer make_shader_mutable_buffer(graphics_shader_mutable_buffer_definition const &definition);
        graphics_shader_instance_buffer make_shader_instance_buffer(graphics_shader_instance_buffer_definition const &definition);
        graphics_texture_1D make_texture(graphics_texture_1D_definition const &definition);
        graphics_texture_2D make_texture(graphics_texture_2D_definition const &definition);
        graphics_texture_3D make_texture(graphics_texture_3D_definition const &definition);
        graphics_texture_cube make_texture(graphics_texture_cube_definition const &definition);

        void execute(graphics_command_queue const &queue);

    private:
        graphics_device() = delete;
        graphics_device(graphics_device const &rhs) = delete;
        graphics_device& operator = (graphics_device const &rhs) = delete;

        // members:
        std::shared_ptr<graphics_device_impl> m_ImplPtr;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_DEVICE_HPP
