#include "m1/utf16_iterator.hpp"

// ====================================================================================================================

template <typename EvalFunc>
static bool end_utf16(char16_t const *code_unit_ptr,
                      char16_t const *code_unit_end);

// --------------------------------------------------------------------------------------------------------------------

template <typename EvalFunc>
static char32_t decode_utf16(char16_t const *code_unit_ptr, EvalFunc &&eval);

// --------------------------------------------------------------------------------------------------------------------

template <typename EvalFunc>
static void next_utf16(char16_t const *&code_unit_ptr, EvalFunc &&eval);

// --------------------------------------------------------------------------------------------------------------------

template <typename EvalFunc>
static void prev_utf16(char16_t const *&code_unit_ptr, EvalFunc &&eval);

// ====================================================================================================================

m1::byte_order m1::consume_utf16_byte_order_mark(char16_t const *&u16_str) noexcept
{
    if(u16_str)
    {
        char16_t const big_endian_mark = *reinterpret_cast<char16_t const*>("\xFE\xFF");
        char16_t const little_endian_mark = *reinterpret_cast<char16_t const*>("\xFF\xFE");

        if(*u16_str == big_endian_mark)
        {
            ++u16_str;
            return byte_order::big_endian;
        }
        else if(*u16_str == little_endian_mark)
        {
            ++u16_str;
            return byte_order::little_endian;
        }
    }

    // no BOM, assume big endian
    return byte_order::big_endian;
}

// ====================================================================================================================

m1::utf16_iterator_big_endian::utf16_iterator_big_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::utf16_iterator_big_endian::utf16_iterator_big_endian(char16_t const *u16_str) noexcept
    : m_CodeUnitPtr(u16_str)
{
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian::utf16_iterator_big_endian(utf16_iterator_big_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian::utf16_iterator_big_endian(utf16_iterator_big_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian& m1::utf16_iterator_big_endian::operator = (utf16_iterator_big_endian &&rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian& m1::utf16_iterator_big_endian::operator = (utf16_iterator_big_endian const &rhs) noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian::~utf16_iterator_big_endian() noexcept = default;

// --------------------------------------------------------------------------------------------------------------------

m1::code_point m1::utf16_iterator_big_endian::operator * () const
{
    return decode_utf16(m_CodeUnitPtr, big_endian);

    //char32_t const code_unit0 = static_cast<char32_t>(big_endian(m_CodeUnitPtr[0]));
    //if((code_unit0 & 0xDC00) == 0xD800)
    //{
    //    char32_t const code_unit1 = static_cast<char32_t>(big_endian(m_CodeUnitPtr[1]));
    //    char32_t const code_point = ((code_unit0 & 0x3FF) << 10) | (code_unit1 & 0x3FF)) + 0x10000;
    //    return code_point;
    //}

    //return code_unit0;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian& m1::utf16_iterator_big_endian::operator ++ ()
{
    next_utf16(m_CodeUnitPtr, big_endian);

    //++m_CodeUnitPtr;
    //char16_t const code_unit = big_endian(m_CodeUnitPtr[0]);
    //if((code_unit & 0xDC00) == 0xDC00)
    //{
    //    ++m_CodeUnitPtr;
    //}

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian m1::utf16_iterator_big_endian::operator ++ (int)
{
    utf16_iterator_big_endian result(*this);
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian& m1::utf16_iterator_big_endian::operator -- ()
{
    prev_utf16(m_CodeUnitPtr, big_endian);

    //--m_CodeUnitPtr;
    //char16_t const code_unit = big_endian(m_CodeUnitPtr[0]);
    //if((code_unit & 0xDC00) == 0xDC00)
    //{
    //    --m_CodeUnitPtr;
    //}

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

m1::utf16_iterator_big_endian m1::utf16_iterator_big_endian::operator -- (int)
{
    utf16_iterator_big_endian result(*this);
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::utf16_iterator_big_endian::swap(utf16_iterator_big_endian &rhs) noexcept
{
    using std::swap;
    swap(m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator == (utf16_iterator_big_endian const &lhs,
                                 utf16_iterator_big_endian const &rhs) noexcept
{
    return end_utf16(lhs.m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// --------------------------------------------------------------------------------------------------------------------

/*friend*/ bool m1::operator != (utf16_iterator_big_endian const &lhs,
                                 utf16_iterator_big_endian const &rhs) noexcept
{
    return !end_utf16(lhs.m_CodeUnitPtr, rhs.m_CodeUnitPtr);
}

// ====================================================================================================================

template <typename EvalFunc>
static bool end_utf16(char16_t const *code_unit_ptr,
                      char16_t const *code_unit_end)
{
    if (code_unit_ptr >= code_unit_end)
    {
        // already at end
        return true;
    }

    char16_t const code_unit0 = eval(code_unit_ptr[0]);
    if((code_unit0 < 0xD8000) || (code_unit0 > 0xDFFF))
    {
        // valid code_point from single code_unit
        return false;
    }

    if((0xD800 <= code_unit0) && (code_unit0 <= 0xDBFF))
    {
        // code_point is from 2 code_units: check if next code_unit is at end
        return (code_unit_ptr + 1) == code_unit_end;
    }

    return true;
}

// ====================================================================================================================

template <typename EvalFunc>
/*static*/ char32_t decode_utf16(char16_t const * const code_unit_ptr, EvalFunc &&eval)
{
    char16_t const code_unit0 = eval(code_unit_ptr[0]);

    if((code_unit0 < 0xD8000) || (code_unit0 > 0xDFFF))
    {
        char32_t const code_point = static_cast<char32_t>(code_unit0);
        return code_point;
    }

    if((0xD800 <= code_unit0) && (code_unit0 <= 0xDBFF))
    {
        // using end_utf16 should ensure that code_unit_ptr[1] is valid
        char16_t const code_unit1 = code_unit_ptr[1];

        if((0xDC00 <= code_unit1) && (code_unit1 <= 0xDFFF))
        {
            char32_t const code_point_hi = code_unit0 & 0x3FF;
            char32_t const code_point_lo = code_unit1 & 0x3FF;
            char32_t const code_point = code_point_hi << 10 | code_point_lo;
            return code_point;
        }
    }

    // error: return unicode replacement character
    return 0xFFFD;
}

// ====================================================================================================================
