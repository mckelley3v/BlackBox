#ifndef M1_GRAPHICS_TEXTURE_HPP
#define M1_GRAPHICS_TEXTURE_HPP

#include "m1/graphics_state.hpp"
#include <memory>

// =====================================================================================================================

namespace m1
{
    // =================================================================================================================

    enum class graphics_texture_format
    {
        //r32g32b32_typeless,
        r32g32b32_float,
        r32g32b32_uint,
        r32g32b32_sint,
        //r16g16b16a16_typeless,
        r16g16b16a16_float,
        r16g16b16a16_unorm,
        r16g16b16a16_uint,
        r16g16b16a16_snorm,
        r16g16b16a16_sint,
        //r32g32_typeless,
        r32g32_float,
        r32g32_uint,
        r32g32_sint,
        //r32g8x24_typeless,
        d32_float_s8x24_uint,
        //r32_float_x8x24_typeless,
        //x32_typeless_g8x24_uint,
        //r10g10b10a2_typeless,
        r10g10b10a2_unorm,
        r10g10b10a2_uint,
        r11g11b10_float,
        //r8g8b8a8_typeless,
        r8g8b8a8_unorm,
        r8g8b8a8_unorm_srgb,
        r8g8b8a8_uint,
        r8g8b8a8_snorm,
        r8g8b8a8_sint,
        //r16g16_typeless,
        r16g16_float,
        r16g16_unorm,
        r16g16_uint,
        r16g16_snorm,
        r16g16_sint,
        //r32_typeless,
        d32_float,
        r32_float,
        r32_uint,
        r32_sint,
        //r24g8_typeless,
        d24_unorm_s8_uint,
        //r24_unorm_x8_typeless,
        //x24_typeless_g8_uint,
        //r8g8_typeless,
        r8g8_unorm,
        r8g8_uint,
        r8g8_snorm,
        r8g8_sint,
        //r16_typeless,
        r16_float,
        d16_unorm,
        r16_unorm,
        r16_uint,
        r16_snorm,
        r16_sint,
        //r8_typeless,
        r8_unorm,
        r8_uint,
        r8_snorm,
        r8_sint,
        a8_unorm,
        r1_unorm,
        r9g9b9e5_sharedexp,
        r8g8_b8g8_unorm,
        g8r8_g8b8_unorm,
        //bc1_typeless,
        bc1_unorm,
        bc1_unorm_srgb,
        //bc2_typeless,
        bc2_unorm,
        bc2_unorm_srgb,
        //bc3_typeless,
        bc3_unorm,
        bc3_unorm_srgb,
        //bc4_typeless,
        bc4_unorm,
        bc4_snorm,
        //bc5_typeless,
        bc5_unorm,
        bc5_snorm,
        b5g6r5_unorm,
        b5g5r5a1_unorm,
        b8g8r8a8_unorm,
        b8g8r8x8_unorm,
        r10g10b10_xr_bias_a2_unorm,
        //b8g8r8a8_typeless,
        b8g8r8a8_unorm_srgb,
        //b8g8r8x8_typeless,
        b8g8r8x8_unorm_srgb,
        //bc6h_typeless,
        bc6h_uf16,
        bc6h_sf16,
        //bc7_typeless,
        bc7_unorm,
        bc7_unorm_srgb,
        //ayuv,
        //y410,
        //y416,
        //nv12,
        //p010,
        //p016,
        //420_opaque,
        //yuy2,
        //y210,
        //y216,
        //nv11,
        //ai44,
        //ia44,
        //p8,
        //a8p8,
        //b4g4r4a4_unorm,
        //p208,
        //v208,
        //v408,
        astc_4x4_unorm,
        astc_4x4_unorm_srgb,
        //astc_5x4_typeless,
        astc_5x4_unorm,
        astc_5x4_unorm_srgb,
        //astc_5x5_typeless,
        astc_5x5_unorm,
        astc_5x5_unorm_srgb,
        //astc_6x5_typeless,
        astc_6x5_unorm,
        astc_6x5_unorm_srgb,
        //astc_6x6_typeless,
        astc_6x6_unorm,
        astc_6x6_unorm_srgb,
        //astc_8x5_typeless,
        astc_8x5_unorm,
        astc_8x5_unorm_srgb,
        //astc_8x6_typeless,
        astc_8x6_unorm,
        astc_8x6_unorm_srgb,
        //astc_8x8_typeless,
        astc_8x8_unorm,
        astc_8x8_unorm_srgb,
        //astc_10x5_typeless,
        astc_10x5_unorm,
        astc_10x5_unorm_srgb,
        //astc_10x6_typeless,
        astc_10x6_unorm,
        astc_10x6_unorm_srgb,
        //astc_10x8_typeless,
        astc_10x8_unorm,
        astc_10x8_unorm_srgb,
        //astc_10x10_typeless,
        astc_10x10_unorm,
        astc_10x10_unorm_srgb,
        //astc_12x10_typeless,
        astc_12x10_unorm,
        astc_12x10_unorm_srgb,
        //astc_12x12_typeless,
        astc_12x12_unorm,
        astc_12x12_unorm_srgb,
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_texture_type
    {
        x1D,
        x2D,
        x3D,
        cube,
    };

    // -----------------------------------------------------------------------------------------------------------------

    typedef unsigned char graphics_texture_options_mask;
    struct graphics_texture_options_bits
    {
        static constexpr graphics_texture_options_mask const enable_draw_target_bit = 0b0001; // allows usage as a draw target attachment
        static constexpr graphics_texture_options_mask const enable_cpu_access_bit  = 0b0010; // forces cpu friendly internal layout
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_texture_cube_face
    {
        positive_x,
        negative_x,
        positive_y,
        negative_y,
        positive_z,
        negative_z,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_texture_1D_definition
    {
        graphics_texture_format format;
        int width;
        int array_size;
        int mip_count;
        graphics_texture_options_mask options;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_texture_2D_definition
    {
        graphics_texture_format format;
        int width;
        int height;
        int array_size;
        int mip_count;
        graphics_texture_options_mask options;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_texture_3D_definition
    {
        graphics_texture_format format;
        int width;
        int height;
        int depth;
        int mip_count;
        graphics_texture_options_mask options;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_texture_cube_definition
    {
        graphics_texture_format format;
        int width;
        int height;
        int array_size;
        int mip_count;
        graphics_texture_options_mask options;
    };

    // =================================================================================================================

    struct graphics_texture_depth_range
    {
        int index;
        int count;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_texture_array_range
    {
        int index;
        int count;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_texture_mip_range
    {
        int index;
        int count;
    };

    // =================================================================================================================

    class graphics_texture_source_1D;
    class graphics_texture_source_2D;
    class graphics_texture_source_3D;
    class graphics_texture_source_cube;
    class graphics_texture_color_target_2D;
    class graphics_texture_depth_target_2D;

    // =================================================================================================================

    class graphics_texture_1D_impl;
    class graphics_texture_2D_impl;
    class graphics_texture_3D_impl;
    class graphics_texture_cube_impl;

    // =================================================================================================================

    class graphics_texture_1D
    {
    friend class graphics_device;
    public:
        graphics_texture_1D(graphics_texture_1D &&rhs) = default;
        graphics_texture_1D(graphics_texture_1D const &rhs) = default;
        graphics_texture_1D& operator = (graphics_texture_1D &&rhs) = default;
        graphics_texture_1D& operator = (graphics_texture_1D const &rhs) = default;
        virtual ~graphics_texture_1D() = default;

        // properties:
        graphics_texture_1D_definition const& get_definition() const;
        graphics_texture_format get_format() const;
        int get_width() const;
        int get_array_size() const;
        int get_mip_count() const;

        // methods:
        //std::future<void> set_image_data(graphics_command_queue &queue,
        //                                 int array_index,
        //                                 int mip_level,
        //                                 void const *data_ptr,
        //                                 int data_size);

        graphics_texture_source_1D lock_as_source() const;
        graphics_texture_source_1D lock_as_source(graphics_texture_array_range const &array_range) const;
        graphics_texture_source_1D lock_as_source(graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_1D lock_as_source(graphics_texture_array_range const &array_range,
                                                  graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_1D lock_as_source(graphics_texture_mip_range const &mip_range,
                                                  graphics_texture_array_range const &array_range) const;

    private:
        graphics_texture_1D() = delete;
        explicit graphics_texture_1D(std::shared_ptr<graphics_texture_1D_impl> const &impl_ptr);

        // members:
        std::shared_ptr<graphics_texture_1D_impl> m_ImplPtr;
    };

    // =================================================================================================================

    class graphics_texture_2D
    {
    friend class graphics_device;
    public:
        graphics_texture_2D(graphics_texture_2D &&rhs) = default;
        graphics_texture_2D(graphics_texture_2D const &rhs) = default;
        graphics_texture_2D& operator = (graphics_texture_2D &&rhs) = default;
        graphics_texture_2D& operator = (graphics_texture_2D const &rhs) = default;
        virtual ~graphics_texture_2D() = default;

        // properties:
        graphics_texture_2D_definition const& get_definition() const;
        graphics_texture_format get_format() const;
        int get_width() const;
        int get_height() const;
        int get_array_size() const;
        int get_mip_count() const;

        // methods:
        //std::future<void> set_image_data(graphics_command_queue &queue,
        //                                 int array_index,
        //                                 int mip_level,
        //                                 void const *data_ptr,
        //                                 int data_size);

        graphics_texture_source_2D lock_as_source() const;
        graphics_texture_source_2D lock_as_source(graphics_texture_array_range const &array_range) const;
        graphics_texture_source_2D lock_as_source(graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_2D lock_as_source(graphics_texture_array_range const &array_range,
                                                  graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_2D lock_as_source(graphics_texture_mip_range const &mip_range,
                                                  graphics_texture_array_range const &array_range) const;

        graphics_texture_color_target_2D lock_as_color_target(int array_index,
                                                              int mip_index);

        graphics_texture_depth_target_2D lock_as_depth_target(int array_index,
                                                              int mip_index);

    private:
        graphics_texture_2D() = delete;
        explicit graphics_texture_2D(std::shared_ptr<graphics_texture_2D_impl> const &impl_ptr);

        // members:
        std::shared_ptr<graphics_texture_2D_impl> m_ImplPtr;
    };

    // =================================================================================================================

    class graphics_texture_3D
    {
    friend class graphics_device;
    public:
        graphics_texture_3D(graphics_texture_3D &&rhs) = default;
        graphics_texture_3D(graphics_texture_3D const &rhs) = default;
        graphics_texture_3D& operator = (graphics_texture_3D &&rhs) = default;
        graphics_texture_3D& operator = (graphics_texture_3D const &rhs) = default;
        virtual ~graphics_texture_3D() = default;

        // properties:
        graphics_texture_3D_definition const& get_definition() const;
        graphics_texture_format get_format() const;
        int get_width() const;
        int get_height() const;
        int get_depth() const;
        int get_mip_count() const;

        // methods:
        //std::future<void> set_image_data(graphics_command_queue &queue,
        //                                 int depth_index,
        //                                 int mip_level,
        //                                 void const *data_ptr,
        //                                 int data_size);

        graphics_texture_source_3D lock_as_source() const;
        graphics_texture_source_3D lock_as_source(graphics_texture_depth_range const &depth_range) const;
        graphics_texture_source_3D lock_as_source(graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_3D lock_as_source(graphics_texture_depth_range const &depth_range,
                                                  graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_3D lock_as_source(graphics_texture_mip_range const &mip_range,
                                                  graphics_texture_depth_range const &depth_range) const;

        graphics_texture_color_target_2D lock_as_color_target(int depth_index,
                                                              int mip_index);

        graphics_texture_depth_target_2D lock_as_depth_target(int depth_index,
                                                              int mip_index);

    private:
        graphics_texture_3D() = delete;
        explicit graphics_texture_3D(std::shared_ptr<graphics_texture_3D_impl> const &impl_ptr);

        // members:
        std::shared_ptr<graphics_texture_3D_impl> m_ImplPtr;
    };

    // =================================================================================================================

    class graphics_texture_cube
    {
    friend class graphics_device;
    public:
        graphics_texture_cube(graphics_texture_cube &&rhs) = default;
        graphics_texture_cube(graphics_texture_cube const &rhs) = default;
        graphics_texture_cube& operator = (graphics_texture_cube &&rhs) = default;
        graphics_texture_cube& operator = (graphics_texture_cube const &rhs) = default;
        virtual ~graphics_texture_cube() = default;

        // properties:
        graphics_texture_cube_definition const& get_definition() const;
        graphics_texture_format get_format() const;
        int get_width() const;
        int get_height() const;
        int get_array_size() const;
        int get_mip_count() const;

        // methods:
        //std::future<void> set_image_data(graphics_command_queue &queue,
        //                                 graphics_texture_cube_face cube_face,
        //                                 int array_index,
        //                                 int mip_level,
        //                                 void const *data_ptr,
        //                                 int data_size);

        graphics_texture_source_cube lock_as_source() const;
        graphics_texture_source_cube lock_as_source(graphics_texture_array_range const &array_range) const;
        graphics_texture_source_cube lock_as_source(graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_cube lock_as_source(graphics_texture_array_range const &array_range,
                                                    graphics_texture_mip_range const &mip_range) const;
        graphics_texture_source_cube lock_as_source(graphics_texture_mip_range const &mip_range,
                                                    graphics_texture_array_range const &array_range) const;

        graphics_texture_color_target_2D lock_as_color_target(graphics_texture_cube_face cube_face,
                                                              int array_index,
                                                              int mip_index);

        graphics_texture_depth_target_2D lock_as_depth_target(graphics_texture_cube_face cube_face,
                                                              int array_index,
                                                              int mip_index);

    private:
        graphics_texture_cube() = delete;
        explicit graphics_texture_cube(std::shared_ptr<graphics_texture_cube_impl> const &impl_ptr);

        // members:
        std::shared_ptr<graphics_texture_cube_impl> m_ImplPtr;
    };

    // =================================================================================================================
} // namespace m1

#endif // M1_GRAPHICS_TEXTURE_HPP
