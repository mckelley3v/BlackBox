{
    'includes':
    [
        "../configurations.gypi",
    ],
    'targets':
    [
        {
            'target_name': "catch",
            'type': "none",
            'sources':
            [
                "catch/single_include/catch.hpp",
                "catch.gyp",
            ],
            'direct_dependent_settings':
            {
                'include_dirs':
                [
                    "catch/single_include/",
                ],
            },
        },
    ],
}
 
