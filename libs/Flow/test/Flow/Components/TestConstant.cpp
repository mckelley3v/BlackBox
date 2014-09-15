#include "Flow/Components/Constant.hpp"
#include "Flow/TypeManager.hpp"
#include <cassert>

bool TestComponent_Constant()
{
    using namespace Flow;
    using namespace Flow::Components;

    ComponentDefinition const c0_definition = {
        // Name
        "Constant<float>{0}",
        Constant<float>::Definition.InputPorts,
        Constant<float>::Definition.OutputPorts,
        Constant<float>::Definition.Annotations,
    };

    TypeManager const type_manager
    {{
        // ComponentTypes
        {
            //                Definition                   MakeInstanceFunc
            {Constant<float>::Definition,                           nullptr},
            {              c0_definition, GetMakeConstantInstanceFunc(1.0f)}, // TODO - handle parameters
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
