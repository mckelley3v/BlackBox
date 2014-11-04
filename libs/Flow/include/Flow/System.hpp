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

namespace Flow
{
namespace IO
{
    // =================================================================================================================

    struct SystemComponentInstance;
    struct SystemConnectionPort;
    struct SystemConnection;
    struct SystemDefinition;

    // =================================================================================================================

    enum class VerifyBuffer : bool
    {
        No,
        Yes,
    };

    // -----------------------------------------------------------------------------------------------------------------

    SystemDefinition const* ParseSystemDefinitionBuffer(void const * const buffer_ptr,
                                                        std::size_t const buffer_size,
                                                        VerifyBuffer const verify_buffer = VerifyBuffer::Yes);

    // =================================================================================================================
} // namespace IO
} // namespace Flow

namespace Flow
{
    // =================================================================================================================

    class TypeManager;

    // =================================================================================================================

    struct SystemComponentInstanceInitializer
    {
        char const *DefinitionName;
        char const *InstanceName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemConnectionPortInitializer
    {
        char const *ComponentInstanceName;
        char const *PortName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemConnectionInitializer
    {
        SystemConnectionPortInitializer SourcePort;
        SystemConnectionPortInitializer TargetPort;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemDefinitionInitializer
    {
        ComponentDefinitionInitializer Interface;
        std::initializer_list<SystemComponentInstanceInitializer> ComponentInstances;
        std::initializer_list<SystemConnectionInitializer> Connections;
    };

    // =================================================================================================================

    class SystemComponentInstance
    {
    public:
        SystemComponentInstance() = delete;
        explicit SystemComponentInstance(SystemComponentInstanceInitializer definition_initializer);
        explicit SystemComponentInstance(IO::SystemComponentInstance const * const definition_io_ptr);
        SystemComponentInstance(SystemComponentInstance &&rhs) = default;
        SystemComponentInstance(SystemComponentInstance const &rhs) = delete;
        SystemComponentInstance& operator = (SystemComponentInstance &&rhs) = default;
        SystemComponentInstance& operator = (SystemComponentInstance const &rhs) = delete;
        ~SystemComponentInstance() = default;

        // members:
        std::string DefinitionName;
        std::string InstanceName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemConnectionPort
    {
    public:
        SystemConnectionPort() = delete;
        explicit SystemConnectionPort(SystemConnectionPortInitializer definition_initializer);
        explicit SystemConnectionPort(IO::SystemConnectionPort const * const definition_io_ptr);
        SystemConnectionPort(SystemConnectionPort &&rhs) = default;
        SystemConnectionPort(SystemConnectionPort const &rhs) = delete;
        SystemConnectionPort& operator = (SystemConnectionPort &&rhs) = default;
        SystemConnectionPort& operator = (SystemConnectionPort const &rhs) = delete;
        ~SystemConnectionPort() = default;

        // members:
        std::string ComponentInstanceName;
        std::string PortName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemConnection
    {
    public:
        SystemConnection() = delete;
        explicit SystemConnection(SystemConnectionInitializer definition_initializer);
        explicit SystemConnection(IO::SystemConnection const * const definition_io_ptr);
        SystemConnection(SystemConnection &&rhs) = default;
        SystemConnection(SystemConnection const &rhs) = delete;
        SystemConnection& operator = (SystemConnection &&rhs) = default;
        SystemConnection& operator = (SystemConnection const &rhs) = delete;
        ~SystemConnection() = default;

        // members:
        SystemConnectionPort SourcePort;
        SystemConnectionPort TargetPort;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemDefinition
    {
    public:
        SystemDefinition() = delete;
        explicit SystemDefinition(SystemDefinitionInitializer definition_initializer);
        explicit SystemDefinition(IO::SystemDefinition const * const definition_io_ptr);
        SystemDefinition(SystemDefinition &&rhs) = default;
        SystemDefinition(SystemDefinition const &rhs) = delete;
        SystemDefinition& operator = (SystemDefinition &&rhs) = default;
        SystemDefinition& operator = (SystemDefinition const &rhs) = delete;
        ~SystemDefinition() = default;

        // members:
        ComponentDefinition Interface;
        std::vector<SystemComponentInstance> ComponentInstances;
        std::vector<SystemConnection> Connections;
    };

    // =================================================================================================================

    class SystemInstance
    {
    public:
        SystemInstance() = delete;
        SystemInstance(SystemInstance &&rhs) = default;
        SystemInstance(SystemInstance const &rhs) = delete;
        SystemInstance& operator = (SystemInstance &&rhs) = default;
        SystemInstance& operator = (SystemInstance const &rhs) = delete;
        ~SystemInstance() = default;

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
        SystemBase(SystemBase const &rhs) = delete;
        SystemBase& operator = (SystemBase &&rhs) = default;
        SystemBase& operator = (SystemBase const &rhs) = delete;
        ~SystemBase() = default;

    protected:
        typedef std::vector<std::unique_ptr<Component>> ComponentPtrs;

        ComponentPtrs const& GetComponentPtrs() const;
        ComponentOutputConnectionPtrDict& OutputConnectionPtrDict();

    private:
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

        System() = delete;
        System(TypeManager const &type_manager,
               SystemDefinition definition_initializer,
               SystemInstance instance);
        System(System &&rhs) = default;
        System(System const &rhs) = delete;
        System& operator = (System &&rhs) = default;
        System& operator = (System const &rhs) = delete;
        ~System() = default;

        virtual void Process() override;

    private:
        // members:
        std::vector<Component*> m_ActiveComponentPtrs;
    };

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_SYSTEM_HPP
