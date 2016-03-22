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
                "libs/m1/ustring/m1_ustring.gyp:m1_ustring",
                "libs/m1/ustring/m1_ustring.gyp:m1_ustring_test",
            ],
        },
    ],
}
