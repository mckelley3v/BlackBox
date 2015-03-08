{
    'includes':
    [
        "../../configurations.gypi",
    ],
    'targets':
    [
        {
            'target_name': "Flow",
            'type': "static_library",
            'include_dirs':
            [
                "include",
                "source",
            ],
            'sources':
            [
                "include/Flow.hpp",
                "include/Flow/Component.hpp",
                "include/Flow/Connection.hpp",
                "include/Flow/Input.hpp",
                "include/Flow/Output.hpp",
                "include/Flow/System.hpp",
                "include/Flow/TypeManager.hpp",
                "source/Flow/Component.cpp",
                "source/Flow/Connection.cpp",
                "source/Flow/Input.cpp",
                "source/Flow/Output.cpp",
                "source/Flow/System.cpp",
                "source/Flow/SystemBase.cpp",
                "source/Flow/SystemGraph.hpp",
                "source/Flow/SystemGraph.cpp",
                "source/Flow/TypeManager.cpp",
                "source/Flow/Verify.hpp",
                "Flow.gyp",
            ],
            'dependencies':
            [
                "../m1/any_ptr/m1_any_ptr.gyp:m1_any_ptr",
                "../m1/dictionary/m1_dictionary.gyp:m1_dictionary",
                "../m1/serialization/m1_serialization.gyp:m1_serialization",
            ],
            'export_dependent_settings':
            [
                "../m1/any_ptr/m1_any_ptr.gyp:m1_any_ptr",
                "../m1/dictionary/m1_dictionary.gyp:m1_dictionary",
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
            'target_name': "FlowTest",
            'type': "executable",
            'include_dirs':
            [
                "test",
            ],
            'sources':
            [
                "test/test_main.cpp",
                "test/Flow/Components/Add.hpp",
                "test/Flow/Components/Constant.hpp",
                "test/Flow/Components/TestAdd.cpp",
                "test/Flow/Components/TestConstant.cpp",
                "test/Flow/Systems/AddNetwork.hpp",
                "test/Flow/Systems/AddNetwork.cpp",
                "test/Flow/Systems/TestAddNetwork.cpp",
                "test/Flow/TypeName.hpp",
            ],
            'dependencies':
            [
                "../../external_libs/catch.gyp:catch",
                "Flow",
            ],
        },
    ],
}
