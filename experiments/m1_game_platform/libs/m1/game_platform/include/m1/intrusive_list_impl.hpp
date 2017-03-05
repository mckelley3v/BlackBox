#ifndef M1_INTRUSIVE_LIST_IMPL_HPP
#define M1_INTRUSIVE_LIST_IMPL_HPP

#include "m1/intrusive_list_node.hpp"
#include <cstddef>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    class intrusive_list_impl;

    void swap(intrusive_list_impl &lhs,
              intrusive_list_impl &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    class intrusive_list_iterator_impl;

    void swap(intrusive_list_iterator_impl &lhs,
              intrusive_list_iterator_impl &rhs) noexcept;

    bool operator == (intrusive_list_iterator_impl const &lhs,
                      intrusive_list_iterator_impl const &rhs) noexcept;

    bool operator != (intrusive_list_iterator_impl const &lhs,
                      intrusive_list_iterator_impl const &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    class intrusive_list_const_iterator_impl;

    void swap(intrusive_list_const_iterator_impl &lhs,
              intrusive_list_const_iterator_impl &rhs) noexcept;

    bool operator == (intrusive_list_const_iterator_impl const &lhs,
                      intrusive_list_const_iterator_impl const &rhs) noexcept;

    bool operator != (intrusive_list_const_iterator_impl const &lhs,
                      intrusive_list_const_iterator_impl const &rhs) noexcept;

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
        intrusive_list_impl(intrusive_list_impl &&rhs) noexcept = default;
        intrusive_list_impl& operator = (intrusive_list_impl &&rhs) noexcept = default;
        ~intrusive_list_impl() noexcept;

        // capacity:
        bool empty() const noexcept;

        // modifiers:
        void push_front(node_type &node) noexcept;
        void push_back(node_type &node) noexcept;
        void pop_front() noexcept;
        void pop_back() noexcept;

        void insert(node_type &at, node_type &node) noexcept;

        void swap(intrusive_list_impl &rhs) noexcept;
        void clear() noexcept;

        // list operations:
        void remove(node_type &node) noexcept;
        void reverse() noexcept;

    protected:
        node_type* begin_node_ptr();
        node_type const* get_begin_node_ptr() const;

        node_type* end_node_ptr();
        node_type const* get_end_node_ptr() const;

    private:
        intrusive_list_impl(intrusive_list_impl const &rhs) = delete;
        intrusive_list_impl& operator = (intrusive_list_impl const &rhs) = delete;

        // members:
        node_type m_SentinelNode {};
    };

    // ================================================================================================================

    class intrusive_list_iterator_impl
    {
    public:
        intrusive_list_iterator_impl(intrusive_list_iterator_impl &&rhs) noexcept = default;
        intrusive_list_iterator_impl(intrusive_list_iterator_impl const &rhs) noexcept = default;
        intrusive_list_iterator_impl& operator = (intrusive_list_iterator_impl &&rhs) noexcept = default;
        intrusive_list_iterator_impl& operator = (intrusive_list_iterator_impl const &rhs) noexcept = default;
        ~intrusive_list_iterator_impl() noexcept = default;

        intrusive_list_iterator_impl& operator ++ ();
        intrusive_list_iterator_impl operator ++ (int);

        intrusive_list_iterator_impl& operator -- ();
        intrusive_list_iterator_impl operator -- (int);

        intrusive_list_node* node_ptr() const;
        intrusive_list_node const* get_node_ptr() const;

        friend void swap(intrusive_list_iterator_impl &lhs,
                         intrusive_list_iterator_impl &rhs) noexcept;

        friend bool operator == (intrusive_list_iterator_impl const &lhs,
                                 intrusive_list_iterator_impl const &rhs) noexcept;

        friend bool operator != (intrusive_list_iterator_impl const &lhs,
                                 intrusive_list_iterator_impl const &rhs) noexcept;

    protected:
        explicit intrusive_list_iterator_impl(intrusive_list_node *node_ptr);

    private:
        friend class intrusive_list_impl;
        friend class intrusive_list_const_iterator_impl;
        intrusive_list_iterator_impl() noexcept = delete;

        // members:
        intrusive_list_node *m_NodePtr = nullptr;
    };

    // ================================================================================================================

    class intrusive_list_const_iterator_impl
    {
    public:
        intrusive_list_const_iterator_impl(intrusive_list_iterator_impl &&rhs) noexcept;
        intrusive_list_const_iterator_impl(intrusive_list_const_iterator_impl &&rhs) noexcept = default;
        intrusive_list_const_iterator_impl(intrusive_list_iterator_impl const &rhs) noexcept;
        intrusive_list_const_iterator_impl(intrusive_list_const_iterator_impl const &rhs) noexcept = default;
        intrusive_list_const_iterator_impl& operator = (intrusive_list_iterator_impl &&rhs) noexcept;
        intrusive_list_const_iterator_impl& operator = (intrusive_list_const_iterator_impl &&rhs) noexcept = default;
        intrusive_list_const_iterator_impl& operator = (intrusive_list_iterator_impl const &rhs) noexcept;
        intrusive_list_const_iterator_impl& operator = (intrusive_list_const_iterator_impl const &rhs) noexcept = default;
        ~intrusive_list_const_iterator_impl() noexcept = default;

        intrusive_list_const_iterator_impl& operator ++ ();
        intrusive_list_const_iterator_impl operator ++ (int);

        intrusive_list_const_iterator_impl& operator -- ();
        intrusive_list_const_iterator_impl operator -- (int);

        intrusive_list_node const* get_node_ptr() const;

        friend void swap(intrusive_list_const_iterator_impl &lhs,
                         intrusive_list_const_iterator_impl &rhs) noexcept;

        friend bool operator == (intrusive_list_const_iterator_impl const &lhs,
                                 intrusive_list_const_iterator_impl const &rhs) noexcept;

        friend bool operator != (intrusive_list_const_iterator_impl const &lhs,
                                 intrusive_list_const_iterator_impl const &rhs) noexcept;

    protected:
        explicit intrusive_list_const_iterator_impl(intrusive_list_node const *node_ptr);

    private:
        friend class intrusive_list_impl;
        intrusive_list_const_iterator_impl() noexcept = delete;

        // members:
        intrusive_list_node const *m_NodePtr = nullptr;
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

#endif // M1_INTRUSIVE_LIST_IMPL_HPP
