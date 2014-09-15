#include "Flow/Component.hpp"

extern bool TestComponent_Add();
extern bool TestComponent_Constant();

bool TestComponent()
{
    bool result = true;
    result &= TestComponent_Add();
    result &= TestComponent_Constant();
    return result;
}
