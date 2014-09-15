#include "m1/any_ptr.hpp"
#include <utility>

// ---------------------------------------------------------------------------------------------------------------------
// m1::any_ptr
// ---------------------------------------------------------------------------------------------------------------------

void m1::swap(any_ptr &lhs, any_ptr &rhs)
{
    lhs.swap(rhs);
}

void m1::any_ptr::swap(any_ptr &rhs)
{
    using std::swap;
    swap(m_Ptr, rhs.m_Ptr);
    swap(m_TypeId, rhs.m_TypeId);
}

/*explicit*/ m1::any_ptr::operator bool () const
{
    return m_Ptr != nullptr;
}

m1::any_ptr::any_ptr(void *ptr, type_id_t const type_id)
    : m_Ptr(ptr)
    , m_TypeId(type_id)
{
}

// ---------------------------------------------------------------------------------------------------------------------
// m1::const_any_ptr
// ---------------------------------------------------------------------------------------------------------------------

void m1::swap(const_any_ptr &lhs, const_any_ptr &rhs)
{
    lhs.swap(rhs);
}

m1::const_any_ptr::const_any_ptr(any_ptr &&rhs)
    : m_Ptr(std::move(rhs.m_Ptr))
    , m_TypeId(std::move(rhs.m_TypeId))
{
    rhs.m_Ptr = nullptr;
    rhs.m_TypeId = nullptr;
}

m1::const_any_ptr::const_any_ptr(any_ptr const &rhs)
    : m_Ptr(rhs.m_Ptr)
    , m_TypeId(rhs.m_TypeId)
{
}

m1::const_any_ptr& m1::const_any_ptr::operator = (any_ptr &&rhs)
{
    m_Ptr = std::move(rhs.m_Ptr);
    m_TypeId = std::move(rhs.m_TypeId);
    rhs.m_Ptr = nullptr;
    rhs.m_TypeId = nullptr;
    return *this;
}

m1::const_any_ptr& m1::const_any_ptr::operator = (any_ptr const &rhs)
{
    m_Ptr = rhs.m_Ptr;
    m_TypeId = rhs.m_TypeId;
    return *this;
}

void m1::const_any_ptr::swap(const_any_ptr &rhs)
{
    using std::swap;
    swap(m_Ptr, rhs.m_Ptr);
    swap(m_TypeId, rhs.m_TypeId);
}

/*explicit*/ m1::const_any_ptr::operator bool () const
{
    return m_Ptr != nullptr;
}

m1::const_any_ptr::const_any_ptr(void const * const ptr, type_id_t const type_id)
    : m_Ptr(ptr)
    , m_TypeId(type_id)
{
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::operator == (std::nullptr_t, any_ptr const &rhs)
{
    return !rhs;
}

bool m1::operator == (std::nullptr_t, const_any_ptr const &rhs)
{
    return !rhs;
}

bool m1::operator == (any_ptr const &lhs, std::nullptr_t)
{
    return !lhs;
}

bool m1::operator == (any_ptr const &lhs, any_ptr const &rhs)
{
    return lhs.m_Ptr == rhs.m_Ptr;
}

bool m1::operator == (any_ptr const &lhs, const_any_ptr const &rhs)
{
    return lhs.m_Ptr == rhs.m_Ptr;
}

bool m1::operator == (const_any_ptr const &lhs, std::nullptr_t)
{
    return !lhs;
}

bool m1::operator == (const_any_ptr const &lhs, any_ptr const &rhs)
{
    return lhs.m_Ptr == rhs.m_Ptr;
}

bool m1::operator == (const_any_ptr const &lhs, const_any_ptr const &rhs)
{
    return lhs.m_Ptr == rhs.m_Ptr;
}

// ---------------------------------------------------------------------------------------------------------------------

bool m1::operator != (std::nullptr_t, any_ptr const &rhs)
{
    return static_cast<bool>(rhs);
}

bool m1::operator != (std::nullptr_t, const_any_ptr const &rhs)
{
    return static_cast<bool>(rhs);
}

bool m1::operator != (any_ptr const &lhs, std::nullptr_t)
{
    return static_cast<bool>(lhs);
}

bool m1::operator != (any_ptr const &lhs, any_ptr const &rhs)
{
    return lhs.m_Ptr != rhs.m_Ptr;
}

bool m1::operator != (any_ptr const &lhs, const_any_ptr const &rhs)
{
    return lhs.m_Ptr != rhs.m_Ptr;
}

bool m1::operator != (const_any_ptr const &lhs, std::nullptr_t)
{
    return static_cast<bool>(lhs);
}

bool m1::operator != (const_any_ptr const &lhs, any_ptr const &rhs)
{
    return lhs.m_Ptr != rhs.m_Ptr;
}

bool m1::operator != (const_any_ptr const &lhs, const_any_ptr const &rhs)
{
    return lhs.m_Ptr != rhs.m_Ptr;
}
