#ifndef R2_DATA_TABLE_HPP
#define R2_DATA_TABLE_HPP

#include "r2/memory_of.hpp"
#include <vector>
#include <scoped_allocator>
#include <memory>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    // a simple memory resource that several data_table_allocators can share
    // the intended usage is for all the memory of the data_table's columns of
    // std::vector<X>'s to share a single allocation instead of each column
    // allocating it's own
    // this is a simplified version of http://en.cppreference.com/w/cpp/memory/memory_resource
    class data_table_memory_resource
    {
    public:
        explicit data_table_memory_resource(void *buffer_ptr,
                                            std::size_t buffer_size) noexcept;
        data_table_memory_resource(data_table_memory_resource &&rhs) noexcept;
        ~data_table_memory_resource() noexcept = default;

        void* allocate(std::size_t bytes,
                       std::size_t alignment) noexcept;

        void deallocate(void *p,
                        std::size_t bytes,
                        std::size_t alignment) noexcept;

    private:
        explicit data_table_memory_resource() = delete;
        data_table_memory_resource(data_table_memory_resource const &rhs) = delete;
        data_table_memory_resource& operator = (data_table_memory_resource &&rhs) = delete;
        data_table_memory_resource& operator = (data_table_memory_resource const &rhs) = delete;

        // members:
        void       *m_BufferPtr  {nullptr};
        std::size_t m_BufferSize {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    // constructs a data_table_memory_resource with an embedded buffer
    //  -   avoids double allocation and provides a safely shareable resource
    std::shared_ptr<data_table_memory_resource> make_data_table_memory_resource(memory_size_description const &embedded_buffer_desc);

    // ================================================================================================================

    // a standard library compliant allocator that shares a data_table_memory_resource for its initial allocation
    // and a fallback allocator for every subsequent allocation
    // the intent is to pre-allocate storage for several std::vector containers
    // the core of this class is just to call allocate/deallocate on the data_table_memory_resource
    // see https://howardhinnant.github.io/allocator_boilerplate.html for a discussion on the boilerplate here
    template <typename T,
              typename FallbackAllocator = std::allocator<T>>
    class data_table_allocator
    {
    public:
        typedef T value_type;
        typedef std::false_type propagate_on_container_copy_assignment;
        typedef std::false_type propagate_on_container_move_assignment;
        typedef std::false_type propagate_on_container_swap;
        typedef std::false_type is_always_equal;
        typedef FallbackAllocator fallback_allocator_type;

        // construct/move/copy/destroy:
        explicit data_table_allocator() noexcept = default;
        explicit data_table_allocator(std::shared_ptr<data_table_memory_resource> &&memory_resource_ptr) noexcept;
        explicit data_table_allocator(FallbackAllocator const &fallback_allocator) noexcept;
        explicit data_table_allocator(FallbackAllocator const &fallback_allocator,
                                      std::shared_ptr<data_table_memory_resource> &&memory_resource_ptr) noexcept;
        template <typename U>
        explicit data_table_allocator(data_table_allocator<U> const &rhs) noexcept;
        data_table_allocator(data_table_allocator &&rhs) noexcept;
        data_table_allocator(data_table_allocator const &rhs) noexcept;
        ~data_table_allocator() noexcept = default;

        value_type* allocate(std::size_t count);
        void deallocate(value_type *p,
                        std::size_t count) noexcept;

        data_table_allocator select_on_container_copy_construction() const;

    private:
        data_table_allocator& operator = (data_table_allocator &&rhs) = delete;
        data_table_allocator& operator = (data_table_allocator const &rhs) = delete;

        bool is_alloc_unused() const noexcept;
        void* release_alloc_ptr(void *default_ptr) noexcept;

        // members:
        FallbackAllocator                           m_FallbackAllocator {};
        std::shared_ptr<data_table_memory_resource> m_MemoryResourcePtr {};
        void                                       *m_AllocPtr          {nullptr}; // nullptr if not allocated
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T,
              typename A>
    bool operator == (data_table_allocator<T, A> const &lhs,
                      data_table_allocator<T, A> const &rhs);

    template <typename T,
              typename A>
    bool operator != (data_table_allocator<T, A> const &lhs,
                      data_table_allocator<T, A> const &rhs);

    // ================================================================================================================

    // using scoped_allocator_adaptor so that any nested containers don't use the data_table_allocator
    template <typename T>
    using data_table_column_allocator = std::scoped_allocator_adaptor<data_table_allocator<T>,
                                                                      typename data_table_allocator<T>::fallback_allocator_type>;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    using data_table_column = std::vector<T, data_table_column_allocator<T>>;

    // ================================================================================================================

    enum class initial_size : size_t {};
    enum class initial_capacity : size_t {};

    // a 2D heterogeneous data structure, presents an interface like vector<tuple<X0,...XN>>
    // but implemented as tuple<vector<X0>,...,vector<XN>> for performance
    template <typename ...Ts>
    class data_table
    {
    public:
        // types:
        typedef std::tuple<Ts...>        value_type;
        typedef std::tuple<Ts&...>       reference;
        typedef std::tuple<Ts const&...> const_reference;

        // construct/move/copy/destroy:
        explicit data_table() noexcept = default;
        explicit data_table(initial_capacity capacity);
        explicit data_table(initial_size size);
        explicit data_table(initial_size size,
                            value_type const &value);
        explicit data_table(std::initializer_list<value_type> const &values);
        data_table(data_table &&rhs) noexcept;
        data_table(data_table const &rhs) = default;
        data_table& operator = (data_table &&rhs) noexcept;
        data_table& operator = (data_table const &rhs) = default;
        ~data_table() noexcept = default;

        // properties:
        reference       operator [] (std::size_t index) noexcept;
        const_reference operator [] (std::size_t index) const noexcept;

        reference       front() noexcept;
        const_reference front() const noexcept;

        reference       back() noexcept;
        const_reference back() const noexcept;

        // capacity:
        bool        empty() const;
        std::size_t size() const;
        std::size_t capacity() const;
        void        reserve(std::size_t capacity);

        // modifiers:
        void clear();
        void push_back(value_type const &value);
        void resize(std::size_t count);
        void resize(std::size_t count,
                    value_type const &value);
        void swap(data_table &rhs) noexcept;

    private:
        static std::shared_ptr<data_table_memory_resource> create_memory_resource(std::size_t count);

        // members:
        std::tuple<data_table_column<Ts>...> m_Columns  {};
    };

    // ================================================================================================================
} // namespace r2

// ====================================================================================================================
// r2::data_table_allocator<T, A>
// ====================================================================================================================

template <typename T,
          typename A>
/*explicit*/ r2::data_table_allocator<T, A>::data_table_allocator(std::shared_ptr<data_table_memory_resource> &&memory_resource_ptr) noexcept
    : m_MemoryResourcePtr(std::move(memory_resource_ptr))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
/*explicit*/ r2::data_table_allocator<T, A>::data_table_allocator(FallbackAllocator const &fallback_allocator) noexcept
    : m_FallbackAllocator(fallback_allocator)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
/*explicit*/ r2::data_table_allocator<T, A>::data_table_allocator(FallbackAllocator const &fallback_allocator,
                                                                  std::shared_ptr<data_table_memory_resource> &&memory_resource_ptr) noexcept
    : m_FallbackAllocator(fallback_allocator)
    , m_MemoryResourcePtr(std::move(memory_resource_ptr))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
template <typename U>
/*explicit*/ r2::data_table_allocator<T, A>::data_table_allocator(data_table_allocator<U> const &rhs) noexcept
    : m_FallbackAllocator(rhs.m_FallbackAllocator)
    , m_MemoryResourcePtr(rhs.m_MemoryResourcePtr)
    , m_AllocPtr(rhs.is_alloc_unused() ? nullptr : this)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
r2::data_table_allocator<T, A>::data_table_allocator(data_table_allocator &&rhs) noexcept
    : m_FallbackAllocator(std::move(rhs.m_FallbackAllocator))
    , m_MemoryResourcePtr(std::move(rhs.m_MemoryResourcePtr))
    , m_AllocPtr(rhs.release_alloc_ptr(this))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
r2::data_table_allocator<T, A>::data_table_allocator(data_table_allocator const &rhs) noexcept
    : m_FallbackAllocator(rhs.m_FallbackAllocator)
    , m_MemoryResourcePtr(rhs.m_MemoryResourcePtr)
    , m_AllocPtr(rhs.is_alloc_unused() ? nullptr : this)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
typename r2::data_table_allocator<T, A>::value_type* r2::data_table_allocator<T, A>::allocate(std::size_t const count)
{
    if(m_MemoryResourcePtr && is_alloc_unused())
    {
        // save allocated pointer so we can deallocate it properly later
        m_AllocPtr = m_MemoryResourcePtr->allocate(sizeof(T) * count, alignof(T));
        return m_AllocPtr;
    }

    return m_FallbackAllocator.allocate(count);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
void r2::data_table_allocator<T, A>::deallocate(value_type * const p,
                                                std::size_t  const count) noexcept
{
    if(p == m_AllocPtr)
    {
        m_MemoryResourcePtr->deallocate(p, sizeof(T) * count, alignof(T));

        // "retire" m_AllocPtr from being used again
        m_AllocPtr = this;
        return;
    }

    m_FallbackAllocator.deallocate(p, count);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
r2::data_table_allocator<T, A> r2::data_table_allocator<T, A>::select_on_container_copy_construction() const
{
    // forces only fallback allocator
    return data_table_allocator(m_FallbackAllocator);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
bool r2::data_table_allocator<T, A>::is_alloc_unused() const noexcept
{
    return m_AllocPtr == nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
void* r2::data_table_allocator<T, A>::release_alloc_ptr(void * const default_ptr) noexcept
{
    if(m_AllocPtr != this)
    {
        void *result = m_AllocPtr;
        m_AllocPtr = this;
        return result;
    }

    return default_ptr;
}

// ====================================================================================================================

template <typename T,
          typename A>
bool r2::operator == (data_table_allocator<T, A> const &lhs,
                      data_table_allocator<T, A> const &rhs)
{
    return &lhs == &rhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T,
          typename A>
bool r2::operator != (data_table_allocator<T, A> const &lhs,
                      data_table_allocator<T, A> const &rhs)
{
    return &lhs != &rhs;
}

// ====================================================================================================================
// r2::data_table_impl
// ====================================================================================================================

namespace r2
{
namespace data_table_impl
{
    // ================================================================================================================

    template <typename ...Ts,
              typename A,
              std::size_t ...Is>
    std::tuple<Ts&...> tie_elements_impl(std::tuple<std::vector<Ts, A>...> &vecs,
                                         std::size_t const index,
                                         std::index_sequence<Is...> /*indices*/)
    {
        return std::tie(std::get<Is>(vecs)[index]...);
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename ...Ts,
              typename A,
              std::size_t ...Is>
    std::tuple<Ts const&...> tie_elements_impl(std::tuple<std::vector<Ts, A>...> const &vecs,
                                               std::size_t const index,
                                               std::index_sequence<Is...> /*indices*/)
    {
        return std::tie(std::get<Is>(vecs)[index]...);
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename ...Ts,
              typename A>
    std::tuple<Ts&...> tie_elements(std::tuple<std::vector<Ts, A>...> &vecs,
                                    std::size_t const index)
    {
        return tie_elements_impl(vecs,
                                 index,
                                 std::make_index_sequence<sizeof...(Ts)>());
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename ...Ts,
              typename A>
    std::tuple<Ts const&...> tie_elements(std::tuple<std::vector<Ts, A>...> const &vecs,
                                          std::size_t const index)
    {
        return tie_elements_impl(vecs,
                                 index,
                                 std::make_index_sequence<sizeof...(Ts)>());
    }

    // ================================================================================================================

} // namespace data_table_impl
} // namespace r2

// ====================================================================================================================
// r2::data_table
// ====================================================================================================================

template <typename ...Ts>
/*explicit*/ r2::data_table<Ts...>::data_table(std::size_t const count)
{
    // doesn't initialize m_Columns' allocators with create_memory_resource
    resize(count);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
/*explicit*/ r2::data_table<Ts...>::data_table(std::size_t const count,
                                               value_type const &value)
{
    // doesn't initialize m_Columns' allocators with create_memory_resource
    assign(count, value);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
/*explicit*/ r2::data_table<Ts...>::data_table(std::initializer_list<value_type> const &values)
{
    // doesn't initialize m_Columns' allocators with create_memory_resource
    assign(values);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
r2::data_table<Ts...>::data_table(data_table &&rhs) noexcept
    : m_Columns(std::move(rhs.m_Columns)) // doesn't propagate allocator
{
    rhs.m_Columns.clear();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
r2::data_table<Ts...>& r2::data_table<Ts...>::operator = (data_table &&rhs) noexcept
{
    m_Columns = std::move(rhs.m_Columns); // doesn't propagate allocator
    rhs.m_Columns.clear();

    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
typename r2::data_table<Ts...>::reference r2::data_table<Ts...>::operator [] (std::size_t const index) noexcept
{
    return data_table_impl::tie_elements(m_Columns, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
typename r2::data_table<Ts...>::const_reference r2::data_table<Ts...>::operator [] (std::size_t const index) const noexcept
{
    return data_table_impl::tie_elements(m_Columns, index);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
typename r2::data_table<Ts...>::reference r2::data_table<Ts...>::front() noexcept
{
    return data_table_impl::tie_elements(m_Columns, 0);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
typename r2::data_table<Ts...>::const_reference r2::data_table<Ts...>::front() const noexcept
{
    return data_table_impl::tie_elements(m_Columns, 0);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
typename r2::data_table<Ts...>::reference r2::data_table<Ts...>::back() noexcept
{
    return data_table_impl::tie_elements(m_Columns, size() - 1);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
typename r2::data_table<Ts...>::const_reference r2::data_table<Ts...>::back() const noexcept
{
    return data_table_impl::tie_elements(m_Columns, size() - 1);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
bool r2::data_table<Ts...>::empty() const;

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
std::size_t r2::data_table<Ts...>::size() const;

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
std::size_t r2::data_table<Ts...>::capacity() const;

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
void r2::data_table<Ts...>::reserve(std::size_t const capacity);

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
void r2::data_table<Ts...>::clear()
{
    // potential exception guarantee issue: if col.clear throws, the column sizes may be mismatched
    data_table_impl::for_each_tuple(m_Columns,
                                    [](auto &col)
                                    {
                                        col.clear();
                                    });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
void r2::data_table<Ts...>::push_back(value_type const &value)
{
    // potential exception guarantee issue: if col.push_back throws, the column sizes may be mismatched
    data_table_impl::for_each_tuple_index(m_Columns,
                                          [&](auto &col,
                                              auto &index)
                                          {
                                              typedef decltype(index) index_type;
                                              col.push_back(std::get<index_type::value>(value));
                                          });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
void r2::data_table<Ts...>::resize(std::size_t const count)
{
/*
    if(empty())
    {
        data_table<Ts...> temp(count);
        // requires propagate_on_container_swap to do what I want
        swap(temp);
    }
*/
/*
    data_table<Ts...> temp(count);
    std::size_t const copy_count = std::min(m_Size, count);
    for(std::size_t i = 0; i < copy_count; ++i)
    {
        temp[i] = std::move_if_noexcept((*this)[i]);
    }
    // requires propagate_on_container_swap to do what I want
    swap(temp);
*/
/*
    // potential exception guarantee issue: if col.resize throws, the column sizes may be mismatched
    data_table_impl::for_each_tuple(m_Columns,
                                    [&](auto &col)
                                    {
                                        col.resize(capacity);
                                    });
*/
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
void r2::data_table<Ts...>::resize(std::size_t const count,
                                   value_type const &value)
{
    // potential exception guarantee issue: if col.resize throws, the column sizes may be mismatched
    data_table_impl::for_each_tuple_index(m_Columns,
                                          [&](auto &col,
                                              auto &index)
                                          {
                                              typedef decltype(index) index_type;
                                              col.resize(count, std::get<index_type::value>(value));
                                          });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
void r2::data_table<Ts...>::swap(data_table &rhs) noexcept;

// --------------------------------------------------------------------------------------------------------------------

template <typename ...Ts>
/*static*/ std::shared_ptr<r2::data_table_memory_resource> r2::data_table<Ts...>::create_memory_resource(std::size_t const count);
// build data_table_memory_resource with buffer large enough for:
//  - memory_of({memory_of<allocate_shared overhead>(), memory_of<m_Columns>(), memory_of<Ts>() * count...})

// ====================================================================================================================

#endif // R2_DATA_TABLE_HPP
