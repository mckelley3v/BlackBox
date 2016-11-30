#ifndef M1_RANGE_VIEW_HPP
#define M1_RANGE_VIEW_HPP

#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <type_traits>
#include <cstddef>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename ForwardItr,
              typename ForwardEnd = ForwardItr>
    class forward_range_view;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename BidirectionalItr,
              typename BidirectionalEnd = BidirectionalItr>
    class bidirectional_range_view;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename RandomAccessItr,
              typename RandomAccessEnd = RandomAccessItr>
    class random_access_range_view;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    using array_view = random_access_range_view<T const*>;

    // ================================================================================================================

    template <typename C>
    auto make_range_view(C &&c) = delete;

    template <typename C>
    auto make_range_view(C const &c);

    template <typename Itr,
              typename End>
    auto make_range_view(Itr &&itr,
                         End &&end);

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T,
              std::size_t N>
    array_view<T> make_array_view(T const (&array)[N]);

    template <typename T>
    array_view<T> make_array_view(T const *array, std::size_t count);

    template <typename T>
    array_view<T> make_array_view(T const *begin, T const *end);

    // ================================================================================================================

    template <typename T>
    struct is_const_pointer : std::false_type {};

    template <typename T>
    struct is_const_pointer<T const*> : std::true_type {};

    template <typename Itr>
    struct is_const_iterator : is_const_pointer<typename std::iterator_traits<Itr>::pointer> {};

    // ================================================================================================================

    template <typename Itr,
              typename End>
    struct range_view_noexcept_traits
    {
        constexpr static bool const nothrow_default_constructible = std::is_nothrow_default_constructible<Itr>::value &&
                                                                    std::is_nothrow_default_constructible<End>::value;

        constexpr static bool const nothrow_move_constructible = std::is_nothrow_move_constructible<Itr>::value &&
                                                                 std::is_nothrow_move_constructible<End>::value;

        constexpr static bool const nothrow_copy_constructible = std::is_nothrow_copy_constructible<Itr>::value &&
                                                                 std::is_nothrow_copy_constructible<End>::value;

        constexpr static bool const nothrow_move_assignable = std::is_nothrow_move_assignable<Itr>::value &&
                                                              std::is_nothrow_move_assignable<End>::value;

        constexpr static bool const nothrow_copy_assignable = std::is_nothrow_copy_assignable<Itr>::value &&
                                                              std::is_nothrow_copy_assignable<End>::value;

        constexpr static bool const nothrow_destructible = std::is_nothrow_destructible<Itr>::value &&
                                                           std::is_nothrow_destructible<End>::value;

        constexpr static bool const nothrow_swappable = nothrow_move_constructible && nothrow_move_assignable;
        //constexpr static bool const nothrow_swappable = std::is_nothrow_swappable<Itr>::value &&
        //                                                std::is_nothrow_swappable<End>::value;
    };

    // ================================================================================================================

    template <typename ForwardItr,
              typename ForwardEnd>
    class forward_range_view
    {
        typedef range_view_noexcept_traits<ForwardItr, ForwardEnd> noexcept_traits;

        // requirements:
        static_assert(is_const_iterator<ForwardItr>::value, "ForwardItr is expected to be a const_iterator");

    public:
        // types:
        typedef ForwardItr                                const_iterator;
        typedef ForwardEnd                                terminator;
        typedef std::iterator_traits<ForwardItr>          iterator_traits;
        typedef typename iterator_traits::value_type      value_type;
        typedef typename iterator_traits::reference       const_reference;
        typedef typename iterator_traits::difference_type difference_type;
        typedef std::size_t                               size_type;

        // construct:
        forward_range_view() noexcept(noexcept_traits::nothrow_default_constructible) = default;
        forward_range_view(ForwardItr &&itr,
                           ForwardEnd &&end) noexcept(noexcept_traits::nothrow_move_constructible);
        forward_range_view(ForwardItr const &itr,
                           ForwardEnd const &end) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move construct:
        forward_range_view(forward_range_view &&rhs) noexcept(noexcept_traits::nothrow_move_constructible) = default;
        forward_range_view(bidirectional_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible);
        forward_range_view(random_access_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible);

        // copy construct:
        forward_range_view(forward_range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible) = default;
        forward_range_view(bidirectional_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible);
        forward_range_view(random_access_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move assign:
        forward_range_view& operator = (forward_range_view &&rhs) noexcept(noexcept_traits::nothrow_move_assignable) = default;
        forward_range_view& operator = (bidirectional_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable);
        forward_range_view& operator = (random_access_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable);

        // copy assign:
        forward_range_view& operator = (forward_range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable) = default;
        forward_range_view& operator = (bidirectional_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable);
        forward_range_view& operator = (random_access_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable);

        // destruct:
        ~forward_range_view() noexcept(noexcept_traits::nothrow_destructible) = default;

        // methods:
        bool empty() const;

        const_iterator begin() const;
        const_iterator cbegin() const;

        terminator end() const;
        terminator cend() const;

        const_reference front() const;

        void swap(forward_range_view &rhs) noexcept(noexcept_traits::nothrow_swappable);

    private:
        // members:
        ForwardItr m_Itr {};
        ForwardEnd m_End {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename ForwardItr, typename ForwardEnd> void swap(forward_range_view<ForwardItr, ForwardEnd> &lhs,
                                                                  forward_range_view<ForwardItr, ForwardEnd> &rhs);

    // operators:
    template <typename ForwardItr, typename ForwardEnd> bool operator == (forward_range_view<ForwardItr, ForwardEnd> const &lhs,
                                                                          forward_range_view<ForwardItr, ForwardEnd> const &rhs);

    template <typename ForwardItr, typename ForwardEnd> bool operator != (forward_range_view<ForwardItr, ForwardEnd> const &lhs,
                                                                          forward_range_view<ForwardItr, ForwardEnd> const &rhs);

    // ================================================================================================================

    template <typename BidirectionalItr,
              typename BidirectionalEnd>
    class bidirectional_range_view
    {
        friend class forward_range_view<BidirectionalItr, BidirectionalEnd>;
        typedef range_view_noexcept_traits<BidirectionalItr, BidirectionalEnd> noexcept_traits;

        // requirements:
        static_assert(is_const_iterator<BidirectionalItr>::value, "BidirectionalItr is expected to be a const_iterator");

    public:
        // types:
        typedef BidirectionalItr                          const_iterator;
        typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;
        typedef BidirectionalEnd                          terminator;
        typedef std::reverse_iterator<terminator>         const_reverse_terminator;
        typedef std::iterator_traits<BidirectionalItr>    iterator_traits;
        typedef typename iterator_traits::value_type      value_type;
        typedef typename iterator_traits::reference       const_reference;
        typedef typename iterator_traits::difference_type difference_type;
        typedef std::size_t                               size_type;

        // construct:
        bidirectional_range_view() noexcept(noexcept_traits::nothrow_default_constructible) = default;
        bidirectional_range_view(BidirectionalItr &&itr,
                                 BidirectionalEnd &&end) noexcept(noexcept_traits::nothrow_move_constructible);
        bidirectional_range_view(BidirectionalItr const &itr,
                                 BidirectionalEnd const &end) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move construct:
        bidirectional_range_view(bidirectional_range_view &&rhs) noexcept(noexcept_traits::nothrow_move_constructible) = default;
        bidirectional_range_view(random_access_range_view<BidirectionalItr, BidirectionalEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible);

        // copy construct:
        bidirectional_range_view(bidirectional_range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible) = default;
        bidirectional_range_view(random_access_range_view<BidirectionalItr, BidirectionalEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move assign:
        bidirectional_range_view& operator = (bidirectional_range_view &&rhs) noexcept(noexcept_traits::nothrow_move_assignable) = default;
        bidirectional_range_view& operator = (random_access_range_view<BidirectionalItr, BidirectionalEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable);

        // copy assign:
        bidirectional_range_view& operator = (bidirectional_range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable) = default;
        bidirectional_range_view& operator = (random_access_range_view<BidirectionalItr, BidirectionalEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable);

        // destruct:
        ~bidirectional_range_view() noexcept(noexcept_traits::nothrow_destructible) = default;

        // methods:
        bool empty() const;

        const_iterator begin() const;
        const_iterator cbegin() const;

        terminator end() const;
        terminator cend() const;

        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const;

        const_reverse_terminator rend() const;
        const_reverse_terminator crend() const;

        const_reference front() const;
        const_reference back() const;

        void swap(bidirectional_range_view &rhs) noexcept(noexcept_traits::nothrow_swappable);

    private:
        // members:
        BidirectionalItr m_Itr {};
        BidirectionalEnd m_End {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename BidirectionalItr, typename BidirectionalEnd> void swap(bidirectional_range_view<BidirectionalItr, BidirectionalEnd> &lhs,
                                                                              bidirectional_range_view<BidirectionalItr, BidirectionalEnd> &rhs);

    // operators:
    template <typename BidirectionalItr, typename BidirectionalEnd> bool operator == (bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &lhs,
                                                                                      bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &rhs);

    template <typename BidirectionalItr, typename BidirectionalEnd> bool operator != (bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &lhs,
                                                                                      bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &rhs);

    // ================================================================================================================

    template <typename RandomAccessItr,
              typename RandomAccessEnd>
    class random_access_range_view
    {
        friend class forward_range_view<RandomAccessItr, RandomAccessEnd>;
        friend class bidirectional_range_view<RandomAccessItr, RandomAccessEnd>;
        typedef range_view_noexcept_traits<RandomAccessItr, RandomAccessEnd> noexcept_traits;

        // requirements:
        static_assert(is_const_iterator<RandomAccessItr>::value, "RandomAccessItr is expected to be a const_iterator");

    public:
        // types:
        typedef RandomAccessItr                           const_iterator;
        typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;
        typedef RandomAccessEnd                           terminator;
        typedef std::reverse_iterator<terminator>         const_reverse_terminator;
        typedef std::iterator_traits<RandomAccessItr>     iterator_traits;
        typedef typename iterator_traits::value_type      value_type;
        typedef typename iterator_traits::reference       const_reference;
        typedef typename iterator_traits::difference_type difference_type;
        typedef std::size_t                               size_type;

        // construct:
        random_access_range_view() noexcept(noexcept_traits::nothrow_default_constructible) = default;
        random_access_range_view(RandomAccessItr &&itr,
                                 RandomAccessEnd &&end) noexcept(noexcept_traits::nothrow_move_constructible);
        random_access_range_view(RandomAccessItr const &itr,
                                 RandomAccessEnd const &end) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move construct:
        random_access_range_view(random_access_range_view &&rhs) noexcept(noexcept_traits::nothrow_move_constructible) = default;

        // copy construct:
        random_access_range_view(random_access_range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible) = default;

        // move assign:
        random_access_range_view& operator = (random_access_range_view &&rhs) noexcept(noexcept_traits::nothrow_move_assignable) = default;

        // copy assign:
        random_access_range_view& operator = (random_access_range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable) = default;

        // destruct:
        ~random_access_range_view() noexcept(noexcept_traits::nothrow_destructible) = default;

        // methods:
        bool empty() const;
        size_type size() const;

        const_iterator begin() const;
        const_iterator cbegin() const;

        terminator end() const;
        terminator cend() const;

        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const;

        const_reverse_terminator rend() const;
        const_reverse_terminator crend() const;

        const_reference at(size_type index) const;
        const_reference operator [] (size_type index) const;

        const_reference front() const;
        const_reference back() const;

        void swap(random_access_range_view &rhs) noexcept(noexcept_traits::nothrow_swappable);

    private:
        // members:
        RandomAccessItr m_Itr {};
        RandomAccessEnd m_End {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    template <typename RandomAccessItr, typename RandomAccessEnd> void swap(random_access_range_view<RandomAccessItr, RandomAccessEnd> &lhs,
                                                                            random_access_range_view<RandomAccessItr, RandomAccessEnd> &rhs);

    // operators:
    template <typename RandomAccessItr, typename RandomAccessEnd> bool operator == (random_access_range_view<RandomAccessItr, RandomAccessEnd> const &lhs,
                                                                                    random_access_range_view<RandomAccessItr, RandomAccessEnd> const &rhs);

    template <typename RandomAccessItr, typename RandomAccessEnd> bool operator != (random_access_range_view<RandomAccessItr, RandomAccessEnd> const &lhs,
                                                                                    random_access_range_view<RandomAccessItr, RandomAccessEnd> const &rhs);

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    template <typename Itr,
              typename End>
    auto make_range_view_impl(Itr &&itr,
                              End &&end,
                              std::forward_iterator_tag)
    {
        return forward_range_view<Itr, End>(std::forward<Itr>(itr),
                                            std::forward<End>(end));
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename Itr,
              typename End>
    auto make_range_view_impl(Itr &&itr,
                              End &&end,
                              std::bidirectional_iterator_tag)
    {
        return bidirectional_range_view<Itr, End>(std::forward<Itr>(itr),
                                                  std::forward<End>(end));
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename Itr,
              typename End>
    auto make_range_view_impl(Itr &&itr,
                              End &&end,
                              std::random_access_iterator_tag)
    {
        return random_access_range_view<Itr, End>(std::forward<Itr>(itr),
                                                  std::forward<End>(end));
    }

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================
// m1::make_range_view
// ====================================================================================================================

template <typename C>
auto m1::make_range_view(C const &c)
{
    using std::cbegin;
    using std::cend;
    return impl::make_range_view_impl(cbegin(c),
                                      cend(c),
                                      std::iterator_traits<typename C::const_iterator>::iterator_category());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Itr,
          typename End>
auto m1::make_range_view(Itr &&itr, End &&end)
{
    return impl::make_range_view_impl(std::forward<Itr>(itr),
                                      std::forward<End>(end),
                                      std::iterator_traits<Itr>::iterator_category());
}

// ====================================================================================================================
// m1::make_array_view
// ====================================================================================================================

template <typename T,
          std::size_t N>
m1::array_view<T> m1::make_array_view(T const (&array)[N])
{
    return array_view<T>(array, array + N);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::array_view<T> m1::make_array_view(T const * const array, std::size_t const count)
{
    return array_view<T>(array, array + count);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::array_view<T> m1::make_array_view(T const * const begin, T const * const end)
{
    return array_view<T>(begin, end);
}

// ====================================================================================================================
// m1::forward_range_view
// ====================================================================================================================

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>::forward_range_view(ForwardItr &&itr,
                                                                   ForwardEnd &&end) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(itr))
    , m_End(std::move_if_noexcept(end))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>::forward_range_view(ForwardItr const &itr,
                                                                   ForwardEnd const &end) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(itr)
    , m_End(end)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>::forward_range_view(bidirectional_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(rhs.m_Itr))
    , m_End(std::move_if_noexcept(rhs.m_End))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>::forward_range_view(random_access_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(rhs.m_Itr))
    , m_End(std::move_if_noexcept(rhs.m_End))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>::forward_range_view(bidirectional_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(rhs.m_Itr)
    , m_End(rhs.m_End)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>::forward_range_view(random_access_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(rhs.m_Itr)
    , m_End(rhs.m_End)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>& m1::forward_range_view<ForwardItr, ForwardEnd>::operator = (bidirectional_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable)
{
    m_Itr = std::move_if_noexcept(rhs.m_Itr);
    m_End = std::move_if_noexcept(rhs.m_End);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>& m1::forward_range_view<ForwardItr, ForwardEnd>::operator = (random_access_range_view<ForwardItr, ForwardEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable)
{
    m_Itr = std::move_if_noexcept(rhs.m_Itr);
    m_End = std::move_if_noexcept(rhs.m_End);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>& m1::forward_range_view<ForwardItr, ForwardEnd>::operator = (bidirectional_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable)
{
    m_Itr = rhs.m_Itr;
    m_End = rhs.m_End;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
m1::forward_range_view<ForwardItr, ForwardEnd>& m1::forward_range_view<ForwardItr, ForwardEnd>::operator = (random_access_range_view<ForwardItr, ForwardEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable)
{
    m_Itr = rhs.m_Itr;
    m_End = rhs.m_End;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
bool m1::forward_range_view<ForwardItr, ForwardEnd>::empty() const
{
    return m_Itr == m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
typename m1::forward_range_view<ForwardItr, ForwardEnd>::const_iterator m1::forward_range_view<ForwardItr, ForwardEnd>::begin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
typename m1::forward_range_view<ForwardItr, ForwardEnd>::const_iterator m1::forward_range_view<ForwardItr, ForwardEnd>::cbegin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
typename m1::forward_range_view<ForwardItr, ForwardEnd>::terminator m1::forward_range_view<ForwardItr, ForwardEnd>::end() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
typename m1::forward_range_view<ForwardItr, ForwardEnd>::terminator m1::forward_range_view<ForwardItr, ForwardEnd>::cend() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
typename m1::forward_range_view<ForwardItr, ForwardEnd>::const_reference m1::forward_range_view<ForwardItr, ForwardEnd>::front() const
{
    return *m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
void m1::forward_range_view<ForwardItr, ForwardEnd>::swap(forward_range_view &rhs) noexcept(noexcept_traits::nothrow_swappable)
{
    using std::swap;
    swap(m_Itr, rhs.m_Itr);
    swap(m_End, rhs.m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
void m1::swap(forward_range_view<ForwardItr, ForwardEnd> &lhs,
              forward_range_view<ForwardItr, ForwardEnd> &rhs)
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
bool m1::operator == (forward_range_view<ForwardItr, ForwardEnd> const &lhs,
                      forward_range_view<ForwardItr, ForwardEnd> const &rhs)
{
    return std::equal(lhs.begin(), lhs.end(),
                      rhs.begin(), rhs.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardItr, typename ForwardEnd>
bool m1::operator != (forward_range_view<ForwardItr, ForwardEnd> const &lhs,
                      forward_range_view<ForwardItr, ForwardEnd> const &rhs)
{
    return !(lhs == rhs);
}

// ====================================================================================================================
// m1::bidirectional_range_view
// ====================================================================================================================

template <typename BidirectionalItr, typename BidirectionalEnd>
m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::bidirectional_range_view(BidirectionalItr &&itr,
                                                                                           BidirectionalEnd &&end) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(itr))
    , m_End(std::move_if_noexcept(end))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::bidirectional_range_view(BidirectionalItr const &itr,
                                                                                           BidirectionalEnd const &end) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(itr)
    , m_End(end)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::bidirectional_range_view(random_access_range_view<BidirectionalItr, BidirectionalEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(rhs.m_Itr))
    , m_End(std::move_if_noexcept(rhs.m_End))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::bidirectional_range_view(random_access_range_view<BidirectionalItr, BidirectionalEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(rhs.m_Itr)
    , m_End(rhs.m_End)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>& m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::operator = (random_access_range_view<BidirectionalItr, BidirectionalEnd> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable)
{
    m_Itr = std::move_if_noexcept(rhs.m_Itr);
    m_End = std::move_if_noexcept(rhs.m_End);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>& m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::operator = (random_access_range_view<BidirectionalItr, BidirectionalEnd> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable)
{
    m_Itr = rhs.m_Itr;
    m_End = rhs.m_End;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
bool m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::empty() const
{
    return m_Itr == m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_iterator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::begin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_iterator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::cbegin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::terminator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::end() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::terminator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::cend() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_reverse_iterator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::rbegin() const
{
    return const_reverse_iterator(m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_reverse_iterator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::crbegin() const
{
    return const_reverse_iterator(m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_reverse_terminator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::rend() const
{
    return const_reverse_iterator(m_Itr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_reverse_terminator m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::crend() const
{
    return const_reverse_iterator(m_Itr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_reference m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::front() const
{
    return *m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
typename m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::const_reference m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::back() const
{
    return *std::prev(m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
void m1::bidirectional_range_view<BidirectionalItr, BidirectionalEnd>::swap(bidirectional_range_view &rhs) noexcept(noexcept_traits::nothrow_swappable)
{
    using std::swap;
    swap(m_Itr, rhs.m_Itr);
    swap(m_End, rhs.m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
void m1::swap(bidirectional_range_view<BidirectionalItr, BidirectionalEnd> &lhs,
              bidirectional_range_view<BidirectionalItr, BidirectionalEnd> &rhs)
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
bool m1::operator == (bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &lhs,
                      bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &rhs)
{
    return std::equal(lhs.begin(), lhs.end(),
                      rhs.begin(), rhs.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename BidirectionalItr, typename BidirectionalEnd>
bool m1::operator != (bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &lhs,
                      bidirectional_range_view<BidirectionalItr, BidirectionalEnd> const &rhs)
{
    return !(lhs == rhs);
}

// ====================================================================================================================
// m1::random_access_range_view
// ====================================================================================================================

template <typename RandomAccessItr, typename RandomAccessEnd>
m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::random_access_range_view(RandomAccessItr &&itr,
                                                                                         RandomAccessEnd &&end) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(itr))
    , m_End(std::move_if_noexcept(end))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::random_access_range_view(RandomAccessItr const &itr,
                                                                                         RandomAccessEnd const &end) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(itr)
    , m_End(end)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
bool m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::empty() const
{
    return m_Itr == m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::size_type m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::size() const
{
    return static_cast<size_type>(std::distance(m_Itr, m_End));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_iterator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::begin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_iterator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::cbegin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::terminator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::end() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::terminator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::cend() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reverse_iterator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::rbegin() const
{
    return const_reverse_iterator(m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reverse_iterator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::crbegin() const
{
    return const_reverse_iterator(m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reverse_terminator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::rend() const
{
    return const_reverse_iterator(m_Itr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reverse_terminator m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::crend() const
{
    return const_reverse_iterator(m_Itr);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reference m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::at(size_type const index) const
{
    if (index < size())
    {
        return m_Itr[index];
    }

    throw std::out_of_range("invalid index");
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reference m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::operator [] (size_type const index) const
{
    return m_Itr[index];
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reference m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::front() const
{
    return *m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
typename m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::const_reference m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::back() const
{
    return *std::prev(m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
void m1::random_access_range_view<RandomAccessItr, RandomAccessEnd>::swap(random_access_range_view &rhs) noexcept(noexcept_traits::nothrow_swappable)
{
    using std::swap;
    swap(m_Itr, rhs.m_Itr);
    swap(m_End, rhs.m_End);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
void m1::swap(random_access_range_view<RandomAccessItr, RandomAccessEnd> &lhs,
              random_access_range_view<RandomAccessItr, RandomAccessEnd> &rhs)
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
bool m1::operator == (random_access_range_view<RandomAccessItr, RandomAccessEnd> const &lhs,
                      random_access_range_view<RandomAccessItr, RandomAccessEnd> const &rhs)
{
    return std::equal(lhs.begin(), lhs.end(),
                      rhs.begin(), rhs.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename RandomAccessItr, typename RandomAccessEnd>
bool m1::operator != (random_access_range_view<RandomAccessItr, RandomAccessEnd> const &lhs,
                      random_access_range_view<RandomAccessItr, RandomAccessEnd> const &rhs)
{
    return !(lhs == rhs);
}

// ====================================================================================================================

#endif // M1_RANGE_VIEW_HPP
