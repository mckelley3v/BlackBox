#ifndef VKU_UTILITY_HPP
#define VKU_UTILITY_HPP

#include <algorithm>
#include <string>
#include <initializer_list>

// ====================================================================================================================

namespace vku
{
    // ================================================================================================================

    class c_str_compare_to
    {
    public:
        explicit c_str_compare_to(char const *lhs);

        bool operator() (char const *rhs) const;

    private:
        // members:
        char const * const m_Lhs = nullptr;
    };

    // ================================================================================================================

    class name_compare_to
    {
    public:
        explicit name_compare_to(char const *lhs);

        bool operator() (char const *rhs) const;

    private:
        // members:
        char const * const m_Lhs = nullptr;
    };

    // ================================================================================================================

    bool c_str_equal(char const *lhs, char const *rhs);

    // ================================================================================================================

    std::string make_string(std::initializer_list<char const*> c_strs);

    // ================================================================================================================

    template <typename Itr,
              typename End,
              typename Pred>
    bool contains(Itr itr, End end, Pred pred);

    // ================================================================================================================
} // namespace vku

// ====================================================================================================================

// ====================================================================================================================

template <typename Itr,
          typename End,
          typename Pred>
/*static*/ bool vku::contains(Itr itr, End end, Pred pred)
{
    return std::find_if(itr, end, pred) != end;
}

// ====================================================================================================================

#endif // VKU_UTILITY_HPP
