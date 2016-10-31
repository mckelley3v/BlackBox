#include "m1/json_input_archive.hpp"
#include "m1/crc32.hpp"
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>
#include "catch.hpp"

// ====================================================================================================================

char const json_file[] =
R"json(
{
    "Material": {
        "Type": "HIST",
        "Name": "Histogram",
        "Defines": [
            "API_VK",
            "MATERIAL_HISTOGRAM"
        ],
        "Features": [
            {
                "Type": "TEXS",
                "Name": "Texture",
                "DataId": "kMaterialDataId_Texture_Histogram_Texture",
                "Options": [
                    {
                        "Name": "Yes",
                        "Defines": "HAS_HISTOGRAM_TEXTURE",
                        "Bindings": [
                            {
                                "Semantic": "Texture",
                                "Variable": "uc_texture"
                            }
                        ]
                    }
                ]
            },
            {
                "Type": "FLT4",
                "Name": "Range",
                "DataId": "kMaterialDataId_Color_Histogram_Range",
                "Options": [
                    {
                        "Name": "Yes",
                        "Defines": "HAS_HISTOGRAM_RANGE",
                        "Bindings": [
                            {
                                "Semantic": "Value",
                                "Variable": "uc_rangeLowHi"
                            }
                        ]
                    }
                ]
            },
            {
                "Type": "FLT4",
                "Name": "Scale",
                "DataId": "kMaterialDataId_Color_Histogram_Scale",
                "Options": [
                    {
                        "OptionName": "Yes",
                        "Defines": "HAS_HISTOGRAM_SCALE",
                        "Bindings": [
                            {
                                "Semantic": "Value",
                                "Variable": "uc_valueScale"
                            }
                        ]
                    }
                ]
            }
        ],
        "ExportFilter": "Texture.Any &&\nRange.Yes\n&&\nScale.Yes",
        "ShaderProgram": "Shaders/glsl/Histogram.vs.glsl"
    }
}
)json";

// ====================================================================================================================

struct VariableBinding
{
    m1::crc32 semantic;
    std::string variable;
};

struct FeatureOption
{
    std::string name;
    std::vector<std::string> defines;
    std::vector<VariableBinding> bindings;
};

enum class FeatureUsage
{
    Static,
    Dynamic,
};

struct Feature
{
    char type[4];
    std::string name;
    m1::crc32 data_id;
    FeatureUsage usage;
    std::vector<FeatureOption> options;
};

struct ShaderProgram
{
    std::string vertex_stage_path;
    std::string geometry_stage_path;
    std::string fragment_stage_path;
    std::string tess_hull_stage_path;
    std::string tess_eval_stage_path;
    std::string compute_stage_path;
};

struct Material
{
    char type[4];
    std::string name;
    std::vector<std::string> defines;
    std::vector<Feature> features;
    std::string export_filter;
};


bool operator >> (m1::serialization::json_input_archive &in, VariableBinding &value)
{
    using namespace m1::literals;
    using namespace m1::serialization;

    return in >> object(property("Semantic"_id, /*ref*/ value.semantic),
                        property("Variable"_id, /*ref*/ value.variable));
}

bool operator >> (m1::serialization::json_input_archive &in, FeatureOption &value)
{
    using namespace m1::literals;
    using namespace m1::serialization;

    return in >> object(property("Name"_id,     /*ref*/ value.name),
                        property("Defines"_id,  /*ref*/ value.defines),
                        property("Bindings"_id, /*ref*/ value.bindings));
}

bool operator >> (m1::serialization::json_input_archive &in, FeatureUsage &value)
{
    using namespace m1::literals;
    using namespace m1::serialization;

    return in >> select(/*ref*/ value, option("Static"_id,  FeatureUsage::Static),
                                       option("Dynamic"_id, FeatureUsage::Dynamic));
}

bool operator >> (m1::serialization::json_input_archive &in, Feature &value)
{
    using namespace m1::literals;
    using namespace m1::serialization;

    return in >> object(property("Type"_id,    /*ref*/ value.type),
                        property("Name"_id,    /*ref*/ value.name),
                        property("DataId"_id,  /*ref*/ value.data_id),
                        property("Usage"_id,   /*ref*/ value.usage),
                        property("Options"_id, /*ref*/ value.options));
}

bool operator >> (m1::serialization::json_input_archive &in, ShaderProgram &value)
{
    using namespace m1::literals;
    using namespace m1::serialization;

    return in >> object(property("Vertex"_id,   /*ref*/ value.vertex_stage_path),
                        property("Geometry"_id, /*ref*/ value.geometry_stage_path),
                        property("Fragment"_id, /*ref*/ value.fragment_stage_path),
                        property("TessHull"_id, /*ref*/ value.tess_hull_stage_path),
                        property("TessEval"_id, /*ref*/ value.tess_eval_stage_path),
                        property("Compute"_id,  /*ref*/ value.compute_stage_path));
}

bool operator >> (m1::serialization::json_input_archive &in, Material &value)
{
    using namespace m1::literals;
    using namespace m1::serialization;

    return in >> object(property("Type"_id,         /*ref*/ value.type),
                        property("Name"_id,         /*ref*/ value.name),
                        property("Defines"_id,      /*ref*/ value.defines),
                        property("Features"_id,     /*ref*/ value.features),
                        property("ExportFilter"_id, /*ref*/ value.export_filter));
}

// ====================================================================================================================

TEST_CASE("Test m1::serialization::json_input_archive", "[m1]")
{
    using namespace m1::literals;
    using namespace m1::serialization;

    Material m;

    std::istringstream in(json_file);
    json_input_archive jin(in.rdbuf());
    CHECK(jin >> m);
    //   m1::ustring s = m1::ustring::format("hello {name}", std::make_pair("name"_id, name),
    //                                                       std::make_pair("date"_id, date));
}
