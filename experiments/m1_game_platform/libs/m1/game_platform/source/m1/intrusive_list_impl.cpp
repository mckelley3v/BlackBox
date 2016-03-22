#include "m1/intrusive_list_impl.hpp"
#include <cassert>

// ====================================================================================================================

m1::intrusive_list_impl::intrusive_list_impl(intrusive_list_impl &&rhs) noexcept
    : m_SentinelNode(std::move(rhs.m_SentinelNode))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl& m1::intrusive_list_impl::operator = (intrusive_list_impl &&rhs) noexcept
{
    m_SentinelNode = std::move(rhs.m_SentinelNode);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::~intrusive_list_impl() noexcept
{
    clear();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::intrusive_list_impl::empty() const noexcept
{
    return m_SentinelNode.unique();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::push_front(node_type &node) noexcept
{
    m_SentinelNode.link(node);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::push_back(node_type &node) noexcept
{
    node.link(m_SentinelNode);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::pop_front() noexcept
{
    assert(!empty());

    m_SentinelNode.m_NextPtr->unlink();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::pop_back() noexcept
{
    assert(!empty());

    m_SentinelNode.m_PrevPtr->unlink();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::swap(intrusive_list_impl &rhs) noexcept
{
    m_SentinelNode.swap(rhs.m_SentinelNode);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::clear() noexcept
{
    for(node_type *node_ptr = m_SentinelNode.m_NextPtr; node_ptr != &m_SentinelNode; /*advance in loop*/)
    {
        node_type * const next_ptr = node_ptr->m_NextPtr;
        node_ptr->unlink();
        node_ptr = next_ptr;
    }
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::remove(node_type &value) noexcept
{
    value.unlink();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::reverse() noexcept
{
    for(node_type *node_ptr = m_SentinelNode.m_NextPtr; node_ptr != &m_SentinelNode; /*advance in loop*/)
    {
        node_type * const next_ptr = node_ptr->m_NextPtr;

        // swap node_ptr's prev/next ptrs
        node_ptr->m_NextPtr = node_ptr->m_PrevPtr;
        node_ptr->m_PrevPtr = next_ptr;

        node_ptr = next_ptr;
    }
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type& m1::intrusive_list_impl::sentinel()
{
    return m_SentinelNode;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type const& m1::intrusive_list_impl::get_sentinel() const
{
    return m_SentinelNode;
}

// ====================================================================================================================
