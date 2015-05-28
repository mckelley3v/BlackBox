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
                "include/m1/graphics_command_queue.hpp",
                "include/m1/graphics_device.hpp",
                "include/m1/graphics_draw_state.hpp",
                "include/m1/graphics_framebuffer_state.hpp",
                "include/m1/graphics_state.hpp",
                "source/m1/graphics_command_queue.cpp",
                "source/m1/graphics_device_none.hpp",
                "source/m1/graphics_device_none.cpp",
                "source/m1/graphics_device_impl.hpp",
                "source/m1/graphics_device_impl.cpp",
                "source/m1/graphics_device.cpp",
                "source/m1/graphics_draw_state.cpp",
                "source/m1/graphics_state.cpp",
                "source/m1/graphics_framebuffer_state.cpp",
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
                "test/m1/test_graphics.cpp",
            ],
            'dependencies':
            [
                "../../../external_libs/catch.gyp:catch",
                "m1_graphics",
            ],
        },
    ],
}
