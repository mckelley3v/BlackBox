#ifndef M1_DICTIONARY_HPP
#define M1_DICTIONARY_HPP

#include "m1/c_str_less.hpp"
#include "m1/string_less.hpp"
#include <string>
#include <map>

namespace m1
{
    // =================================================================================================================

    template <typename T,
              typename Allocator = std::allocator<std::pair<char const * const, T>>>
    using c_str_dictionary = std::map<char const *,
                                      T,
                                      m1::c_str_less,
                                      Allocator>;

    // =================================================================================================================

    template <typename T,
              typename Allocator = std::allocator<std::pair<std::string const, T>>>
    using dictionary = std::map<std::string,
                                T,
                                m1::string_less,
                                Allocator>;

    // =================================================================================================================
} // namespace m1

#endif // M1_DICTIONARY_HPP
