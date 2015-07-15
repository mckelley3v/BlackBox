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
        source,                     // target = source                  copy
        zero,                       // target = 0.0                     clear
        source_bitand_target,       // target = source & target         and
        source_bitand_compl_target, // target = source & ~target        and_reverse
        compl_source_bitand_target, // target = ~source & target        and_inverted
        target,                     // target = target                  noop
        source_bitxor_target,       // target = source ^ target         xor
        source_bitor_target,        // target = source | target         or
        source_bitnor_target,       // target = ~(source | target)      nor
        source_bitxnor_target,      // target = ~(source ^ target)      equiv
        compl_target,               // target = ~target                 invert
        source_bitor_compl_target,  // target = source | ~target        or_reverse
        compl_source,               // target = ~source                 copy_inverted
        compl_source_bitor_target,  // target = ~source | target        or_inverted
        source_bitnand_target,      // target = ~(source & target)      nand
        one,                        // target = 1.0                     set
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
        graphics_multisampling_count samples;
        graphics_multisampling_mask mask;
    };

    // =================================================================================================================
} // namespace m1

#endif // M1_GRAPHICS_STATE_HPP
