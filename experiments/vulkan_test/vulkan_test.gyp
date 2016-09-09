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
                "source/vku.cpp",
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
