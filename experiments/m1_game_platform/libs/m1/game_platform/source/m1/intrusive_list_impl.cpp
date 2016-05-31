#include "m1/intrusive_list_impl.hpp"
#include <utility>
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
    m_SentinelNode.link_next(node);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::push_back(node_type &node) noexcept
{
    node.link_next(m_SentinelNode);
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::pop_front() noexcept
{
    assert(!empty());

    begin_node_ptr()->clear_links();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::pop_back() noexcept
{
    assert(!empty());

    end_node_ptr()->m_PrevPtr->clear_links();
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
    node.clear_links();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::intrusive_list_impl::reverse() noexcept
{
    for(node_type *node_ptr = begin_node_ptr(); node_ptr != end_node_ptr(); /*increment in loop*/)
    {
        node_type * const next_ptr = node_ptr->m_NextPtr;

        std::swap(node_ptr->m_PrevPtr, node_ptr->m_NextPtr);

        node_ptr = next_ptr;
    }
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type* m1::intrusive_list_impl::begin_node_ptr()
{
    return m_SentinelNode.m_NextPtr;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_impl::node_type const* m1::intrusive_list_impl::get_begin_node_ptr() const
{
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

/*explicit*/ m1::intrusive_list_iterator_impl::intrusive_list_iterator_impl(intrusive_list_node *node_ptr)
    : m_NodePtr(node_ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_iterator_impl& m1::intrusive_list_iterator_impl::operator ++ ()
{
    m_NodePtr = m_NodePtr->next_node_ptr();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_iterator_impl m1::intrusive_list_iterator_impl::operator ++ (int)
{
    intrusive_list_iterator_impl result = *this;
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_iterator_impl& m1::intrusive_list_iterator_impl::operator -- ()
{
    m_NodePtr = m_NodePtr->prev_node_ptr();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_iterator_impl m1::intrusive_list_iterator_impl::operator -- (int)
{
    intrusive_list_iterator_impl result = *this;
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node* m1::intrusive_list_iterator_impl::get_node_ptr() const
{
    return m_NodePtr;
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ void m1::swap(intrusive_list_iterator_impl &lhs,
                         intrusive_list_iterator_impl &rhs) noexcept
{
    std::swap(lhs.m_NodePtr, rhs.m_NodePtr);
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator == (intrusive_list_iterator_impl const &lhs,
                                 intrusive_list_iterator_impl const &rhs) noexcept
{
    return lhs.m_NodePtr == rhs.m_NodePtr;
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator != (intrusive_list_iterator_impl const &lhs,
                                 intrusive_list_iterator_impl const &rhs) noexcept
{
    return lhs.m_NodePtr != rhs.m_NodePtr;
}

// ====================================================================================================================

/*explicit*/ m1::intrusive_list_const_iterator_impl::intrusive_list_const_iterator_impl(intrusive_list_node const *node_ptr)
    : m_NodePtr(node_ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl::intrusive_list_const_iterator_impl(intrusive_list_iterator_impl &&rhs) noexcept
    : m_NodePtr(std::move(rhs.m_NodePtr))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl::intrusive_list_const_iterator_impl(intrusive_list_iterator_impl const &rhs) noexcept
    : m_NodePtr(rhs.m_NodePtr)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl& m1::intrusive_list_const_iterator_impl::operator = (intrusive_list_iterator_impl &&rhs) noexcept
{
    m_NodePtr = std::move(rhs.m_NodePtr);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl& m1::intrusive_list_const_iterator_impl::operator = (intrusive_list_iterator_impl const &rhs) noexcept
{
    m_NodePtr = rhs.m_NodePtr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl& m1::intrusive_list_const_iterator_impl::operator ++ ()
{
    m_NodePtr = m_NodePtr->get_next_node_ptr();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl m1::intrusive_list_const_iterator_impl::operator ++ (int)
{
    intrusive_list_const_iterator_impl result = *this;
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl& m1::intrusive_list_const_iterator_impl::operator -- ()
{
    m_NodePtr = m_NodePtr->get_prev_node_ptr();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_const_iterator_impl m1::intrusive_list_const_iterator_impl::operator -- (int)
{
    intrusive_list_const_iterator_impl result = *this;
    --(*this);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::intrusive_list_node const* m1::intrusive_list_const_iterator_impl::get_node_ptr() const
{
    return m_NodePtr;
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ void m1::swap(intrusive_list_const_iterator_impl &lhs,
                         intrusive_list_const_iterator_impl &rhs) noexcept
{
    std::swap(lhs.m_NodePtr, rhs.m_NodePtr);
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator == (intrusive_list_const_iterator_impl const &lhs,
                                 intrusive_list_const_iterator_impl const &rhs) noexcept
{
    return lhs.m_NodePtr == rhs.m_NodePtr;
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator != (intrusive_list_const_iterator_impl const &lhs,
                                 intrusive_list_const_iterator_impl const &rhs) noexcept
{
    return lhs.m_NodePtr != rhs.m_NodePtr;
}

// ====================================================================================================================
