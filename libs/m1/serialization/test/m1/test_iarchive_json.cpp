#include "m1/iarchive_json.hpp"
#include <iostream>
#include "catch.hpp"

struct vector3f
{
    float x;
    float y;
    float z;
};

struct color3f
{
    float r;
    float g;
    float b;
};

struct quaternionf
{
    float real;
    vector3f imag;
};

struct transformf
{
    vector3f position;
    vector3f scale;
    quaternionf orientation;
};

struct component
{
    virtual ~component() = default;
};

struct transform_component
    : component
    , transformf
{};

enum class light_type
{
    spot,
    point,
    directional,
};

struct light_distance_range
{
    float inner_radius;
    float outer_radius;
};

struct light_angle_range
{
    float inner_angle;
    float outer_angle;
};

enum class shadow_map_texture_size
{
    x256,
    x512,
    x1024,
    x2048,
    x4096,
};

enum class shadow_map_cascade_count
{
    x1,
    x2,
    x4,
};

struct shadow_map_depth_bias
{
    float offset;
    float slope_scale;
    float clamp;
};

struct shadow_map
{
    bool enabled;
    shadow_map_texture_size texture_size;
    shadow_map_cascade_count cascade_count;
    shadow_map_depth_bias depth_bias;
};

struct light
{
    light_type type;
    light_distance_range distance_range;
    light_angle_range angle_range;
    color3f direct_color;
    color3f bounce_color;
    color3f ambient_color;
    shadow_map shadow_map;
};

struct light_component
    : component
    , light
{};

struct entity
{
    std::string name;
    std::vector<std::unique_ptr<component>> components;
};

struct scene
{
    std::vector<entity> entities;
};

bool read_value(m1::iarchive_json &in, m1::log &logger, vector3f &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, color3f &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, quaternionf &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, transformf &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, light_type &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, light_distance_range &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, light_angle_range &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map_texture_size &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map_cascade_count &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map_depth_bias &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, light &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, std::unique_ptr<component> &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, entity &value);
bool read_value(m1::iarchive_json &in, m1::log &logger, scene &value);

// object (null, empty, unbracketed, regular)
// array (null, empty, unbracketed, regular)
// property
// string (regular, escaped)
// int (positive, negative)
// float (positive, negative, int, frac, exp)
// true, false
TEST_CASE("Test m1::iarchive_json", "[m1]")
{
    char const * const json =
        "{\n"
        "    \"entities\":\n"
        "    [\n"
        "        {\n"
        "            \"name\": \"Entity0\",\n"
        "            \"components\":\n"
        "            [\n"
        "                {\n"
        "                    \"type\": \"transform\",\n"
        "                    \"data\":\n"
        "                    {\n"
        "                        \"position\":    {\"x\": 0.0, \"y\": 0.0, \"z\": 1.0},\n"
        "                        \"scale\":       {\"x\": 1.0, \"y\": 1.0, \"z\": 2.0},\n"
        "                        \"orientation\": {\"real\": 1.0, \"imag\": {\"x\": 0.0, \"y\": 0.0, \"z\": 0.0}}\n"
        "                    }\n"
        "                }\n"
        "            ]\n"
        "        },\n"
        "        {\n"
        "            \"name\":  \"Entity1\",\n"
        "            \"components\":\n"
        "            [\n"
        "                {\n"
        "                    \"type\": \"transform\",\n"
        "                    \"data\":\n"
        "                    {\n"
        "                        \"position\":    {\"x\": 2.0, \"y\": 0.0, \"z\": 1.0},\n"
        "                        \"scale\":       {\"x\": 1.0, \"y\": 1.0, \"z\": 2.0},\n"
        "                        \"orientation\": {\"real\": 1.0, \"imag\": {\"x\": 0.0, \"y\": 0.0, \"z\": 0.0}}\n"
        "                    }\n"
        "                }\n"
        "            ]\n"
        "        },\n"
        "        {\n"
        "            \"name\": \"Entity2\",\n"
        "            \"components\":\n"
        "            [\n"
        "                {\n"
        "                    \"type\": \"transform\",\n"
        "                    \"data\":\n"
        "                    {\n"
        "                        \"position\":    {\"x\": 0.0, \"y\": 0.0, \"z\": 5},\n"
        "                        \"scale\":       {\"x\": 1.0, \"y\": 1.0, \"z\": 1.0},\n"
        "                        \"orientation\": {\"real\": 1.0, \"imag\": {\"x\": 0.0, \"y\": 0.0, \"z\": 0.0}}\n"
        "                    }\n"
        "                },\n"
        "                {\n"
        "                    \"type\": \"light\",\n"
        "                    \"data\":\n"
        "                    {\n"
        "                        \"type\": \"directional\",\n"
        "                        \"distance_range\": null,\n"
        "                        \"angle_range\": null,\n"
        "                        \"direct_color\": {\"r\": 1e2, \"g\": 1.01e2, \"b\": 0.8e2},\n"
        "                        \"bounce_color\": {\"r\": 9.5, \"g\": 8.0, \"b\": 5.25},\n"
        "                        \"ambient_color\": {\"r\": 1.0, \"g\": 1.0, \"b\": 1.5},\n"
        "                        \"shadow_map\":\n"
        "                        {\n"
        "                            \"enabled\": false,\n"
        "                            \"texture_size\": 1024,\n"
        "                            \"cascade_count\": 4,\n"
        "                            \"depth_bias\": \"default\"\n"
        "                        }\n"
        "                    }\n"
        "                }\n"
        "            ]\n"
        "        },\n"
        "        null\n"
        "    ]\n"
        "}";

    m1::log logger(std::cout,
                   std::clog,
                   std::cerr);

    m1::iarchive_json in(json);

    scene data = {};
    bool const is_data_valid = read_value(in, logger, data);
    REQUIRE(is_data_valid);

    std::vector<entity> const &entities = data.entities;
    REQUIRE(entities.size() == 4);

    {
        entity const &entity = entities[0];
        CHECK(entity.name == "Entity0");
        REQUIRE(entity.components.size() == 1);

        transform_component const * const transform = dynamic_cast<transform_component const*>(entity.components[0].get());
        CHECK(transform != nullptr);
        CHECK(transform->position.x == Approx(0.0f));
        CHECK(transform->position.y == Approx(0.0f));
        CHECK(transform->position.z == Approx(1.0f));

        CHECK(transform->scale.x == Approx(1.0f));
        CHECK(transform->scale.y == Approx(1.0f));
        CHECK(transform->scale.z == Approx(2.0f));

        CHECK(transform->orientation.real == Approx(1.0f));
        CHECK(transform->orientation.imag.x == Approx(0.0f));
        CHECK(transform->orientation.imag.y == Approx(0.0f));
        CHECK(transform->orientation.imag.z == Approx(0.0f));
    }

    {
        entity const &entity = entities[1];
        CHECK(entity.name == "Entity1");
        REQUIRE(entity.components.size() == 1);

        transform_component const * const transform = dynamic_cast<transform_component const*>(entity.components[0].get());
        CHECK(transform != nullptr);
        CHECK(transform->position.x == Approx(2.0f));
        CHECK(transform->position.y == Approx(0.0f));
        CHECK(transform->position.z == Approx(1.0f));

        CHECK(transform->scale.x == Approx(1.0f));
        CHECK(transform->scale.y == Approx(1.0f));
        CHECK(transform->scale.z == Approx(2.0f));

        CHECK(transform->orientation.real == Approx(1.0f));
        CHECK(transform->orientation.imag.x == Approx(0.0f));
        CHECK(transform->orientation.imag.y == Approx(0.0f));
        CHECK(transform->orientation.imag.z == Approx(0.0f));
    }

    {
        entity const &entity = entities[2];
        CHECK(entity.name == "Entity2");
        REQUIRE(entity.components.size() == 2);

        transform_component const * const transform = dynamic_cast<transform_component const*>(entity.components[0].get());
        CHECK(transform != nullptr);
        CHECK(transform->position.x == Approx(0.0f));
        CHECK(transform->position.y == Approx(0.0f));
        CHECK(transform->position.z == Approx(5.0f));

        CHECK(transform->scale.x == Approx(1.0f));
        CHECK(transform->scale.y == Approx(1.0f));
        CHECK(transform->scale.z == Approx(1.0f));

        CHECK(transform->orientation.real == Approx(1.0f));
        CHECK(transform->orientation.imag.x == Approx(0.0f));
        CHECK(transform->orientation.imag.y == Approx(0.0f));
        CHECK(transform->orientation.imag.z == Approx(0.0f));

        light_component const * const light = dynamic_cast<light_component const*>(entity.components[1].get());
        CHECK(light != nullptr);
        CHECK(light->type == light_type::directional);
        CHECK(light->distance_range.inner_radius == Approx(0.0f));
        CHECK(light->distance_range.outer_radius == Approx(0.0f));
        CHECK(light->angle_range.inner_angle == Approx(0.0f));
        CHECK(light->angle_range.outer_angle == Approx(0.0f));
        CHECK(light->direct_color.r == Approx(100.0f));
        CHECK(light->direct_color.g == Approx(101.0f));
        CHECK(light->direct_color.b == Approx(80.0f));
        CHECK(light->bounce_color.r == Approx(9.5f));
        CHECK(light->bounce_color.g == Approx(8.0f));
        CHECK(light->bounce_color.b == Approx(5.25f));
        CHECK(light->ambient_color.r == Approx(1.0f));
        CHECK(light->ambient_color.g == Approx(1.0f));
        CHECK(light->ambient_color.b == Approx(1.5f));
        CHECK(!light->shadow_map.enabled);
        CHECK(light->shadow_map.texture_size == shadow_map_texture_size::x1024);
        CHECK(light->shadow_map.cascade_count == shadow_map_cascade_count::x4);
        CHECK(light->shadow_map.depth_bias.offset == Approx(2.0f));
        CHECK(light->shadow_map.depth_bias.slope_scale == Approx(4.0f));
        CHECK(light->shadow_map.depth_bias.clamp == Approx(0.0f));
    }

    {
        entity const &entity = entities[3];
        CHECK(entity.name.empty());
        CHECK(entity.components.empty());
    }
}

bool read_value(m1::iarchive_json &in, m1::log &logger, vector3f &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("x"):
                result &= read_value(in, logger, value.x);
                break;

            case m1::property_id("y"):
                result &= read_value(in, logger, value.y);
                break;

            case m1::property_id("z"):
                result &= read_value(in, logger, value.z);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, color3f &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("r"):
            case m1::property_id("red"):
                result &= read_value(in, logger, value.r);
                break;

            case m1::property_id("g"):
            case m1::property_id("green"):
                result &= read_value(in, logger, value.g);
                break;

            case m1::property_id("b"):
            case m1::property_id("blue"):
                result &= read_value(in, logger, value.b);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, quaternionf &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("real"):
                result &= read_value(in, logger, value.real);
                break;

            case m1::property_id("imag"):
                result &= read_value(in, logger, value.imag);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, transformf &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("position"):
                result &= read_value(in, logger, value.position);
                break;

            case m1::property_id("scale"):
                result &= read_value(in, logger, value.scale);
                break;

            case m1::property_id("orientation"):
                result &= read_value(in, logger, value.orientation);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, light_type &value)
{
    m1::crc32 type;
    if(read_value(in, logger, type))
    {
        switch(type)
        {
            case m1::crc32("spot"):
                value = light_type::spot;
                return true;

            case m1::crc32("point"):
                value = light_type::point;
                return true;

            case m1::crc32("directional"):
                value = light_type::directional;
                return true;

            default:
                M1_ERROR(logger, "Invalid light_type");
                return false;
        }
    }

    return false;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, light_distance_range &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("inner_radius"):
                result &= read_value(in, logger, value.inner_radius);
                break;

            case m1::property_id("outer_radius"):
                result &= read_value(in, logger, value.outer_radius);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, light_angle_range &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("inner_angle"):
                result &= read_value(in, logger, value.inner_angle);
                break;

            case m1::property_id("outer_angle"):
                result &= read_value(in, logger, value.outer_angle);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map_texture_size &value)
{
    int size = 0;
    if(read_value(in, logger, size))
    {
        switch(size)
        {
            case 256:
                value = shadow_map_texture_size::x256;
                return true;

            case 512:
                value = shadow_map_texture_size::x512;
                return true;

            case 1024:
                value = shadow_map_texture_size::x1024;
                return true;

            case 2048:
                value = shadow_map_texture_size::x2048;
                return true;

            case 4096:
                value = shadow_map_texture_size::x4096;
                return true;

            default:
                return false;
        }
    }

    return false;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map_cascade_count &value)
{
    int size = 0;
    if(read_value(in, logger, size))
    {
        switch(size)
        {
            case 1:
                value = shadow_map_cascade_count::x1;
                return true;

            case 2:
                value = shadow_map_cascade_count::x2;
                return true;

            case 4:
                value = shadow_map_cascade_count::x4;
                return true;

            default:
                return false;
        }
    }

    return false;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map_depth_bias &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case 0:
            {
                m1::crc32 crc;
                if(result &= read_value(in, logger, crc))
                {
                    switch(crc)
                    {
                        case m1::crc32("default"):
                            value.offset = 2.0f;
                            value.slope_scale = 4.0f;
                            value.clamp = 0.0f;
                            break;

                        default:
                            M1_ERROR(logger, "Unknown value");
                            return false;
                    }
                }
                break;
            }

            case m1::property_id("offset"):
                result &= read_value(in, logger, value.offset);
                break;

            case m1::property_id("slope_scale"):
                result &= read_value(in, logger, value.slope_scale);
                break;

            case m1::property_id("clamp"):
                result &= read_value(in, logger, value.clamp);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, shadow_map &value)
{
    bool result = true;
    bool use_default_enable = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("enabled"):
                result &= read_value(in, logger, value.enabled);
                use_default_enable = false;
                break;

            case m1::property_id("texture_size"):
                result &= read_value(in, logger, value.texture_size);
                break;

            case m1::property_id("cascade_count"):
                result &= read_value(in, logger, value.cascade_count);
                break;

            case m1::property_id("depth_bias"):
                result &= read_value(in, logger, value.depth_bias);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    if(result && use_default_enable)
    {
        value.enabled = true;
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, light &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("type"):
                result &= read_value(in, logger, value.type);
                break;

            case m1::property_id("distance_range"):
                result &= read_value(in, logger, value.distance_range);
                break;

            case m1::property_id("angle_range"):
                result &= read_value(in, logger, value.angle_range);
                break;

            case m1::property_id("direct_color"):
                result &= read_value(in, logger, value.direct_color);
                break;

            case m1::property_id("bounce_color"):
                result &= read_value(in, logger, value.bounce_color);
                break;

            case m1::property_id("ambient_color"):
                result &= read_value(in, logger, value.ambient_color);
                break;

            case m1::property_id("shadow_map"):
                result &= read_value(in, logger, value.shadow_map);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, std::unique_ptr<component> &value)
{
    value.reset();

    bool result = true;
    transform_component *transform = nullptr;
    light_component *light = nullptr;

    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("type"):
            {
                m1::crc32 type;
                if(result &= read_value(in, logger, type))
                {
                    switch(type)
                    {
                        case m1::crc32("transform"):
                            value.reset(transform = new transform_component);
                            break;

                        case m1::crc32("light"):
                            value.reset(light = new light_component);
                            break;

                        default:
                            M1_WARN(logger, "Unknown component type");
                            break;
                    }
                    break;
                }
            }

            case m1::property_id("data"):
                if(transform != nullptr)
                {
                    result &= read_value(in, logger, *transform);
                }
                else if(light != nullptr)
                {
                    result &= read_value(in, logger, *light);
                }
                else
                {
                    skip_value(in, logger);
                }
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, entity &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("name"):
                result &= read_value(in, logger, value.name);
                break;

            case m1::property_id("components"):
                result &= read_value(in, logger, value.components);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, m1::log &logger, scene &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids(logger))
    {
        switch(id)
        {
            case m1::property_id("entities"):
                result &= read_value(in, logger, value.entities);
                break;

            default:
                M1_WARN(logger, "Unknown property");
                skip_value(in, logger);
                break;
        }
    }

    return result;
}
