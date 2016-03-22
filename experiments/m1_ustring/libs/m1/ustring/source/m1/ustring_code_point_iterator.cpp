#include "m1/ustring.hpp"
#include "m1/ustring_buffer.hpp"
#include <cassert>

// ====================================================================================================================

static m1::ustring::size_type ustring_index_add(m1::ustring::size_type lhs,
                                                m1::ustring::code_point_iterator::difference_type rhs) noexcept;

static m1::ustring::size_type ustring_index_add(m1::ustring::code_point_iterator::difference_type lhs,
                                                m1::ustring::size_type rhs) noexcept;

// --------------------------------------------------------------------------------------------------------------------

static m1::ustring::code_point_iterator::difference_type ustring_index_subtract(m1::ustring::size_type lhs,
                                                                                m1::ustring::size_type rhs) noexcept;

// ====================================================================================================================

m1::ustring::code_point_iterator::code_point_iterator(ustring const &str,
                                                      ustring::size_type const index)
    : m_StrPtr(&str)
    , m_Index(index)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator::code_point_iterator(code_point_iterator &&rhs) = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator::code_point_iterator(code_point_iterator const &rhs) = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator& m1::ustring::code_point_iterator::operator = (code_point_iterator &&rhs) = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator& m1::ustring::code_point_iterator::operator = (code_point_iterator const &rhs) = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator::~code_point_iterator() = default;

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::ustring::code_point_iterator::operator * () const
{
    return (*m_StrPtr)[m_Index];
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::ustring::code_point_iterator::operator [] (difference_type n) const
{
    return (*m_StrPtr)[m_Index + n];
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator& m1::ustring::code_point_iterator::operator ++ ()
{
    ++m_Index;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator m1::ustring::code_point_iterator::operator ++ (int)
{
    code_point_iterator result = *this;
    ++(*this);
    return result;
}
// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator& m1::ustring::code_point_iterator::operator -- ()
{
    --m_Index;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator m1::ustring::code_point_iterator::operator -- (int)
{
    code_point_iterator result = *this;
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator& m1::ustring::code_point_iterator::operator += (difference_type const n)
{
    m_Index += n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator& m1::ustring::code_point_iterator::operator -= (difference_type const n)
{
    m_Index -= n;
    return *this;
}

// ====================================================================================================================

/*friend*/ m1::ustring::code_point_iterator m1::operator + (ustring::code_point_iterator const &lhs,
                                                            ustring::code_point_iterator::difference_type const rhs)
{
    return ustring::code_point_iterator(*lhs.m_StrPtr,
                                        ustring_index_add(lhs.m_Index, rhs));
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ m1::ustring::code_point_iterator m1::operator + (ustring::code_point_iterator::difference_type const lhs,
                                                            ustring::code_point_iterator const &rhs)
{
    return ustring::code_point_iterator(*rhs.m_StrPtr,
                                        ustring_index_add(lhs, rhs.m_Index));
}

// ====================================================================================================================

/*friend*/ m1::ustring::code_point_iterator::difference_type m1::operator - (ustring::code_point_iterator const &lhs,
                                                                             ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return ustring_index_subtract(lhs.m_Index, rhs.m_Index);
}

// ====================================================================================================================

/*friend*/ bool m1::operator == (ustring::code_point_iterator const &lhs,
                                 ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return lhs.m_Index == rhs.m_Index;
}

// ====================================================================================================================

/*friend*/ bool m1::operator != (ustring::code_point_iterator const &lhs,
                                 ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return lhs.m_Index != rhs.m_Index;
}

// ====================================================================================================================

/*friend*/ bool m1::operator < (ustring::code_point_iterator const &lhs,
                                ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return lhs.m_Index < rhs.m_Index;
}

// ====================================================================================================================

/*friend*/ bool m1::operator <= (ustring::code_point_iterator const &lhs,
                                 ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return lhs.m_Index <= rhs.m_Index;
}

// ====================================================================================================================

/*friend*/ bool m1::operator > (ustring::code_point_iterator const &lhs,
                                ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return lhs.m_Index > rhs.m_Index;
}

// ====================================================================================================================

/*friend*/ bool m1::operator >= (ustring::code_point_iterator const &lhs,
                                 ustring::code_point_iterator const &rhs)
{
    assert(lhs.m_StrPtr == rhs.m_StrPtr);
    return lhs.m_Index >= rhs.m_Index;
}

// ====================================================================================================================

/*static*/ m1::ustring::size_type ustring_index_add(m1::ustring::size_type const lhs,
                                                    m1::ustring::code_point_iterator::difference_type const rhs) noexcept
{
    return static_cast<m1::ustring::size_type>(static_cast<m1::ustring::code_point_iterator::difference_type>(lhs) + rhs);
}

/*static*/ m1::ustring::size_type ustring_index_add(m1::ustring::code_point_iterator::difference_type const lhs,
                                                    m1::ustring::size_type const rhs) noexcept
{
    return static_cast<m1::ustring::size_type>(lhs + static_cast<m1::ustring::code_point_iterator::difference_type>(rhs));
}

// --------------------------------------------------------------------------------------------------------------------

/*static*/ m1::ustring::code_point_iterator::difference_type ustring_index_subtract(m1::ustring::size_type const lhs,
                                                                                    m1::ustring::size_type const rhs) noexcept
{
    return static_cast<m1::ustring::code_point_iterator::difference_type>(lhs) - static_cast<m1::ustring::code_point_iterator::difference_type>(rhs);
}

// ====================================================================================================================
