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

void m1::intrusive_list_node::insert_link(intrusive_list_node &prev) noexcept
{
    assert(!prev.is_linked());

    m_PrevPtr->m_NextPtr = &prev;
    prev.m_PrevPtr = m_PrevPtr;
    prev.m_NextPtr = this;
    m_PrevPtr = &prev;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::splice_link_range(intrusive_list_node &prev_begin,
                                                intrusive_list_node &prev_end) noexcept
{
    intrusive_list_node * const this_prev = m_PrevPtr;
    intrusive_list_node * const prev_head = prev_begin.m_PrevPtr;
    intrusive_list_node * const prev_back = prev_end.m_PrevPtr;

    this_prev->m_NextPtr = &prev_begin;
    prev_begin.m_PrevPtr = this_prev;
    prev_back->m_NextPtr = this;
    m_PrevPtr = prev_back;

    prev_head->m_NextPtr = &prev_end;
    prev_end.m_PrevPtr = prev_head;
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
