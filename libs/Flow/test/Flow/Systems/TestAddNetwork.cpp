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
            //                             Definition                 MakeInstanceFunc                           MakeInstanceDataFunc
            {          Constant<int>::GetDefinition(),       MakeConstantInstance<int>, std::make_shared<Constant<int>::InstanceData>},
            {               Add<int>::GetDefinition(),   MakeSystemComponent<Add<int>>},
            {   AddNetwork::GetDefinition().Interface, MakeSystemComponent<AddNetwork>},
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
