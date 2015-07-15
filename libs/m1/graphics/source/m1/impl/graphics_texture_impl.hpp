#ifndef M1_GRAPHICS_TEXTURE_IMPL_HPP
#define M1_GRAPHICS_TEXTURE_IMPL_HPP

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_texture_impl
    {
    public:
        graphics_texture_impl() = default;
        virtual ~graphics_texture_impl() = default;

    private:
        graphics_texture_impl(graphics_texture_impl &&rhs) = delete;
        graphics_texture_impl(graphics_texture_impl const &rhs) = delete;
        graphics_texture_impl& operator = (graphics_texture_impl &&rhs) = delete;
        graphics_texture_impl& operator = (graphics_texture_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_TEXTURE_IMPL_HPP
