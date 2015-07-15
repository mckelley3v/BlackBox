# To use this, create a gyp target with the following form:
#{
#	"target_name": "my_lib",
#	"type": "static_library",
#	"includes":
#	[
#		"path/to/this/gypi/file"
#	],
#	"sources":
#	[
#		"foo.fbs",
#		"bar.fbs",
#	],
#}

{
	"variables":
	{
		"flatbuffers_compiler_exe": "<(PRODUCT_DIR)/flatbuffers_compiler",
		"flatbuffers_include_dir": "<(SHARED_INTERMEDIATE_DIR)/flatbuffers_generator",
		"flatbuffers_intermediate_dir": "<(SHARED_INTERMEDIATE_DIR)/flatbuffers_generator",
	},
	"rules":
	[
		{
			"rule_name": "flatbuffers_generator",
			"extension": "fbs",
			"outputs":
			[
				"<(flatbuffers_intermediate_dir)/<(RULE_INPUT_ROOT)_generated.h",
			],
			"action":
			[
				"<(flatbuffers_compiler_exe)",
				"-c",
				"-o",
				"<(flatbuffers_intermediate_dir)",
				"<(RULE_INPUT_PATH)",
			],
			"message": "FlatBuffers code generation -- <(RULE_INPUT_ROOT)_generated.h: <(RULE_INPUT_NAME)",
			"process_outputs_as_sources": 1,
		},
	],
	"dependencies":
	[
		"<(DEPTH)/external_libs/flatbuffers.gyp:flatbuffers_compiler",
	],
	"include_dirs":
	[
		"<(flatbuffers_include_dir)",
	],
	"direct_dependent_settings":
	{
		"include_dirs":
		[
			"<(flatbuffers_include_dir)",
		]
	},
	# This target exports a hard dependency because it generates header files
	"hard_dependency": 1,
}
