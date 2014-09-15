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

    struct SystemDefinition;

    enum class VerifyBuffer : bool
    {
        No,
        Yes,
    };

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

    struct SystemComponentInstance
    {
        char const *DefinitionName;
        char const *InstanceName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemConnectionPort
    {
        char const *ComponentInstanceName;
        char const *PortName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemConnection
    {
        SystemConnectionPort SourcePort;
        SystemConnectionPort TargetPort;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemDefinition
    {
        ComponentDefinition Interface;
        std::initializer_list<SystemComponentInstance> ComponentInstances;
        std::initializer_list<SystemConnection> Connections;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct SystemInstance
    {
        std::string Name;
        ComponentInputConnectionPtrsDict InputConnectionPtrsDict;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class SystemBase
    {
    public:
        SystemBase(TypeManager const &type_manager,
                   SystemDefinition const &definition,
                   ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict);
//        SystemBase(TypeManager const &type_manager,
//                   IO::SystemDefinition const * const definition_ptr,
//                   ComponentInputConnectionPtrsDict const &input_connection_ptrs_dict);
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

        System(TypeManager const &type_manager,
               SystemDefinition definition,
               SystemInstance instance);
//        System(TypeManager const &type_manager,
//               IO::SystemDefinition const * const definition_ptr,
//               SystemInstance instance);
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
