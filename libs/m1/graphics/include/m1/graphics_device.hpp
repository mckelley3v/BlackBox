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
        gl_2_1,
        gl_3_3_core,
        gl_4_4_core,
        gles_2_0,
        gles_3_1,
        vk_1_0,
    };

    // --------------------------------------------------------------------------------------------------

    class graphics_command_queue;
    class graphics_texture_source;
    class graphics_texture_color_target;
    class graphics_texture_depth_target;
    class graphics_draw_target;
    class graphics_memory_buffer;
    class graphics_geometry_index_buffer;
    class graphics_geometry_vertex_buffer;
    class graphics_shader_const_buffer;
    class graphics_shader_mutable_buffer;
    class graphics_shader_instance_buffer;

    struct graphics_texture_source_definition;
    struct graphics_texture_color_target_definition;
    struct graphics_texture_depth_target_definition;
    struct graphics_draw_target_definition;
    struct graphics_memory_buffer_definition;
    struct graphics_geometry_index_buffer_definition;
    struct graphics_geometry_vertex_buffer_definition;
    struct graphics_shader_const_buffer_definition;
    struct graphics_shader_mutable_buffer_definition;
    struct graphics_shader_instance_buffer_definition;

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
        graphics_texture_source make_texture_source(graphics_texture_source_definition const &definition);
        graphics_texture_color_target make_texture_color_target(graphics_texture_color_target_definition const &definition);
        graphics_texture_depth_target make_texture_depth_target(graphics_texture_depth_target_definition const &definition);
        graphics_draw_target make_draw_target(graphics_draw_target_definition const &definition);
        graphics_memory_buffer make_memory_buffer(graphics_memory_buffer_definition const &definition);
        graphics_geometry_index_buffer make_geometry_index_buffer(graphics_geometry_index_buffer_definition const &definition);
        graphics_geometry_vertex_buffer make_geometry_vertex_buffer(graphics_geometry_vertex_buffer_definition const &definition);
        graphics_shader_const_buffer make_shader_const_buffer(graphics_shader_const_buffer_definition const &definition);
        graphics_shader_mutable_buffer make_shader_mutable_buffer(graphics_shader_mutable_buffer_definition const &definition);
        graphics_shader_instance_buffer make_shader_instance_buffer(graphics_shader_instance_buffer_definition const &definition);

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
