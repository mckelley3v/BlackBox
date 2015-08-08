{
    "targets":
    [
        {
            "target_name": "flatbuffers",
            "type": "none",
            "sources":
            [
                "flatbuffers/include/flatbuffers/flatbuffers.h",
                "flatbuffers/flatbuffers.gyp",
            ],
            "direct_dependent_settings":
            {
                "include_dirs":
                [
                    "flatbuffers/include",
                ],
            },
        },
        {
            "target_name": "flatbuffers_idl",
            "type": "static_library",
            "sources":
            [
                "flatbuffers/include/flatbuffers/idl.h",
                "flatbuffers/include/flatbuffers/util.h",
                "flatbuffers/src/idl_gen_cpp.cpp",
                "flatbuffers/src/idl_gen_fbs.cpp",
                "flatbuffers/src/idl_gen_general.cpp",
                "flatbuffers/src/idl_gen_go.cpp",
                "flatbuffers/src/idl_gen_text.cpp",
                "flatbuffers/src/idl_parser.cpp",
            ],
            "dependencies":
            [
                "flatbuffers",
            ],
            "export_dependent_settings":
            [
                "flatbuffers",
            ],
        },
        {
            "target_name": "flatbuffers_compiler",
            "type": "executable",
            "sources":
            [
                "flatbuffers/src/flatc.cpp",
            ],
            "dependencies":
            [
                "flatbuffers_idl",
            ],
        },
        {
            "target_name": "flatbuffers_test",
            "type": "executable",
            "configurations":
            {
                "codelite_settings":
                {
                    "WorkingDirectory": "./flatbuffers",
                },
            },
            "sources":
            [
                "flatbuffers/tests/test.cpp",
                "flatbuffers/tests/monster_test_generated.h",
            ],
            "dependencies":
            [
                "flatbuffers_idl",
            ],
        },
        {
            "target_name": "flatbuffers_sample_binary",
            "type": "executable",
            "configurations":
            {
                "codelite_settings":
                {
                    "WorkingDirectory": "./flatbuffers",
                },
            },
            "sources":
            [
                "flatbuffers/samples/sample_binary.cpp",
                "flatbuffers/samples/monster_generated.h",
            ],
            "dependencies":
            [
                "flatbuffers_idl",
            ],
        },
        {
            "target_name": "flatbuffers_sample_text",
            "type": "executable",
            "configurations":
            {
                "codelite_settings":
                {
                    "WorkingDirectory": "./flatbuffers",
                },
            },
            "sources":
            [
                "flatbuffers/samples/sample_text.cpp",
                "flatbuffers/samples/monster_generated.h",
            ],
            "dependencies":
            [
                "flatbuffers_idl",
            ],
        },
    ],
}
 
