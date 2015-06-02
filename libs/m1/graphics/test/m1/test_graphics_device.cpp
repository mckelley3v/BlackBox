#include "catch.hpp"
#include "m1/graphics_device.hpp"

TEST_CASE("Test m1::graphics_device", "[m1_graphics]")
{
    m1::graphics_device device(m1::graphics_api::gl_2_1);
    REQUIRE(device.get_api() == m1::graphics_api::gl_2_1);
}
