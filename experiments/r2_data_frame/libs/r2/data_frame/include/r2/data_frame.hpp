#ifndef R2_DATA_FRAME_HPP
#define R2_DATA_FRAME_HPP

#include "r2/data_source.hpp"
#include "r2/data_sequence.hpp"
#include <memory>
#include <cstddef>
#include <cassert>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    template <typename ...Ts>
    class data_frame
    {
    private:
        // types:
        struct buffer_range_type
        {
            std::shared_ptr<void> ptr {};
            void const           *end {};
        };

        template <typename T>
        using column_ptr_type = std::shared_ptr<data_sequence<T>>;

        // helpers:
        static buffer_range_type make_buffer(std::size_t row_count);

        // members:
        std::tuple<column_ptr_type<Ts>...> m_ColumnPtrs {};
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

        // types:
        struct buffer_range_type
        {
            std::shared_ptr<void> ptr {};
            void const           *end {};
        };

        // members:
        buffer_range_type m_Buffer {};
        std::size_t       m_Count  {};
        std::ptrdiff_t    m_Offset {};
        std::ptrdiff_t    m_Stride {};
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

// ====================================================================================================================
// r2::data_frame<Ts...>
// ====================================================================================================================

template <typename ...Ts>
/*static*/ typename r2::data_frame<Ts...>::buffer_range_type r2::data_frame<Ts...>::make_buffer(std::size_t const row_count)
{
    memory_desc const row_mem_desc = memory_of<Ts...>();
    memory_desc const table_mem_desc = row_mem_desc * row_count;
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
    , m_Buffer({buffer_ptr, buffer_end})
    , m_Count(elem_count)
    , m_Offset(elem_offset)
    , m_Stride(elem_stride)
{
    assert(get_unchecked_elem_ptr(m_Count) <= m_Buffer.end);

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
    assert(elem_ptr + sizeof(T) <= m_BufferPtr.end);
    assert(elem_ptr % alignof(T) == 0);

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
