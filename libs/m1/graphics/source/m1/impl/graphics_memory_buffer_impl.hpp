#ifndef M1_GRAPHICS_MEMORY_BUFFER_IMPL_HPP
#define M1_GRAPHICS_MEMORY_BUFFER_IMPL_HPP

// ======================================================================================================

namespace m1
{
    // ==================================================================================================

    class graphics_memory_buffer_impl
    {
    public:
        graphics_memory_buffer_impl() = default;
        virtual ~graphics_memory_buffer_impl() = default;

    private:
        graphics_memory_buffer_impl(graphics_memory_buffer_impl &&rhs) = delete;
        graphics_memory_buffer_impl(graphics_memory_buffer_impl const &rhs) = delete;
        graphics_memory_buffer_impl& operator = (graphics_memory_buffer_impl &&rhs) = delete;
        graphics_memory_buffer_impl& operator = (graphics_memory_buffer_impl const &rhs) = delete;
    };

    // ==================================================================================================
} // namespace m1

// ======================================================================================================

#endif // M1_GRAPHICS_MEMORY_BUFFER_IMPL_HPP
