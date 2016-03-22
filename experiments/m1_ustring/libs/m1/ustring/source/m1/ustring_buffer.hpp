#ifndef M1_USTRING_BUFFER_HPP
#define M1_USTRING_BUFFER_HPP

#include "m1/ustring.hpp"
#include <memory>
#include <cstddef>

namespace m1
{
    // ================================================================================================================

    code_point get_code_point(std::shared_ptr<void const> const &buffer_ptr,
                              ustring::size_type index,
                              ustring::size_type code_point_size) noexcept;

    // ================================================================================================================

    void const* get_code_point_ptr(void const *buffer_ptr,
                                   ustring::size_type index,
                                   ustring::size_type code_point_size) noexcept;

    std::shared_ptr<void const> get_code_point_ptr(std::shared_ptr<void const> const &buffer_ptr,
                                                   ustring::size_type index,
                                                   ustring::size_type code_point_size) noexcept;

    // ================================================================================================================

    // make ustring from null-terminated ascii string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    ascii_encoding encoding,
                                                    char const *c_str);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from length-terminated ascii string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    ascii_encoding encoding,
                                                    char const *c_str,
                                                    std::size_t c_str_length);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from explicitly-terminated ascii string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    ascii_encoding encoding,
                                                    char const *c_str,
                                                    char const *c_end);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from null-terminated narrow string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    char const *n_str);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from length-terminated narrow string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    char const *n_str,
                                                    std::size_t n_str_length);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from explicitly-terminated narrow string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    char const *n_str,
                                                    char const *n_end);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from null-terminated wide string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    wchar_t const *w_str);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from length-terminated wide string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    wchar_t const *w_str,
                                                    std::size_t w_str_length);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from explicitly-terminated wide string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    std::locale const &locale,
                                                    wchar_t const *w_str,
                                                    wchar_t const *w_end);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from null-terminated utf8 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf8_encoding encoding,
                                                    unsigned char const *u8_str);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from length-terminated utf8 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf8_encoding encoding,
                                                    unsigned char const *u8_str,
                                                    std::size_t u8_str_length);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from explicitly-terminated utf8 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf8_encoding encoding,
                                                    unsigned char const *u8_str,
                                                    unsigned char const *u8_end);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from null-terminated utf16 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf16_encoding encoding,
                                                    char16_t const *u16_str);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from length-terminated utf16 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf16_encoding encoding,
                                                    char16_t const *u16_str,
                                                    std::size_t u16_str_length);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from explicitly-terminated utf16 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf16_encoding encoding,
                                                    char16_t const *u16_str,
                                                    char16_t const *u16_end);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from null-terminated utf32 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf32_encoding encoding,
                                                    char32_t const *u32_str);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from length-terminated utf32 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf32_encoding encoding,
                                                    char32_t const *u32_str,
                                                    std::size_t u32_str_length);

    // --------------------------------------------------------------------------------------------------------------------

    // make ustring from explicitly-terminated utf32 string
    std::shared_ptr<void const> make_ustring_buffer(ustring::size_type &out_str_length,
                                                    ustring::size_type &out_code_point_size,
                                                    utf32_encoding encoding,
                                                    char32_t const *u32_str,
                                                    char32_t const *u32_end);

    // ================================================================================================================
} // namespace m1

#endif // M1_USTRING_BUFFER_HPP
