#ifndef FLOW_COMPONENT_HPP
#define FLOW_COMPONENT_HPP

// =====================================================================================================================
// class Flow::Component
// - Base class that provides a processing interface and methods to query for available inputs and outputs
// - Derive from this class to extend data flow capabilites
// =====================================================================================================================

#include "Flow/Input.hpp"
#include "Flow/Output.hpp"
#include "m1/dictionary.hpp"
#include <string>
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cassert>

namespace m1
{
    // =================================================================================================================

    class iarchive_json;
    class iarchive_ubjson;

    // =================================================================================================================
} // namespace m1

namespace Flow
{
    // =================================================================================================================

    class TypeManager;

    // =================================================================================================================

    enum class ComponentProcessAnnotation
    {
        Always,
        Once,
        Never,
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, ComponentProcessAnnotation &value);
    bool read_value(m1::iarchive_ubjson &in, ComponentProcessAnnotation &value);

    // =================================================================================================================

    struct ComponentAnnotations
    {
        ComponentProcessAnnotation Process;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, ComponentAnnotations &value);
    bool read_value(m1::iarchive_ubjson &in, ComponentAnnotations &value);

    // =================================================================================================================

    struct ComponentDefinition
    {
        // members:
        std::string Name;
        std::vector<InputPortDefinition> InputPorts;
        std::vector<OutputPortDefinition> OutputPorts;
        ComponentAnnotations Annotations;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, ComponentDefinition &value);
    bool read_value(m1::iarchive_ubjson &in, ComponentDefinition &value);

    // =================================================================================================================

    typedef m1::dictionary<std::vector<m1::const_any_ptr>> ComponentInputConnectionPtrsDict;
    typedef m1::dictionary<m1::any_ptr> ComponentOutputConnectionPtrDict;

    // =================================================================================================================

    struct ComponentInstance
    {
        // members:
        std::string Name;
        ComponentInputConnectionPtrsDict InputConnectionPtrsDict;
        ComponentOutputConnectionPtrDict OutputConnectionPtrDict;
    };

    // =================================================================================================================

    typedef m1::dictionary<InputPort> ComponentInputPortDict;
    typedef m1::dictionary<OutputPort> ComponentOutputPortDict;

    // =================================================================================================================

    class Component
    {
    public:
        class InstanceData;

        Component(TypeManager const &type_manager,
                  ComponentDefinition definition,
                  ComponentInstance instance);
        Component(Component &&rhs) = default;
        Component& operator = (Component &&rhs) = default;
        virtual ~Component() = default;

        // definition:
        std::string const& GetDefinitionName() const;
        ComponentAnnotations const& GetAnnotations() const;

        // instance:
        std::string const& GetInstanceName() const;

        ComponentInputPortDict& InputPortDict();
        ComponentInputPortDict const& GetInputPortDict() const;

        ComponentOutputPortDict& OutputPortDict();
        ComponentOutputPortDict const& GetOutputPortDict() const;

        virtual void Process();

    private:
        Component() = delete;
        Component(Component const &rhs) = delete;
        Component& operator = (Component const &rhs) = delete;

        // members:
        std::string m_DefinitionName;
        ComponentAnnotations m_Annotations;
        std::string m_InstanceName;
        ComponentInputPortDict m_InputPortDict;
        ComponentOutputPortDict m_OutputPortDict;
    };

    // =================================================================================================================

    template <typename T> T const* GetInputConnectionPtr(ComponentInputPortDict const &input_port_dict,
                                                         char const *port_name,
                                                         int index = 0);

    template <typename T> T const* GetInputConnectionPtr(Component const &component,
                                                         char const *port_name,
                                                         int index = 0);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> T const& GetInputConnectionRef(ComponentInputPortDict const &input_port_dict,
                                                         char const *port_name,
                                                         int index = 0);

    template <typename T> T const& GetInputConnectionRef(Component const &component,
                                                         char const *port_name,
                                                         int index = 0);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> T const* GetOutputConnectionPtr(ComponentOutputPortDict const &output_port_dict,
                                                          char const *port_name);

    template <typename T> T const* GetOutputConnectionPtr(Component const &component,
                                                          char const *port_name);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> T const& GetOutputConnectionRef(ComponentOutputPortDict const &output_port_dict,
                                                          char const *port_name);

    template <typename T> T const& GetOutputConnectionRef(Component const &component,
                                                          char const *port_name);

    // =================================================================================================================

    bool read_value(m1::iarchive_json &in, Component::InstanceData &value);
    bool read_value(m1::iarchive_ubjson &in, Component::InstanceData &value);

    class Component::InstanceData
    {
    public:
        InstanceData() = default;
        InstanceData(InstanceData &&rhs) = default;
        InstanceData& operator = (InstanceData &&rhs) = default;
        virtual ~InstanceData() = default;

        friend bool read_value(m1::iarchive_json &in, InstanceData &value);
        friend bool read_value(m1::iarchive_ubjson &in, InstanceData &value);

    private:
        InstanceData(InstanceData const &rhs) = delete;
        InstanceData& operator = (InstanceData const &rhs) = delete;

        virtual bool ReadArchive(m1::iarchive_json &in) = 0;
        virtual bool ReadArchive(m1::iarchive_ubjson &in) = 0;
    };

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

template <typename T> T const* Flow::GetInputConnectionPtr(ComponentInputPortDict const &input_port_dict,
                                                           char const * const port_name,
                                                           int const index /*= 0*/)
{
    InputPort const &port = input_port_dict.at(port_name);
    m1::const_any_ptr const &connection_ptr = port.GetConnectionPtrs().at(index);
    return m1::static_pointer_cast<T>(connection_ptr);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const* Flow::GetInputConnectionPtr(Component const &component,
                                                           char const * const port_name,
                                                           int const index /*= 0*/)
{
    return GetInputConnectionPtr<T>(component.GetInputPortDict(), port_name, index);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const& Flow::GetInputConnectionRef(ComponentInputPortDict const &input_port_dict,
                                                           char const * const port_name,
                                                           int const index /*= 0*/)
{
    T const * const connection_ptr = GetInputConnectionPtr<T>(input_port_dict, port_name, index);
    assert(connection_ptr != nullptr);
    if(!connection_ptr) throw std::runtime_error("Unexpected null connection");
    return *connection_ptr;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const& Flow::GetInputConnectionRef(Component const &component,
                                                           char const * const port_name,
                                                           int const index /*= 0*/)
{
    return GetInputConnectionRef<T>(component.GetInputPortDict(), port_name, index);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const* Flow::GetOutputConnectionPtr(ComponentOutputPortDict const &output_port_dict,
                                                            char const * const port_name)
{
    OutputPort const &port = output_port_dict.at(port_name);
    return m1::static_pointer_cast<T>(port.GetConnectionPtr());
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const* Flow::GetOutputConnectionPtr(Component const &component,
                                                            char const * const port_name)
{
    return GetOutputConnectionPtr<T>(component.GetOutputPortDict(), port_name);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const& Flow::GetOutputConnectionRef(ComponentOutputPortDict const &output_port_dict,
                                                            char const * const port_name)
{
    T const * const connection_ptr = GetOutputConnectionPtr<T>(output_port_dict, port_name);
    assert(connection_ptr != nullptr);
    if(!connection_ptr) throw std::runtime_error("Unexpected null connection");
    return *connection_ptr;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T> T const& Flow::GetOutputConnectionRef(Component const &component,
                                                            char const * const port_name)
{
    return GetOutputConnectionRef<T>(component.GetOutputPortDict(), port_name);
}

// =====================================================================================================================

#endif // FLOW_COMPONENT_HPP
