#include "Flow/FlowIO.hpp"

// =====================================================================================================================

/*static*/ char const* Flow::IO::get_c_str(flatbuffers::String const * const str_ptr)
{
    return get_c_str(str_ptr ? str_ptr->c_str() : nullptr);
}

// ---------------------------------------------------------------------------------------------------------------------

/*static*/ char const* Flow::IO::get_c_str(char const * const c_str)
{
    return c_str ? c_str : "";
}

// =====================================================================================================================

std::string Flow::IO::get_str(flatbuffers::String const * const str_ptr)
{
    return str_ptr ? std::string(str_ptr->begin(), str_ptr->end()) : std::string();
}

// =====================================================================================================================
