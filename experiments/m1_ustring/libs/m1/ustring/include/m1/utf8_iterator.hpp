#ifndef M1_UTF8_ITERATOR_HPP
#define M1_UTF8_ITERATOR_HPP

#include <iterator>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    class utf8_iterator;
    class utf8_counted_iterator;
    class utf8_terminator_null;
    class utf8_terminator_length;

    // ================================================================================================================

    void consume_utf8_byte_order_mark(char const *&u8_str) noexcept;

    // ================================================================================================================

    class utf8_iterator
        : public std::iterator<std::bidirectional_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf8_iterator() noexcept;
        explicit utf8_iterator(char const *u8_str) noexcept;
        utf8_iterator(utf8_iterator &&rhs) noexcept;
        utf8_iterator(utf8_iterator const &rhs) noexcept;
        utf8_iterator& operator = (utf8_iterator &&rhs) noexcept;
        utf8_iterator& operator = (utf8_iterator const &rhs) noexcept;
        ~utf8_iterator() noexcept;

        code_point operator * () const;

        utf8_iterator& operator ++ ();
        utf8_iterator operator ++ (int);
        utf8_iterator& operator -- ();
        utf8_iterator operator -- (int);

        void swap(utf8_iterator &rhs) noexcept;

        friend bool operator == (utf8_iterator const &lhs,
                                 utf8_iterator const &rhs) noexcept;

        friend bool operator != (utf8_iterator const &lhs,
                                 utf8_iterator const &rhs) noexcept;

    private:
        // members:
        char const *m_CodeUnitPtr {nullptr};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf8_iterator const &lhs,
                      utf8_iterator const &rhs) noexcept;

    bool operator != (utf8_iterator const &lhs,
                      utf8_iterator const &rhs) noexcept;

    // ================================================================================================================

    class utf8_counted_iterator
        : public std::iterator<std::bidirectional_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf8_counted_iterator() noexcept;
        explicit utf8_counted_iterator(char const *u8_str) noexcept;
        utf8_counted_iterator(utf8_counted_iterator &&rhs) noexcept;
        utf8_counted_iterator(utf8_counted_iterator const &rhs) noexcept;
        utf8_counted_iterator& operator = (utf8_counted_iterator &&rhs) noexcept;
        utf8_counted_iterator& operator = (utf8_counted_iterator const &rhs) noexcept;
        ~utf8_counted_iterator() noexcept;

        code_point operator * () const;

        utf8_counted_iterator& operator ++ ();
        utf8_counted_iterator operator ++ (int);
        utf8_counted_iterator& operator -- ();
        utf8_counted_iterator operator -- (int);

        std::size_t count() const noexcept;

        void swap(utf8_counted_iterator &rhs) noexcept;

        friend bool operator == (utf8_counted_iterator const &lhs,
                                 utf8_counted_iterator const &rhs) noexcept;

        friend bool operator != (utf8_counted_iterator const &lhs,
                                 utf8_counted_iterator const &rhs) noexcept;

    private:
        // members:
        char const *m_CodeUnitPtr    {nullptr};
        std::size_t m_CodePointCount {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf8_counted_iterator const &lhs,
                      utf8_counted_iterator const &rhs) noexcept;

    bool operator != (utf8_counted_iterator const &lhs,
                      utf8_counted_iterator const &rhs) noexcept;

    // ================================================================================================================

    class utf8_terminator_null {};
    constexpr utf8_terminator_null const utf8_end{};

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf8_terminator_null const &lhs,
                      utf8_iterator const &rhs) noexcept;

    bool operator == (utf8_iterator const &lhs,
                      utf8_terminator_null const &rhs) noexcept;

    bool operator == (utf8_terminator_null const &lhs,
                      utf8_counted_iterator const &rhs) noexcept;

    bool operator == (utf8_counted_iterator const &lhs,
                      utf8_terminator_null const &rhs) noexcept;

    bool operator != (utf8_terminator_null const &lhs,
                      utf8_iterator const &rhs) noexcept;

    bool operator != (utf8_iterator const &lhs,
                      utf8_terminator_null const &rhs) noexcept;

    bool operator != (utf8_terminator_null const &lhs,
                      utf8_counted_iterator const &rhs) noexcept;

    bool operator != (utf8_counted_iterator const &lhs,
                      utf8_terminator_null const &rhs) noexcept;

    // ================================================================================================================

    class utf8_terminator_length
    {
    public:
        utf8_terminator_length() noexcept;
        explicit utf8_terminator_length(std::size_t length) noexcept;
        utf8_terminator_length(utf8_terminator_length &&rhs) noexcept;
        utf8_terminator_length(utf8_terminator_length const &rhs) noexcept;
        utf8_terminator_length& operator = (utf8_terminator_length &&rhs) noexcept;
        utf8_terminator_length& operator = (utf8_terminator_length const &rhs) noexcept;
        ~utf8_terminator_length() noexcept;

        std::size_t length() const noexcept;

    private:
        // members:
        std::size_t m_Length {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf8_terminator_length const &lhs,
                      utf8_counted_iterator const &rhs) noexcept;

    bool operator == (utf8_counted_iterator const &lhs,
                      utf8_terminator_length const &rhs) noexcept;

    bool operator != (utf8_terminator_length const &lhs,
                      utf8_counted_iterator const &rhs) noexcept;

    bool operator != (utf8_counted_iterator const &lhs,
                      utf8_terminator_length const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    void swap(m1::utf8_iterator &lhs,
              m1::utf8_iterator &rhs) noexcept;

    void swap(m1::utf8_counted_iterator &lhs,
              m1::utf8_counted_iterator &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================

#endif // M1_UTF8_ITERATOR_HPP
