#ifndef M1_ANY_PTR_HPP
#define M1_ANY_PTR_HPP

#include <cstddef>
#include <cassert>

namespace m1
{
    // -----------------------------------------------------------------------------------------------------------------

    typedef void (*type_id_t)();
    template <typename T> constexpr type_id_t get_type_id();

    // -----------------------------------------------------------------------------------------------------------------

    class any_ptr;
    class const_any_ptr;

    void swap(any_ptr &lhs, any_ptr &rhs);
    void swap(const_any_ptr &lhs, const_any_ptr &rhs);

    bool operator == (std::nullptr_t, any_ptr const &rhs);
    bool operator == (std::nullptr_t, const_any_ptr const &rhs);
    bool operator == (any_ptr const &lhs, std::nullptr_t);
    bool operator == (any_ptr const &lhs, any_ptr const &rhs);
    bool operator == (any_ptr const &lhs, const_any_ptr const &rhs);
    bool operator == (const_any_ptr const &lhs, std::nullptr_t);
    bool operator == (const_any_ptr const &lhs, any_ptr const &rhs);
    bool operator == (const_any_ptr const &lhs, const_any_ptr const &rhs);

    bool operator != (std::nullptr_t, any_ptr const &rhs);
    bool operator != (std::nullptr_t, const_any_ptr const &rhs);
    bool operator != (any_ptr const &lhs, std::nullptr_t);
    bool operator != (any_ptr const &lhs, any_ptr const &rhs);
    bool operator != (any_ptr const &lhs, const_any_ptr const &rhs);
    bool operator != (const_any_ptr const &lhs, std::nullptr_t);
    bool operator != (const_any_ptr const &lhs, any_ptr const &rhs);
    bool operator != (const_any_ptr const &lhs, const_any_ptr const &rhs);

    template <typename T> T* reinterpret_pointer_cast(any_ptr const &p);
    template <typename T> T const* reinterpret_pointer_cast(const_any_ptr const &p);

    template <typename T> T* static_pointer_cast(any_ptr const &p);
    template <typename T> T const* static_pointer_cast(const_any_ptr const &p);

    template <typename T> T* dynamic_pointer_cast(any_ptr const &p);
    template <typename T> T const* dynamic_pointer_cast(const_any_ptr const &p);

    // -----------------------------------------------------------------------------------------------------------------

    class any_ptr
    {
        friend class const_any_ptr;

    public:
        any_ptr() = default;
        any_ptr(any_ptr &&rhs) = default;
        any_ptr(any_ptr const &rhs) = default;
        template <typename T> any_ptr(T * const rhs);
        any_ptr& operator = (any_ptr &&rhs) = default;
        any_ptr& operator = (any_ptr const &rhs) = default;
        template <typename T> any_ptr& operator = (T * const rhs);
        ~any_ptr() = default;

        void swap(any_ptr &rhs);
        explicit operator bool () const;

        friend bool operator == (any_ptr const &lhs, any_ptr const &rhs);
        friend bool operator == (any_ptr const &lhs, const_any_ptr const &rhs);
        friend bool operator == (const_any_ptr const &lhs, any_ptr const &rhs);

        friend bool operator != (any_ptr const &lhs, any_ptr const &rhs);
        friend bool operator != (any_ptr const &lhs, const_any_ptr const &rhs);
        friend bool operator != (const_any_ptr const &lhs, any_ptr const &rhs);

        template <typename T> friend T* reinterpret_pointer_cast(any_ptr const &p);
        template <typename T> friend T* static_pointer_cast(any_ptr const &p);
        template <typename T> friend T* dynamic_pointer_cast(any_ptr const &p);

    private:
        any_ptr(void * const ptr, type_id_t const type_id);

        // members:
        void *m_Ptr = nullptr;
        type_id_t m_TypeId = nullptr;
    };

    // -----------------------------------------------------------------------------------------------------------------

    class const_any_ptr
    {
    public:
        const_any_ptr() = default;
        const_any_ptr(any_ptr &&rhs);
        const_any_ptr(any_ptr const &rhs);
        const_any_ptr(const_any_ptr &&rhs) = default;
        const_any_ptr(const_any_ptr const &rhs) = default;
        template <typename T> const_any_ptr(T const * const rhs);
        const_any_ptr& operator = (any_ptr &&rhs);
        const_any_ptr& operator = (any_ptr const &rhs);
        const_any_ptr& operator = (const_any_ptr &&rhs) = default;
        const_any_ptr& operator = (const_any_ptr const &rhs) = default;
        template <typename T> const_any_ptr& operator = (T const * const rhs);
        ~const_any_ptr() = default;

        void swap(const_any_ptr &rhs);
        explicit operator bool () const;

        friend bool operator == (any_ptr const &lhs, const_any_ptr const &rhs);
        friend bool operator == (const_any_ptr const &lhs, any_ptr const &rhs);
        friend bool operator == (const_any_ptr const &lhs, const_any_ptr const &rhs);

        friend bool operator != (any_ptr const &lhs, const_any_ptr const &rhs);
        friend bool operator != (const_any_ptr const &lhs, any_ptr const &rhs);
        friend bool operator != (const_any_ptr const &lhs, const_any_ptr const &rhs);

        template <typename T> friend T const* reinterpret_pointer_cast(const_any_ptr const &p);
        template <typename T> friend T const* static_pointer_cast(const_any_ptr const &p);
        template <typename T> friend T const* dynamic_pointer_cast(const_any_ptr const &p);

    private:
        const_any_ptr(void const * const ptr, type_id_t const type_id);

        // members:
        void const *m_Ptr = nullptr;
        type_id_t m_TypeId = nullptr;
    };

    // -----------------------------------------------------------------------------------------------------------------
} // namespace m1

// =====================================================================================================================
// implementation
// =====================================================================================================================

// ---------------------------------------------------------------------------------------------------------------------
// m1::type_id
// ---------------------------------------------------------------------------------------------------------------------

namespace m1
{
    template <typename T> void type_id_func();
} // namespace m1

template <typename T> void m1::type_id_func()
{
    throw static_cast<T*>(nullptr);
}

template <typename T> constexpr m1::type_id_t m1::get_type_id()
{
    return &type_id_func<T>;
}

// ---------------------------------------------------------------------------------------------------------------------
// m1::any_ptr
// ---------------------------------------------------------------------------------------------------------------------

template <typename T> m1::any_ptr::any_ptr(T * const rhs)
    : any_ptr(rhs, get_type_id<T>())
{
}

template <typename T> m1::any_ptr& m1::any_ptr::operator = (T * const rhs)
{
    m_Ptr = rhs;
    m_TypeId = get_type_id<T>();
    return *this;
}

template <typename T> T* m1::reinterpret_pointer_cast(any_ptr const &p)
{
    assert(static_pointer_cast<T>(p) != nullptr);
    return static_cast<T*>(p.m_Ptr);
}

template <typename T> T* m1::static_pointer_cast(any_ptr const &p)
{
    return (p.m_TypeId == get_type_id<T>())
           ? static_cast<T*>(p.m_Ptr)
           : nullptr;
}

template <typename T> T* m1::dynamic_pointer_cast(any_ptr const &p)
{
    try
    {
        if(T * const result = static_pointer_cast<T>(p))
        {
            return result;
        }

        if(p.m_TypeId) p.m_TypeId();
        return nullptr;
    }
    catch(T*)
    {
        return static_cast<T*>(p.m_Ptr);
    }
    catch(...)
    {
        return nullptr;
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// m1::const_any_ptr
// ---------------------------------------------------------------------------------------------------------------------

template <typename T> m1::const_any_ptr::const_any_ptr(T const * const rhs)
    : const_any_ptr(rhs, get_type_id<T>())
{
}

template <typename T> m1::const_any_ptr& m1::const_any_ptr::operator = (T const * const rhs)
{
    m_Ptr = rhs;
    m_TypeId = get_type_id<T>();
    return *this;
}

template <typename T> T const* m1::reinterpret_pointer_cast(const_any_ptr const &p)
{
    assert(static_pointer_cast<T>(p) != nullptr);
    return static_cast<T const*>(p.m_Ptr);
}

template <typename T> T const* m1::static_pointer_cast(const_any_ptr const &p)
{
    return (p.m_TypeId == get_type_id<T>())
           ? static_cast<T const*>(p.m_Ptr)
           : nullptr;
}

template <typename T> T const* m1::dynamic_pointer_cast(const_any_ptr const &p)
{
    try
    {
        if(T const * const result = static_pointer_cast<T>(p))
        {
            return result;
        }

        if(p.m_TypeId) p.m_TypeId();
        return nullptr;
    }
    catch(T const*)
    {
        return static_cast<T const*>(p.m_Ptr);
    }
    catch(...)
    {
        return nullptr;
    }
}

#endif // M1_ANY_PTR_HPP
