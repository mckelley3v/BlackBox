#include "m1/signal.hpp"

// ====================================================================================================================

void m1::connection_impl::enable()
{
    m_IsEnabled = true;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::connection_impl::disable()
{
    m_IsEnabled = false;
}

// --------------------------------------------------------------------------------------------------------------------

void m1::connection_impl::set_enabled(bool value)
{
    m_IsEnabled = value;
}

// --------------------------------------------------------------------------------------------------------------------

bool m1::connection_impl::is_enabled() const
{
    return m_IsEnabled;
}

// ====================================================================================================================
