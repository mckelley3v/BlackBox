 #include "m1/graphics_device_none.hpp"
 #include <cassert>

// ======================================================================================================

/*virtual*/ m1::graphics_api m1::graphics_device_none::get_api() const /*override*/
{
    return graphics_api::none;
}

// -----------------------------------------------------------------------------------------------------

/*virtual*/ void m1::graphics_device_none::execute(graphics_command_queue const &/*queue*/) /*override*/
{
    // intentionally empty
}

// ======================================================================================================
