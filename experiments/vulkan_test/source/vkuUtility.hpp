#ifndef VKU_UTILITY_HPP
#define VKU_UTILITY_HPP

#include <algorithm>
#include <string>
#include <initializer_list>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    std::size_t string_length(char const *str);
    std::size_t string_length(std::string const &str);

    template <typename String,
              typename ...Strings>
    std::size_t string_length(String const &str0, Strings const &...strN);

    // ================================================================================================================

    template <typename String>
    void append_string(std::string &result, String const &str);

    template <typename String,
              typename ...Strings>
    void append_string(std::string &result, String const &str0, Strings const &...strN);

    // ================================================================================================================

    template <typename ...Strings>
    std::string make_string(Strings const &...strs);

    // ================================================================================================================

    template <typename Itr,
              typename End,
              typename T>
    bool contains(Itr itr, End end, T const &value);

    // ================================================================================================================

    template <typename Itr,
              typename End,
              typename Pred>
    bool contains_if(Itr itr, End end, Pred pred);

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

template <typename String,
          typename ...Strings>
std::size_t vku::string_length(String const &str, Strings const &...strs)
{
    return string_length(str) + string_length(strs...);
}

// ================================================================================================================

template <typename String>
void vku::append_string(std::string &result, String const &str)
{
    result += str;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename String,
          typename ...Strings>
void vku::append_string(std::string &result, String const &str0, Strings const &...strN)
{
    append_string(result, str0);
    append_string(result, strN...);
}

// ====================================================================================================================

template <typename ...Strings>
std::string vku::make_string(Strings const &...strs)
{
    std::string result;
    result.reserve(string_length(strs...));
    append_string(result, strs...);
    return result;
}

// ====================================================================================================================

template <typename Itr,
          typename End,
          typename T>
/*static*/ bool vku::contains(Itr itr, End end, T const &value)
{
    return std::find(itr, end, value) != end;
}

// ====================================================================================================================

template <typename Itr,
          typename End,
          typename Pred>
/*static*/ bool vku::contains_if(Itr itr, End end, Pred pred)
{
    return std::find_if(itr, end, pred) != end;
}

// ====================================================================================================================

#endif // VKU_UTILITY_HPP
