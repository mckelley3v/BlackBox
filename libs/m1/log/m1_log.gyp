{
    "targets":
    [
        {
            "target_name": "m1_log",
            "type": "static_library",
            "include_dirs":
            [
                "include",
            ],
            "sources":
            [
                "include/m1/log.hpp",
                "source/m1/log.cpp",
                "m1_log.gyp",
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
            "target_name": "m1_log_test",
            "type": "executable",
            "sources":
            [
                "test/test_main.cpp",
                "test/m1/test_log.cpp",
            ],
            "dependencies":
            [
                "<(catch_gyp_file):catch",
                "m1_log",
            ],
        },
    ],
}
