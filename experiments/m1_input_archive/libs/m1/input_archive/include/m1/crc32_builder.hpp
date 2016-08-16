#ifndef M1_CRC32_BUILDER_HPP
#define M1_CRC32_BUILDER_HPP

#include "m1/string_builder_base.hpp"
#include "m1/crc32.hpp"

namespace m1
{
    // ================================================================================================================

    class crc32_builder
        : public string_builder_base
    {
    public:
        crc32_builder() = default;
        virtual ~crc32_builder() override = default;

        virtual void append(code_point ch) override;

        crc32 crc() &&;

    private:
        crc32_builder(crc32_builder &&rhs) = delete;
        crc32_builder(crc32_builder const &rhs) = delete;
        crc32_builder& operator = (crc32_builder &&rhs) = delete;
        crc32_builder& operator = (crc32_builder const &rhs) = delete;

        // members:
        crc32 m_Crc;
    };

    // ================================================================================================================
} // namespace m1

#endif // M1_CRC32_BUILDER_HPP
