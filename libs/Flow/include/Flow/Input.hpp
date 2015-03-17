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

    enum class InputPortOptional : bool
    {
        No = false,
        Yes = true,
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, InputPortOptional &value);
    bool read_value(m1::iarchive_ubjson &in, InputPortOptional &value);

    // =================================================================================================================

    enum class InputPortMultiplex : bool
    {
        No = false,
        Yes = true,
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, InputPortMultiplex &value);
    bool read_value(m1::iarchive_ubjson &in, InputPortMultiplex &value);

    // =================================================================================================================

    struct InputPortDefinition
    {
        // members:
        std::string PortName;
        std::string TypeName;
        InputPortOptional IsOptional;
        InputPortMultiplex IsMultiplex;
    };

    // -----------------------------------------------------------------------------------------------------------------

    bool read_value(m1::iarchive_json &in, InputPortDefinition &value);
    bool read_value(m1::iarchive_ubjson &in, InputPortDefinition &value);

    // =================================================================================================================

    struct InputPortInstance
    {
        // members:
        std::vector<m1::const_any_ptr> ConnectionPtrs;
    };

    // =================================================================================================================

    class InputPort
    {
    public:
        InputPort(InputPortDefinition definition,
                  InputPortInstance instance);
        InputPort(InputPort &&rhs) = default;
        InputPort& operator = (InputPort &&rhs) = default;
        ~InputPort() = default;

        // definition:
        std::string const& GetPortName() const;
        std::string const& GetTypeName() const;
        bool IsOptional() const;
        bool IsMultiplex() const;

        // instance:
        std::vector<m1::const_any_ptr> const& GetConnectionPtrs() const;

    private:
        InputPort() = delete;
        InputPort(InputPort const &rhs) = delete;
        InputPort& operator = (InputPort const &rhs) = delete;

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
