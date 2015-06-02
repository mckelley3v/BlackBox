#ifndef M1_GRAPHICS_TEXTURE_SOURCE_HPP
#define M1_GRAPHICS_TEXTURE_SOURCE_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_texture_source_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_texture_source
    {
    friend class graphics_device;
    public:
        graphics_texture_source(graphics_texture_source &&rhs) = default;
        graphics_texture_source(graphics_texture_source const &rhs) = default;
        graphics_texture_source& operator = (graphics_texture_source &&rhs) = default;
        graphics_texture_source& operator = (graphics_texture_source const &rhs) = default;
        virtual ~graphics_texture_source() = default;

    protected:
        explicit graphics_texture_source(std::shared_ptr<graphics_texture_source_impl> const &impl_ptr);

    private:
        graphics_texture_source() = delete;

        // members:
        std::shared_ptr<graphics_texture_source_impl> m_ImplPtr;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_TEXTURE_SOURCE_HPP
