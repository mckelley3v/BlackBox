#ifndef FLOW_VERIFY_HPP
#define FLOW_VERIFY_HPP

#include <cassert>

// simple macro to test a condition and throw an exception if condition is false
// for debugging convenience an assert is also triggered if the condition is false
#define FLOW_VERIFY(condition, error) do { if(!(condition)) { assert(!#condition); throw error; } } while(false)

#endif // FLOW_VERIFY_HPP
