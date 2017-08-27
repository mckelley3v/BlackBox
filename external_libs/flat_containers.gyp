{
    "targets":
    [
        {
            "target_name": "flat_containers",
            "type": "none",
            "sources":
            [
                "include\flat_map.hpp",
                "include\flat_multimap.hpp",
                "include\flat_multiset.hpp",
                "include\flat_set.hpp",
                "include\impl\class_def.hpp",
                "include\impl\container_traits.hpp",
                "include\impl\flat_impl.hpp",
                "flat_containers.gyp",
            ],
            "direct_dependent_settings":
            {
                "include_dirs":
                [
                    "flat_containers/include/",
                ],
            },
        },
    ],
}
