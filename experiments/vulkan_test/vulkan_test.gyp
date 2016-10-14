{
    "targets":
    [
        {
            "target_name": "vulkan_test",
            "type": "executable",
            "include_dirs":
            [
                "include",
            ],
            "sources":
            [
                "include/vku.hpp",
                "include/vku_instance.hpp",
                "include/vku_device.hpp",
                "include/vku_extension.hpp",
                "include/vku_iostream.hpp",
                "source/vku.cpp",
                "source/vku_utility.hpp",
                "source/vku_utility.cpp",
                "source/vku_instance.cpp",
                "source/vku_device.cpp",
                "source/vku_extension.cpp",
                "source/vku_iostream.cpp",
                "test/main.cpp",
            ],
            "dependencies":
            [
                "<(catch_gyp_file):catch",
                "<(vulkan_gyp_file):vulkan-1",
                "<(workspace_dir)/experiments/m1_game_platform/libs/m1/game_platform/m1_game_platform.gyp:m1_game_platform"
            ],
        },
    ],
}
