{
    "targets":
    [
        {
            "target_name": "experiment",
            "type": "none",
            "sources":
            [
                "experiment.gyp",
            ],
            "dependencies":
            [
                "<(catch_gyp_file):catch",
                "libs/m1/game_platform/m1_game_platform.gyp:m1_game_platform",
                "libs/m1/game_platform/m1_game_platform.gyp:m1_game_platform_test",
            ],
        },
    ],
}
