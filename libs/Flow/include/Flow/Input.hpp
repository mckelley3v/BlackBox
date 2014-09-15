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

    struct InputPortDefinition
    {
        char const *PortName;
        char const *TypeName;
        InputPortOptional IsOptional;
        InputPortMultiplex IsMultiplex;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct InputPortInstance
    {
        std::vector<m1::const_any_ptr> ConnectionPtrs;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class InputPort
    {
    public:
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
