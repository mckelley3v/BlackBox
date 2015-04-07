#ifndef FLOW_SYSTEMS_ADDNETWORK_HPP
#define FLOW_SYSTEMS_ADDNETWORK_HPP

#include "Flow/System.hpp"

namespace Flow
{
namespace Systems
{
    // =================================================================================================================

    class AddNetwork
        : public System
    {
    public:
        static SystemDefinition GetDefinition();

        AddNetwork(TypeManager const &type_manager,
                   std::string instance_name,
                   ComponentInputConnectionPtrsDict input_connection_ptrs_dict);
        AddNetwork(AddNetwork &&rhs) = default;
        AddNetwork& operator = (AddNetwork &&rhs) = default;
        ~AddNetwork() = default;

        int const& GetResult() const;

    private:
        AddNetwork() = delete;
        AddNetwork(AddNetwork const &rhs) = delete;
        AddNetwork& operator = (AddNetwork const &rhs) = delete;

        // members:
        int const &m_Result;
    };

    // =================================================================================================================
} // namespace Systems
} // namespace Flow

#endif // FLOW_SYSTEMS_ADDNETWORK_HPP
