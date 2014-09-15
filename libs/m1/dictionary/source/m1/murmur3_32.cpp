#include "m1/murmur3_32.hpp"
#include <ctime>

// =====================================================================================================================
// m1::murmur3_32
// =====================================================================================================================

std::uint32_t m1::murmur3_32_seed()
{
    static std::uint32_t const seed = static_cast<std::uint32_t>(std::time(NULL));
    return seed;
}

// ---------------------------------------------------------------------------------------------------------------------

std::uint32_t m1::murmur3_32(void const *data,
                             std::uint32_t const data_length,
                             std::uint32_t const seed)
{
    std::uint32_t const block_size = sizeof(std::uint32_t);
    std::uint32_t const c1 = 0xcc9e2d51u;
    std::uint32_t const c2 = 0x1b873593u;
    std::uint32_t const r1 = 15u;
    std::uint32_t const r2 = 13u;
    std::uint32_t const m = 5u;
    std::uint32_t const n = 0xe6546b64u;

    uint32_t hash = seed;

    std::uint32_t const block_count = data_length / block_size;
    std::uint32_t const * const blocks = static_cast<std::uint32_t const*>(data);

    for(std::uint32_t block_index = 0; block_index < block_count; ++block_index)
    {
        std::uint32_t k = blocks[block_index];
        k *= c1;
        k = (k << r1) | (k >> (32u - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32u - r2))) * m + n;
    }

    uint8_t const * const tail = reinterpret_cast<uint8_t const*>(blocks + block_count);

    std::uint32_t k1 = 0u;
    switch(data_length & (block_size - 1u))
    {
        case 3:
            k1 ^= tail[2] << 16u;
        case 2:
            k1 ^= tail[1] << 8u;
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32u - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= data_length;
    hash ^= (hash >> 16u);
    hash *= 0x85ebca6bu;
    hash ^= (hash >> 13u);
    hash *= 0xc2b2ae35u;
    hash ^= (hash >> 16u);

    return hash;
}
