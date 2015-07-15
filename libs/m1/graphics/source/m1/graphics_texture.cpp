#include "m1/graphics_texture.hpp"

// =====================================================================================================================

/*explicit*/ m1::graphics_texture_1D::graphics_texture_1D(std::shared_ptr<graphics_texture_1D_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
}

// =====================================================================================================================

/*explicit*/ m1::graphics_texture_2D::graphics_texture_2D(std::shared_ptr<graphics_texture_2D_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
}

// =====================================================================================================================

/*explicit*/ m1::graphics_texture_3D::graphics_texture_3D(std::shared_ptr<graphics_texture_3D_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
}

// =====================================================================================================================

/*explicit*/ m1::graphics_texture_cube::graphics_texture_cube(std::shared_ptr<graphics_texture_cube_impl> const &impl_ptr)
    : m_ImplPtr(impl_ptr)
{
}

// =====================================================================================================================
