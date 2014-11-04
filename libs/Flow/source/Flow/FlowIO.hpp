#ifndef FLOWIO_HPP
#define FLOWIO_HPP

#include "FlowIO_generated.h"
#include <vector>
#include <string>

// =====================================================================================================================

#define FLOWIO_GET_PTR_MEMBER(obj_ptr, member) (obj_ptr ? (obj_ptr->member) : nullptr)
#define FLOWIO_GET_INT8_MEMBER(obj_ptr, member) (obj_ptr ? (obj_ptr->member) : std::int8_t(0))
#define FLOWIO_GET_STR_MEMBER(obj_ptr, member) Flow::IO::get_str(obj_ptr ? (obj_ptr->member) : nullptr)
#define FLOWIO_GET_C_STR_MEMBER(obj_ptr, member) Flow::IO::get_c_str(obj_ptr ? (obj_ptr->member) : nullptr)
#define FLOWIO_GET_BOOL_MEMBER(obj_ptr, member) (obj_ptr ? static_cast<bool>(obj_ptr->member) : false)

// =====================================================================================================================

namespace Flow
{
namespace IO
{
    // =================================================================================================================

    char const* get_c_str(flatbuffers::String const * const str_ptr);
    char const* get_c_str(char const * const c_str);

    // =================================================================================================================

    std::string get_str(flatbuffers::String const * const str_ptr);

    // =================================================================================================================

    template <typename T> std::vector<T> get_vector(flatbuffers::Vector<flatbuffers::Offset<T>> const * const fb_vector_ptr);
    template <typename T1, typename T2> std::vector<T1> get_vector(flatbuffers::Vector<flatbuffers::Offset<T2>> const * const fb_vector_ptr);

    // =================================================================================================================

} // namespace IO
} // namespace Flow

// =====================================================================================================================
// =====================================================================================================================

template <typename T> std::vector<T> Flow::IO::get_vector(flatbuffers::Vector<flatbuffers::Offset<T>> const * const fb_vector_ptr)
{
    std::vector<T> result;
    if(fb_vector_ptr == nullptr) return result;

    result.assign(fb_vector_ptr->begin(),
                  fb_vector_ptr->end());

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T1, typename T2> std::vector<T1> Flow::IO::get_vector(flatbuffers::Vector<flatbuffers::Offset<T2>> const * const fb_vector_ptr)
{
    std::vector<T1> result;
    if(fb_vector_ptr == nullptr) return result;

    result.reserve(fb_vector_ptr->Length());
    for(T2 const * const fb_entry_ptr : *fb_vector_ptr)
    {
        result.push_back(T1(fb_entry_ptr));
    }

    return result;
}

// =====================================================================================================================

#endif // FLOWIO_HPP
