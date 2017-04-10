#ifndef R2_DATA_FRAME_HPP
#define R2_DATA_FRAME_HPP

#include "r2/data_source.hpp"
#include "r2/data_sequence.hpp"
#include <tuple>
#include <memory>
#include <cstddef>
#include <cassert>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    struct data_frame_buffer
    {
        std::shared_ptr<void> ptr;
        void const           *end;
    };

    // ================================================================================================================

    template <typename ...Ts>
    class data_frame
    {
    public:
    //private:
        // helpers:
        void build_buffer(std::size_t row_count);

        // members:
        std::tuple<data_sequence<Ts>...> m_Columns {};
    };

    // ================================================================================================================

    // shared_ptr to buffer containing entire data_frame, but with stride/offset to just one column
    template <typename T>
    class data_frame_buffer_source
        : public data_source<T>
    {
        typedef data_source<T> base_type;

    public:
        // types:
        typedef T value_type;

        // construct/move/destroy:
        data_frame_buffer_source() = default;
        data_frame_buffer_source(std::shared_ptr<void> const &buffer_ptr,
                                 void const *buffer_end,
                                 std::size_t elem_count,
                                 std::ptrdiff_t elem_offset,
                                 std::ptrdiff_t elem_stride);
        data_frame_buffer_source(data_frame_buffer_source &&rhs) = default;
        data_frame_buffer_source& operator = (data_frame_buffer_source &&rhs) = default;
        virtual ~data_frame_buffer_source() override = default;

        // properties:
        virtual std::size_t size() const override;
        virtual value_type const& operator [] (std::size_t index) const override;

    private:
        // copy (deleted):
        data_frame_buffer_source(data_frame_buffer_source const &rhs) = delete;
        data_frame_buffer_source& operator = (data_frame_buffer_source const &rhs) = delete;

        // helpers:
        unsigned char const* get_unchecked_elem_ptr(std::size_t index) const;

        // members:
        data_frame_buffer m_Buffer {};
        std::size_t       m_Count  {0};
        std::ptrdiff_t    m_Offset {0};
        std::ptrdiff_t    m_Stride {0};
    };

    // ================================================================================================================

    // shared_ptr to some underlying data, return value through func(underlying[index])
    // class data_frame_func_source

    // ================================================================================================================

    // shared_ptr to some underlying data, return value through func(itr(underlying), end(underlying))
    // class data_frame_aggregate_source;

    // ================================================================================================================
} // namespace r2

#include "r2/memory_of.hpp"
#include <new>

// ====================================================================================================================

namespace r2
{
namespace data_frame_impl
{
    // ================================================================================================================

    template <typename T>
    constexpr T* align_up(T* const p, std::size_t const align)
    {
        // implementation from:
        // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4201.html

        return reinterpret_cast<T*>(memory_of_impl::align_up(reinterpret_cast<std::uintptr_t>(p), align));
    }

    // ================================================================================================================

    void* increment_ptr(void *p, std::size_t increment)
    {
        return reinterpret_cast<unsigned char*>(p) + increment;
    }

    // ================================================================================================================

    template <typename T>
    class data_frame_buffer_allocator
    {
    public:
        typedef T value_type;
        template <typename U> friend class data_frame_buffer_allocator;

        explicit data_frame_buffer_allocator(memory_size_description const &buffer_mem_desc) noexcept;
        template <typename U> data_frame_buffer_allocator(data_frame_buffer_allocator<U> const &rhs) noexcept;

        data_frame_buffer_allocator(data_frame_buffer_allocator &&rhs) noexcept = default;
        data_frame_buffer_allocator(data_frame_buffer_allocator const &rhs) noexcept = default;
        data_frame_buffer_allocator& operator = (data_frame_buffer_allocator &&rhs) noexcept = default;
        data_frame_buffer_allocator& operator = (data_frame_buffer_allocator const &rhs) noexcept = default;
        ~data_frame_buffer_allocator() noexcept = default;

        value_type* allocate(std::size_t n);
        void deallocate(value_type *p, std::size_t n) noexcept;

    private:
        // members:
        memory_size_description m_BufferMemDesc = {0, 1};
    };

    // ================================================================================================================
    // r2::data_frame_impl::data_frame_buffer_allocator<T>
    // ================================================================================================================

    template <typename T>
    /*explicit*/ data_frame_buffer_allocator<T>::data_frame_buffer_allocator(memory_size_description const &buffer_mem_desc) noexcept
        : m_BufferMemDesc(buffer_mem_desc)
    {
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    template <typename U>
    data_frame_buffer_allocator<T>::data_frame_buffer_allocator(data_frame_buffer_allocator<U> const &rhs) noexcept
        : m_BufferMemDesc(rhs.m_BufferMemDesc)
    {
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    typename data_frame_buffer_allocator<T>::value_type* data_frame_buffer_allocator<T>::allocate(std::size_t const n)
    {
        memory_size_description const alloc_mem_desc = memory_of({memory_of<T>() * n, m_BufferMemDesc});
        void * const mem_ptr = ::operator new (alloc_mem_desc.size);
        return static_cast<value_type*>(mem_ptr);
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void data_frame_buffer_allocator<T>::deallocate(value_type *p, std::size_t const n) noexcept
    {
        ::operator delete(p, n);
    }

    // ================================================================================================================
} // namespace data_frame_impl
} // namespace r2

  // ====================================================================================================================
// r2::data_frame<Ts...>
// ====================================================================================================================

template <typename ...Ts>
void r2::data_frame<Ts...>::build_buffer(std::size_t const row_count)
{
    using namespace data_frame_impl;

    // note: primary goal of the complexity here is to construct the entire data_frame's columns' data
    // and data_sequences in a single allocation
    //  this should provide maximal performance and cache locality

    // construct a buffer big enough to hold a column for each T, with row_count number of values
    // use memory_size_description to help calculate appropriate buffer sizes and alignments

    // the buffer is arranged as contiguous columns of data, each column after the other in memory
    // (with appropriate padding in between for alignment)
    // example:
    //  struct buffer
    //  {
    //      T0 col0[row_count];
    //      T1 col2[row_count];
    //      ...
    //      TN colN[row_count];
    //  };

    // the header tuple will contain pointers to each column's data
    //  the columns' data will be part of the buffer created after the header
    //  the data_frame_buffer_source for each column will be initialized to a shared_ptr to the
    //      beginning of that columns data, but using the aliasing constructor to header_ptr so
    //      the data's lifetime is tied to the buffer but without any additional allocations
    // the data_frame's tuple of data_sequence (which hold shared_ptr to data_source) will be assigned
    //  to the data_frame_buffer_source's created here
    typedef std::tuple<data_frame_buffer_source<Ts>...> header_tuple_type;

    std::initializer_list<memory_size_description> const column_mem_descs = {(memory_of<Ts>() * row_count)...};
    memory_size_description const buffer_mem_desc = memory_of(column_mem_descs);

    // the data_frame_buffer_allocator will append space for the given memory_size_description to the given allocation
    // so we'll use allocate_shared to construct a shared_ptr to the header, then get the allocated pointer and do some
    // arithmetic to the beginning of the actual buffer memory
    // example:
    //  shared_ptr::ref_count rc:
    //      data_frame_buffer_source<T0> col0_header:
    //          buffer:
    //              ptr = {rc, buffer_ptr}
    //              end = buffer_end
    //          count = row_count
    //          offset = col0 - buffer_ptr
    //          stride = sizeof(T0)
    //      data_frame_buffer_source<T1> col1_header
    //      ...
    //      data_frame_buffer_source<TN> colN_header
    //  buffer_ptr:
    //      T0 col0[row_count]
    //      T1 col1[row_count]
    //      ...
    //      TN colN[row_count]
    //  buffer_end:

    std::shared_ptr<header_tuple_type> const header_ptr = std::allocate_shared<header_tuple_type>(data_frame_buffer_allocator<header_tuple_type>(buffer_mem_desc));
    void * const header_end = increment_ptr(header_ptr.get(), sizeof(header_tuple_type));

    std::shared_ptr<void> const buffer_ptr(header_ptr, align_up(header_end, buffer_mem_desc.align));
    void * const buffer_end = increment_ptr(buffer_ptr.get(), buffer_mem_desc.size);

    // some trickery here to assign to a tuple with runtime indexing
    typedef void (*header_assign_column_func)(header_tuple_type &header,
                                              std::shared_ptr<void> const &buffer_ptr,
                                              void const * const buffer_end,
                                              std::size_t const elem_count,
                                              std::ptrdiff_t const elem_offset,
                                              std::ptrdiff_t const elem_stride);

    header_assign_column_func const header_assign_column_funcs[] =
        {
            [](header_tuple_type &header,
               std::shared_ptr<void> const &buffer_ptr,
               void const * const buffer_end,
               std::size_t const elem_count,
               std::ptrdiff_t const elem_offset,
               std::ptrdiff_t const elem_stride)
            {
                std::get<data_frame_buffer_source<Ts>>(header) = data_frame_buffer_source<Ts>(buffer_ptr,
                                                                                              buffer_end,
                                                                                              elem_count,
                                                                                              elem_offset,
                                                                                              elem_stride);
            }
            ...
        };

    // calculate each column's offset and construct a data_frame_buffer_source for each column
    memory_offset_description column_offset_desc = {0, 1};
    std::size_t const column_count = column_mem_descs.size();
    for(std::size_t column_index = 0; column_index < column_count; ++column_index)
    {
        memory_size_description const &column_mem_desc = column_mem_descs.begin()[column_index];
        std::size_t const column_offset = offset_of(column_offset_desc, column_mem_desc);
        std::ptrdiff_t const column_stride = static_cast<std::ptrdiff_t>(column_mem_desc.size);

        // std::get<column_index>(*header_ptr) isn't valid so must be routed through header_assign_column_funcs
        // which has "erased" the compile-type indexing
        header_assign_column_funcs[column_index](*header_ptr,
                                                 buffer_ptr,
                                                 buffer_end,
                                                 row_count,
                                                 column_offset,
                                                 column_stride);

        column_offset_desc += column_mem_desc;
    }

}

// ====================================================================================================================
// r2::data_frame_buffer_source<T>
// ====================================================================================================================

template <typename T>
r2::data_frame_buffer_source<T>::data_frame_buffer_source(std::shared_ptr<void> const &buffer_ptr,
                                                          void const * const buffer_end,
                                                          std::size_t const elem_count,
                                                          std::ptrdiff_t const elem_offset,
                                                          std::ptrdiff_t const elem_stride)
    : base_type()
    , m_Buffer{buffer_ptr, buffer_end}
    , m_Count(elem_count)
    , m_Offset(elem_offset)
    , m_Stride(elem_stride)
{
    assert(get_unchecked_elem_ptr(m_Count) <= m_Buffer.end);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
/*virtual*/ std::size_t r2::data_frame_buffer_source<T>::size() const /*override*/
{
    return m_Count;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
/*virtual*/ typename r2::data_frame_buffer_source<T>::value_type const& r2::data_frame_buffer_source<T>::operator [] (std::size_t const index) const /*override*/
{
    assert(index < m_Count);
    assert(m_Buffer.ptr);

    unsigned char const * const elem_ptr = get_unchecked_elem_ptr(index);
    assert(elem_ptr + sizeof(T) <= m_Buffer.end);
    assert(reinterpret_cast<std::uintptr_t>(elem_ptr) % alignof(T) == 0);

    return *reinterpret_cast<value_type const*>(elem_ptr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
unsigned char const* r2::data_frame_buffer_source<T>::get_unchecked_elem_ptr(std::size_t const index) const
{
    return reinterpret_cast<unsigned char const*>(m_Buffer.ptr.get()) + m_Offset + index * m_Stride;
}

// ====================================================================================================================

#endif // R2_DATA_FRAME_HPP
