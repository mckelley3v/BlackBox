#ifndef M1_GRAPHICS_MEMORY_BUFFER_HPP
#define M1_GRAPHICS_MEMORY_BUFFER_HPP

#include <memory>

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_memory_buffer_impl;

    // --------------------------------------------------------------------------------------------------

    class graphics_memory_buffer
    {
    friend class graphics_device;
    public:
        graphics_memory_buffer(graphics_memory_buffer &&rhs) = default;
        graphics_memory_buffer(graphics_memory_buffer const &rhs) = default;
        graphics_memory_buffer& operator = (graphics_memory_buffer &&rhs) = default;
        graphics_memory_buffer& operator = (graphics_memory_buffer const &rhs) = default;
        virtual ~graphics_memory_buffer() = default;

    protected:
        explicit graphics_memory_buffer(std::shared_ptr<graphics_memory_buffer_impl> const &impl_ptr);

    private:
        graphics_memory_buffer() = delete;

        // members:
        std::shared_ptr<graphics_memory_buffer_impl> m_ImplPtr;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_MEMORY_BUFFER_HPP
