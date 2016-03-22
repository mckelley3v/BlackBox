#ifndef M1_UTF16_ITERATOR_HPP
#define M1_UTF16_ITERATOR_HPP

#include "m1/byte_order.hpp"
#include <iterator>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    class utf16_iterator_big_endian;
    class utf16_iterator_little_endian;
    class utf16_counted_iterator_big_endian;
    class utf16_counted_iterator_little_endian;
    class utf16_terminator_null;
    class utf16_terminator_length;

    using utf16_iterator = std::conditional_t<native_byte_order() == byte_order::big_endian,
                                              utf16_iterator_big_endian,
                                              utf16_iterator_little_endian>;

    using utf16_counted_iterator = std::conditional_t<native_byte_order() == byte_order::big_endian,
                                                      utf16_counted_iterator_big_endian,
                                                      utf16_counted_iterator_little_endian>;

    // ================================================================================================================

    byte_order consume_utf16_byte_order_mark(char16_t const *&u16_str) noexcept;

    // ================================================================================================================

    class utf16_iterator_big_endian
        : public std::iterator<std::bidirectional_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf16_iterator_big_endian() noexcept;
        explicit utf16_iterator_big_endian(char16_t const *u16_str) noexcept;
        utf16_iterator_big_endian(utf16_iterator_big_endian &&rhs) noexcept;
        utf16_iterator_big_endian(utf16_iterator_big_endian const &rhs) noexcept;
        utf16_iterator_big_endian& operator = (utf16_iterator_big_endian &&rhs) noexcept;
        utf16_iterator_big_endian& operator = (utf16_iterator_big_endian const &rhs) noexcept;
        ~utf16_iterator_big_endian() noexcept;

        code_point operator * () const;

        utf16_iterator_big_endian& operator ++ ();
        utf16_iterator_big_endian operator ++ (int);
        utf16_iterator_big_endian& operator -- ();
        utf16_iterator_big_endian operator -- (int);

        void swap(utf16_iterator_big_endian &rhs) noexcept;

        friend bool operator == (utf16_iterator_big_endian const &lhs,
                                 utf16_iterator_big_endian const &rhs) noexcept;

        friend bool operator != (utf16_iterator_big_endian const &lhs,
                                 utf16_iterator_big_endian const &rhs) noexcept;

    private:
        // members:
        char16_t const *m_CodeUnitPtr {nullptr};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf16_iterator_big_endian const &lhs,
                      utf16_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf16_iterator_big_endian const &lhs,
                      utf16_iterator_big_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf16_iterator_little_endian
        : public std::iterator<std::bidirectional_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf16_iterator_little_endian() noexcept;
        explicit utf16_iterator_little_endian(char16_t const *u16_str) noexcept;
        utf16_iterator_little_endian(utf16_iterator_little_endian &&rhs) noexcept;
        utf16_iterator_little_endian(utf16_iterator_little_endian const &rhs) noexcept;
        utf16_iterator_little_endian& operator = (utf16_iterator_little_endian &&rhs) noexcept;
        utf16_iterator_little_endian& operator = (utf16_iterator_little_endian const &rhs) noexcept;
        ~utf16_iterator_little_endian() noexcept;

        code_point operator * () const;

        utf16_iterator_little_endian& operator ++ ();
        utf16_iterator_little_endian operator ++ (int);
        utf16_iterator_little_endian& operator -- ();
        utf16_iterator_little_endian operator -- (int);

        void swap(utf16_iterator_little_endian &rhs) noexcept;

        friend bool operator == (utf16_iterator_little_endian const &lhs,
                                 utf16_iterator_little_endian const &rhs) noexcept;

        friend bool operator != (utf16_iterator_little_endian const &lhs,
                                 utf16_iterator_little_endian const &rhs) noexcept;

    private:
        // members:
        char16_t const *m_CodeUnitPtr {nullptr};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf16_iterator_little_endian const &lhs,
                      utf16_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf16_iterator_little_endian const &lhs,
                      utf16_iterator_little_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf16_counted_iterator_big_endian
        : public std::iterator<std::bidirectional_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf16_counted_iterator_big_endian() noexcept;
        explicit utf16_counted_iterator_big_endian(char16_t const *u16_str) noexcept;
        utf16_counted_iterator_big_endian(utf16_counted_iterator_big_endian &&rhs) noexcept;
        utf16_counted_iterator_big_endian(utf16_counted_iterator_big_endian const &rhs) noexcept;
        utf16_counted_iterator_big_endian& operator = (utf16_counted_iterator_big_endian &&rhs) noexcept;
        utf16_counted_iterator_big_endian& operator = (utf16_counted_iterator_big_endian const &rhs) noexcept;
        ~utf16_counted_iterator_big_endian() noexcept;

        code_point operator * () const;

        utf16_counted_iterator_big_endian& operator ++ ();
        utf16_counted_iterator_big_endian operator ++ (int);
        utf16_counted_iterator_big_endian& operator -- ();
        utf16_counted_iterator_big_endian operator -- (int);

        std::size_t count() const noexcept;

        void swap(utf16_counted_iterator_big_endian &rhs) noexcept;

        friend bool operator == (utf16_counted_iterator_big_endian const &lhs,
                                 utf16_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator != (utf16_counted_iterator_big_endian const &lhs,
                                 utf16_counted_iterator_big_endian const &rhs) noexcept;

    private:
        // members:
        char16_t const *m_CodeUnitPtr {nullptr};
        std::size_t m_CodePointCount  {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf16_counted_iterator_big_endian const &lhs,
                      utf16_counted_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf16_counted_iterator_big_endian const &lhs,
                      utf16_counted_iterator_big_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf16_counted_iterator_little_endian
        : public std::iterator<std::bidirectional_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf16_counted_iterator_little_endian() noexcept;
        explicit utf16_counted_iterator_little_endian(char16_t const *u16_str) noexcept;
        utf16_counted_iterator_little_endian(utf16_counted_iterator_little_endian &&rhs) noexcept;
        utf16_counted_iterator_little_endian(utf16_counted_iterator_little_endian const &rhs) noexcept;
        utf16_counted_iterator_little_endian& operator = (utf16_counted_iterator_little_endian &&rhs) noexcept;
        utf16_counted_iterator_little_endian& operator = (utf16_counted_iterator_little_endian const &rhs) noexcept;
        ~utf16_counted_iterator_little_endian() noexcept;

        code_point operator * () const;

        utf16_counted_iterator_little_endian& operator ++ ();
        utf16_counted_iterator_little_endian operator ++ (int);
        utf16_counted_iterator_little_endian& operator -- ();
        utf16_counted_iterator_little_endian operator -- (int);

        std::size_t count() const noexcept;

        void swap(utf16_counted_iterator_little_endian &rhs) noexcept;

        friend bool operator == (utf16_counted_iterator_little_endian const &lhs,
                                 utf16_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator != (utf16_counted_iterator_little_endian const &lhs,
                                 utf16_counted_iterator_little_endian const &rhs) noexcept;

    private:
        // members:
        char16_t const *m_CodeUnitPtr {nullptr};
        std::size_t m_CodePointCount  {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf16_counted_iterator_little_endian const &lhs,
                      utf16_counted_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf16_counted_iterator_little_endian const &lhs,
                      utf16_counted_iterator_little_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf16_terminator_null {};
    constexpr utf16_terminator_null const utf16_end{};

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf16_terminator_null const &lhs,
                      utf16_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf16_iterator_big_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator == (utf16_terminator_null const &lhs,
                      utf16_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf16_iterator_little_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator == (utf16_terminator_null const &lhs,
                      utf16_counted_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf16_counted_iterator_big_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator == (utf16_terminator_null const &lhs,
                      utf16_counted_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf16_counted_iterator_little_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator != (utf16_terminator_null const &lhs,
                      utf16_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf16_iterator_big_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator != (utf16_terminator_null const &lhs,
                      utf16_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf16_iterator_little_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator != (utf16_terminator_null const &lhs,
                      utf16_counted_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf16_counted_iterator_big_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    bool operator != (utf16_terminator_null const &lhs,
                      utf16_counted_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf16_counted_iterator_little_endian const &lhs,
                      utf16_terminator_null const &rhs) noexcept;

    // ================================================================================================================

    class utf16_terminator_length
    {
    public:
        utf16_terminator_length() noexcept;
        explicit utf16_terminator_length(std::size_t length) noexcept;
        utf16_terminator_length(utf16_terminator_length &&rhs) noexcept;
        utf16_terminator_length(utf16_terminator_length const &rhs) noexcept;
        utf16_terminator_length& operator = (utf16_terminator_length &&rhs) noexcept;
        utf16_terminator_length& operator = (utf16_terminator_length const &rhs) noexcept;
        ~utf16_terminator_length() noexcept;

        std::size_t length() const noexcept;

    private:
        // members:
        std::size_t m_Length = 0;
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf16_terminator_length const &lhs,
                      utf16_counted_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf16_counted_iterator_big_endian const &lhs,
                      utf16_terminator_length const &rhs) noexcept;

    bool operator == (utf16_terminator_length const &lhs,
                      utf16_counted_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf16_counted_iterator_little_endian const &lhs,
                      utf16_terminator_length const &rhs) noexcept;

    bool operator != (utf16_terminator_length const &lhs,
                      utf16_counted_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf16_counted_iterator_big_endian const &lhs,
                      utf16_terminator_length const &rhs) noexcept;

    bool operator != (utf16_terminator_length const &lhs,
                      utf16_counted_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf16_counted_iterator_little_endian const &lhs,
                      utf16_terminator_length const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    void swap(m1::utf16_iterator_big_endian &lhs,
              m1::utf16_iterator_big_endian &rhs) noexcept;

    void swap(m1::utf16_iterator_little_endian &lhs,
              m1::utf16_iterator_little_endian &rhs) noexcept;

    void swap(m1::utf16_counted_iterator_big_endian &lhs,
              m1::utf16_counted_iterator_big_endian &rhs) noexcept;

    void swap(m1::utf16_counted_iterator_little_endian &lhs,
              m1::utf16_counted_iterator_little_endian &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================

#endif // M1_UTF16_ITERATOR_HPP
