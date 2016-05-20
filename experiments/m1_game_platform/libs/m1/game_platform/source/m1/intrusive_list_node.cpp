#include "m1/intrusive_list_node.hpp"
#include <cassert>

// ====================================================================================================================

m1::intrusive_list_node::intrusive_list_node(intrusive_list_node &&rhs) noexcept
{
    swap_links(rhs);
    rhs.remove_links();
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node& m1::intrusive_list_node::operator = (intrusive_list_node &&rhs) noexcept
{
    swap_links(rhs);
    rhs.remove_links();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node::~intrusive_list_node() noexcept
{
    if(is_linked())
    {
        remove_links();
    }
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node* m1::intrusive_list_node::next_node_ptr()
{
    return m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node const* m1::intrusive_list_node::get_next_node_ptr()
{
    return m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node* m1::intrusive_list_node::next_prev_ptr()
{
    return m_PrevPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node const* m1::intrusive_list_node::get_prev_node_ptr()
{
    return m_PrevPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::intrusive_list_node::is_linked() const noexcept
{
    assert(((m_PrevPtr != this) && (m_NextPtr != this)) ||
           ((m_PrevPtr == this) && (m_NextPtr == this)));
    return m_NextPtr != this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::add_link(intrusive_list_node &next) noexcept
{
    assert(!is_linked());

    m_NextPtr = &next;
    m_PrevPtr = next.m_PrevPtr;
    next.m_PrevPtr->m_NextPtr = this;
    next.m_PrevPtr = this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::swap_links(intrusive_list_node &rhs) noexcept
{
    {
        intrusive_list_node * const p = m_NextPtr;
        m_PrevPtr->m_NextPtr = &rhs;
        p->m_PrevPtr = &rhs;
    }
    {
        intrusive_list_node * const p = rhs.m_NextPtr;
        rhs.m_PrevPtr->m_NextPtr = this;
        p->m_PrevPtr = this;
    }
    {
        intrusive_list_node * const p = m_PrevPtr;
        m_PrevPtr = rhs.m_PrevPtr;
        rhs.m_PrevPtr = p;
    }
    {
        intrusive_list_node * const p = m_NextPtr;
        m_NextPtr = rhs.m_NextPtr;
        rhs.m_NextPtr = p;
    }
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::remove_links() noexcept
{
    assert(is_linked());

    m_PrevPtr->m_NextPtr = m_NextPtr;
    m_NextPtr->m_PrevPtr = m_PrevPtr;

    m_NextPtr = this;
    m_PrevPtr = this;
}

// ====================================================================================================================

void m1::swap(intrusive_list_node &lhs,
              intrusive_list_node &rhs) noexcept
{
   lhs.swap_links(rhs);
}

// ====================================================================================================================
