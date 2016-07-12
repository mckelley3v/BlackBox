#include "m1/intrusive_list_node.hpp"
#include <cassert>

// ====================================================================================================================

m1::intrusive_list_node::intrusive_list_node(intrusive_list_node &&rhs) noexcept
{
    swap_links(rhs);
    rhs.clear_links();
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node& m1::intrusive_list_node::operator = (intrusive_list_node &&rhs) noexcept
{
    swap_links(rhs);
    rhs.clear_links();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node::~intrusive_list_node() noexcept
{
    clear_links();
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node* m1::intrusive_list_node::next_node_ptr() noexcept
{
    return m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node const* m1::intrusive_list_node::get_next_node_ptr() const noexcept
{
    return m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node* m1::intrusive_list_node::prev_node_ptr() noexcept
{
    return m_PrevPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node const* m1::intrusive_list_node::get_prev_node_ptr() const noexcept
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

void m1::intrusive_list_node::insert_link(intrusive_list_node &next) noexcept
{
    m_NextPtr = &next;
    m_PrevPtr = next.m_PrevPtr;
    next.m_PrevPtr->m_NextPtr = this;
    next.m_PrevPtr = this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::splice_link_range(intrusive_list_node &next,
                                                intrusive_list_node &end) noexcept
{
    intrusive_list_node * const n = m_NextPtr;
    intrusive_list_node * const p = next.m_PrevPtr;
    intrusive_list_node * const e = end.m_PrevPtr;

    p->m_NextPtr = &end;
    end.m_PrevPtr = p;

    m_NextPtr = &next;
    next.m_PrevPtr = this;

    e->m_NextPtr = n;
    n->m_PrevPtr = e;

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

void m1::intrusive_list_node::clear_links() noexcept
{
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
