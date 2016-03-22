#ifndef M1_USTRING_HPP
#define M1_USTRING_HPP

#include <iterator>
#include <memory>

namespace m1
{
    // ================================================================================================================

    class ustring;
    typedef char32_t code_point;

    // ----------------------------------------------------------------------------------------------------------------

    // normalization:
    enum class normal_form
    {
        NFD,  // Canonical Decomposition
        NFC,  // Canonical Decomposition, followed by Canonical Composition
        NFKD, // Compatibility Decomposition
        NFKC, // Compatibility Decomposition, followed by Canonical Composition
    };

    ustring normalize(ustring const &str,
                      normal_form form = normal_form::NFC);

    // ----------------------------------------------------------------------------------------------------------------

    // comparisons: uses compare(lhs, rhs) with default normal_form and compare_case
    bool operator == (ustring const &lhs, ustring const &rhs);
    bool operator != (ustring const &lhs, ustring const &rhs);
    bool operator <  (ustring const &lhs, ustring const &rhs);
    bool operator <= (ustring const &lhs, ustring const &rhs);
    bool operator >  (ustring const &lhs, ustring const &rhs);
    bool operator >= (ustring const &lhs, ustring const &rhs);

    enum class compare_case : bool
    {
        no,
        yes,
    };

    int compare(ustring const &lhs,
                ustring const &rhs,
                normal_form form = normal_form::NFC,
                compare_case compare = compare_case::yes);

    std::size_t hash(ustring const &str) noexcept;

    void swap(ustring &lhs,
              ustring &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    // input encodings:
    enum class ascii_encoding
    {
        standard,
    };

    enum class utf8_encoding
    {
        standard,           // assumes there is no BOM
        byte_order_mark,    // looks for 3 byte header containing: {0xEF, 0xBB, 0xBF} -- consumed and ignored if present
    };

    enum class utf16_encoding
    {
        byte_order_mark,    // looks for 2 byte header containing: {0xFE, 0xFF} or {0xFF, 0xFE} -- uses value to determine big_endian or little_endian, if not present big_endian is assumed
        big_endian,         // assumes there is no BOM
        little_endian,      // assumes there is no BOM
        native_endian,      // assumes there is no BOM
    };

    enum class utf32_encoding
    {
        byte_order_mark,    // looks for 4 byte header containing: {0x00, 0x00, 0xFE, 0xFF} or {0xFF, 0xFE, 0x00, 0x00} -- uses value to determine big_endian or little_endian, if not present big_endian is assumed
        big_endian,         // assumes there is no BOM
        little_endian,      // assumes there is no BOM
        native_endian,      // assumes there is no BOM
    };

    constexpr ascii_encoding const ascii_encoding_default = ascii_encoding::standard;
    constexpr utf8_encoding const utf8_encoding_default = utf8_encoding::standard;
    constexpr utf16_encoding const utf16_encoding_default = utf16_encoding::byte_order_mark;
    constexpr utf32_encoding const utf32_encoding_default = utf32_encoding::byte_order_mark;

    // ----------------------------------------------------------------------------------------------------------------

    namespace literals
    {
       ustring operator "" _us(char const *c_str, std::size_t length) noexcept; // ascii string literal
       ustring operator "" _us(wchar_t const *w_str, std::size_t length) noexcept; // wide string literal
       ustring operator "" _us(char32_t const *u32_str, std::size_t length) noexcept; // utf32 string literal
    }

    ustring make_ustring_view(char const *c_str, std::size_t length) noexcept;
    ustring make_ustring_view(wchar_t const *w_str, std::size_t length) noexcept;
    ustring make_ustring_view(char32_t const *u32_str, std::size_t length) noexcept;

    template <std::size_t N> ustring make_ustring_view(char const (&c_str)[N]) noexcept;
    template <std::size_t N> ustring make_ustring_view(wchar_t const (&w_str)[N]) noexcept;
    template <std::size_t N> ustring make_ustring_view(char32_t const (&u32_str)[N]) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    class ustring
    {
    public:
       // types:
        typedef std::size_t size_type;

        // iterator types: 
        class code_point_iterator; // random access
        typedef std::reverse_iterator<code_point_iterator> reverse_code_point_iterator;

        class grapheme_cluster_iterator; // bidirectional
        typedef std::reverse_iterator<grapheme_cluster_iterator> reverse_grapheme_cluster_iterator;

        // constants:
        static size_type const npos = static_cast<size_type>(-1);

        // construct:
        ustring() noexcept;

        // null terminated strings:
        ustring(ascii_encoding encoding, char const *c_str);
        ustring(std::locale const &locale, char const *n_str);
        ustring(std::locale const &locale, wchar_t const *w_str);
        ustring(utf8_encoding encoding, unsigned char const *u8_str);
        ustring(utf16_encoding encoding, char16_t const *u16_str);
        ustring(utf32_encoding encoding, char32_t const *u32_str);

        // length terminated strings:
        ustring(ascii_encoding encoding, char const *c_str, size_type str_length);
        ustring(std::locale const &locale, char const *n_str, size_type str_length);
        ustring(std::locale const &locale, wchar_t const *w_str, size_type str_length);
        ustring(utf8_encoding encoding, unsigned char const *u8_str, size_type str_length);
        ustring(utf16_encoding encoding, char16_t const *u16_str, size_type str_length);
        ustring(utf32_encoding encoding, char32_t const *u32_str, size_type str_length);

        // explicitly terminated strings:
        ustring(ascii_encoding encoding, char const *c_str, char const *c_end);
        ustring(std::locale const &locale, char const *n_str, char const *n_end);
        ustring(std::locale const &locale, wchar_t const *w_str, wchar_t const *w_end);
        ustring(utf8_encoding encoding, unsigned char const *u8_str, unsigned char const *u8_end);
        ustring(utf16_encoding encoding, char16_t const *u16_str, char16_t const *u16_end);
        ustring(utf32_encoding encoding, char32_t const *u32_str, char32_t const *u32_end);

        // substr:
        ustring(code_point_iterator const &begin,
                code_point_iterator const &end) noexcept;

        // default move/copy/destroy:
        ustring(ustring &&rhs) noexcept;
        ustring(ustring const &rhs) noexcept;
        ustring& operator = (ustring &&rhs) noexcept;
        ustring& operator = (ustring const &rhs) noexcept;
        ~ustring() noexcept;

        // iterators:
        code_point_iterator begin() const noexcept;
        code_point_iterator cbegin() const noexcept;
        reverse_code_point_iterator rbegin() const noexcept;
        reverse_code_point_iterator crbegin() const noexcept;

        code_point_iterator end() const noexcept;
        code_point_iterator cend() const noexcept;
        reverse_code_point_iterator rend() const noexcept;
        reverse_code_point_iterator crend() const noexcept;

        // capacity:
        bool empty() const noexcept;
        size_type length() const noexcept; // code_point count

        // element access:
        code_point at(size_type index) const;
        code_point operator [] (size_type index) const noexcept;
        code_point front() const noexcept;
        code_point back() const noexcept;

        // buffer access:
        void const* data() const noexcept;
        size_type size() const noexcept; // byte count

        // string operations:
        ustring substr(size_type index,
                       size_type length = npos) const noexcept;

        // modifiers:
        void clear() noexcept;
        void swap(ustring &rhs) noexcept;

        // friends:
        friend ustring literals::operator "" _us(char const *c_str, std::size_t length) noexcept;
        friend ustring literals::operator "" _us(wchar_t const *w_str, std::size_t length) noexcept;
        friend ustring literals::operator "" _us(char32_t const *u32_str, std::size_t length) noexcept;

        friend ustring make_ustring_view(char const *c_str, std::size_t length) noexcept;
        friend ustring make_ustring_view(wchar_t const *w_str, std::size_t length) noexcept;
        friend ustring make_ustring_view(char32_t const *u32_str, std::size_t length) noexcept;

    private:
        ustring(size_type str_length,
                size_type code_point_size,
                std::shared_ptr<void const> const &buffer_owner,
                void const *buffer_ptr,
                void const *buffer_end);

        // members:
        // m_CodePointSize is calculated from max value of code point in string (0xFF => 1, 0xFFFF => 2, else 4)
        // support non-owning buffer (fixed sized encodings only, others will have to be decoded to support random access)
        // supports sharing of owning buffer between strings/substrings
        // strings are null terminated, substrings not ending at the same location as the original string are not null terminated
        size_type m_StrLength                   {0};
        size_type m_CodePointSize               {0};
        std::shared_ptr<void const> m_BufferPtr {nullptr};
        void const *m_BufferEnd                 {nullptr};
    };

    // ================================================================================================================

    class ustring::code_point_iterator
        : public std::iterator<std::random_access_iterator_tag, // iterator_tag
                               code_point,                      // value_type
                               std::ptrdiff_t,                  // difference_type
                               void,                            // pointer
                               code_point>                      // reference
    {
    friend class ustring;
    public:
        code_point_iterator(code_point_iterator &&rhs);
        code_point_iterator(code_point_iterator const &rhs);
        code_point_iterator& operator = (code_point_iterator &&rhs);
        code_point_iterator& operator = (code_point_iterator const &rhs);
        ~code_point_iterator();

        code_point operator * () const;
        code_point operator [] (difference_type n) const;

        code_point_iterator& operator ++ ();
        code_point_iterator operator ++ (int);

        code_point_iterator& operator -- ();
        code_point_iterator operator -- (int);

        code_point_iterator& operator += (difference_type n);
        code_point_iterator& operator -= (difference_type n);

        friend code_point_iterator operator + (code_point_iterator const &lhs,
                                               difference_type rhs);

        friend code_point_iterator operator + (difference_type lhs,
                                               code_point_iterator const &rhs);

        friend difference_type operator - (code_point_iterator const &lhs,
                                           code_point_iterator const &rhs);

        friend bool operator == (code_point_iterator const &lhs,
                                 code_point_iterator const &rhs);

        friend bool operator != (code_point_iterator const &lhs,
                                 code_point_iterator const &rhs);

        friend bool operator < (code_point_iterator const &lhs,
                                code_point_iterator const &rhs);

        friend bool operator <= (code_point_iterator const &lhs,
                                 code_point_iterator const &rhs);

        friend bool operator > (code_point_iterator const &lhs,
                                code_point_iterator const &rhs);

        friend bool operator >= (code_point_iterator const &lhs,
                                 code_point_iterator const &rhs);

    private:
        code_point_iterator(ustring const &str,
                            ustring::size_type index);
        code_point_iterator() = delete;

        // members:
        ustring const *m_StrPtr    {nullptr};
        ustring::size_type m_Index {0};

    };

    // ----------------------------------------------------------------------------------------------------------------

    ustring::code_point_iterator operator + (ustring::code_point_iterator const &lhs,
                                             ustring::code_point_iterator::difference_type rhs);

    ustring::code_point_iterator operator + (ustring::code_point_iterator::difference_type lhs,
                                             ustring::code_point_iterator const &rhs);

    bool operator == (ustring::code_point_iterator const &lhs,
                      ustring::code_point_iterator const &rhs);

    bool operator != (ustring::code_point_iterator const &lhs,
                      ustring::code_point_iterator const &rhs);

    bool operator < (ustring::code_point_iterator const &lhs,
                     ustring::code_point_iterator const &rhs);

    bool operator <= (ustring::code_point_iterator const &lhs,
                      ustring::code_point_iterator const &rhs);

    bool operator > (ustring::code_point_iterator const &lhs,
                     ustring::code_point_iterator const &rhs);

    bool operator >= (ustring::code_point_iterator const &lhs,
                      ustring::code_point_iterator const &rhs);

    // ================================================================================================================
} // namespace m1

// ====================================================================================================================

namespace std
{
    // ================================================================================================================

    template <>
    struct hash<m1::ustring>
    {
       typedef m1::ustring argument_type;
       typedef std::size_t result_type;

       result_type operator () (argument_type const &arg) const;
    };

    // ================================================================================================================

    void swap(m1::ustring &lhs,
              m1::ustring &rhs) noexcept;

    // ================================================================================================================
} // namespace std

// ====================================================================================================================
// ====================================================================================================================

template <std::size_t N> m1::ustring m1::make_ustring_view(char const (&c_str)[N]) noexcept
{
    return make_ustring_view(c_str, (c_str[N - 1] == 0) ? (N - 1) : N);
}

// --------------------------------------------------------------------------------------------------------------------

template <std::size_t N> m1::ustring m1::make_ustring_view(wchar_t const (&w_str)[N]) noexcept
{
    return make_ustring_view(w_str, (w_str[N - 1] == 0) ? (N - 1) : N);
}

// --------------------------------------------------------------------------------------------------------------------

template <std::size_t N> m1::ustring m1::make_ustring_view(char32_t const (&u32_str)[N]) noexcept
{
    return make_ustring_view(u32_str, (u32_str[N - 1] == 0) ? (N - 1) : N);
}

// ====================================================================================================================

#endif // M1_USTRING_HPP
