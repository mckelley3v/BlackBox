{
    "target_defaults":
    {
        "msbuild_toolset": "Clang_3_6",
        "msbuild_cpp_stdlib": "c++_static",
        "msbuild_enable_android": "true",
        "msbuild_configuration_attributes":
        {
            "OutputDirectory": "$(SolutionDir)..\\bin\\$(Platform)\\$(ConfigurationName)\\",
            "IntermediateDirectory": "$(SolutionDir)..\\temp\\$(Platform)\\$(ConfigurationName)\\$(ProjectName)\\",
        },
        "msbuild_settings":
        {
            "ClCompile":
            {
                "TreatWarningAsError": "true",
                # "ExceptionHandling": "Enabled",
                "AdditionalIncludeDirectories":
                [
                    "$(VS_NdkRoot)\\sources\\android\\support\\include",
                ],
            },
        },
        "configurations":
        {
            "debug_x86":
            {
                "msvs_configuration_platform": "x86",
                "msbuild_settings":
                {
                    "ClCompile":
                    {
                        "Optimization": "Disabled",
                        "CppLanguageStandard": "c++1y",
                    },
                    "Link":
                    {
                        "GenerateDebugInformation": "true",
                    },
                },
            },
            "debug_ARM":
            {
                "inherit_from":
                [
                    "debug_x86"
                ],
                "msvs_configuration_platform": "ARM",
            },
            "release":
            {
                "defines":
                [
                    "NDEBUG",
                ],
                "msvs_configuration_platform": "x86",
                "msbuild_settings":
                {
                    "ClCompile":
                    {
                        "Optimization": "Full",
                    },
                },
            },
            "release_ARM":
            {
                "inherit_from":
                [
                    "release"
                ],
                "msvs_configuration_platform": "ARM",
            },
        },
        "default_configuration": "debug_x86",
    },
}
