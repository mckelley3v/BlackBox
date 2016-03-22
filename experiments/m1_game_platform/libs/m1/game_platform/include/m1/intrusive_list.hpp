#ifndef M1_INTRUSIVE_LIST_HPP
#define M1_INTRUSIVE_LIST_HPP

#include "m1/intrusive_list_impl.hpp"
#include <iterator>
#include <type_traits>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    struct is_iterator;

    // ================================================================================================================
} // namespace m1


// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename ValueType,
              typename NodeAccessTraits>
    class intrusive_list
        : private intrusive_list_impl
    {
    private:
        typedef intrusive_list_impl impl_type;

    public:
        // types:
        typedef ValueType value_type;
        using impl_type::size_type;
        using impl_type::difference_type;

        class iterator;
        class const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // construct/move/copy/destroy:
        intrusive_list() noexcept = default;
        template <typename InputIterator,
                  typename = std::enable_if_t<is_iterator<InputIterator>::value>>
        intrusive_list(InputIterator range_first,
                       InputIterator range_last) noexcept;
        intrusive_list(intrusive_list &&rhs) noexcept;
        intrusive_list& operator = (intrusive_list &&rhs) noexcept;
        ~intrusive_list() noexcept;

        // iterators:
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;

        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

        // capacity:
        using impl_type::empty;

        // element access:
        value_type& front() noexcept;
        value_type const& front() const noexcept;
        value_type& back() noexcept;
        value_type const& back() const noexcept;

        // modifiers:
        void push_front(value_type &node) noexcept;
        void push_back(value_type &node) noexcept;
        using impl_type::pop_front;
        using impl_type::pop_back;

        iterator insert(const_iterator at, value_type &node) noexcept;
        iterator insert(const_iterator at, std::initializer_list<value_type> const &nodes) noexcept;
        template <typename InputIterator,
                  typename = std::enable_if_t<is_iterator<InputIterator>::value>>
        iterator insert(const_iterator at,
                        InputIterator range_first,
                        InputIterator range_last) noexcept;

        iterator erase(const_iterator from_position) noexcept;
        iterator erase(const_iterator from_range_first,
                       const_iterator from_range_last) noexcept;

        void swap(intrusive_list &rhs) noexcept;
        using impl_type::clear;

        // list operations:
        iterator find(value_type const &value) noexcept;
        const_iterator find(value_type const &value) const noexcept;

        void splice(const_iterator at,
                    intrusive_list &from_list) noexcept;
        void splice(const_iterator at,
                    intrusive_list &&from_list) noexcept;
        void splice(const_iterator at,
                    intrusive_list &from_list,
                    const_iterator from_position) noexcept;
        void splice(const_iterator at,
                    intrusive_list &&from_list,
                    const_iterator from_position) noexcept;
        void splice(const_iterator at,
                    intrusive_list &from_list,
                    const_iterator from_range_first,
                    const_iterator from_range_last) noexcept;
        void splice(const_iterator at,
                    intrusive_list &&from_list,
                    const_iterator from_range_first,
                    const_iterator from_range_last) noexcept;

        void remove(value_type const &value) noexcept;
        template <typename Predicate>
        void remove_if(Predicate pred) noexcept;

        void unique();
        template <typename BinaryPredicate>
        void unique(BinaryPredicate binary_pred);

        void merge(intrusive_list &&from_list) noexcept;
        template <typename Compare>
        void merge(intrusive_list &&from_list, Compare comp) noexcept;

        void sort() noexcept;
        template <typename Compare>
        void sort(Compare comp) noexcept;

        using impl_type::reverse;

    private:
        intrusive_list(intrusive_list const &rhs) = delete;
        intrusive_list& operator = (intrusive_list const &rhs) = delete;
    };

    // ----------------------------------------------------------------------------------------------------------------

    void swap(intrusive_list_impl &lhs,
              intrusive_list_impl &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (intrusive_list_impl const &lhs,
                      intrusive_list_impl const &rhs) noexcept;

    bool operator != (intrusive_list_impl const &lhs,
                      intrusive_list_impl const &rhs) noexcept;

    bool operator < (intrusive_list_impl const &lhs,
                     intrusive_list_impl const &rhs) noexcept;

    bool operator <= (intrusive_list_impl const &lhs,
                      intrusive_list_impl const &rhs) noexcept;

    bool operator > (intrusive_list_impl const &lhs,
                     intrusive_list_impl const &rhs) noexcept;

    bool operator >= (intrusive_list_impl const &lhs,
                      intrusive_list_impl const &rhs) noexcept;

    std::size_t hash(intrusive_list_impl const &l) noexcept;

    // ================================================================================================================

    class intrusive_list_impl::iterator
        : public std::iterator<std::bidirectional_iterator_tag,
                               intrusive_list_node>
    {
    public:
        iterator() noexcept = default;
        iterator(iterator &&rhs) noexcept;
        iterator(iterator const &rhs) noexcept = default;
        iterator& operator = (iterator &&rhs) noexcept;
        iterator& operator = (iterator const &rhs) noexcept = default;
        ~iterator() noexcept = default;

        iterator& operator ++ ();
        iterator operator ++ (int);

        iterator& operator -- ();
        iterator operator -- (int);

        value_type& operator * () const;
        value_type* operator -> () const;

    private:
        // members:
        intrusive_list_node *m_NodePtr = nullptr;
    };

    // ----------------------------------------------------------------------------------------------------------------

    void swap(intrusive_list_impl::iterator &lhs,
              intrusive_list_impl::iterator &rhs) noexcept;

    bool operator == (intrusive_list_impl::iterator const &lhs,
                      intrusive_list_impl::iterator const &rhs) noexcept;

    bool operator != (intrusive_list_impl::iterator const &lhs,
                      intrusive_list_impl::iterator const &rhs) noexcept;

    // ================================================================================================================

    class intrusive_list_impl::const_iterator
        : public std::iterator<std::bidirectional_iterator_tag,
                               intrusive_list_node const>
    {
    public:
        const_iterator() noexcept = default;
        const_iterator(const_iterator &&rhs) noexcept;
        const_iterator(const_iterator const &rhs) noexcept = default;
        const_iterator& operator = (const_iterator &&rhs) noexcept;
        const_iterator& operator = (const_iterator const &rhs) noexcept = default;
        ~const_iterator() noexcept = default;

        const_iterator& operator ++ ();
        const_iterator operator ++ (int);

        const_iterator& operator -- ();
        const_iterator operator -- (int);

        value_type const& operator * () const;
        value_type const* operator -> () const;

    private:
        // members:
        intrusive_list_node const *m_NodePtr = nullptr;
    };

    // ----------------------------------------------------------------------------------------------------------------

    void swap(intrusive_list_impl::const_iterator &lhs,
              intrusive_list_impl::const_iterator &rhs) noexcept;

    bool operator == (intrusive_list_impl::const_iterator const &lhs,
                      intrusive_list_impl::const_iterator const &rhs) noexcept;

    bool operator != (intrusive_list_impl::const_iterator const &lhs,
                      intrusive_list_impl::const_iterator const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    template <>
    struct hash<m1::intrusive_list_impl>
    {
       typedef m1::intrusive_list_impl argument_type;
       typedef std::size_t result_type;

       result_type operator () (argument_type const &arg) const;
    };

    // ================================================================================================================

    void swap(m1::intrusive_list_impl &lhs,
              m1::intrusive_list_impl &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================

namespace m1
{
    namespace impl
    {
        // ============================================================================================================

        template <typename T>
        struct is_iterator_test
        {
            typedef char (&no_type)[1];
            typedef char (&yes_type)[2];

            constexpr static no_type test(...);

            template <typename U,
                      typename = typename std::iterator_traits<U>::iterator_category,
                      typename = typename std::iterator_traits<U>::value_type,
                      typename = typename std::iterator_traits<U>::pointer,
                      typename = typename std::iterator_traits<U>::reference,
                      typename = typename std::iterator_traits<U>::distance_type>
            constexpr static yes_type test(T*);

            constexpr static bool const value = sizeof(test(std::declval<T>())) == sizeof(yes_type);
        };

        // ============================================================================================================
    } // namespace impl

    // ================================================================================================================

    template <typename T>
    struct is_iterator
        : std::integral_constant<bool, is_iterator_test<T>::value>
    {};

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

template <typename InputIterator,
          typename = std::enable_if_t<is_iterator<InputIterator>::value>>
m1::intrusive_list_impl::iterator m1::intrusive_list_impl::insert(InputIterator const range_first,
                                                                  InputIterator const range_last) noexcept
{
    for(InputIterator range_itr = range_first; range_itr != range_last; ++range_itr)
    {
        insert(*range_itr);
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Predicate>
void m1::intrusive_list_impl::remove_if(Predicate pred) noexcept
{
    const_iterator const end_itr = cend();
    for(const_iterator curr_itr = cbegin(); curr_itr != end_itr; /*increment in loop*/)
    {
        if(pred(*curr_itr))
        {
            curr_itr = erase(curr_itr);
        }
        else
        {
            ++curr_itr;
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------
#include <list>
template <typename BinaryPredicate>
void m1::intrusive_list_impl::unique(BinaryPredicate binary_pred)
{
    if(empty())
    {
        return;
    }

    const_iterator const end_itr = cend();
    const_iterator prev_itr = cbegin();
    const_iterator curr_itr = std::next(prev_itr);

    while(curr_itr != end_itr)
    {
        if(binary_pred(*prev_itr, *curr_itr))
        {
            curr_itr = erase(curr_itr);
        }
        else
        {
            ++prev_itr;
            ++curr_itr;
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename Compare>
void m1::intrusive_list_impl::merge(intrusive_list_impl &&from_list, Compare comp) noexcept
{
    if(this == &from_list)
    {
        return;
    }

    const_iterator into_list_curr_itr = cbegin();
    const_iterator const into_list_end_itr = cend();

    const_iterator from_list_curr_itr = from_list.begin();
    const_iterator const from_list_end_itr = from_list.cend();

    while((into_list_curr_itr != into_list_end_itr) &&
          (from_list_curr_itr != from_list_end_itr))
    {
        // if from_list's node is "less" than into_list's node
        if(comp(*from_list_curr_itr, *into_list_curr_itr))
        {
            // splice from_list's node in front of into_list's node
            const_iterator const from_list_next_itr = std::next(from_list_curr_itr);
            splice(into_list_curr_itr,
                   from_list,
                   from_list_curr_itr,
                   from_list_next_itr);
            from_list_curr_itr = from_list_next_itr;
        }
        else
        {
            ++into_list_curr_itr;
        }
    }

    if(from_list_curr_itr != from_list_end_itr)
    {
        // splice remainder of from_list to end of into_list
        splice(into_list_end_itr,
               from_list,
               from_list_curr_itr,
               from_list_end_itr);
    }
}

// --------------------------------------------------------------------------------------------------------------------

//template <typename Compare>
//void m1::intrusive_list_impl::sort(Compare comp) noexcept;

// ====================================================================================================================

#endif // M1_INTRUSIVE_LIST_HPP
