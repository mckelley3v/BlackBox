#include "Flow/Systems/AddNetwork.hpp"
#include "Flow/Components/Add.hpp"
#include "Flow/Components/Constant.hpp"
#include "Flow/TypeManager.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::Systems::AddNetwork", "[Flow]")
{
    using namespace Flow;
    using namespace Flow::Components;
    using namespace Flow::Systems;

    TypeManager const type_manager
    {{
        // ComponentTypes
        {
            Constant<int>::GetComponentTypeEntry(),
            Add<int>::GetComponentTypeEntry(),
            AddNetwork::GetComponentTypeEntry(),
        },
        // ConnectionTypes
        {
            // Name    BaseNames
            {  "bool",        {}},
            {   "int",        {}},
            { "float",        {}},
        },
    }};

    Systems::AddNetwork add_network(type_manager, "add_network", {});
    add_network.Process();
    CHECK(add_network.GetResult() == 7);
}
