#ifndef FLOW_INPUT_HPP
#define FLOW_INPUT_HPP

// =====================================================================================================================
// Flow::InputPort
// - Simple class that acts as an input port for a Flow::Component
// - Contains one or more type-safe pointers to values provided by another Flow::Component's output port
// =====================================================================================================================

#include "m1/any_ptr.hpp"
#include <vector>
#include <string>

namespace Flow
{
namespace IO
{
    // =================================================================================================================

    struct InputPortDefinition;

    // =================================================================================================================
} // namespace IO
} // namespace Flow

namespace Flow
{
    // =================================================================================================================

    enum class InputPortOptional : bool
    {
        No = false,
        Yes = true,
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class InputPortMultiplex : bool
    {
        No = false,
        Yes = true,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct InputPortDefinitionInitializer
    {
        char const *PortName;
        char const *TypeName;
        InputPortOptional IsOptional;
        InputPortMultiplex IsMultiplex;
    };

    // =================================================================================================================

    class InputPortDefinition
    {
    public:
        InputPortDefinition() = delete;
        explicit InputPortDefinition(InputPortDefinitionInitializer definition_initializer);
        explicit InputPortDefinition(IO::InputPortDefinition const * const definition_io_ptr);
        InputPortDefinition(InputPortDefinition &&rhs) = default;
        InputPortDefinition(InputPortDefinition const &rhs) = default;
        InputPortDefinition& operator = (InputPortDefinition &&rhs) = default;
        InputPortDefinition& operator = (InputPortDefinition const &rhs) = default;
        ~InputPortDefinition() = default;

        // members:
        std::string PortName;
        std::string TypeName;
        InputPortOptional IsOptional;
        InputPortMultiplex IsMultiplex;
    };

    // =================================================================================================================

    class InputPortInstance
    {
    public:
        InputPortInstance() = delete;
        InputPortInstance(InputPortInstance &&rhs) = default;
        InputPortInstance(InputPortInstance const &rhs) = default;
        InputPortInstance& operator = (InputPortInstance &&rhs) = default;
        InputPortInstance& operator = (InputPortInstance const &rhs) = default;
        ~InputPortInstance() = default;

        // members:
        std::vector<m1::const_any_ptr> ConnectionPtrs;
    };

    // =================================================================================================================

    class InputPort
    {
    public:
        InputPort() = delete;
        InputPort(InputPortDefinition definition,
                  InputPortInstance instance);
        InputPort(InputPort &&rhs) = default;
        InputPort(InputPort const &rhs) = delete;
        InputPort& operator = (InputPort &&rhs) = default;
        InputPort& operator = (InputPort const &rhs) = delete;
        ~InputPort() = default;

        // definition:
        std::string const& GetPortName() const;
        std::string const& GetTypeName() const;
        bool IsOptional() const;
        bool IsMultiplex() const;

        // instance:
        std::vector<m1::const_any_ptr> const& GetConnectionPtrs() const;

    private:
        // members:
        std::string m_PortName;
        std::string m_TypeName;
        bool m_IsOptional;
        bool m_IsMultiplex;
        std::vector<m1::const_any_ptr> m_ConnectionPtrs;
    };

    // =================================================================================================================
} // namespace Flow

#endif // FLOW_INPUT_HPP
