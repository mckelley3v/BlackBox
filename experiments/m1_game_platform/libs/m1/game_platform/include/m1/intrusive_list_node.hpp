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
        intrusive_list_node() = default;
        intrusive_list_node(intrusive_list_node &&rhs);
        intrusive_list_node& operator = (intrusive_list_node &&rhs);
        ~intrusive_list_node();

        // methods:
        bool unique() const;
        void unlink();
        void link(intrusive_list_node &next);
        void swap(intrusive_list_node &rhs);

    private:
        intrusive_list_node(intrusive_list_node const &rhs) = delete;
        intrusive_list_node& operator = (intrusive_list_node const &rhs) = delete;

        // members:
        intrusive_list_node *m_NextPtr = this;
        intrusive_list_node *m_PrevPtr = this;
    };

    // ----------------------------------------------------------------------------------------------------------------

    void swap(intrusive_list_node &lhs,
              intrusive_list_node &rhs);

    // ================================================================================================================
} // namespace m1

#endif // M1_INTRUSIVE_LIST_NODE_HPP
