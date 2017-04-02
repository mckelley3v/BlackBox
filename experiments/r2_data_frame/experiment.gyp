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
                "libs/r2/data_frame/r2_data_frame.gyp:r2_data_frame",
                "libs/r2/data_frame/r2_data_frame.gyp:r2_data_frame_test",
            ],
        },
    ],
}
