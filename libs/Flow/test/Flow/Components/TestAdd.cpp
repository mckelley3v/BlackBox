#include "Flow/Components/Add.hpp"
#include "Flow/TypeManager.hpp"
#include <cassert>

bool TestComponent_Add()
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
    assert(GetInputConnectionPtr<float>(add, "Lhs") == &lhs);
    assert(GetInputConnectionPtr<float>(add, "Rhs") == &rhs);
    assert(GetOutputConnectionPtr<float>(add, "Result") == &add.GetResult());
    assert(add.GetResult() == 3.0f);
    return true;
}
