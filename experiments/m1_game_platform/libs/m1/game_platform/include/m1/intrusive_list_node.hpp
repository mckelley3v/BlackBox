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
        intrusive_list_node* next_node_ptr();
        intrusive_list_node const* get_next_node_ptr();
        intrusive_list_node* next_prev_ptr();
        intrusive_list_node const* get_prev_node_ptr();

        // methods:
        bool is_linked() const noexcept;
        void add_link(intrusive_list_node &next) noexcept;
        void swap_links(intrusive_list_node &rhs) noexcept;
        void remove_links() noexcept;

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
