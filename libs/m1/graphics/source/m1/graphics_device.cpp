#include "m1/graphics_device.hpp"
#include "m1/graphics_device_impl.hpp"
#include "m1/graphics_device_none.hpp"
#include "m1/graphics_command_queue.hpp"
#include "m1/graphics_command_queue_impl.hpp"
//#include "m1/d3d_11/graphics_device_d3d_11.hpp"
//#include "m1/d3d_12/graphics_device_d3d_12.hpp"
//#include "m1/gl_2_1/graphics_device_gl_2_1.hpp"
//#include "m1/gl_3_3_core/graphics_device_gl_3_3_core.hpp"
//#include "m1/gl_4_4_core/graphics_device_gl_4_4_core.hpp"
//#include "m1/gles_2_0/graphics_device_gles_2_0.hpp"
//#include "m1/gles_3_1/graphics_device_gles_3_1.hpp"
//#include "m1/vk_1_0/graphics_device_vk_1_0.hpp"

// ======================================================================================================

// typedef any unsupported APIs to graphics_device_none

namespace m1
{
#ifndef M1_GRAPHICS_DEVICE_D3D_11_HPP
    typedef graphics_device_none graphics_device_d3d_11;
#endif

#ifndef M1_GRAPHICS_DEVICE_D3D_12_HPP
    typedef graphics_device_none graphics_device_d3d_12;
#endif

#ifndef M1_GRAPHICS_DEVICE_GL_2_1_HPP
    typedef graphics_device_none graphics_device_gl_2_1;
#endif

#ifndef M1_GRAPHICS_DEVICE_GL_3_3_CORE_HPP
    typedef graphics_device_none graphics_device_gl_3_3_core;
#endif

#ifndef M1_GRAPHICS_DEVICE_GL_4_4_CORE_HPP
    typedef graphics_device_none graphics_device_gl_4_4_core;
#endif

#ifndef M1_GRAPHICS_DEVICE_GLES_2_0_HPP
    typedef graphics_device_none graphics_device_gles_2_0;
#endif

#ifndef M1_GRAPHICS_DEVICE_GLES_3_1_HPP
    typedef graphics_device_none graphics_device_gles_3_1;
#endif

#ifndef M1_GRAPHICS_DEVICE_VK_1_0_HPP
    typedef graphics_device_none graphics_device_vk_1_0;
#endif
} // namespace m1

// ======================================================================================================

/*explicit*/ m1::graphics_device::graphics_device(graphics_api const api)
    : m_ImplPtr{}
{
    switch(api)
    {
        case graphics_api::none:
            m_ImplPtr = std::make_unique<graphics_device_none>();
            break;

        case graphics_api::d3d_11:
            m_ImplPtr = std::make_unique<graphics_device_d3d_11>();
            break;

        case graphics_api::d3d_12:
            m_ImplPtr = std::make_unique<graphics_device_d3d_12>();
            break;

        case graphics_api::gl_2_1:
            m_ImplPtr = std::make_unique<graphics_device_gl_2_1>();
            break;

        case graphics_api::gl_3_3_core:
            m_ImplPtr = std::make_unique<graphics_device_gl_3_3_core>();
            break;

        case graphics_api::gl_4_4_core:
            m_ImplPtr = std::make_unique<graphics_device_gl_4_4_core>();
            break;

        case graphics_api::gles_2_0:
            m_ImplPtr = std::make_unique<graphics_device_gles_2_0>();
            break;

        case graphics_api::gles_3_1:
            m_ImplPtr = std::make_unique<graphics_device_gles_3_1>();
            break;

        case graphics_api::vk_1_0:
            m_ImplPtr = std::make_unique<graphics_device_vk_1_0>();
            break;
    }
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_api m1::graphics_device::get_api() const
{
    return m_ImplPtr->get_api();
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_command_queue m1::graphics_device::make_command_queue() const
{
    return graphics_command_queue(m_ImplPtr->make_command_queue_impl());
}

// ------------------------------------------------------------------------------------------------------

void m1::graphics_device::execute(graphics_command_queue const &queue)
{
    m_ImplPtr->execute(queue);
}

// ======================================================================================================
