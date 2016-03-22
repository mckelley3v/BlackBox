#include "m1/ustring.hpp"
#include "m1/ustring_buffer.hpp"
#include "m1/pragma_message.hpp"
#include <limits>
#include <string>
#include <cassert>

// ====================================================================================================================

m1::ustring::ustring() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(ascii_encoding const encoding, char const * const c_str)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      c_str))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::locale const &locale, char const * const n_str)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      locale,
                                      n_str))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::locale const &locale, wchar_t const * const w_str)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      locale,
                                      w_str))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf8_encoding const encoding, unsigned char const * const u8_str)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u8_str))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf16_encoding const encoding, char16_t const * const u16_str)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u16_str))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf32_encoding const encoding, char32_t const * const u32_str)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u32_str))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(ascii_encoding const encoding, char const * const c_str, size_type const str_length)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      c_str,
                                      str_length))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::locale const &locale, char const * const n_str, size_type const str_length)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      locale,
                                      n_str,
                                      str_length))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::locale const &locale, wchar_t const * const w_str, size_type const str_length)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      locale,
                                      w_str,
                                      str_length))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf8_encoding const encoding, unsigned char const * const u8_str, size_type const str_length)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u8_str,
                                      str_length))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf16_encoding const encoding, char16_t const * const u16_str, size_type const str_length)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u16_str,
                                      str_length))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf32_encoding const encoding, char32_t const * const u32_str, size_type const str_length)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u32_str,
                                      str_length))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(ascii_encoding const encoding, char const * const c_str, char const * const c_end)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      c_str,
                                      c_end))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::locale const &locale, char const * const n_str, char const * const n_end)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      locale,
                                      n_str,
                                      n_end))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::locale const &locale, wchar_t const * const w_str, wchar_t const * const w_end)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      locale,
                                      w_str,
                                      w_end))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf8_encoding const encoding, unsigned char const * const u8_str, unsigned char const * const u8_end)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u8_str,
                                      u8_end))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf16_encoding const encoding, char16_t const * const u16_str, char16_t const * const u16_end)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u16_str,
                                      u16_end))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(utf32_encoding const encoding, char32_t const * const u32_str, char32_t const * const u32_end)
    : m_BufferPtr(make_ustring_buffer(/*out*/ m_StrLength,
                                      /*out*/ m_CodePointSize,
                                      encoding,
                                      u32_str,
                                      u32_end))
    , m_BufferEnd(get_code_point_ptr(m_BufferPtr.get(),
                                     m_StrLength,
                                     m_CodePointSize))
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(code_point_iterator const &begin,
                     code_point_iterator const &end) noexcept
    : m_StrLength(begin.m_Index - end.m_Index)
    , m_CodePointSize(begin.m_StrPtr->m_CodePointSize)
    , m_BufferPtr(get_code_point_ptr(begin.m_StrPtr->m_BufferPtr,
                                     begin.m_Index,
                                     begin.m_StrPtr->m_CodePointSize))
    , m_BufferEnd(get_code_point_ptr(end.m_StrPtr->m_BufferPtr.get(),
                                     end.m_Index,
                                     end.m_StrPtr->m_CodePointSize))
{
    #pragma M1_MESSAGE("consider allowing construction of ustring from begin/end iterators of different ustrings if they reference the same ustring_buffer")
    assert(begin.m_StrPtr == end.m_StrPtr);
    assert(begin.m_Index <= end.m_Index);
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::size_t const str_length,
                     std::size_t const code_point_size,
                     std::shared_ptr<void const> const &buffer_owner,
                     void const * const buffer_ptr,
                     void const * const buffer_end)
    : m_StrLength(str_length)
    , m_CodePointSize(code_point_size)
    , m_BufferPtr(buffer_owner, buffer_ptr)
    , m_BufferEnd(buffer_end)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(ustring &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(ustring const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring& m1::ustring::operator = (ustring &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring& m1::ustring::operator = (ustring const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::~ustring() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator m1::ustring::begin() const noexcept
{
    return code_point_iterator(*this, 0);
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator m1::ustring::cbegin() const noexcept
{
    return code_point_iterator(*this, 0);
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::reverse_code_point_iterator m1::ustring::rbegin() const noexcept
{
    return reverse_code_point_iterator(begin());
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::reverse_code_point_iterator m1::ustring::crbegin() const noexcept
{
    return reverse_code_point_iterator(cbegin());
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator m1::ustring::end() const noexcept
{
    return code_point_iterator(*this, m_StrLength);
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point_iterator m1::ustring::cend() const noexcept
{
    return code_point_iterator(*this, m_StrLength);
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::reverse_code_point_iterator m1::ustring::rend() const noexcept
{
    return reverse_code_point_iterator(end());
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::reverse_code_point_iterator m1::ustring::crend() const noexcept
{
    return reverse_code_point_iterator(cend());
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::ustring::empty() const noexcept
{
    return m_StrLength == 0;
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::size_type m1::ustring::length() const noexcept
{
    return m_StrLength;
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::ustring::at(size_type const index) const
{
    if(index < m_StrLength)
    {
        return operator [] (index);
    }

    throw std::out_of_range("Invalid index");
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::ustring::operator [] (size_type const index) const noexcept
{
    assert(index < m_StrLength);
    return get_code_point(m_BufferPtr, index, m_CodePointSize);
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::ustring::front() const noexcept
{
    return operator [] (0);
}

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::ustring::back() const noexcept
{
    return operator [] (m_StrLength - 1);
}

// --------------------------------------------------------------------------------------------------------------------

void const* m1::ustring::data() const noexcept
{
    return m_BufferPtr.get();
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring::size_type m1::ustring::size() const noexcept
{
    return m_StrLength * m_CodePointSize;
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring m1::ustring::substr(size_type const index,
                                size_type const length /*= npos*/) const noexcept
{
    if(index < m_StrLength)
    {
        size_type const substr_max_length = m_StrLength - index;
        size_type const substr_length = (length < substr_max_length) ? length : substr_max_length;
        size_type const substr_end_index = index + substr_length;

        return m1::ustring(code_point_iterator(*this, index),
                           code_point_iterator(*this, substr_end_index));
    }

    return ustring();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::ustring::clear() noexcept
{
    *this = ustring();
}

// --------------------------------------------------------------------------------------------------------------------

void m1::ustring::swap(ustring &rhs) noexcept
{
    using std::swap;
    swap(m_StrLength, rhs.m_StrLength);
    swap(m_CodePointSize, rhs.m_CodePointSize);
    swap(m_BufferPtr, rhs.m_BufferPtr);
    swap(m_BufferEnd, rhs.m_BufferEnd);
}

// ====================================================================================================================

/*friend*/ m1::ustring m1::literals::operator "" _us(char const * const c_str,
                                                    std::size_t const length) noexcept
{
    return make_ustring_view(c_str, length);
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ m1::ustring m1::literals::operator "" _us(wchar_t const * const w_str,
                                                    std::size_t const length) noexcept
{
    return make_ustring_view(w_str, length);
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ m1::ustring m1::literals::operator "" _us(char32_t const * const u32_str,
                                                    std::size_t const length) noexcept
{
    return make_ustring_view(u32_str, length);
}

// ====================================================================================================================

m1::ustring m1::make_ustring_view(char const *c_str, std::size_t const length) noexcept
{
    return ustring(length, // str_length
                   sizeof(*c_str), // code_point_size
                   std::shared_ptr<void const>(), // buffer_owner
                   c_str, // buffer_ptr
                   c_str + length); // buffer_end
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring m1::make_ustring_view(wchar_t const *w_str, std::size_t const length) noexcept
{
    return ustring(length, // str_length
                   sizeof(*w_str), // code_point_size
                   std::shared_ptr<void const>(), // buffer_owner
                   w_str, // buffer_ptr
                   w_str + length); // buffer_end
}

// --------------------------------------------------------------------------------------------------------------------

m1::ustring m1::make_ustring_view(char32_t const *u32_str, std::size_t const length) noexcept
{
    return ustring(length, // str_length
                   sizeof(*u32_str), // code_point_size
                   std::shared_ptr<void const>(), // buffer_owner
                   u32_str, // buffer_ptr
                   u32_str + length); // buffer_end
}

// ====================================================================================================================

m1::ustring m1::normalize(ustring const &str,
                          normal_form /*form*/ /*= normal_form::NFC*/)
{
#pragma M1_MESSAGE("implement m1::normalize")
    assert(false && "TODO");
    return str;
}

// ====================================================================================================================

bool m1::operator == (ustring const &lhs, ustring const &rhs)
{
    return compare(lhs, rhs) == 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator != (ustring const &lhs, ustring const &rhs)
{
    return compare(lhs, rhs) != 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator < (ustring const &lhs, ustring const &rhs)
{
    return compare(lhs, rhs) < 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator <= (ustring const &lhs, ustring const &rhs)
{
    return compare(lhs, rhs) <= 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator > (ustring const &lhs, ustring const &rhs)
{
    return compare(lhs, rhs) > 0;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::operator >= (ustring const &lhs, ustring const &rhs)
{
    return compare(lhs, rhs) >= 0;
}

// ====================================================================================================================

int m1::compare(ustring const &/*lhs*/,
                ustring const &/*rhs*/,
                normal_form /*form*/ /*= normal_form::NFC*/,
                compare_case /*compare*/ /*= compare_case::yes*/)
{
#pragma M1_MESSAGE("implement m1::compare")
    assert(false && "TODO");
    return 0;
}

// ====================================================================================================================

std::size_t m1::hash(ustring const &str) noexcept
{
#pragma M1_MESSAGE("consider 64-bit hash")
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    constexpr std::size_t const fnv_basis = 2166136261u; // 14695981039346656037ull;
    constexpr std::size_t const fnv_prime = 16777619u; // 1099511628211ull;

    std::hash<code_point> const h;
    std::size_t result = fnv_basis;
    for(code_point const c : str)
    {
        result ^= h(c);
        result *= fnv_prime;
    }

    return result;
}

// ====================================================================================================================

void m1::swap(ustring &lhs,
              ustring &rhs) noexcept
{
    return lhs.swap(rhs);
}

// ====================================================================================================================

std::hash<m1::ustring>::result_type std::hash<m1::ustring>::operator () (argument_type const &arg) const
{
    return m1::hash(arg);
}

// ====================================================================================================================

void std::swap(m1::ustring &lhs,
               m1::ustring &rhs) noexcept
{
    return lhs.swap(rhs);
}

// ====================================================================================================================
