{
    'includes':
    [
        "../../../configurations.gypi",
    ],
    'targets':
    [
        {
            'target_name': "m1_any_ptr",
            'type': "static_library",
            'include_dirs':
            [
                "include",
            ],
            'sources':
            [
                "include/m1/any_ptr.hpp",
                "source/m1/any_ptr.cpp",
                "m1_any_ptr.gyp",
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
            'target_name': "m1_any_ptr_test",
            'type': "executable",
            'sources':
            [
                "test/test_main.cpp",
                "test/m1/test_any_ptr.cpp",
            ],
            'dependencies':
            [
                "../../../external_libs/catch.gyp:catch",
                "m1_any_ptr",
            ],
        },
    ],
}
