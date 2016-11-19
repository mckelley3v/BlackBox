#ifndef M1_RANGE_VIEW_HPP
#define M1_RANGE_VIEW_HPP

#include <iterator>
#include <type_traits>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename ForwardIterator,
              typename Terminator = ForwardIterator>
    class range_view;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename BidirectionalIterator,
              typename Terminator = BidirectionalIterator>
    class bidirectional_range_view;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename RandomAccessIterator,
              typename Terminator = RandomAccessIterator>
    class random_access_range_view;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    using array_view = random_access_range_view<T const*>;

    // ================================================================================================================

    template <typename C>
    auto make_range_view(C const &c);

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

    template <typename Iterator>
    struct is_const_iterator : is_const_pointer<typename std::iterator_traits<Iterator>::pointer> {};

    // ================================================================================================================

    template <typename Iterator,
              typename Terminator>
    struct range_view_noexcept_traits
    {
        //constexpr static bool const nothrow_constructible = std::is_nothrow_constructible<Iterator>::value &&
        //                                                    std::is_nothrow_constructible<Terminator>::value;

        constexpr static bool const nothrow_default_constructible = std::is_nothrow_default_constructible<Iterator>::value &&
                                                                    std::is_nothrow_default_constructible<Terminator>::value;

        constexpr static bool const nothrow_move_constructible = std::is_nothrow_move_constructible<Iterator>::value &&
                                                                 std::is_nothrow_move_constructible<Terminator>::value;

        constexpr static bool const nothrow_copy_constructible = std::is_nothrow_copy_constructible<Iterator>::value &&
                                                                 std::is_nothrow_copy_constructible<Terminator>::value;

        //constexpr static bool const nothrow_assignable = std::is_nothrow_assignable<Iterator>::value &&
        //                                                 std::is_nothrow_assignable<Terminator>::value;

        constexpr static bool const nothrow_move_assignable = std::is_nothrow_move_assignable<Iterator>::value &&
                                                              std::is_nothrow_move_assignable<Terminator>::value;

        constexpr static bool const nothrow_copy_assignable = std::is_nothrow_copy_assignable<Iterator>::value &&
                                                              std::is_nothrow_copy_assignable<Terminator>::value;

        constexpr static bool const nothrow_destructible = std::is_nothrow_destructible<Iterator>::value &&
                                                           std::is_nothrow_destructible<Terminator>::value;

        constexpr static bool const nothrow_swappable = true;
        //constexpr static bool const nothrow_swappable = std::is_nothrow_swappable<Iterator>::value &&
        //                                                std::is_nothrow_swappable<Terminator>::value;
    };

    // ================================================================================================================

    template <typename ForwardIterator,
              typename Terminator>
    class range_view
    {
        typedef range_view_noexcept_traits<ForwardIterator, Terminator> noexcept_traits;

        // requirements:
        static_assert(is_const_iterator<ForwardIterator>::value, "ForwardIterator is expected to be a const_iterator");

    public:
        // types:
        typedef ForwardIterator                           const_iterator;
        typedef Terminator                                terminator;
        typedef std::iterator_traits<ForwardIterator>     iterator_traits;
        typedef typename iterator_traits::value_type      value_type;
        typedef typename iterator_traits::reference       const_reference;
        typedef typename iterator_traits::difference_type difference_type;
        //typedef typename iterator_traits::size_type       size_type;

        // construct:
        range_view() noexcept(noexcept_traits::nothrow_default_constructible) = default;
        range_view(ForwardIterator &&itr,
                   Terminator &&end) noexcept(noexcept_traits::nothrow_move_constructible);
        range_view(ForwardIterator const &itr,
                   Terminator const &end) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move construct:
        range_view(range_view &&rhs) noexcept(noexcept_traits::nothrow_move_constructible) = default;
        range_view(bidirectional_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible);
        range_view(random_access_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible);

        // copy construct:
        range_view(range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible) = default;
        range_view(bidirectional_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible);
        range_view(random_access_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible);

        // move assign:
        range_view& operator = (range_view &&rhs) noexcept(noexcept_traits::nothrow_move_assignable) = default;
        range_view& operator = (bidirectional_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable);
        range_view& operator = (random_access_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable);

        // copy assign:
        range_view& operator = (range_view const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable) = default;
        range_view& operator = (bidirectional_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable);
        range_view& operator = (random_access_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable);

        // destruct:
        ~range_view() noexcept(noexcept_traits::nothrow_destructible) = default;

        // methods:
        bool empty() const;

        const_iterator begin() const;
        const_iterator cbegin() const;

        terminator end() const;
        terminator cend() const;

        void swap(range_view &rhs) noexcept(noexcept_traits::nothrow_swappable);

    private:
        // members:
        ForwardIterator m_Itr {};
        Terminator      m_End {};
    };

    // ----------------------------------------------------------------------------------------------------------------

    // operators:
    template <typename ForwardIterator, typename Terminator> bool operator == (range_view<ForwardIterator, Terminator> const &lhs,
                                                                               range_view<ForwardIterator, Terminator> const &rhs);

    template <typename ForwardIterator, typename Terminator> bool operator != (range_view<ForwardIterator, Terminator> const &lhs,
                                                                               range_view<ForwardIterator, Terminator> const &rhs);

    // ================================================================================================================

    template <typename BidirectionalIterator,
              typename Terminator>
    class bidirectional_range_view
    {
        friend class range_view<BidirectionalIterator, Terminator>;
    public:

    private:
        // members:
        BidirectionalIterator m_Itr {};
        Terminator            m_End {};
    };

    // ================================================================================================================

    template <typename RandomAccessIterator,
              typename Terminator>
    class random_access_range_view
    {
        friend class range_view<RandomAccessIterator, Terminator>;
        friend class bidirectional_range_view<RandomAccessIterator, Terminator>;

    public:

    private:
        // members:
        RandomAccessIterator m_Itr {};
        Terminator           m_End {};
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    template <typename C>
    auto make_range_view_impl(C const &c, std::forward_iterator_tag)
    {
        return range_view<decltype(c.begin()), decltype(c.end())>(c.begin(), c.end());
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename C>
    auto make_range_view_impl(C const &c, std::bidirectional_iterator_tag)
    {
        return bidirectional_range_view<decltype(c.begin()), decltype(c.end())>(c.begin(), c.end());
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename C>
    auto make_range_view_impl(C const &c, std::random_access_iterator_tag)
    {
        return random_access_range_view<decltype(c.begin()), decltype(c.end())>(c.begin(), c.end());
    }

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================

template <typename C>
auto m1::make_range_view(C const &c)
{
    return impl::make_range_view_impl(c, std::iterator_traits<typename C::const_iterator>::iterator_category());
}

// ====================================================================================================================

template <typename T,
            std::size_t N>
m1::array_view<T> m1::make_array_view(T const (&array)[N])
{
    return array_view<T>(array, array + N);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::array_view<T> m1::make_array_view(T const *array, std::size_t count)
{
    return array_view<T>(array, array + count);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::array_view<T> m1::make_array_view(T const *begin, T const *end)
{
    return array_view<T>(begin, end);
}

// ====================================================================================================================

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>::range_view(ForwardIterator &&itr,
                                                        Terminator &&end) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(itr))
    , m_End(std::move_if_noexcept(end))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>::range_view(ForwardIterator const &itr,
                                                        Terminator const &end) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(itr)
    , m_End(end)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>::range_view(bidirectional_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(rhs.m_Itr))
    , m_End(std::move_if_noexcept(rhs.m_End))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>::range_view(random_access_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_constructible)
    : m_Itr(std::move_if_noexcept(rhs.m_Itr))
    , m_End(std::move_if_noexcept(rhs.m_End))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>::range_view(bidirectional_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(rhs.m_Itr)
    , m_End(rhs.m_End)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>::range_view(random_access_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_constructible)
    : m_Itr(rhs.m_Itr)
    , m_End(rhs.m_End)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>& m1::range_view<ForwardIterator, Terminator>::operator = (bidirectional_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable)
{
    m_Itr = std::move_if_noexcept(rhs.m_Itr);
    m_End = std::move_if_noexcept(rhs.m_End);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>& m1::range_view<ForwardIterator, Terminator>::operator = (random_access_range_view<ForwardIterator, Terminator> &&rhs) noexcept(noexcept_traits::nothrow_move_assignable)
{
    m_Itr = std::move_if_noexcept(rhs.m_Itr);
    m_End = std::move_if_noexcept(rhs.m_End);
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>& m1::range_view<ForwardIterator, Terminator>::operator = (bidirectional_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable)
{
    m_Itr = rhs.m_Itr;
    m_End = rhs.m_End;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
m1::range_view<ForwardIterator, Terminator>& m1::range_view<ForwardIterator, Terminator>::operator = (random_access_range_view<ForwardIterator, Terminator> const &rhs) noexcept(noexcept_traits::nothrow_copy_assignable)
{
    m_Itr = rhs.m_Itr;
    m_End = rhs.m_End;
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
bool m1::range_view<ForwardIterator, Terminator>::empty() const
{
    return m_Itr == m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
typename m1::range_view<ForwardIterator, Terminator>::const_iterator m1::range_view<ForwardIterator, Terminator>::begin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
typename m1::range_view<ForwardIterator, Terminator>::const_iterator m1::range_view<ForwardIterator, Terminator>::cbegin() const
{
    return m_Itr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
typename m1::range_view<ForwardIterator, Terminator>::terminator m1::range_view<ForwardIterator, Terminator>::end() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
typename m1::range_view<ForwardIterator, Terminator>::terminator m1::range_view<ForwardIterator, Terminator>::cend() const
{
    return m_End;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForwardIterator, typename Terminator>
void m1::range_view<ForwardIterator, Terminator>::swap(range_view &rhs) noexcept(noexcept_traits::nothrow_swappable)
{
    using std::swap;
    swap(m_Itr, rhs.m_Itr);
    swap(m_End, rhs.m_End);
}

// ====================================================================================================================

#endif // M1_RANGE_VIEW_HPP
