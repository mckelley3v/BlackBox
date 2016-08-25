{
    "variables":
    {
        "vulkan_sdk_dir": "<!(ECHO %VK_SDK_PATH%)", # "<!(python import os; print os.environ("VK_SDK_PATH");)",
    },
    "targets":
    [
        {
            "target_name": "vulkan",
            "type": "none",
            "defines":
            [
                "VK_USE_PLATFORM_WIN32_KHR",
            ],
            "sources":
            [
                "<(vulkan_sdk_dir)/include/vulkan/vulkan.h",
                "vulkan.gyp",
            ],
            "direct_dependent_settings":
            {
                "include_dirs":
                [
                    "<(vulkan_sdk_dir)/include",
                ],
                "link_settings":
                {
                    "libraries":
                    [
                        "<(vulkan_sdk_dir)/bin/vulkan-1.lib",
                    ],
                },
            },
        },
    ],
}
