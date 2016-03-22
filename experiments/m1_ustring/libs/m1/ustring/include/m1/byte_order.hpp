#ifndef M1_BYTE_ORDER_HPP
#define M1_BYTE_ORDER_HPP

#include <type_traits>
#include <cstdint>

namespace m1
{
    // ================================================================================================================

    enum class byte_order
    {
        big_endian,
        little_endian,
    };

    constexpr byte_order native_byte_order() noexcept;

    constexpr char16_t swap_byte_order(char16_t value) noexcept;
    constexpr char32_t swap_byte_order(char32_t value) noexcept;
    constexpr std::uint16_t swap_byte_order(std::uint16_t value) noexcept;
    constexpr std::uint32_t swap_byte_order(std::uint32_t value) noexcept;

    // converts from big_endian to native and from native to big_endian
    constexpr char16_t big_endian(char16_t value) noexcept;
    constexpr char32_t big_endian(char32_t value) noexcept;
    constexpr std::uint16_t big_endian(std::uint16_t value) noexcept;
    constexpr std::uint32_t big_endian(std::uint32_t value) noexcept;

    // converts from little_endian to native and from native to little_endian
    constexpr char16_t little_endian(char16_t value) noexcept;
    constexpr char32_t little_endian(char32_t value) noexcept;
    constexpr std::uint16_t little_endian(std::uint16_t value) noexcept;
    constexpr std::uint32_t little_endian(std::uint32_t value) noexcept;

    // ================================================================================================================
}

// ====================================================================================================================

constexpr m1::byte_order m1::native_byte_order() noexcept
{
    return ('\xFF\xFE' == 0xFFFE) ? byte_order::big_endian
                                  : byte_order::little_endian;
}

// ====================================================================================================================

namespace m1
{
namespace impl
{
    // ================================================================================================================

    using is_native_byte_order_big_endian = std::integral_constant<bool, native_byte_order() == byte_order::big_endian>;
    using is_native_byte_order_little_endian = std::integral_constant<bool, native_byte_order() == byte_order::little_endian>;

    // ================================================================================================================

    template <typename T>
    constexpr T set_byte_order(T value, std::true_type swap_bytes);

    template <typename T>
    constexpr T set_byte_order(T value, std::false_type swap_bytes);

    // ================================================================================================================
} // namespace impl
} // namespace m1

// ====================================================================================================================

constexpr char16_t m1::swap_byte_order(char16_t const value) noexcept
{
    return ((value & 0x00FF) << 8) |
           ((value & 0xFF00) >> 8);
}

// --------------------------------------------------------------------------------------------------------------------

constexpr char32_t m1::swap_byte_order(char32_t const value) noexcept
{
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) <<  8) |
           ((value & 0x00FF0000) >>  8) |
           ((value & 0xFF000000) >> 24);
}

// --------------------------------------------------------------------------------------------------------------------

constexpr std::uint16_t m1::swap_byte_order(std::uint16_t const value) noexcept
{
    return ((value & 0x00FF) << 8) |
           ((value & 0xFF00) >> 8);
}

// --------------------------------------------------------------------------------------------------------------------

constexpr std::uint32_t m1::swap_byte_order(std::uint32_t const value) noexcept
{
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) <<  8) |
           ((value & 0x00FF0000) >>  8) |
           ((value & 0xFF000000) >> 24);
}

// ====================================================================================================================

constexpr char16_t m1::big_endian(char16_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_little_endian());
}

// --------------------------------------------------------------------------------------------------------------------

constexpr char32_t m1::big_endian(char32_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_little_endian());
}

// --------------------------------------------------------------------------------------------------------------------

constexpr std::uint16_t m1::big_endian(std::uint16_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_little_endian());
}

// --------------------------------------------------------------------------------------------------------------------

constexpr std::uint32_t m1::big_endian(std::uint32_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_little_endian());
}

// ====================================================================================================================

constexpr char16_t m1::little_endian(char16_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_big_endian());
}

// --------------------------------------------------------------------------------------------------------------------

constexpr char32_t m1::little_endian(char32_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_big_endian());
}

// --------------------------------------------------------------------------------------------------------------------

constexpr std::uint16_t m1::little_endian(std::uint16_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_big_endian());
}

// --------------------------------------------------------------------------------------------------------------------

constexpr std::uint32_t m1::little_endian(std::uint32_t value) noexcept
{
    return impl::set_byte_order(value, /*swap_bytes =*/ impl::is_native_byte_order_big_endian());
}

// ====================================================================================================================

template <typename T>
constexpr T m1::impl::set_byte_order(T const value, std::true_type const /*swap_bytes*/)
{
    return swap_byte_order(value);
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T>
constexpr T m1::impl::set_byte_order(T const value, std::false_type const /*swap_bytes*/)
{
    return value;
}

// ====================================================================================================================

#endif // M1_BYTE_ORDER_HPP
