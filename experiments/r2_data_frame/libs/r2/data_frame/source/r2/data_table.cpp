#include "r2/data_table.hpp"
#include "r2/memory_of.hpp"

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    class data_table_embedded_buffer_memory_resource
        : public data_table_memory_resource
    {
    public:
        using data_table_memory_resource::data_table_memory_resource;
        explicit data_table_embedded_buffer_memory_resource(std::size_t const embedded_buffer_offset,
                                                            std::size_t const embedded_buffer_size) noexcept;
    };

    // ================================================================================================================

    // this is alignment simple allocator that "over" allocates by the given memory_size_description
    // so that the user can construct additional objects in the extra memory
    template <typename T>
    class over_allocator
    {
    public:
        typedef T value_type;
        template <typename U> friend class over_allocator;

        explicit over_allocator(memory_size_description const &buffer_mem_desc) noexcept;
        template <typename U> over_allocator(over_allocator<U> const &rhs) noexcept;

        over_allocator(over_allocator &&rhs) noexcept = default;
        over_allocator(over_allocator const &rhs) noexcept = default;
        over_allocator& operator = (over_allocator &&rhs) noexcept = default;
        over_allocator& operator = (over_allocator const &rhs) noexcept = default;
        ~over_allocator() noexcept = default;

        value_type* allocate(std::size_t n);
        void deallocate(value_type *p, std::size_t n) noexcept;

    private:
        // members:
        memory_size_description m_BufferMemDesc = {0, 1};
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    bool operator == (over_allocator<T> const &lhs,
                      over_allocator<T> const &rhs);

    template <typename T>
    bool operator != (over_allocator<T> const &lhs,
                      over_allocator<T> const &rhs);

    // ================================================================================================================
    // r2::over_allocator<T>
    // ================================================================================================================

    template <typename T>
    /*explicit*/ over_allocator<T>::over_allocator(memory_size_description const &buffer_mem_desc) noexcept
        : m_BufferMemDesc(buffer_mem_desc)
    {
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    template <typename U>
    over_allocator<T>::over_allocator(over_allocator<U> const &rhs) noexcept
        : m_BufferMemDesc(rhs.m_BufferMemDesc)
    {
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    typename over_allocator<T>::value_type* over_allocator<T>::allocate(std::size_t const n)
    {
        memory_size_description const alloc_mem_desc = memory_of({memory_of<T>() * n, m_BufferMemDesc});
        void * const mem_ptr = ::operator new (alloc_mem_desc.size);
        return static_cast<value_type*>(mem_ptr);
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void over_allocator<T>::deallocate(value_type *p, std::size_t const n) noexcept
    {
        ::operator delete(p, n);
    }

    // ================================================================================================================

    template <typename T>
    bool operator == (over_allocator<T> const &lhs,
                      over_allocator<T> const &rhs)
    {
        return &lhs == &rhs;
    }

    template <typename T>
    bool operator != (over_allocator<T> const &lhs,
                      over_allocator<T> const &rhs)
    {
        return &lhs != &rhs;
    }

    // ================================================================================================================
}

// ====================================================================================================================

/*explicit*/ r2::data_table_memory_resource::data_table_memory_resource(void * const buffer_ptr,
                                                                        std::size_t const buffer_size) noexcept
    : m_BufferPtr(buffer_ptr)
    , m_BufferSize(buffer_size)
{
}

// --------------------------------------------------------------------------------------------------------------------

r2::data_table_memory_resource::data_table_memory_resource(data_table_memory_resource &&rhs) noexcept
    : m_BufferPtr(rhs.m_BufferPtr)
    , m_BufferSize(rhs.m_BufferSize)
{
    rhs.m_BufferPtr = nullptr;
    rhs.m_BufferSize = nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

void* r2::data_table_memory_resource::allocate(std::size_t const bytes,
                                               std::size_t const alignment) noexcept
{
    if (std::align(alignment,
                   bytes,
                   m_BufferPtr, // ref
                   m_BufferSize)) // ref
    {
        void * const result_ptr = m_BufferPtr;
        m_BufferPtr = static_cast<unsigned char*>(m_BufferPtr) + bytes;
        m_BufferSize -= bytes;

        return result_ptr;
    }

    return nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

void r2::data_table_memory_resource::deallocate(void * const /*p*/,
                                                std::size_t const /*bytes*/,
                                                std::size_t const /*alignment*/) noexcept
{
    // nothing to do
}

// ====================================================================================================================

std::shared_ptr<r2::data_table_memory_resource> r2::make_data_table_memory_resource(memory_size_description const &embedded_buffer_desc)
{
    typedef data_table_embedded_buffer_memory_resource memory_resource;
    return std::allocate_shared<memory_resource>(over_allocator<memory_resource>(embedded_buffer_desc), // allocator
                                                 offset_of(memory_offset_description {0, 1} +memory_of<memory_resource>(), embedded_buffer_desc), // embedded_buffer_offset
                                                 embedded_buffer_desc.size); // embedded_buffer_size
}

// ====================================================================================================================

/*explicit*/ r2::data_table_embedded_buffer_memory_resource::data_table_embedded_buffer_memory_resource(std::size_t const embedded_buffer_offset,
                                                                                                        std::size_t const embedded_buffer_size) noexcept
    : data_table_memory_resource(this + embedded_buffer_offset, embedded_buffer_size)
{
}

// ====================================================================================================================
