#ifndef M1_GRAPHICS_DRAW_STATE_HPP
#define M1_GRAPHICS_DRAW_STATE_HPP

#include "m1/graphics_state.hpp"

namespace m1
{
    // =================================================================================================================

    class graphics_draw_state
    {
    public:
        graphics_draw_state() = default;
        explicit graphics_draw_state(graphics_raster_state const &state);
        explicit graphics_draw_state(graphics_color_target_state const &state);
        explicit graphics_draw_state(graphics_depth_target_state const &state);
        template <typename T, typename... Ts> explicit graphics_draw_state(T const &state,
                                                                           Ts const &...states);
        graphics_draw_state(graphics_draw_state &&rhs) = default;
        graphics_draw_state(graphics_draw_state const &rhs) = default;
        graphics_draw_state& operator = (graphics_draw_state &&rhs) = default;
        graphics_draw_state& operator = (graphics_draw_state const &rhs) = default;
        ~graphics_draw_state() = default;

        bool is_raster_state_default() const;
        graphics_raster_state& raster_state();
        graphics_raster_state const& get_raster_state() const;

        bool is_color_target_state_default() const;
        graphics_color_target_state& color_target_state();
        graphics_color_target_state const& get_color_target_state() const;

        bool is_depth_target_state_default() const;
        graphics_depth_target_state& depth_target_state();
        graphics_depth_target_state const& get_depth_target_state() const;

        void set_state(graphics_raster_state const &state);
        void set_state(graphics_color_target_state const &state);
        void set_state(graphics_depth_target_state const &state);

    private:
        template <typename T, typename ...Ts> void set_state(T const &state,
                                                             Ts const &...states);

        typedef unsigned char state_mask;
        struct state_bits
        {
            static constexpr state_mask const raster_bit       = 0b0001;
            static constexpr state_mask const color_target_bit = 0b0010;
            static constexpr state_mask const depth_target_bit = 0b0100;
            static constexpr state_mask const all              = 0b0111;
        };

        // members:
        state_mask m_StateMask = 0u;

        graphics_raster_state m_Raster =
            {
                graphics_fill_mode::solid, // fill_mode
                graphics_cull_mode::back,  // cull_mode
                graphics_front_face::ccw,  // front_face
                //  depth_bias
                {
                    0,    // offset
                    0.0f, // slope_scale
                    0.0f, // clamp
                },
            };

        graphics_color_target_state m_ColorTarget =
            {
                false, // enable_alpha_to_coverage
                false, // enable_dual_source_blend
                // constant
                {
                    0.0f, // red
                    0.0f, // green
                    0.0f, // blue
                    0.0f, // alpha
                },
                // targets
                {
                    // [0]
                    {
                        // blend
                        {
                            false, // enable
                            // rgb
                            {
                                graphics_blend_factor::one,  // source_factor
                                graphics_blend_func::add,    // blend_func
                                graphics_blend_factor::zero, // target_factor
                            },
                            // alpha
                            {
                                graphics_blend_factor::one,  // source_factor
                                graphics_blend_func::add,    // blend_func
                                graphics_blend_factor::zero, // target_factor
                            },
                        },
                        graphics_logic_op::source, // logic_op
                        graphics_channel_bits::all, // channel_mask
                    },
                },
            };

        graphics_depth_target_state m_DepthTarget =
            {
                true, // enable_clip
                0.0f, // depth_min
                1.0f, // depth_max
                // depth_test
                {
                    true,                        // enable_test
                    true,                        // enable_write
                    graphics_compare_func::less, // compare_func
                    0.0f,                        // clamp_min
                    1.0f,                        // clamp_max
                },
                // stencil_test
                {
                    false,                      // enable_test
                    graphics_stencil_bits::all, // read_mask
                    graphics_stencil_bits::all, // write_mask
                    // front_face_test
                    {
                        0x00, // ref_value
                        graphics_compare_func::always, // compare_func
                        graphics_stencil_op::keep,     // stencil_pass_depth_pass_op
                        graphics_stencil_op::keep,     // stencil_pass_depth_fail_op
                        graphics_stencil_op::keep,     // stencil_fail_op
                    },
                    // back_face_test
                    {
                        0x00, // ref_value;
                        graphics_compare_func::always, // compare_func
                        graphics_stencil_op::keep,     // stencil_pass_depth_pass_op
                        graphics_stencil_op::keep,     // stencil_pass_depth_fail_op
                        graphics_stencil_op::keep,     // stencil_fail_op
                    },
                },
            };
    };

    // -----------------------------------------------------------------------------------------------------------------

    graphics_draw_state merge_graphics_state(graphics_draw_state const &original,
                                             graphics_draw_state const &override);

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

template <typename T, typename... Ts> /*explicit*/ m1::graphics_draw_state::graphics_draw_state(T const &state,
                                                                                                Ts const &...states)
    : graphics_draw_state()
{
    set_state(state);
    set_state(states...);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T, typename ...Ts> void m1::graphics_draw_state::set_state(T const &state,
                                                                              Ts const &...states)
{
    set_state(state);
    set_state(states...);
}

// =====================================================================================================================

#endif // M1_GRAPHICS_DRAW_STATE_HPP
