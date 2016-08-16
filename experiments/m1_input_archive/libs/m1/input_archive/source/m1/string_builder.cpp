#include "m1/string_builder.hpp"
#include "m1/utf8_encode.hpp"
#include "m1/utf16_encode.hpp"
#include "m1/verify.hpp"
#include <iterator>

// ====================================================================================================================

template <typename CharT,
          typename Traits,
          typename Allocator>
static void append_utf32(std::basic_string<CharT, Traits, Allocator> &str,
                         std::locale const &locale,
                         char32_t ch);

// ====================================================================================================================

/*explicit*/ m1::string_builder::string_builder(std::size_t const reserve_hint)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::string_builder::string_builder(std::locale const &locale)
    : m_Locale(locale)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::string_builder::string_builder(std::size_t const reserve_hint, std::locale const &locale)
    : m_Locale(locale)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::string_builder::append(code_point const ch) /*override*/
{
    append_utf32(/*ref*/ m_Str,
                 m_Locale,
                 ch);
}

// --------------------------------------------------------------------------------------------------------------------

std::string m1::string_builder::str() &&
{
    return std::move(m_Str);
}

// ====================================================================================================================

/*explicit*/ m1::wstring_builder::wstring_builder(std::size_t const reserve_hint)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::wstring_builder::wstring_builder(std::locale const &locale)
    : m_Locale(locale)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::wstring_builder::wstring_builder(std::size_t const reserve_hint, std::locale const &locale)
    : m_Locale(locale)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::wstring_builder::append(code_point const ch) /*override*/
{
    append_utf32(/*ref*/ m_Str,
                 m_Locale,
                 ch);
}

// --------------------------------------------------------------------------------------------------------------------

std::wstring m1::wstring_builder::str() &&
{
    return std::move(m_Str);
}

// ====================================================================================================================

/*explicit*/ m1::u8string_builder::u8string_builder(std::size_t const reserve_hint)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::u8string_builder::append(code_point const ch) /*override*/
{
    utf8_encode_next(std::back_inserter(m_Str), ch);
}

// --------------------------------------------------------------------------------------------------------------------

std::string m1::u8string_builder::str() &&
{
    return std::move(m_Str);
}

// ====================================================================================================================

/*explicit*/ m1::u16string_builder::u16string_builder(std::size_t const reserve_hint)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::u16string_builder::append(code_point const ch) /*override*/
{
    utf16_encode_next(std::back_inserter(m_Str), ch);
}

// --------------------------------------------------------------------------------------------------------------------

std::u16string m1::u16string_builder::str() &&
{
    return std::move(m_Str);
}

// ====================================================================================================================

/*explicit*/ m1::u32string_builder::u32string_builder(std::size_t const reserve_hint)
{
    m_Str.reserve(reserve_hint);
}

// --------------------------------------------------------------------------------------------------------------------

/*virtual*/ void m1::u32string_builder::append(code_point const ch) /*override*/
{
    m_Str.push_back(ch);
}

// --------------------------------------------------------------------------------------------------------------------

std::u32string m1::u32string_builder::str() &&
{
    return std::move(m_Str);
}

// ====================================================================================================================

template <typename CharT,
          typename Traits,
          typename Allocator>
static void append_utf32(std::basic_string<CharT, Traits, Allocator> &str,
                         std::locale const &locale,
                         char32_t const ch)
{
    typedef std::codecvt<char32_t, CharT, std::mbstate_t> codecvt;
    codecvt const &cvt = std::use_facet<codecvt>(locale);

    constexpr std::size_t const multibyte_buffer_capacity = 4;
    CharT multibyte_buffer[multibyte_buffer_capacity] = {};
    CharT *multibyte_buffer_end = nullptr;

    char32_t const *ch_next = nullptr;
    codecvt::state_type mbstate;
    switch(cvt.out(/*ref*/ mbstate,
                   &ch,
                   &ch + 1,
                   /*ref*/ ch_next,
                   multibyte_buffer,
                   multibyte_buffer + multibyte_buffer_capacity,
                   /*ref*/ multibyte_buffer_end))
    {
        case codecvt::ok:
        case codecvt::partial:
        {
            std::size_t const multibyte_buffer_size = multibyte_buffer_end - multibyte_buffer;
            str.append(multibyte_buffer, multibyte_buffer_size);
            break;
        }

        case codecvt::error:
            M1_ERROR(throw std::range_error("Error converting UTF-32 to locale dependent multibyte string"));
            break;

        case codecvt::noconv:
            M1_ERROR(throw std::range_error("Error converting UTF-32 to locale dependent multibyte string: unexpected non-conversion"));
            break;
    }
}

// ====================================================================================================================
