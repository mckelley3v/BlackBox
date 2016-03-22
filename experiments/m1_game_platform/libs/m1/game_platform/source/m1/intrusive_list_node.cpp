#include "m1/intrusive_list_node.hpp"
#include <cassert>

// ====================================================================================================================

m1::intrusive_list_node::intrusive_list_node(intrusive_list_node &&rhs)
{
    swap(rhs);
    rhs.unlink();
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node& m1::intrusive_list_node::operator = (intrusive_list_node &&rhs)
{
    swap(rhs);
    rhs.unlink();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node::~intrusive_list_node()
{
    if(!unique())
    {
        unlink();
    }
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::intrusive_list_node::unique() const
{
    assert(((m_PrevPtr != this) && (m_NextPtr != this)) ||
           ((m_PrevPtr == this) && (m_NextPtr == this)));
    return m_NextPtr == this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::unlink()
{
    assert(!unique());

    m_PrevPtr->m_NextPtr = m_NextPtr;
    m_NextPtr->m_PrevPtr = m_PrevPtr;

    m_NextPtr = this;
    m_PrevPtr = this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::link(intrusive_list_node &next)
{
    assert(unique());
    assert(next.unique());

    m_NextPtr = &next;
    m_PrevPtr = next.m_PrevPtr;
    next.m_PrevPtr->m_NextPtr = this;
    next.m_PrevPtr = this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_node::swap(intrusive_list_node &rhs)
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

// ====================================================================================================================

void m1::swap(intrusive_list_node &lhs,
              intrusive_list_node &rhs)
{
   lhs.swap(rhs);
}

// ====================================================================================================================
