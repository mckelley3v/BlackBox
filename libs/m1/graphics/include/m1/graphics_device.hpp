#ifndef M1_GRAPHICS_DEVICE_HPP
#define M1_GRAPHICS_DEVICE_HPP

#include <memory>

namespace m1
{
    enum class graphics_api
    {
        gl_2_1,
        gl_3_3,
        gl_3_3_core,
        gles_2_0,
        gles_3_0,
        gles_3_1,
        dx_10,
        dx_11,
        dx_12,
        vk_1_0,
    };

    class graphics_command_queue;

    class graphics_device
    {
    public:
        explicit graphics_device(graphics_api api);
        ~graphics_device() = default;

        void execute(graphics_command_queue const &queue);

    private:
        graphics_device() = delete;
        graphics_device(graphics_device &&rhs) = delete;
        graphics_device(graphics_device const &rhs) = delete;
        graphics_device& operator = (graphics_device &&rhs) = delete;
        graphics_device& operator = (graphics_device const &rhs) = delete;

        class impl;

        // members:
        std::unique_ptr<impl> m_ImplPtr;
    };
} // namespace m1

#endif // M1_GRAPHICS_DEVICE_HPP
