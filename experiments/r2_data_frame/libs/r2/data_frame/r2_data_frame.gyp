{
    "targets":
    [
        {
            "target_name": "r2_data_frame",
            "type": "static_library",
            "include_dirs":
            [
                "include",
                "source",
            ],
            "sources":
            [
                "include/r2/data_frame.hpp",
                "include/r2/data_sequence.hpp",
                "include/r2/data_source.hpp",
                "source/r2/data_frame.cpp",
                "source/r2/data_sequence.cpp",
                "source/r2/data_source.cpp",
                "r2_data_frame.gyp",
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
                ],
            },
        },
        {
            "target_name": "r2_data_frame_test",
            "type": "executable",
            "include_dirs":
            [
                "test",
            ],
            "sources":
            [
                "test/test_main.cpp",
                "test/test_data_frame.cpp",
            ],
            "dependencies":
            [
                "<(catch_gyp_file):catch",
                "r2_data_frame",
            ],
        },
    ],
}
