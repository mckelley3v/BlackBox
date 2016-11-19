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
                "libs/m1/range_view/m1_range_view.gyp:m1_range_view",
                "libs/m1/range_view/m1_range_view.gyp:m1_range_view_test",
            ],
        },
    ],
}
