#include "Flow/System.hpp"

extern bool TestSystem_AddNetwork();

bool TestSystem()
{
    bool result = true;
    result &= TestSystem_AddNetwork();
    return result;
}
