#ifndef M1_GRAPHICS_GEOMETRY_VERTEX_BUFFER_HPP
#define M1_GRAPHICS_GEOMETRY_VERTEX_BUFFER_HPP

#include "m1/graphics_memory_buffer.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_geometry_vertex_buffer_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_geometry_vertex_buffer
        : public graphics_memory_buffer
    {
    friend class graphics_device;
    public:
        graphics_geometry_vertex_buffer(graphics_geometry_vertex_buffer &&rhs) = default;
        graphics_geometry_vertex_buffer(graphics_geometry_vertex_buffer const &rhs) = default;
        graphics_geometry_vertex_buffer& operator = (graphics_geometry_vertex_buffer &&rhs) = default;
        graphics_geometry_vertex_buffer& operator = (graphics_geometry_vertex_buffer const &rhs) = default;
        virtual ~graphics_geometry_vertex_buffer() override = default;

    private:
        graphics_geometry_vertex_buffer() = delete;
        explicit graphics_geometry_vertex_buffer(std::shared_ptr<graphics_geometry_vertex_buffer_impl> const &impl_ptr);

        graphics_geometry_vertex_buffer_impl* impl_ptr();
        graphics_geometry_vertex_buffer_impl const* get_impl_ptr() const;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_GEOMETRY_VERTEX_BUFFER_HPP
