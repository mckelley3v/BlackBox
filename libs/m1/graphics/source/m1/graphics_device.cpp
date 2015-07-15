#include "m1/graphics_device.hpp"
#include "m1/impl/graphics_device_impl.hpp"
//#include "m1/d3d_11/graphics_device_d3d_11.hpp"
//#include "m1/d3d_12/graphics_device_d3d_12.hpp"
//#include "m1/gl_2/graphics_device_gl_2.hpp"
//#include "m1/gl_3/graphics_device_gl_3.hpp"
//#include "m1/gl_4/graphics_device_gl_4.hpp"
//#include "m1/gles_2/graphics_device_gles_2.hpp"
//#include "m1/gles_3/graphics_device_gles_3.hpp"
//#include "m1/vk_1/graphics_device_vk_1.hpp"
#include "m1/impl/graphics_command_queue_impl.hpp"
#include "m1/impl/graphics_draw_target_impl.hpp"
#include "m1/impl/graphics_memory_buffer_impl.hpp"
#include "m1/impl/graphics_geometry_index_buffer_impl.hpp"
#include "m1/impl/graphics_geometry_vertex_buffer_impl.hpp"
#include "m1/impl/graphics_shader_const_buffer_impl.hpp"
#include "m1/impl/graphics_shader_mutable_buffer_impl.hpp"
#include "m1/impl/graphics_shader_instance_buffer_impl.hpp"
#include "m1/impl/graphics_texture_impl.hpp"
#include "m1/graphics_command_queue.hpp"
#include "m1/graphics_texture.hpp"
#include "m1/graphics_draw_target.hpp"
#include "m1/graphics_memory_buffer.hpp"
#include "m1/graphics_geometry_index_buffer.hpp"
#include "m1/graphics_geometry_vertex_buffer.hpp"
#include "m1/graphics_shader_const_buffer.hpp"
#include "m1/graphics_shader_mutable_buffer.hpp"
#include "m1/graphics_shader_instance_buffer.hpp"
#include <cassert>

// ======================================================================================================

/*explicit*/ m1::graphics_device::graphics_device(graphics_api const api)
    : m_ImplPtr{}
{
    switch(api)
    {
        case graphics_api::none:
            break;

        case graphics_api::d3d_11:
        #ifdef M1_GRAPHICS_DEVICE_D3D_11_HPP
            m_ImplPtr = std::make_shared<graphics_device_d3d_11>();
        #endif
            break;

        case graphics_api::d3d_12:
        #ifdef M1_GRAPHICS_DEVICE_D3D_12_HPP
            m_ImplPtr = std::make_shared<graphics_device_d3d_12>();
        #endif
            break;

        case graphics_api::gl_2:
        #ifdef M1_GRAPHICS_DEVICE_GL_2_HPP
            m_ImplPtr = std::make_shared<graphics_device_gl_2>();
        #endif
            break;

        case graphics_api::gl_3:
        #ifdef M1_GRAPHICS_DEVICE_GL_3_HPP
            m_ImplPtr = std::make_shared<graphics_device_gl_3>();
        #endif
            break;

        case graphics_api::gl_4:
        #ifdef M1_GRAPHICS_DEVICE_GL_4_HPP
            m_ImplPtr = std::make_shared<graphics_device_gl_4>();
        #endif
            break;

        case graphics_api::gles_2:
        #ifdef M1_GRAPHICS_DEVICE_GLES_2_HPP
            m_ImplPtr = std::make_shared<graphics_device_gles_2>();
        #endif
            break;

        case graphics_api::gles_3:
        #ifdef M1_GRAPHICS_DEVICE_GLES_3_HPP
            m_ImplPtr = std::make_shared<graphics_device_gles_3>();
        #endif
            break;

        case graphics_api::vk_1:
        #ifdef M1_GRAPHICS_DEVICE_VK_1_HPP
            m_ImplPtr = std::make_shared<graphics_device_vk_1>();
        #endif
            break;
    }
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_api m1::graphics_device::get_api() const
{
    return m_ImplPtr ? m_ImplPtr->get_api() : graphics_api::none;
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_command_queue m1::graphics_device::make_command_queue()
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_command_queue(m_ImplPtr->make_command_queue_impl());
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_draw_target m1::graphics_device::make_draw_target(graphics_draw_target_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_draw_target(m_ImplPtr->make_draw_target(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_geometry_index_buffer m1::graphics_device::make_geometry_index_buffer(graphics_geometry_index_buffer_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_geometry_index_buffer(m_ImplPtr->make_geometry_index_buffer(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_geometry_vertex_buffer m1::graphics_device::make_geometry_vertex_buffer(graphics_geometry_vertex_buffer_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_geometry_vertex_buffer(m_ImplPtr->make_geometry_vertex_buffer(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_memory_buffer m1::graphics_device::make_memory_buffer(graphics_memory_buffer_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_memory_buffer(m_ImplPtr->make_memory_buffer(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_shader_const_buffer m1::graphics_device::make_shader_const_buffer(graphics_shader_const_buffer_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_shader_const_buffer(m_ImplPtr->make_shader_const_buffer(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_shader_mutable_buffer m1::graphics_device::make_shader_mutable_buffer(graphics_shader_mutable_buffer_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_shader_mutable_buffer(m_ImplPtr->make_shader_mutable_buffer(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_shader_instance_buffer m1::graphics_device::make_shader_instance_buffer(graphics_shader_instance_buffer_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_shader_instance_buffer(m_ImplPtr->make_shader_instance_buffer(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_texture_1D m1::graphics_device::make_texture(graphics_texture_1D_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_texture_1D(m_ImplPtr->make_texture(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_texture_2D m1::graphics_device::make_texture(graphics_texture_2D_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_texture_2D(m_ImplPtr->make_texture(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_texture_3D m1::graphics_device::make_texture(graphics_texture_3D_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_texture_3D(m_ImplPtr->make_texture(definition));
}

// ------------------------------------------------------------------------------------------------------

m1::graphics_texture_cube m1::graphics_device::make_texture(graphics_texture_cube_definition const &definition)
{
    assert(m_ImplPtr && "Invalid graphics_device");
    return graphics_texture_cube(m_ImplPtr->make_texture(definition));
}

// ------------------------------------------------------------------------------------------------------

void m1::graphics_device::execute(graphics_command_queue const &queue)
{
    m_ImplPtr->execute(queue);
}

// ======================================================================================================
