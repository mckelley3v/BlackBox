#ifndef FLOW_OUTPUT_HPP
#define FLOW_OUTPUT_HPP

// =====================================================================================================================
// Flow::OutputPort
// - Simple class that acts as an output port for a Flow::Component
// - Contains a type-safe pointer to values provided by Flow::Component and updated via Component::Process
// =====================================================================================================================

#include "m1/any_ptr.hpp"
#include <string>

namespace Flow
{
namespace IO
{
    // =================================================================================================================

    struct OutputPortDefinition;

    // =================================================================================================================
} // namespace IO
} // namespace Flow

namespace Flow
{
    // =================================================================================================================

    struct OutputPortDefinitionInitializer
    {
        char const *PortName;
        char const *TypeName;
    };

    // =================================================================================================================

    class OutputPortDefinition
    {
    public:
        OutputPortDefinition() = delete;
        explicit OutputPortDefinition(OutputPortDefinitionInitializer definition_initializer);
        explicit OutputPortDefinition(IO::OutputPortDefinition const * const definition_io_ptr);
        OutputPortDefinition(OutputPortDefinition &&rhs) = default;
        OutputPortDefinition(OutputPortDefinition const &rhs) = default;
        OutputPortDefinition& operator = (OutputPortDefinition &&rhs) = default;
        OutputPortDefinition& operator = (OutputPortDefinition const &rhs) = default;
        ~OutputPortDefinition() = default;

        // members:
        std::string PortName;
        std::string TypeName;
    };

    // =================================================================================================================

    class OutputPortInstance
    {
    public:
        OutputPortInstance() = delete;
        OutputPortInstance(OutputPortInstance &&rhs) = default;
        OutputPortInstance(OutputPortInstance const &rhs) = default;
        OutputPortInstance& operator = (OutputPortInstance &&rhs) = default;
        OutputPortInstance& operator = (OutputPortInstance const &rhs) = default;
        ~OutputPortInstance() = default;

        // members:
        m1::any_ptr ConnectionPtr;
    };

    // =================================================================================================================

    class OutputPort
    {
    public:
        OutputPort() = delete;
        OutputPort(OutputPortDefinition definition,
                   OutputPortInstance instance);
        OutputPort(OutputPort &&rhs) = default;
        OutputPort(OutputPort const &rhs) = delete;
        OutputPort& operator = (OutputPort &&rhs) = default;
        OutputPort& operator = (OutputPort const &rhs) = delete;
        ~OutputPort() = default;

        // definition:
        std::string const& GetPortName() const;
        std::string const& GetTypeName() const;

        // instance:
        m1::any_ptr const& GetConnectionPtr() const;

    private:
        // members:
        std::string m_PortName;
        std::string m_TypeName;
        m1::any_ptr m_ConnectionPtr;
    };

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_OUTPUT_HPP
