#include "m1/intrusive_list_impl.hpp"
#include <cassert>

// ====================================================================================================================

m1::intrusive_list_impl::~intrusive_list_impl() noexcept
{
    clear();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::intrusive_list_impl::empty() const noexcept
{
    return !m_SentinelNode.is_linked();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::push_front(node_type &node) noexcept
{
    m_SentinelNode.add_link(node);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::push_back(node_type &node) noexcept
{
    node.add_link(m_SentinelNode);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::pop_front() noexcept
{
    assert(!empty());

    m_SentinelNode.m_NextPtr->remove_links();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::pop_back() noexcept
{
    assert(!empty());

    m_SentinelNode.m_PrevPtr->remove_links();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::swap(intrusive_list_impl &rhs) noexcept
{
    m_SentinelNode.swap_links(rhs.m_SentinelNode);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::clear() noexcept
{
    while(!empty())
    {
        pop_back();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::remove(node_type &node) noexcept
{
    node.remove_links();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::reverse() noexcept
{
    for(node_type *node_ptr = m_SentinelNode.m_NextPtr; node_ptr != &m_SentinelNode; /*increment in loop*/)
    {
        node_type * const next_ptr = node_ptr->m_NextPtr;

        // swap node_ptr's prev/next ptrs
        node_ptr->m_NextPtr = node_ptr->m_PrevPtr;
        node_ptr->m_PrevPtr = next_ptr;

        node_ptr = next_ptr;
    }
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type* m1::intrusive_list_impl::begin_node_ptr()
{
    assert(!empty());
    return m_SentinelNode.m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type const* m1::intrusive_list_impl::get_begin_node_ptr() const
{
    assert(!empty());
    return m_SentinelNode.m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type* m1::intrusive_list_impl::end_node_ptr()
{
    return &m_SentinelNode;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type const* m1::intrusive_list_impl::get_end_node_ptr() const
{
    return &m_SentinelNode;
}

// ====================================================================================================================

void m1::swap(intrusive_list_impl &lhs,
              intrusive_list_impl &rhs) noexcept
{
    lhs.swap(rhs);
}

// ====================================================================================================================
