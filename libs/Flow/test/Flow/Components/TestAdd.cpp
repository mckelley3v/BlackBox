#include "Flow/Components/Add.hpp"
#include "Flow/TypeManager.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::Components::Add", "[Flow]")
{
    using namespace Flow;
    using namespace Flow::Components;

    TypeManager const type_manager
    {{
        // ComponentTypes
        {
            //                  Definition                 MakeInstanceFunc
            {  Add<float>::GetDefinition(), MakeSystemComponent<Add<float>>},
        },
        // ConnectionTypes
        {
            // Name  BaseNames
            { "bool",       {}},
            {  "int",       {}},
            { "float",      {}},
        },
    }};

    float const lhs = 1.0f;
    float const rhs = 2.0f;
    Add<float> add(type_manager,
                   "add",
                   {{"Lhs", {&lhs}},
                    {"Rhs", {&rhs}}});

    add.Process();
    CHECK(GetInputConnectionPtr<float>(add, "Lhs") == &lhs);
    CHECK(GetInputConnectionPtr<float>(add, "Rhs") == &rhs);
    CHECK(GetOutputConnectionPtr<float>(add, "Result") == &add.GetResult());
    CHECK(add.GetResult() == 3.0f);
}
