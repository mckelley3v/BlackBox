#include "m1/log.hpp"
#include <ostream>

// =====================================================================================================================

m1::log::log(std::ostream &message_out,
             std::ostream &warning_out,
             std::ostream &error_out)
    : m_MessageCount(0)
    , m_WarningCount(0)
    , m_ErrorCount(0)
    , m_MessageOut(message_out)
    , m_WarningOut(warning_out)
    , m_ErrorOut(error_out)
{
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::log::clear()
{
    m_MessageCount = 0;
    m_WarningCount = 0;
    m_ErrorCount = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

int m1::log::get_message_count() const
{
    return m_MessageCount;
}

// ---------------------------------------------------------------------------------------------------------------------

int m1::log::get_warning_count() const
{
    return m_WarningCount;
}

// ---------------------------------------------------------------------------------------------------------------------

int m1::log::get_error_count() const
{
    return m_ErrorCount;
}

// ---------------------------------------------------------------------------------------------------------------------

std::ostream& m1::log::message(char const * const file, int const line, char const * const func)
{
    ++m_MessageCount;
    return m_MessageOut << file << "(" << line << ") -- " << func << " : message: ";
}

// ---------------------------------------------------------------------------------------------------------------------

std::ostream& m1::log::warning(char const * const file, int const line, char const * const func)
{
    ++m_WarningCount;
    return m_WarningOut << file << "(" << line << ") -- " << func << " : warning: ";
}

// ---------------------------------------------------------------------------------------------------------------------

std::ostream& m1::log::error(char const * const file, int const line, char const * const func)
{
    ++m_ErrorCount;
    return m_ErrorOut << file << "(" << line << ") -- " << func << " : error: ";
}

// =====================================================================================================================
