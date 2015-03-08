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

    class log;
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

    bool read_value(m1::iarchive_json &in, m1::log &logger, ComponentProcessAnnotation &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, ComponentProcessAnnotation &value);

    // =================================================================================================================

    struct ComponentAnnotations
    {
        ComponentProcessAnnotation Process;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, m1::log &logger, ComponentAnnotations &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, ComponentAnnotations &value);

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

    bool read_value(m1::iarchive_json &in, m1::log &logger, ComponentDefinition &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, ComponentDefinition &value);

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

    class Component
    {
    public:
        typedef m1::dictionary<InputPort> InputPortDict;
        typedef m1::dictionary<OutputPort> OutputPortDict;

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
        InputPortDict const& GetInputPortDict() const;
        OutputPortDict const& GetOutputPortDict() const;

        virtual void Process();

    private:
        Component() = delete;
        Component(Component const &rhs) = delete;
        Component& operator = (Component const &rhs) = delete;

        // members:
        std::string m_DefinitionName;
        ComponentAnnotations m_Annotations;
        std::string m_InstanceName;
        InputPortDict m_InputPortDict;
        OutputPortDict m_OutputPortDict;
    };

    // =================================================================================================================

    template <typename T> T const* GetInputConnectionPtr(Component::InputPortDict const &input_port_dict,
                                                         char const * const port_name,
                                                         int const index = 0);

    template <typename T> T const* GetInputConnectionPtr(Component const &component,
                                                         char const * const port_name,
                                                         int const index = 0);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> T const& GetInputConnectionRef(Component::InputPortDict const &input_port_dict,
                                                         char const * const port_name,
                                                         int const index = 0);

    template <typename T> T const& GetInputConnectionRef(Component const &component,
                                                         char const * const port_name,
                                                         int const index = 0);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> T const* GetOutputConnectionPtr(Component::OutputPortDict const &output_port_dict,
                                                          char const * const port_name);

    template <typename T> T const* GetOutputConnectionPtr(Component const &component,
                                                          char const * const port_name);

    // -----------------------------------------------------------------------------------------------------------------

    template <typename T> T const& GetOutputConnectionRef(Component::OutputPortDict const &output_port_dict,
                                                          char const * const port_name);

    template <typename T> T const& GetOutputConnectionRef(Component const &component,
                                                          char const * const port_name);

    // =================================================================================================================
} // namespace Flow

// =====================================================================================================================

template <typename T> T const* Flow::GetInputConnectionPtr(Component::InputPortDict const &input_port_dict,
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

template <typename T> T const& Flow::GetInputConnectionRef(Component::InputPortDict const &input_port_dict,
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

template <typename T> T const* Flow::GetOutputConnectionPtr(Component::OutputPortDict const &output_port_dict,
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

template <typename T> T const& Flow::GetOutputConnectionRef(Component::OutputPortDict const &output_port_dict,
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
