{
    "targets":
    [
        {
            "target_name": "vulkan_test",
            "type": "executable",
            "include_dirs":
            [
                "test",
            ],
            "sources":
            [
                "main.cpp",
            ],
            "dependencies":
            [
                "<(vulkan_gyp_file):vulkan",
            ],
        },
    ],
}
