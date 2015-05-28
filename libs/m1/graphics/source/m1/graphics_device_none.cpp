 #include "m1/graphics_device_none.hpp"
 #include "m1/graphics_command_queue_none.hpp"

// ======================================================================================================

/*virtual*/ m1::graphics_api m1::graphics_device_none::get_api() const /*override*/
{
    return graphics_api::none;
}

// -----------------------------------------------------------------------------------------------------

/*virtual*/ std::unique_ptr<m1::graphics_command_queue_impl> m1::graphics_device_none::make_command_queue_impl() const /*override*/
{
    return std::make_unique<m1::graphics_command_queue_none>();
}

// -----------------------------------------------------------------------------------------------------

/*virtual*/ void m1::graphics_device_none::execute(graphics_command_queue const &/*queue*/) /*override*/
{
    // intentionally empty
}

// ======================================================================================================
