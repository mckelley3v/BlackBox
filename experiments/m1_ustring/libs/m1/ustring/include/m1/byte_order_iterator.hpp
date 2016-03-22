#ifndef M1_BYTE_ORDER_ITERATOR_HPP
#define M1_BYTE_ORDER_ITERATOR_HPP

#include "m1/byte_order.hpp"
#include <iterator>
#include <utility>

namespace m1
{
    // ================================================================================================================

    template <typename Itr>
    class swap_byte_order_iterator;

    template <typename Itr>
    using big_endian_iterator = std::conditional_t<native_byte_order() == byte_order::big_endian,
                                                   Itr,
                                                   swap_byte_order_iterator<Itr>>;

    template <typename Itr>
    using little_endian_iterator = std::conditional_t<native_byte_order() == byte_order::little_endian,
                                                      Itr,
                                                      swap_byte_order_iterator<Itr>>;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename Itr>
    big_endian_iterator<Itr> make_big_endian_iterator(Itr const &itr);

    template <typename Itr>
    little_endian_iterator<Itr> make_little_endian_iterator(Itr const &itr);

    // ================================================================================================================

    template <typename Itr>
    class swap_byte_order_iterator
        : public std::iterator<typename std::iterator_traits<Itr>::iterator_category,
                               typename std::iterator_traits<Itr>::value_type,
                               typename std::iterator_traits<Itr>::difference_type,
                               typename std::iterator_traits<Itr>::reference,
                               typename std::iterator_traits<Itr>::pointer>
    {
    public:
        swap_byte_order_iterator() noexcept = default;
        explicit swap_byte_order_iterator(Itr &&itr) noexcept;
        explicit swap_byte_order_iterator(Itr const &itr) noexcept;
        swap_byte_order_iterator(swap_byte_order_iterator &&rhs) noexcept = default;
        swap_byte_order_iterator(swap_byte_order_iterator const &rhs) noexcept = default;
        swap_byte_order_iterator& operator = (swap_byte_order_iterator &&rhs) noexcept = default;
        swap_byte_order_iterator& operator = (swap_byte_order_iterator const &rhs) noexcept = default;
        ~swap_byte_order_iterator() noexcept = default;

        value_type operator * () const noexcept;
        value_type operator [] (difference_type n) const noexcept;

        swap_byte_order_iterator& operator ++ () noexcept;
        swap_byte_order_iterator operator ++ (int) noexcept;
        swap_byte_order_iterator& operator -- () noexcept;
        swap_byte_order_iterator operator -- (int) noexcept;

        swap_byte_order_iterator& operator += (difference_type n) noexcept;
        swap_byte_order_iterator& operator -= (difference_type n) noexcept;

        void swap(swap_byte_order_iterator &rhs) noexcept;

        template <typename I>
        friend swap_byte_order_iterator<I> operator + (swap_byte_order_iterator<I> const &lhs,
                                                    difference_type rhs) noexcept;

        template <typename I>
        friend swap_byte_order_iterator<I> operator + (difference_type lhs,
                                                    swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend difference_type operator - (swap_byte_order_iterator<I> const &lhs,
                                           swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend bool operator == (swap_byte_order_iterator<I> const &lhs,
                                 swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend bool operator != (swap_byte_order_iterator<I> const &lhs,
                                 swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend bool operator < (swap_byte_order_iterator<I> const &lhs,
                                swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend bool operator <= (swap_byte_order_iterator<I> const &lhs,
                                 swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend bool operator > (swap_byte_order_iterator<I> const &lhs,
                                swap_byte_order_iterator<I> const &rhs) noexcept;

        template <typename I>
        friend bool operator >= (swap_byte_order_iterator<I> const &lhs,
                                 swap_byte_order_iterator<I> const &rhs) noexcept;

    private:
        // members:
        Itr m_Itr {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    extern template swap_byte_order_iterator<char16_t*>;
    extern template swap_byte_order_iterator<char16_t const*>;
    extern template swap_byte_order_iterator<char32_t*>;
    extern template swap_byte_order_iterator<char32_t const*>;
    extern template swap_byte_order_iterator<std::uint16_t*>;
    extern template swap_byte_order_iterator<std::uint16_t const*>;
    extern template swap_byte_order_iterator<std::uint32_t*>;
    extern template swap_byte_order_iterator<std::uint32_t const*>;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename Itr>
    swap_byte_order_iterator<Itr> operator + (swap_byte_order_iterator<Itr> const &lhs,
                                              typename swap_byte_order_iterator<Itr>::difference_type rhs) noexcept;

    template <typename Itr>
    swap_byte_order_iterator<Itr> operator + (typename swap_byte_order_iterator<Itr>::difference_type lhs,
                                              swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    typename swap_byte_order_iterator<Itr>::difference_type operator - (swap_byte_order_iterator<Itr> const &lhs,
                                                                        swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    bool operator == (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    bool operator != (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    bool operator < (swap_byte_order_iterator<Itr> const &lhs,
                     swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    bool operator <= (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    bool operator > (swap_byte_order_iterator<Itr> const &lhs,
                     swap_byte_order_iterator<Itr> const &rhs) noexcept;

    template <typename Itr>
    bool operator >= (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    template <typename Itr>
    void swap(m1::swap_byte_order_iterator<Itr> &lhs,
              m1::swap_byte_order_iterator<Itr> &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================
// ====================================================================================================================

template <typename Itr>
/*explicit*/ m1::swap_byte_order_iterator<Itr>::swap_byte_order_iterator(Itr &&itr) noexcept
    : m_Itr(std::move(itr))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
/*explicit*/ m1::swap_byte_order_iterator<Itr>::swap_byte_order_iterator(Itr const &itr) noexcept
    : m_Itr(itr)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
typename m1::swap_byte_order_iterator<Itr>::value_type m1::swap_byte_order_iterator<Itr>::operator * () const noexcept
{
    return swap_byte_order(*m_Itr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
typename m1::swap_byte_order_iterator<Itr>::value_type m1::swap_byte_order_iterator<Itr>::operator [] (difference_type n) const noexcept
{
    return swap_byte_order(m_Itr[n]);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr>& m1::swap_byte_order_iterator<Itr>::operator ++ () noexcept
{
    ++m_Itr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr> m1::swap_byte_order_iterator<Itr>::operator ++ (int) noexcept
{
    swap_byte_order_iterator result(*this);
    ++(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr>& m1::swap_byte_order_iterator<Itr>::operator -- () noexcept
{
    --m_Itr;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr> m1::swap_byte_order_iterator<Itr>::operator -- (int) noexcept
{
    swap_byte_order_iterator result(*this);
    --(*this);
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr>& m1::swap_byte_order_iterator<Itr>::operator += (difference_type n) noexcept
{
    m_Itr += n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr>& m1::swap_byte_order_iterator<Itr>::operator -= (difference_type n) noexcept
{
    m_Itr -= n;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
void m1::swap_byte_order_iterator<Itr>::swap(swap_byte_order_iterator &rhs) noexcept
{
    using std::swap;
    swap(m_Itr, rhs.m_Itr);
}

// ====================================================================================================================

template <typename Itr>
m1::swap_byte_order_iterator<Itr> m1::operator + (swap_byte_order_iterator<Itr> const &lhs,
                                                  typename swap_byte_order_iterator<Itr>::difference_type const rhs) noexcept
{
    return swap_byte_order_iterator<Itr>(lhs.m_Itr + rhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
m1::swap_byte_order_iterator<Itr> m1::operator + (typename swap_byte_order_iterator<Itr>::difference_type const lhs,
                                                  swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return swap_byte_order_iterator<Itr>(lhs + rhs.m_Itr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
typename m1::swap_byte_order_iterator<Itr>::difference_type m1::operator - (swap_byte_order_iterator<Itr> const &lhs,
                                                                            swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr - rhs.m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
bool m1::operator == (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr == rhs.m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
bool m1::operator != (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr != rhs.m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
bool m1::operator < (swap_byte_order_iterator<Itr> const &lhs,
                     swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr < rhs.m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
bool m1::operator <= (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr <= rhs.m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
bool m1::operator > (swap_byte_order_iterator<Itr> const &lhs,
                     swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr > rhs.m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr>
bool m1::operator >= (swap_byte_order_iterator<Itr> const &lhs,
                      swap_byte_order_iterator<Itr> const &rhs) noexcept
{
    return lhs.m_Itr >= rhs.m_Itr;
}

// ====================================================================================================================

template <typename Itr>
m1::big_endian_iterator<Itr> m1::make_big_endian_iterator(Itr const &itr)
{
    return big_endian_iterator<Itr>(itr);
}

// ====================================================================================================================

template <typename Itr>
m1::little_endian_iterator<Itr> m1::make_little_endian_iterator(Itr const &itr)
{
    return little_endian_iterator<Itr>(itr);
}

// ====================================================================================================================

template <typename Itr>
void std::swap(m1::swap_byte_order_iterator<Itr> &lhs,
               m1::swap_byte_order_iterator<Itr> &rhs) noexcept
{
    lhs.swap(rhs);
}

// ====================================================================================================================

#endif // M1_BYTE_ORDER_ITERATOR_HPP
