#include "m1/ustring.hpp"
#include <limits>
#include <string>
#include <codecvt>
#include <cassert>

// =====================================================================================================================

namespace
{
    // temporary work around lack of std::allocate_shared_array
    template <typename T>
    class ustring_allocator
    {
    public:
        typedef T value_type;
        template <typename U> friend class ustring_allocator;

        explicit ustring_allocator(std::size_t extra_buffer_size) noexcept;
        template <typename U> ustring_allocator(ustring_allocator<U> const &rhs) noexcept;

        ustring_allocator(ustring_allocator &&rhs) noexcept = default;
        ustring_allocator(ustring_allocator const &rhs) noexcept = default;
        ustring_allocator& operator = (ustring_allocator &&rhs) noexcept = default;
        ustring_allocator& operator = (ustring_allocator const &rhs) noexcept = default;
        ~ustring_allocator() noexcept = default;

        value_type* allocate(std::size_t n);
        void deallocate(value_type *p, std::size_t n) noexcept;

    private:
        // members:
        std::size_t m_ExtraBufferSize = 0;
    };

    // ================================================================================================================

    template <typename T>
    /*explicit*/ ustring_allocator<T>::ustring_allocator(std::size_t const extra_buffer_size) noexcept
        : m_ExtraBufferSize(extra_buffer_size)
    {
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    template <typename U> ustring_allocator<T>::ustring_allocator(ustring_allocator<U> const &rhs) noexcept
        : m_ExtraBufferSize(rhs.m_ExtraBufferSize)
    {
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    typename ustring_allocator<T>::value_type* ustring_allocator<T>::allocate(std::size_t const n)
    {
        return static_cast<value_type*>(::operator new(n * sizeof(value_type) + m_ExtraBufferSize));
    }

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    void ustring_allocator<T>::deallocate(value_type * const p, std::size_t const /*n*/) noexcept
    {
        ::operator delete(p);
    }

    // ================================================================================================================
} // namespace

// ====================================================================================================================

template <typename CodePoint>
static std::shared_ptr<void const> make_ustring_buffer_from_fixed_sized_encoding(CodePoint const *str_first,
                                                                                 CodePoint const *str_end);

// --------------------------------------------------------------------------------------------------------------------

template <typename CodeUnit, typename Codecvt>
static std::shared_ptr<void const> make_ustring_buffer_from_variable_sized_encoding(Codecvt const &cvt,
                                                                                    CodeUnit const * const code_unit_begin,
                                                                                    CodeUnit const * const code_unit_end,
                                                                                    std::size_t &out_str_length,
                                                                                    std::size_t &out_code_point_size);

// =====================================================================================================================

/*explicit*/ m1::ustring::ustring(char const * const u8_str)
    : m_BufferPtr(make_ustring_buffer_from_variable_sized_encoding(std::codecvt_utf8<char32_t>(),
                                                                   u8_str,
                                                                   u8_str + std::char_traits<char>::length(u8_str),
                                                                   /*out*/ m_StrLength,
                                                                   /*out*/ m_CodePointSize))
    , m_BufferEnd(static_cast<char const*>(m_BufferPtr.get()) + m_StrLength * m_CodePointSize)
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::ustring::ustring(wchar_t const * const w_str)
    : m_StrLength(std::char_traits<wchar_t>::length(w_str))
    , m_CodePointSize(sizeof(*w_str))
    , m_BufferPtr(make_ustring_buffer_from_fixed_sized_encoding(w_str, w_str + m_StrLength))
    , m_BufferEnd(static_cast<wchar_t const*>(m_BufferPtr.get()) + m_StrLength)
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::ustring::ustring(char16_t const * const u16_str)
    : m_BufferPtr(make_ustring_buffer_from_variable_sized_encoding(std::codecvt_utf16<char32_t>(),
                                                                   u16_str,
                                                                   u16_str + std::char_traits<char16_t>::length(u16_str),
                                                                   /*out*/ m_StrLength,
                                                                   /*out*/ m_CodePointSize))
    , m_BufferEnd(static_cast<char const*>(m_BufferPtr.get()) + m_StrLength * m_CodePointSize)
{
}

// ---------------------------------------------------------------------------------------------------------------------

/*explicit*/ m1::ustring::ustring(char32_t const * const u32_str)
    : m_StrLength(std::char_traits<char32_t>::length(u32_str))
    , m_CodePointSize(sizeof(*u32_str))
    , m_BufferPtr(make_ustring_buffer_from_fixed_sized_encoding(u32_str, u32_str + m_StrLength))
    , m_BufferEnd(static_cast<char32_t const*>(m_BufferPtr.get()) + m_StrLength)
{
}

// ---------------------------------------------------------------------------------------------------------------------

//ustring(char const *u8_str, size_type str_length); // utf8
//ustring(wchar_t const *w_str, size_type str_length); // wide
//ustring(char16_t const *u16_str, size_type str_length); // utf16
//ustring(char32_t const *u32_str, size_type str_length); // utf32

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(char const *u8_str, char const *u8_end)
    : m_BufferPtr(make_ustring_buffer_from_variable_sized_encoding(std::codecvt_utf8<char32_t>(),
                                                                   u8_str,
                                                                   u8_end,
                                                                   /*out*/ m_StrLength,
                                                                   /*out*/ m_CodePointSize))
    , m_BufferEnd(static_cast<char const*>(m_BufferPtr.get()) + m_StrLength * m_CodePointSize)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(wchar_t const *w_str, wchar_t const *w_end)
    : m_StrLength(w_end - w_str)
    , m_CodePointSize(sizeof(*w_str))
    , m_BufferPtr(make_ustring_buffer_from_fixed_sized_encoding(w_str, w_end))
    , m_BufferEnd(static_cast<wchar_t const*>(m_BufferPtr.get()) + m_StrLength)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(char16_t const *u16_str, char16_t const *u16_end)
    : m_BufferPtr(make_ustring_buffer_from_variable_sized_encoding(std::codecvt_utf16<char32_t>(),
                                                                   u16_str,
                                                                   u16_end,
                                                                   /*out*/ m_StrLength,
                                                                   /*out*/ m_CodePointSize))
    , m_BufferEnd(static_cast<char const*>(m_BufferPtr.get()) + m_StrLength * m_CodePointSize)
{
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(char32_t const *u32_str, char32_t const *u32_end)
    : m_StrLength(u32_end - u32_str)
    , m_CodePointSize(sizeof(*u32_str))
    , m_BufferPtr(make_ustring_buffer_from_fixed_sized_encoding(u32_str, u32_end))
    , m_BufferEnd(static_cast<char32_t const*>(m_BufferPtr.get()) + m_StrLength)
{
}

// ---------------------------------------------------------------------------------------------------------------------

//ustring(code_point_iterator const &begin,
//        code_point_iterator const &end) noexcept;

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::ustring(std::size_t const str_length,
                     std::size_t const code_point_size,
                     std::shared_ptr<void const> const &buffer_owner,
                     void const *buffer_ptr,
                     void const *buffer_end)
    : m_StrLength(str_length)
    , m_CodePointSize(code_point_size)
    , m_BufferPtr(buffer_owner, buffer_ptr)
    , m_BufferEnd(buffer_end)
{
}

// ---------------------------------------------------------------------------------------------------------------------

//code_point_iterator begin() const noexcept;
//code_point_iterator cbegin() const noexcept;
//reverse_code_point_iterator rbegin() const noexcept;
//reverse_code_point_iterator crbegin() const noexcept;
//code_point_iterator end() const noexcept;
//code_point_iterator cend() const noexcept;
//reverse_code_point_iterator rend() const noexcept;
//reverse_code_point_iterator crend() const noexcept;

// ---------------------------------------------------------------------------------------------------------------------

bool m1::ustring::empty() const noexcept
{
    return m_StrLength == 0;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::size_type m1::ustring::length() const noexcept
{
    return m_StrLength;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point m1::ustring::at(size_type const index) const
{
    if(index < m_StrLength)
    {
        return operator [] (index);
    }

    throw std::out_of_range("Invalid index");
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point m1::ustring::operator [] (size_type const index) const noexcept
{
    assert(index < m_StrLength);

    switch(m_CodePointSize)
    {
        case sizeof(char):
            return static_cast<code_point>(reinterpret_cast<char const*>(m_BufferPtr.get())[index]);

        case sizeof(char16_t):
            return static_cast<code_point>(reinterpret_cast<char16_t const*>(m_BufferPtr.get())[index]);

        case sizeof(char32_t):
            return static_cast<code_point>(reinterpret_cast<char32_t const*>(m_BufferPtr.get())[index]);

        default:
            assert(false && "Invalid ustring");
            return 0;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point m1::ustring::front() const noexcept
{
    return operator [] (0);
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::code_point m1::ustring::back() const noexcept
{
    return operator [] (m_StrLength - 1);
}

// ---------------------------------------------------------------------------------------------------------------------

void const* m1::ustring::data() const noexcept
{
    return m_BufferPtr.get();
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring::size_type m1::ustring::size() const noexcept
{
    return m_StrLength * m_CodePointSize;
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring m1::ustring::substr(size_type const index,
                                size_type const length /*= npos*/) const noexcept
{
    if(index < m_StrLength)
    {
        size_type const substr_max_length = m_StrLength - index;
        size_type const substr_length = (length < substr_max_length) ? length : substr_max_length;

        switch(m_CodePointSize)
        {
            case sizeof(char):
            {
                char const * const substr = reinterpret_cast<char const*>(m_BufferPtr.get()) + index;
                return m1::ustring(substr_length, // str_length
                                   m_CodePointSize, // code_point_size
                                   m_BufferPtr, // buffer_owner
                                   substr, // buffer_ptr
                                   substr + substr_length); // buffer_end
            }

            case sizeof(char16_t):
            {
                char16_t const * const substr = reinterpret_cast<char16_t const*>(m_BufferPtr.get()) + index;
                return m1::ustring(substr_length, // str_length
                                   m_CodePointSize, // code_point_size
                                   m_BufferPtr, // buffer_owner
                                   substr, // buffer_ptr
                                   substr + substr_length); // buffer_end
            }

            case sizeof(char32_t):
            {
                char32_t const * const substr = reinterpret_cast<char32_t const*>(m_BufferPtr.get()) + index;
                return m1::ustring(substr_length, // str_length
                                   m_CodePointSize, // code_point_size
                                   m_BufferPtr, // buffer_owner
                                   substr, // buffer_ptr
                                   substr + substr_length); // buffer_end
            }

            default:
                assert(false && "Invalid ustring");
        }
    }

    return ustring();
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::ustring::clear() noexcept
{
    *this = ustring();
}

// ---------------------------------------------------------------------------------------------------------------------

void m1::ustring::swap(ustring &rhs) noexcept
{
    using std::swap;
    swap(m_StrLength, rhs.m_StrLength);
    swap(m_CodePointSize, rhs.m_CodePointSize);
    swap(m_BufferPtr, rhs.m_BufferPtr);
    swap(m_BufferEnd, rhs.m_BufferEnd);
}

// =====================================================================================================================

m1::ustring m1::literals::operator "" _s(char const * const c_str,
                                         std::size_t const length) noexcept
{
   return m1::ustring(length, // str_length
                      sizeof(*c_str), // code_point_size
                      std::shared_ptr<void const>(), // buffer_owner
                      c_str, // buffer_ptr
                      c_str + length); // buffer_end
}

// ---------------------------------------------------------------------------------------------------------------------

m1::ustring m1::literals::operator "" _s(wchar_t const * const w_str,
                                         std::size_t const length) noexcept
{
   return m1::ustring(length, // str_length
                      sizeof(*w_str), // code_point_size
                      std::shared_ptr<void const>(), // buffer_owner
                      w_str, // buffer_ptr
                      w_str + length); // buffer_end
}

// =====================================================================================================================

static std::shared_ptr<void const> make_uninitialized_ustring_buffer(std::size_t const str_length,
                                                                     std::size_t const code_point_size)
{
    std::size_t const buffer_size = (str_length + 1) * code_point_size;
    std::size_t const ustring_allocator_extra_buffer_size = ustring_buffer_size - sizeof(char); // subtract because allocate_shared<char> will add that back in
    std::shared_ptr<char> const ustring_buffer_ptr = std::allocate_shared<char>(ustring_allocator<char>(ustring_allocator_extra_buffer_size));

    // set zero terminator
    char * const ustring_buffer_terminator = ustring_buffer_ptr.get() + (str_length * code_point_size);
    std::memset(ustring_buffer_terminator, 0, code_point_size);

    return ustring_buffer_ptr;
}

// ====================================================================================================================

template <typename CodePoint>
/*static*/ std::shared_ptr<void const> make_ustring_buffer_from_fixed_sized_encoding(CodePoint const *str_first,
                                                                                     CodePoint const *str_end)
{
    std::size_t const str_length = static_cast<std::size_t>(str_end - str_first);
    std::shared_ptr<char> const ustring_buffer_ptr = make_uninitialized_ustring_buffer(str_length, sizeof(CodePoint));

    CodePoint * const ustring_buffer_first = reinterpret_cast<CodePoint*>(ustring_buffer_ptr.get());
    std::char_traits<CodePoint>::copy(ustring_buffer_first, str_first, str_length);

    return ustring_buffer_ptr;
}

// ====================================================================================================================

/*static*/ std::size_t code_point_size(m1::ustring::code_point const max_code_point)
{
    return (max_code_point > static_cast<std::size_t>(std::numeric_limits<char16_t>::max())) ? sizeof(char32_t) :
           (max_code_point > static_cast<std::size_t>(std::numeric_limits<char>::max())) ? sizeof(char16_t) :
           sizeof(char);
}

// ====================================================================================================================

template <typename CodeUnit>
/*static*/ std::size_t code_unit_n_length(CodeUnit const * const str,
                                          std::size_t const max_length)
{
    CodeUnit const *p = str;
    std::size_t n = 0;

    while(*p && n < max_length)
    {
        ++p;
        ++n;
    }

    return n;
}

// ====================================================================================================================

template <typename CodeUnit, typename Codecvt>
/*static*/ bool convert_uchar_increment_code_unit(Codecvt const &cvt,
                                                  typename Codecvt::state_type &cvt_state,
                                                  CodeUnit const *&code_unit_ptr,
                                                  CodeUnit const * const code_unit_end,
                                                  m1::ustring::code_point &out_code_point)
{
    using m1::ustring::code_point;

    code_point cvt_ch = 0;
    code_point * const cvt_ch_ptr = &cvt_ch;
    code_point * const cvt_ch_end = cvt_ch_ptr + 1;
    code_point *cvt_ch_next = cvt_ch_ptr;

    char const * const str_byte_ptr = reinterpret_cast<char const*>(code_unit_ptr);
    char const * const str_byte_end = reinterpret_cast<char const*>(code_unit_end);
    char const * str_byte_next = str_byte_ptr;

    std::codecvt_base::result const cvt_result = cvt.in(cvt_state,
                                                        str_byte_ptr,           // from
                                                        str_byte_end,           // from_end
                                                        /*ref*/ str_byte_next,  // from_next
                                                        cvt_ch_ptr,             // to
                                                        cvt_ch_end,             // to_end
                                                        /*ref*/ cvt_ch_next);   // to_next

    switch(cvt_result)
    {
        case std::codecvt_base::error:
            return false;

        case std::codecvt_base::noconv:
            // no conversion, just cast and increment
            out_code_point = static_cast<code_point>(*code_unit_ptr++);
            return true;

        default:
            code_unit_ptr = reinterpret_cast<CodeUnit const*>(str_byte_next);
            out_code_point = cvt_ch;
            return true;
    }
}

// ====================================================================================================================

template <typename CodeUnit, typename Codecvt>
/*static*/ void calculate_ustring_buffer_params(Codecvt const &cvt,
                                                CodeUnit const * const code_unit_begin,
                                                CodeUnit const * const code_unit_end,
                                                std::size_t &out_str_length,
                                                std::size_t &out_code_point_size)
{
    std::size_t const code_unit_max_count = (cvt.max_length() + sizeof(CodeUnit) - 1) / sizeof(CodeUnit);

    typename Codecvt::state_type cvt_state{};
    code_point ustring_ch_max = 0;
    std::size_t str_length = 0;

    for (CodeUnit const *code_unit_ptr = code_unit_begin; code_unit_ptr != code_unit_end; ++str_length)
    {
        code_point ustring_ch;
        if (!convert_uchar_increment_code_unit(cvt,
                                               cvt_state,
                                               /*ref*/ code_unit_ptr, // increments
                                               code_unit_end,
                                               /*out*/ ustring_ch))
        {
            break;
        }

        // track max code point value
        if (ustring_ch > ustring_ch_max)
        {
            ustring_ch_max = ustring_ch;
        }
    }

    // calculate code_point_size from max_code_point_value
    out_str_length = str_length;
    out_code_point_size = code_point_size(ustring_ch_max);
}

// ====================================================================================================================

template <typename Codecvt>
/*static*/ void fill_ustring_buffer_from_variable_sized_encoding(char * const ustring_buffer_begin,
                                                                 char * const ustring_buffer_end,
                                                                 std::size_t const ustring_str_length,
                                                                 std::size_t const ustring_code_point_size,
                                                                 Codecvt const &cvt,
                                                                 void const * const code_unit_begin,
                                                                 void const * const code_unit_end)
{
    static_assert(false, "implement");
}

// ====================================================================================================================

template <typename CodeUnit, typename Codecvt>
/*static*/ std::shared_ptr<void const> make_ustring_buffer_from_variable_sized_encoding(Codecvt const &cvt,
                                                                                        CodeUnit const * const code_unit_begin,
                                                                                        CodeUnit const * const code_unit_end,
                                                                                        std::size_t &out_str_length,
                                                                                        std::size_t &out_code_point_size)
{
    assert(code_unit_begin != nullptr);

    calculate_ustring_buffer_params(cvt,
                                    code_unit_begin,
                                    code_unit_end,
                                    /*out*/ out_str_length,
                                    /*out*/ out_code_point_size);

    std::shared_ptr<char> const ustring_buffer_ptr = make_uninitialized_ustring_buffer(out_str_length,
                                                                                       out_code_point_size);

    fill_ustring_buffer_from_variable_sized_encoding(ustring_buffer_ptr.get(),
                                                     ustring_buffer_ptr.get() + (out_str_length * out_code_point_size),
                                                     out_str_length,
                                                     out_code_point_size,
                                                     cvt,
                                                     code_unit_begin,
                                                     code_unit_end);

    return ustring_buffer_ptr;

//    switch(code_point_size)
//    {
//        case sizeof(char):
//        {
//            return make_ustring_buffer_from_variable_sized_encoding<char>(str_length,
//                                                                          cvt,
//                                                                          code_unit_begin,
//                                                                          code_unit_end);
//        }
//
//        case sizeof(char16_t):
//        {
//            return make_ustring_buffer_from_variable_sized_encoding<char16_t>(str_length,
//                                                                              cvt,
//                                                                              code_unit_begin,
//                                                                              code_unit_end);
//        }
//
//        case sizeof(char32_t):
//        {
//            return make_ustring_buffer_from_variable_sized_encoding<char32_t>(str_length,
//                                                                              cvt,
//                                                                              code_unit_begin,
//                                                                              code_unit_end);
//        }
//
//        default:
//            return nullptr;
//    }
//
//    // allocate ustring_buffer then copy str into ustring_buffer by converting each code_point and copying code_point_size bytes of that code_point into ustring_buffer
//    std::size_t const ustring_buffer_size = (str_length + 1) * out_code_point_size; // include room for zero character
//    std::size_t const ustring_allocator_extra_buffer_size = ustring_buffer_size - sizeof(char); // subtract because allocate_shared<char> will add that back in
//
//    std::shared_ptr<char> const ustring_buffer_ptr = std::allocate_shared<char>(ustring_allocator<char>(ustring_allocator_extra_buffer_size));
//    char * const ustring_first = ustring_buffer_ptr.get();
//    char * const ustring_end = ustring_first + str_length;
//
//    std::char_traits<CodePoint>::copy(ustring_first, str_first, str_length);
//    *ustring_end = 0; // assign zero character
//
//#error implement
//    return std::shared_ptr<void const>();
}

// =====================================================================================================================
