#ifndef M1_GRAPHICS_TEXTURE_SOURCE_HPP
#define M1_GRAPHICS_TEXTURE_SOURCE_HPP

// =====================================================================================================================

namespace m1
{
    // =================================================================================================================

    class graphics_texture_source_1D
    {
    public:
        graphics_texture_source_1D(graphics_texture_source_1D &&rhs) = default;
        graphics_texture_source_1D& operator = (graphics_texture_source_1D &&rhs) = default;
        virtual ~graphics_texture_source_1D() = default;

    private:
        graphics_texture_source_1D() = delete;
        graphics_texture_source_1D(graphics_texture_source_1D const &rhs) = default;
        graphics_texture_source_1D& operator = (graphics_texture_source_1D const &rhs) = default;

        // members:
    };

    // =================================================================================================================

    class graphics_texture_source_2D
    {
    public:
        graphics_texture_source_2D(graphics_texture_source_2D &&rhs) = default;
        graphics_texture_source_2D& operator = (graphics_texture_source_2D &&rhs) = default;
        virtual ~graphics_texture_source_2D() = default;

    private:
        graphics_texture_source_2D() = delete;
        graphics_texture_source_2D(graphics_texture_source_2D const &rhs) = default;
        graphics_texture_source_2D& operator = (graphics_texture_source_2D const &rhs) = default;

        // members:
    };

    // =================================================================================================================

    class graphics_texture_source_3D
    {
    public:
        graphics_texture_source_3D(graphics_texture_source_3D &&rhs) = default;
        graphics_texture_source_3D& operator = (graphics_texture_source_3D &&rhs) = default;
        virtual ~graphics_texture_source_3D() = default;

    private:
        graphics_texture_source_3D() = delete;
        graphics_texture_source_3D(graphics_texture_source_3D const &rhs) = default;
        graphics_texture_source_3D& operator = (graphics_texture_source_3D const &rhs) = default;

        // members:
    };

    // =================================================================================================================

    class graphics_texture_source_cube
    {
    public:
        graphics_texture_source_cube(graphics_texture_source_cube &&rhs) = default;
        graphics_texture_source_cube& operator = (graphics_texture_source_cube &&rhs) = default;
        virtual ~graphics_texture_source_cube() = default;

    private:
        graphics_texture_source_cube() = delete;
        graphics_texture_source_cube(graphics_texture_source_cube const &rhs) = default;
        graphics_texture_source_cube& operator = (graphics_texture_source_cube const &rhs) = default;

        // members:
    };

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

#endif // M1_GRAPHICS_TEXTURE_SOURCE_HPP
