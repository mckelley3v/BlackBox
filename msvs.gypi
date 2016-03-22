{
    "target_defaults":
    {
        "msvs_configuration_attributes":
        {
            "OutputDirectory": "$(SolutionDir)..\\bin\\$(Platform)\\$(ConfigurationName)\\",
            "IntermediateDirectory": "$(SolutionDir)..\\temp\\$(Platform)\\$(ConfigurationName)\\$(ProjectName)\\",
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
            "debug_Win32":
            {
                "msvs_configuration_platform": "Win32",
                "msvs_settings":
                {
                    "VCCLCompilerTool":
                    {
                        "Optimization": 0, # "Disabled"
                    },
                    "VCLinkerTool":
                    {
                        "GenerateDebugInformation": "true",
                    },
                },
            },
            "debug_x64":
            {
                "inherit_from":
                [
                    "debug_Win32"
                ],
                "msvs_configuration_platform": "x64",
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
            },
            "release_x64":
            {
                "inherit_from":
                [
                    "release"
                ],
                "msvs_configuration_platform": "x64",
            },
        },
        "default_configuration": "debug_Win32",
    },
}
