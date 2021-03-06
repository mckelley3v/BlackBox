#include "m1/graphics_command_queue.hpp"
#include "m1/impl/graphics_command_queue_impl.hpp"

// ======================================================================================================

/*explicit*/ m1::graphics_command_queue::graphics_command_queue(std::shared_ptr<graphics_command_queue_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
}

// ======================================================================================================
