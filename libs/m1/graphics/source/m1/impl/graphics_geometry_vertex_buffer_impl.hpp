#ifndef M1_GRAPHICS_GEOMETRY_VERTEX_BUFFER_IMPL_HPP
#define M1_GRAPHICS_GEOMETRY_VERTEX_BUFFER_IMPL_HPP

#include "m1/impl/graphics_memory_buffer_impl.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_geometry_vertex_buffer_impl
        : public graphics_memory_buffer_impl
    {
    public:
        graphics_geometry_vertex_buffer_impl() = default;
        virtual ~graphics_geometry_vertex_buffer_impl() = default;

    private:
        graphics_geometry_vertex_buffer_impl(graphics_geometry_vertex_buffer_impl &&rhs) = delete;
        graphics_geometry_vertex_buffer_impl(graphics_geometry_vertex_buffer_impl const &rhs) = delete;
        graphics_geometry_vertex_buffer_impl& operator = (graphics_geometry_vertex_buffer_impl &&rhs) = delete;
        graphics_geometry_vertex_buffer_impl& operator = (graphics_geometry_vertex_buffer_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_GEOMETRY_VERTEX_BUFFER_IMPL_HPP
