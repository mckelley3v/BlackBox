#include "m1/crc32.hpp"

// =====================================================================================================================

/*explicit*/ m1::crc32_combine_iterator::crc32_combine_iterator(crc32 &crc)
    : m_CrcPtr(&crc)
{
    *m_CrcPtr = crc32_seed();
}

// ---------------------------------------------------------------------------------------------------------------------

m1::crc32_combine_iterator& m1::crc32_combine_iterator::operator = (std::uint8_t const byte)
{
    *m_CrcPtr = calc_crc32(*m_CrcPtr, byte);
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

// =====================================================================================================================
