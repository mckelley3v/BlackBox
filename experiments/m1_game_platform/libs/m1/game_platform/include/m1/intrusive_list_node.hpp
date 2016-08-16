#ifndef M1_INTRUSIVE_LIST_NODE_HPP
#define M1_INTRUSIVE_LIST_NODE_HPP

#include <type_traits>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    class intrusive_list_node
    {
    friend class intrusive_list_impl;
    public:
        // construct/move/destroy:
        intrusive_list_node() noexcept = default;
        intrusive_list_node(intrusive_list_node &&rhs) noexcept;
        intrusive_list_node& operator = (intrusive_list_node &&rhs) noexcept;
        ~intrusive_list_node() noexcept;

        // properties:
        intrusive_list_node* next_node_ptr() noexcept;
        intrusive_list_node const* get_next_node_ptr() const noexcept;
        intrusive_list_node* prev_node_ptr() noexcept;
        intrusive_list_node const* get_prev_node_ptr() const noexcept;

        // methods:
        bool is_linked() const noexcept;
        void insert_link(intrusive_list_node &next) noexcept;
        void splice_link_range(intrusive_list_node &next,
                               intrusive_list_node &end) noexcept;
        void swap_links(intrusive_list_node &rhs) noexcept;
        void clear_links() noexcept;

    private:
        intrusive_list_node(intrusive_list_node const &rhs) = delete;
        intrusive_list_node& operator = (intrusive_list_node const &rhs) = delete;

        // members:
        intrusive_list_node *m_NextPtr = this;
        intrusive_list_node *m_PrevPtr = this;
    };

    // ----------------------------------------------------------------------------------------------------------------

    void swap(intrusive_list_node &lhs,
              intrusive_list_node &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

#endif // M1_INTRUSIVE_LIST_NODE_HPP
