#ifndef M1_SERIALIZATION_PROPERTY_ID_HPP
#define M1_SERIALIZATION_PROPERTY_ID_HPP

#include "m1/crc32.hpp"

namespace m1
{
namespace serialization
{
    // ================================================================================================================

    class property_id
        : private crc32
    {
    public:
        using crc32::crc32;
        constexpr property_id() noexcept = default;
        property_id(property_id &&rhs) noexcept = default;
        property_id(property_id const &rhs) noexcept = default;
        property_id& operator = (property_id &&rhs) noexcept = default;
        property_id& operator = (property_id const &rhs) noexcept = default;
        ~property_id() noexcept = default;

        using crc32::operator std::uint32_t;
    };
} // namespace serialization
} // namespace m1

// ====================================================================================================================

namespace m1
{
inline namespace literals
{
    // ================================================================================================================

    constexpr serialization::property_id operator "" _id(char const *str,
                                                         std::size_t len);

    // ================================================================================================================
} // namespace literals
} // namespace m1

// ====================================================================================================================
// ====================================================================================================================

constexpr m1::serialization::property_id m1::literals::operator "" _id(char const * const str,
                                                                       std::size_t const len)
{
    return serialization::property_id(str, str + len);
}


// ====================================================================================================================

#endif // M1_SERIALIZATION_PROPERTY_ID_HPP
