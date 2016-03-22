#include "m1/byte_order.hpp"
#include "m1/byte_order_iterator.hpp"
#include "m1/code_unit_terminator.hpp"
#include "m1/utf8_decode.hpp"
#include "m1/utf16_decode.hpp"
#include "m1/utf32_decode.hpp"
#include "m1/ustring_buffer.hpp"
#include "m1/pragma_message.hpp"
#include <locale>
#include <cassert>

// ====================================================================================================================

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

template <typename InputItr,
          typename InputEnd>
static m1::byte_order deduce_byte_order(m1::utf16_encoding encoding,
                                        InputItr &u16_itr,
                                        InputEnd u16_end) noexcept;

template <typename InputItr,
          typename InputEnd>
static m1::byte_order deduce_byte_order(m1::utf32_encoding encoding,
                                        InputItr &u32_itr,
                                        InputEnd u32_end) noexcept;

// --------------------------------------------------------------------------------------------------------------------

template <typename Codecvt,
          typename CodePointFunc>
static void cvt_decode_each(Codecvt const &cvt,
                            typename Codecvt::extern_type const *bytes_ptr,
                            typename Codecvt::extern_type const *bytes_end,
                            CodePointFunc code_point_func);

// --------------------------------------------------------------------------------------------------------------------

static std::size_t calculate_ustring_code_point_size(m1::code_point max_code_point) noexcept;

// --------------------------------------------------------------------------------------------------------------------

template <typename ForEachCodePointFunc>
static void calculate_ustring_buffer_size(m1::ustring::size_type &out_str_length,
                                          m1::ustring::size_type &out_code_point_size,
                                          ForEachCodePointFunc for_each_code_point_func);

// --------------------------------------------------------------------------------------------------------------------

static std::shared_ptr<unsigned char> make_uninitialized_ustring_buffer(std::size_t str_length,
                                                                        std::size_t code_point_size);

// --------------------------------------------------------------------------------------------------------------------

static std::shared_ptr<void const> make_null_ustring_buffer(m1::ustring::size_type &out_str_length,
                                                            m1::ustring::size_type &out_code_point_size);

// --------------------------------------------------------------------------------------------------------------------

static std::shared_ptr<void const> make_ustring_buffer_from_c_str(m1::ustring::size_type &out_str_length,
                                                                  m1::ustring::size_type &out_code_point_size,
                                                                  char const *c_str,
                                                                  std::size_t c_str_length);

// --------------------------------------------------------------------------------------------------------------------

static std::shared_ptr<void const> make_ustring_buffer_from_locale(m1::ustring::size_type &out_str_length,
                                                                   m1::ustring::size_type &out_code_point_size,
                                                                   std::locale const &locale,
                                                                   char const * const bytes_ptr,
                                                                   char const * const bytes_end);

// --------------------------------------------------------------------------------------------------------------------

static std::shared_ptr<void const> make_ustring_buffer_from_locale(m1::ustring::size_type &out_str_length,
                                                                   m1::ustring::size_type &out_code_point_size,
                                                                   std::locale const &locale,
                                                                   wchar_t const * const bytes_ptr,
                                                                   wchar_t const * const bytes_end);

// --------------------------------------------------------------------------------------------------------------------

template <typename ForEachCodePointFunc>
static std::shared_ptr<void const> make_ustring_buffer_from_unicode(m1::ustring::size_type &out_str_length,
                                                                    m1::ustring::size_type &out_code_point_size,
                                                                    ForEachCodePointFunc for_each_code_point_func);

// ====================================================================================================================

m1::code_point m1::get_code_point(std::shared_ptr<void const> const &buffer_ptr,
                                  ustring::size_type const index,
                                  ustring::size_type const code_point_size) noexcept
{
    assert(buffer_ptr != nullptr);

    switch(code_point_size)
    {
        case sizeof(unsigned char):
            return static_cast<code_point>(reinterpret_cast<unsigned char const*>(buffer_ptr.get())[index]);

        case sizeof(char16_t):
            return static_cast<code_point>(reinterpret_cast<char16_t const*>(buffer_ptr.get())[index]);

        case sizeof(char32_t):
            return static_cast<code_point>(reinterpret_cast<char32_t const*>(buffer_ptr.get())[index]);

        default:
            assert(false && "Invalid ustring_buffer");
            return 0;
    }
}

// ====================================================================================================================

void const* m1::get_code_point_ptr(void const * const buffer_ptr,
                                   ustring::size_type const index,
                                   ustring::size_type const code_point_size) noexcept
{
    return reinterpret_cast<unsigned char const*>(buffer_ptr) + code_point_size * index;
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::get_code_point_ptr(std::shared_ptr<void const> const &buffer_ptr,
                                                   ustring::size_type const index,
                                                   ustring::size_type const code_point_size) noexcept
{
    return std::shared_ptr<void const>(buffer_ptr,
                                       get_code_point_ptr(buffer_ptr.get(),
                                                          index,
                                                          code_point_size));
}

// ====================================================================================================================

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    ascii_encoding const /*encoding*/,
                                                    char const * const c_str)
{
    if((c_str == nullptr) || (*c_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    return make_ustring_buffer_from_c_str(/*out*/ out_str_length,
                                          /*out*/ out_code_point_size,
                                          c_str,
                                          std::char_traits<char>::length(c_str));
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    ascii_encoding const /*encoding*/,
                                                    char const * const c_str,
                                                    std::size_t const c_str_length)
{
    if((c_str == nullptr) || (c_str_length == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    return make_ustring_buffer_from_c_str(/*out*/ out_str_length,
                                          /*out*/ out_code_point_size,
                                          c_str,
                                          c_str_length);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    ascii_encoding const /*encoding*/,
                                                    char const * const c_str,
                                                    char const * const c_end)
{
    if((c_str == nullptr) || (c_str >= c_end))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    std::size_t const c_str_length = static_cast<std::size_t>(c_end - c_str);
    return make_ustring_buffer_from_c_str(/*out*/ out_str_length,
                                          /*out*/ out_code_point_size,
                                          c_str,
                                          c_str_length);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    char const * const n_str)
{
    if((n_str == nullptr) || (*n_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    std::size_t const n_str_length = std::char_traits<char>::length(n_str);
    return make_ustring_buffer_from_locale(/*out*/ out_str_length,
                                           /*out*/ out_code_point_size,
                                           locale,
                                           n_str,
                                           n_str + n_str_length);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    char const * const n_str,
                                                    std::size_t const n_str_length)
{
    if((n_str == nullptr) || (n_str_length == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    return make_ustring_buffer_from_locale(/*out*/ out_str_length,
                                           /*out*/ out_code_point_size,
                                           locale,
                                           n_str,
                                           n_str + n_str_length);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    char const * const n_str,
                                                    char const * const n_end)
{
    if((n_str == nullptr) || (n_str >= n_end))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    return make_ustring_buffer_from_locale(/*out*/ out_str_length,
                                           /*out*/ out_code_point_size,
                                           locale,
                                           n_str,
                                           n_end);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    wchar_t const * const w_str)
{
    if((w_str == nullptr) || (*w_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    std::size_t const w_str_length = std::char_traits<wchar_t>::length(w_str);
    return make_ustring_buffer_from_locale(/*out*/ out_str_length,
                                           /*out*/ out_code_point_size,
                                           locale,
                                           w_str,
                                           w_str + w_str_length);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    wchar_t const * const w_str,
                                                    std::size_t const w_str_length)
{
    if((w_str == nullptr) || (w_str_length == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    return make_ustring_buffer_from_locale(/*out*/ out_str_length,
                                           /*out*/ out_code_point_size,
                                           locale,
                                           w_str,
                                           w_str + w_str_length);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    wchar_t const * const w_str,
                                                    wchar_t const * const w_end)
{
    if((w_str == nullptr) || (*w_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    return make_ustring_buffer_from_locale(/*out*/ out_str_length,
                                           /*out*/ out_code_point_size,
                                           locale,
                                           w_str,
                                           w_end);
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf8_encoding encoding,
                                                    unsigned char const * const u8_str)
{
    if((u8_str == nullptr) || (*u8_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    unsigned char const *u8_first = u8_str;
    switch(encoding)
    {
        case utf8_encoding::byte_order_mark:
            consume_utf8_byte_order_mark(/*ref*/ u8_first,
                                         code_unit_terminator_null());
            // fallthrough

        case utf8_encoding::standard:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf8_decode_each(u8_str,
                                                                                code_unit_terminator_null(),
                                                                                f);
                                                    });

        default:
            assert(false && "Invalid encoding");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf8_encoding encoding,
                                                    unsigned char const * const u8_str,
                                                    std::size_t const u8_str_length)
{
    if((u8_str == nullptr) || (u8_str_length == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    unsigned char const *u8_first = u8_str;
    switch(encoding)
    {
        case utf8_encoding::byte_order_mark:
            consume_utf8_byte_order_mark(/*ref*/ u8_first,
                                         code_unit_terminator_never());
            // fallthrough

        case utf8_encoding::standard:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf8_decode_each_n(u8_str,
                                                                                  code_unit_terminator_never(),
                                                                                  u8_str_length,
                                                                                  f);
                                                    });

        default:
            assert(false && "Invalid encoding");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf8_encoding encoding,
                                                    unsigned char const * const u8_str,
                                                    unsigned char const * const u8_end)
{
    if((u8_str == nullptr) || (u8_str >= u8_end))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    unsigned char const *u8_first = u8_str;
    switch(encoding)
    {
        case utf8_encoding::byte_order_mark:
            consume_utf8_byte_order_mark(/*ref*/ u8_first,
                                         u8_end);
            // fallthrough

        case utf8_encoding::standard:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf8_decode_each(u8_str,
                                                                                u8_end,
                                                                                f);
                                                    });

        default:
            assert(false && "Invalid encoding");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf16_encoding encoding,
                                                    char16_t const * const u16_str)
{
    if((u16_str == nullptr) || (*u16_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    char16_t const *u16_first = u16_str;
    switch(deduce_byte_order(encoding,
                             /*ref*/ u16_first,
                             code_unit_terminator_null()))
    {
        case m1::byte_order::big_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf16_decode_each(make_big_endian_iterator(u16_str),
                                                                                code_unit_terminator_null(),
                                                                                f);
                                                    });

        case m1::byte_order::little_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf16_decode_each(make_little_endian_iterator(u16_str),
                                                                                 code_unit_terminator_null(),
                                                                                 f);
                                                    });

        default:
            assert(false && "Invalid byte_order");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf16_encoding encoding,
                                                    char16_t const * const u16_str,
                                                    std::size_t const u16_str_length)
{
    if((u16_str == nullptr) || (u16_str_length == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    char16_t const *u16_first = u16_str;
    switch(deduce_byte_order(encoding,
                             /*ref*/ u16_first,
                             code_unit_terminator_never()))
    {
        case m1::byte_order::big_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf16_decode_each_n(make_big_endian_iterator(u16_str),
                                                                                   code_unit_terminator_never(),
                                                                                   u16_str_length,
                                                                                   f);
                                                    });

        case m1::byte_order::little_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf16_decode_each_n(make_little_endian_iterator(u16_str),
                                                                                   code_unit_terminator_never(),
                                                                                   u16_str_length,
                                                                                   f);
                                                    });

        default:
            assert(false && "Invalid byte_order");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf16_encoding encoding,
                                                    char16_t const * const u16_str,
                                                    char16_t const * const u16_end)
{
    if((u16_str == nullptr) || (u16_str >= u16_end))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    char16_t const *u16_first = u16_str;
    switch(deduce_byte_order(encoding,
                             /*ref*/ u16_first,
                             u16_end))
    {
        case m1::byte_order::big_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf16_decode_each(make_big_endian_iterator(u16_str),
                                                                                 make_big_endian_iterator(u16_end),
                                                                                 f);
                                                    });

        case m1::byte_order::little_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf16_decode_each(make_little_endian_iterator(u16_str),
                                                                                 make_little_endian_iterator(u16_end),
                                                                                 f);
                                                    });

        default:
            assert(false && "Invalid byte_order");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf32_encoding const encoding,
                                                    char32_t const * const u32_str)
{
    if((u32_str == nullptr) || (*u32_str == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    char32_t const *u32_first = u32_str;
    switch(deduce_byte_order(encoding,
                             u32_first,
                             code_unit_terminator_null()))
    {
        case m1::byte_order::big_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf32_decode_each(make_big_endian_iterator(u32_str),
                                                                                code_unit_terminator_null(),
                                                                                f);
                                                    });

        case m1::byte_order::little_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf32_decode_each(make_little_endian_iterator(u32_str),
                                                                                 code_unit_terminator_null(),
                                                                                 f);
                                                    });

        default:
            assert(false && "Invalid byte_order");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf32_encoding const encoding,
                                                    char32_t const * const u32_str,
                                                    std::size_t const u32_str_length)
{
    if((u32_str == nullptr) || (u32_str_length == 0))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    char32_t const *u32_first = u32_str;
    switch(deduce_byte_order(encoding,
                             u32_first,
                             code_unit_terminator_never()))
    {
        case m1::byte_order::big_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf32_decode_each_n(make_big_endian_iterator(u32_str),
                                                                                   code_unit_terminator_never(),
                                                                                   u32_str_length,
                                                                                   f);
                                                    });

        case m1::byte_order::little_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf32_decode_each_n(make_little_endian_iterator(u32_str),
                                                                                   code_unit_terminator_never(),
                                                                                   u32_str_length,
                                                                                   f);
                                                    });

        default:
            assert(false && "Invalid byte_order");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// --------------------------------------------------------------------------------------------------------------------

std::shared_ptr<void const> m1::make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf32_encoding encoding,
                                                    char32_t const * const u32_str,
                                                    char32_t const * const u32_end)
{
    if((u32_str == nullptr) || (u32_str >= u32_end))
    {
        return make_null_ustring_buffer(/*out*/ out_str_length,
                                        /*out*/ out_code_point_size);
    }

    char32_t const *u32_first = u32_str;
    switch(deduce_byte_order(encoding,
                             u32_first,
                             u32_end))
    {
        case m1::byte_order::big_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf32_decode_each(make_big_endian_iterator(u32_str),
                                                                                 make_big_endian_iterator(u32_end),
                                                                                 f);
                                                    });

        case m1::byte_order::little_endian:
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return utf32_decode_each(make_little_endian_iterator(u32_str),
                                                                                 make_little_endian_iterator(u32_end),
                                                                                 f);
                                                    });

        default:
            assert(false && "Invalid byte_order");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }
}

// ====================================================================================================================

template <typename InputItr,
          typename InputEnd>
/*static*/ m1::byte_order deduce_byte_order(m1::utf16_encoding encoding,
                                            InputItr &u16_itr,
                                            InputEnd u16_end) noexcept
{
    switch(encoding)
    {
        case m1::utf16_encoding::byte_order_mark:
            return m1::consume_utf16_byte_order_mark(u16_itr, u16_end);

        case m1::utf16_encoding::big_endian:
            return m1::byte_order::big_endian;

        case m1::utf16_encoding::little_endian:
            return m1::byte_order::little_endian;

        case m1::utf16_encoding::native_endian:
            return m1::native_byte_order();

        default:
            assert(false && "Invalid encoding");
            return m1::byte_order::big_endian;
    }
}

// --------------------------------------------------------------------------------------------------------------------

template <typename InputItr,
          typename InputEnd>
/*static*/ m1::byte_order deduce_byte_order(m1::utf32_encoding encoding,
                                            InputItr &u32_itr,
                                            InputEnd u32_end) noexcept
{
    switch(encoding)
    {
        case m1::utf32_encoding::byte_order_mark:
            return m1::consume_utf32_byte_order_mark(u32_itr, u32_end);

        case m1::utf32_encoding::big_endian:
            return m1::byte_order::big_endian;

        case m1::utf32_encoding::little_endian:
            return m1::byte_order::little_endian;

        case m1::utf32_encoding::native_endian:
            return m1::native_byte_order();

        default:
            assert(false && "Invalid encoding");
            return m1::byte_order::big_endian;
    }
}

// ====================================================================================================================

template <typename Codecvt,
          typename CodePointFunc>
/*static*/ void cvt_decode_each(Codecvt const &cvt,
                                typename Codecvt::extern_type const * const bytes_ptr,
                                typename Codecvt::extern_type const * const bytes_end,
                                CodePointFunc code_point_func)
{
    typename Codecvt::state_type state {};

    for(typename Codecvt::extern_type const *ptr = bytes_ptr; ptr != bytes_end;)
    {
        typename Codecvt::intern_type cvt_value = 0;
        typename Codecvt::intern_type *cvt_next = &cvt_value;

        std::codecvt_base::result const cvt_result = cvt.in(/*ref*/ state,
                                                            ptr,
                                                            bytes_end,
                                                            /*ref*/ ptr,
                                                            &cvt_value,
                                                            &cvt_value + 1,
                                                            /*ref*/ cvt_next);
        if(cvt_result != std::codecvt_base::ok)
        {
            break;
        }

        m1::code_point const c = static_cast<m1::code_point>(cvt_value);
        code_point_func(c);
    }
}

// ====================================================================================================================

/*static*/ std::size_t calculate_ustring_code_point_size(m1::code_point const max_code_point) noexcept
{
    return (max_code_point > static_cast<std::size_t>(std::numeric_limits<char16_t>::max()))      ? sizeof(char32_t) :
           (max_code_point > static_cast<std::size_t>(std::numeric_limits<unsigned char>::max())) ? sizeof(char16_t) :
           sizeof(unsigned char);
}

// ===================================================================================================================

template <typename ForEachCodePointFunc>
/*static*/ void calculate_ustring_buffer_size(m1::ustring::size_type &out_str_length,
                                              m1::ustring::size_type &out_code_point_size,
                                              ForEachCodePointFunc for_each_code_point_func)
{
    std::size_t str_length = 0;
    m1::code_point max_code_point = 0;

    for_each_code_point_func([&] (m1::code_point const c)
                             {
                                 if(c > max_code_point)
                                 {
                                     max_code_point = c;
                                 }

                                 ++str_length;
                             });

    out_str_length = str_length;
    out_code_point_size = calculate_ustring_code_point_size(max_code_point);
}

// ====================================================================================================================

/*static*/ std::shared_ptr<unsigned char> make_uninitialized_ustring_buffer(std::size_t const str_length,
                                                                            std::size_t const code_point_size)
{
    std::size_t const buffer_size = (str_length + 1) * code_point_size;
    std::size_t const allocator_extra_buffer_size = buffer_size - sizeof(unsigned char); // subtract because allocate_shared<char> will add that back in
    std::shared_ptr<unsigned char> const buffer_ptr = std::allocate_shared<unsigned char>(ustring_allocator<unsigned char>(allocator_extra_buffer_size));

    // set zero terminator
    unsigned char * const buffer_terminator = buffer_ptr.get() + (str_length * code_point_size);
    std::memset(buffer_terminator, 0, code_point_size);

    return buffer_ptr;
}

// ====================================================================================================================

static std::shared_ptr<void const> make_null_ustring_buffer(m1::ustring::size_type &out_str_length,
                                                            m1::ustring::size_type &out_code_point_size)
{
    out_str_length = 0;
    out_code_point_size = 0;
    return nullptr;
}

// --------------------------------------------------------------------------------------------------------------------

static std::shared_ptr<void const> make_ustring_buffer_from_c_str(m1::ustring::size_type &out_str_length,
                                                                  m1::ustring::size_type &out_code_point_size,
                                                                  char const * const c_str,
                                                                  std::size_t const c_str_length)
{
    std::size_t const code_point_size = sizeof(unsigned char);
    std::shared_ptr<unsigned char> const buffer_ptr = make_uninitialized_ustring_buffer(c_str_length, code_point_size);

    char * const buffer_first = reinterpret_cast<char*>(buffer_ptr.get());
    std::char_traits<char>::copy(buffer_first, c_str, c_str_length);

    out_str_length = c_str_length;
    out_code_point_size = code_point_size;
    return buffer_ptr;
}

// --------------------------------------------------------------------------------------------------------------------

/*static*/ std::shared_ptr<void const> make_ustring_buffer_from_locale(m1::ustring::size_type &out_str_length,
                                                                       m1::ustring::size_type &out_code_point_size,
                                                                       std::locale const &locale,
                                                                       char const * const bytes_ptr,
                                                                       char const * const bytes_end)
{
    #pragma M1_MESSAGE("change std::uint32_t to char32_t, this is a workaround for VS 2015 linker error")
    typedef std::codecvt<std::uint32_t, char, std::mbstate_t> codecvt_utf32;

    if(std::has_facet<codecvt_utf32>(locale))
    {
        codecvt_utf32 const &cvt = std::use_facet<codecvt_utf32>(locale);
        if(!cvt.always_noconv())
        {
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return cvt_decode_each(cvt,
                                                                               bytes_ptr,
                                                                               bytes_end,
                                                                               f);
                                                    });
        }
    }

    // non-converting locale, treat as c_str
    return make_ustring_buffer_from_c_str(/*out*/ out_str_length,
                                          /*out*/ out_code_point_size,
                                          bytes_ptr,
                                          bytes_end - bytes_ptr);
}

// --------------------------------------------------------------------------------------------------------------------

/*static*/ std::shared_ptr<void const> make_ustring_buffer_from_locale(m1::ustring::size_type &out_str_length,
                                                                       m1::ustring::size_type &out_code_point_size,
                                                                       std::locale const &locale,
                                                                       wchar_t const * const bytes_ptr,
                                                                       wchar_t const * const bytes_end)
{
    // TODO: change std::uint32_t to char32_t, this is a workaround for VS 2015 linker error
    typedef std::codecvt<std::uint32_t, wchar_t, std::mbstate_t> codecvt_utf32;

    if(std::has_facet<codecvt_utf32>(locale))
    {
        codecvt_utf32 const &cvt = std::use_facet<codecvt_utf32>(locale);
        if(!cvt.always_noconv())
        {
            return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                                    /*out*/ out_code_point_size,
                                                    [&](auto &&f)
                                                    {
                                                        return cvt_decode_each(cvt,
                                                                               bytes_ptr,
                                                                               bytes_end,
                                                                               f);
                                                    });
        }
    }

    // non-converting locale, treat as utf-32 encoded string
    return make_ustring_buffer_from_unicode(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size,
                                            [&](auto &&f)
                                            {
                                                for (wchar_t const *p = bytes_ptr; p != bytes_end; ++p)
                                                {
                                                    f(*p);
                                                }
                                            });
}

// --------------------------------------------------------------------------------------------------------------------

template <typename ForEachCodePointFunc>
/*static*/ std::shared_ptr<void const> make_ustring_buffer_from_unicode(m1::ustring::size_type &out_str_length,
                                                                        m1::ustring::size_type &out_code_point_size,
                                                                        ForEachCodePointFunc for_each_code_point_func)
{
    calculate_ustring_buffer_size(/*out*/ out_str_length,
                                  /*out*/ out_code_point_size,
                                  for_each_code_point_func);

    std::shared_ptr<unsigned char> const buffer_ptr = make_uninitialized_ustring_buffer(out_str_length, out_code_point_size);

    switch(out_code_point_size)
    {
        case sizeof(unsigned char):
        {
            unsigned char *code_point_ptr = reinterpret_cast<unsigned char*>(buffer_ptr.get());
            for_each_code_point_func([&] (m1::code_point const c)
                                     {
                                         *code_point_ptr++ = static_cast<unsigned char>(c);
                                     });
            break;
        }

        case sizeof(char16_t):
        {
            char16_t *code_point_ptr = reinterpret_cast<char16_t*>(buffer_ptr.get());
            for_each_code_point_func([&] (m1::code_point const c)
                                     {
                                         *code_point_ptr++ = static_cast<char16_t>(c);
                                     });
            break;
        }

        case sizeof(char32_t):
        {
            char32_t *code_point_ptr = reinterpret_cast<char32_t*>(buffer_ptr.get());
            for_each_code_point_func([&] (m1::code_point const c)
                                     {
                                         *code_point_ptr++ = static_cast<char32_t>(c);
                                     });
            break;
        }

        default:
            assert(false && "Invalid ustring_buffer");
            return make_null_ustring_buffer(/*out*/ out_str_length,
                                            /*out*/ out_code_point_size);
    }

    return buffer_ptr;
}

// ====================================================================================================================
