#ifndef R2_MEMORY_OF_HPP
#define R2_MEMORY_OF_HPP

#include <initializer_list>
#include <array>
#include <cstddef>
#include <cassert>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    struct memory_size_description
    {
        std::size_t size;
        std::size_t align;
    };

    // ----------------------------------------------------------------------------------------------------------------

    constexpr memory_size_description operator * (memory_size_description const &lhs, std::size_t rhs) noexcept;
    constexpr memory_size_description operator * (std::size_t lhs, memory_size_description const &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    constexpr memory_size_description memory_of() noexcept;

    template <typename T0,
              typename T1,
              typename ...Ts>
    constexpr memory_size_description memory_of() noexcept;

    memory_size_description memory_of(std::initializer_list<memory_size_description> const &elem_descs) noexcept;

    // ================================================================================================================

    struct memory_offset_description
    {
        std::size_t offset;
        std::size_t align;
    };

    // ----------------------------------------------------------------------------------------------------------------

    memory_offset_description& operator += (memory_offset_description &lhs,
                                            memory_size_description const &rhs) noexcept;

    constexpr memory_offset_description operator + (memory_offset_description const &lhs,
                                                    memory_size_description const &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    constexpr std::size_t offset_of(memory_offset_description const &curr,
                                    memory_size_description const &next) noexcept;

    // ================================================================================================================
/*
    template <typename T>
    constexpr std::array<std::size_t, 1> offsets_of() noexcept;

    template <typename T0,
              typename T1,
              typename ...Ts>
    constexpr std::array<std::size_t, 2 + sizeof...(Ts)> offsets_of() noexcept;
*/
    // ================================================================================================================
} // namespace r2

// ====================================================================================================================
// r2::memory_size_description
// ====================================================================================================================

namespace r2
{
namespace memory_of_impl
{
    // ================================================================================================================

    constexpr bool is_pow2(std::size_t const value) noexcept
    {
        return value && !(value & (value - 1));
    }

    // ================================================================================================================

    template <typename Integral>
    constexpr Integral align_up(Integral const value,
                                std::size_t const align) noexcept
    {
        // implementation from:
        // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4201.html

        return
            assert(is_pow2(align)),
            (value + (Integral(align) - 1)) & ~Integral(align - 1);
    }

    // ================================================================================================================

    constexpr std::size_t align_max(std::size_t const lhs,
                                    std::size_t const rhs) noexcept
    {
        return
            assert(is_pow2(lhs) && is_pow2(rhs)),
            (lhs > rhs) ? lhs : rhs;
    }

    // ================================================================================================================

    constexpr memory_offset_description sum(memory_offset_description const &curr,
                                            memory_size_description const &next) noexcept
    {
        return curr + next;
    }

    // ================================================================================================================

    template <typename ...MemDescs>
    constexpr memory_offset_description sum(memory_offset_description const &curr,
                                            memory_size_description const &next,
                                            MemDescs const &...remainder) noexcept
    {
        return sum(curr + next, remainder...);

    }

    // ================================================================================================================

    constexpr memory_size_description finalize(memory_offset_description const &memory_offset_description)
    {
        return {align_up(memory_offset_description.offset, memory_offset_description.align),
                memory_offset_description.align};
    }

    // ================================================================================================================
} // namespace memory_of_impl
} // namespace r2

// ====================================================================================================================

constexpr r2::memory_size_description r2::operator * (memory_size_description const &lhs, std::size_t rhs) noexcept
{
    return {lhs.size * rhs, lhs.align};
}

// --------------------------------------------------------------------------------------------------------------------

constexpr r2::memory_size_description r2::operator * (std::size_t lhs, memory_size_description const &rhs) noexcept
{
    return {lhs * rhs.size, rhs.align};
}

// ====================================================================================================================

template <typename T>
constexpr r2::memory_size_description r2::memory_of() noexcept
{
    return {sizeof(T), alignof(T)};
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T0,
          typename T1,
          typename ...Ts>
constexpr r2::memory_size_description r2::memory_of() noexcept
{
    using namespace memory_of_impl;

    return finalize(sum(memory_offset_description{0, 1},
                        memory_of<T0>(),
                        memory_of<T1>(),
                        memory_of<Ts>()...));
}

// --------------------------------------------------------------------------------------------------------------------

inline r2::memory_size_description r2::memory_of(std::initializer_list<memory_size_description> const &elem_descs) noexcept
{
    using namespace memory_of_impl;

    memory_offset_description curr = {0, 1};

    for(memory_size_description const &elem_desc : elem_descs)
    {
        curr = sum(curr, elem_desc);
    }

    return finalize(curr);
}

// ====================================================================================================================

inline r2::memory_offset_description& r2::operator += (memory_offset_description &lhs,
                                                       memory_size_description const &rhs) noexcept
{
    lhs = lhs + rhs;
    return lhs;
}

// --------------------------------------------------------------------------------------------------------------------

constexpr r2::memory_offset_description r2::operator + (memory_offset_description const &lhs,
                                                        memory_size_description const &rhs) noexcept
{
    using namespace memory_of_impl;

    return {align_up(lhs.offset, rhs.align) + rhs.size,
            align_max(lhs.align, rhs.align)};
}

// ====================================================================================================================

constexpr std::size_t r2::offset_of(memory_offset_description const &curr,
                                    memory_size_description const &next) noexcept
{
    using namespace memory_of_impl;

    return align_up(curr.offset, next.align);
}

// ====================================================================================================================
/*
template <typename T>
constexpr std::array<std::size_t, 1> r2::offsets_of() noexcept
{
    return {0};
}
*/
// --------------------------------------------------------------------------------------------------------------------
/*
template <typename T0,
          typename T1,
          typename ...Ts>
constexpr std::array<std::size_t, 2 + sizeof...(Ts)> r2::offsets_of() noexcept
{
    using namespace memory_of_impl;

//    return {0,
//            align_up(memory_of<T0>().size, memory_of<T1>().align),
//            align_up(memory_of<T0, T1>().size, memory_of<T2>().align)};
}
*/
// ====================================================================================================================

#endif // R2_MEMORY_OF_HPP
