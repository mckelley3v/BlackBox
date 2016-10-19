{
    "variables":
    {
        "conditions":
        [
            [
                "OS == 'win'",
                {
                    "vulkan_sdk_dir": "<!(echo %VULKAN_SDK%)",
                }
            ],
            [
                "OS == 'linux'",
                {
                    "vulkan_sdk_dir": "<!(echo $VULKAN_SDK)",
                },
            ],
        ],
    },
    "targets":
    [
        {
            "target_name": "vulkan-1",
            "type": "none",
            "sources":
            [
                "<(vulkan_sdk_dir)/include/vulkan/vulkan.hpp",
                "<(vulkan_sdk_dir)/include/vulkan/vulkan.h",
                "<(vulkan_sdk_dir)/include/vulkan/vk_platform.h",
                "vulkan.gyp",
            ],
            "direct_dependent_settings":
            {
                "include_dirs":
                [
                    "<(vulkan_sdk_dir)/include",
                ],
            },
            "conditions":
            [
                [
                    "OS == 'win'",
                    {
                        "direct_dependent_settings":
                        {
                            "defines":
                            [
                                "VK_USE_PLATFORM_WIN32_KHR",
                                "WIN32_LEAN_AND_MEAN",
                                "NOMINMAX",
                            ],
                        },
                        "link_settings":
                        {
                            "libraries":
                            [
                                "-lvulkan-1.lib",
                            ],
                            "library_dirs":
                            [
                                # TODO: detect x86 vs x64
                                "<(vulkan_sdk_dir)/bin/",
                            ]
                        },
                    }
                ],
                [
                    "OS == 'linux'",
                    {
                        "direct_dependent_settings":
                        {
                            "defines":
                            [
                                # TODO: detect windowing system or make separate explicit targets
                                "VK_USE_PLATFORM_XCB_KHR",
                            ],
                        },
                        "link_settings":
                        {
                            "libraries":
                            [
                                "-lvulkan-1",
                            ],
                            "library_dirs":
                            [
                                "<(vulkan_sdk_dir)/bin/",
                            ]
                        },
                    }
                ],
            ],
        },
    ],
}
