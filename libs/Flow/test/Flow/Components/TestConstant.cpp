#include "Flow/Components/Constant.hpp"
#include "Flow/TypeManager.hpp"
#include "catch.hpp"

TEST_CASE("Test m1::Components::Constant", "[Flow]")
{
    using namespace Flow;
    using namespace Flow::Components;

    TypeManager const type_manager
    {{
        // ComponentTypes
        {
            //                     Definition  MakeInstanceFunc
            {Constant<float>::GetDefinition(),          nullptr},
        },
        // ConnectionTypes
        {
            // Name  BaseNames
            { "bool",       {}},
            {  "int",       {}},
            { "float",      {}},
        },
    }};

    Constant<float> const_one(type_manager, "one", {}, 1.0f);
    CHECK(GetOutputConnectionPtr<float>(const_one, "Value") == &const_one.GetValue());
    CHECK(const_one.GetValue() == 1.0f);
}
