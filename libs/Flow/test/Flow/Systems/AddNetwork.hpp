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

        AddNetwork() = delete;
        AddNetwork(TypeManager const &type_manager,
                   std::string instance_name,
                   ComponentInputConnectionPtrsDict input_connection_ptrs_dict);
        AddNetwork(AddNetwork &&rhs) = default;
        AddNetwork(AddNetwork const &rhs) = delete;
        AddNetwork& operator = (AddNetwork &&rhs) = default;
        AddNetwork& operator = (AddNetwork const &rhs) = delete;
        ~AddNetwork() = default;

        int const& GetResult() const;

    private:
        // members:
        int const &m_Result;
    };

    // =================================================================================================================
} // namespace Systems
} // namespace Flow

#endif // FLOW_SYSTEMS_ADDNETWORK_HPP
