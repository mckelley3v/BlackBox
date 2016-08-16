#ifndef M1_OBSERVER_PTR_HPP
#define M1_OBSERVER_PTR_HPP

#include <utility>
#include <type_traits>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename W>
    class observer_ptr
    {
    public:
        typedef W element_type;

        // construct/move/copy/destroy:
        /*constexpr*/ observer_ptr() /*noexcept*/;
        /*constexpr*/ observer_ptr(std::nullptr_t) /*noexcept*/;
        explicit observer_ptr(element_type *p) /*noexcept*/;
        template <typename W2> observer_ptr(observer_ptr<W2> rhs);
        observer_ptr(observer_ptr &&rhs) /*= default*/;
        observer_ptr(observer_ptr const &rhs) = default;
        observer_ptr& operator = (observer_ptr &&rhs) /*= default*/;
        observer_ptr& operator = (observer_ptr const &rhs) = default;
        ~observer_ptr() = default;

        // modifiers:
        /*constexpr*/ element_type* release() /*noexcept*/;
        /*constexpr*/ void reset(element_type *p = nullptr) /*noexcept*/;
        /*constexpr*/ void swap(observer_ptr &other) /*noexcept*/;

        // observers:
        /*constexpr*/ element_type* get() const /*noexcept*/;
        /*constexpr*/ element_type* operator -> () const /*noexcept*/;
        /*constexpr*/ std::add_lvalue_reference_t<element_type> operator * () const /*noexcept*/;
        /*constexpr*/ explicit operator bool() const /*noexcept*/;
        /*constexpr*/ explicit operator element_type* () const /*noexcept*/;

    private:
        W *m_Ptr;
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename W>
    observer_ptr<W> make_observer(W *p) /*noexcept*/;

    template <typename W>
    void swap(observer_ptr<W> &lhs, observer_ptr<W> &rhs) /*noexcept*/;

    template <typename W>
    std::size_t hash(observer_ptr<W> &p);

    template <typename W>
    bool operator == (observer_ptr<W> const &lhs, std::nullptr_t) /*noexcept*/;

    template <typename W>
    bool operator == (std::nullptr_t, observer_ptr<W> const &rhs) /*noexcept*/;

    template <typename W1, typename W2>
    bool operator == (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/;

    template <typename W>
    bool operator != (observer_ptr<W> const &lhs, std::nullptr_t) /*noexcept*/;

    template <typename W>
    bool operator != (std::nullptr_t, observer_ptr<W> const &rhs) /*noexcept*/;

    template <typename W1, typename W2>
    bool operator != (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/;

    template <typename W1, typename W2>
    bool operator < (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/;

    template <typename W1, typename W2>
    bool operator <= (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/;

    template <typename W1, typename W2>
    bool operator > (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/;

    template <typename W1, typename W2>
    bool operator >= (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

template <typename W>
struct std::hash<m1::observer_ptr<W>>
{
    typedef m1::observer_ptr<W> argument_type;
    typedef std::size_t result_type;

    result_type operator () (argument_type const &arg) const;
};

// ====================================================================================================================

template <typename W>
/*constexpr*/ m1::observer_ptr<W>::observer_ptr() /*noexcept*/
    : m_Ptr{}
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ m1::observer_ptr<W>::observer_ptr(std::nullptr_t) /*noexcept*/
    : m_Ptr{}
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*explicit*/ m1::observer_ptr<W>::observer_ptr(element_type *p) /*noexcept*/
    : m_Ptr{p}
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
template <typename W2>
m1::observer_ptr<W>::observer_ptr(observer_ptr<W2> rhs)
    : m_Ptr(rhs.m_Ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
m1::observer_ptr<W>::observer_ptr(observer_ptr &&rhs) /*= default*/
    : m_Ptr(std::move(rhs))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
m1::observer_ptr<W>& m1::observer_ptr<W>::operator = (observer_ptr &&rhs) /*= default*/
{
    m_Ptr = std::move(rhs.m_Ptr);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ typename m1::observer_ptr<W>::element_type* m1::observer_ptr<W>::release() /*noexcept*/
{
    element_type *result = m_Ptr;
    m_Ptr = nullptr;
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ void m1::observer_ptr<W>::reset(element_type *p = nullptr) /*noexcept*/
{
    m_Ptr = p;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ void m1::observer_ptr<W>::swap(observer_ptr &other) /*noexcept*/
{
    std::swap(m_Ptr, other.m_Ptr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ typename m1::observer_ptr<W>::element_type* m1::observer_ptr<W>::get() const /*noexcept*/
{
    return m_Ptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ typename m1::observer_ptr<W>::element_type* m1::observer_ptr<W>::operator -> () const /*noexcept*/
{
    return m_Ptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ std::add_lvalue_reference_t<typename m1::observer_ptr<W>::element_type> m1::observer_ptr<W>::operator * () const /*noexcept*/
{
    return *m_Ptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ /*explicit*/ m1::observer_ptr<W>::operator bool() const /*noexcept*/
{
    return m_Ptr != nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
/*constexpr*/ /*explicit*/ m1::observer_ptr<W>::operator element_type* () const /*noexcept*/
{
    return m_Ptr;
}

// ====================================================================================================================

template <typename W>
m1::observer_ptr<W> m1::make_observer(W *p) /*noexcept*/
{
    return m1::observer_ptr<W>(p);
}

// ====================================================================================================================

template <typename W>
void m1::swap(observer_ptr<W> &lhs, observer_ptr<W> &rhs) /*noexcept*/
{
    lhs.swap(rhs);
}

// ====================================================================================================================

template <typename W>
std::size_t m1::hash(observer_ptr<W> &p)
{
    return std::hash<W*>()(p.get());
}

// ====================================================================================================================

template <typename W>
bool m1::operator == (observer_ptr<W> const &lhs, std::nullptr_t) /*noexcept*/
{
    return lhs.get() == nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
bool m1::operator == (std::nullptr_t, observer_ptr<W> const &rhs) /*noexcept*/
{
    return nullptr == rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W1, typename W2>
bool m1::operator == (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/
{
    return lhs.get() == rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
bool m1::operator != (observer_ptr<W> const &lhs, std::nullptr_t) /*noexcept*/
{
    return lhs.get() != nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W>
bool m1::operator != (std::nullptr_t, observer_ptr<W> const &rhs) /*noexcept*/
{
    return nullptr != rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W1, typename W2>
bool m1::operator != (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/
{
    return lhs.get() != rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W1, typename W2>
bool m1::operator < (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/
{
    return lhs.get() < rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W1, typename W2>
bool m1::operator <= (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/
{
    return lhs.get() <= rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W1, typename W2>
bool m1::operator > (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/
{
    return lhs.get() > rhs.get();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename W1, typename W2>
bool m1::operator >= (observer_ptr<W1> const &lhs, observer_ptr<W2> const &rhs) /*noexcept*/
{
    return lhs.get() >= rhs.get();
}

// ====================================================================================================================

template <typename W>
typename std::hash<m1::observer_ptr<W>>::result_type std::hash<m1::observer_ptr<W>>::operator () (argument_type const &arg) const
{
    return m1::hash(arg);
}

// ====================================================================================================================

#endif // M1_OBSERVER_PTR_HPP
