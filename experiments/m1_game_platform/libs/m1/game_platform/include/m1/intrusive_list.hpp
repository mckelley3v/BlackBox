#ifndef M1_INTRUSIVE_LIST_HPP
#define M1_INTRUSIVE_LIST_HPP

#include "m1/intrusive_list_impl.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <type_traits>
#include <cassert>

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T> class intrusive_list;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void swap(intrusive_list<T> &lhs,
              intrusive_list<T> &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    bool operator == (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept;

    template <typename T>
    bool operator != (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept;

    template <typename T>
    bool operator < (intrusive_list<T> const &lhs,
                     intrusive_list<T> const &rhs) noexcept;

    template <typename T>
    bool operator <= (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept;

    template <typename T>
    bool operator > (intrusive_list<T> const &lhs,
                     intrusive_list<T> const &rhs) noexcept;

    template <typename T>
    bool operator >= (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept;

    // ================================================================================================================

    template <typename T> class intrusive_list_iterator;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void swap(intrusive_list_iterator<T> &lhs,
              intrusive_list_iterator<T> &rhs) noexcept;

    template <typename T>
    bool operator == (intrusive_list_iterator<T> const &lhs,
                      intrusive_list_iterator<T> const &rhs) noexcept;

    template <typename T>
    bool operator != (intrusive_list_iterator<T> const &lhs,
                      intrusive_list_iterator<T> const &rhs) noexcept;

    // ================================================================================================================

    template <typename T> class intrusive_list_const_iterator;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void swap(intrusive_list_const_iterator<T> &lhs,
              intrusive_list_const_iterator<T> &rhs) noexcept;

    template <typename T>
    bool operator == (intrusive_list_const_iterator<T> const &lhs,
                      intrusive_list_const_iterator<T> const &rhs) noexcept;

    template <typename T>
    bool operator != (intrusive_list_const_iterator<T> const &lhs,
                      intrusive_list_const_iterator<T> const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace m1
{
    // ================================================================================================================

    template <typename T>
    class intrusive_list
        : private intrusive_list_impl
    {
    private:
        static_assert(std::is_base_of<intrusive_list_node, T>::value, "T must inherit from m1::intrusive_list_node");
        typedef intrusive_list_impl impl_type;

    public:
        // types:
        typedef T value_type;
        using impl_type::size_type;
        using impl_type::difference_type;

        typedef intrusive_list_iterator<value_type> iterator;
        typedef intrusive_list_const_iterator<value_type> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // construct/move/copy/destroy:
        intrusive_list() noexcept = default;
        template <typename InputIterator>
        intrusive_list(InputIterator range_first,
                       InputIterator range_last) noexcept;
        intrusive_list(intrusive_list &&rhs) noexcept = default;
        intrusive_list& operator = (intrusive_list &&rhs) noexcept = default;
        ~intrusive_list() noexcept = default;

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

        iterator insert(iterator at,
                        value_type &node) noexcept;
        template <typename InputIterator>
        void insert(iterator at,
                    InputIterator range_first,
                    InputIterator range_last) noexcept;

        iterator erase(iterator from_position) noexcept;
        iterator erase(iterator from_range_first,
                       iterator from_range_last) noexcept;

        void swap(intrusive_list &rhs) noexcept;
        using impl_type::clear;

        // list operations:
        iterator find(value_type &value) noexcept;
        const_iterator find(value_type const &value) const noexcept;

        void splice(iterator at,
                    intrusive_list &from_list) noexcept;
        void splice(iterator at,
                    intrusive_list &&from_list) noexcept;
        void splice(iterator at,
                    intrusive_list &from_list,
                    iterator from_position) noexcept;
        void splice(iterator at,
                    intrusive_list &&from_list,
                    iterator from_position) noexcept;
        void splice(iterator at,
                    intrusive_list &from_list,
                    iterator from_range_first,
                    iterator from_range_last) noexcept;
        void splice(iterator at,
                    intrusive_list &&from_list,
                    iterator from_range_first,
                    iterator from_range_last) noexcept;

        void remove(value_type &value) noexcept;
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

        friend bool operator == <T>(intrusive_list<T> const &lhs,
                                    intrusive_list<T> const &rhs) noexcept;

        friend bool operator != <T>(intrusive_list<T> const &lhs,
                                    intrusive_list<T> const &rhs) noexcept;

        friend bool operator < <T>(intrusive_list<T> const &lhs,
                                   intrusive_list<T> const &rhs) noexcept;

        friend bool operator <= <T>(intrusive_list<T> const &lhs,
                                    intrusive_list<T> const &rhs) noexcept;

        friend bool operator > <T>(intrusive_list<T> const &lhs,
                                   intrusive_list<T> const &rhs) noexcept;

        friend bool operator >= <T>(intrusive_list<T> const &lhs,
                                    intrusive_list<T> const &rhs) noexcept;

    private:
        intrusive_list(intrusive_list const &rhs) = delete;
        intrusive_list& operator = (intrusive_list const &rhs) = delete;

        template <typename Compare>
        iterator sort_impl(iterator first,
                           iterator last,
                           Compare &comp,
                           size_type size) noexcept;

        impl_type& impl();
        impl_type const& get_impl() const;
    };

    // ================================================================================================================

    template <typename T>
    class intrusive_list_iterator
        : private intrusive_list_iterator_impl
        , public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        static_assert(std::is_base_of<intrusive_list_node, T>::value, "T must inherit from m1::intrusive_list_node");
        typedef intrusive_list_iterator_impl impl_type;

    public:
        intrusive_list_iterator(intrusive_list_iterator &&rhs) noexcept = default;
        intrusive_list_iterator(intrusive_list_iterator const &rhs) noexcept = default;
        intrusive_list_iterator& operator = (intrusive_list_iterator &&rhs) noexcept = default;
        intrusive_list_iterator& operator = (intrusive_list_iterator const &rhs) noexcept = default;
        ~intrusive_list_iterator() noexcept = default;

        intrusive_list_iterator& operator ++ ();
        intrusive_list_iterator operator ++ (int);

        intrusive_list_iterator& operator -- ();
        intrusive_list_iterator operator -- (int);

        value_type& operator * () const;
        value_type* operator -> () const;

        friend void swap<T>(intrusive_list_iterator<T> &lhs,
                            intrusive_list_iterator<T> &rhs) noexcept;

        friend bool operator == <T>(intrusive_list_iterator<T> const &lhs,
                                    intrusive_list_iterator<T> const &rhs) noexcept;

        friend bool operator != <T>(intrusive_list_iterator<T> const &lhs,
                                    intrusive_list_iterator<T> const &rhs) noexcept;

    protected:
        impl_type& impl();
        impl_type const& get_impl() const;

    private:
        friend class intrusive_list<T>;
        friend class intrusive_list_const_iterator<T>;
        intrusive_list_iterator() noexcept = delete;
        explicit intrusive_list_iterator(intrusive_list_node *node_ptr);
    };

    // ================================================================================================================

    template <typename T>
    class intrusive_list_const_iterator
        : private intrusive_list_const_iterator_impl
        , public std::iterator<std::bidirectional_iterator_tag,
                               T const>
    {
    private:
        static_assert(std::is_base_of<intrusive_list_node, T>::value, "T must inherit from m1::intrusive_list_node");
        typedef intrusive_list_const_iterator_impl impl_type;

    public:
        intrusive_list_const_iterator(intrusive_list_iterator<T> &&rhs) noexcept;
        intrusive_list_const_iterator(intrusive_list_const_iterator &&rhs) noexcept = default;
        intrusive_list_const_iterator(intrusive_list_iterator<T> const &rhs) noexcept;
        intrusive_list_const_iterator(intrusive_list_const_iterator const &rhs) noexcept = default;
        intrusive_list_const_iterator& operator = (intrusive_list_iterator<T> &&rhs) noexcept;
        intrusive_list_const_iterator& operator = (intrusive_list_const_iterator &&rhs) noexcept = default;
        intrusive_list_const_iterator& operator = (intrusive_list_iterator<T> const &rhs) noexcept;
        intrusive_list_const_iterator& operator = (intrusive_list_const_iterator const &rhs) noexcept = default;
        ~intrusive_list_const_iterator() noexcept = default;

        intrusive_list_const_iterator& operator ++ ();
        intrusive_list_const_iterator operator ++ (int);

        intrusive_list_const_iterator& operator -- ();
        intrusive_list_const_iterator operator -- (int);

        value_type const& operator * () const;
        value_type const* operator -> () const;

        friend void swap<T>(intrusive_list_const_iterator<T> &lhs,
                            intrusive_list_const_iterator<T> &rhs) noexcept;

        friend bool operator == <T>(intrusive_list_const_iterator<T> const &lhs,
                                    intrusive_list_const_iterator<T> const &rhs) noexcept;

        friend bool operator != <T>(intrusive_list_const_iterator<T> const &lhs,
                                    intrusive_list_const_iterator<T> const &rhs) noexcept;

    protected:
        impl_type& impl();
        impl_type const& get_impl() const;

    private:
        friend class intrusive_list<T>;
        intrusive_list_const_iterator() noexcept = delete;
        explicit intrusive_list_const_iterator(intrusive_list_node const *node_ptr);
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    template <typename T>
    void swap(m1::intrusive_list<T> &lhs,
              m1::intrusive_list<T> &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    template <typename T,
              typename ValueType>
    struct is_input_iterator
        : std::bool_constant<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<T>::iterator_category>::value &&
                             std::is_convertible<typename std::iterator_traits<T>::value_type, ValueType>::value>
    {};

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================
// intrusive_list
// ====================================================================================================================

template <typename T>
template <typename InputIterator>
m1::intrusive_list<T>::intrusive_list(InputIterator range_first,
                                      InputIterator range_last) noexcept
{
    static_assert(impl::is_input_iterator<InputIterator, value_type>::value, "Invalid InputIterator");

    while (range_first != range_last)
    {
        insert(*range_first);
        ++range_first;
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::begin() noexcept
{
    return iterator(begin_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_iterator m1::intrusive_list<T>::begin() const noexcept
{
    return const_iterator(get_begin_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::end() noexcept
{
    return iterator(end_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_iterator m1::intrusive_list<T>::end() const noexcept
{
    return const_iterator(get_end_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::reverse_iterator m1::intrusive_list<T>::rbegin() noexcept
{
    return reverse_iterator(begin());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_reverse_iterator m1::intrusive_list<T>::rbegin() const noexcept
{
    return const_reverse_iterator(begin());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::reverse_iterator m1::intrusive_list<T>::rend() noexcept
{
    return reverse_iterator(end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_reverse_iterator m1::intrusive_list<T>::rend() const noexcept
{
    return const_reverse_iterator(end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_iterator m1::intrusive_list<T>::cbegin() const noexcept
{
    return const_iterator(get_begin_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_iterator m1::intrusive_list<T>::cend() const noexcept
{
    return const_iterator(get_end_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_reverse_iterator m1::intrusive_list<T>::crbegin() const noexcept
{
    return const_reverse_iterator(cbegin());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_reverse_iterator m1::intrusive_list<T>::crend() const noexcept
{
    return const_reverse_iterator(cend());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type& m1::intrusive_list<T>::front() noexcept
{
    return *static_cast<value_type*>(begin_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type const& m1::intrusive_list<T>::front() const noexcept
{
    return *static_cast<value_type const*>(get_begin_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type& m1::intrusive_list<T>::back() noexcept
{
    return *static_cast<value_type*>(end_node_ptr()->prev_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type const& m1::intrusive_list<T>::back() const noexcept
{
    return *static_cast<value_type const*>(get_end_node_ptr()->get_prev_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::push_front(value_type &node) noexcept
{
    impl_type::push_front(node);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::push_back(value_type &node) noexcept
{
    impl_type::push_back(node);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::insert(iterator at,
                                                                       value_type &node) noexcept
{
    impl_type::insert(*at, node);
    return iterator(&node);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename InputIterator>
void m1::intrusive_list<T>::insert(iterator at,
                                   InputIterator const range_first,
                                   InputIterator const range_last) noexcept
{
    static_assert(impl::is_input_iterator<InputIterator, value_type>::value, "Invalid InputIterator");

    for(InputIterator range_itr = range_first; range_itr != range_last; ++range_itr)
    {
        impl_type::insert(*at, *range_itr);
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::erase(iterator from_position) noexcept
{
    iterator erase_position = from_position++;
    erase_position->clear_links();
    return from_position;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::erase(iterator from_range_first,
                                                                      iterator from_range_last) noexcept
{
    while(from_range_first != from_range_last)
    {
        from_range_first = erase(from_range_first);
    }

    return from_range_last;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::swap(intrusive_list &rhs) noexcept
{
    impl().swap(rhs.impl());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::find(value_type &value) noexcept
{
#ifndef NDEBUG
    // linear search if not NDEBUG
    return std::find(begin(), end(), value);
#else
    return iterator(&value);
#endif
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::const_iterator m1::intrusive_list<T>::find(value_type const &value) const noexcept
{
#ifndef NDEBUG
    // linear search if not NDEBUG
    return std::find(cbegin(), cend(), value);
#else
    return const_iterator(&value);
#endif
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::splice(iterator at,
                                   intrusive_list &from_list) noexcept
{
    splice(at,
           from_list,
           from_list.begin(),
           from_list.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::splice(iterator at,
                                   intrusive_list &&from_list) noexcept
{
    splice(at,
           from_list,
           from_list.begin(),
           from_list.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::splice(iterator at,
                                   intrusive_list &from_list,
                                   iterator from_position) noexcept
{
    splice(at,
           from_list,
           from_position,
           std::next(from_position));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::splice(iterator at,
                                   intrusive_list &&from_list,
                                   iterator from_position) noexcept
{
    splice(at,
           from_list,
           from_position,
           std::next(from_position));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::splice(iterator at,
                                   intrusive_list &from_list,
                                   iterator from_range_first,
                                   iterator from_range_last) noexcept
{
    assert(this != &from_list);
    assert(from_range_first.node_ptr() != nullptr);
    assert(from_range_last.node_ptr() != nullptr);

    at.node_ptr()->splice_link_range(*from_range_first.node_ptr(),
                                     *from_range_last.node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::splice(iterator at,
                                   intrusive_list &&from_list,
                                   iterator from_range_first,
                                   iterator from_range_last) noexcept
{
    splice(at,
           from_list,
           from_range_first,
           from_range_last);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::remove(value_type &value) noexcept
{
    assert(!value.is_linked() || (find(value) != end())); // linear search if not NDEBUG
    value.clear_links();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename Predicate>
void m1::intrusive_list<T>::remove_if(Predicate pred) noexcept
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

template <typename T>
void m1::intrusive_list<T>::unique()
{
    unique(std::equal_to<T>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename BinaryPredicate>
void m1::intrusive_list<T>::unique(BinaryPredicate binary_pred)
{
    if(empty())
    {
        return;
    }

    iterator const end_itr = end();
    iterator prev_itr = begin();
    iterator curr_itr = std::next(prev_itr);

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

template <typename T>
void m1::intrusive_list<T>::merge(intrusive_list<T> &&from_list) noexcept
{
    merge(std::move(from_list),
          std::less<T>());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename Compare>
void m1::intrusive_list<T>::merge(intrusive_list<T> &&from_list,
                                  Compare comp) noexcept
{
    if(this == &from_list)
    {
        return;
    }

    iterator into_list_curr_itr = begin();
    iterator const into_list_end_itr = end();

    iterator from_list_curr_itr = from_list.begin();
    iterator const from_list_end_itr = from_list.end();

    while((into_list_curr_itr != into_list_end_itr) &&
          (from_list_curr_itr != from_list_end_itr))
    {
        // if from_list's node is "less" than into_list's node
        if(comp(*from_list_curr_itr, *into_list_curr_itr))
        {
            // splice from_list's node in front of into_list's node
            iterator const from_list_next_itr = std::next(from_list_curr_itr);
            splice(into_list_curr_itr,
                   from_list, // ref
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
               from_list, // ref
               from_list_curr_itr,
               from_list_end_itr);
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::sort() noexcept
{
    std::less<T> comp;
    sort_impl(begin(),
              end(),
              comp,
              std::distance(begin(), end()));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename Compare>
void m1::intrusive_list<T>::sort(Compare comp) noexcept
{
    sort_impl(begin(),
              end(),
              comp,
              std::distance(begin(), end()));
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename Compare>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::sort_impl(iterator first,
                                                                          iterator last,
                                                                          Compare &comp,
                                                                          size_type size) noexcept
{
    if(size < 2)
    {
        return first;
    }

    iterator mid = std::next(first, size / 2);
    first = sort_impl(first, mid, comp, size / 2);
    mid = sort_impl(mid, last, comp, size - size / 2);

    iterator result = first;
    for (bool init = true; ; init = false)
    {
        if(comp(*mid, *first))
        {
            if(init)
            {
                result = mid;
            }

            splice(first, *this, mid++);

            if(mid == last)
            {
                return result;
            }
        }
        else
        {
            ++first;
            if(first == mid)
            {
                return result;
            }
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::impl_type& m1::intrusive_list<T>::impl()
{
    return static_cast<impl_type&>(*this);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::impl_type const& m1::intrusive_list<T>::get_impl() const
{
    return static_cast<impl_type const&>(*this);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::swap(intrusive_list<T> &lhs,
              intrusive_list<T> &rhs) noexcept
{
    lhs.swap(rhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator == (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept
{
    return std::equal(lhs.begin(), lhs.end(),
                      rhs.begin(), rhs.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator != (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept
{
    return !(lhs == rhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator < (intrusive_list<T> const &lhs,
                     intrusive_list<T> const &rhs) noexcept
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator <= (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept
{
    return !(rhs < lhs);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator > (intrusive_list<T> const &lhs,
                     intrusive_list<T> const &rhs) noexcept
{
    return rhs < lhs;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator >= (intrusive_list<T> const &lhs,
                      intrusive_list<T> const &rhs) noexcept
{
    return !(lhs < rhs);
}

// ====================================================================================================================
// intrusive_list_iterator
// ====================================================================================================================

template <typename T>
/*explicit*/ m1::intrusive_list_iterator<T>::intrusive_list_iterator(intrusive_list_node *node_ptr)
    : intrusive_list_iterator_impl(node_ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_iterator<T>& m1::intrusive_list_iterator<T>::operator ++ ()
{
    intrusive_list_iterator_impl::operator ++ ();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_iterator<T> m1::intrusive_list_iterator<T>::operator ++ (int)
{
    intrusive_list_iterator result(*this);
    intrusive_list_iterator_impl::operator ++ ();
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_iterator<T>& m1::intrusive_list_iterator<T>::operator -- ()
{
    intrusive_list_iterator_impl::operator -- ();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_iterator<T> m1::intrusive_list_iterator<T>::operator -- (int)
{
    intrusive_list_iterator result(*this);
    intrusive_list_iterator_impl::operator -- ();
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_iterator<T>::value_type& m1::intrusive_list_iterator<T>::operator * () const
{
    return *static_cast<value_type*>(node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_iterator<T>::value_type* m1::intrusive_list_iterator<T>::operator -> () const
{
    return static_cast<value_type*>(node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_iterator<T>::impl_type& m1::intrusive_list_iterator<T>::impl()
{
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_iterator<T>::impl_type const& m1::intrusive_list_iterator<T>::get_impl() const
{
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::swap(intrusive_list_iterator<T> &lhs,
              intrusive_list_iterator<T> &rhs) noexcept
{
    swap(lhs.impl(),  // ref
         rhs.impl()); // ref
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator == (intrusive_list_iterator<T> const &lhs,
                      intrusive_list_iterator<T> const &rhs) noexcept
{
    return lhs.get_impl() == rhs.get_impl();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator != (intrusive_list_iterator<T> const &lhs,
                      intrusive_list_iterator<T> const &rhs) noexcept
{
    return lhs.get_impl() != rhs.get_impl();
}

// ====================================================================================================================
// intrusive_list_const_iterator
// ====================================================================================================================

template <typename T>
/*explicit*/ m1::intrusive_list_const_iterator<T>::intrusive_list_const_iterator(intrusive_list_node const *node_ptr)
    : intrusive_list_const_iterator_impl(node_ptr)
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T>::intrusive_list_const_iterator(intrusive_list_iterator<T> &&rhs) noexcept
    : intrusive_list_const_iterator_impl(std::move(rhs.impl()))
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T>::intrusive_list_const_iterator(intrusive_list_iterator<T> const &rhs) noexcept
    : intrusive_list_const_iterator_impl(rhs.get_impl())
{
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T>& m1::intrusive_list_const_iterator<T>::operator = (intrusive_list_iterator<T> &&rhs) noexcept
{
    intrusive_list_const_iterator_impl::operator = (std::move(rhs.impl()));
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T>& m1::intrusive_list_const_iterator<T>::operator = (intrusive_list_iterator<T> const &rhs) noexcept
{
    intrusive_list_const_iterator_impl::operator = (rhs.get_impl());
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T>& m1::intrusive_list_const_iterator<T>::operator ++ ()
{
    intrusive_list_const_iterator_impl::operator ++ ();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T> m1::intrusive_list_const_iterator<T>::operator ++ (int)
{
    intrusive_list_const_iterator result(*this);
    intrusive_list_const_iterator_impl::operator ++ ();
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T>& m1::intrusive_list_const_iterator<T>::operator -- ()
{
    intrusive_list_const_iterator_impl::operator -- ();
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
m1::intrusive_list_const_iterator<T> m1::intrusive_list_const_iterator<T>::operator -- (int)
{
    intrusive_list_const_iterator result(*this);
    intrusive_list_const_iterator_impl::operator -- ();
    return result;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_const_iterator<T>::value_type const& m1::intrusive_list_const_iterator<T>::operator * () const
{
    return *static_cast<value_type const*>(get_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_const_iterator<T>::value_type const* m1::intrusive_list_const_iterator<T>::operator -> () const
{
    return static_cast<value_type const*>(get_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_const_iterator<T>::impl_type& m1::intrusive_list_const_iterator<T>::impl()
{
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list_const_iterator<T>::impl_type const& m1::intrusive_list_const_iterator<T>::get_impl() const
{
    return *this;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::swap(intrusive_list_const_iterator<T> &lhs,
              intrusive_list_const_iterator<T> &rhs) noexcept
{
    swap(lhs.impl(),  // ref
         rhs.impl()); // ref
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator == (intrusive_list_const_iterator<T> const &lhs,
                      intrusive_list_const_iterator<T> const &rhs) noexcept
{
    return lhs.get_impl() == rhs.get_impl();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator != (intrusive_list_const_iterator<T> const &lhs,
                      intrusive_list_const_iterator<T> const &rhs) noexcept
{
    return lhs.get_impl() != rhs.get_impl();
}

// ====================================================================================================================

#endif // M1_INTRUSIVE_LIST_HPP
