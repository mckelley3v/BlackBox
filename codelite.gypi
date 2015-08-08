{
    "target_defaults":
    {
        "configurations":
        {
            "debug_x86":
            {
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
                    "debug_x86"
                ],
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
            "release_x86":
            {
                "defines":
                [
                    "NDEBUG",
                ],
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
                    "release_x86"
                ],
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
        "default_configuration": "debug_x86",
    },
}
