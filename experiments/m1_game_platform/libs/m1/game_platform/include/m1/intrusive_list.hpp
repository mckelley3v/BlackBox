#ifndef M1_INTRUSIVE_LIST_HPP
#define M1_INTRUSIVE_LIST_HPP

#include "m1/intrusive_list_impl.hpp"
#include <iterator>
#include <type_traits>

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

    template <typename T>
    std::size_t hash(intrusive_list<T> const &l) noexcept;

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

    template <typename T,
              typename ValueType>
    struct is_forward_iterator
        : std::bool_constant<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<T>::iterator_category>::value &&
                             std::is_base_of<ValueType, typename std::iterator_traits<T>::value_type>::value>
    {};

    template <typename T,
              typename ValueType>
    using enable_if_forward_iterator = std::enable_if_t<is_forward_iterator<T, ValueType>::value>;

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
        template <typename InputIterator,
                  typename = enable_if_forward_iterator<InputIterator, value_type>>
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

        iterator insert(const_iterator at,
                        value_type &node) noexcept;
        void insert(const_iterator at,
                    std::initializer_list<value_type&> const &nodes) noexcept;
        template <typename InputIterator,
                  typename = enable_if_forward_iterator<InputIterator, value_type>>
        void insert(const_iterator at,
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

        friend std::size_t hash<T>(intrusive_list<T> const &l) noexcept;

    private:
        intrusive_list(intrusive_list const &rhs) = delete;
        intrusive_list& operator = (intrusive_list const &rhs) = delete;
    };

    // ================================================================================================================

    template <typename T>
    class intrusive_list_iterator
        : private intrusive_list_iterator_impl
        , public std::iterator<std::bidirectional_iterator_tag,
                               T>
    {
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

    private:
        friend class intrusive_list<T>;
        intrusive_list_iterator() noexcept = delete;
        explicit intrusive_list_iterator(intrusive_list_node *node_ptr);

        // members:
        intrusive_list_node *m_NodePtr = nullptr;
    };

    // ================================================================================================================

    template <typename T>
    class intrusive_list_const_iterator
        : private intrusive_list_const_iterator_impl
        , public std::iterator<std::bidirectional_iterator_tag,
                               T const>
    {
    public:
        intrusive_list_const_iterator(iterator &&rhs) noexcept;
        intrusive_list_const_iterator(intrusive_list_const_iterator &&rhs) noexcept = default;
        intrusive_list_const_iterator(iterator const &rhs) noexcept;
        intrusive_list_const_iterator(intrusive_list_const_iterator const &rhs) noexcept = default;
        intrusive_list_const_iterator& operator = (iterator &&rhs) noexcept;
        intrusive_list_const_iterator& operator = (intrusive_list_const_iterator &&rhs) noexcept = default;
        intrusive_list_const_iterator& operator = (iterator const &rhs) noexcept;
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

    private:
        friend class intrusive_list<T>;
        intrusive_list_const_iterator() noexcept = delete;
        explicit intrusive_list_const_iterator(intrusive_list_node const *node_ptr);

        // members:
        intrusive_list_node const *m_NodePtr = nullptr;
    };

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    template <typename T>
    struct hash<m1::intrusive_list<T>>
    {
       typedef m1::intrusive_list<T> argument_type;
       typedef std::size_t result_type;

       result_type operator () (argument_type const &arg) const;
    };

    // ================================================================================================================

    template <typename T>
    void swap(m1::intrusive_list<T> &lhs,
              m1::intrusive_list<T> &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================
// ====================================================================================================================

template <typename T>
template <typename InputIterator,
          typename /*= enable_if_forward_iterator<InputIterator, value_type>*/>
m1::intrusive_list<T>::intrusive_list(InputIterator range_first,
                                      InputIterator range_last) noexcept
{
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
    return cosnt_reverse_iterator(begin());
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
    return *begin_node_ptr();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type const& m1::intrusive_list<T>::front() const noexcept
{
    return *get_begin_node_ptr();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type& m1::intrusive_list<T>::back() noexcept
{
    return *end_node_ptr()->prev_node_ptr();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::value_type const& m1::intrusive_list<T>::back() const noexcept
{
    return *get_end_node_ptr()->get_prev_node_ptr();
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::push_front(value_type &node) noexcept
{
    node.add_link(*begin_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::push_back(value_type &node) noexcept
{
    node.add_link(*end_node_ptr());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
typename m1::intrusive_list<T>::iterator m1::intrusive_list<T>::insert(const_iterator at,
                                                                       value_type &node) noexcept;

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
void m1::intrusive_list<T>::insert(const_iterator at,
                                                                       std::initializer_list<value_type&> const &nodes) noexcept
{
    insert(at, nodes.begin(), nodes.end());
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
template <typename InputIterator,
          typename /*= enable_if_forward_iterator<InputIterator, value_type>*/>
void m1::intrusive_list<T>::insert(const_iterator at,
                                                                       InputIterator const range_first,
                                                                       InputIterator const range_last) noexcept
{
    for(InputIterator range_itr = range_first; range_itr != range_last; ++range_itr)
    {
        insert(at, *range_itr);
    }
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
template <typename BinaryPredicate>
void m1::intrusive_list<T>::unique(BinaryPredicate binary_pred)
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

template <typename T>
template <typename Compare>
void m1::intrusive_list<T>::merge(intrusive_list<T> &&from_list,
                                  Compare comp) noexcept
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

//template <typename T>
//template <typename Compare>
//void m1::intrusive_list_impl::sort(Compare comp) noexcept;

// ====================================================================================================================

template <typename T>
bool m1::operator == (intrusive_list_iterator<T> const &lhs,
                      intrusive_list_iterator<T> const &rhs) noexcept
{
    return lhs.m_NodePtr == rhs.m_NodePtr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator != (intrusive_list_iterator<T> const &lhs,
                      intrusive_list_iterator<T> const &rhs) noexcept
{
    return lhs.m_NodePtr != rhs.m_NodePtr;
}

// ====================================================================================================================

template <typename T>
bool m1::operator == (intrusive_list_const_iterator<T> const &lhs,
                      intrusive_list_const_iterator<T> const &rhs) noexcept
{
    return lhs.m_NodePtr == rhs.m_NodePtr;
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
bool m1::operator != (intrusive_list_const_iterator<T> const &lhs,
                      intrusive_list_const_iterator<T> const &rhs) noexcept
{
    return lhs.m_NodePtr != rhs.m_NodePtr;
}

// ================================================================================================================

#endif // M1_INTRUSIVE_LIST_HPP
