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
                "libs/m1/input_archive/m1_input_archive.gyp:m1_input_archive",
                "libs/m1/input_archive/m1_input_archive.gyp:m1_input_archive_test",
            ],
        },
    ],
}
