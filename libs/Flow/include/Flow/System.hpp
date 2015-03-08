#ifndef FLOW_SYSTEM_HPP
#define FLOW_SYSTEM_HPP

// =====================================================================================================================
// class Flow::System
// - a Flow::Component that implements a graph of Flow::Component objects
//   and processes them in dependency order
// =====================================================================================================================

#include "Flow/Component.hpp"
#include <functional>
#include <string>
#include <memory>

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

    struct SystemComponentInstance
    {
        // members:
        std::string DefinitionName;
        std::string InstanceName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, m1::log &logger, SystemComponentInstance &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemComponentInstance &value);

    // =================================================================================================================

    struct SystemConnectionPort
    {
        // members:
        std::string ComponentInstanceName;
        std::string PortName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, m1::log &logger, SystemConnectionPort &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemConnectionPort &value);

    // =================================================================================================================

    struct SystemConnection
    {
        // members:
        SystemConnectionPort SourcePort;
        SystemConnectionPort TargetPort;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, m1::log &logger, SystemConnection &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemConnection &value);

    // =================================================================================================================

    struct SystemDefinition
    {
        // members:
        ComponentDefinition Interface;
        std::vector<SystemComponentInstance> ComponentInstances;
        std::vector<SystemConnection> Connections;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, m1::log &logger, SystemDefinition &value);
    bool read_value(m1::iarchive_ubjson &in, m1::log &logger, SystemDefinition &value);

    // =================================================================================================================

    struct SystemInstance
    {
        // members:
        std::string Name;
        ComponentInputConnectionPtrsDict InputConnectionPtrsDict;
    };

    // =================================================================================================================

    class SystemBase
    {
    public:
        SystemBase(TypeManager const &type_manager,
                   SystemDefinition const &definition,
                   ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict);
        SystemBase(SystemBase &&rhs) = default;
        SystemBase& operator = (SystemBase &&rhs) = default;
        ~SystemBase() = default;

    protected:
        typedef std::vector<std::unique_ptr<Component>> ComponentPtrs;

        ComponentPtrs const& GetComponentPtrs() const;
        ComponentOutputConnectionPtrDict& OutputConnectionPtrDict();

    private:
        SystemBase() = delete;
        SystemBase& operator = (SystemBase const &rhs) = delete;
        SystemBase(SystemBase const &rhs) = delete;

        // members:
        ComponentPtrs m_ComponentPtrs;
        ComponentOutputConnectionPtrDict m_OutputConnectionPtrDict;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class System
        : private SystemBase
        , public Component
    {
    public:
        static char const * const In;
        static char const * const Out;

        System(TypeManager const &type_manager,
               SystemDefinition definition_initializer,
               SystemInstance instance);
        System(System &&rhs) = default;
        System& operator = (System &&rhs) = default;
        ~System() = default;

        virtual void Process() override;

    private:
        System() = delete;
        System(System const &rhs) = delete;
        System& operator = (System const &rhs) = delete;

        // members:
        int m_ProcessCount;
        std::vector<Component*> m_ActiveComponentPtrs;
    };

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_SYSTEM_HPP
