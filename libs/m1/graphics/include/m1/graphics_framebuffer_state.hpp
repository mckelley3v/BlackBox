#ifndef M1_GRAPHICS_FRAMEBUFFER_STATE_HPP
#define M1_GRAPHICS_FRAMEBUFFER_STATE_HPP

#include "m1/graphics_state.hpp"

namespace m1
{
    // =================================================================================================================

    class graphics_framebuffer_state
    {
    public:
        graphics_framebuffer_state() = default;
        explicit graphics_framebuffer_state(int width,
                                            int height,
                                            graphics_multisampling_count multisampling_count);
        explicit graphics_framebuffer_state(graphics_viewport_state const &state);
        explicit graphics_framebuffer_state(graphics_scissor_state const &state);
        explicit graphics_framebuffer_state(graphics_multisampling_state const &state);
        template <typename T, typename ...Ts> explicit graphics_framebuffer_state(T const &state,
                                                                                  Ts const &...states);
        graphics_framebuffer_state(graphics_framebuffer_state &&rhs) = default;
        graphics_framebuffer_state(graphics_framebuffer_state const &rhs) = default;
        graphics_framebuffer_state& operator = (graphics_framebuffer_state &&rhs) = default;
        graphics_framebuffer_state& operator = (graphics_framebuffer_state const &rhs) = default;
        ~graphics_framebuffer_state() = default;

        bool is_viewport_state_default() const;
        graphics_viewport_state& viewport_state();
        graphics_viewport_state const& get_viewport_state() const;

        bool is_scissor_state_default() const;
        graphics_scissor_state& scissor_state();
        graphics_scissor_state const& get_scissor_state() const;

        bool is_multisampling_state_default() const;
        graphics_multisampling_state& multisampling_state();
        graphics_multisampling_state const& get_multisampling_state() const;

        void set_state(graphics_viewport_state const &state);
        void set_state(graphics_scissor_state const &state);
        void set_state(graphics_multisampling_state const &state);

    private:
        template <typename T, typename ...Ts> void set_state(T const &state,
                                                             Ts const &...states);

        typedef unsigned char state_mask;
        struct state_bits
        {
            static constexpr state_mask const viewport_bit      = 0b0001;
            static constexpr state_mask const scissor_bit       = 0b0010;
            static constexpr state_mask const multisampling_bit = 0b0100;
            static constexpr state_mask const all               = 0b0111;
        };

        // members:
        state_mask m_StateMask = 0u;

        graphics_viewport_state m_Viewport =
            {
                0,    // x
                0,    // y
                0,    // width
                0,    // height
            };

        graphics_scissor_state m_Scissor =
            {
                false, // enable
                0,     // x
                0,     // y
                0,     // width
                0,     // height
            };

        graphics_multisampling_state m_Multisampling =
            {
                graphics_multisampling_count::x1,    // count
                graphics_multisampling_bits::all, // mask
            };
    };

    // -----------------------------------------------------------------------------------------------------------------

    graphics_framebuffer_state merge_graphics_state(graphics_framebuffer_state const &original,
                                                    graphics_framebuffer_state const &override);

    // =================================================================================================================
} // namespace m1

// =====================================================================================================================

template <typename T, typename... Ts> /*explicit*/ m1::graphics_framebuffer_state::graphics_framebuffer_state(T const &state,
                                                                                                              Ts const &...states)
    : graphics_framebuffer_state()
{
    set_state(state);
    set_state(states...);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename T, typename ...Ts> void m1::graphics_framebuffer_state::set_state(T const &state,
                                                                                     Ts const &...states)
{
    set_state(state);
    set_state(states...);
}

// =====================================================================================================================

#endif // M1_GRAPHICS_FRAMEBUFFER_STATE_HPP
