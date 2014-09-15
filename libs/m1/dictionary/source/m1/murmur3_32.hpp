#ifndef M1_MURMUR3_32_HPP
#define M1_MURMUR3_32_HPP

#include <cstdint>

namespace m1
{
    // =================================================================================================================

    std::uint32_t murmur3_32_seed();

    // -----------------------------------------------------------------------------------------------------------------

    // http://en.wikipedia.org/wiki/MurmurHash#Algorithm
    std::uint32_t murmur3_32(void const *data,
                             std::uint32_t const data_length,
                             std::uint32_t const seed);

    // =================================================================================================================
} // namespace m1

#endif // M1_MURMUR3_32_HPP
