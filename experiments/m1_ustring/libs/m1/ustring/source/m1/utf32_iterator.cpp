#include "m1/utf32_iterator.hpp"

// ====================================================================================================================

m1::byte_order m1::consume_utf32_byte_order_mark(char32_t const *&u32_str) noexcept
{
    if(u32_str)
    {
        char32_t const big_endian_mark = *reinterpret_cast<char32_t const*>("\x00\x00\xFE\xFF");
        char32_t const little_endian_mark = *reinterpret_cast<char32_t const*>("\xFF\xFE\x00\x00");

        if(*u32_str == big_endian_mark)
        {
            ++u32_str;
            return byte_order::big_endian;
        }
        else if(*u32_str == little_endian_mark)
        {
            ++u32_str;
            return byte_order::little_endian;
        }
    }

    // no BOM, assume big endian
    return byte_order::big_endian;
}

// ====================================================================================================================

m1::utf32_iterator_big_endian::utf32_iterator_big_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::utf32_iterator_big_endian::utf32_iterator_big_endian(char32_t const * const u32_str) noexcept
    : m_CodeUnitPtr(u32_str)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian::utf32_iterator_big_endian(utf32_iterator_big_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian::utf32_iterator_big_endian(utf32_iterator_big_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian& m1::utf32_iterator_big_endian::operator = (utf32_iterator_big_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian& m1::utf32_iterator_big_endian::operator = (utf32_iterator_big_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian::~utf32_iterator_big_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_iterator_big_endian::operator * () const noexcept
{
    return big_endian(*m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_iterator_big_endian::operator [] (difference_type n) const noexcept
{
    return big_endian(m_CodeUnitPtr[n]);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian& m1::utf32_iterator_big_endian::operator ++ () noexcept
{
    ++m_CodeUnitPtr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian m1::utf32_iterator_big_endian::operator ++ (int) noexcept
{
    utf32_iterator_big_endian result(*this);
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian& m1::utf32_iterator_big_endian::operator -- () noexcept
{
    --m_CodeUnitPtr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian m1::utf32_iterator_big_endian::operator -- (int) noexcept
{
    utf32_iterator_big_endian result(*this);
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian& m1::utf32_iterator_big_endian::operator += (difference_type n) noexcept
{
    m_CodeUnitPtr += n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian& m1::utf32_iterator_big_endian::operator -= (difference_type n) noexcept
{
    m_CodeUnitPtr -= n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::utf32_iterator_big_endian::swap(utf32_iterator_big_endian &rhs) noexcept
{
    using std::swap;
    swap(m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// ====================================================================================================================

m1::utf32_iterator_big_endian m1::operator + (utf32_iterator_big_endian const &lhs,
                                              utf32_iterator_big_endian::difference_type const rhs) noexcept
{
    return utf32_iterator_big_endian(lhs.m_CodeUnitPtr + rhs);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian m1::operator + (utf32_iterator_big_endian::difference_type const lhs,
                                              utf32_iterator_big_endian const &rhs) noexcept
{
    return utf32_iterator_big_endian(lhs + rhs.m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_big_endian::difference_type m1::operator - (utf32_iterator_big_endian const &lhs,
                                                               utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr - rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr == rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr != rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator < (utf32_iterator_big_endian const &lhs,
                     utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr < rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator <= (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr <= rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator > (utf32_iterator_big_endian const &lhs,
                     utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr > rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator >= (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr >= rhs.m_CodeUnitPtr;
}

// ====================================================================================================================

m1::utf32_iterator_little_endian::utf32_iterator_little_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::utf32_iterator_little_endian::utf32_iterator_little_endian(char32_t const * const u32_str) noexcept
    : m_CodeUnitPtr(u32_str)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian::utf32_iterator_little_endian(utf32_iterator_little_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian::utf32_iterator_little_endian(utf32_iterator_little_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian& m1::utf32_iterator_little_endian::operator = (utf32_iterator_little_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian& m1::utf32_iterator_little_endian::operator = (utf32_iterator_little_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian::~utf32_iterator_little_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_iterator_little_endian::operator * () const noexcept
{
    return little_endian(*m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_iterator_little_endian::operator [] (difference_type n) const noexcept
{
    return little_endian(m_CodeUnitPtr[n]);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian& m1::utf32_iterator_little_endian::operator ++ () noexcept
{
    ++m_CodeUnitPtr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian m1::utf32_iterator_little_endian::operator ++ (int) noexcept
{
    utf32_iterator_little_endian result(*this);
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian& m1::utf32_iterator_little_endian::operator -- () noexcept
{
    --m_CodeUnitPtr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian m1::utf32_iterator_little_endian::operator -- (int) noexcept
{
    utf32_iterator_little_endian result(*this);
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian& m1::utf32_iterator_little_endian::operator += (difference_type n) noexcept
{
    m_CodeUnitPtr += n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian& m1::utf32_iterator_little_endian::operator -= (difference_type n) noexcept
{
    m_CodeUnitPtr -= n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::utf32_iterator_little_endian::swap(utf32_iterator_little_endian &rhs) noexcept
{
    using std::swap;
    swap(m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// ====================================================================================================================

m1::utf32_iterator_little_endian m1::operator + (utf32_iterator_little_endian const &lhs,
                                                 utf32_iterator_little_endian::difference_type const rhs) noexcept
{
    return utf32_iterator_little_endian(lhs.m_CodeUnitPtr + rhs);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian m1::operator + (utf32_iterator_little_endian::difference_type const lhs,
                                                 utf32_iterator_little_endian const &rhs) noexcept
{
    return utf32_iterator_little_endian(lhs + rhs.m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_iterator_little_endian::difference_type m1::operator - (utf32_iterator_little_endian const &lhs,
                                                                  utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr - rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr == rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr != rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator < (utf32_iterator_little_endian const &lhs,
                     utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr < rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator <= (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr <= rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator > (utf32_iterator_little_endian const &lhs,
                     utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr > rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator >= (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr >= rhs.m_CodeUnitPtr;
}

// ====================================================================================================================

m1::utf32_counted_iterator_big_endian::utf32_counted_iterator_big_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::utf32_counted_iterator_big_endian::utf32_counted_iterator_big_endian(char32_t const * const u32_str, std::size_t const count /*= 0*/) noexcept
    : m_CodeUnitPtr(u32_str)
    , m_CodePointCount(count)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian::utf32_counted_iterator_big_endian(utf32_counted_iterator_big_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian::utf32_counted_iterator_big_endian(utf32_counted_iterator_big_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian& m1::utf32_counted_iterator_big_endian::operator = (utf32_counted_iterator_big_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian& m1::utf32_counted_iterator_big_endian::operator = (utf32_counted_iterator_big_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian::~utf32_counted_iterator_big_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_counted_iterator_big_endian::operator * () const noexcept
{
    return big_endian(*m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_counted_iterator_big_endian::operator [] (difference_type n) const noexcept
{
    return big_endian(m_CodeUnitPtr[n]);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian& m1::utf32_counted_iterator_big_endian::operator ++ () noexcept
{
    ++m_CodeUnitPtr;
    ++m_CodePointCount;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian m1::utf32_counted_iterator_big_endian::operator ++ (int) noexcept
{
    utf32_counted_iterator_big_endian result(*this);
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian& m1::utf32_counted_iterator_big_endian::operator -- () noexcept
{
    --m_CodeUnitPtr;
    --m_CodePointCount;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian m1::utf32_counted_iterator_big_endian::operator -- (int) noexcept
{
    utf32_counted_iterator_big_endian result(*this);
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian& m1::utf32_counted_iterator_big_endian::operator += (difference_type n) noexcept
{
    m_CodeUnitPtr += n;
    m_CodePointCount += n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian& m1::utf32_counted_iterator_big_endian::operator -= (difference_type n) noexcept
{
    m_CodeUnitPtr -= n;
    m_CodePointCount -= n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

std::size_t m1::utf32_counted_iterator_big_endian::count() const noexcept
{
    return m_CodePointCount;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::utf32_counted_iterator_big_endian::swap(utf32_counted_iterator_big_endian &rhs) noexcept
{
    using std::swap;
    swap(m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// ====================================================================================================================

m1::utf32_counted_iterator_big_endian m1::operator + (utf32_counted_iterator_big_endian const &lhs,
                                                      utf32_counted_iterator_big_endian::difference_type const rhs) noexcept
{
    return utf32_counted_iterator_big_endian(lhs.m_CodeUnitPtr + rhs, lhs.m_CodePointCount + rhs);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian m1::operator + (utf32_counted_iterator_big_endian::difference_type const lhs,
                                                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return utf32_counted_iterator_big_endian(lhs + rhs.m_CodeUnitPtr, lhs + rhs.m_CodePointCount);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_big_endian::difference_type m1::operator - (utf32_counted_iterator_big_endian const &lhs,
                                                                       utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr - rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr == rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr != rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator < (utf32_counted_iterator_big_endian const &lhs,
                     utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr != rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator <= (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr <= rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator > (utf32_counted_iterator_big_endian const &lhs,
                     utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr > rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator >= (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr >= rhs.m_CodeUnitPtr;
}

// ====================================================================================================================

m1::utf32_counted_iterator_little_endian::utf32_counted_iterator_little_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::utf32_counted_iterator_little_endian::utf32_counted_iterator_little_endian(char32_t const * const u32_str, std::size_t const count /*= 0*/) noexcept
    : m_CodeUnitPtr(u32_str)
    , m_CodePointCount(count)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian::utf32_counted_iterator_little_endian(utf32_counted_iterator_little_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian::utf32_counted_iterator_little_endian(utf32_counted_iterator_little_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian& m1::utf32_counted_iterator_little_endian::operator = (utf32_counted_iterator_little_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian& m1::utf32_counted_iterator_little_endian::operator = (utf32_counted_iterator_little_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian::~utf32_counted_iterator_little_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_counted_iterator_little_endian::operator * () const noexcept
{
    return little_endian(*m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf32_counted_iterator_little_endian::operator [] (difference_type n) const noexcept
{
    return little_endian(m_CodeUnitPtr[n]);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian& m1::utf32_counted_iterator_little_endian::operator ++ () noexcept
{
    ++m_CodeUnitPtr;
    ++m_CodePointCount;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian m1::utf32_counted_iterator_little_endian::operator ++ (int) noexcept
{
    utf32_counted_iterator_little_endian result(*this);
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian& m1::utf32_counted_iterator_little_endian::operator -- () noexcept
{
    --m_CodeUnitPtr;
    --m_CodePointCount;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian m1::utf32_counted_iterator_little_endian::operator -- (int) noexcept
{
    utf32_counted_iterator_little_endian result(*this);
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian& m1::utf32_counted_iterator_little_endian::operator += (difference_type n) noexcept
{
    m_CodeUnitPtr += n;
    m_CodePointCount += n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian& m1::utf32_counted_iterator_little_endian::operator -= (difference_type n) noexcept
{
    m_CodeUnitPtr -= n;
    m_CodePointCount -= n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

std::size_t m1::utf32_counted_iterator_little_endian::count() const noexcept
{
    return m_CodePointCount;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::utf32_counted_iterator_little_endian::swap(utf32_counted_iterator_little_endian &rhs) noexcept
{
    using std::swap;
    swap(m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// ====================================================================================================================

m1::utf32_counted_iterator_little_endian m1::operator + (utf32_counted_iterator_little_endian const &lhs,
                                                         utf32_counted_iterator_little_endian::difference_type const rhs) noexcept
{
    return utf32_counted_iterator_little_endian(lhs.m_CodeUnitPtr + rhs, lhs.m_CodePointCount + rhs);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian m1::operator + (utf32_counted_iterator_little_endian::difference_type const lhs,
                                                         utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return utf32_counted_iterator_little_endian(lhs + rhs.m_CodeUnitPtr, lhs + rhs.m_CodePointCount);
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_counted_iterator_little_endian::difference_type m1::operator - (utf32_counted_iterator_little_endian const &lhs,
                                                                          utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr - rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr == rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr != rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator < (utf32_counted_iterator_little_endian const &lhs,
                     utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr != rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator <= (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr <= rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator > (utf32_counted_iterator_little_endian const &lhs,
                     utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr > rhs.m_CodeUnitPtr;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator >= (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.m_CodeUnitPtr >= rhs.m_CodeUnitPtr;
}

// ====================================================================================================================

m1::utf32_terminator_length::utf32_terminator_length() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::utf32_terminator_length::utf32_terminator_length(std::size_t const length) noexcept
    : m_Length(length)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_terminator_length::utf32_terminator_length(utf32_terminator_length &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_terminator_length::utf32_terminator_length(utf32_terminator_length const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_terminator_length& m1::utf32_terminator_length::operator = (utf32_terminator_length &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_terminator_length& m1::utf32_terminator_length::operator = (utf32_terminator_length const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf32_terminator_length::~utf32_terminator_length() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

std::size_t m1::utf32_terminator_length::length() const noexcept
{
    return m_Length;
}

// ====================================================================================================================

bool m1::operator == (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.length() == rhs.count();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept
{
    return lhs.count() == rhs.length();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.length() == rhs.count();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept
{
    return lhs.count() == rhs.length();
}

// ====================================================================================================================

bool m1::operator != (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return lhs.length() != rhs.count();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept
{
    return lhs.count() != rhs.length();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return lhs.length() != rhs.count();
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept
{
    return lhs.count() != rhs.length();
}

// ====================================================================================================================

bool m1::operator == (utf32_terminator_null const &/*lhs*/,
                      utf32_iterator_big_endian const &rhs) noexcept
{
    return 0 == *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_iterator_big_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs == 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_terminator_null const &/*lhs*/,
                      utf32_iterator_little_endian const &rhs) noexcept
{
    return 0 == *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_iterator_little_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs == 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_terminator_null const &/*lhs*/,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return 0 == *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs == 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_terminator_null const &/*lhs*/,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return 0 == *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator == (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs == 0;
}

// ====================================================================================================================

bool m1::operator != (utf32_terminator_null const &/*lhs*/,
                      utf32_iterator_big_endian const &rhs) noexcept
{
    return 0 != *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_iterator_big_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs != 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_terminator_null const &/*lhs*/,
                      utf32_iterator_little_endian const &rhs) noexcept
{
    return 0 != *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_iterator_little_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs != 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_terminator_null const &/*lhs*/,
                      utf32_counted_iterator_big_endian const &rhs) noexcept
{
    return 0 != *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs != 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_terminator_null const &/*lhs*/,
                      utf32_counted_iterator_little_endian const &rhs) noexcept
{
    return 0 != *rhs;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_null const &/*rhs*/) noexcept
{
    return *lhs != 0;
}

// ====================================================================================================================

void std::swap(m1::utf32_iterator_big_endian &lhs,
               m1::utf32_iterator_big_endian &rhs) noexcept
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

void std::swap(m1::utf32_iterator_little_endian &lhs,
               m1::utf32_iterator_little_endian &rhs) noexcept
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

void std::swap(m1::utf32_counted_iterator_big_endian &lhs,
               m1::utf32_counted_iterator_big_endian &rhs) noexcept
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

void std::swap(m1::utf32_counted_iterator_little_endian &lhs,
               m1::utf32_counted_iterator_little_endian &rhs) noexcept
{
    lhs.swap(rhs);
}

// ====================================================================================================================
