#include "m1/crc32.hpp"
#include "m1/utf8_encode.hpp"

// =====================================================================================================================

/*explicit*/ m1::crc32_combine_iterator::crc32_combine_iterator(crc32 &crc)
    : m_CrcPtr(&crc)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::crc32_combine_iterator& m1::crc32_combine_iterator::operator = (std::uint8_t const byte)
{
    *m_CrcPtr = crc32_combine(*m_CrcPtr, byte);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::crc32_combine_iterator& m1::crc32_combine_iterator::operator * ()
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::crc32_combine_iterator& m1::crc32_combine_iterator::operator ++ ()
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::crc32_combine_iterator m1::crc32_combine_iterator::operator ++ (int)
{
    crc32_combine_iterator result = *this;
    ++(*this);
    return result;;
}

// ====================================================================================================================

/*explicit*/ m1::utf8_crc32_iterator::utf8_crc32_iterator(crc32 &crc)
    : m_Itr(crc)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::utf8_crc32_iterator& m1::utf8_crc32_iterator::operator = (char const ch)
{
    m_Itr = ch;
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::utf8_crc32_iterator& m1::utf8_crc32_iterator::operator = (char32_t const ch)
{
    utf8_encode_next(m_Itr, ch);
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::utf8_crc32_iterator& m1::utf8_crc32_iterator::operator * ()
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::utf8_crc32_iterator& m1::utf8_crc32_iterator::operator ++ ()
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::utf8_crc32_iterator m1::utf8_crc32_iterator::operator ++ (int)
{
    utf8_crc32_iterator result = *this;
    ++(*this);
    return result;;
}

// ====================================================================================================================
