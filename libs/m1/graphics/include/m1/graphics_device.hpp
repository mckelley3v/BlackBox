#ifndef M1_GRAPHICS_DEVICE_HPP
#define M1_GRAPHICS_DEVICE_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    enum class graphics_api
    {
        none,
        d3d_11,
        d3d_12,
        gl_2_1,
        gl_3_3_core,
        gl_4_4_core,
        gles_2_0,
        gles_3_1,
        vk_1_0,
    };

    // --------------------------------------------------------------------------------------------------

    class graphics_command_queue;
    class graphics_device_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_device
    {
    public:
        explicit graphics_device(graphics_api api);
        graphics_device(graphics_device &&rhs) = default;
        graphics_device& operator = (graphics_device &&rhs) = default;
        ~graphics_device() = default;

        graphics_api get_api() const;
        graphics_command_queue make_command_queue() const;

        void execute(graphics_command_queue const &queue);

    private:
        graphics_device() = delete;
        graphics_device(graphics_device const &rhs) = delete;
        graphics_device& operator = (graphics_device const &rhs) = delete;

        // members:
        std::unique_ptr<graphics_device_impl> m_ImplPtr;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_DEVICE_HPP
