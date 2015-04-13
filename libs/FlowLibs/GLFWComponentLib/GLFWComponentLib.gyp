{
    'includes':
    [
        "../../../configurations.gypi",
    ],
    'targets':
    [
        {
            'target_name': "GLFWComponentLib",
            'type': "static_library",
            'include_dirs':
            [
                "include",
                "source",
            ],
            'sources':
            [
                "include/GL/gl.h",
                "include/Flow/glfwSwapBuffersComponent.hpp",
                "include/Flow/GLFWlibComponent.hpp",
                "include/Flow/GLFWwindowComponent.hpp",
                "source/Flow/glfwSwapBuffersComponent.cpp",
                "source/Flow/GLFWlibComponent.cpp",
                "source/Flow/GLFWwindowComponent.cpp",
                "GLFWComponentLib.gyp",
            ],
            'dependencies':
            [
                "../../../external_libs/glfw.gyp:glfw",
                "../../../external_libs/glbinding.gyp:glbinding",
                "../../Flow/Flow.gyp:Flow",
                "../../m1/serialization/m1_serialization.gyp:m1_serialization",
            ],
            'export_dependent_settings':
            [
                "../../../external_libs/glbinding.gyp:glbinding",
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
            'target_name': "GLFWComponentLibTest",
            'type': "executable",
            'include_dirs':
            [
                "test",
            ],
            'sources':
            [
                "test/test_main.cpp",
                "test/Flow/DrawTestTriangleComponent.hpp",
                "test/Flow/DrawTestTriangleComponent.cpp",
                "test/Flow/TestGLFWComponentLib01.cpp",
            ],
            'dependencies':
            [
                "../../../external_libs/catch.gyp:catch",
                "../../m1/serialization/m1_serialization.gyp:m1_serialization",
                "../../Flow/Flow.gyp:Flow",
                "GLFWComponentLib",
            ],
        },
    ],
}