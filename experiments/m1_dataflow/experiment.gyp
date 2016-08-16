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
                "libs/m1/dataflow/m1_dataflow.gyp:m1_dataflow",
                "libs/m1/dataflow/m1_dataflow.gyp:m1_dataflow_test",
            ],
        },
    ],
}
