#ifndef M1_INTRUSIVE_LIST_IMPL_HPP
#define M1_INTRUSIVE_LIST_IMPL_HPP

#include "m1/intrusive_list_node.hpp"
#include <cstddef>

#ifdef _MSC_VER
#define noexcept
#define constexpr /*inline*/
#endif

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    class intrusive_list_impl
    {
    public:
        // types:
        typedef intrusive_list_node node_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        // construct/move/copy/destroy:
        intrusive_list_impl() noexcept = default;
        intrusive_list_impl(intrusive_list_impl &&rhs) noexcept /*= default*/;
        intrusive_list_impl& operator = (intrusive_list_impl &&rhs) noexcept /*= default*/;
        ~intrusive_list_impl() noexcept;

        // capacity:
        bool empty() const noexcept;

        // modifiers:
        void push_front(node_type &node) noexcept;
        void push_back(node_type &node) noexcept;
        void pop_front() noexcept;
        void pop_back() noexcept;

        void swap(intrusive_list_impl &rhs) noexcept;
        void clear() noexcept;

        // list operations:
        void remove(node_type &value) noexcept;
        void reverse() noexcept;

    protected:
        node_type& sentinel();
        node_type const& get_sentinel() const;

    private:
        intrusive_list_impl(intrusive_list_impl const &rhs) = delete;
        intrusive_list_impl& operator = (intrusive_list_impl const &rhs) = delete;

        // members:
        node_type m_SentinelNode {};
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_INTRUSIVE_LIST_IMPL_HPP
