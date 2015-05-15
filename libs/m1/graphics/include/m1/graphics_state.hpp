#ifndef M1_GRAPHICS_STATE_HPP
#define M1_GRAPHICS_STATE_HPP

namespace m1
{
    // =================================================================================================================

    struct color4f
    {
        float red;
        float green;
        float blue;
        float alpha;
    };

    // =================================================================================================================

    enum class graphics_fill_mode
    {
        solid,
        wireframe,
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_cull_mode
    {
        back,
        front,
        none,
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_front_face
    {
        ccw,
        cw,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_depth_bias
    {
        int offset;
        float slope_scale;
        float clamp;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_raster_state
    {
        graphics_fill_mode fill_mode;
        graphics_cull_mode cull_mode;
        graphics_front_face front_face;
        graphics_depth_bias depth_bias;
    };

    // =================================================================================================================

    enum class graphics_blend_factor
   {
        zero,
        one,

        source_rgb,
        one_minus_source_rgb,
        source_alpha,
        one_minus_source_alpha,
        source_alpha_saturate,

        source1_rgb,
        one_minus_source1_rgb,
        source1_alpha,
        one_minus_source1_alpha,

        target_rgb,
        one_minus_target_rgb,
        target_alpha,
        one_minus_target_alpha,

        constant_rgb,
        one_minus_constant_rgb,
        constant_alpha,
        one_minus_constant_alpha,
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_blend_func
    {
        add,
        subtract,
        reverse_subtract,
        min,
        max,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_blend_equation
    {
        graphics_blend_factor source_factor;
        graphics_blend_func blend_func;
        graphics_blend_factor target_factor;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_target_blend
    {
        bool enable;
        graphics_blend_equation rgb;
        graphics_blend_equation alpha;
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_logic_op
    {
        source,                     // copy
        zero,                       // clear
        source_bitand_target,       // and
        source_bitand_compl_target, // and_reverse
        compl_source_bitand_target, // and_inverted
        target,                     // noop
        source_bitxor_target,       // xor
        source_bitor_target,        // or
        source_bitnor_target,       // nor
        source_bitxnor_target,      // equiv
        compl_target,               // invert
        source_bitor_compl_target,  // or_reverse
        compl_source,               // copy_inverted
        compl_source_bitor_target,  // or_inverted
        source_bitnand_target,      // nand
        one,                        // set
    };

    // -----------------------------------------------------------------------------------------------------------------

    typedef unsigned char graphics_channel_mask;
    struct graphics_channel_bits
    {
        static constexpr graphics_channel_mask const red_bit   = 0b0001;
        static constexpr graphics_channel_mask const green_bit = 0b0010;
        static constexpr graphics_channel_mask const blue_bit  = 0b0100;
        static constexpr graphics_channel_mask const alpha_bit = 0b1000;
        static constexpr graphics_channel_mask const all       = 0b1111;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_color_target
    {
        graphics_target_blend blend;
        graphics_logic_op logic_op;
        graphics_channel_mask channel_mask;
    };

    // -----------------------------------------------------------------------------------------------------------------

    constexpr static const int graphics_color_target_capacity = 8;

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_color_target_state
    {
        bool enable_alpha_to_coverage;
        bool enable_dual_source_blend;
        color4f blend_constant;
        graphics_color_target targets[graphics_color_target_capacity];
    };

    // =================================================================================================================

    enum class graphics_compare_func
    {
        less,
        less_equal,
        greater,
        greater_equal,
        not_equal,
        always,
        never,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_depth_test
    {
        bool enable_test;
        bool enable_write;
        graphics_compare_func compare_func;
        float clamp_min;
        float clamp_max;
    };

    // -----------------------------------------------------------------------------------------------------------------

    enum class graphics_stencil_op
    {
        keep,
        zero,
        replace,
        inc_clamp,
        dec_clamp,
        invert,
        inc_wrap,
        dec_wrap,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_stencil_face_test
    {
        unsigned char ref_value;
        graphics_compare_func compare_func;
        graphics_stencil_op stencil_pass_depth_pass_op;
        graphics_stencil_op stencil_pass_depth_fail_op;
        graphics_stencil_op stencil_fail_op;
    };

    // -----------------------------------------------------------------------------------------------------------------

    typedef unsigned char graphics_stencil_mask;
    struct graphics_stencil_bits
    {
        static constexpr graphics_stencil_mask const bit_0 = 0b00000001;
        static constexpr graphics_stencil_mask const bit_1 = 0b00000010;
        static constexpr graphics_stencil_mask const bit_2 = 0b00000100;
        static constexpr graphics_stencil_mask const bit_3 = 0b00001000;
        static constexpr graphics_stencil_mask const bit_4 = 0b00010000;
        static constexpr graphics_stencil_mask const bit_5 = 0b00100000;
        static constexpr graphics_stencil_mask const bit_6 = 0b01000000;
        static constexpr graphics_stencil_mask const bit_7 = 0b10000000;
        static constexpr graphics_stencil_mask const all   = 0b11111111;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_stencil_test
    {
        bool enable_test;
        graphics_stencil_mask read_mask;
        graphics_stencil_mask write_mask;
        graphics_stencil_face_test front_face_test;
        graphics_stencil_face_test back_face_test;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_depth_target_state
    {
        bool enable_clip;
        float depth_min;
        float depth_max;
        graphics_depth_test depth_test;
        graphics_stencil_test stencil_test;
    };

    // =================================================================================================================

    enum class graphics_geometry_topology
    {
        point_list,
        line_list,
        line_strip,
        triangle_list,
        triangle_strip,
        rect_list,
        quad_list,
        quad_strip,
        line_list_adjacency,
        line_strip_adjacency,
        triangle_list_adjacency,
        triangle_strip_adjacency,
        tessellator_patch,
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_geometry_state
    {
        graphics_geometry_topology topology;
        int tessellator_patch_point_count;
    };

    // =================================================================================================================

    struct graphics_viewport_state
    {
        int x;
        int y;
        int width;
        int height;
    };

    // =================================================================================================================

    struct graphics_scissor_state
    {
        bool enable;
        int x;
        int y;
        int width;
        int height;
    };

    // =================================================================================================================

    enum class graphics_multisampling_count
    {
        x1,
        x2,
        x4,
        x8,
    };

    // -----------------------------------------------------------------------------------------------------------------

    typedef unsigned char graphics_multisampling_mask;
    struct graphics_multisampling_bits
    {
        static constexpr graphics_multisampling_mask const bit_1 = 0b00000001;
        static constexpr graphics_multisampling_mask const bit_2 = 0b00000010;
        static constexpr graphics_multisampling_mask const bit_3 = 0b00000100;
        static constexpr graphics_multisampling_mask const bit_4 = 0b00001000;
        static constexpr graphics_multisampling_mask const bit_5 = 0b00010000;
        static constexpr graphics_multisampling_mask const bit_6 = 0b00100000;
        static constexpr graphics_multisampling_mask const bit_7 = 0b01000000;
        static constexpr graphics_multisampling_mask const bit_8 = 0b10000000;
        static constexpr graphics_multisampling_mask const all   = 0b11111111;
    };

    // -----------------------------------------------------------------------------------------------------------------

    struct graphics_multisampling_state
    {
        graphics_multisampling_count count;
        graphics_multisampling_mask mask;
    };

    // =================================================================================================================

    enum class graphics_image_format
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

//    enum class graphics_channel_format
//    {
//        none,
//        r4g4,
//        r4g4b4a4,
//        r5g6b5,
//        b5g6r5,
//        r5g5b5a1,
//        r8,
//        r8g8,
//        r8g8b8a8,
//        b8g8r8a8,
//        r10g11b11,
//        r11g11b10,
//        r10g10b10a2,
//        r16,
//        r16g16,
//        r16g16b16a16,
//        r32,
//        r32g32,
//        r32g32b32,
//        r32g32b32a32,
//        r16g8,
//        r32g8,
//        r9g9b9e5,
//        compressed_bc1,
//        compressed_bc2,
//        compressed_bc3,
//        compressed_bc4,
//        compressed_bc5,
//        compressed_bc6u,
//        compressed_bc6s,
//        compressed_bc7,
//    };
//
//    // -----------------------------------------------------------------------------------------------------------------
//
//    enum class graphics_numeric_format
//    {
//        typeless,
//        unorm,
//        snorm,
//        uint,
//        sint,
//        float,
//        srgb,
//        depth_stencil,
//    };
//
//    // -----------------------------------------------------------------------------------------------------------------
//
//    struct graphics_image_format
//    {
//        graphics_channel_format channel_format;
//        graphics_numeric_format numeric_format;
//    };

    // =================================================================================================================
} // namespace m1

#endif // M1_GRAPHICS_STATE_HPP
