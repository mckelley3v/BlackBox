#include "Flow/Components/Constant.hpp"
#include "Flow/TypeManager.hpp"
#include <cassert>

bool TestComponent_Constant()
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
    assert(GetOutputConnectionPtr<float>(const_one, "Value") == &const_one.GetValue());
    assert(const_one.GetValue() == 1.0f);
    return true;
}
