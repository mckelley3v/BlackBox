#ifndef M1_UTF32_ITERATOR_HPP
#define M1_UTF32_ITERATOR_HPP

#include "m1/byte_order.hpp"
#include <iterator>

namespace m1
{
    // ================================================================================================================

    typedef char32_t code_point;

    class utf32_iterator_big_endian;
    class utf32_iterator_little_endian;
    class utf32_counted_iterator_big_endian;
    class utf32_counted_iterator_little_endian;
    class utf32_terminator_null;
    class utf32_terminator_length;

    using utf32_iterator = std::conditional_t<native_byte_order() == byte_order::big_endian,
                                              utf32_iterator_big_endian,
                                              utf32_iterator_little_endian>;

    using utf32_counted_iterator = std::conditional_t<native_byte_order() == byte_order::big_endian,
                                                      utf32_counted_iterator_big_endian,
                                                      utf32_counted_iterator_little_endian>;

    // ================================================================================================================

    byte_order consume_utf32_byte_order_mark(char32_t const *&u32_str) noexcept;

    // ================================================================================================================

    class utf32_iterator_big_endian
        : public std::iterator<std::random_access_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf32_iterator_big_endian() noexcept;
        explicit utf32_iterator_big_endian(char32_t const *u32_str) noexcept;
        utf32_iterator_big_endian(utf32_iterator_big_endian &&rhs) noexcept;
        utf32_iterator_big_endian(utf32_iterator_big_endian const &rhs) noexcept;
        utf32_iterator_big_endian& operator = (utf32_iterator_big_endian &&rhs) noexcept;
        utf32_iterator_big_endian& operator = (utf32_iterator_big_endian const &rhs) noexcept;
        ~utf32_iterator_big_endian() noexcept;

        code_point operator * () const noexcept;
        code_point operator [] (difference_type n) const noexcept;

        utf32_iterator_big_endian& operator ++ () noexcept;
        utf32_iterator_big_endian operator ++ (int) noexcept;
        utf32_iterator_big_endian& operator -- () noexcept;
        utf32_iterator_big_endian operator -- (int) noexcept;

        utf32_iterator_big_endian& operator += (difference_type n) noexcept;
        utf32_iterator_big_endian& operator -= (difference_type n) noexcept;

        void swap(utf32_iterator_big_endian &rhs) noexcept;

        friend utf32_iterator_big_endian operator + (utf32_iterator_big_endian const &lhs,
                                                     difference_type rhs) noexcept;

        friend utf32_iterator_big_endian operator + (difference_type lhs,
                                                     utf32_iterator_big_endian const &rhs) noexcept;

        friend difference_type operator - (utf32_iterator_big_endian const &lhs,
                                           utf32_iterator_big_endian const &rhs) noexcept;

        friend bool operator == (utf32_iterator_big_endian const &lhs,
                                 utf32_iterator_big_endian const &rhs) noexcept;

        friend bool operator != (utf32_iterator_big_endian const &lhs,
                                 utf32_iterator_big_endian const &rhs) noexcept;

        friend bool operator < (utf32_iterator_big_endian const &lhs,
                                utf32_iterator_big_endian const &rhs) noexcept;

        friend bool operator <= (utf32_iterator_big_endian const &lhs,
                                 utf32_iterator_big_endian const &rhs) noexcept;

        friend bool operator > (utf32_iterator_big_endian const &lhs,
                                utf32_iterator_big_endian const &rhs) noexcept;

        friend bool operator >= (utf32_iterator_big_endian const &lhs,
                                 utf32_iterator_big_endian const &rhs) noexcept;

    private:
        // members:
        char32_t const *m_CodeUnitPtr {nullptr};
    };

    // ----------------------------------------------------------------------------------------------------------------

    utf32_iterator_big_endian operator + (utf32_iterator_big_endian const &lhs,
                                          utf32_iterator_big_endian::difference_type rhs) noexcept;

    utf32_iterator_big_endian operator + (utf32_iterator_big_endian::difference_type lhs,
                                          utf32_iterator_big_endian const &rhs) noexcept;

    utf32_iterator_big_endian::difference_type operator - (utf32_iterator_big_endian const &lhs,
                                                           utf32_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept;

    bool operator < (utf32_iterator_big_endian const &lhs,
                     utf32_iterator_big_endian const &rhs) noexcept;

    bool operator <= (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept;

    bool operator > (utf32_iterator_big_endian const &lhs,
                     utf32_iterator_big_endian const &rhs) noexcept;

    bool operator >= (utf32_iterator_big_endian const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf32_iterator_little_endian
        : public std::iterator<std::random_access_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf32_iterator_little_endian() noexcept;
        explicit utf32_iterator_little_endian(char32_t const *u32_str) noexcept;
        utf32_iterator_little_endian(utf32_iterator_little_endian &&rhs) noexcept;
        utf32_iterator_little_endian(utf32_iterator_little_endian const &rhs) noexcept;
        utf32_iterator_little_endian& operator = (utf32_iterator_little_endian &&rhs) noexcept;
        utf32_iterator_little_endian& operator = (utf32_iterator_little_endian const &rhs) noexcept;
        ~utf32_iterator_little_endian() noexcept;

        code_point operator * () const noexcept;
        code_point operator [] (difference_type n) const noexcept;

        utf32_iterator_little_endian& operator ++ () noexcept;
        utf32_iterator_little_endian operator ++ (int) noexcept;
        utf32_iterator_little_endian& operator -- () noexcept;
        utf32_iterator_little_endian operator -- (int) noexcept;

        utf32_iterator_little_endian& operator += (difference_type n) noexcept;
        utf32_iterator_little_endian& operator -= (difference_type n) noexcept;

        void swap(utf32_iterator_little_endian &rhs) noexcept;

        friend utf32_iterator_little_endian operator + (utf32_iterator_little_endian const &lhs,
                                                        difference_type rhs) noexcept;

        friend utf32_iterator_little_endian operator + (difference_type lhs,
                                                        utf32_iterator_little_endian const &rhs) noexcept;

        friend difference_type operator - (utf32_iterator_little_endian const &lhs,
                                           utf32_iterator_little_endian const &rhs) noexcept;

        friend bool operator == (utf32_iterator_little_endian const &lhs,
                                 utf32_iterator_little_endian const &rhs) noexcept;

        friend bool operator != (utf32_iterator_little_endian const &lhs,
                                 utf32_iterator_little_endian const &rhs) noexcept;

        friend bool operator < (utf32_iterator_little_endian const &lhs,
                                utf32_iterator_little_endian const &rhs) noexcept;

        friend bool operator <= (utf32_iterator_little_endian const &lhs,
                                 utf32_iterator_little_endian const &rhs) noexcept;

        friend bool operator > (utf32_iterator_little_endian const &lhs,
                                utf32_iterator_little_endian const &rhs) noexcept;

        friend bool operator >= (utf32_iterator_little_endian const &lhs,
                                 utf32_iterator_little_endian const &rhs) noexcept;

    private:
        // members:
        char32_t const *m_CodeUnitPtr {nullptr};
    };

    // ----------------------------------------------------------------------------------------------------------------

    utf32_iterator_little_endian operator + (utf32_iterator_little_endian const &lhs,
                                             utf32_iterator_little_endian::difference_type rhs) noexcept;

    utf32_iterator_little_endian operator + (utf32_iterator_little_endian::difference_type lhs,
                                             utf32_iterator_little_endian const &rhs) noexcept;

    utf32_iterator_little_endian::difference_type operator - (utf32_iterator_little_endian const &lhs,
                                                              utf32_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept;

    bool operator < (utf32_iterator_little_endian const &lhs,
                     utf32_iterator_little_endian const &rhs) noexcept;

    bool operator <= (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept;

    bool operator > (utf32_iterator_little_endian const &lhs,
                     utf32_iterator_little_endian const &rhs) noexcept;

    bool operator >= (utf32_iterator_little_endian const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf32_counted_iterator_big_endian
        : public std::iterator<std::random_access_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf32_counted_iterator_big_endian() noexcept;
        explicit utf32_counted_iterator_big_endian(char32_t const *u32_str, std::size_t count = 0) noexcept;
        utf32_counted_iterator_big_endian(utf32_counted_iterator_big_endian &&rhs) noexcept;
        utf32_counted_iterator_big_endian(utf32_counted_iterator_big_endian const &rhs) noexcept;
        utf32_counted_iterator_big_endian& operator = (utf32_counted_iterator_big_endian &&rhs) noexcept;
        utf32_counted_iterator_big_endian& operator = (utf32_counted_iterator_big_endian const &rhs) noexcept;
        ~utf32_counted_iterator_big_endian() noexcept;

        code_point operator * () const noexcept;
        code_point operator [] (difference_type n) const noexcept;

        utf32_counted_iterator_big_endian& operator ++ () noexcept;
        utf32_counted_iterator_big_endian operator ++ (int) noexcept;
        utf32_counted_iterator_big_endian& operator -- () noexcept;
        utf32_counted_iterator_big_endian operator -- (int) noexcept;

        utf32_counted_iterator_big_endian& operator += (difference_type n) noexcept;
        utf32_counted_iterator_big_endian& operator -= (difference_type n) noexcept;

        std::size_t count() const noexcept;

        void swap(utf32_counted_iterator_big_endian &rhs) noexcept;

        friend utf32_counted_iterator_big_endian operator + (utf32_counted_iterator_big_endian const &lhs,
                                                             difference_type rhs) noexcept;

        friend utf32_counted_iterator_big_endian operator + (difference_type lhs,
                                                             utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend difference_type operator - (utf32_counted_iterator_big_endian const &lhs,
                                           utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator == (utf32_counted_iterator_big_endian const &lhs,
                                 utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator != (utf32_counted_iterator_big_endian const &lhs,
                                 utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator < (utf32_counted_iterator_big_endian const &lhs,
                                utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator <= (utf32_counted_iterator_big_endian const &lhs,
                                 utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator > (utf32_counted_iterator_big_endian const &lhs,
                                utf32_counted_iterator_big_endian const &rhs) noexcept;

        friend bool operator >= (utf32_counted_iterator_big_endian const &lhs,
                                 utf32_counted_iterator_big_endian const &rhs) noexcept;

    private:
        // members:
        char32_t const *m_CodeUnitPtr {nullptr};
        std::size_t m_CodePointCount  {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    utf32_counted_iterator_big_endian operator + (utf32_counted_iterator_big_endian const &lhs,
                                                  utf32_counted_iterator_big_endian::difference_type rhs) noexcept;

    utf32_counted_iterator_big_endian operator + (utf32_counted_iterator_big_endian::difference_type lhs,
                                                  utf32_counted_iterator_big_endian const &rhs) noexcept;

    utf32_counted_iterator_big_endian::difference_type operator - (utf32_counted_iterator_big_endian const &lhs,
                                                                   utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator < (utf32_counted_iterator_big_endian const &lhs,
                     utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator <= (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator > (utf32_counted_iterator_big_endian const &lhs,
                     utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator >= (utf32_counted_iterator_big_endian const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf32_counted_iterator_little_endian
        : public std::iterator<std::random_access_iterator_tag,
                               code_point,      // value_type
                               std::ptrdiff_t,  // difference_type
                               code_point,      // reference
                               void>            // pointer
    {
    public:
        utf32_counted_iterator_little_endian() noexcept;
        explicit utf32_counted_iterator_little_endian(char32_t const *u32_str, std::size_t count = 0) noexcept;
        utf32_counted_iterator_little_endian(utf32_counted_iterator_little_endian &&rhs) noexcept;
        utf32_counted_iterator_little_endian(utf32_counted_iterator_little_endian const &rhs) noexcept;
        utf32_counted_iterator_little_endian& operator = (utf32_counted_iterator_little_endian &&rhs) noexcept;
        utf32_counted_iterator_little_endian& operator = (utf32_counted_iterator_little_endian const &rhs) noexcept;
        ~utf32_counted_iterator_little_endian() noexcept;

        code_point operator * () const noexcept;
        code_point operator [] (difference_type n) const noexcept;

        utf32_counted_iterator_little_endian& operator ++ () noexcept;
        utf32_counted_iterator_little_endian operator ++ (int) noexcept;
        utf32_counted_iterator_little_endian& operator -- () noexcept;
        utf32_counted_iterator_little_endian operator -- (int) noexcept;

        utf32_counted_iterator_little_endian& operator += (difference_type n) noexcept;
        utf32_counted_iterator_little_endian& operator -= (difference_type n) noexcept;

        std::size_t count() const noexcept;

        void swap(utf32_counted_iterator_little_endian &rhs) noexcept;

        friend utf32_counted_iterator_little_endian operator + (utf32_counted_iterator_little_endian const &lhs,
                                                                difference_type rhs) noexcept;

        friend utf32_counted_iterator_little_endian operator + (difference_type lhs,
                                                                utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend difference_type operator - (utf32_counted_iterator_little_endian const &lhs,
                                           utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator == (utf32_counted_iterator_little_endian const &lhs,
                                 utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator != (utf32_counted_iterator_little_endian const &lhs,
                                 utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator < (utf32_counted_iterator_little_endian const &lhs,
                                utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator <= (utf32_counted_iterator_little_endian const &lhs,
                                 utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator > (utf32_counted_iterator_little_endian const &lhs,
                                utf32_counted_iterator_little_endian const &rhs) noexcept;

        friend bool operator >= (utf32_counted_iterator_little_endian const &lhs,
                                 utf32_counted_iterator_little_endian const &rhs) noexcept;

    private:
        // members:
        char32_t const *m_CodeUnitPtr {nullptr};
        std::size_t m_CodePointCount  {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    utf32_counted_iterator_little_endian operator + (utf32_counted_iterator_little_endian const &lhs,
                                                     utf32_counted_iterator_little_endian::difference_type rhs) noexcept;

    utf32_counted_iterator_little_endian operator + (utf32_counted_iterator_little_endian::difference_type lhs,
                                                     utf32_counted_iterator_little_endian const &rhs) noexcept;

    utf32_counted_iterator_little_endian::difference_type operator - (utf32_counted_iterator_little_endian const &lhs,
                                                                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator < (utf32_counted_iterator_little_endian const &lhs,
                     utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator <= (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator > (utf32_counted_iterator_little_endian const &lhs,
                     utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator >= (utf32_counted_iterator_little_endian const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    // ================================================================================================================

    class utf32_terminator_null {};
    constexpr utf32_terminator_null const utf32_end{};

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf32_terminator_null const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf32_iterator_big_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator == (utf32_terminator_null const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf32_iterator_little_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator == (utf32_terminator_null const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator == (utf32_terminator_null const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator != (utf32_terminator_null const &lhs,
                      utf32_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf32_iterator_big_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator != (utf32_terminator_null const &lhs,
                      utf32_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf32_iterator_little_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator != (utf32_terminator_null const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    bool operator != (utf32_terminator_null const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_null const &rhs) noexcept;

    // ================================================================================================================

    class utf32_terminator_length
    {
    public:
        utf32_terminator_length() noexcept;
        explicit utf32_terminator_length(std::size_t length) noexcept;
        utf32_terminator_length(utf32_terminator_length &&rhs) noexcept;
        utf32_terminator_length(utf32_terminator_length const &rhs) noexcept;
        utf32_terminator_length& operator = (utf32_terminator_length &&rhs) noexcept;
        utf32_terminator_length& operator = (utf32_terminator_length const &rhs) noexcept;
        ~utf32_terminator_length() noexcept;

        std::size_t length() const noexcept;

    private:
        // members:
        std::size_t m_Length {0};
    };

    // ----------------------------------------------------------------------------------------------------------------

    bool operator == (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator == (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept;

    bool operator == (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator == (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept;

    bool operator != (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_big_endian const &rhs) noexcept;

    bool operator != (utf32_counted_iterator_big_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept;

    bool operator != (utf32_terminator_length const &lhs,
                      utf32_counted_iterator_little_endian const &rhs) noexcept;

    bool operator != (utf32_counted_iterator_little_endian const &lhs,
                      utf32_terminator_length const &rhs) noexcept;

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    void swap(m1::utf32_iterator_big_endian &lhs,
              m1::utf32_iterator_big_endian &rhs) noexcept;

    void swap(m1::utf32_iterator_little_endian &lhs,
              m1::utf32_iterator_little_endian &rhs) noexcept;

    void swap(m1::utf32_counted_iterator_big_endian &lhs,
              m1::utf32_counted_iterator_big_endian &rhs) noexcept;

    void swap(m1::utf32_counted_iterator_little_endian &lhs,
              m1::utf32_counted_iterator_little_endian &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================

#endif // M1_UTF32_ITERATOR_HPP
