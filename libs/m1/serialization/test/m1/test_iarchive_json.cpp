#include "m1/iarchive_json.hpp"
#include "m1/numeric/is_close.hpp"
#include "m1/log.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

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

bool read_value(m1::iarchive_json &in, vector3f &value);
bool read_value(m1::iarchive_json &in, color3f &value);
bool read_value(m1::iarchive_json &in, quaternionf &value);
bool read_value(m1::iarchive_json &in, transformf &value);
bool read_value(m1::iarchive_json &in, light_type &value);
bool read_value(m1::iarchive_json &in, light_distance_range &value);
bool read_value(m1::iarchive_json &in, light_angle_range &value);
bool read_value(m1::iarchive_json &in, shadow_map_texture_size &value);
bool read_value(m1::iarchive_json &in, shadow_map_cascade_count &value);
bool read_value(m1::iarchive_json &in, shadow_map_depth_bias &value);
bool read_value(m1::iarchive_json &in, shadow_map &value);
bool read_value(m1::iarchive_json &in, light &value);
bool read_value(m1::iarchive_json &in, std::unique_ptr<component> &value);
bool read_value(m1::iarchive_json &in, entity &value);
bool read_value(m1::iarchive_json &in, scene &value);

// object (null, empty, unbracketed, regular)
// array (null, empty, unbracketed, regular)
// property
// string (regular, escaped)
// int (positive, negative)
// float (positive, negative, int, frac, exp)
// true, false
bool test_iarchive_json()
{
    char const * const json =
        "{\n"
        "    \"entities\":\n"
        "    [\n"
        "        {\n"
        "            \"name\":  \"Entity0\",\n"
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
        "            \"name\":  \"Entity2\",\n"
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
        "        }\n"
        "    ]\n"
        "}";

    m1::log logger(std::cout,
                   std::clog,
                   std::cerr);
    // TODO - move logger out from iarchive_json and instead pass as arg to read_value functions
    m1::iarchive_json in(logger, json);

    scene data = {};
    bool const is_data_valid = read_value(in, data);
    assert(is_data_valid);

    using m1::is_close;

    std::vector<entity> const &entities = data.entities;
    assert(entities.size() == 3);

    {
        entity const &entity = entities[0];
        assert(entity.name == "Entity0");

        transform_component const * const transform = dynamic_cast<transform_component const*>(entity.components[0].get());
        assert(transform != nullptr);
        assert(is_close(transform->position.x, 0.0f));
        assert(is_close(transform->position.y, 0.0f));
        assert(is_close(transform->position.z, 1.0f));

        assert(is_close(transform->scale.x, 1.0f));
        assert(is_close(transform->scale.y, 1.0f));
        assert(is_close(transform->scale.z, 2.0f));

        assert(is_close(transform->orientation.real, 1.0f));
        assert(is_close(transform->orientation.imag.x, 0.0f));
        assert(is_close(transform->orientation.imag.y, 0.0f));
        assert(is_close(transform->orientation.imag.z, 0.0f));
    }

    {
        entity const &entity = entities[1];
        assert(entity.name == "Entity1");
        assert(entity.components.size() == 1);

        transform_component const * const transform = dynamic_cast<transform_component const*>(entity.components[0].get());
        assert(transform != nullptr);
        assert(is_close(transform->position.x, 2.0f));
        assert(is_close(transform->position.y, 0.0f));
        assert(is_close(transform->position.z, 1.0f));

        assert(is_close(transform->scale.x, 1.0f));
        assert(is_close(transform->scale.y, 1.0f));
        assert(is_close(transform->scale.z, 2.0f));

        assert(is_close(transform->orientation.real, 1.0f));
        assert(is_close(transform->orientation.imag.x, 0.0f));
        assert(is_close(transform->orientation.imag.y, 0.0f));
        assert(is_close(transform->orientation.imag.z, 0.0f));
    }

    {
        entity const &entity = entities[2];
        assert(entity.name == "Entity2");
        assert(entity.components.size() == 2);

        transform_component const * const transform = dynamic_cast<transform_component const*>(entity.components[0].get());
        assert(transform != nullptr);
        assert(is_close(transform->position.x, 0.0f));
        assert(is_close(transform->position.y, 0.0f));
        assert(is_close(transform->position.z, 5.0f));

        assert(is_close(transform->scale.x, 1.0f));
        assert(is_close(transform->scale.y, 1.0f));
        assert(is_close(transform->scale.z, 1.0f));

        assert(is_close(transform->orientation.real, 1.0f));
        assert(is_close(transform->orientation.imag.x, 0.0f));
        assert(is_close(transform->orientation.imag.y, 0.0f));
        assert(is_close(transform->orientation.imag.z, 0.0f));

        light_component const * const light = dynamic_cast<light_component const*>(entity.components[1].get());
        assert(light != nullptr);
        assert(light->type == light_type::directional);
        assert(is_close(light->distance_range.inner_radius, 0.0f));
        assert(is_close(light->distance_range.outer_radius, 0.0f));
        assert(is_close(light->angle_range.inner_angle, 0.0f));
        assert(is_close(light->angle_range.outer_angle, 0.0f));
        assert(is_close(light->direct_color.r, 100.0f));
        assert(is_close(light->direct_color.g, 101.0f));
        assert(is_close(light->direct_color.b, 80.0f));
        assert(is_close(light->bounce_color.r, 9.5f));
        assert(is_close(light->bounce_color.g, 8.0f));
        assert(is_close(light->bounce_color.b, 5.25f));
        assert(is_close(light->ambient_color.r, 1.0f));
        assert(is_close(light->ambient_color.g, 1.0f));
        assert(is_close(light->ambient_color.b, 1.5f));
        assert(!light->shadow_map.enabled);
        assert(light->shadow_map.texture_size == shadow_map_texture_size::x1024);
        assert(light->shadow_map.cascade_count == shadow_map_cascade_count::x4);
        assert(is_close(light->shadow_map.depth_bias.offset, 2.0f));
        assert(is_close(light->shadow_map.depth_bias.slope_scale, 4.0f));
        assert(is_close(light->shadow_map.depth_bias.clamp, 0.0f));
    }

    return true;
}

bool read_value(m1::iarchive_json &in, vector3f &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("x"):
                result &= read_value(in, value.x);
                break;

            case m1::property_id("y"):
                result &= read_value(in, value.y);
                break;

            case m1::property_id("z"):
                result &= read_value(in, value.z);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, color3f &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("r"):
            case m1::property_id("red"):
                result &= read_value(in, value.r);
                break;

            case m1::property_id("g"):
            case m1::property_id("green"):
                result &= read_value(in, value.g);
                break;

            case m1::property_id("b"):
            case m1::property_id("blue"):
                result &= read_value(in, value.b);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, quaternionf &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("real"):
                result &= read_value(in, value.real);
                break;

            case m1::property_id("imag"):
                result &= read_value(in, value.imag);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, transformf &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("position"):
                result &= read_value(in, value.position);
                break;

            case m1::property_id("scale"):
                result &= read_value(in, value.scale);
                break;

            case m1::property_id("orientation"):
                result &= read_value(in, value.orientation);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, light_type &value)
{
    m1::crc32 type;
    if(read_value(in, type))
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
                assert(false && "Invalid light_type");
                return false;
        }
    }

    return false;
}

bool read_value(m1::iarchive_json &in, light_distance_range &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("inner_radius"):
                result &= read_value(in, value.inner_radius);
                break;

            case m1::property_id("outer_radius"):
                result &= read_value(in, value.outer_radius);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, light_angle_range &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("inner_angle"):
                result &= read_value(in, value.inner_angle);
                break;

            case m1::property_id("outer_angle"):
                result &= read_value(in, value.outer_angle);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, shadow_map_texture_size &value)
{
    int size = 0;
    if(read_value(in, size))
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

bool read_value(m1::iarchive_json &in, shadow_map_cascade_count &value)
{
    int size = 0;
    if(read_value(in, size))
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

bool read_value(m1::iarchive_json &in, shadow_map_depth_bias &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case 0:
            {
                m1::crc32 crc;
                if(result &= read_value(in, crc))
                {
                    switch(crc)
                    {
                        case m1::crc32("default"):
                            value.offset = 2.0f;
                            value.slope_scale = 4.0f;
                            value.clamp = 0.0f;
                            break;

                        default:
                            assert(false && "Invalid named identifier");
                            return false;
                    }
                }
                break;
            }

            case m1::property_id("offset"):
                result &= read_value(in, value.offset);
                break;

            case m1::property_id("slope_scale"):
                result &= read_value(in, value.slope_scale);
                break;

            case m1::property_id("clamp"):
                result &= read_value(in, value.clamp);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, shadow_map &value)
{
    bool result = true;
    bool use_default_enable = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("enabled"):
                result &= read_value(in, value.enabled);
                use_default_enable = false;
                break;

            case m1::property_id("texture_size"):
                result &= read_value(in, value.texture_size);
                break;

            case m1::property_id("cascade_count"):
                result &= read_value(in, value.cascade_count);
                break;

            case m1::property_id("depth_bias"):
                result &= read_value(in, value.depth_bias);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    if(result && use_default_enable)
    {
        value.enabled = true;
    }

    return result;
}

bool read_value(m1::iarchive_json &in, light &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("type"):
                result &= read_value(in, value.type);
                break;

            case m1::property_id("distance_range"):
                result &= read_value(in, value.distance_range);
                break;

            case m1::property_id("angle_range"):
                result &= read_value(in, value.angle_range);
                break;

            case m1::property_id("direct_color"):
                result &= read_value(in, value.direct_color);
                break;

            case m1::property_id("bounce_color"):
                result &= read_value(in, value.bounce_color);
                break;

            case m1::property_id("ambient_color"):
                result &= read_value(in, value.ambient_color);
                break;

            case m1::property_id("shadow_map"):
                result &= read_value(in, value.shadow_map);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, std::unique_ptr<component> &value)
{
    value.reset();

    bool result = true;
    transform_component *transform = nullptr;
    light_component *light = nullptr;

    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("type"):
            {
                m1::crc32 type;
                if(result &= read_value(in, type))
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
                            result = false;
                            break;
                    }
                    break;
                }
            }

            case m1::property_id("data"):
                if(transform != nullptr)
                {
                    result &= read_value(in, *transform);
                }
                else if(light != nullptr)
                {
                    result &= read_value(in, *light);
                }
                else
                {
                    assert(false && "Unspecified type");
                    skip_value(in);
                    result = false;
                }
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, entity &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("name"):
                result &= read_value(in, value.name);
                break;

            case m1::property_id("components"):
                result &= read_value(in, value.components);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}

bool read_value(m1::iarchive_json &in, scene &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("entities"):
                result &= read_value(in, value.entities);
                break;

            default:
                skip_value(in);
                break;
        }
    }

    return result;
}
