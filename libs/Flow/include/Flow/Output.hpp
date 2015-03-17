#ifndef FLOW_OUTPUT_HPP
#define FLOW_OUTPUT_HPP

// =====================================================================================================================
// Flow::OutputPort
// - Simple class that acts as an output port for a Flow::Component
// - Contains a type-safe pointer to values provided by Flow::Component and updated via Component::Process
// =====================================================================================================================

#include "m1/any_ptr.hpp"
#include <string>

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

    struct OutputPortDefinition
    {
        // members:
        std::string PortName;
        std::string TypeName;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, OutputPortDefinition &value);
    bool read_value(m1::iarchive_ubjson &in, OutputPortDefinition &value);

    // =================================================================================================================

    struct OutputPortInstance
    {
        // members:
        m1::any_ptr ConnectionPtr;
    };

    // =================================================================================================================

    class OutputPort
    {
    public:
        OutputPort(OutputPortDefinition definition,
                   OutputPortInstance instance);
        OutputPort(OutputPort &&rhs) = default;
        OutputPort& operator = (OutputPort &&rhs) = default;
        ~OutputPort() = default;

        // definition:
        std::string const& GetPortName() const;
        std::string const& GetTypeName() const;

        // instance:
        m1::any_ptr const& GetConnectionPtr() const;

    private:
        OutputPort() = delete;
        OutputPort(OutputPort const &rhs) = delete;
        OutputPort& operator = (OutputPort const &rhs) = delete;

        // members:
        std::string m_PortName;
        std::string m_TypeName;
        m1::any_ptr m_ConnectionPtr;
    };

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_OUTPUT_HPP
