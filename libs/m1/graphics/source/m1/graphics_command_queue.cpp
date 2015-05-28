#include "m1/graphics_command_queue.hpp"
#include "m1/graphics_command_queue_impl.hpp"

// ======================================================================================================

m1::graphics_command_queue::graphics_command_queue(std::unique_ptr<graphics_command_queue_impl> impl_ptr)
    : m_ImplPtr(std::move(impl_ptr))
{
}

// ======================================================================================================
