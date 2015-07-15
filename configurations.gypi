{
    "target_defaults":
    {
        "msvs_configuration_attributes":
        {
            "OutputDirectory": "$(SolutionDir)..\\bin\\$(Platform)\\$(ConfigurationName)",
            "IntermediateDirectory": "$(SolutionDir)..\\temp\\$(Platform)\\$(ConfigurationName)\\$(ProjectName)",
        },
        "msvs_settings":
        {
            "VCCLCompilerTool":
            {
                "WarningLevel": 4, # "Level4"
                "WarnAsError": "true",
                "PreprocessorDefinitions":
                [
                    "_CRT_SECURE_NO_WARNINGS",
                    "_SCL_SECURE_NO_WARNINGS",
                ],
                "DisableSpecificWarnings":
                [
                    "4351", # new behavior: elements of array will be default initialized
                    "4512", # assignment operator was implicitly defined as deleted
                    "4510", # default constructor was implicitly defined as deleted
                ],
            },
        },
        "configurations":
        {
            "debug":
            {
                "msvs_configuration_platform": "Win32",
                "msvs_settings":
                {
                    "VCCLCompilerTool":
                    {
                        "Optimization": 0, # "Disabled"
                        "PreprocessorDefinitions":
                        [
                            "_DEBUG",
                        ],
                    },
                    "VCLinkerTool":
                    {
                        "GenerateDebugInformation": "true",
                    },
                },
                "codelite_settings":
                {
                    "CompilerType": "clang++",
                    "Compiler":
                    {
                        "Options": "-std=c++1y -nostdinc++ -isystem /usr/include/c++/v1/ -m32 -g",
                    },
                    "Linker":
                    {
                        "Options": "-m32 -stdlib=libc++ -lc++abi"
                    },
                },
            },
            "debug_x64":
            {
                "inherit_from":
                [
                    "debug"
                ],
                "msvs_configuration_platform": "x64",
                "codelite_settings":
                {
                    "CompilerType": "clang++",
                    "Compiler":
                    {
                        "Options": "-std=c++1y -nostdinc++ -isystem /usr/include/c++/v1/ -m64 -g",
                    },
                    "Linker":
                    {
                        "Options": "-m64 -stdlib=libc++ -lc++abi"
                    },
                },
            },
            "release":
            {
                "defines":
                [
                    "NDEBUG",
                ],
                "msvs_configuration_platform": "Win32",
                "msvs_settings":
                {
                    "VCCLCompilerTool":
                    {
                        "Optimization": 3, # "Full"
                    },
                },
                "codelite_settings":
                {
                    "CompilerType": "clang++",
                    "Compiler":
                    {
                        "Options": "-std=c++1y -nostdinc++ -isystem /usr/include/c++/v1/ -m32 -O2",
                    },
                    "Linker":
                    {
                        "Options": "-stdlib=libc++ -lc++abi"
                    },
                },
            },
            "release_x64":
            {
                "inherit_from":
                [
                    "release"
                ],
                "msvs_configuration_platform": "x64",
                "codelite_settings":
                {
                    "CompilerType": "clang++",
                    "Compiler":
                    {
                        "Options": "-std=c++1y -nostdinc++ -isystem /usr/include/c++/v1/ -m64 -O2",
                    },
                    "Linker":
                    {
                        "Options": "-stdlib=libc++ -lc++abi"
                    },
                },
            },
        },
        "default_configuration": "debug",
    },
}
