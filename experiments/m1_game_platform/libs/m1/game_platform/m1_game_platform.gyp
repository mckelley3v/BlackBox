{
    "targets":
    [
        {
            "target_name": "m1_game_platform",
            "type": "static_library",
            "include_dirs":
            [
                "include",
                "source",
            ],
            "sources":
            [
                "include/m1/intrusive_list.hpp",
                "include/m1/intrusive_list_impl.hpp",
                "include/m1/intrusive_list_node.hpp",
                "include/m1/signal.hpp",
                "include/m1/game_platform.hpp",
                "source/m1/game_platform.cpp",
                # windows:
                "include/m1/platform_impl/windows/m1/game_platform_impl.hpp",
                "source/m1/platform_impl/windows/m1/game_platform_impl.cpp",
                "source/m1/intrusive_list_impl.cpp",
                "source/m1/intrusive_list_node.cpp",
                "m1_game_platform.gyp",
            ],
            "dependencies":
            [
            ],
            "export_dependent_settings":
            [
            ],
            "direct_dependent_settings":
            {
                "include_dirs":
                [
                    "include",
                    # windows:
                    "include/m1/platform_impl/windows",
                ],
                "libraries":
                [
                    "-luser32.lib",
                ],
            },
        },
        {
            "target_name": "m1_game_platform_test",
            "type": "executable",
            "include_dirs":
            [
                "test",
            ],
            "sources":
            [
                "test/test_main.cpp",
                "test/test_game_platform.cpp",
            ],
            "dependencies":
            [
                "<(catch_gyp_file):catch",
                "m1_game_platform",
            ],
        },
    ],
}
