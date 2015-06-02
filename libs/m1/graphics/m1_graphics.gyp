{
    'includes':
    [
        "../../../configurations.gypi",
    ],
    'targets':
    [
        {
            'target_name': "m1_graphics",
            'type': "static_library",
            'include_dirs':
            [
                "include",
                "source",
            ],
            'sources':
            [
                "include/m1/graphics_device.hpp",
                "include/m1/graphics_draw_state.hpp",
                "include/m1/graphics_draw_target_state.hpp",
                "include/m1/graphics_command_queue.hpp",
                "include/m1/graphics_texture_source.hpp",
                "include/m1/graphics_texture_color_target.hpp",
                "include/m1/graphics_texture_depth_target.hpp",
                "include/m1/graphics_draw_target.hpp",
                "include/m1/graphics_memory_buffer.hpp",
                "include/m1/graphics_geometry_index_buffer.hpp",
                "include/m1/graphics_geometry_vertex_buffer.hpp",
                "include/m1/graphics_shader_const_buffer.hpp",
                "include/m1/graphics_shader_mutable_buffer.hpp",
                "include/m1/graphics_shader_instance_buffer.hpp",
                "include/m1/graphics_state.hpp",
                "source/m1/impl/graphics_device_impl.hpp",
                "source/m1/impl/graphics_device_impl.cpp",
                "source/m1/impl/graphics_command_queue_impl.hpp",
                "source/m1/impl/graphics_command_queue_impl.cpp",
                "source/m1/impl/graphics_texture_source_impl.hpp",
                "source/m1/impl/graphics_texture_source_impl.cpp",
                "source/m1/impl/graphics_texture_color_target_impl.hpp",
                "source/m1/impl/graphics_texture_color_target_impl.cpp",
                "source/m1/impl/graphics_texture_depth_target_impl.hpp",
                "source/m1/impl/graphics_texture_depth_target_impl.cpp",
                "source/m1/impl/graphics_draw_target_impl.hpp",
                "source/m1/impl/graphics_draw_target_impl.cpp",
                "source/m1/impl/graphics_memory_buffer_impl.hpp",
                "source/m1/impl/graphics_memory_buffer_impl.cpp",
                "source/m1/impl/graphics_geometry_index_buffer_impl.hpp",
                "source/m1/impl/graphics_geometry_index_buffer_impl.cpp",
                "source/m1/impl/graphics_geometry_vertex_buffer_impl.hpp",
                "source/m1/impl/graphics_geometry_vertex_buffer_impl.cpp",
                "source/m1/impl/graphics_shader_const_buffer_impl.hpp",
                "source/m1/impl/graphics_shader_const_buffer_impl.cpp",
                "source/m1/impl/graphics_shader_mutable_buffer_impl.hpp",
                "source/m1/impl/graphics_shader_mutable_buffer_impl.cpp",
                "source/m1/impl/graphics_shader_instance_buffer_impl.hpp",
                "source/m1/impl/graphics_shader_instance_buffer_impl.cpp",
                "source/m1/graphics_command_queue.cpp",
                "source/m1/graphics_device.cpp",
                "source/m1/graphics_draw_state.cpp",
                "source/m1/graphics_draw_target_state.cpp",
                "source/m1/graphics_texture_source.cpp",
                "source/m1/graphics_texture_color_target.cpp",
                "source/m1/graphics_texture_depth_target.cpp",
                "source/m1/graphics_draw_target.cpp",
                "source/m1/graphics_memory_buffer.cpp",
                "source/m1/graphics_geometry_index_buffer.cpp",
                "source/m1/graphics_geometry_vertex_buffer.cpp",
                "source/m1/graphics_shader_const_buffer.cpp",
                "source/m1/graphics_shader_mutable_buffer.cpp",
                "source/m1/graphics_shader_instance_buffer.cpp",
                "source/m1/graphics_state.cpp",
                "m1_graphics.gyp",
            ],
            'direct_dependent_settings':
            {
                'include_dirs':
                [
                    "include",
                ],
            },
        },
        {
            'target_name': "m1_graphics_test",
            'type': "executable",
            'sources':
            [
                "test/test_main.cpp",
                "test/m1/test_graphics_device.cpp",
            ],
            'dependencies':
            [
                "../../../external_libs/catch.gyp:catch",
                "m1_graphics",
            ],
        },
    ],
}