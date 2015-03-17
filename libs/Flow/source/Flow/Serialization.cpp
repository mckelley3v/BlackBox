#include "Flow/Input.hpp"
#include "Flow/Output.hpp"
#include "Flow/Component.hpp"
#include "Flow/System.hpp"
#include "Flow/TypeManager.hpp"
#include "m1/iarchive_json.hpp"
#include "m1/iarchive_ubjson.hpp"

namespace Flow
{
    // =================================================================================================================
    // define inside namespace to allow proper ADL

    // Input
    template <typename IArchive> static bool read_value(IArchive &in, InputPortOptional &value);
    template <typename IArchive> static bool read_value(IArchive &in, InputPortMultiplex &value);
    template <typename IArchive> static bool read_value(IArchive &in, InputPortDefinition &value);

    // Output
    template <typename IArchive> static bool read_value(IArchive &in, OutputPortDefinition &value);

    // Component
    template <typename IArchive> static bool read_value(IArchive &in, ComponentProcessAnnotation &value);
    template <typename IArchive> static bool read_value(IArchive &in, ComponentAnnotations &value);
    template <typename IArchive> static bool read_value(IArchive &in, ComponentDefinition &value);

    // System
    template <typename IArchive, typename T> static bool read_value(IArchive &in,
                                                                    TypeManager const &type_manager,
                                                                    std::vector<T> &values);

    template <typename IArchive> static bool read_value(IArchive &in,
                                                        TypeManager const &type_manager,
                                                        SystemComponentInstance &value);

    template <typename IArchive> static bool read_value(IArchive &in,
                                                        TypeManager const &type_manager,
                                                        SystemConnectionPort &value);

    template <typename IArchive> static bool read_value(IArchive &in,
                                                        TypeManager const &type_manager,
                                                        SystemConnection &value);

    template <typename IArchive> static bool read_value(IArchive &in,
                                                        TypeManager const &type_manager,
                                                        SystemDefinition &value);

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, InputPortOptional &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, InputPortOptional &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, InputPortOptional &value)
{
    bool bool_value = false;
    if(read_value(in, bool_value))
    {
        value = bool_value ? InputPortOptional::Yes : InputPortOptional::No;
        return true;
    }

    return false;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, InputPortMultiplex &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, InputPortMultiplex &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, InputPortMultiplex &value)
{
    bool bool_value = false;
    if(read_value(in, bool_value))
    {
        value = bool_value ? InputPortMultiplex::Yes : InputPortMultiplex::No;
        return true;
    }

    return false;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, InputPortDefinition &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, InputPortDefinition &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, InputPortDefinition &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("PortName"):
                result &= read_value(in, value.PortName);
                break;

            case m1::property_id("TypeName"):
                result &= read_value(in, value.TypeName);
                break;

            case m1::property_id("IsOptional"):
                result &= read_value(in, value.IsOptional);
                break;

            case m1::property_id("IsMultiplex"):
                result &= read_value(in, value.IsMultiplex);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, OutputPortDefinition &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, OutputPortDefinition &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, OutputPortDefinition &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("PortName"):
                result &= read_value(in, value.PortName);
                break;

            case m1::property_id("TypeName"):
                result &= read_value(in, value.TypeName);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, ComponentProcessAnnotation &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, ComponentProcessAnnotation &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, ComponentProcessAnnotation &value)
{
    m1::crc32 crc;
    if(read_value(in, crc))
    {
        switch(crc)
        {
            case m1::crc32("Always"):
                value = ComponentProcessAnnotation::Always;
                return true;

            case m1::crc32("Once"):
                value = ComponentProcessAnnotation::Once;
                return true;

            case m1::crc32("Never"):
                value = ComponentProcessAnnotation::Never;
                return true;

            default:
                M1_ERROR(in.logger(), "Invalid Flow::ComponentProcessAnnotation");
                in.set_error_state();
                return false;
        }
    }

    return false;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, ComponentAnnotations &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, ComponentAnnotations &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, ComponentAnnotations &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("Process"):
                result &= read_value(in, value.Process);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, ComponentDefinition &value)
{
    return read_value<m1::iarchive_json>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, ComponentDefinition &value)
{
    return false;
    //return read_value<m1::iarchive_ubjson>(in, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in, ComponentDefinition &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("Name"):
                result &= read_value(in, value.Name);
                break;

            case m1::property_id("InputPorts"):
                result &= read_value(in, value.InputPorts);
                break;

            case m1::property_id("OutputPorts"):
                result &= read_value(in, value.OutputPorts);
                break;

            case m1::property_id("Annotations"):
                result &= read_value(in, value.Annotations);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in, Component::InstanceData &value)
{
    return value.ReadArchive(in);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in, Component::InstanceData &value)
{
    return value.ReadArchive(in);
}

// =====================================================================================================================

template <typename IArchive, typename T> /*static*/ bool Flow::read_value(IArchive &in,
                                                                          TypeManager const &type_manager,
                                                                          std::vector<T> &values)
{
    T temp{};
    values.clear();
    for(int const array_index : in.get_array_indices())
    {
        // allow user-defined overloads
        using m1::read_value;
        if(read_value(in, type_manager, temp))
        {
            values.push_back(std::move(temp));
        }
        else
        {
            M1_ERROR(in.logger(), "Unable to read value at index: " << array_index << "\n");
            in.set_error_state();
            return false;
        }
    }

    return true;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in,
                      TypeManager const &type_manager,
                      SystemComponentInstance &value)
{
    return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in,
                      TypeManager const &type_manager,
                      SystemComponentInstance &value)
{
    return false;
    //return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in,
                                                              TypeManager const &type_manager,
                                                              SystemComponentInstance &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("DefinitionName"):
                result &= read_value(in, value.DefinitionName);
                break;

            case m1::property_id("InstanceName"):
                result &= read_value(in, value.InstanceName);
                break;

            case m1::property_id("InstanceData"):
                value.InstanceDataPtr = type_manager.MakeComponentInstanceData(value.DefinitionName);
                result &= read_value(in, *value.InstanceDataPtr);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in,
                      TypeManager const &type_manager,
                      SystemConnectionPort &value)
{
    return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in,
                      TypeManager const &type_manager,
                      SystemConnectionPort &value)
{
    return false;
    //return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in,
                                                              TypeManager const &type_manager,
                                                              SystemConnectionPort &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("ComponentInstanceName"):
                result &= read_value(in, value.ComponentInstanceName);
                break;

            case m1::property_id("PortName"):
                result &= read_value(in, value.PortName);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in,
                      TypeManager const &type_manager,
                      SystemConnection &value)
{
    return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in,
                      TypeManager const &type_manager,
                      SystemConnection &value)
{
    return false;
    //return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in,
                                                              TypeManager const &type_manager,
                                                              SystemConnection &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("SourcePort"):
                result &= read_value(in, type_manager, value.SourcePort);
                break;

            case m1::property_id("TargetPort"):
                result &= read_value(in, type_manager, value.TargetPort);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================

bool Flow::read_value(m1::iarchive_json &in,
                      TypeManager const &type_manager,
                      SystemDefinition &value)
{
    return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Flow::read_value(m1::iarchive_ubjson &in,
                      TypeManager const &type_manager,
                      SystemDefinition &value)
{
    return false;
    //return read_value(in, type_manager, value);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename IArchive> /*static*/ bool Flow::read_value(IArchive &in,
                                                              TypeManager const &type_manager,
                                                              SystemDefinition &value)
{
    bool result = true;
    for(m1::property_id const &id : in.get_property_ids())
    {
        switch(id)
        {
            case m1::property_id("Interface"):
                result &= read_value(in, value.Interface);
                break;

            case m1::property_id("ComponentInstances"):
                result &= read_value(in, type_manager, value.ComponentInstances);
                break;

            case m1::property_id("Connections"):
                result &= read_value(in, type_manager, value.Connections);
                break;

            default:
                M1_WARN(in.logger(), "Unknown property");
                result &= skip_value(in);
                break;
        }
    }

    return result;
}

// =====================================================================================================================
