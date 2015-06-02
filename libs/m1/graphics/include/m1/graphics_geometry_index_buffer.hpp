#ifndef M1_GRAPHICS_GEOMETRY_INDEX_BUFFER_HPP
#define M1_GRAPHICS_GEOMETRY_INDEX_BUFFER_HPP

#include "m1/graphics_memory_buffer.hpp"

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_geometry_index_buffer_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_geometry_index_buffer
        : public graphics_memory_buffer
    {
    friend class graphics_device;
    public:
        graphics_geometry_index_buffer(graphics_geometry_index_buffer &&rhs) = default;
        graphics_geometry_index_buffer(graphics_geometry_index_buffer const &rhs) = default;
        graphics_geometry_index_buffer& operator = (graphics_geometry_index_buffer &&rhs) = default;
        graphics_geometry_index_buffer& operator = (graphics_geometry_index_buffer const &rhs) = default;
        virtual ~graphics_geometry_index_buffer() override = default;

    private:
        graphics_geometry_index_buffer() = delete;
        explicit graphics_geometry_index_buffer(std::shared_ptr<graphics_geometry_index_buffer_impl> const &impl_ptr);

        graphics_geometry_index_buffer_impl* impl_ptr();
        graphics_geometry_index_buffer_impl const* get_impl_ptr() const;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_GEOMETRY_INDEX_BUFFER_HPP
