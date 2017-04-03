#ifndef R2_MEMORY_OF_HPP
#define R2_MEMORY_OF_HPP

#include <initializer_list>
#include <cstddef>
#include <cassert>

// ====================================================================================================================

namespace r2
{
    // ================================================================================================================

    struct memory_desc
    {
        std::size_t size;
        std::size_t align;
    };

    // ----------------------------------------------------------------------------------------------------------------

    constexpr memory_desc operator * (memory_desc const &lhs, std::size_t rhs) noexcept;
    constexpr memory_desc operator * (std::size_t lhs, memory_desc const &rhs) noexcept;

    // ----------------------------------------------------------------------------------------------------------------

    template <typename T>
    constexpr memory_desc memory_of() noexcept;

    template <typename T0,
              typename T1,
              typename ...Ts>
    constexpr memory_desc memory_of() noexcept;

    memory_desc memory_of(std::initializer_list<memory_desc> const &mem_descs) noexcept;

    // ================================================================================================================
} // namespace r2

// ====================================================================================================================
// r2::memory_desc
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

    constexpr std::size_t align_up(std::size_t const value,
                                   std::size_t const align) noexcept
    {
        assert(is_pow2(align));
        return (value + (align - 1)) & ~(align - 1);
    }

    // ================================================================================================================

    constexpr std::size_t align_max(std::size_t const lhs,
                                    std::size_t const rhs) noexcept
    {
        assert(is_pow2(lhs));
        assert(is_pow2(rhs));

        return (lhs > rhs) ? lhs : rhs;
    }

    // ================================================================================================================

    constexpr memory_desc combine(memory_desc const &curr,
                                  memory_desc const &next) noexcept
    {
        return {align_up(curr.size, next.align) + next.size,
                align_max(curr.align, next.align)};

    }

    // ================================================================================================================

    template <typename ...MemDescs>
    constexpr memory_desc combine(memory_desc const &curr,
                                  memory_desc const &next,
                                  MemDescs const &...remainder) noexcept
    {
        return combine(combine(curr, next), remainder...);

    }

    // ================================================================================================================

    constexpr memory_desc finalize(memory_desc const &mem_desc)
    {
        return {align_up(mem_desc.size, mem_desc.align),
                mem_desc.align};
    }

    // ================================================================================================================
} // namespace memory_of_impl
} // namespace r2

// ====================================================================================================================

constexpr r2::memory_desc r2::operator * (memory_desc const &lhs, std::size_t rhs) noexcept
{
    return {lhs.size * rhs, lhs.align};
}

// --------------------------------------------------------------------------------------------------------------------

constexpr r2::memory_desc r2::operator * (std::size_t lhs, memory_desc const &rhs) noexcept
{
    return {lhs * rhs.size, rhs.align};
}

// ====================================================================================================================

template <typename T>
constexpr r2::memory_desc r2::memory_of() noexcept
{
    return {sizeof(T), alignof(T)};
}

// --------------------------------------------------------------------------------------------------------------------

template <typename T0,
          typename T1,
          typename ...Ts>
constexpr r2::memory_desc r2::memory_of() noexcept
{
    using namespace memory_of_impl;

    return finalize(combine(combine(memory_of<T0>(), memory_of<T1>()),
                            memory_of<Ts>()...));
}

// --------------------------------------------------------------------------------------------------------------------

inline r2::memory_desc r2::memory_of(std::initializer_list<memory_desc> const &mem_descs) noexcept
{
    using namespace memory_of_impl;

    memory_desc result = {};

    for(memory_desc const &mem_desc : mem_descs)
    {
        result = combine(result, mem_desc);
    }

    result = finalize(result);

    return result;
}

// ====================================================================================================================

#endif // R2_MEMORY_OF_HPP
